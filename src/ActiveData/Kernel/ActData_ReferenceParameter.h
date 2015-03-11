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

#ifndef ActData_ReferenceParameter_HeaderFile
#define ActData_ReferenceParameter_HeaderFile

// Active Data includes
#include <ActData_UserParameter.h>
#include <ActData_Common.h>

// OCCT includes
#include <TDF_LabelList.hxx>

//-----------------------------------------------------------------------------
// Parameter DTO
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_ReferenceDTO, ActData_ParameterDTO)

//! \ingroup AD_DF
//!
//! Data Transfer Object (DTO) corresponding to data wrapped with
//! Reference Parameter without any OCAF connectivity.
class ActData_ReferenceDTO : public ActData_ParameterDTO
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_ReferenceDTO, ActData_ParameterDTO)

public:

  //! Constructor accepting GID.
  //! \param theGID [in] GID.
  ActData_ReferenceDTO(const ActAPI_ParameterGID& theGID)
  : ActData_ParameterDTO( theGID, Parameter_Reference ),
    Target(NULL)
  {}

public:

  Handle(ActAPI_IDataCursor) Target; //!< Reference target.

};

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_ReferenceParameter, ActData_UserParameter)

//! \ingroup AD_DF
//!
//! Parameter representing a reference onto CAF TDF Label corresponding to the
//! root of some Data Object (e.g. Node or Parameter).
class ActData_ReferenceParameter : public ActData_UserParameter
{
friend class ActData_BaseNode;
friend class ActData_BaseModel;

public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_ReferenceParameter, ActData_UserParameter)

public:

  //! Managed reference types.
  enum RefType
  {
    Ref_Undefined = 1,
    Ref_Parameter,
    Ref_Node
  };

public:

  ActData_EXPORT static Handle(ActData_ReferenceParameter)
    Instance();

  ActData_EXPORT void
    SetTarget(const TDF_Label& theLabel,
              const ActAPI_ModificationType theModType = MT_Touched,
              const Standard_Boolean doResetValidity = Standard_True,
              const Standard_Boolean doResetPending = Standard_True);

  ActData_EXPORT void
    SetTarget(const Handle(ActAPI_IDataCursor)& theDC,
              const ActAPI_ModificationType theModType = MT_Touched,
              const Standard_Boolean doResetValidity = Standard_True,
              const Standard_Boolean doResetPending = Standard_True);

  ActData_EXPORT Handle(ActAPI_IDataCursor)
    GetTarget(const RefType theRefType) const;

  ActData_EXPORT Handle(ActAPI_IDataCursor)
    GetTarget() const;

  ActData_EXPORT TDF_Label
    GetTargetLabel() const;

  ActData_EXPORT Standard_Boolean
    IsTarget(const Handle(ActAPI_IDataCursor)& theDC);

  ActData_EXPORT void
    RemoveTarget(const ActAPI_ModificationType theModType = MT_Touched,
                 const Standard_Boolean doResetValidity = Standard_True,
                 const Standard_Boolean doResetPending = Standard_True);

protected:

  ActData_ReferenceParameter();

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

protected:

  //! Tags for the stored CAF data chunks.
  enum Datum
  {
    DS_Ref = ActData_UserParameter::DS_DatumLast,
    DS_DatumLast = DS_Ref + RESERVED_DATUM_RANGE
  };

};

#endif
