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
#include <ActTest_CopyPasteEngine.h>

// Active Data unit tests
#include <ActTest_DummyTreeFunction.h>
#include <ActTest_StubANode.h>
#include <ActTest_StubBNode.h>
#include <ActTest_StubMeshNode.h>

// ACT Test Library includes
#include <ActTestLib_Common.h>
#include <ActTestLib_Launcher.h>

// Active Data includes
#include <ActData_CAFDumper.h>
#include <ActData_RealEvaluatorFunc.h>
#include <ActData_RealVarNode.h>
#include <ActData_Utils.h>

// Mesh includes
#include <Mesh_Node.h>

#pragma warning(disable: 4127) // "Conditional expression is constant" by ACT_VERIFY
#pragma warning(disable: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY

//-----------------------------------------------------------------------------
// Business logic
//-----------------------------------------------------------------------------

//! Performs test on Copy method.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_PlainToPlain(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_PlainToPlain");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ===================================
   *  Prepare initial data to be copied
   * =================================== */

  ACT_VERIFY( M->NewEmpty() );

  // Prepare detached data
  Handle(ActTest_StubBNode) aSourceNode_B = Handle(ActTest_StubBNode)::DownCast( ActTest_StubBNode::Instance() );
  Handle(ActTest_StubANode) aTargetNode_A = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() );
  TopoDS_Shape aTargetShapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() };
  Standard_Real aTargetRealVal = ActTestLib_Common::RandomReal();
  Standard_Integer aSourceIntVal = ActTestLib_Common::RandomInteger();
  Standard_Integer aSourceAltIntVal = -aSourceIntVal;
  Standard_Real aSourceRealVal = ActTestLib_Common::RandomReal();
  Standard_Real aSourceAltRealVal = -aSourceRealVal;
  
  // Attach data to the CAF Document
  M->OpenCommand();
  M->StubAPartition()->AddNode(aTargetNode_A); // This will be a ROOT Node
  M->StubBPartition()->AddNode(aSourceNode_B);
  aTargetNode_A->SetName("Parent A");
  aTargetNode_A->Init(aTargetShapes[0], aTargetShapes[1], aTargetRealVal);
  aSourceNode_B->SetName("Source B");
  aSourceNode_B->Init(aSourceIntVal, aSourceRealVal);
  ACT_VERIFY( aSourceNode_B->IsWellFormed() );
  ACT_VERIFY( aTargetNode_A->IsWellFormed() );
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  /* ==============
   *  Perform Copy
   * ============== */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(aSourceNode_B);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  // Access the Data Node which has been just created for buffering purpose.
  // Such Nodes have their own dedicated Label in the Data Model. We can
  // access this Label and settle down a Node onto it in order to check if
  // data is generally Ok
  Handle(ActTest_StubBNode) aBufferNode = Handle(ActTest_StubBNode)::DownCast( tool->GetRootBuffered() );
  ACT_VERIFY( aBufferNode->IsWellFormed() );

  // Do something with source Node to assure that copy is not affected
  M->OpenCommand();
  aSourceNode_B->Init(aSourceAltIntVal, aSourceAltRealVal);
  M->CommitCommand();

  ACT_VERIFY(aSourceNode_B->GetIntValue() == aSourceAltIntVal);
  ACT_VERIFY(aSourceNode_B->GetRealValue() == aSourceAltRealVal);

  /* ===============
   *  Perform Paste
   * =============== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  aTargetNode_A->AddChildNode(aSourceCopy);
  M->CommitCommand();

  ACT_VERIFY( !aSourceCopy.IsNull() );
  ACT_VERIFY( aSourceCopy->IsWellFormed() );

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  Handle(ActTest_StubBNode) aSourceCopyStub = Handle(ActTest_StubBNode)::DownCast(aSourceCopy);

  // Values should be equal to the initial sources
  ACT_VERIFY(aSourceCopyStub->GetIntValue() == aSourceIntVal);
  ACT_VERIFY(aSourceCopyStub->GetRealValue() == aSourceRealVal);

  return true;
}

//! Performs test on Copy method with the following Nodes:
//! ---------------------------------------------------------------------------
//!
//!  A [ROOT] ---+---> A_1 ---+---> B_1
//!              |            |
//!              |            +---> A_2 ---+---> B_2
//!              |                         |
//!              |                         +---> A_3
//!              |
//!              +---> B_3
//!
//! ---------------------------------------------------------------------------
//! Here A_1 is the sub-tree being copied, while B_3 is the target Node.
//! The expected results are as follows:
//! ---------------------------------------------------------------------------
//!
//!  A [ROOT] ---+---> A_1 ---+---> B_1
//!              |            |
//!              |            +---> A_2 ---+---> B_2
//!              |                         |
//!              |                         +---> A_3
//!              |
//!              +---> B_3 ---+---> A_1 ---+---> B_1
//!                                        |
//!                                        +---> A_2 ---+---> B_2
//!                                                     |
//!                                                     +---> A_3
//!
//! ---------------------------------------------------------------------------
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeToPlain(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeToPlain");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  // Prepare data for tree verification
  NCollection_Sequence<ActAPI_DataObjectId> TreeLevel_1;
  TreeLevel_1.Append( A_1->GetId() );
  NCollection_Sequence<ActAPI_DataObjectId> TreeLevel_2;
  TreeLevel_2.Append( B_1->GetId() );
  TreeLevel_2.Append( A_2->GetId() );
  NCollection_Sequence<ActAPI_DataObjectId> TreeLevel_3;
  TreeLevel_3.Append( B_2->GetId() );
  TreeLevel_3.Append( A_3->GetId() );
  TreeLevelSeq TreeLevels[] = {TreeLevel_1, TreeLevel_2, TreeLevel_3};

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* ======================================================
   *  Now we delete the initial sub-tree in order to check
   *  that the prepared copy is fully independent
   * ====================================================== */

  M->OpenCommand();
  ACT_VERIFY( M->DeleteNode( A_1->GetId() ) );
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =========================================
   *  Now check the cloned hierarchy of Nodes
   * ========================================= */
  
  isOk = Standard_True;
  verifyTree(aSourceCopy, COPY_Reloc, PASTE_Reloc, TreeLevels, 0, 1, isOk);
  ACT_VERIFY(isOk);

  return true;
}

//! See case 3.1 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithReferencesToPlain_1(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithReferencesToPlain_1");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* =====================================
   *  Establish Tree Function connections
   * ===================================== */

  M->OpenCommand();

  A_2->ConnectTreeFunction( ActTest_StubANode::PID_TFunc,
                            ActTest_DummyTreeFunction::GUID(),
                            ActAPI_ParameterStream() << B_2->Parameter(ActTest_StubBNode::PID_Int)
                                                     << A_3->Parameter(ActTest_StubANode::PID_Real),
                            ActAPI_ParameterStream() << B_1->Parameter(ActTest_StubBNode::PID_Int) );

  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==========================================
   *  Verify relocation of involved references
   * ========================================== */

  Handle(ActAPI_IUserParameter) A_2_copy_TFunc = A_2_copy->Parameter(ActTest_StubANode::PID_TFunc);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_2) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_3_copy) ); // !!!
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_2_copy) ); // !!!

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_1_copy) ); // !!!
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_2) );

  // Precise the actual Parameters referred to by Tree Function one
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_copy_TFunc).HasAsArgument( A_3_copy->Parameter(ActTest_StubANode::PID_Real) ) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_copy_TFunc).HasAsArgument( B_2_copy->Parameter(ActTest_StubBNode::PID_Int) ) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_copy_TFunc).HasAsResult( B_1_copy->Parameter(ActTest_StubBNode::PID_Int) ) );

  return true;
}

