//-----------------------------------------------------------------------------
// Created on: March 2012
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
#include <ActTest_BoolArrayParameter.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing value of BoolArrayParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_BoolArrayParameter::accessValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new BOOL ARRAY Parameter");

  ActTest_DocAlloc docAlloc;
  Handle(TDocStd_Document) doc = docAlloc.Doc;

  doc->NewCommand();
  Handle(ActData_BoolArrayParameter)
    param = ActParamTool::AsBoolArray( createParameter(doc, Parameter_BoolArray) );
  doc->CommitCommand();

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =======================================
   *  Initialize input array with test data
   * ======================================= */

  const Standard_Integer NB_ELEMS = 1000;
  Handle(HBoolArray) anArray_TO = new HBoolArray(0, NB_ELEMS - 1);

  for ( Standard_Integer i = 0; i < NB_ELEMS; i++ )
    anArray_TO->SetValue( i, (i % 2 ? Standard_True : Standard_False) );

  /* =====================
   *  Set Parameter value
   * ===================== */

  TCollection_AsciiString
    aMsg = TCollection_AsciiString("Setting a test array of ")
                              .Cat(NB_ELEMS)
                              .Cat(" elements");

  doc->NewCommand();
  TEST_PRINT_DECOR_L( aMsg.ToCString() );
  param->SetArray(anArray_TO);
  doc->CommitCommand();

  // Now we expect the Parameter to become well-formed
  ACT_VERIFY( param->IsWellFormed() )

  /* ==========================================================
   *  Access array FROM CAF structure. Perform validations on:
   *  - the number of elements;
   *  - the entire array;
   * ========================================================== */

  // Access number of elements
  Standard_Integer aNbElems_FROM = param->NbElements();

  // Check if the number of elements is as expected
  ACT_VERIFY(NB_ELEMS == aNbElems_FROM)

  // Access array
  Handle(HBoolArray) anArray_FROM = param->GetArray();

  // Check array element-by-element
  for ( Standard_Integer i = anArray_FROM->Lower(); i <= anArray_FROM->Upper(); i++ )
  {
    Standard_Boolean aValue_TO = anArray_TO->Value(i);
    Standard_Boolean aValue_FROM = anArray_FROM->Value(i);
    ACT_VERIFY(aValue_TO == aValue_FROM);
  }

  return true;
}

//! Performs test on accessing particular elements of BoolArrayParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_BoolArrayParameter::accessElements(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new BOOL ARRAY Parameter");

  ActTest_DocAlloc docAlloc;
  Handle(TDocStd_Document) doc = docAlloc.Doc;

  doc->NewCommand();
  Handle(ActData_BoolArrayParameter)
    param = ActParamTool::AsBoolArray( createParameter(doc, Parameter_BoolArray) );
  doc->CommitCommand();

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =======================================
   *  Initialize input array with test data
   * ======================================= */

  const Standard_Integer NB_ELEMS = 2;
  Handle(HBoolArray) anArray_TO = new HBoolArray(0, NB_ELEMS - 1);

  anArray_TO->SetValue(0, Standard_False);
  anArray_TO->SetValue(1, Standard_False);
  
  /* =====================
   *  Set Parameter value
   * ===================== */

  TCollection_AsciiString
    aMsg = TCollection_AsciiString("Setting a test array of ")
                              .Cat(NB_ELEMS)
                              .Cat(" elements");

  doc->NewCommand();
  TEST_PRINT_DECOR_L( aMsg.ToCString() );
  param->SetArray(anArray_TO);
  doc->CommitCommand();

  // Now we expect the Parameter to become well-formed
  ACT_VERIFY( param->IsWellFormed() )

  /* ========================
   *  Update Parameter value
   * ======================== */

  doc->NewCommand();
  param->SetElement(0, Standard_True);
  param->SetElement(1, Standard_False);
  doc->CommitCommand();

  /* =====================
   *  Perform validations
   * ===================== */

  ACT_VERIFY(param->NbElements()  == NB_ELEMS)
  ACT_VERIFY(param->GetElement(0) == Standard_True)
  ACT_VERIFY(param->GetElement(1) == Standard_False)

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
