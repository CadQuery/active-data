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
#include <ActTest_ComplexArrayParameter.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing value of ComplexArrayParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_ComplexArrayParameter::accessValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new COMPLEX ARRAY Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_ComplexArrayParameter)
    param = ActParamTool::AsComplexArray( createParameter(doc, Parameter_ComplexArray) );
  doc->CommitCommand();

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =======================================
   *  Initialize input array with test data
   * ======================================= */

  const Standard_Integer NB_ELEMS = 1000;
  Handle(HComplexArray) anArray_TO = new HComplexArray(0, NB_ELEMS - 1);

  for ( Standard_Integer i = 0; i < NB_ELEMS; i++ )
  {
    ComplexNumber aNextNum(i, NB_ELEMS - i);
    anArray_TO->SetValue(i, aNextNum);
  }

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
  ACT_VERIFY(NB_ELEMS == aNbElems_FROM);

  // Access array
  Handle(HComplexArray) anArray_FROM = param->GetArray();

  // Check array element-by-element
  for ( Standard_Integer i = anArray_FROM->Lower(); i <= anArray_FROM->Upper(); i++ )
  {
    ComplexNumber aValue_TO   = anArray_TO->Value(i);
    ComplexNumber aValue_FROM = anArray_FROM->Value(i);

    ACT_VERIFY(aValue_TO.Re      == aValue_FROM.Re)
    ACT_VERIFY(aValue_TO.Im == aValue_FROM.Im)
  }

  return true;
}

//! Performs test on accessing particular elements of ComplexArrayParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_ComplexArrayParameter::accessElements(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new COMPLEX ARRAY Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_ComplexArrayParameter)
    param = ActParamTool::AsComplexArray( createParameter(doc, Parameter_ComplexArray) );
  doc->CommitCommand();

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =======================================
   *  Initialize input array with test data
   * ======================================= */

  const Standard_Integer NB_ELEMS = 2;
  Handle(HComplexArray) anArray_TO = new HComplexArray(0, NB_ELEMS - 1);

  anArray_TO->SetValue( 0, ComplexNumber() );
  anArray_TO->SetValue( 1, ComplexNumber() );
  
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
  param->SetElement( 0, ComplexNumber(1.0, 2.0) );
  param->SetElement( 1, ComplexNumber(3.0, 4.0) );
  doc->CommitCommand();

  /* =====================
   *  Perform validations
   * ===================== */

  ACT_VERIFY(param->NbElements()     == NB_ELEMS)
  ACT_VERIFY(param->GetElement(0).Re == 1.0)
  ACT_VERIFY(param->GetElement(0).Im == 2.0)
  ACT_VERIFY(param->GetElement(1).Re == 3.0)
  ACT_VERIFY(param->GetElement(1).Im == 4.0)

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
