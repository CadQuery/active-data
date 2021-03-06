//-----------------------------------------------------------------------------
// Created on: March 2013
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//    * Neither the name of OPEN CASCADE SAS nor the
//      names of all contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Web: http://dev.opencascade.org
//-----------------------------------------------------------------------------

#ifndef ActTest_StubCNode_HeaderFile
#define ActTest_StubCNode_HeaderFile

// Active Data unit tests
#include <ActTest.h>

// Active Data includes
#include <ActData_BaseNode.h>

DEFINE_STANDARD_HANDLE(ActTest_StubCNode, ActData_BaseNode)

//! \ingroup AD_TEST
//!
//! Implementation of Data Node for unit tests.
class ActTest_StubCNode : public ActData_BaseNode
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActTest_StubCNode, ActData_BaseNode)

  // Automatic registration of Node instance in the Nodal Factory.
  DEFINE_NODE_FACTORY(ActTest_StubCNode, Instance)

public:

  //! IDs of the underlying Parameters.
  enum ParamId
  {
    /* Int            */ PID_Int = 100,
    /* Real           */ PID_Real,
    /* Boolean        */ PID_Bool,
    /* Shape          */ PID_Shape,
    /* Real Array     */ PID_RealArray,
    /* Tree Function  */ PID_TFunc,
    /* ASCII String   */ PID_AStr,
    /* UNICODE String */ PID_UStr,
    /* Boolean Array  */ PID_BoolArray,
    /* String Array   */ PID_StrArray,
    /* Complex Array  */ PID_ComplexArray,
    /* Int Array      */ PID_IntArray,
    /* Reference List */ PID_RefList,
    /* Group          */ PID_Group,
    /* Mesh           */ PID_Mesh,
    /* Reference      */ PID_Ref,
    /* Selection      */ PID_Selection,
    /* Timestamp      */ PID_TimeStamp
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
  ActTest_StubCNode();

};

#endif