//! See case 3.2 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithReferencesToPlain_2(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithReferencesToPlain_2");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* =====================================
   *  Establish Tree Function connections
   * ===================================== */

  M->OpenCommand();

  A_2->ConnectTreeFunction( ActTest_StubANode::PID_TFunc,
                            ActTest_DummyTreeFunction::GUID(),
                            ActAPI_ParameterStream() << B_2->Parameter(ActTest_StubBNode::PID_Int)
                                                     << B_3->Parameter(ActTest_StubBNode::PID_Int),
                            ActAPI_ParameterStream() << B_1->Parameter(ActTest_StubBNode::PID_Int) );

  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==========================================
   *  Verify relocation of involved references
   * ========================================== */

  Handle(ActAPI_IUserParameter) A_2_copy_TFunc = A_2_copy->Parameter(ActTest_StubANode::PID_TFunc);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_2) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_2) );

  ACT_VERIFY( ActData_ParameterFactory::AsTreeFunction(A_2_copy_TFunc)->Arguments().IsNull() );
  ACT_VERIFY( ActData_ParameterFactory::AsTreeFunction(A_2_copy_TFunc)->Results().IsNull() );

  /* ==================================================
   *  Verify that the source references is still there
   * ================================================== */

  Handle(ActAPI_IUserParameter) A_2_TFunc = A_2->Parameter(ActTest_StubANode::PID_TFunc);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_1) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_2) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_3) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_3) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_3) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_2_copy) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3).HasObservers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_1).HasObservers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_2).HasObservers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_3).HasObservers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasObservers() );

  return true;
}

//! See case 3.3 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithReferencesToPlain_3(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithReferencesToPlain_3");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* =====================================
   *  Establish Tree Function connections
   * ===================================== */

  M->OpenCommand();

  A_2->ConnectTreeFunction( ActTest_StubANode::PID_TFunc,
                            ActTest_DummyTreeFunction::GUID(),
                            ActAPI_ParameterStream() << B_2->Parameter(ActTest_StubBNode::PID_Int)
                                                     << A_3->Parameter(ActTest_StubANode::PID_Real),
                            ActAPI_ParameterStream() << B_3->Parameter(ActTest_StubBNode::PID_Int) );

  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==========================================
   *  Verify relocation of involved references
   * ========================================== */

  Handle(ActAPI_IUserParameter) A_2_copy_TFunc = A_2_copy->Parameter(ActTest_StubANode::PID_TFunc);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_2) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_2) );

  ACT_VERIFY( ActData_ParameterFactory::AsTreeFunction(A_2_copy_TFunc)->Arguments().IsNull() );
  ACT_VERIFY( ActData_ParameterFactory::AsTreeFunction(A_2_copy_TFunc)->Results().IsNull() );

  /* ==================================================
   *  Verify that the source references is still there
   * ================================================== */

  Handle(ActAPI_IUserParameter) A_2_TFunc = A_2->Parameter(ActTest_StubANode::PID_TFunc);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_2) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_1) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_2) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_2) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_3) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_2_copy) );  

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasObservers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_3).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasObservers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_2).HasObservers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_3).HasObservers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasObservers() );

  return true;
}

//! See case 3.4 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithReferencesToPlain_4(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithReferencesToPlain_4");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* =====================================
   *  Establish Tree Function connections
   * ===================================== */

  M->OpenCommand();

  B_3->ConnectTreeFunction( ActTest_StubBNode::PID_TFunc,
                            ActTest_DummyTreeFunction::GUID(),
                            ActAPI_ParameterStream() << A_2->Parameter(ActTest_StubANode::PID_Real),
                            ActAPI_ParameterStream() << A_3->Parameter(ActTest_StubANode::PID_Real) );

  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==================================================
   *  Verify that the source references is still there
   * ================================================== */

  Handle(ActAPI_IUserParameter) B_3_TFunc = B_3->Parameter(ActTest_StubBNode::PID_TFunc);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(A_1) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(B_3) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsInputReaderFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(A_2) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(B_3) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(B_3_TFunc).IsOutputWriterFor(B_2_copy) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasObservers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_2).HasObservers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_3).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_3).HasObservers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasObservers() );

  return true;
}

//! See case 3.5 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithReferencesToPlain_5(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithReferencesToPlain_5");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* =====================================
   *  Establish Tree Function connections
   * ===================================== */

  M->OpenCommand();

  A_2->ConnectTreeFunction( ActTest_StubANode::PID_TFunc,
                            ActTest_DummyTreeFunction::GUID(),
                            ActAPI_ParameterStream() << A_2->Parameter(ActTest_StubANode::PID_DummyShapeA),
                            ActAPI_ParameterStream() << A_2->Parameter(ActTest_StubANode::PID_Real) );

  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ===================================================
   *  Verify that the source references are still there
   * =================================================== */

  Handle(ActAPI_IUserParameter) A_2_TFunc = A_2->Parameter(ActTest_StubANode::PID_TFunc);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_3) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsInputReaderFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_3) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_TFunc).IsOutputWriterFor(B_2_copy) );

  /* ==========================
   *  Verify copied references
   * ========================== */

  Handle(ActAPI_IUserParameter) A_2_copy_TFunc = A_2_copy->Parameter(ActTest_StubANode::PID_TFunc);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_3) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsInputReaderFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_3) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_TFunc).IsOutputWriterFor(B_2_copy) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_3).HasObservers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasObservers() );

  /* ===================
   *  Nano Verification
   * =================== */

  ACT_VERIFY( ReferenceValidator::TreeFunction(A_2_TFunc).HasAsArgument( A_2->Parameter(ActTest_StubANode::PID_DummyShapeA) ) );
  ACT_VERIFY( ReferenceValidator::TreeFunction(A_2_TFunc).HasAsResult( A_2->Parameter(ActTest_StubANode::PID_Real) ) );

  ACT_VERIFY( ReferenceValidator::TreeFunction(A_2_copy_TFunc).HasAsArgument( A_2_copy->Parameter(ActTest_StubANode::PID_DummyShapeA) ) );
  ACT_VERIFY( ReferenceValidator::TreeFunction(A_2_copy_TFunc).HasAsResult( A_2_copy->Parameter(ActTest_StubANode::PID_Real) ) );

  return true;
}

