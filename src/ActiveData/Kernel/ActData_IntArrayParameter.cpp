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
#include <ActData_IntArrayParameter.h>

// Active Data includes
#include <ActData_Utils.h>

// OCCT includes
#include <Standard_ProgramError.hxx>
#include <TDataStd_Integer.hxx>
#include <TDataStd_IntegerArray.hxx>

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

//! Default constructor.
ActData_IntArrayParameter::ActData_IntArrayParameter() : ActData_UserParameter()
{
}

//! Ensures correct construction of the Parameter object, e.g. prevents
//! allocating it in stack memory.
//! \return Parameter instance.
Handle(ActData_IntArrayParameter) ActData_IntArrayParameter::Instance()
{
  return new ActData_IntArrayParameter();
}

//! Initializes Parameter with empty array. Actually, this means that the
//! internal OCAF structures are prepared as usual. However, no data is
//! recorded there (array is just NULL), so the Attribute is kept dummy.
void ActData_IntArrayParameter::InitEmpty()
{
  // Clean up array
  ActData_Utils::ChooseLabelByTag(m_label, DS_Array, Standard_True).ForgetAllAttributes();

  // Store Array dimension
  ActData_Utils::SetIntegerValue(m_label, DS_ElemNum, 0);
}

//! Back-ups the underlying array data for transactional usage.
void ActData_IntArrayParameter::BackupArray()
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Data inconsistent");

  ActData_Utils::BackupIntegerArray(m_label, DS_Array);
}

//! Sets value for a single element.
//! \param theIndex [in] index of the element to set.
//! \param theValue [in] value to set.
//! \param theModType [in] modification type.
//! \param doResetValidity [in] indicates whether this Parameter must be
//!        switched to VALID state automatically. Pass FALSE if you want
//!        to treat this flag manually. TRUE is the default value.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property. Pass FALSE if you want to treat
//!        this flag manually. TRUE is the default value.
void ActData_IntArrayParameter::SetElement(const Standard_Integer theIndex,
                                           const Standard_Integer theValue,
                                           const ActAPI_ModificationType theModType,
                                           const Standard_Boolean doResetValidity,
                                           const Standard_Boolean doResetPending)
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Data inconsistent");

  if ( theIndex > this->NbElements() )
    Standard_Failure::Raise("SetElement -- out of range");

  ActData_Utils::SetIntegerArrayElem(m_label, DS_Array, theIndex, theValue);

  // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
  SPRING_INTO_FUNCTION(theModType)
  // Reset Parameter's validity flag if requested
  RESET_VALIDITY(doResetValidity)
  // Reset Parameter's PENDING property
  RESET_PENDING(doResetPending);
}

//! Returns element for the given index.
//! \param theIndex [in] index of the element to access.
//! \return requested element.
Standard_Integer
  ActData_IntArrayParameter::GetElement(const Standard_Integer theIndex)
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Data inconsistent");

  if ( theIndex > this->NbElements() )
    Standard_Failure::Raise("GetElement -- out of range");

  return ActData_Utils::GetIntegerArrayElem(m_label, DS_Array, theIndex);
}

//! Sets entire array.
//! \param theArray [in] array to set.
//! \param theModType [in] modification type.
//! \param doResetValidity [in] indicates whether this Parameter must be
//!        switched to VALID state automatically. Pass FALSE if you want
//!        to treat this flag manually. TRUE is the default value.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property. Pass FALSE if you want to treat
//!        this flag manually. TRUE is the default value.
void ActData_IntArrayParameter::SetArray(const Handle(HIntArray)& theArray,
                                         const ActAPI_ModificationType theModType,
                                         const Standard_Boolean doResetValidity,
                                         const Standard_Boolean doResetPending)
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  if ( theArray.IsNull() )
    this->InitEmpty();
  else
  {
    // Store Array data
    ActData_Utils::InitIntegerArray(m_label, DS_Array, theArray);

    // Store Array dimension
    ActData_Utils::SetIntegerValue( m_label, DS_ElemNum, theArray->Length() );
  }

  // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
  SPRING_INTO_FUNCTION(theModType)
  // Reset Parameter's validity flag if requested
  RESET_VALIDITY(doResetValidity)
  // Reset Parameter's PENDING property
  RESET_PENDING(doResetPending);
}

//! Accessor for the stored array data.
//! \return stored array.
Handle(HIntArray) ActData_IntArrayParameter::GetArray()
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Data inconsistent");

  return ActData_Utils::GetIntegerArray(m_label, DS_Array);
}

//! Returns number of elements in the stored array.
//! \return number of elements.
Standard_Integer ActData_IntArrayParameter::NbElements()
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Data inconsistent");

  Standard_Integer aValue;
  ActData_Utils::GetIntegerValue(m_label, DS_ElemNum, aValue);
  return aValue;
}

//! Checks if this Parameter object is mapped onto CAF data structure in a
//! correct way.
//! \return true if the object is well-formed, false -- otherwise.
Standard_Boolean ActData_IntArrayParameter::isWellFormed() const
{
  // Missing DS_Array Attribute means EMPTY array for us. We do not use
  // empty Attributes just in order not to loose them on storage/retrieval

  if ( !ActData_Utils::CheckLabelAttr( m_label, DS_ElemNum,
                                       TDataStd_Integer::GetID() ) )
    return Standard_False;

  return Standard_True;
}

//! Returns Parameter type.
//! \return Parameter type.
Standard_Integer ActData_IntArrayParameter::parameterType() const
{
  return Parameter_IntArray;
}

//-----------------------------------------------------------------------------
// DTO construction
//-----------------------------------------------------------------------------

//! Populates Parameter from the passed DTO.
//! \param theDTO [in] DTO to source data from.
//! \param theModType [in] modification type.
//! \param doResetValidity [in] indicates whether validity flag must be
//!        reset or not.
//! \param doResetPending [in] indicates whether pending flag must be reset
//!        or not.
void ActData_IntArrayParameter::setFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
                                           const ActAPI_ModificationType theModType,
                                           const Standard_Boolean doResetValidity,
                                           const Standard_Boolean doResetPending)
{
  Handle(ActData_IntArrayDTO) MyDTO = Handle(ActData_IntArrayDTO)::DownCast(theDTO);
  this->SetArray(MyDTO->Array, theModType, doResetValidity, doResetPending);
}

//! Creates and populates DTO.
//! \param theGID [in] ready-to-use GID for DTO.
//! \return constructed DTO instance.
Handle(ActData_ParameterDTO)
  ActData_IntArrayParameter::createDTO(const ActAPI_ParameterGID& theGID)
{
  Handle(ActData_IntArrayDTO) aRes = new ActData_IntArrayDTO(theGID);
  aRes->Array = this->GetArray();
  return aRes;
}
