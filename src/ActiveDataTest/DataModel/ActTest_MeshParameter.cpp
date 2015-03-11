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

// Own include
#include <ActTest_MeshParameter.h>

// Mesh includes
#include <Mesh_Node.h>

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

  Handle(TDocStd_Document) doc = initCAFDocument();

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

  Handle(Mesh_Node) aNode1 = aMeshFrom->FindNode(1);
  Handle(Mesh_Node) aNode2 = aMeshFrom->FindNode(2);
  Handle(Mesh_Node) aNode3 = aMeshFrom->FindNode(3);

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