//! See case 4 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithEvalReferencesToPlain(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithEvalReferencesToPlain");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  Handle(ActAPI_INode) VAR_1 = M->FindNode( VARNodeIDs(1) );
  Handle(ActAPI_INode) VAR_2 = M->FindNode( VARNodeIDs(2) );

  Handle(ActData_RealParameter) VAR_1P =
    Handle(ActData_RealParameter)::DownCast( VAR_1->Parameter(ActData_RealVarNode::Param_Value) );
  Handle(ActData_RealParameter) VAR_2P =
    Handle(ActData_RealParameter)::DownCast( VAR_2->Parameter(ActData_RealVarNode::Param_Value) );

  /* ===============================
   *  Connect evaluator to A_2 Node
   * =============================== */

  M->OpenCommand();

  A_2->ConnectEvaluator(ActTest_StubANode::PID_Real,
                        ActAPI_ParameterStream() << VAR_1P << VAR_2P);

  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* ====================================================================
   *  Register Real Evaluator as Tree Function passing out-scoped filter
   * ==================================================================== */

  tool->AccessReferenceFilter().AccessTreeFunctionFilter().PassOutScoped( ActData_RealEvaluatorFunc::GUID() );

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ================================================
   *  Verify that the copied reference is consistent
   * ================================================ */

  Handle(ActAPI_IUserParameter) A_2_copy_Eval = A_2_copy->Evaluator(ActTest_StubANode::PID_Real);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(B_3) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(VAR_1) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(VAR_2) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsInputReaderFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(B_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(VAR_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(VAR_2) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_copy_Eval).IsOutputWriterFor(B_2_copy) );

  /* =================================================
   *  Verify that the source reference is still there
   * ================================================= */

  Handle(ActAPI_IUserParameter) A_2_Eval = A_2->Evaluator(ActTest_StubANode::PID_Real);

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(B_3) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(VAR_1) );
  ACT_VERIFY(  ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(VAR_2) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsInputReaderFor(B_2_copy) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(A_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(A_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(A_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(B_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(B_2) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(B_3) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(VAR_1) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(VAR_2) );

  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(A_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(A_2_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(B_1_copy) );
  ACT_VERIFY( !ReferenceValidator::TreeFunction(A_2_Eval).IsOutputWriterFor(B_2_copy) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_3).HasObservers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasObservers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasObservers() );

  ACT_VERIFY( ReferenceValidator::Node(VAR_1).HasObservers() );
  ACT_VERIFY( ReferenceValidator::Node(VAR_2).HasObservers() );

  ACT_VERIFY( ReferenceValidator::Node(VAR_1).InputReadersAre(ActAPI_ParameterStream() << A_2_Eval << A_2_copy_Eval) );
  ACT_VERIFY( ReferenceValidator::Node(VAR_2).InputReadersAre(ActAPI_ParameterStream() << A_2_Eval << A_2_copy_Eval) );

  return true;
}

//! See case 5.1 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithPlainReferenceToPlain_1(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithPlainReferenceToPlain_1");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* ======================================
   *  Establish plain Reference connection
   * ====================================== */

  M->OpenCommand();
  B_2->ConnectReference(ActTest_StubBNode::PID_Ref, A_2);
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==============================
   *  Verify the copied references
   * ============================== */

  Handle(ActAPI_IUserParameter) B_2_copy_Ref = B_2_copy->Parameter(ActTest_StubBNode::PID_Ref);

  ACT_VERIFY( ReferenceValidator::Reference(B_2_copy_Ref).TargetIs(A_2_copy) );

  /* =================================================
   *  Verify that the source reference is still there
   * ================================================= */

  Handle(ActAPI_IUserParameter) B_2_Ref = B_2->Parameter(ActTest_StubBNode::PID_Ref);

  ACT_VERIFY( ReferenceValidator::Reference(B_2_Ref).TargetIs(A_2) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_2).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_3).HasReferrers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_2_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasReferrers() );

  ACT_VERIFY( ReferenceValidator::Node(A_2).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref) );
  ACT_VERIFY( ReferenceValidator::Node(A_2_copy).ReferrersAre(ActAPI_ParameterStream() << B_2_copy_Ref) );

  return true;
}

//! See case 5.2 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithPlainReferenceToPlain_2(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithPlainReferenceToPlain_2");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* ======================================
   *  Establish plain Reference connection
   * ====================================== */

  M->OpenCommand();
  B_2->ConnectReference(ActTest_StubBNode::PID_Ref, B_3);
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==============================
   *  Verify the copied references
   * ============================== */

  Handle(ActAPI_IUserParameter) B_2_copy_Ref = B_2_copy->Parameter(ActTest_StubBNode::PID_Ref);

  ACT_VERIFY( ActData_ParameterFactory::AsReference(B_2_copy_Ref)->GetTarget().IsNull() );

  /* =================================================
   *  Verify that the source reference is still there
   * ================================================= */

  Handle(ActAPI_IUserParameter) B_2_Ref = B_2->Parameter(ActTest_StubBNode::PID_Ref);

  ACT_VERIFY( ReferenceValidator::Reference(B_2_Ref).TargetIs(B_3) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_3).HasReferrers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasReferrers() );

  ACT_VERIFY( ReferenceValidator::Node(B_3).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref) );

  return true;
}

//! See case 5.3 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithPlainReferenceToPlain_3(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithPlainReferenceToPlain_3");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* ======================================
   *  Establish plain Reference connection
   * ====================================== */

  M->OpenCommand();
  B_2->ConnectReference(ActTest_StubBNode::PID_Ref, B_3);
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* ==========================================================
   *  Configure Reference Filter to allow out-scoped Reference
   * ========================================================== */

  tool->AccessReferenceFilter().AccessRefParamFilter()
         .PassOutScoped(B_2->GetTypeName(), ActTest_StubBNode::PID_Ref);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==============================
   *  Verify the copied references
   * ============================== */

  Handle(ActAPI_IUserParameter) B_2_copy_Ref = B_2_copy->Parameter(ActTest_StubBNode::PID_Ref);

  ACT_VERIFY( ReferenceValidator::Reference(B_2_copy_Ref).TargetIs(B_3) );

  /* =================================================
   *  Verify that the source reference is still there
   * ================================================= */

  Handle(ActAPI_IUserParameter) B_2_Ref = B_2->Parameter(ActTest_StubBNode::PID_Ref);

  ACT_VERIFY( ReferenceValidator::Reference(B_2_Ref).TargetIs(B_3) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_3).HasReferrers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasReferrers() );

  ACT_VERIFY( ReferenceValidator::Node(B_3).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref << B_2_copy_Ref) );

  return true;
}

