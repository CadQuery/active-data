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

#ifndef ActData_MeshParameter_HeaderFile
#define ActData_MeshParameter_HeaderFile

// Active Data includes
#include <ActData_UserParameter.h>
#include <ActData_Common.h>
#include <ActData_ParameterDTO.h>

// Mesh includes
#include <Mesh.h>

//-----------------------------------------------------------------------------
// Parameter DTO
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_MeshDTO, ActData_ParameterDTO)

//! \ingroup AD_DF
//!
//! Data Transfer Object (DTO) corresponding to data wrapped with
//! Mesh Parameter without any OCAF connectivity.
class ActData_MeshDTO : public ActData_ParameterDTO
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_MeshDTO, ActData_ParameterDTO)

public:

  //! Constructor accepting GID.
  //! \param theGID [in] GID.
  ActData_MeshDTO(const ActAPI_ParameterGID& theGID) : ActData_ParameterDTO( theGID, Parameter_Mesh ) {}

public:

  Handle(ActData_Mesh) Mesh; //!< Actual mesh.

};

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_MeshParameter, ActData_UserParameter)

//! \ingroup AD_DF
//!
//! Parameter class representing Mesh data.
class ActData_MeshParameter : public ActData_UserParameter
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_MeshParameter, ActData_UserParameter)

public:

  ActData_EXPORT static Handle(ActData_MeshParameter) Instance();

public:

  ActData_EXPORT void
    DeltaModeOn();

  ActData_EXPORT void
    DeltaModeOff();

  ActData_EXPORT void
    SetMesh(const Handle(ActData_Mesh)& theMesh,
            const ActAPI_ModificationType theModType = MT_Touched,
            const Standard_Boolean doResetValidity = Standard_True,
            const Standard_Boolean doResetPending = Standard_True);

  ActData_EXPORT Standard_Integer
    AddNode(const Standard_Real theNodeX,
            const Standard_Real theNodeY,
            const Standard_Real theNodeZ,
            const ActAPI_ModificationType theModType = MT_Touched,
            const Standard_Boolean doResetValidity = Standard_True,
            const Standard_Boolean doResetPending = Standard_True);

  ActData_EXPORT Standard_Integer
    AddElement(Standard_Address theNodes,
               const Standard_Integer theNbNodes,
               const ActAPI_ModificationType theModType = MT_Touched,
               const Standard_Boolean doResetValidity = Standard_True,
               const Standard_Boolean doResetPending = Standard_True);

  ActData_EXPORT Handle(ActData_Mesh)
    GetMesh();

private:

  ActData_MeshParameter();

private:

  virtual Standard_Boolean isWellFormed() const;
  virtual Standard_Integer parameterType() const;

private:

  virtual void
    setFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
               const ActAPI_ModificationType theModType = MT_Touched,
               const Standard_Boolean doResetValidity = Standard_True,
               const Standard_Boolean doResetPending = Standard_True);

  virtual Handle(ActData_ParameterDTO)
    createDTO(const ActAPI_ParameterGID& theGID);

private:

  //! Tags range for storage mapping.
  enum Datum
  {
    DS_Mesh = ActData_UserParameter::DS_DatumLast,
    DS_DatumLast = DS_Mesh + RESERVED_DATUM_RANGE
  };

};

#endif
