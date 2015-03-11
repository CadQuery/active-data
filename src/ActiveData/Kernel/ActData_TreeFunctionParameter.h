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

#ifndef ActData_TreeFunctionParameter_HeaderFile
#define ActData_TreeFunctionParameter_HeaderFile

// Active Data includes
#include <ActData_UserParameter.h>
#include <ActData_Common.h>

// Active Data (API) includes
#include <ActAPI_ITreeFunction.h>

// OCCT includes
#include <TDataStd_ReferenceList.hxx>
#include <TDF_LabelList.hxx>

//-----------------------------------------------------------------------------
// Parameter DTO
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_TreeFunctionDTO, ActData_ParameterDTO)

//! \ingroup AD_DF
//!
//! Data Transfer Object (DTO) corresponding to data wrapped with
//! Tree Function Parameter without any OCAF connectivity.
class ActData_TreeFunctionDTO : public ActData_ParameterDTO
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_TreeFunctionDTO, ActData_ParameterDTO)

public:

  //! Constructor accepting GID.
  //! \param theGID [in] GID.
  ActData_TreeFunctionDTO(const ActAPI_ParameterGID& theGID)
  : ActData_ParameterDTO( theGID, Parameter_TreeFunction )
  {}

public:

  Standard_GUID                DriverGUID; //!< Tree Function GUID.
  Handle(ActAPI_HParameterList) Arguments;  //!< Tree Function arguments.
  Handle(ActAPI_HParameterList) Results;    //!< Tree Function results.

};

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_TreeFunctionParameter, ActData_UserParameter)

//! \ingroup AD_DF
//!
//! \todo provide comment here
class ActData_TreeFunctionParameter : public ActData_UserParameter
{
friend class ActData_BaseNode;
friend class ActData_BaseModel;
friend class ActData_CopyPasteEngine;
friend class ActData_TreeFunctionDriver;
friend class ActData_CAFConversionCtx;

public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_TreeFunctionParameter, ActData_UserParameter)

public:

  ActData_EXPORT static Handle(ActData_TreeFunctionParameter)
    Instance();

  ActData_EXPORT void
    SetDriverGUID(const Standard_GUID& theGUID);

  ActData_EXPORT Standard_Boolean
    GetDriverGUID(Standard_GUID& theGUID) const;

  ActData_EXPORT void
    AddArgument(const Handle(ActAPI_IUserParameter)& theParam);

  ActData_EXPORT Standard_Boolean
    HasArgument(const TDF_Label& theParamLab) const;

  ActData_EXPORT Standard_Boolean
    HasArgument(const Handle(ActAPI_IUserParameter)& theParam) const;

  ActData_EXPORT void
    AddResult(const Handle(ActAPI_IUserParameter)& theParam);

  ActData_EXPORT Standard_Boolean
    HasResult(const TDF_Label& theParamLab) const;

  ActData_EXPORT Standard_Boolean
    HasResult(const Handle(ActAPI_IUserParameter)& theParam) const;

  ActData_EXPORT void
    Disconnect(const Standard_Boolean toKillCompletely = Standard_True);

  ActData_EXPORT void
    DisconnectSoft();

  ActData_EXPORT Standard_Boolean
    IsConnected() const;

  ActData_EXPORT Handle(ActAPI_HParameterList)
    Arguments() const;

  ActData_EXPORT Handle(ActAPI_HParameterList)
    Results() const;

  ActData_EXPORT Standard_Boolean
    IsHeavyFunction() const;

  ActData_EXPORT Standard_Boolean
    HasPendingArguments() const;

  ActData_EXPORT Standard_Boolean
    HasPendingResults() const;

protected:

  ActData_TreeFunctionParameter();

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

  Handle(TDataStd_ReferenceList)
    getArgumentsAttr() const;

  Handle(TDataStd_ReferenceList)
    getResultsAttr() const;

  TDF_Label
    getArgumentsLabel() const;

  TDF_Label
    getResultsLabel() const;

  void
    getArguments(TDF_LabelList& theLabelList) const;

  void
    getResults(TDF_LabelList& theLabelList) const;

  Standard_Boolean
    hasPending(const Handle(ActAPI_HParameterList)& theParams) const;

protected:

  //! Tags for the underlying CAF Labels.
  enum Datum
  {
    DS_Arguments = ActData_UserParameter::DS_DatumLast,
    DS_Results,
    DS_DatumLast = DS_Arguments + RESERVED_DATUM_RANGE
  };

};

#endif
