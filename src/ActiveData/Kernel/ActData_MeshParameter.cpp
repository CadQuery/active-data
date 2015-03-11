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
#include <ActData_MeshParameter.h>

// Active Data includes
#include <ActData_MeshAttr.h>
#include <ActData_Utils.h>

// OCCT includes
#include <Standard_ProgramError.hxx>

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

//! Default constructor.
ActData_MeshParameter::ActData_MeshParameter() : ActData_UserParameter()
{
}

//! Ensures correct construction of the Parameter object, e.g. prevents
//! allocating it in stack memory.
//! \return Parameter instance.
Handle(ActData_MeshParameter) ActData_MeshParameter::Instance()
{
  return new ActData_MeshParameter();
}

//! Switches ON modification delta recording mode.
void ActData_MeshParameter::DeltaModeOn()
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  Handle(ActData_MeshAttr) aMeshAttr = ActData_Utils::AccessMeshAttr(m_label, DS_Mesh);
  if ( aMeshAttr.IsNull() )
    Standard_ProgramError::Raise("Cannot access NULL Mesh DS");

  aMeshAttr->DeltaModeOn();
}

//! Switches OFF modification delta recording mode.
void ActData_MeshParameter::DeltaModeOff()
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  Handle(ActData_MeshAttr) aMeshAttr = ActData_Utils::AccessMeshAttr(m_label, DS_Mesh);
  if ( aMeshAttr.IsNull() )
    Standard_ProgramError::Raise("Cannot access NULL Mesh DS");

  aMeshAttr->DeltaModeOff();
}

//! Sets Mesh data for the Parameter.
//! \param theMesh [in] Mesh data to set.
//! \param theModType [in] Modification Type.
//! \param doResetValidity [in] indicates whether to reset validity flag.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property.
void ActData_MeshParameter::SetMesh(const Handle(ActData_Mesh)& theMesh,
                                    const ActAPI_ModificationType theModType,
                                    const Standard_Boolean doResetValidity,
                                    const Standard_Boolean doResetPending)
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  ActData_Utils::SetMesh(m_label, DS_Mesh, theMesh);

  // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
  SPRING_INTO_FUNCTION(theModType)
  // Reset Parameter's validity flag if requested
  RESET_VALIDITY(doResetValidity)
  // Reset Parameter's PENDING property
  RESET_PENDING(doResetPending);
}

//! Adds a new mesh node with the given co-ordinates.
//! \param theNodeX [in] X co-ordinate.
//! \param theNodeY [in] Y co-ordinate.
//! \param theNodeZ [in] Z co-ordinate.
//! \param theModType [in] Modification Type.
//! \param doResetValidity [in] indicates whether to reset validity flag.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property.
//! \return ID of the just created mesh node.
Standard_Integer
  ActData_MeshParameter::AddNode(const Standard_Real theNodeX,
                                 const Standard_Real theNodeY,
                                 const Standard_Real theNodeZ,
                                 const ActAPI_ModificationType theModType,
                                 const Standard_Boolean doResetValidity,
                                 const Standard_Boolean doResetPending)
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Cannot access BAD-FORMED data");

  Handle(ActData_MeshAttr) aMeshAttr = ActData_Utils::AccessMeshAttr(m_label, DS_Mesh);
  if ( aMeshAttr.IsNull() )
    Standard_ProgramError::Raise("Cannot access NULL Mesh DS");

  Standard_Integer aResID = aMeshAttr->AddNode(theNodeX, theNodeY, theNodeZ);

  // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
  SPRING_INTO_FUNCTION(theModType)
  // Reset Parameter's validity flag if requested
  RESET_VALIDITY(doResetValidity)
  // Reset Parameter's PENDING property
  RESET_PENDING(doResetPending);

  return aResID;
}

//! Adds new mesh element comprised of the given set of mesh nodes.
//! \param theNodes [in] mesh nodes.
//! \param theNbNodes [in] number of nodes.
//! \param theModType [in] Modification Type.
//! \param doResetValidity [in] indicates whether to reset validity flag.
//! \param doResetPending [in] indicates whether this Parameter must lose its
//!        PENDING (or out-dated) property.
//! \return ID of the just created mesh element.
Standard_Integer
  ActData_MeshParameter::AddElement(Standard_Address theNodes,
                                    const Standard_Integer theNbNodes,
                                    const ActAPI_ModificationType theModType,
                                    const Standard_Boolean doResetValidity,
                                    const Standard_Boolean doResetPending)
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Cannot access BAD-FORMED data");

  Handle(ActData_MeshAttr) aMeshAttr = ActData_Utils::AccessMeshAttr(m_label, DS_Mesh);
  if ( aMeshAttr.IsNull() )
    Standard_ProgramError::Raise("Cannot access NULL Mesh DS");

  Standard_Integer aResID = aMeshAttr->AddElement(theNodes, theNbNodes);

  // Mark root label of the Parameter as modified (Touched, Impacted or Silent)
  SPRING_INTO_FUNCTION(theModType)
  // Reset Parameter's validity flag if requested
  RESET_VALIDITY(doResetValidity)
  // Reset Parameter's PENDING property
  RESET_PENDING(doResetPending);

  return aResID;
}

//! Accessor for the stored Mesh DS.
//! \return Mesh DS.
Handle(ActData_Mesh) ActData_MeshParameter::GetMesh()
{
  if ( !this->IsWellFormed() )
    Standard_ProgramError::Raise("Data inconsistent");

  return ActData_Utils::GetMesh(m_label, DS_Mesh);
}

//! Checks if this Parameter object is mapped onto CAF data structure in a
//! correct way.
//! \return true if the object is well-formed, false -- otherwise.
Standard_Boolean ActData_MeshParameter::isWellFormed() const
{
  if ( !ActData_Utils::CheckLabelAttr( m_label, DS_Mesh,
                                       ActData_MeshAttr::GUID() ) )
    return Standard_False;

  return Standard_True;
}

//! Returns Parameter type.
//! \return Parameter type.
Standard_Integer ActData_MeshParameter::parameterType() const
{
  return Parameter_Mesh;
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
void ActData_MeshParameter::setFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
                                      const ActAPI_ModificationType theModType,
                                      const Standard_Boolean doResetValidity,
                                      const Standard_Boolean doResetPending)
{
  Handle(ActData_MeshDTO) MyDTO = Handle(ActData_MeshDTO)::DownCast(theDTO);
  this->SetMesh(MyDTO->Mesh, theModType, doResetValidity, doResetPending);
}

//! Creates and populates DTO.
//! \param theGID [in] ready-to-use GID for DTO.
//! \return constructed DTO instance.
Handle(ActData_ParameterDTO)
  ActData_MeshParameter::createDTO(const ActAPI_ParameterGID& theGID)
{
  Handle(ActData_MeshDTO) aRes = new ActData_MeshDTO(theGID);
  aRes->Mesh = this->GetMesh();
  return aRes;
}
