//-----------------------------------------------------------------------------
// Created on: February 2012
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
#include <ActData_AsciiStringParameter.h>

// Active Data includes
#include <ActData_Utils.h>

// OCCT includes
#include <Standard_ProgramError.hxx>
#include <TDataStd_AsciiString.hxx>

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

//! Default constructor.
ActData_AsciiStringParameter::ActData_AsciiStringParameter() : ActData_UserParameter()
{
}

//! Ensures correct construction of the Parameter object, e.g. prevents
//! allocating it in stack memory.
//! \return Parameter instance.
Handle(ActData_AsciiStringParameter) ActData_AsciiStringParameter::Instance()
{
  return new ActData_AsciiStringParameter();
}

//! Sets ASCII string value.
//! \param theString [in] value to set.
//! \param theModType [in] modification marker to record the corresponding
//!        modification request in the global LogBook utilized by Tree
//!        Function mechanism. The default value is TOUCHED, indicating that
//!        this value has been affected by user (e.g. via GUI), rather than
//!        via Tree Function execution routine itself (the corresponding
//!        marker is IMPACTED in that case). Another possible value is
//!        SILENT, indicating that current modification should not result
//!        in execution of Tree Function mechanism. Notice that if the
//!        affected Parameter is not involved into Tree Function dependency
//!        graph (i.e. it is neither INPUT nor OUTPUT Parameter for any
//!        Tree Function), the actual value of theModType argument makes
//!        no sense. The entire set of modification records will be cleaned
//!        up after the application requests execution of Tree Function
//!        graph. Therefore, LogBook contains modification records for single
//!        current working Data Model session only.
//! \param doResetValidity [in] indicates whether this Parameter must be
//!        switched to VALID state automatically. Pass FALSE if you want
//!        to treat this flag manually. TRUE is the default value.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property. Pass FALSE if you want to treat
//!        this flag manually. TRUE is the default value.
void ActData_AsciiStringParameter::SetValue(const TCollection_AsciiString& theString,
                                            const ActAPI_ModificationType theModType,
                                            const Standard_Boolean doResetValidity,
                                            const Standard_Boolean doResetPending)
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  ActData_Utils::SetAsciiStringValue(m_label, DS_Value, theString);

  // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
  SPRING_INTO_FUNCTION(theModType)
  // Reset Parameter's validity flag if requested
  RESET_VALIDITY(doResetValidity)
  // Reset Parameter's PENDING property
  RESET_PENDING(doResetPending);
}

//! Accessor for the underlying ASCII string value.
//! \return requested value.
TCollection_AsciiString ActData_AsciiStringParameter::GetValue()
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Data inconsistent");

  return ActData_Utils::GetAsciiStringValue(m_label, DS_Value);
}

//! Checks if this Parameter object is mapped onto CAF data structure in a
//! correct way.
//! \return true if the object is well-formed, false -- otherwise.
Standard_Boolean ActData_AsciiStringParameter::isWellFormed() const
{
  if ( !ActData_Utils::CheckLabelAttr( m_label, DS_Value,
                                       TDataStd_AsciiString::GetID() ) )
    return Standard_False;

  return Standard_True;
}

//! Returns Parameter type.
//! \return Parameter type.
Standard_Integer ActData_AsciiStringParameter::parameterType() const
{
  return Parameter_AsciiString;
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
void ActData_AsciiStringParameter::setFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
                                              const ActAPI_ModificationType theModType,
                                              const Standard_Boolean doResetValidity,
                                              const Standard_Boolean doResetPending)
{
  Handle(ActData_AsciiStringDTO) MyDTO = Handle(ActData_AsciiStringDTO)::DownCast(theDTO);
  this->SetValue(MyDTO->Value, theModType, doResetValidity, doResetPending);
}

//! Creates and populates DTO.
//! \param theGID [in] ready-to-use GID for DTO.
//! \return constructed DTO instance.
Handle(ActData_ParameterDTO)
  ActData_AsciiStringParameter::createDTO(const ActAPI_ParameterGID& theGID)
{
  Handle(ActData_AsciiStringDTO) aRes = new ActData_AsciiStringDTO(theGID);
  aRes->Value = this->GetValue();
  return aRes;
}