//! See case 5.4 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithPlainReferenceToPlain_4(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithPlainReferenceToPlain_4");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* ======================================
   *  Establish plain Reference connection
   * ====================================== */

  M->OpenCommand();
  B_2->ConnectReference(ActTest_StubBNode::PID_Ref, B_3);
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* ==========================================================
   *  Configure Reference Filter to allow out-scoped Reference
   * ========================================================== */

  tool->AccessReferenceFilter().AccessRefParamFilter()
         .PassOutScoped(B_2->GetTypeName(), ActTest_StubBNode::PID_Ref);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==============================
   *  Verify the copied references
   * ============================== */

  Handle(ActAPI_IUserParameter) B_2_copy_Ref = B_2_copy->Parameter(ActTest_StubBNode::PID_Ref);

  ACT_VERIFY( ReferenceValidator::Reference(B_2_copy_Ref).TargetIs(B_3) );

  /* ==================================
   *  Copy A_1_copy sub-tree to buffer
   * ================================== */

  M->OpenCommand();
  isOk = tool->TransferToBuffer(A_1_copy);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgressNC = dumpPath().Cat(fn_name).Cat("_progress_nextcopy").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgressNC, M);

  ActData_CopyPasteEngine::RelocationTable Dbl_COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* =======================================
   *  Restore A_1_copy sub-tree from buffer
   * ======================================= */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceDblCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceDblCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfterNC = dumpPath().Cat(fn_name).Cat("_after_nextcopy").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterNC, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTNNC = dumpPath().Cat(fn_name).Cat("_after_TN_nextcopy").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTNNC, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable Dbl_PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy_copy = ActData_NodeFactory::NodeSettle( Dbl_PASTE_Reloc.Find1( Dbl_COPY_Reloc.Find1( A_1_copy->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy_copy = ActData_NodeFactory::NodeSettle( Dbl_PASTE_Reloc.Find1( Dbl_COPY_Reloc.Find1( A_2_copy->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy_copy = ActData_NodeFactory::NodeSettle( Dbl_PASTE_Reloc.Find1( Dbl_COPY_Reloc.Find1( A_3_copy->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy_copy = ActData_NodeFactory::NodeSettle( Dbl_PASTE_Reloc.Find1( Dbl_COPY_Reloc.Find1( B_1_copy->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy_copy = ActData_NodeFactory::NodeSettle( Dbl_PASTE_Reloc.Find1( Dbl_COPY_Reloc.Find1( B_2_copy->RootLabel() ) ) );

  /* ==============================
   *  Verify the copied references
   * ============================== */

  Handle(ActAPI_IUserParameter) B_2_copy_copy_Ref = B_2_copy_copy->Parameter(ActTest_StubBNode::PID_Ref);

  ACT_VERIFY( ReferenceValidator::Reference(B_2_copy_copy_Ref).TargetIs(B_3) );

  /* =================================================
   *  Verify that the source reference is still there
   * ================================================= */

  Handle(ActAPI_IUserParameter) B_2_Ref = B_2->Parameter(ActTest_StubBNode::PID_Ref);

  ACT_VERIFY( ReferenceValidator::Reference(B_2_Ref).TargetIs(B_3) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_3).HasReferrers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasReferrers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy_copy).HasReferrers() );

  ACT_VERIFY( ReferenceValidator::Node(B_3).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref << B_2_copy_Ref << B_2_copy_copy_Ref) );

  return true;
}

//! See case 6.1 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithListReferenceToPlain_1(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithListReferenceToPlain_1");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* =====================================
   *  Establish Reference List connection
   * ===================================== */

  M->OpenCommand();
  B_2->ConnectReferenceToList(ActTest_StubBNode::PID_RefList, A_2);
  B_2->ConnectReferenceToList(ActTest_StubBNode::PID_RefList, A_3);
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==============================
   *  Verify the copied references
   * ============================== */

  Handle(ActAPI_IUserParameter) B_2_copy_Ref = B_2_copy->Parameter(ActTest_StubBNode::PID_RefList);

  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_copy_Ref).HasTarget(A_2_copy) );
  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_copy_Ref).HasTarget(A_3_copy) );

  /* =================================================
   *  Verify that the source reference is still there
   * ================================================= */

  Handle(ActAPI_IUserParameter) B_2_Ref = B_2->Parameter(ActTest_StubBNode::PID_RefList);

  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_Ref).HasTarget(A_2) );
  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_Ref).HasTarget(A_3) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_2).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_4).HasReferrers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_2_copy).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_3_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasReferrers() );

  ACT_VERIFY( ReferenceValidator::Node(A_2).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref) );
  ACT_VERIFY( ReferenceValidator::Node(A_3).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref) );
  ACT_VERIFY( ReferenceValidator::Node(A_2_copy).ReferrersAre(ActAPI_ParameterStream() << B_2_copy_Ref) );
  ACT_VERIFY( ReferenceValidator::Node(A_3_copy).ReferrersAre(ActAPI_ParameterStream() << B_2_copy_Ref) );

  return true;
}

//! See case 6.2 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithListReferenceToPlain_2(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithListReferenceToPlain_2");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* =====================================
   *  Establish Reference List connection
   * ===================================== */

  M->OpenCommand();
  B_2->ConnectReferenceToList(ActTest_StubBNode::PID_RefList, B_3);
  B_2->ConnectReferenceToList(ActTest_StubBNode::PID_RefList, B_4);
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==============================
   *  Verify the copied references
   * ============================== */

  Handle(ActAPI_IUserParameter) B_2_copy_Ref = B_2_copy->Parameter(ActTest_StubBNode::PID_RefList);

  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_copy_Ref).IsEmpty() );

  /* =================================================
   *  Verify that the source reference is still there
   * ================================================= */

  Handle(ActAPI_IUserParameter) B_2_Ref = B_2->Parameter(ActTest_StubBNode::PID_RefList);

  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_Ref).HasTarget(B_3) );
  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_Ref).HasTarget(B_4) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_3).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_4).HasReferrers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_3_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasReferrers() );

  ACT_VERIFY( ReferenceValidator::Node(B_3).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref) );
  ACT_VERIFY( ReferenceValidator::Node(B_4).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref) );

  return true;
}

//! See case 6.3 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithListReferenceToPlain_3(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithListReferenceToPlain_3");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* =====================================
   *  Establish Reference List connection
   * ===================================== */

  M->OpenCommand();
  B_2->ConnectReferenceToList(ActTest_StubBNode::PID_RefList, B_3);
  B_2->ConnectReferenceToList(ActTest_StubBNode::PID_RefList, A_3);
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==============================
   *  Verify the copied references
   * ============================== */

  Handle(ActAPI_IUserParameter) B_2_copy_Ref = B_2_copy->Parameter(ActTest_StubBNode::PID_RefList);

  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_copy_Ref).HasTarget(A_3_copy) );
  ACT_VERIFY( !ReferenceValidator::ReferenceList(B_2_copy_Ref).HasTarget(B_3) );

  /* =================================================
   *  Verify that the source reference is still there
   * ================================================= */

  Handle(ActAPI_IUserParameter) B_2_Ref = B_2->Parameter(ActTest_StubBNode::PID_RefList);

  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_Ref).HasTarget(B_3) );
  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_Ref).HasTarget(A_3) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_4).HasReferrers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_3_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasReferrers() );

  ACT_VERIFY( ReferenceValidator::Node(B_3).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref) );
  ACT_VERIFY( ReferenceValidator::Node(A_3).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref) );
  ACT_VERIFY( ReferenceValidator::Node(A_3_copy).ReferrersAre(ActAPI_ParameterStream() << B_2_copy_Ref) );

  return true;
}

