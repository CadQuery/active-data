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
#include <ActTest_TreeNodeParameter.h>

// OCCT includes
#include <TDataStd_ChildNodeIterator.hxx>
#include <TDF_Tool.hxx>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on accessing USER tree of Parameters defined by Tree Nodes.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_TreeNodeParameter::accessUserTree(const int ActTestLib_NotUsed(funcID))
{
  /* ====================================
   *  Initialize underlying CAF document
   * ==================================== */

  TEST_PRINT_DECOR_L("Create new TREE NODE Parameter");

  Handle(TDocStd_Document) doc = initCAFDocument();

  // Root label
  TDF_Label label;

  doc->NewCommand();
  Handle(ActData_TreeNodeParameter)
    param = ActParamTool::AsTreeNode( createParameter(doc, Parameter_TreeNode, label) );
  doc->CommitCommand();

  /* ===================================================
   *  Prepare simple USER tree of Tree Node Parameters:
   *
   *  THIS --> A
   *     |
   *     + --> B --> C
   *           |
   *           + --> D
   * =================================================== */

  // Parameter is always well-formed
  ACT_VERIFY( param->IsWellFormed() )

  doc->NewCommand();

  // Create Tree Node A
  Handle(ActAPI_IUserParameter) AGeneric = createParameter(doc, Parameter_TreeNode);
  Handle(ActData_TreeNodeParameter) A = Handle(ActData_TreeNodeParameter)::DownCast(AGeneric);

  // Create Tree Node B
  Handle(ActAPI_IUserParameter) BGeneric = createParameter(doc, Parameter_TreeNode);
  Handle(ActData_TreeNodeParameter) B = Handle(ActData_TreeNodeParameter)::DownCast(BGeneric);

  // Create Tree Node C
  Handle(ActAPI_IUserParameter) CGeneric = createParameter(doc, Parameter_TreeNode);
  Handle(ActData_TreeNodeParameter) C = Handle(ActData_TreeNodeParameter)::DownCast(CGeneric);

  // Create Tree Node D
  Handle(ActAPI_IUserParameter) DGeneric = createParameter(doc, Parameter_TreeNode);
  Handle(ActData_TreeNodeParameter) D = Handle(ActData_TreeNodeParameter)::DownCast(DGeneric);

  // Add direct children
  param->AppendChild(A);
  param->AppendChild(B);

  // Add children to B
  B->AppendChild(C);
  B->AppendChild(D);

  doc->CommitCommand();

  /* ==================
   *  Verify USER tree
   * ================== */

  ACT_VERIFY( param->IsWellFormed() )
  ACT_VERIFY( A->IsWellFormed() )
  ACT_VERIFY( B->IsWellFormed() )
  ACT_VERIFY( C->IsWellFormed() )
  ACT_VERIFY( D->IsWellFormed() )

  // Verify root
  Handle(TDataStd_TreeNode) aTN_THIS = param->GetCAFTreeNode();
  ACT_VERIFY( !aTN_THIS->Father().IsNull() )
  ACT_VERIFY( aTN_THIS->Father()->Father().IsNull() )

  // Verify the number of children
  ACT_VERIFY(aTN_THIS->NbChildren() == 2);

  TCollection_AsciiString THISEntry, AEntry, BEntry, CEntry, DEntry;
  TDF_Tool::Entry(param->GetCAFTreeNode()->Label(), THISEntry);
  TDF_Tool::Entry(A->GetCAFTreeNode()->Label(), AEntry);
  TDF_Tool::Entry(B->GetCAFTreeNode()->Label(), BEntry);
  TDF_Tool::Entry(C->GetCAFTreeNode()->Label(), CEntry);
  TDF_Tool::Entry(D->GetCAFTreeNode()->Label(), DEntry);

  // Prepare a collection of expected entries
  EntriesByLevels EXPECTED_ENTIRES;
  EXPECTED_ENTIRES.Append( EntryList() );
  EXPECTED_ENTIRES.ChangeValue(1).Append(THISEntry);
  EXPECTED_ENTIRES.Append( EntryList() );
  EXPECTED_ENTIRES.ChangeValue(2).Append(AEntry);
  EXPECTED_ENTIRES.ChangeValue(2).Append(BEntry);
  EXPECTED_ENTIRES.Append( EntryList() );
  EXPECTED_ENTIRES.ChangeValue(3).Append(CEntry);
  EXPECTED_ENTIRES.ChangeValue(3).Append(DEntry);

  // Verify USER tree recursively
  return verifyTreeStructure(1, aTN_THIS->Father(), EXPECTED_ENTIRES);
}

//! Recursive tree validation routine. Checks that the iterated Labels are
//! those as expected.
//! \param LEVEL [in] currently iterated tree level.
//! \param TN [in] current root Tree Node.
//! \param theEntriesByLevels [in] reference collection of expected results.
//! \return true in case of success, false -- otherwise.
bool ActTest_TreeNodeParameter::verifyTreeStructure(const Standard_Integer LEVEL,
                                                    const Handle(TDataStd_TreeNode)& TN,
                                                    const EntriesByLevels& theEntriesByLevels)
{
  TDataStd_ChildNodeIterator aChildIt(TN, Standard_False);
  for ( ; aChildIt.More(); aChildIt.Next() )
  {
    Handle(TDataStd_TreeNode) aChildTN = aChildIt.Value();

    ACT_VERIFY( !aChildTN.IsNull() )

    TCollection_AsciiString aNextEntry;
    TDF_Tool::Entry(aChildTN->Label(), aNextEntry);

    ACT_VERIFY( isLabelExpectedByLevel(LEVEL, aNextEntry, theEntriesByLevels) )

    if ( !verifyTreeStructure(LEVEL + 1, aChildTN, theEntriesByLevels) )
      return false;
  }
  return true;
}

#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
