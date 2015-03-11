//-----------------------------------------------------------------------------
// Created on: April 2012
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
#include <ActTest_ReferenceListParameter.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Test function for Reference List Parameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_ReferenceListParameter::testReferences(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new REFERENCE LIST Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_ReferenceListParameter)
    param = ActParamTool::AsReferenceList( createParameter(doc, Parameter_ReferenceList) );
  doc->CommitCommand();

  // Root label for Parameter
  TDF_Label label;

  /* ==========================================
   *  Create some other Parameters to refer to
   * ========================================== */

  doc->NewCommand();

  ActAPI_ParameterList PARAMS;
  PARAMS.Append( createParameter(doc, Parameter_Int,         label) );
  PARAMS.Append( createParameter(doc, Parameter_Real,        label) );
  PARAMS.Append( createParameter(doc, Parameter_Bool,        label) );
  PARAMS.Append( createParameter(doc, Parameter_AsciiString, label) );
  PARAMS.Append( createParameter(doc, Parameter_BoolArray,   label) );

  doc->CommitCommand();

  /* =======================
   *  Set up the references
   * ======================= */

  doc->NewCommand();

  param->AddTarget( PARAMS(1) );
  param->AddTarget( PARAMS(2) );
  param->AddTarget( PARAMS(3) );
  param->AddTarget( PARAMS(4) );

  doc->CommitCommand();

  /* =======================
   *  Verify the references
   * ======================= */

  ACT_VERIFY(  param->HasTarget( PARAMS(1) ) )
  ACT_VERIFY(  param->HasTarget( PARAMS(2) ) )
  ACT_VERIFY(  param->HasTarget( PARAMS(3) ) )
  ACT_VERIFY(  param->HasTarget( PARAMS(4) ) )
  ACT_VERIFY( !param->HasTarget( PARAMS(5) ) )

  /* ========================
   *  Remove some references
   * ======================== */

  doc->NewCommand();

  ACT_VERIFY(  param->RemoveTarget( PARAMS(1) ) )
  ACT_VERIFY(  param->RemoveTarget( PARAMS(3) ) )
  ACT_VERIFY( !param->RemoveTarget( PARAMS(5) ) )

  doc->CommitCommand();

  /* ===============================
   *  Verify the rest of references
   * =============================== */

  ACT_VERIFY( !param->HasTarget( PARAMS(1) ) )
  ACT_VERIFY(  param->HasTarget( PARAMS(2) ) )
  ACT_VERIFY( !param->HasTarget( PARAMS(3) ) )
  ACT_VERIFY(  param->HasTarget( PARAMS(4) ) )
  ACT_VERIFY( !param->HasTarget( PARAMS(5) ) )

  return true;
}

//! Test function for Reference List Parameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_ReferenceListParameter::testReferenceListParameter_SwapTargets(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new REFERENCE LIST Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_ReferenceListParameter)
    param = ActParamTool::AsReferenceList( createParameter(doc, Parameter_ReferenceList) );
  doc->CommitCommand();

  // Root label for Parameter
  TDF_Label label;

  /* ==========================================
   *  Create some other Parameters to refer to
   * ========================================== */

  doc->NewCommand();

  ActAPI_ParameterList PARAMS;
  PARAMS.Append( createParameter(doc, Parameter_Int,         label) );
  PARAMS.Append( createParameter(doc, Parameter_Real,        label) );
  PARAMS.Append( createParameter(doc, Parameter_Bool,        label) );
  PARAMS.Append( createParameter(doc, Parameter_AsciiString, label) );
  PARAMS.Append( createParameter(doc, Parameter_BoolArray,   label) );

  doc->CommitCommand();

  /* =========================================
   *  Add targets to Reference List Parameter
   * ========================================= */

  doc->NewCommand();

  param->AddTarget( PARAMS(1) );
  param->AddTarget( PARAMS(2) );
  param->AddTarget( PARAMS(3) );
  param->AddTarget( PARAMS(4) );

  doc->CommitCommand();

  ACT_VERIFY(  param->HasTarget( PARAMS(1) ) )
  ACT_VERIFY(  param->HasTarget( PARAMS(2) ) )
  ACT_VERIFY(  param->HasTarget( PARAMS(3) ) )
  ACT_VERIFY(  param->HasTarget( PARAMS(4) ) )
  ACT_VERIFY( !param->HasTarget( PARAMS(5) ) )

  /* =====================
   *  Try to swap targets
   * ===================== */

  doc->NewCommand();

  ACT_VERIFY( param->SwapTargets( 1, 3 ) );
  ACT_VERIFY( param->SwapTargets( 4, 2 ) );

  doc->CommitCommand();

  // check swap (1,3)
  ACT_VERIFY( param->HasTarget( PARAMS(1) ) == 3 )
  ACT_VERIFY( param->HasTarget( PARAMS(3) ) == 1 )

  // check swap (4,2)
  ACT_VERIFY( param->HasTarget( PARAMS(4) ) == 2 )
  ACT_VERIFY( param->HasTarget( PARAMS(2) ) == 4 )

  doc->NewCommand();

  // check swap with unreferenced target
  ACT_VERIFY( !param->SwapTargets( 5, 3 ) )

  doc->CommitCommand();

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
