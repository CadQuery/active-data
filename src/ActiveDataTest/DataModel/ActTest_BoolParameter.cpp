//-----------------------------------------------------------------------------
// Created on: March 2012
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

// Own include
#include <ActTest_BoolParameter.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//! Performs test on accessing value of BoolParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_BoolParameter::accessValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new BOOL Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_BoolParameter)
    param = ActParamTool::AsBool( createParameter(doc, Parameter_Bool) );
  doc->CommitCommand();

  const Standard_Boolean VALUE = Standard_True;

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =====================
   *  Set Parameter value
   * ===================== */

  TCollection_AsciiString
    aMsg = TCollection_AsciiString("Setting a test value: ")
                              .Cat(VALUE ? "TRUE" : "FALSE");

  doc->NewCommand();
  TEST_PRINT_DECOR_L( aMsg.ToCString() );
  param->SetValue(VALUE);
  doc->CommitCommand();

  // Now we expect the Parameter to become well-formed
  ACT_VERIFY( param->IsWellFormed() );

  /* ==========================
   *  Validate Parameter value
   * ========================== */

  // Validate
  ACT_VERIFY(param->GetValue() == VALUE)
  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
