//-----------------------------------------------------------------------------
// Created on: July 2017
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
#include <ActTest_TriangulationParameter.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing value of TriangulationParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_TriangulationParameter::accessValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new TRIANGULATION Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_TriangulationParameter)
    param = ActParamTool::AsTriangulation( createParameter(doc, Parameter_Triangulation) );
  doc->CommitCommand();

  ACT_VERIFY( !param->IsWellFormed() ) // As not yet initialized

  /* ===========================
   *  Initialize Mesh Parameter
   * =========================== */

  static Handle(Poly_Triangulation) TRIS = new Poly_Triangulation(3, 1, 0);
  TRIS->ChangeNode(1) = gp_Pnt(0.0, 0.0, 0.0);
  TRIS->ChangeNode(2) = gp_Pnt(1.0, 0.0, 0.0);
  TRIS->ChangeNode(3) = gp_Pnt(1.0, 1.0, 0.0);
  //
  TRIS->ChangeTriangle(1) = Poly_Triangle(1, 2, 3);

  doc->OpenCommand();
  param->SetTriangulation(TRIS);
  doc->CommitCommand();

  ACT_VERIFY( param->IsWellFormed() )

  /* ==============================================
   *  Verify Mesh DS retrieved from Mesh Parameter
   * ============================================== */

  Handle(Poly_Triangulation) aMeshFrom = param->GetTriangulation();

  ACT_VERIFY( !aMeshFrom.IsNull() )
  ACT_VERIFY( aMeshFrom->NbTriangles() == 1 )
  ACT_VERIFY( aMeshFrom->NbNodes() == 3 )

  const gp_Pnt& aNode1 = aMeshFrom->Node(1);
  const gp_Pnt& aNode2 = aMeshFrom->Node(2);
  const gp_Pnt& aNode3 = aMeshFrom->Node(3);

  ACT_VERIFY(aNode1.X() == 0.0)
  ACT_VERIFY(aNode1.Y() == 0.0)
  ACT_VERIFY(aNode1.Z() == 0.0)
  //
  ACT_VERIFY(aNode2.X() == 1.0)
  ACT_VERIFY(aNode2.Y() == 0.0)
  ACT_VERIFY(aNode2.Z() == 0.0)
  //
  ACT_VERIFY(aNode3.X() == 1.0)
  ACT_VERIFY(aNode3.Y() == 1.0)
  ACT_VERIFY(aNode3.Z() == 0.0)

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
