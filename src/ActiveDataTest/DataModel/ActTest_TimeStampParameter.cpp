//-----------------------------------------------------------------------------
// Created on: June 2012
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
#include <ActTest_TimeStampParameter.h>

// ACT Algorithmic layer includes
#include <ActAux_TimeStamp.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing value of TimeStampParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_TimeStampParameter::accessValue(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new TIMESTAMP Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_TimeStampParameter)
    param = ActParamTool::AsTimeStamp( createParameter(doc, Parameter_TimeStamp) );
  doc->CommitCommand();

  Handle(ActAux_TimeStamp) TS = ActAux_TimeStampTool::Generate();

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =====================
   *  Set Parameter value
   * ===================== */

  doc->NewCommand();
  param->SetValue(TS);
  doc->CommitCommand();

  // Now we expect the Parameter to become well-formed
  ACT_VERIFY( param->IsWellFormed() )

  /* ==========================
   *  Validate Parameter value
   * ========================== */

  // Validate
  ACT_VERIFY( param->GetValue()->IsEqual(TS) )
  return true;
}

//! Performs test on accessing value of TimeStampParameter by portions.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_TimeStampParameter::accessValueByPortions(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new TIMESTAMP Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_TimeStampParameter)
    param = ActParamTool::AsTimeStamp( createParameter(doc, Parameter_TimeStamp) );
  doc->CommitCommand();

  Handle(ActAux_TimeStamp) TS = ActAux_TimeStampTool::Generate();
  Handle(HIntArray) TSArr = ActAux_TimeStampTool::AsChunked(TS);

  Standard_Integer Seconds = TSArr->Value(0);
  Standard_Integer Minutes = TSArr->Value(1);
  Standard_Integer Hours   = TSArr->Value(2);
  Standard_Integer MDays   = TSArr->Value(3);
  Standard_Integer Month   = TSArr->Value(4);
  Standard_Integer Years   = TSArr->Value(5);
  Standard_Integer WDays   = TSArr->Value(6);
  Standard_Integer YDays   = TSArr->Value(7);
  Standard_Integer IsDST   = TSArr->Value(8);

  // Parameter is not well-formed as it does not have value Attribute yet
  ACT_VERIFY( !param->IsWellFormed() )

  /* =====================
   *  Set Parameter value
   * ===================== */

  doc->NewCommand();
  param->SetValue(Seconds, ActData_TimeStampParameter::Item_Seconds);
  param->SetValue(Minutes, ActData_TimeStampParameter::Item_Minutes);
  param->SetValue(Hours,   ActData_TimeStampParameter::Item_Hours);
  param->SetValue(MDays,   ActData_TimeStampParameter::Item_MDays);
  param->SetValue(Month,   ActData_TimeStampParameter::Item_Month);
  param->SetValue(Years,   ActData_TimeStampParameter::Item_Years);
  param->SetValue(WDays,   ActData_TimeStampParameter::Item_WDays);
  param->SetValue(YDays,   ActData_TimeStampParameter::Item_YDays);
  param->SetValue(IsDST,   ActData_TimeStampParameter::Item_IsDST);
  doc->CommitCommand();

  // Now we expect the Parameter to become well-formed
  ACT_VERIFY( param->IsWellFormed() )

  /* ==========================
   *  Validate Parameter value
   * ========================== */

  // Validate
  ACT_VERIFY(param->GetValue(ActData_TimeStampParameter::Item_Seconds) == Seconds)
  ACT_VERIFY(param->GetValue(ActData_TimeStampParameter::Item_Minutes) == Minutes)
  ACT_VERIFY(param->GetValue(ActData_TimeStampParameter::Item_Hours)   == Hours)
  ACT_VERIFY(param->GetValue(ActData_TimeStampParameter::Item_MDays)   == MDays)
  ACT_VERIFY(param->GetValue(ActData_TimeStampParameter::Item_Month)   == Month)
  ACT_VERIFY(param->GetValue(ActData_TimeStampParameter::Item_Years)   == Years)
  ACT_VERIFY(param->GetValue(ActData_TimeStampParameter::Item_WDays)   == WDays)
  ACT_VERIFY(param->GetValue(ActData_TimeStampParameter::Item_YDays)   == YDays)
  ACT_VERIFY(param->GetValue(ActData_TimeStampParameter::Item_IsDST)   == IsDST)
  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
