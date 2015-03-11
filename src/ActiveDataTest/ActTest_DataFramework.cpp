//-----------------------------------------------------------------------------
// Created on: March 2012
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
#include <ActTest_DataFramework.h>

// Active Data includes
#include <ActData_Application.h>

Standard_Integer ActTest_DataFramework::PARAM_TAG = 1;

//-----------------------------------------------------------------------------
// Test functions support
//-----------------------------------------------------------------------------

//! Initializes CAF document.
//! \return CAF document.
Handle(TDocStd_Document) ActTest_DataFramework::initCAFDocument()
{
  Handle(TDocStd_Document) doc;
  ActData_Application::Instance()->NewDocument(ACTBinFormat, doc);
  doc->SetModificationMode(Standard_True);
  doc->SetUndoLimit(10);
  return doc;
}

//! Saves the internal CAF document to file with the passed name.
//! \param doc [in] CAF document to save.
//! \param filename [in] filename.
//! \return true in case of success, false -- otherwise.
Standard_Boolean
  ActTest_DataFramework::saveDocument(const Handle(TDocStd_Document)& doc,
                                      const TCollection_AsciiString& filename)
{
  if ( doc.IsNull() )
    Standard_ProgramError::Raise("Cannot save NULL Document");

  PCDM_StoreStatus
    aStat = ActData_Application::Instance()->SaveAs(doc, filename);

  return aStat == PCDM_SS_OK;
}

//! Loads the CAF document from the file with the passed name.
//! \param filename [in] filename.
//! \param doc [out] document retrieved from file.
//! \return true in case of success, false -- otherwise.
Standard_Boolean
  ActTest_DataFramework::openDocument(const TCollection_AsciiString& filename,
                                      Handle(TDocStd_Document)& doc)
{
  doc.Nullify();
  PCDM_ReaderStatus
    aStat = ActData_Application::Instance()->Open(filename, doc);

  if ( aStat != PCDM_RS_OK )
    return Standard_False;

  doc->SetModificationMode(Standard_True);
  doc->SetUndoLimit(10);

  return Standard_True;
}

//! Creates new Parameter of the passed type.
//! \param doc [in] working CAF document.
//! \param type [in] type of the Parameter to allocate.
//! \return Parameter instance.
Handle(ActAPI_IUserParameter)
  ActTest_DataFramework::createParameter(const Handle(TDocStd_Document)& doc,
                                         const ActAPI_ParameterType type)
{
  TDF_Label aParamLab = nextParameterLabel(doc);
  Handle(ActAPI_IUserParameter)
    aParam = ActData_ParameterFactory::NewParameterExpand(type, aParamLab);

  TEST_PRINT_DECOR_L("    |")
  TEST_PRINT_DECOR  ("    +---> ")
  TEST_PRINT        ("Created Parameter with ID: ")
  TEST_PRINT_L      ( aParam->GetId().ToCString() )

  return aParam;
}

//! Creates new Parameter of the passed type returning the corresponding TDF
//! Label as an output argument.
//! \param doc [in] working CAF document.
//! \param type [in] type of the Parameter.
//! \param newLabel [out] just created TDF Label.
//! \return new Parameter.
Handle(ActAPI_IUserParameter)
  ActTest_DataFramework::createParameter(const Handle(TDocStd_Document)& doc,
                                         const ActAPI_ParameterType type,
                                         TDF_Label& newLabel)
{
  newLabel = nextParameterLabel(doc);
  Handle(ActAPI_IUserParameter)
    aParam = ActData_ParameterFactory::NewParameterExpand(type, newLabel);

  TEST_PRINT_DECOR_L("    |")
  TEST_PRINT_DECOR  ("    +---> ")
  TEST_PRINT        ("Created Parameter with ID: ")
  TEST_PRINT_L      ( aParam->GetId().ToCString() )

  return aParam;
}

//! Returns next TDF Label for settling down a Parameter.
//! \param doc [in] working CAF document.
//! \return TDF Label.
TDF_Label ActTest_DataFramework::nextParameterLabel(const Handle(TDocStd_Document)& doc)
{
  return doc->Main().Root().FindChild(nextParameterTag(), Standard_True);
}

//! Returns next Tag for Parameter Labels.
//! \return integer Tag.
Standard_Integer ActTest_DataFramework::nextParameterTag()
{
  return PARAM_TAG++;
}

//-----------------------------------------------------------------------------
// Methods for working with graphs and trees
//-----------------------------------------------------------------------------

//! Checks whether the passed Label entry is expected to be found on the passed
//! level of a graph or tree.
//! \param theLevel [in] actual level the Label is found on.
//! \param theEntry [in] entry of the Label.
//! \param theEntriesByLevels [in] reference collection to check the Label against.
//! \return true if the Label is in place, false -- otherwise.
Standard_Boolean
  ActTest_DataFramework::isLabelExpectedByLevel(const Standard_Integer theLevel,
                                                const TCollection_AsciiString& theEntry,
                                                const EntriesByLevels& theEntriesByLevels)
{
  Standard_Boolean isFound = Standard_False;
  const EntryList& theEntriesByLevel = theEntriesByLevels.Value(theLevel);
  EntryList::Iterator anEntryIt(theEntriesByLevel);
  for ( ; anEntryIt.More(); anEntryIt.Next() )
  {
    const TCollection_AsciiString& anEntry = anEntryIt.Value();
    if ( anEntry == theEntry )
    {
      isFound = Standard_True;
      break;
    }
  }
  return isFound;
}
