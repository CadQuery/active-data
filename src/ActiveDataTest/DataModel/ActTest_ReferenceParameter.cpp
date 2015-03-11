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
#include <ActTest_ReferenceParameter.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Test function for Reference Parameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_ReferenceParameter::testReference(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new REFERENCE Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_ReferenceParameter)
    param = ActParamTool::AsReference( createParameter(doc, Parameter_Reference) );
  doc->CommitCommand();

  // Root label for Parameter
  TDF_Label label;

  /* ======================================
   *  Create another Parameter to refer to
   * ====================================== */

  doc->NewCommand();

  ActAPI_ParameterList PARAMS;
  PARAMS.Append( createParameter(doc, Parameter_Int,  label) );
  PARAMS.Append( createParameter(doc, Parameter_Real, label) );
  PARAMS.Append( createParameter(doc, Parameter_Bool, label) );

  doc->CommitCommand();

  /* =====================================================
   *  Set up the reference to the 1-st Parameter & verify
   * ===================================================== */

  doc->NewCommand();
  param->SetTarget( PARAMS(1) );
  doc->CommitCommand();

  ACT_VERIFY( param->IsTarget( PARAMS(1) ) )

  doc->NewCommand();
  param->RemoveTarget();
  doc->CommitCommand();

  ACT_VERIFY( param->GetTarget().IsNull() )

  /* =====================================================
   *  Set up the reference to the 2-nd Parameter & verify
   * ===================================================== */

  doc->NewCommand();
  param->SetTarget( PARAMS(2) );
  doc->CommitCommand();

  ACT_VERIFY( param->IsTarget( PARAMS(2) ) )
  ACT_VERIFY( !param->GetTarget().IsNull() )

  /* =====================================================
   *  Set up the reference to the 3-rd Parameter & verify
   * ===================================================== */

  doc->NewCommand();
  param->SetTarget( PARAMS(3) );
  doc->CommitCommand();

  ACT_VERIFY( param->IsTarget( PARAMS(3) ) )
  ACT_VERIFY( !param->GetTarget().IsNull() )

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
