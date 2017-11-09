//-----------------------------------------------------------------------------
// Created on: June 2012
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the OPEN CASCADE SAS.
// 4. Neither the name of the OPEN CASCADE SAS nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY OPEN CASCADE SAS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL OPEN CASCADE SAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Web: http://dev.opencascade.org
//-----------------------------------------------------------------------------

#ifndef ActTest_StubMeshNode_HeaderFile
#define ActTest_StubMeshNode_HeaderFile

// Active Data unit tests
#include <ActTest.h>

// Active Data includes
#include <ActData_BaseNode.h>

// Mesh includes
#include <Mesh.h>

DEFINE_STANDARD_HANDLE(ActTest_StubMeshNode, ActData_BaseNode)

//! \ingroup AD_TEST
//!
//! Implementation of Data Node for unit tests.
class ActTest_StubMeshNode : public ActData_BaseNode
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActTest_StubMeshNode, ActData_BaseNode)

  // Automatic registration of Node instance in the Nodal Factory.
  DEFINE_NODE_FACTORY(ActTest_StubMeshNode, Instance)

public:

  //! IDs of the underlying Parameters.
  enum ParamId
  {
    Param_Name = ActData_BaseNode::UserParam_Last,
    Param_Mesh //!< Test mesh.
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

  void
    Init(const Handle(ActData_Mesh)& theMesh);

  Handle(ActData_Mesh)
    GetMesh() const;

protected:

  //! Allocation is allowed only via Instance method.
  ActTest_StubMeshNode();

};

#endif
