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

#ifndef ActData_BaseVarNode_HeaderFile
#define ActData_BaseVarNode_HeaderFile

// Active Data includes
#include <ActData_BaseNode.h>
#include <ActData_Common.h>
#include <ActData_Utils.h>

DEFINE_STANDARD_HANDLE(ActData_BaseVarNode, ActData_BaseNode)

//! \ingroup AD_DF
//!
//! Base class for Data Nodes playing as Variables in embedded ACT Data
//! Framework evaluation mechanism.
class ActData_BaseVarNode : public ActData_BaseNode
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_BaseVarNode, ActData_BaseNode)

public:

  //! Contained Parameters.
  enum ParamId
  {
    Param_Name = ActData_BaseNode::UserParam_Last, //!< Name of the Node, not variable (!)
    Param_Value, //!< Variable's value.
    Param_Last = Param_Name + ActData_BaseNode::RESERVED_PARAM_RANGE
  };

// Generic naming support:
public:

  ActData_EXPORT virtual TCollection_ExtendedString
    GetName();

  ActData_EXPORT virtual void
    SetName(const TCollection_ExtendedString& theName);

// Setters & Getters:
public:

  ActData_EXPORT void
    SetVariableName(const TCollection_AsciiString& Name);

  ActData_EXPORT TCollection_AsciiString
    GetVariableName() const;

// Service methods:
public:

  ActData_EXPORT virtual void
    RenameConnected(const TCollection_AsciiString& NewName);

protected:

  //! Allocation of base class prohibited.
  ActData_EXPORT ActData_BaseVarNode();

protected:

  ActData_EXPORT virtual void
    beforeRemove();

private:

  void replaceInEvalStrings(const TCollection_AsciiString& What,
                            const TCollection_AsciiString& With = TCollection_AsciiString(),
                            const Standard_Boolean isCompleteErase = Standard_False);

  void replaceRecursive(TCollection_AsciiString& Source,
                        const TCollection_AsciiString& What,
                        const TCollection_AsciiString& With);

};

#endif
