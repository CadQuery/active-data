//-----------------------------------------------------------------------------
// Created on: February 2012
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
#include <ActData_TreeNodeParameter.h>

// Active Data includes
#include <ActData_NodeFactory.h>
#include <ActData_Utils.h>

// OCCT includes
#include <Standard_ProgramError.hxx>
#include <TDF_Tool.hxx>

//-----------------------------------------------------------------------------
// Parameter
//-----------------------------------------------------------------------------

//! Hidden constructor.
ActData_TreeNodeParameter::ActData_TreeNodeParameter() : ActData_UserParameter()
{
}

//! Ensures correct construction of the Parameter object, e.g. prevents
//! allocating it in stack memory.
//! \return Parameter instance.
Handle(ActData_TreeNodeParameter) ActData_TreeNodeParameter::Instance()
{
  return new ActData_TreeNodeParameter();
}

//! Appends the passed Tree Node Parameter as a child to this one.
//! \param theTreeNode [in] Tree Node Parameter to append.
void ActData_TreeNodeParameter::AppendChild(const Handle(ActData_TreeNodeParameter)& theTreeNode)
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  /* ================================================
   *  If child attribute already has some father, it
   *  must be removed from there
   * ================================================ */

  Handle(TDataStd_TreeNode) aChildNode =
    accessInternalNode( theTreeNode->m_label.FindChild(DS_TreeNode) );

  if ( aChildNode->HasFather() )
    aChildNode->Remove();

  /* ========================================
   *  Perform requested parent-child binding
   * ======================================== */

  Handle(TDataStd_TreeNode) aParentNode =
    accessInternalNode( m_label.FindChild(DS_TreeNode) );

  aParentNode->Append(aChildNode);

  /* ====================================================
   *  Get ultimate root in USER tree hierarchy and check
   *  if current father must be appended as a child to
   *  this ultimate root
   * ==================================================== */

  Handle(TDataStd_TreeNode) aRootNode = accessInternalNode( m_label.Root() );
  if ( aParentNode->Father().IsNull() )
    aRootNode->Append(aParentNode);
}

//! Removes the passed Tree Node Parameter from the list of children of this
//! Parameter.
//! \param theTreeNode [in] Tree Node Parameter to remove.
//! \return true in case of success, false -- otherwise.
Standard_Boolean ActData_TreeNodeParameter::RemoveChild(const Handle(ActData_TreeNodeParameter)& theTreeNode)
{
  if ( this->IsDetached() )
    Standard_ProgramError::Raise("Cannot access detached data");

  Handle(TDataStd_TreeNode) aChild      = theTreeNode->GetCAFTreeNode();
  Handle(TDataStd_TreeNode) aThisParent = this->GetCAFTreeNode();

  if ( aChild->Father() != aThisParent )
    return Standard_False; // The passed Tree Node Parameter is not a child
                           // for this one, so lets return false

  // Remove the child Tree Node from this one
  return aChild->Remove();
}

//! \return underlying OCAF attribute.
Handle(TDataStd_TreeNode) ActData_TreeNodeParameter::GetCAFTreeNode()
{
  return accessInternalNode( m_label.FindChild(DS_TreeNode, Standard_False),
                             Standard_False );
}

//! Gives access to the underlying OCAF attribute.
//! \param theLab   [in] owning OCAF Label.
//! \param toCreate [in] indicates whether creation is allowed.
//! \return Tree Node attribute.
Handle(TDataStd_TreeNode)
  ActData_TreeNodeParameter::accessInternalNode(const TDF_Label&       theLab,
                                                const Standard_Boolean toCreate)
{
  return ActData_Utils::AccessTreeNode(theLab, toCreate);
}

//! Checks if this Parameter object is mapped onto CAF data structure in a
//! correct way.
//! \return true if the object is well-formed, false -- otherwise.
Standard_Boolean ActData_TreeNodeParameter::isWellFormed() const
{
  // Tree Node is an optional Parameter, so it is Ok even without anything ;)
  return Standard_True;
}

//! Returns Parameter type.
//! \return Parameter type.
Standard_Integer
  ActData_TreeNodeParameter::parameterType() const
{
  return Parameter_TreeNode;
}

//-----------------------------------------------------------------------------
// DTO construction
//-----------------------------------------------------------------------------

//! Populates Parameter from the passed DTO.
//! \param theDTO          [in] DTO to source data from.
//! \param theModType      [in] modification type.
//! \param doResetValidity [in] indicates whether validity flag must be
//!                             reset or not.
//! \param doResetPending  [in] indicates whether pending flag must be reset
//!                             or not.
void ActData_TreeNodeParameter::setFromDTO(const Handle(ActData_ParameterDTO)& theDTO,
                                           const ActAPI_ModificationType       ActData_NotUsed(theModType),
                                           const Standard_Boolean              ActData_NotUsed(doResetValidity),
                                           const Standard_Boolean              ActData_NotUsed(doResetPending))
{
  Handle(ActData_TreeNodeDTO) MyDTO = Handle(ActData_TreeNodeDTO)::DownCast(theDTO);

  // Get parent Label
  TDF_Label aParentLab;
  TDF_Tool::Label(m_label.Data(), MyDTO->ParentId, aParentLab);

  if ( !aParentLab.IsNull() && ActData_NodeFactory::IsNode(aParentLab) )
  {
    // Access parent Data Node
    Handle(ActData_BaseNode)
      aParentNode = Handle(ActData_BaseNode)::DownCast( ActData_NodeFactory::NodeSettle(aParentLab) );

    // Access parent's Tree Node Parameter
    Handle(ActData_TreeNodeParameter)
      aParentTNParam = aParentNode->accessTreeNodeParameter(MyDTO->PID);

    // Access OCAF Tree Node Attribute for parent
    Handle(TDataStd_TreeNode) aParentTN = aParentTNParam->GetCAFTreeNode();

    // Access OCAF Tree Node Attribute for this
    Handle(TDataStd_TreeNode) aChildTN = this->GetCAFTreeNode();

    // Establish parent-child relation
    aChildTN->SetFather(aParentTN);
  }
}

//! Creates and populates DTO.
//! \param theGID [in] ready-to-use GID for DTO.
//! \return constructed DTO instance.
Handle(ActData_ParameterDTO)
  ActData_TreeNodeParameter::createDTO(const ActAPI_ParameterGID& theGID)
{
  // Access OCAF Tree Node Attribute for this & father
  Handle(TDataStd_TreeNode) aChildTN  = this->GetCAFTreeNode();
  Handle(TDataStd_TreeNode) aParentTN = aChildTN->Father();

  // Access parent Node
  Handle(ActAPI_INode) aParentNode;
  if ( !aParentTN.IsNull() )
    aParentNode = ActData_NodeFactory::NodeSettle( aParentTN->Label().Father().Father().Father() );

  // ...
  // Create DTO
  // ...

  Handle(ActData_TreeNodeDTO) aResult = new ActData_TreeNodeDTO(theGID);
  //
  if ( !aParentNode.IsNull() )
  {
    aResult->ParentId = aParentNode->GetId();
    aResult->PID      = aParentTN->Label().Tag();
  }

  return aResult;
}
