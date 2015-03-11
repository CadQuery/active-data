//-----------------------------------------------------------------------------
// Created on: April 2014
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

// Active Data includes
#include <ActData_RealArrayOwnerAPI.h>

// Active Data (auxiliary) includes
#include <ActAux_ArrayUtils.h>

//! Appends the passed element to the end of the stored array.
//! \param theArrPID [in] ID of the Real Array Parameter containing
//!        actual data.
//! \param theVal [in] data to add.
void ActData_RealArrayOwnerAPI::AddElement(const Standard_Integer theArrPID,
                                           const Standard_Real theVal)
{
  Handle(HRealArray) aSourceArr = this->arrParam(theArrPID)->GetArray();
  Handle(HRealArray) aResArr =
    ActAux_ArrayUtils::Append<HRealArray, Handle(HRealArray), Standard_Real>(aSourceArr, theVal);
  this->arrParam(theArrPID)->SetArray(aResArr);
}

//! Prepends the passed data to the beginning of the stored array.
//! \param theArrPID [in] ID of the Real Array Parameter containing
//!        actual data.
//! \param theVal [in] data to prepend.
void ActData_RealArrayOwnerAPI::PrependElement(const Standard_Integer theArrPID,
                                               const Standard_Real theVal)
{
  Handle(HRealArray) aSourceArr = this->arrParam(theArrPID)->GetArray();
  Handle(HRealArray) aResArr =
    ActAux_ArrayUtils::Prepend<HRealArray, Handle(HRealArray), Standard_Real>(aSourceArr, theVal);
  this->arrParam(theArrPID)->SetArray(aResArr);
}

//! Removes the element referred to by the given index.
//! \param theArrPID [in] ID of the Real Array Parameter containing
//!        actual data.
//! \param theIndex [in] index of the element in the internal collection.
//! \return true in case of success, false -- otherwise.
Standard_Boolean
  ActData_RealArrayOwnerAPI::RemoveElement(const Standard_Integer theArrPID,
                                           const Standard_Integer theIndex)
{
  Handle(HRealArray) aSourceArr = this->arrParam(theArrPID)->GetArray();
  Handle(HRealArray) aResArr =
    ActAux_ArrayUtils::Remove<HRealArray, Handle(HRealArray)>(aSourceArr, theIndex);
  this->arrParam(theArrPID)->SetArray(aResArr);

  const Standard_Integer resLen = ( aResArr.IsNull() ? 0 : aResArr->Length() );
  const Standard_Integer srcLen = ( aSourceArr.IsNull() ? 0 : aSourceArr->Length() );

  return resLen != srcLen;
}

//! Inserts the given data after another item referred to by the passed index.
//! \param theArrPID [in] ID of the Real Array Parameter containing
//!        actual data.
//! \param theIndex [in] index of the element to insert the new one after.
//! \param theVal [in] data to insert.
void ActData_RealArrayOwnerAPI::InsertElementAfter(const Standard_Integer theArrPID,
                                                   const Standard_Integer theIndex,
                                                   const Standard_Real theVal)
{
  if ( theIndex == -1 )
    this->PrependElement(theArrPID, theVal);
  else if ( theIndex == (this->NbElements(theArrPID) - 1) )
    this->AddElement(theArrPID, theVal);
  else
  {
    Handle(HRealArray) aSourceArr = this->arrParam(theArrPID)->GetArray();
    Handle(HRealArray) aResArr =
      ActAux_ArrayUtils::InsertAfter<HRealArray, Handle(HRealArray), Standard_Real>(aSourceArr, theVal, theIndex);
    this->arrParam(theArrPID)->SetArray(aResArr);
  }
}

//! Accessor for the element referred to by the passed index.
//! \param theArrPID [in] ID of the Real Array Parameter containing
//!        actual data.
//! \param theIndex [in] index of the element to access.
//! \return requested data.
Standard_Real
  ActData_RealArrayOwnerAPI::GetElement(const Standard_Integer theArrPID,
                                        const Standard_Integer theIndex) const
{
  Handle(ActData_RealArrayParameter) p = this->arrParam(theArrPID);
  if ( p.IsNull() || !p->IsWellFormed() )
    return DBL_MAX;

  return p->GetElement(theIndex);
}

//! Sets element.
//! \param theArrPID [in] ID of the Real Array Parameter containing
//!        actual data.
//! \param theIndex [in] index of the element to set.
//! \param theVal [in] value to set.
void ActData_RealArrayOwnerAPI::SetElement(const Standard_Integer theArrPID,
                                           const Standard_Integer theIndex,
                                           const Standard_Real theVal) const
{
  Handle(ActData_RealArrayParameter) p = this->arrParam(theArrPID);
  if ( p.IsNull() || !p->IsWellFormed() )
    return;

  p->SetElement(theIndex, theVal);
}

//! Returns the number of stored element.
//! \param theArrPID [in] ID of the Real Array Parameter containing
//!        actual data.
//! \return number of elements.
Standard_Integer
  ActData_RealArrayOwnerAPI::NbElements(const Standard_Integer theArrPID) const
{
  Handle(ActData_RealArrayParameter) p = this->arrParam(theArrPID);
  if ( p.IsNull() || !p->IsWellFormed() )
    return 0;

  return p->NbElements();
}

//! Convenient accessor for the Real Array Parameter identified by
//! the given ID.
//! \param theArrPID [in] ID of the Real Array Parameter to access.
//! \return requested Parameter.
Handle(ActData_RealArrayParameter)
  ActData_RealArrayOwnerAPI::arrParam(const Standard_Integer theArrPID) const
{
  return ActParamTool::AsRealArray( this->RealArraySource()->Parameter(theArrPID) );
}
