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

#ifndef ActData_UserParameter_HeaderFile
#define ActData_UserParameter_HeaderFile

// Active Data includes
#include <ActData_Common.h>
#include <ActData_ParameterDTO.h>

// Active Data (auxiliary) layer includes
#include <ActAux_TimeStamp.h>

// Active Data (API) includes
#include <ActAPI_IParameter.h>

// OCCT includes
#include <NCollection_Handle.hxx>
#include <NCollection_Sequence.hxx>
#include <TCollection_HAsciiString.hxx>
#include <TDF_Label.hxx>

// Active Data forward declarations
class ActData_BaseNode;

// Enriches Parameter modification routines (normally "Setter" methods)
// with a dedicated stuff for recording modification type in Tree Function
// LogBook. Also populates a Parameter's modification timestamp.
#define SPRING_INTO_FUNCTION(ModType) \
  if ( ModType != MT_Silent ) \
    this->SetModified(); \
  if ( ModType == MT_Touched ) \
    this->SetTouched(); \
  else if ( ModType == MT_Impacted ) \
    this->SetImpacted();

#define RESET_VALIDITY(DoResetValidity) \
  if ( DoResetValidity ) \
    this->SetValidity(Standard_True, MT_Silent);

#define RESET_PENDING(DoResetPending) \
  if ( DoResetPending ) \
    this->SetPending(Standard_False, MT_Silent);

DEFINE_STANDARD_HANDLE(ActData_UserParameter, ActAPI_IUserParameter)

//! \ingroup AD_DF
//!
//! Base class for ACT Nodal Parameters.
//!
//! Parameter objects must be settled down into distinct CAF TDF Labels
//! in order to ensure that their underlying TDF labels never interfere by the
//! numerical tags (IDs). The latter problem can theoretically arise for
//! several Parameter objects referring to a sole TDF Label as Parameter
//! tags are guaranteed to be unique only in scope of a single Parameter
//! object, not in the scope of more common entities like Nodes.
class ActData_UserParameter : public ActAPI_IUserParameter
{
friend class ActData_BaseModel;
friend class ActData_BaseNode;
friend class ActData_MetaParameter;
friend class ActData_DependencyAnalyzer;
friend class ActData_ParameterFactory;
friend class ActData_ReferenceListParameter;
friend class ActData_ReferenceParameter;
friend class ActData_TreeFunctionParameter;
friend class ActData_TreeFunctionDriver;
friend class ActData_Utils;
friend class ActData_CAFDumper;

public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_UserParameter, ActAPI_IUserParameter)

// Transient properties of Data Cursor:
public:

  ActData_EXPORT virtual Standard_Boolean
    IsAttached();

  ActData_EXPORT virtual Standard_Boolean
    IsDetached();

  ActData_EXPORT virtual Standard_Boolean
    IsWellFormed();

  ActData_EXPORT virtual ActAPI_DataObjectId
    GetId() const;

// Manipulation with DTO:
public:

  ActData_EXPORT virtual void
    SetFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
               const ActAPI_ModificationType theModType = MT_Touched,
               const Standard_Boolean doResetValidity = Standard_True,
               const Standard_Boolean doResetPending = Standard_True);

  ActData_EXPORT virtual Handle(ActData_ParameterDTO)
    GetAsDTO();

