//-----------------------------------------------------------------------------
// Created on: May 2012
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

// Own include
#include <ActTest_MeshParameter.h>

// Mesh includes
#include <ActData_Mesh_Node.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing value of MeshParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_MeshParameter::accessValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new MESH Parameter");

  ActTest_DocAlloc docAlloc;
  Handle(TDocStd_Document) doc = docAlloc.Doc;

  doc->NewCommand();
  Handle(ActData_MeshParameter)
    param = ActParamTool::AsMesh( createParameter(doc, Parameter_Mesh) );
  doc->CommitCommand();

  ACT_VERIFY( !param->IsWellFormed() ) // As not yet initialized

  /* ===========================
   *  Initialize Mesh Parameter
   * =========================== */

  static Handle(ActData_Mesh) MESH = new ActData_Mesh();
  MESH->AddNode(0.0, 0.0, 0.0);
  MESH->AddNode(0.0, 0.0, 1.0);
  MESH->AddNode(0.0, 0.0, 2.0);

  doc->OpenCommand();
  param->SetMesh(MESH);
  doc->CommitCommand();

  ACT_VERIFY( param->IsWellFormed() )

  /* ==============================================
   *  Verify Mesh DS retrieved from Mesh Parameter
   * ============================================== */

  Handle(ActData_Mesh) aMeshFrom = param->GetMesh();

  ACT_VERIFY( !aMeshFrom.IsNull() )
  ACT_VERIFY( aMeshFrom->NbFaces() == 0 )
  ACT_VERIFY( aMeshFrom->NbNodes() == 3 )

  Handle(ActData_Mesh_Node) aNode1 = aMeshFrom->FindNode(1);
  Handle(ActData_Mesh_Node) aNode2 = aMeshFrom->FindNode(2);
  Handle(ActData_Mesh_Node) aNode3 = aMeshFrom->FindNode(3);

  ACT_VERIFY( !aNode1.IsNull() )
  ACT_VERIFY( !aNode2.IsNull() )
  ACT_VERIFY( !aNode3.IsNull() )

  ACT_VERIFY(aNode1->Pnt().X() == 0.0)
  ACT_VERIFY(aNode2->Pnt().X() == 0.0)
  ACT_VERIFY(aNode3->Pnt().X() == 0.0)
  ACT_VERIFY(aNode1->Pnt().Y() == 0.0)
  ACT_VERIFY(aNode2->Pnt().Y() == 0.0)
  ACT_VERIFY(aNode3->Pnt().Y() == 0.0)
  ACT_VERIFY(aNode1->Pnt().Z() == 0.0)
  ACT_VERIFY(aNode2->Pnt().Z() == 1.0)
  ACT_VERIFY(aNode3->Pnt().Z() == 2.0)

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
