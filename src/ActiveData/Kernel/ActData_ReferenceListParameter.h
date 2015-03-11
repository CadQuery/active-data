//-----------------------------------------------------------------------------
// Created on: April 2012
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

#ifndef ActData_ReferenceListParameter_HeaderFile
#define ActData_ReferenceListParameter_HeaderFile

// Active Data includes
#include <ActData_UserParameter.h>
#include <ActData_Common.h>
#include <ActData_ParameterDTO.h>

// OCCT includes
#include <TDataStd_ReferenceList.hxx>
#include <TDF_LabelList.hxx>

//-----------------------------------------------------------------------------
// Parameter DTO
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_ReferenceListDTO, ActData_ParameterDTO)

//! \ingroup AD_DF
//!
//! Data Transfer Object (DTO) corresponding to data wrapped with
//! Reference List Parameter without any OCAF connectivity.
class ActData_ReferenceListDTO : public ActData_ParameterDTO
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_ReferenceListDTO, ActData_ParameterDTO)

public:

  //! Constructor accepting GID.
  //! \param theGID [in] GID.
  ActData_ReferenceListDTO(const ActAPI_ParameterGID& theGID)
  : ActData_ParameterDTO( theGID, Parameter_ReferenceList )
  {}

public:

  Handle(ActAPI_HDataCursorList) Targets; //!< Reference targets.

};

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_ReferenceListParameter, ActData_UserParameter)

//! \ingroup AD_DF
//!
//! Parameter representing a list of references onto CAF TDF Labels
//! corresponding to the roots of Parameter entities.
//! NOTICE: NULL references are not supported.
//! \todo it is necessary to introduce NULL references. This could not be
//!       just TDF_Label() as it will be lost after persistence routines
//!       perform.
//! \todo take care of issue #23465 is OCCT (about standard lists).
class ActData_ReferenceListParameter : public ActData_UserParameter
{
friend class ActData_BaseNode;
friend class ActData_BaseModel;
friend class ActData_CAFConversionCtx;
friend class ActData_CopyPasteEngine;

public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_ReferenceListParameter, ActData_UserParameter)

public:

  ActData_EXPORT static Handle(ActData_ReferenceListParameter) Instance();