//! See case 6.4 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_TreeWithListReferenceToPlain_4(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_TreeWithListReferenceToPlain_4");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ======================
   *  Prepare initial data
   * ====================== */

  ActAPI_DataObjectIdList ANodeIDs, BNodeIDs, VARNodeIDs;
  populateSampleTree(M, ANodeIDs, BNodeIDs, VARNodeIDs);

  Handle(ActAPI_INode) A   = M->FindNode( ANodeIDs(1) );
  Handle(ActAPI_INode) A_1 = M->FindNode( ANodeIDs(2) );
  Handle(ActAPI_INode) A_2 = M->FindNode( ANodeIDs(3) );
  Handle(ActAPI_INode) A_3 = M->FindNode( ANodeIDs(4) );

  Handle(ActAPI_INode) B_1 = M->FindNode( BNodeIDs(1) );
  Handle(ActAPI_INode) B_2 = M->FindNode( BNodeIDs(2) );
  Handle(ActAPI_INode) B_3 = M->FindNode( BNodeIDs(3) );
  Handle(ActAPI_INode) B_4 = M->FindNode( BNodeIDs(4) );

  /* =====================================
   *  Establish Reference List connection
   * ===================================== */

  M->OpenCommand();
  B_2->ConnectReferenceToList(ActTest_StubBNode::PID_RefList, B_3);
  B_2->ConnectReferenceToList(ActTest_StubBNode::PID_RefList, A_3);
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  /* ============================
   *  Configure Reference Filter
   * ============================ */

  tool->AccessReferenceFilter()
         .AccessRefParamFilter()
         .PassOutScoped(B_3->GetTypeName(), ActTest_StubBNode::PID_RefList);

  /* =============================
   *  Copy A_1 sub-tree to buffer
   * ============================= */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(A_1);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  ActData_CopyPasteEngine::RelocationTable COPY_Reloc = tool->GetRelocationTable(Standard_True);

  /* ==================================
   *  Restore A_1 sub-tree from buffer
   * ================================== */

  M->OpenCommand();
  Handle(ActAPI_INode) aSourceCopy = tool->RestoreFromBuffer();
  B_4->AddChildNode(aSourceCopy);
  M->CommitCommand();

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureNodesOnly);

  ActData_CopyPasteEngine::RelocationTable PASTE_Reloc = tool->GetRelocationTable(Standard_False);

  /* =============================
   *  Access all resulting copies
   * ============================= */

  Handle(ActAPI_INode) A_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_1->RootLabel() ) ) );
  Handle(ActAPI_INode) A_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_2->RootLabel() ) ) );
  Handle(ActAPI_INode) A_3_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( A_3->RootLabel() ) ) );

  Handle(ActAPI_INode) B_1_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_1->RootLabel() ) ) );
  Handle(ActAPI_INode) B_2_copy = ActData_NodeFactory::NodeSettle( PASTE_Reloc.Find1( COPY_Reloc.Find1( B_2->RootLabel() ) ) );

  /* ==============================
   *  Verify the copied references
   * ============================== */

  Handle(ActAPI_IUserParameter) B_2_copy_Ref = B_2_copy->Parameter(ActTest_StubBNode::PID_RefList);

  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_copy_Ref).HasTarget(B_3) );
  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_copy_Ref).HasTarget(A_3_copy) );

  /* =================================================
   *  Verify that the source reference is still there
   * ================================================= */

  Handle(ActAPI_IUserParameter) B_2_Ref = B_2->Parameter(ActTest_StubBNode::PID_RefList);

  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_Ref).HasTarget(B_3) );
  ACT_VERIFY( ReferenceValidator::ReferenceList(B_2_Ref).HasTarget(A_3) );

  /* =====================================
   *  Verification from Nodal perspective
   * ===================================== */

  ACT_VERIFY( !ReferenceValidator::Node(A_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(B_3).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_4).HasReferrers() );

  ACT_VERIFY( !ReferenceValidator::Node(A_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(A_2_copy).HasReferrers() );
  ACT_VERIFY(  ReferenceValidator::Node(A_3_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_1_copy).HasReferrers() );
  ACT_VERIFY( !ReferenceValidator::Node(B_2_copy).HasReferrers() );

  ACT_VERIFY( ReferenceValidator::Node(B_3).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref << B_2_copy_Ref) );
  ACT_VERIFY( ReferenceValidator::Node(A_3).ReferrersAre(ActAPI_ParameterStream() << B_2_Ref) );
  ACT_VERIFY( ReferenceValidator::Node(A_3_copy).ReferrersAre(ActAPI_ParameterStream() << B_2_copy_Ref) );

  return true;
}

//! See case 7 in UNIT-TESTING section of reference documentation.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_PlainMeshToPlain(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_PlainMeshToPlain");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ===================================
   *  Prepare initial data to be copied
   * =================================== */

  ACT_VERIFY( M->NewEmpty() );

  // Prepare detached data
  Handle(ActTest_StubMeshNode) MESH = Handle(ActTest_StubMeshNode)::DownCast( ActTest_StubMeshNode::Instance() );
  Handle(ActTest_StubANode) A = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() );
  TopoDS_Shape aTargetShapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() };
  Standard_Real aTargetRealVal = ActTestLib_Common::RandomReal();

  // Attach data to the CAF Document
  M->OpenCommand();
  M->StubAPartition()->AddNode(A); // This will be a ROOT Node
  M->StubMeshPartition()->AddNode(MESH);
  A->SetName("Parent A");
  A->Init(aTargetShapes[0], aTargetShapes[1], aTargetRealVal);
  MESH->SetName("Mesh Node");
  MESH->Init(new ActData_Mesh);
  ACT_VERIFY( A->IsWellFormed() );
  ACT_VERIFY( MESH->IsWellFormed() );
  M->CommitCommand();

  // Prepare simple test mesh
  M->OpenCommand();
  Handle(ActData_MeshParameter)
    MESH_P = ActData_ParameterFactory::AsMesh( MESH->Parameter(ActTest_StubMeshNode::Param_Mesh) );
  Standard_Integer NODES[] = { MESH_P->AddNode(0, 0, 0),
                               MESH_P->AddNode(0, 0, 1),
                               MESH_P->AddNode(0, 1, 0) };
  MESH_P->AddElement(NODES, 3);
  M->CommitCommand();

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  /* ==============
   *  Perform Copy
   * ============== */

  M->OpenCommand();
  Standard_Boolean isOk = tool->TransferToBuffer(MESH);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  /* ===============
   *  Perform Paste
   * =============== */

  M->OpenCommand();
  Handle(ActAPI_INode) MESH_COPY = tool->RestoreFromBuffer();
  A->AddChildNode(MESH_COPY);
  M->CommitCommand();

  ACT_VERIFY( !MESH_COPY.IsNull() );
  ACT_VERIFY( MESH_COPY->IsWellFormed() );

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  /* ======================
   *  Perform verification
   * ====================== */

  Handle(ActTest_StubMeshNode) MESH_COPY_STUB = Handle(ActTest_StubMeshNode)::DownCast(MESH_COPY);

  Handle(ActData_MeshParameter)
    MESH_COPY_P = ActData_ParameterFactory::AsMesh( MESH->Parameter(ActTest_StubMeshNode::Param_Mesh) );

  Handle(ActData_Mesh) aMeshDS_Copy = MESH_COPY_P->GetMesh();

  for ( Standard_Integer k = 0; k < 3; k++ )
  {
    ACT_VERIFY( aMeshDS_Copy->FindNode(NODES[k])->X() == MESH_P->GetMesh()->FindNode(NODES[k])->X() );
    ACT_VERIFY( aMeshDS_Copy->FindNode(NODES[k])->Y() == MESH_P->GetMesh()->FindNode(NODES[k])->Y() );
    ACT_VERIFY( aMeshDS_Copy->FindNode(NODES[k])->Z() == MESH_P->GetMesh()->FindNode(NODES[k])->Z() );
  }

  return true;
}

