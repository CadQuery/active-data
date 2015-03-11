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
#include <ActTest_StringArrayParameter.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing value of StringArrayParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_StringArrayParameter::accessValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new STRING ARRAY Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_StringArrayParameter)
    param = ActParamTool::AsStringArray( createParameter(doc, Parameter_StringArray) );
  doc->CommitCommand();

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =======================================
   *  Initialize input array with test data
   * ======================================= */

  const Standard_Integer NB_ELEMS = 500;
  Handle(HStringArray) anArray_TO = new HStringArray(0, NB_ELEMS - 1);

  for ( Standard_Integer i = 0; i < NB_ELEMS; i++ )
  {
    TCollection_ExtendedString aNextString( TCollection_AsciiString("STR_").Cat(i) );
    anArray_TO->SetValue(i, aNextString);
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
  ACT_VERIFY(NB_ELEMS == aNbElems_FROM)

  // Access array
  Handle(HStringArray) anArray_FROM = param->GetArray();

  // Check array element-by-element
  for ( Standard_Integer i = anArray_FROM->Lower(); i <= anArray_FROM->Upper(); i++ )
  {
    TCollection_ExtendedString aValue_TO = anArray_TO->Value(i);
    TCollection_ExtendedString aValue_FROM = anArray_FROM->Value(i);

    ACT_VERIFY(aValue_TO == aValue_FROM)
  }

  return true;
}

//! Performs test on accessing individual elements of StringArrayParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_StringArrayParameter::accessElements(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new STRING ARRAY Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_StringArrayParameter)
    param = ActParamTool::AsStringArray( createParameter(doc, Parameter_StringArray) );
  doc->CommitCommand();

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =======================================
   *  Initialize input array with test data
   * ======================================= */

  const Standard_Integer NB_ELEMS = 2;
  Handle(HStringArray) anArray_TO = new HStringArray(0, NB_ELEMS - 1);

  anArray_TO->SetValue( 0, TCollection_ExtendedString() );
  anArray_TO->SetValue( 1, TCollection_ExtendedString() );
  
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

  TCollection_ExtendedString aString1("String 1");
  TCollection_ExtendedString aString2("String 2");

  doc->NewCommand();
  param->SetElement(0, aString1);
  param->SetElement(1, aString2);
  doc->CommitCommand();

  /* =====================
   *  Perform validations
   * ===================== */

  ACT_VERIFY(param->NbElements()  == NB_ELEMS)
  ACT_VERIFY(param->GetElement(0) == aString1)
  ACT_VERIFY(param->GetElement(1) == aString2)

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
