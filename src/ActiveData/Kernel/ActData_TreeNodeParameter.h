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

#ifndef ActData_TreeNodeParameter_HeaderFile
#define ActData_TreeNodeParameter_HeaderFile

// Active Data includes
#include <ActData_UserParameter.h>
#include <ActData_Common.h>

// OCCT includes
#include <TDataStd_TreeNode.hxx>

//-----------------------------------------------------------------------------
// Parameter DTO
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_TreeNodeDTO, ActData_ParameterDTO)

//! \ingroup AD_DF
//!
//! Data Transfer Object (DTO) corresponding to data wrapped with
//! Tree Node Parameter without any OCAF connectivity.
class ActData_TreeNodeDTO : public ActData_ParameterDTO
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_TreeNodeDTO, ActData_ParameterDTO)

public:

  //! Constructor accepting GID.
  //! \param theGID [in] GID.
  ActData_TreeNodeDTO(const ActAPI_ParameterGID& theGID)
  : ActData_ParameterDTO ( theGID, Parameter_TreeNode ),
    ParentId             ( ActAPI_DataObjectId() ),
    PID                  ( -1 )
  {}

public:

  ActAPI_DataObjectId ParentId; //!< ID of the parent object.
  int                 PID;      //!< PID of the parent Parameter.

};

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_TreeNodeParameter, ActData_UserParameter)

//! \ingroup AD_DF
//!
//! Using this type of Parameter you are free to create your own tree of
//! Nodes which is non-standard. Be aware that Tree Node functionality is
//! already implemented in META header of each Node. So this Parameter is
//! kept only for very specific and not very common use cases.
class ActData_TreeNodeParameter : public ActData_UserParameter
{
friend class ActData_BaseNode;
friend class ActData_BaseChildIterator;

public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_TreeNodeParameter, ActData_UserParameter)

public:

  ActData_EXPORT static Handle(ActData_TreeNodeParameter)
    Instance();

  ActData_EXPORT void
    AppendChild(const Handle(ActData_TreeNodeParameter)& theTreeNode);

  ActData_EXPORT Standard_Boolean
    RemoveChild(const Handle(ActData_TreeNodeParameter)& theTreeNode);

public:

  ActData_EXPORT Handle(TDataStd_TreeNode)
    GetCAFTreeNode();

protected:

  Handle(TDataStd_TreeNode)
    accessInternalNode(const TDF_Label&       theLab,
                       const Standard_Boolean toCreate = Standard_True);

private:

  ActData_TreeNodeParameter();

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

  //! Tags for the underlying CAF Labels.
  enum Datum
  {
    DS_TreeNode = ActData_UserParameter::DS_DatumLast,
    DS_DatumLast = DS_TreeNode + RESERVED_DATUM_RANGE
  };

};

#endif
