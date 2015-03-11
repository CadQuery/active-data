//-----------------------------------------------------------------------------
// Created on: May 2012
//-----------------------------------------------------------------------------
// Copyright (c) 2017 Sergey Slyadnev
// Code covered by the MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// Web: http://dev.opencascade.org
//-----------------------------------------------------------------------------

// Own include
#include <ActData_CAFConverter.h>

// Active Data includes
#include <ActData_BaseModel.h>
#include <ActData_BasePartition.h>

// OCCT includes
#include <Message_ProgressSentry.hxx>

//! Constructor accepting the conversion stream managed by this CAF Converter
//! instance.
//! \param theCStream [in] conversion stream.
ActData_CAFConverter::ActData_CAFConverter(const ActData_ConversionStream& theCStream)
  : Standard_Transient()
{
  for ( ActData_ConversionTupleSequence::Iterator it( *theCStream.List.operator->() );
        it.More(); it.Next() )
  {
    this->registerConversionRoutine( it.Value() );
  }
}

//! Performs conversion of the Data Model from the passed older version
//! to the given newer one. Returns false if such conversion is impossible.
//! \param theModel [in/out] Data Model to convert.
//! \param theOldVer [in] older version to perform conversion from.
//! \param theNewVer [in] newer version to perform conversion to.
//! \param theProgress [in] Progress Indicator.
//! \return true/false.
Standard_Boolean
  ActData_CAFConverter::Perform(Handle(ActAPI_IModel)& theModel,
                                const Standard_Integer theOldVer,
                                const Standard_Integer theNewVer,
                                const Handle(Message_ProgressIndicator)& theProgress)
{
  Handle(ActData_BaseModel) aModelBase = Handle(ActData_BaseModel)::DownCast(theModel);

  // Prepare a sequence of conversion routines to apply.
  ActData_ConversionSequence aCSeq;

  // Iterate over the conversion repository in order to check if the
  // ultimate version is reachable
  Standard_Integer aNextVer = -1, aCurrentOldVer = theOldVer;
  Standard_Boolean isNewVerReachable = Standard_True;
  while ( aNextVer != theNewVer )
  {
    aNextVer = m_conversionMap.NewByOld(aCurrentOldVer);
    if ( aNextVer == -1 )
    {
      isNewVerReachable = Standard_False;
      break;
    }
    aCSeq.Append( m_conversionMap.RoutineByDelta( ActData_VersionDelta(aCurrentOldVer, aNextVer) ) );
    aCurrentOldVer = aNextVer;
  }

  if ( !isNewVerReachable )
    return Standard_False;

  // Prepare progress entry
  Message_ProgressSentry PEntry(theProgress, "CAF_CONVERSION_TRAVERSING", 0, aCSeq.Length(), 1);
  PEntry.Show();

  // Apply the conversion sequence
  for ( ActData_ConversionSequence::Iterator it(aCSeq); it.More(); it.Next() )
  {
    const ActData_ConversionRoutine& aRoutine = it.Value();
    theModel->DisableTransactions();
    Standard_Boolean aConvRes = (*aRoutine)(theModel, theProgress);
    if ( !aConvRes )
    {
      return Standard_False;
    }
    PEntry.Next();
    PEntry.Show();
  }

  return Standard_True;
}

//! Performs registration of the given conversion routine for the passed
//! version delta.
//! \param theTuple [in] coversion tuple.
void ActData_CAFConverter::registerConversionRoutine(const ActData_ConversionTuple& theTuple)
{
  m_conversionMap.BindRoutine(theTuple);
}