public:

  ActData_EXPORT void
    AddTarget(const Handle(ActAPI_IDataCursor)& theTarget,
              const ActAPI_ModificationType     theModType      = MT_Touched,
              const Standard_Boolean            doResetValidity = Standard_True,
              const Standard_Boolean            doResetPending  = Standard_True);

  ActData_EXPORT void
    AddTarget(const TDF_Label&              theTargetLab,
              const ActAPI_ModificationType theModType      = MT_Touched,
              const Standard_Boolean        doResetValidity = Standard_True,
              const Standard_Boolean        doResetPending  = Standard_True);

  ActData_EXPORT void
    PrependTarget(const Handle(ActAPI_IDataCursor)& theTarget,
                  const ActAPI_ModificationType     theModType      = MT_Touched,
                  const Standard_Boolean            doResetValidity = Standard_True,
                  const Standard_Boolean            doResetPending  = Standard_True);

  ActData_EXPORT void
    PrependTarget(const TDF_Label&              theTargetLab,
                  const ActAPI_ModificationType theModType      = MT_Touched,
                  const Standard_Boolean        doResetValidity = Standard_True,
                  const Standard_Boolean        doResetPending  = Standard_True);

  ActData_EXPORT void
    InsertTargetAfter(const Standard_Integer            theIndex,
                      const Handle(ActAPI_IDataCursor)& theTarget,
                      const ActAPI_ModificationType     theModType      = MT_Touched,
                      const Standard_Boolean            doResetValidity = Standard_True,
                      const Standard_Boolean            doResetPending  = Standard_True);

  ActData_EXPORT void
    InsertTargetAfter(const Standard_Integer        theIndex,
                      const TDF_Label&              theTargetLab,
                      const ActAPI_ModificationType theModType      = MT_Touched,
                      const Standard_Boolean        doResetValidity = Standard_True,
                      const Standard_Boolean        doResetPending  = Standard_True);

  ActData_EXPORT Standard_Integer
    HasTarget(const Handle(ActAPI_IDataCursor)& theTarget);

  ActData_EXPORT Standard_Integer
    HasTarget(const TDF_Label& theTargetLab);

  ActData_EXPORT Standard_Boolean
    RemoveTargetOccurrences(const Handle(ActAPI_IDataCursor)& theTarget,
                            const ActAPI_ModificationType     theModType      = MT_Touched,
                            const Standard_Boolean            doResetValidity = Standard_True,
                            const Standard_Boolean            doResetPending  = Standard_True);

  ActData_EXPORT Standard_Boolean
    RemoveTarget(const Handle(ActAPI_IDataCursor)& theTarget,
                 const ActAPI_ModificationType     theModType      = MT_Touched,
                 const Standard_Boolean            doResetValidity = Standard_True,
                 const Standard_Boolean            doResetPending  = Standard_True);

  ActData_EXPORT Standard_Boolean
    RemoveTarget(const Standard_Integer        theTargetIndex,
                 const ActAPI_ModificationType theModType      = MT_Touched,
                 const Standard_Boolean        doResetValidity = Standard_True,
                 const Standard_Boolean        doResetPending  = Standard_True);

  ActData_EXPORT Standard_Boolean
    RemoveTargets(const ActAPI_ModificationType theModType      = MT_Touched,
                  const Standard_Boolean        doResetValidity = Standard_True,
                  const Standard_Boolean        doResetPending  = Standard_True);

  ActData_EXPORT Handle(ActAPI_IDataCursor)
    GetTarget(const Standard_Integer theIndex) const;

  ActData_EXPORT TDF_Label
    GetTargetLabel(const Standard_Integer theIndex) const;

  ActData_EXPORT Handle(ActAPI_HDataCursorList)
    GetTargets() const;

  ActData_EXPORT void
    SetTargets(const Handle(ActAPI_HDataCursorList)& theTargets,
               const ActAPI_ModificationType         theModType      = MT_Touched,
               const Standard_Boolean                doResetValidity = Standard_True,
               const Standard_Boolean                doResetPending  = Standard_True);

  ActData_EXPORT Standard_Boolean
    ExchangeTarget(const TDF_Label&              theTargetOldLab,
                   const TDF_Label&              theTargetNewLab,
                   const ActAPI_ModificationType theModType      = MT_Touched,
                   const Standard_Boolean        doResetValidity = Standard_True,
                   const Standard_Boolean        doResetPending  = Standard_True);

  ActData_EXPORT Standard_Boolean
    ExchangeTarget(const Handle(ActAPI_IDataCursor)& theTargetOld,
                   const Handle(ActAPI_IDataCursor)& theTargetNew,
                   const ActAPI_ModificationType     theModType      = MT_Touched,
                   const Standard_Boolean            doResetValidity = Standard_True,
                   const Standard_Boolean            doResetPending  = Standard_True);

  ActData_EXPORT Standard_Boolean
    SwapTargets(const Standard_Integer        theFirstIndex,
                const Standard_Integer        theSecondIndex,
                const ActAPI_ModificationType theModType      = MT_Touched,
                const Standard_Boolean        doResetValidity = Standard_True,
                const Standard_Boolean        doResetPending  = Standard_True);

  ActData_EXPORT Standard_Integer
    NbTargets();

  ActData_EXPORT Handle(TDataStd_ReferenceList)
    AccessReferenceList() const;

protected:

  ActData_ReferenceListParameter();

private:

  void getTargets(TDF_LabelList& theLabelList) const;

  Standard_Boolean removeTarget(const TDF_Label& theTargetLab);

private:

  virtual Standard_Boolean isWellFormed() const;
  virtual Standard_Integer parameterType() const;

private:

  virtual void
    setFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
               const ActAPI_ModificationType       theModType      = MT_Touched,
               const Standard_Boolean              doResetValidity = Standard_True,
               const Standard_Boolean              doResetPending  = Standard_True);

  virtual Handle(ActData_ParameterDTO)
    createDTO(const ActAPI_ParameterGID& theGID);

protected:

  //! Tags for the underlying sub-Labels.
  enum Datum
  {
    DS_Targets = ActData_UserParameter::DS_DatumLast,
    //
    DS_DatumLast = ActData_UserParameter::DS_DatumLast + RESERVED_DATUM_RANGE
  };

};

#endif
