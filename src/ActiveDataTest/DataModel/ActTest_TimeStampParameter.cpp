//-----------------------------------------------------------------------------
// Created on: June 2012
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
