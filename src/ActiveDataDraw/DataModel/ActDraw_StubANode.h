//-----------------------------------------------------------------------------
// Created on: March 2015
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

#ifndef ActDraw_StubANode_HeaderFile
#define ActDraw_StubANode_HeaderFile

// Active Data Draw includes
#include <ActDraw.h>

// Active Data includes
#include <ActData_BaseNode.h>

DEFINE_STANDARD_HANDLE(ActDraw_StubANode, ActData_BaseNode)

//! \ingroup AD_DRAW
//!
//! Implementation of Data Node for Draw commands.
class ActDraw_StubANode : public ActData_BaseNode
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActDraw_StubANode, ActData_BaseNode)

  // Automatic registration of Node instance in the Nodal Factory.
  DEFINE_NODE_FACTORY(ActDraw_StubANode, Instance)

public:

  //! IDs of the underlying Parameters.
  enum ParamId
  {
    PID_Name = ActData_BaseNode::UserParam_Last,
    PID_Real //!< Some dummy real value...
  };

public:

  ActDraw_EXPORT static Handle(ActAPI_INode) Instance();

// Generic accessors:
public:

  ActDraw_EXPORT virtual TCollection_ExtendedString
    GetName();

  ActDraw_EXPORT virtual void
    SetName(const TCollection_ExtendedString& theName);

// Initialization and accessors:
public:

  ActDraw_EXPORT void
    Init(const Standard_Real theVal);

  ActDraw_EXPORT Standard_Real
    GetValue() const;

protected:

  //! Allocation is allowed only via Instance method.
  ActDraw_StubANode();

};

#endif
