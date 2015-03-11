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
#include <ActTest_SelectionParameter.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing map of integer values stored in
//! SelectionParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_SelectionParameter::accessSelectionMask(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new SELECTION Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_SelectionParameter)
    param = ActParamTool::AsSelection( createParameter(doc, Parameter_Selection) );
  doc->CommitCommand();

  // Not yet initialized -> BAD-FORMED
  ACT_VERIFY( !param->IsWellFormed() )

  /* =====================
   *  Prepare a test mask
   * ===================== */

  Standard_Integer MASKED_IDs[] = {10, 20, 30, 40, 15, 25, 35, 45};

  TColStd_PackedMapOfInteger aTestMap;
  for ( Standard_Integer i = 0; i < sizeof(MASKED_IDs)/sizeof(Standard_Integer); i++ )
    aTestMap.Add(MASKED_IDs[i]);
  
  /* =====================
   *  Store the test mask
   * ===================== */

  doc->OpenCommand();
  param->SetMask( new TColStd_HPackedMapOfInteger(aTestMap) );
  doc->CommitCommand();

  /* ================
   *  Verify results
   * ================ */

  // Initialized -> WELL-FORMED
  ACT_VERIFY( param->IsWellFormed() )

  // Access stored mask
  Handle(TColStd_HPackedMapOfInteger) aMask_FROM = param->GetMask();

  ACT_VERIFY( !aMask_FROM.IsNull() )

  // Compare the contents of both maps: they should be identical
  ACT_VERIFY( aMask_FROM->Map().IsEqual(aTestMap) )

  return true;
}

//! Performs test on accessing individual masked IDs of SelectionParameter.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_SelectionParameter::accessSelectionMaskIDs(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new SELECTION Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  doc->NewCommand();
  Handle(ActData_SelectionParameter)
    param = ActParamTool::AsSelection( createParameter(doc, Parameter_Selection) );
  doc->CommitCommand();

  TColStd_PackedMapOfInteger aTestMap;

  /* ========================================
   *  Store the test mask -- initially empty
   * ======================================== */

  doc->OpenCommand();
  param->SetMask( new TColStd_HPackedMapOfInteger(aTestMap) );
  doc->CommitCommand();

  ACT_VERIFY(param->Size() == 0);

  /* ========================
   *  Try per-element access
   * ======================== */

  Standard_Integer MASKED_IDs[] = {10, 40, 15};

  doc->OpenCommand();
  param->Add(MASKED_IDs[0]);
  doc->CommitCommand();

  ACT_VERIFY(  param->Size() == 1 )
  ACT_VERIFY(  param->Contains(MASKED_IDs[0]) )
  ACT_VERIFY( !param->Contains(MASKED_IDs[1]) )
  ACT_VERIFY( !param->Contains(MASKED_IDs[2]) )

  // Try again just the sampe
  doc->OpenCommand();
  param->Add(MASKED_IDs[0]);
  doc->CommitCommand();

  // Verify again
  ACT_VERIFY(  param->Size() == 1 )
  ACT_VERIFY(  param->Contains(MASKED_IDs[0]) )
  ACT_VERIFY( !param->Contains(MASKED_IDs[1]) )
  ACT_VERIFY( !param->Contains(MASKED_IDs[2]) )

  doc->OpenCommand();
  param->Add(MASKED_IDs[1]);
  doc->CommitCommand();

  ACT_VERIFY(  param->Size() == 2 )
  ACT_VERIFY(  param->Contains(MASKED_IDs[0]) )
  ACT_VERIFY(  param->Contains(MASKED_IDs[1]) )
  ACT_VERIFY( !param->Contains(MASKED_IDs[2]) )

  doc->OpenCommand();
  param->Add(MASKED_IDs[2]);
  doc->CommitCommand();

  ACT_VERIFY( param->Size() == 3 )
  ACT_VERIFY( param->Contains(MASKED_IDs[0]) )
  ACT_VERIFY( param->Contains(MASKED_IDs[1]) )
  ACT_VERIFY( param->Contains(MASKED_IDs[2]) )

  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
