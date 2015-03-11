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
#include <ActTest_NameParameter.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing value of NameParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_NameParameter::accessValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new NAME Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_NameParameter)
    param = ActParamTool::AsName( createParameter(doc, Parameter_Name) );
  doc->CommitCommand();

  TCollection_ExtendedString VALUE = "TEST_TEST";

  // Parameter is always well-formed
  ACT_VERIFY( param->IsWellFormed() )

  /* =====================
   *  Set Parameter value
   * ===================== */

  TCollection_ExtendedString
    aMsg = TCollection_ExtendedString("Setting a test value: ").Cat(VALUE);

  doc->NewCommand();
  TEST_PRINT_DECOR_L( TCollection_AsciiString(aMsg).ToCString() );
  param->SetValue(VALUE);
  doc->CommitCommand();

  // Parameter is always well-formed
  ACT_VERIFY( param->IsWellFormed() )

  /* ========================
   *  Access Parameter value
   * ======================== */

  TCollection_ExtendedString aString = param->GetValue();

  // Finally, we check if the output is equal to the input to ensure
  // that no corruption has happened during data transferring to/from CAF
  ACT_VERIFY( ActAux::are_equal( TCollection_AsciiString(aString).ToCString(),
                                 TCollection_AsciiString(VALUE).ToCString() ) )

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
