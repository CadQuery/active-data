//-----------------------------------------------------------------------------
// Created on: June 2012
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
#include <ActData_TimeStampParameter.h>

// Active Data includes
#include <ActData_Utils.h>

// OCCT includes
#include <Standard_ProgramError.hxx>
#include <TDataStd_IntegerArray.hxx>

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

//! Default constructor.
ActData_TimeStampParameter::ActData_TimeStampParameter() : ActData_UserParameter()
{
}

//! Ensures correct construction of the Parameter object, e.g. prevents
//! allocating it in stack memory.
//! \return Parameter instance.
Handle(ActData_TimeStampParameter) ActData_TimeStampParameter::Instance()
{
  return new ActData_TimeStampParameter();
}

//! Sets Parameter value.
//! \param theVal [in] value to set.
//! \param theModType [in] Modification Type.
//! \param doResetValidity [in] indicates whether to reset validity flag.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property.
void ActData_TimeStampParameter::SetValue(const Handle(ActAux_TimeStamp)& theVal,
                                          const ActAPI_ModificationType theModType,
                                          const Standard_Boolean doResetValidity,
                                          const Standard_Boolean doResetPending)
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  TDF_Label aDataLab = m_label.FindChild(DS_Value, Standard_True);
  Handle(TDataStd_IntegerArray) aDataAttr = TDataStd_IntegerArray::Set(aDataLab, 0, Item_IsDST);
  Handle(HIntArray) aChunkedTS = ActAux_TimeStampTool::AsChunked(theVal);

  for ( Standard_Integer i = 0; i <= Item_IsDST; i++ )
    aDataAttr->SetValue( i, aChunkedTS->Value(i) );

  // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
  SPRING_INTO_FUNCTION(theModType)
  // Reset Parameter's validity flag if requested
  RESET_VALIDITY(doResetValidity)
  // Reset Parameter's PENDING property
  RESET_PENDING(doResetPending);
}

//! Sets Parameter value for one of its items represening full time structure.
//! \param theItemVal [in] value to set.
//! \param theItemType [in] item to set the value for.
//! \param theModType [in] Modification Type.
//! \param doResetValidity [in] indicates whether to reset validity flag.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property.
void ActData_TimeStampParameter::SetValue(const Standard_Integer theItemVal,
                                          const Item theItemType,
                                          const ActAPI_ModificationType theModType,
                                          const Standard_Boolean doResetValidity,
                                          const Standard_Boolean doResetPending)
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  TDF_Label aDataLab = m_label.FindChild(DS_Value, Standard_True);
  Handle(TDataStd_IntegerArray) aDataAttr = TDataStd_IntegerArray::Set(aDataLab, 0, Item_IsDST);
  aDataAttr->SetValue(theItemType - 1, theItemVal);

  // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
  SPRING_INTO_FUNCTION(theModType)
  // Reset Parameter's validity flag if requested
  RESET_VALIDITY(doResetValidity)
  // Reset Parameter's PENDING property
  RESET_PENDING(doResetPending);
}

//! Accessor for the stored timestamp.
//! \return stored timestamp.
Handle(ActAux_TimeStamp) ActData_TimeStampParameter::GetValue()
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Data inconsistent");

  return ActData_Utils::GetTimeStampValue(m_label, DS_Value);
}

//! Accessor for specific time structure item.
//! \param theItemType [in] time structure item to access.
//! \return stored value.
Standard_Integer ActData_TimeStampParameter::GetValue(const Item theItemType)
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Data inconsistent");

  TDF_Label aDataLab = m_label.FindChild(DS_Value, Standard_False);
  Handle(TDataStd_IntegerArray) aDataAttr;
  aDataLab.FindAttribute(TDataStd_IntegerArray::GetID(), aDataAttr);

  Standard_Integer anItemIndex = ( (Standard_Integer) theItemType ) - 1;
  return aDataAttr->Value(anItemIndex);
}

//! Checks if this Parameter object is mapped onto CAF data structure in a
//! correct way.
//! \return true if the object is well-formed, false -- otherwise.
Standard_Boolean ActData_TimeStampParameter::isWellFormed() const
{
  if ( !ActData_Utils::CheckLabelAttr( m_label, DS_Value,
                                       TDataStd_IntegerArray::GetID() ) )
    return Standard_False;

  return Standard_True;
}

//! Returns Parameter type.
//! \return Parameter type.
Standard_Integer ActData_TimeStampParameter::parameterType() const
{
  return Parameter_TimeStamp;
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
void ActData_TimeStampParameter::setFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
                                            const ActAPI_ModificationType theModType,
                                            const Standard_Boolean doResetValidity,
                                            const Standard_Boolean doResetPending)
{
  Handle(ActData_TimeStampDTO) MyDTO = Handle(ActData_TimeStampDTO)::DownCast(theDTO);
  this->SetValue(MyDTO->TimeStamp, theModType, doResetValidity, doResetPending);
}

//! Creates and populates DTO.
//! \param theGID [in] ready-to-use GID for DTO.
//! \return constructed DTO instance.
Handle(ActData_ParameterDTO)
  ActData_TimeStampParameter::createDTO(const ActAPI_ParameterGID& theGID)
{
  Handle(ActData_TimeStampDTO) aRes = new ActData_TimeStampDTO(theGID);
  aRes->TimeStamp = this->GetValue();
  return aRes;
}
