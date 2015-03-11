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

#ifndef ActData_StringArrayParameter_HeaderFile
#define ActData_StringArrayParameter_HeaderFile

// Active Data includes
#include <ActData_UserParameter.h>
#include <ActData_Common.h>
#include <ActData_ParameterDTO.h>

// OCCT includes
#include <TCollection_ExtendedString.hxx>

//-----------------------------------------------------------------------------
// Parameter DTO
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_StringArrayDTO, ActData_ParameterDTO)

//! \ingroup AD_DF
//!
//! Data Transfer Object (DTO) corresponding to data wrapped with
//! String Array without any OCAF connectivity.
class ActData_StringArrayDTO : public ActData_ParameterDTO
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_StringArrayDTO, ActData_ParameterDTO)

public:

  //! Constructor accepting GID.
  //! \param theGID [in] GID.
  ActData_StringArrayDTO(const ActAPI_ParameterGID& theGID) : ActData_ParameterDTO( theGID, Parameter_StringArray ) {}

public:

  Handle(HStringArray) Array; //!< Actual array.

};

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_StringArrayParameter, ActData_UserParameter)

//! \ingroup AD_DF
//!
//! Node Parameter representing an array of string values.
class ActData_StringArrayParameter : public ActData_UserParameter
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_StringArrayParameter, ActData_UserParameter)

public:

  ActData_EXPORT static Handle(ActData_StringArrayParameter) Instance();

public:

  ActData_EXPORT void
    InitEmpty();

  ActData_EXPORT void
    BackupArray();

  ActData_EXPORT void
    SetElement(const Standard_Integer theIndex,
               const TCollection_ExtendedString& theValue,
               const ActAPI_ModificationType theModType = MT_Silent,
               const Standard_Boolean doResetValidity = Standard_False,
               const Standard_Boolean doResetPending = Standard_False);

  ActData_EXPORT TCollection_ExtendedString
    GetElement(const Standard_Integer theIndex);

  ActData_EXPORT void
    SetArray(const Handle(HStringArray)& theArray,
             const ActAPI_ModificationType theModType = MT_Touched,
             const Standard_Boolean doResetValidity = Standard_True,
             const Standard_Boolean doResetPending = Standard_True);

  ActData_EXPORT Handle(HStringArray)
    GetArray();

  ActData_EXPORT Standard_Integer
    NbElements();

protected:

  ActData_StringArrayParameter();

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

  //! Tags for the underlying CAF Labels.
  enum Datum
  {
    DS_Array = ActData_UserParameter::DS_DatumLast,
    DS_ElemNum,
    DS_DatumLast = DS_Array + RESERVED_DATUM_RANGE
  };

};

#endif