// Persistent properties:
public:

  ActData_EXPORT virtual Standard_Integer
    GetParamType();

  ActData_EXPORT virtual void
    SetEvalString(const TCollection_AsciiString& theEvalString,
                  const ActAPI_ModificationType theModType = MT_Touched);

  ActData_EXPORT virtual TCollection_AsciiString
    GetEvalString();

  ActData_EXPORT virtual void
    SetName(const TCollection_ExtendedString& theString,
            const ActAPI_ModificationType theModType = MT_Silent);

  ActData_EXPORT virtual TCollection_ExtendedString
    GetName();

  ActData_EXPORT virtual Handle(ActAPI_INode)
    GetNode();

  ActData_EXPORT virtual void
    SetUserFlags(const Standard_Integer theUFlags,
                 const ActAPI_ModificationType theModType = MT_Silent);

  ActData_EXPORT virtual Standard_Boolean
    HasUserFlags(const Standard_Integer theUFlags);

  ActData_EXPORT virtual void
    AddUserFlags(const Standard_Integer theUFlags,
                 const ActAPI_ModificationType theModType = MT_Silent);

  ActData_EXPORT virtual void
    RemoveUserFlags(const Standard_Integer theUFlags,
                    const ActAPI_ModificationType theModType = MT_Silent);

  ActData_EXPORT virtual Standard_Integer
    GetUserFlags();

  ActData_EXPORT virtual void
    SetSemanticId(const TCollection_AsciiString& theId,
                  const ActAPI_ModificationType theModType = MT_Silent);

  ActData_EXPORT virtual TCollection_AsciiString
    GetSemanticId();

  ActData_EXPORT virtual Standard_Boolean
    IsValidData();

  ActData_EXPORT virtual void
    SetValidity(const Standard_Boolean isValid,
                const ActAPI_ModificationType theModType = MT_Silent);

  ActData_EXPORT virtual Standard_Boolean
    IsPendingData();

  ActData_EXPORT virtual void
    SetPending(const Standard_Boolean isPending,
               const ActAPI_ModificationType theModType = MT_Silent);

  ActData_EXPORT virtual void
    SetModified();

  ActData_EXPORT virtual Handle(ActAux_TimeStamp)
    GetMTime();

// Accessors to OCAF internals:
public:

  ActData_EXPORT virtual TDF_Label
    RootLabel() const;

// Modification support:
public:

  ActData_EXPORT void
    SetTouched();

  ActData_EXPORT void
    SetImpacted();

protected:

  ActData_EXPORT
    ActData_UserParameter();

// Data Cursor internals:
protected:

  ActData_EXPORT virtual void attach   (const TDF_Label& theLabel);
  ActData_EXPORT virtual void expandOn (const TDF_Label& theLabel);
  ActData_EXPORT virtual void settleOn (const TDF_Label& theLabel);

protected:

  //! Stores a number of reserved tags for future extensions.
  static const Standard_Integer RESERVED_DATUM_RANGE = 100;

  //! Tags for the underlying data chunks (TDF Labels).
  enum Datum
  {
    DS_ParamType = 1, //!< Parameter type.
    DS_Name,          //!< Unicode name.
    DS_SemanticId,    //!< Semantic ID to extend persistent data by client data.
    DS_EvalString,    //!< Evaluation string.
    DS_MTime,         //!< Modification time.
    DS_IsValid,       //!< Indicates whether the stored value is valid or not.
    DS_UserFlags,     //!< Additional client-specific flags.
    DS_IsPending,     //!< Indicates whether the stored value is out-dated or not.
    DS_DatumLast = DS_ParamType + RESERVED_DATUM_RANGE
  };

  //! Parameter status: ATTACHED or DETACHED.
  enum StorageStatus
  {
    SS_Detached,
    SS_Attached
  };

private:

  //! This validation method should be implemented by the derived classes
  //! in order to provide consistency check for the underlying CAF structures
  //! representing client-specific data chunks.
  //! \return true is the underlying CAF structure is consistent,
  //!         false -- otherwise.
  virtual Standard_Boolean isWellFormed() const = 0;

  //! Returns type ID for the actual implementation of Parameter.
  //! \return Parameter type.
  virtual Standard_Integer parameterType() const = 0;

  //! Method to create and populate DTO instance.
  //! \param theGID [in] GID prepared by base class.
  //! \return DTO instance.
  virtual Handle(ActData_ParameterDTO) createDTO(const ActAPI_ParameterGID& theGID) = 0;

  //! Initializes Parameter with the passed DTO.
  //! \param theDTO [in] data for initialization.
  //! \param theModType [in] modification type.
  //! \param doResetValidity [in] flag to reset validity state.
  //! \param doResetPending [in] flag to reset pending state.
  virtual void setFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
                          const ActAPI_ModificationType theModType = MT_Touched,
                          const Standard_Boolean doResetValidity = Standard_True,
                          const Standard_Boolean doResetPending = Standard_True) = 0;

protected:

  //! Root TDF Label for the Parameter.
  TDF_Label m_label;

  //! Current settling status (ATTACHED or DETACHED).
  StorageStatus m_status;

};

#endif
