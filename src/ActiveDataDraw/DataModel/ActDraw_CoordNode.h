//-----------------------------------------------------------------------------
// Created on: January 2016
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

#ifndef ActDraw_CoordNode_HeaderFile
#define ActDraw_CoordNode_HeaderFile

// Active Data Draw includes
#include <ActDraw.h>

// Active Data includes
#include <ActData_BaseNode.h>

DEFINE_STANDARD_HANDLE(ActDraw_CoordNode, ActData_BaseNode)

//! \ingroup AD_DRAW
//!
//! Sample Node representing Cartesian triple in three-dimensional space.
class ActDraw_CoordNode : public ActData_BaseNode
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActDraw_CoordNode, ActData_BaseNode)

  // Automatic registration of Node instance in the Nodal Factory.
  DEFINE_NODE_FACTORY(ActDraw_CoordNode, Instance)

public:

  //! IDs of the underlying Parameters.
  enum ParamId
  {
    PID_Name = ActData_BaseNode::UserParam_Last,
    PID_X, //!< X.
    PID_Y, //!< Y.
    PID_Z  //!< Z.
  };

public:

  ActDraw_EXPORT static Handle(ActAPI_INode) Instance();

// Generic accessors:
public:

  ActDraw_EXPORT virtual TCollection_ExtendedString
    GetName();

  ActDraw_EXPORT virtual void
    SetName(const TCollection_ExtendedString& name);

// Initialization and accessors:
public:

  ActDraw_EXPORT void
    Init(const Standard_Real x,
         const Standard_Real y,
         const Standard_Real z);

protected:

  //! Allocation is allowed only via Instance method.
  ActDraw_CoordNode();

};

#endif