//! Attempts to paste simple Node having Tree Function Parameter with
//! outdated argument. This can happen if the problematic argument has
//! been deleted between Copy & Paste invocations.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_PasteWithDEAD_DFunctionArgument(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_PasteWithDEAD_DFunctionArgument");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ===================================
   *  Prepare initial data to be copied
   * =================================== */

  ACT_VERIFY( M->NewEmpty() );

  // Prepare detached data for root
  Handle(ActTest_StubANode) ROOT = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() );
  TopoDS_Shape aROOTShapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() };
  Standard_Real aROOTRealVal = ActTestLib_Common::RandomReal();

  // Prepare detached data to be copied
  Handle(ActTest_StubANode) A = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() );
  TopoDS_Shape aTargetShapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() };
  Standard_Real aTargetRealVal = ActTestLib_Common::RandomReal();

  // Prepare detached data to be used as Function arguments
  Handle(ActTest_StubBNode) B = Handle(ActTest_StubBNode)::DownCast( ActTest_StubBNode::Instance() );
  Standard_Integer aBIntVal = ActTestLib_Common::RandomInteger();
  Standard_Real aBRealVal = ActTestLib_Common::RandomReal();
  
  // Push data to the CAF Document
  {
    M->OpenCommand();

    M->StubAPartition()->AddNode(ROOT); // This will be a ROOT Node
    M->StubAPartition()->AddNode(A);
    M->StubBPartition()->AddNode(B);

    ROOT->SetName("ROOT A");
    A->SetName("Target A");
    B->SetName("Input B");

    ROOT->Init(aROOTShapes[0], aROOTShapes[1], aROOTRealVal);
    A->Init(aTargetShapes[0], aTargetShapes[1], aTargetRealVal);
    B->Init(aBIntVal, aBRealVal);

    ACT_VERIFY( ROOT->IsWellFormed() );
    ACT_VERIFY( A->IsWellFormed() );
    ACT_VERIFY( B->IsWellFormed() );

    ROOT->AddChildNode(A);
    ROOT->AddChildNode(B);

    A->ConnectTreeFunction( ActTest_StubANode::PID_TFunc, ActTest_DummyTreeFunction::GUID(),
                            ActAPI_ParameterStream() << B->Parameter(ActTest_StubBNode::PID_Real),
                            ActAPI_ParameterStream() << A->Parameter(ActTest_StubANode::PID_Real) );

    M->CommitCommand();
  }

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  /* =============================================================
   *  Set up filtering strategy for out-scoped A <-> B connection
   * ============================================================= */

  M->LoadCopyFuncGUIDs( ActAPI_FuncGUIDStream() << ActTest_DummyTreeFunction::GUID() );

  /* ==============
   *  Perform Copy
   * ============== */

  M->OpenCommand();
  Standard_Boolean isOk = M->CopyNode(A);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  /* ================================================================
   *  Delete Node A and then Node B in order to have DEAD references
   *  in the Copy/Paste buffer
   * ================================================================ */

   M->OpenCommand();
   ACT_VERIFY( M->DeleteNode(A) );
   ACT_VERIFY( M->DeleteNode(B) );
   M->CommitCommand();

   // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgressDel = dumpPath().Cat(fn_name).Cat("_progress_del").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgressDel, M);

  /* ===============
   *  Perform Paste
   * =============== */

  M->OpenCommand();
  Handle(ActAPI_INode) A_COPY = M->PasteAsChild(ROOT);
  M->CommitCommand();

  // Some very preliminary verifications which assure us that pasting has
  // been really performed
  ACT_VERIFY( !A_COPY.IsNull() );
  ACT_VERIFY( A_COPY->IsWellFormed() );

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  /* ======================
   *  Perform verification
   * ====================== */

  Standard_Integer PasteStatus = M->CopyPasteEngine()->Status();

  ACT_VERIFY(PasteStatus & ActData_CopyPasteEngine::Status_WarnNullFuncArgument);
  ACT_VERIFY( A_COPY->IsValidData() );

  return true;
}

//! Attempts to paste simple Node having Tree Function Parameter with
//! outdated result. This can happen if the problematic result has
//! been deleted between Copy & Paste invocations.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_PasteWithDEAD_DFunctionResult(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_PasteWithDEAD_DFunctionResult");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ===================================
   *  Prepare initial data to be copied
   * =================================== */

  ACT_VERIFY( M->NewEmpty() );

  // Prepare detached data for root
  Handle(ActTest_StubANode) ROOT = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() );
  TopoDS_Shape aROOTShapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() };
  Standard_Real aROOTRealVal = ActTestLib_Common::RandomReal();

  // Prepare detached data to be copied
  Handle(ActTest_StubANode) A = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() );
  TopoDS_Shape aTargetShapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() };
  Standard_Real aTargetRealVal = ActTestLib_Common::RandomReal();

  // Prepare detached data to be used as Function arguments
  Handle(ActTest_StubBNode) B = Handle(ActTest_StubBNode)::DownCast( ActTest_StubBNode::Instance() );
  Standard_Integer aBIntVal = ActTestLib_Common::RandomInteger();
  Standard_Real aBRealVal = ActTestLib_Common::RandomReal();

  // Push data to the CAF Document
  {
    M->OpenCommand();

    M->StubAPartition()->AddNode(ROOT); // This will be a ROOT Node
    M->StubAPartition()->AddNode(A);
    M->StubBPartition()->AddNode(B);

    ROOT->SetName("ROOT A");
    A->SetName("Target A");
    B->SetName("Input B");

    ROOT->Init(aROOTShapes[0], aROOTShapes[1], aROOTRealVal);
    A->Init(aTargetShapes[0], aTargetShapes[1], aTargetRealVal);
    B->Init(aBIntVal, aBRealVal);

    ACT_VERIFY( ROOT->IsWellFormed() );
    ACT_VERIFY( A->IsWellFormed() );
    ACT_VERIFY( B->IsWellFormed() );

    ROOT->AddChildNode(A);
    ROOT->AddChildNode(B);

    A->ConnectTreeFunction( ActTest_StubANode::PID_TFunc, ActTest_DummyTreeFunction::GUID(),
                            ActAPI_ParameterStream() << A->Parameter(ActTest_StubANode::PID_Real),
                            ActAPI_ParameterStream() << B->Parameter(ActTest_StubBNode::PID_Real) );

    M->CommitCommand();
  }

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  /* =============================================================
   *  Set up filtering strategy for out-scoped A <-> B connection
   * ============================================================= */

  M->LoadCopyFuncGUIDs( ActAPI_FuncGUIDStream() << ActTest_DummyTreeFunction::GUID() );

  /* ==============
   *  Perform Copy
   * ============== */

  M->OpenCommand();
  Standard_Boolean isOk = M->CopyNode(A);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  /* ================================================================
   *  Delete Node A and then Node B in order to have DEAD references
   *  in the Copy/Paste buffer
   * ================================================================ */

   M->OpenCommand();
   ACT_VERIFY( M->DeleteNode(A) );
   ACT_VERIFY( M->DeleteNode(B) );
   M->CommitCommand();

   // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgressDel = dumpPath().Cat(fn_name).Cat("_progress_del").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgressDel, M);

  /* ===============
   *  Perform Paste
   * =============== */

  M->OpenCommand();
  Handle(ActAPI_INode) A_COPY = M->PasteAsChild(ROOT);
  M->CommitCommand();

  // Some very preliminary verifications which assure us that pasting has
  // been really performed
  ACT_VERIFY( !A_COPY.IsNull() );
  ACT_VERIFY( A_COPY->IsWellFormed() );

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  /* ======================
   *  Perform verification
   * ====================== */

  Standard_Integer PasteStatus = M->CopyPasteEngine()->Status();

  ACT_VERIFY(PasteStatus & ActData_CopyPasteEngine::Status_WarnNullFuncResult);
  ACT_VERIFY( A_COPY->IsValidData() );

  return true;
}

