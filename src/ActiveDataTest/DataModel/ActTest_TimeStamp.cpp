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
#include <ActTest_TimeStamp.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs complex test on TimeStamp functionality.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_TimeStamp::cumulTest(const int ActTestLib_NotUsed(funcID))
{
  TEST_PRINT_DECOR_L("Generating UniqueTime structure for current time")

  Handle(ActAux_TimeStamp) aTS1 = ActAux_TimeStampTool::Generate();

  TEST_PRINT_DECOR_L("Sleep for a while just for clear experiment")

  Sleep(100);

  TEST_PRINT_DECOR_L("Convert initial UniqueTime structure to CAF-suitable array")

  Handle(HIntArray) aCAFSuitedTM = ActAux_TimeStampTool::AsChunked(aTS1);

  TEST_PRINT_DECOR_L("Convert CAF-suitable array back to UniqueTime structure")

  Handle(ActAux_TimeStamp) aTS2 = ActAux_TimeStampTool::FromChunked(aCAFSuitedTM);

  // Take advantage of overloaded equality operator
  ACT_VERIFY( aTS1->IsEqual(aTS2) )

  return true;
}

//! Performs a simple test on accessing modification time for
//! Integer Parameters.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_TimeStamp::accessMTime(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  Handle(TDocStd_Document) doc = initCAFDocument();

  /* ===========================
   *  Create Integer Parameters
   * =========================== */

  doc->NewCommand();
  Handle(ActAPI_IUserParameter) aParam1 = createParameter(doc, Parameter_Int);
  Handle(ActAPI_IUserParameter) aParam2 = createParameter(doc, Parameter_Int);
  doc->CommitCommand();

  Handle(ActData_IntParameter)
    anIntParam1 = Handle(ActData_IntParameter)::DownCast(aParam1);
  Handle(ActData_IntParameter)
    anIntParam2 = Handle(ActData_IntParameter)::DownCast(aParam2);

  /* ===============================================================
   *  Set some values and read the correspondent modification times
   * =============================================================== */

  doc->NewCommand();
  anIntParam1->SetValue(0);
  anIntParam2->SetValue(0);
  doc->CommitCommand();

  Handle(ActAux_TimeStamp) aTSFor1 = anIntParam1->GetMTime();
  Handle(ActAux_TimeStamp) aTSFor2 = anIntParam2->GetMTime();

  ACT_VERIFY( aTSFor1->IsLess(aTSFor2) )

  doc->NewCommand();
  anIntParam2->SetValue(0);
  anIntParam1->SetValue(0);
  doc->CommitCommand();

  aTSFor1 = anIntParam1->GetMTime();
  aTSFor2 = anIntParam2->GetMTime();

  ACT_VERIFY( aTSFor1->IsGreater(aTSFor2) )

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
