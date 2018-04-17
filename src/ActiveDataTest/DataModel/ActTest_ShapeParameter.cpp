//-----------------------------------------------------------------------------
// Created on: April 2012
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
#include <ActTest_ShapeParameter.h>

// OCCT includes
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <gp_Pln.hxx>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing value of ShapeParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_ShapeParameter::accessValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new SHAPE Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_ShapeParameter)
    param = ActParamTool::AsShape( createParameter(doc, Parameter_Shape) );
  doc->CommitCommand();

  TopoDS_Shape VALUE = BRepPrimAPI_MakeBox(10, 20, 30).Shape();

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =====================
   *  Set Parameter value
   * ===================== */

  TCollection_AsciiString
    aMsg = TCollection_AsciiString("Setting a test value: ")
                              .Cat( VALUE.TShape()->DynamicType()->Name() );

  doc->NewCommand();
  TEST_PRINT_DECOR_L( aMsg.ToCString() );
  param->SetShape(VALUE);
  doc->CommitCommand();

  // Now we expect the Parameter to become well-formed
  ACT_VERIFY( param->IsWellFormed() )

  /* ==========================
   *  Validate Parameter value
   * ========================== */

  // Validate
  ACT_VERIFY(param->GetShape() == VALUE)
  return true;
}

//-----------------------------------------------------------------------------

//! Performs test on accessing value of ShapeParameter where value is a single
//! reversed face.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_ShapeParameter::accessReversedValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new SHAPE Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_ShapeParameter)
    param = ActParamTool::AsShape( createParameter(doc, Parameter_Shape) );
  doc->CommitCommand();

  TopoDS_Shape
    VALUE = BRepBuilderAPI_MakeFace( gp_Pln( gp::Origin(), gp::DZ() ) );

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =====================
   *  Set Parameter value
   * ===================== */

  TCollection_AsciiString
    aMsg = TCollection_AsciiString("Setting a test value: ")
                              .Cat( VALUE.TShape()->DynamicType()->Name() );

  doc->NewCommand();
  TEST_PRINT_DECOR_L( aMsg.ToCString() );
  param->SetShape(VALUE);
  doc->CommitCommand();

  // Now we expect the Parameter to become well-formed
  ACT_VERIFY( param->IsWellFormed() )

  /* ==========================
   *  Validate Parameter value
   * ========================== */

  TopoDS_Shape returnedShape = param->GetShape();

  // Validate
  ACT_VERIFY(returnedShape == VALUE)

  /* =======================================
   *  Reverse shape and set it back to OCAF
   * ======================================= */

  // Reverse shape before storing.
  returnedShape.Reverse();

  aMsg = TCollection_AsciiString("Setting reversed value: ")
                            .Cat( returnedShape.TShape()->DynamicType()->Name() );

  doc->NewCommand();
  TEST_PRINT_DECOR_L( aMsg.ToCString() );
  param->SetShape(returnedShape);
  doc->CommitCommand();

  /* ==========================
   *  Validate Parameter value
   * ========================== */

  TopoDS_Shape returnedShape2 = param->GetShape();

  // Validate the expected problem: orientation should change but that
  // does not happen.
  ACT_VERIFY(returnedShape2 != returnedShape)

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