//! Attempts to paste simple Node having Reference Parameter with
//! outdated target. This can happen if the problematic target has
//! been deleted between Copy & Paste invocations.
//! \param funcID [in] ID of test function.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::testCopyPaste_PasteWithDEADReference(const int ActTestLib_NotUsed(funcID))
{
  TCollection_AsciiString fn_name("testCopyPaste_PasteWithDEADReference");
  Handle(ActTest_DummyModel) M = new ActTest_DummyModel;
  Handle(ActData_CopyPasteEngine) tool = new ActData_CopyPasteEngine(M);

  /* ===================================
   *  Prepare initial data to be copied
   * =================================== */

  ACT_VERIFY( M->NewEmpty() );

  // Prepare detached data for root
  Handle(ActTest_StubANode) ROOT = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() );
  TopoDS_Shape aROOTShapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() };
  Standard_Real aROOTRealVal = ActTestLib_Common::RandomReal();

  // Prepare detached data to be copied
  Handle(ActTest_StubANode) A = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() );
  TopoDS_Shape aTargetShapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() };
  Standard_Real aTargetRealVal = ActTestLib_Common::RandomReal();

  // Prepare detached data to be used as Function arguments
  Handle(ActTest_StubBNode) B = Handle(ActTest_StubBNode)::DownCast( ActTest_StubBNode::Instance() );
  Standard_Integer aBIntVal = ActTestLib_Common::RandomInteger();
  Standard_Real aBRealVal = ActTestLib_Common::RandomReal();

  // Push data to the CAF Document
  {
    M->OpenCommand();

    M->StubAPartition()->AddNode(ROOT); // This will be a ROOT Node
    M->StubAPartition()->AddNode(A);
    M->StubBPartition()->AddNode(B);

    ROOT->SetName("ROOT A");
    A->SetName("Target A");
    B->SetName("Input B");

    ROOT->Init(aROOTShapes[0], aROOTShapes[1], aROOTRealVal);
    A->Init(aTargetShapes[0], aTargetShapes[1], aTargetRealVal);
    B->Init(aBIntVal, aBRealVal);

    ACT_VERIFY( ROOT->IsWellFormed() );
    ACT_VERIFY( A->IsWellFormed() );
    ACT_VERIFY( B->IsWellFormed() );

    ROOT->AddChildNode(A);
    ROOT->AddChildNode(B);

    A->ConnectReference(ActTest_StubANode::PID_Ref, B);

    M->CommitCommand();
  }

  // Dump the Model before modifications
  TCollection_AsciiString
    aFilenameBefore = dumpPath().Cat(fn_name).Cat("_before").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBefore, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameBeforeTN = dumpPath().Cat(fn_name).Cat("_before_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameBeforeTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  /* =============================================================
   *  Set up filtering strategy for out-scoped A <-> B connection
   * ============================================================= */

  M->CopyPasteEngine()->AccessReferenceFilter()
                             .AccessRefParamFilter()
                             .PassOutScoped(A->GetTypeName(), ActTest_StubANode::PID_Ref);

  /* ==============
   *  Perform Copy
   * ============== */

  M->OpenCommand();
  Standard_Boolean isOk = M->CopyNode(A);
  M->CommitCommand();

  ACT_VERIFY(isOk);

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgress = dumpPath().Cat(fn_name).Cat("_progress").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgress, M);

  /* ================================================================
   *  Delete Node A and then Node B in order to have DEAD references
   *  in the Copy/Paste buffer
   * ================================================================ */

   M->OpenCommand();
   ACT_VERIFY( M->DeleteNode(A) );
   ACT_VERIFY( M->DeleteNode(B) );
   M->CommitCommand();

  // Dump the Model just after the copying
  TCollection_AsciiString
    aFilenameProgressDel = dumpPath().Cat(fn_name).Cat("_progress_del").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameProgressDel, M);

  /* ===============
   *  Perform Paste
   * =============== */

  M->OpenCommand();
  Handle(ActAPI_INode) A_COPY = M->PasteAsChild(ROOT);
  M->CommitCommand();

  // Some very preliminary verifications which assure us that pasting has
  // been really performed
  ACT_VERIFY( !A_COPY.IsNull() );
  ACT_VERIFY( A_COPY->IsWellFormed() );

  // Dump the Model just after the pasting
  TCollection_AsciiString
    aFilenameAfter = dumpPath().Cat(fn_name).Cat("_after").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfter, M);

  // Dump the Model in Tree Node mode
  TCollection_AsciiString
    aFilenameAfterTN = dumpPath().Cat(fn_name).Cat("_after_TN").Cat(".dump");
  ActData_CAFDumper::Dump(aFilenameAfterTN, M,
                          ActData_CAFDumper::Content_TreeNodes,
                          ActData_CAFDumper::Verbosity_StructureOnly);

  /* ======================
   *  Perform verification
   * ====================== */

  Standard_Integer PasteStatus = M->CopyPasteEngine()->Status();

  ACT_VERIFY(PasteStatus & ActData_CopyPasteEngine::Status_NoError);
  ACT_VERIFY( A_COPY->IsValidData() );
  ACT_VERIFY( ActData_ParameterFactory::AsReference( A->Parameter(ActTest_StubANode::PID_Ref) )->GetTarget().IsNull() );

  return true;
}

//-----------------------------------------------------------------------------
// Auxiliary functions
//-----------------------------------------------------------------------------

