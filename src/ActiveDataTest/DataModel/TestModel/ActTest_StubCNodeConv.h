//-----------------------------------------------------------------------------
// Created on: March 2013
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

#ifndef ActTest_StubCNodeConv_HeaderFile
#define ActTest_StubCNodeConv_HeaderFile

// ACT Unit Test Suite includes
#include <ActTest.h>

// Active Data includes
#include <ActData_BaseNode.h>

DEFINE_STANDARD_HANDLE(ActTest_StubCNodeConv, ActData_BaseNode)

//! \ingroup AD_TEST
//!
//! C test Node representing expected data format after conversion.
class ActTest_StubCNodeConv : public ActData_BaseNode
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActTest_StubCNodeConv, ActData_BaseNode)

  // Automatic registration of Node instance in the Nodal Factory.
  DEFINE_NODE_FACTORY(ActTest_StubCNodeConv, Instance)

public:

  //! IDs of the underlying Parameters.
  enum ParamId
  {
    /* Int            */ PID_Int = 100,
    /* Bool           */ PID_Bool,
    /* Int            */ PID_NEWInt1,
    /* Shape          */ PID_Shape,
    /* Real Array     */ PID_RealArray,
    /* Tree Function  */ PID_TFunc,
    /* ASCII String   */ PID_AStr,
    /* Bool Array     */ PID_BoolArray,
    /* String Array   */ PID_StrArray,
    /* Complex Array  */ PID_ComplexArray,
    /* Int Array      */ PID_IntArray,
    /* Int            */ PID_NEWInt2,
    /* Reference List */ PID_RefList,
    /* Group          */ PID_Group,
    /* Mesh           */ PID_Mesh,
    /* Int            */ PID_NEWInt3,
    /* Reference      */ PID_Ref,
    /* Selection      */ PID_Selection,
    /* Timestamp      */ PID_TimeStamp,
    /* Int            */ PID_NEWInt4
  };

public:

  static Handle(ActAPI_INode) Instance();

// Generic accessors:
public:

  virtual TCollection_ExtendedString
    GetName();
  
  virtual void
    SetName(const TCollection_ExtendedString& theName);

// Initialization and accessors:
public:

  void Init();

protected:

  //! Allocation is allowed only via Instance method.
  ActTest_StubCNodeConv();

};

#endif
