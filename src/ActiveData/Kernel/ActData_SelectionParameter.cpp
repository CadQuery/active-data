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
#include <ActData_SelectionParameter.h>

// Active Data includes
#include <ActData_Utils.h>

// OCCT includes
#include <Standard_ProgramError.hxx>
#include <TDataStd_IntPackedMap.hxx>

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

//! Default constructor.
ActData_SelectionParameter::ActData_SelectionParameter() : ActData_UserParameter()
{
}

//! Ensures correct construction of the Parameter object, e.g. prevents
//! allocating it in stack memory.
//! \return Parameter instance.
Handle(ActData_SelectionParameter) ActData_SelectionParameter::Instance()
{
  return new ActData_SelectionParameter();
}

//! Sets entire selection mask.
//! \param theMask [in] mask to set.
//! \param theModType [in] modification type.
//! \param doResetValidity [in] indicates whether to reset validity flag.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property.
void ActData_SelectionParameter::SetMask(const Handle(TColStd_HPackedMapOfInteger)& theMask,
                                         const ActAPI_ModificationType theModType,
                                         const Standard_Boolean doResetValidity,
                                         const Standard_Boolean doResetPending)
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  ActData_Utils::SetIntPackedMap(m_label, DS_IntPackedMap, theMask);

  // Record modification in LogBook:
  // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
  SPRING_INTO_FUNCTION(theModType)
  // Reset Parameter's validity flag if requested
  RESET_VALIDITY(doResetValidity)
  // Reset Parameter's PENDING property
  RESET_PENDING(doResetPending);
}

//! Adds the passed ID to the mask.
//! \param theID [in] ID to add.
//! \param theModType [in] modification type.
//! \param doResetValidity [in] indicates whether to reset validity flag.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property.
//! \return true if ID has been added, false -- otherwise.
Standard_Boolean
  ActData_SelectionParameter::Add(const Standard_Integer theID,
                                  const ActAPI_ModificationType theModType,
                                  const Standard_Boolean doResetValidity,
                                  const Standard_Boolean doResetPending)
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Cannot affect BAD-FORMED data");

  Standard_Boolean
    aResult = ActData_Utils::AddIntPackedMapValue(m_label, DS_IntPackedMap, theID);

  if ( aResult )
  {
    // Record modification in LogBook:
    // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
    SPRING_INTO_FUNCTION(theModType)
    // Reset Parameter's validity flag if requested
    RESET_VALIDITY(doResetValidity)
    // Reset Parameter's PENDING property
    RESET_PENDING(doResetPending);
  }

  return aResult;
}

//! Removes the passed ID from the mask.
//! \param theID [in] ID to remove.
//! \param theModType [in] modification type.
//! \param doResetValidity [in] indicates whether to reset validity flag.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property.
//! \return true if ID has been removed, false -- otherwise.
Standard_Boolean
  ActData_SelectionParameter::Remove(const Standard_Integer theID,
                                     const ActAPI_ModificationType theModType,
                                     const Standard_Boolean doResetValidity,
                                     const Standard_Boolean doResetPending)
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Cannot affect BAD-FORMED data");

  Standard_Boolean
    aResult = ActData_Utils::RemoveIntPackedMapValue(m_label, DS_IntPackedMap, theID);

  if ( aResult )
  {
    // Record modification in LogBook:
    // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
    SPRING_INTO_FUNCTION(theModType)
    // Reset Parameter's validity flag if requested
    RESET_VALIDITY(doResetValidity)
    // Reset Parameter's PENDING property
    RESET_PENDING(doResetPending);
  }

  return aResult;
}

//! Checks whether the passed ID belongs to the mask.
//! \param theID [in] ID to check.
//! \return true/false.
Standard_Boolean
  ActData_SelectionParameter::Contains(const Standard_Integer theID)
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Cannot access BAD-FORMED data");

  return ActData_Utils::HasIntPackedMapValue(m_label, DS_IntPackedMap, theID);
}

//! Returns the size of the mask (number of masked IDs).
//! \return size of the mask.
Standard_Integer
  ActData_SelectionParameter::Size()
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Cannot access BAD-FORMED data");

  return ActData_Utils::GetIntPackedMap(m_label, DS_IntPackedMap)->Map().Extent();
}

//! Returns entire mask.
//! \return mask.
Handle(TColStd_HPackedMapOfInteger) ActData_SelectionParameter::GetMask()
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Cannot access BAD-FORMED data");

  return ActData_Utils::GetIntPackedMap(m_label, DS_IntPackedMap);
}

//! Checks if this Parameter object is mapped onto CAF data structure in a
//! correct way.
//! \return true if the object is well-formed, false -- otherwise.
Standard_Boolean ActData_SelectionParameter::isWellFormed() const
{
  if ( !ActData_Utils::CheckLabelAttr( m_label, DS_IntPackedMap,
                                       TDataStd_IntPackedMap::GetID() ) )
    return Standard_False;

  return Standard_True;
}

//! Returns Parameter type.
//! \return Parameter type.
Standard_Integer ActData_SelectionParameter::parameterType() const
{
  return Parameter_Selection;
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
void ActData_SelectionParameter::setFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
                                            const ActAPI_ModificationType theModType,
                                            const Standard_Boolean doResetValidity,
                                            const Standard_Boolean doResetPending)
{
  Handle(ActData_SelectionDTO) MyDTO = Handle(ActData_SelectionDTO)::DownCast(theDTO);
  this->SetMask(MyDTO->Mask, theModType, doResetValidity, doResetPending);
}

//! Creates and populates DTO.
//! \param theGID [in] ready-to-use GID for DTO.
//! \return constructed DTO instance.
Handle(ActData_ParameterDTO)
  ActData_SelectionParameter::createDTO(const ActAPI_ParameterGID& theGID)
{
  Handle(ActData_SelectionDTO) aRes = new ActData_SelectionDTO(theGID);
  aRes->Mask = this->GetMask();
  return aRes;
}