//! Prepares non-trivial initial data for Copy/Paste functionality testing.
//! \param M [in] sample Model.
//! \param ANodeIDs [out] collection of Nodal IDs for Data Nodes of type A.
//! \param BNodeIDs [out] collection of Nodal IDs for Data Nodes of type B.
//! \param VARNodeIDs [out] collection of Nodal IDs for REAL Variable Nodes.
//! \return true if test is passed, false -- otherwise.
bool ActTest_CopyPasteEngine::populateSampleTree(const Handle(ActTest_DummyModel)& M,
                                                 ActAPI_DataObjectIdList& ANodeIDs,
                                                 ActAPI_DataObjectIdList& BNodeIDs,
                                                 ActAPI_DataObjectIdList& VARNodeIDs)
{
  ACT_VERIFY( M->NewEmpty() );

  // Prepare detached A Nodes
  Handle(ActTest_StubANode) A   = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() ),
                            A_1 = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() ),
                            A_2 = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() ),
                            A_3 = Handle(ActTest_StubANode)::DownCast( ActTest_StubANode::Instance() );

  // Prepare detached B Nodes
  Handle(ActTest_StubBNode) B_1 = Handle(ActTest_StubBNode)::DownCast( ActTest_StubBNode::Instance() ),
                            B_2 = Handle(ActTest_StubBNode)::DownCast( ActTest_StubBNode::Instance() ),
                            B_3 = Handle(ActTest_StubBNode)::DownCast( ActTest_StubBNode::Instance() ),
                            B_4 = Handle(ActTest_StubBNode)::DownCast( ActTest_StubBNode::Instance() );

  // Prepare VARIABLE Nodes
  Handle(ActData_RealVarNode) VAR_1 = Handle(ActData_RealVarNode)::DownCast( ActData_RealVarNode::Instance() ),
                              VAR_2 = Handle(ActData_RealVarNode)::DownCast( ActData_RealVarNode::Instance() );

  // Prepare data to initialize the involved A Nodes
  TopoDS_Shape A_Shapes[]   = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() },
               A_1_Shapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() },
               A_2_Shapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() },
               A_3_Shapes[] = { ActTestLib_Common::RandomShape(), ActTestLib_Common::RandomShape() };
  Standard_Real A_Value   = ActTestLib_Common::RandomReal(),
                A_1_Value = ActTestLib_Common::RandomReal(),
                A_2_Value = ActTestLib_Common::RandomReal(),
                A_3_Value = ActTestLib_Common::RandomReal();

  // Prepare data to initialize the involved B Nodes
  Standard_Integer B_1_iValue = ActTestLib_Common::RandomInteger(),
                   B_2_iValue = ActTestLib_Common::RandomInteger(),
                   B_3_iValue = ActTestLib_Common::RandomInteger(),
                   B_4_iValue = ActTestLib_Common::RandomInteger();
  Standard_Real B_1_fValue = ActTestLib_Common::RandomReal(),
                B_2_fValue = ActTestLib_Common::RandomReal(),
                B_3_fValue = ActTestLib_Common::RandomReal(),
                B_4_fValue = ActTestLib_Common::RandomReal();

  // Prepare data for VARIABLE Nodes
  Standard_Real VAR_1_fValue = 1.0,
                VAR_2_fValue = 2.0;

  // Attach data to the CAF Document
  M->OpenCommand();

  ANodeIDs.Append( M->StubAPartition()->AddNode(A) ); // This will be a ROOT Node
  ANodeIDs.Append( M->StubAPartition()->AddNode(A_1) );
  ANodeIDs.Append( M->StubAPartition()->AddNode(A_2) );
  ANodeIDs.Append( M->StubAPartition()->AddNode(A_3) );
  BNodeIDs.Append( M->StubBPartition()->AddNode(B_1) );
  BNodeIDs.Append( M->StubBPartition()->AddNode(B_2) );
  BNodeIDs.Append( M->StubBPartition()->AddNode(B_3) );
  BNodeIDs.Append( M->StubBPartition()->AddNode(B_4) );
  VARNodeIDs.Append( M->VariablePartition(ActAPI_IModel::Variable_Real)->AddNode(VAR_1) );
  VARNodeIDs.Append( M->VariablePartition(ActAPI_IModel::Variable_Real)->AddNode(VAR_2) );

  A  ->SetName("Root A");
  A_1->SetName("A_1");
  A_2->SetName("A_2");
  A_3->SetName("A_3");
  B_1->SetName("B_1");
  B_2->SetName("B_2");
  B_3->SetName("B_3");
  B_4->SetName("B_4");
  VAR_1->SetName("VAR_1");
  VAR_2->SetName("VAR_2");

  A  ->Init(A_Shapes[0],   A_Shapes[1],   A_Value);
  A_1->Init(A_1_Shapes[0], A_1_Shapes[1], A_1_Value);
  A_2->Init(A_2_Shapes[0], A_2_Shapes[1], A_2_Value);
  A_3->Init(A_3_Shapes[0], A_3_Shapes[1], A_3_Value);

  B_1->Init(B_1_iValue, B_1_fValue);
  B_2->Init(B_2_iValue, B_2_fValue);
  B_3->Init(B_3_iValue, B_3_fValue);
  B_4->Init(B_4_iValue, B_4_fValue);

  VAR_1->Init("v1", VAR_1_fValue);
  VAR_2->Init("v2", VAR_2_fValue);

  M->CommitCommand();

  // Check if initial data is OK
  ACT_VERIFY( A_1->IsWellFormed() );
  ACT_VERIFY( A_2->IsWellFormed() );
  ACT_VERIFY( A_3->IsWellFormed() );
  ACT_VERIFY( B_1->IsWellFormed() );
  ACT_VERIFY( B_2->IsWellFormed() );
  ACT_VERIFY( B_3->IsWellFormed() );
  ACT_VERIFY( B_4->IsWellFormed() );
  ACT_VERIFY( VAR_1->IsWellFormed() );
  ACT_VERIFY( VAR_2->IsWellFormed() );

  // Build parent-child relationship
  M->OpenCommand();
  A->AddChildNode(A_1);
  A->AddChildNode(B_3);
  A->AddChildNode(B_4);
  A->AddChildNode(VAR_1);
  A->AddChildNode(VAR_2);
  A_1->AddChildNode(B_1);
  A_1->AddChildNode(A_2);
  A_2->AddChildNode(B_2);
  A_2->AddChildNode(A_3);
  M->CommitCommand();

  return true;
}

//! Verifies the Nodal sub-tree against the passed pattern. Relocation tables
//! are used to retrieve the ultimate source IDs for each target Data Node
//! which is treated as a result of copying operation.
//! \param theRoot [in] root of the Nodal sub-tree to verify.
//! \param COPYReloc [in] relocation table prepared at COPY stage.
//! \param PASTEReloc [in] relocation table prepared at PASTE stage.
//! \param TREELevels [in] pattern to check the actual tree against.
//! \param LevelIndex [in] tree level to check.
//! \param SiblingIndex [in] sibling to check.
//! \param IsOK [out] verification result.
void
  ActTest_CopyPasteEngine::verifyTree(const Handle(ActAPI_INode)& theRoot,
                                      const ActData_CopyPasteEngine::RelocationTable& COPYReloc,
                                      const ActData_CopyPasteEngine::RelocationTable& PASTEReloc,
                                      TreeLevelSeq* TREELevels,
                                      const Standard_Integer LevelIndex,
                                      const Standard_Integer SiblingIndex,
                                      Standard_Boolean& IsOK)
{
  TDF_Label aLabTrg = theRoot->RootLabel();
  TDF_Label aLabSrc = COPYReloc.Find2( PASTEReloc.Find2(aLabTrg) );

  TCollection_AsciiString aSourceID = ActData_Utils::GetEntry(aLabSrc);
  TCollection_AsciiString anExpectedID = TREELevels[LevelIndex].Value(SiblingIndex);

  if ( !::IsEqual(aSourceID, anExpectedID) )
  {
    IsOK = Standard_False;
    return;
  }

  Standard_Integer i = 0;
  for ( Handle(ActAPI_IChildIterator) it1 = theRoot->GetChildIterator(); it1->More(); it1->Next() )
  {
    Handle(ActAPI_INode) aChild = it1->Value();
    verifyTree(aChild, COPYReloc, PASTEReloc, TREELevels, LevelIndex + 1, ++i, IsOK);
  }
}

//! Returns path where temporary files are dumped.
//! \return dumping path.
TCollection_AsciiString ActTest_CopyPasteEngine::dumpPath()
{
  TCollection_AsciiString
    path = ActAux::slashed( ActTestLib_Launcher::current_temp_dir_files() ).c_str();
  return path;
}

#pragma warning(default: 4800) // "Standard_Boolean: forcing value to bool" by ACT_VERIFY
#pragma warning(default: 4127) // "Conditional expression is constant" by ACT_VERIFY
