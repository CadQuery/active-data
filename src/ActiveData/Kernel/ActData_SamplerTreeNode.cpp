//-----------------------------------------------------------------------------
// Created on: November 2012
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
#include <ActData_SamplerTreeNode.h>

//! Constructor accepting entity ID.
//! \param theID [in] entity ID.
ActData_SamplerTreeNode::ActData_SamplerTreeNode(const ActAPI_DataObjectId& theID)
: Standard_Transient(),
  ID(theID),
  ParentPtr(NULL),
  NextSiblingPtr(NULL)
{}

//! Adds new tree node into collection of children.
//! \return reference to the added tree node.
ActData_SamplerTreeNode& ActData_SamplerTreeNode::NewChild()
{
  Children.Append( ActData_SamplerTreeNode() );
  Standard_Integer aLastIndex = Children.Length();
  ActData_SamplerTreeNode& aNewChild = Children.ChangeValue(aLastIndex);

  // Set traversal references
  aNewChild.ParentPtr = this;
  if ( aLastIndex > 1 )
  {
    ActData_SamplerTreeNode& aPrevChild = Children.ChangeValue(aLastIndex - 1);
    aPrevChild.NextSiblingPtr = &aNewChild;
  }

  return aNewChild;
}

//! Builds Sampler Tree model starting from the given Data Node.
//! \param theNode [in] root Node for the modeled branch.
//! \return resulting Sampler Tree.
Handle(ActData_SamplerTreeNode)
  ActData_SamplerTreeNode::Build(const Handle(ActAPI_INode)& theNode)
{
  Handle(ActData_SamplerTreeNode) aResult = new ActData_SamplerTreeNode;
  ActData_SamplerTreeNode* aResultPtr = reinterpret_cast<ActData_SamplerTreeNode*>( aResult.get() );
  build(theNode, *aResultPtr);
  return aResult;
}

//! Internal Sampler Tree construction routine.
//! \param theNode [in] currently processed Data Node.
//! \param theSNode [in/out] Sample Tree Node representation of the currently
//!        processed Data Node.
void ActData_SamplerTreeNode::build(const Handle(ActAPI_INode)& theNode,
                                    ActData_SamplerTreeNode& theSNode)
{
  theSNode.ID = theNode->GetId();
  for ( Handle(ActAPI_IChildIterator) it = theNode->GetChildIterator(); it->More(); it->Next() )
  {
    Handle(ActAPI_INode) aChild = it->Value();
    build( aChild, theSNode.NewChild() );
  }
}
