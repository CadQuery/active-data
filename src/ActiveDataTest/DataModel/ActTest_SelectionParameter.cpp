//-----------------------------------------------------------------------------
// Created on: May 2012
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

  ActTest_DocAlloc docAlloc;
  Handle(TDocStd_Document) doc = docAlloc.Doc;

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

  ActTest_DocAlloc docAlloc;
  Handle(TDocStd_Document) doc = docAlloc.Doc;

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
