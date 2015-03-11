//-----------------------------------------------------------------------------
// Created on: June 2012
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


#ifndef ActTest_StubANode_HeaderFile
#define ActTest_StubANode_HeaderFile

// ACT Unit Test Suite includes
#include <ActTest.h>

// Active Data includes
#include <ActData_BaseNode.h>

DEFINE_STANDARD_HANDLE(ActTest_StubANode, ActData_BaseNode)

//! \ingroup AD_TEST
//!
//! Implementation of Data Node for unit tests.
class ActTest_StubANode : public ActData_BaseNode
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActTest_StubANode, ActData_BaseNode)

  // Automatic registration of Node instance in the Nodal Factory.
  DEFINE_NODE_FACTORY(ActTest_StubANode, Instance)

public:

  //! IDs of the underlying Parameters.
  enum ParamId
  {
    PID_Name = ActData_BaseNode::UserParam_Last,
    PID_DummyShapeA, //!< Let it be some topological shape here...
    PID_DummyShapeB, //!< Let's have another shape...
    PID_Real,        //!< And some dummy real value...
    PID_TFunc,       //!< Plus sole Tree Function to test alternative dependencies...
    PID_Ref          //!< Plus plain reference to other Parameters...
  };

public:

  ActTest_EXPORT static Handle(ActAPI_INode) Instance();

// Generic accessors:
public:

  ActTest_EXPORT virtual TCollection_ExtendedString
    GetName();

  ActTest_EXPORT virtual void
    SetName(const TCollection_ExtendedString& theName);

// Initialization and accessors:
public:

  ActTest_EXPORT void
    Init(const TopoDS_Shape& theShapeA,
         const TopoDS_Shape& theShapeB,
         const Standard_Real theVal);

  ActTest_EXPORT TopoDS_Shape
    GetShapeA() const;

  ActTest_EXPORT TopoDS_Shape
    GetShapeB() const;

  ActTest_EXPORT Standard_Real
    GetValue() const;

  ActTest_EXPORT Standard_Boolean
    HasConnectedFunction() const;

protected:

  //! Allocation is allowed only via Instance method.
  ActTest_StubANode();

};

#endif
