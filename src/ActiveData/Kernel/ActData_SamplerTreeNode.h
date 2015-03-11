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

#ifndef ActData_SamplerTreeNode_HeaderFile
#define ActData_SamplerTreeNode_HeaderFile

// Active Data includes
#include <ActData_Common.h>
#include <ActData_Utils.h>

// Active Data (API) includes
#include <ActAPI_INode.h>

DEFINE_STANDARD_HANDLE(ActData_SamplerTreeNode, Standard_Transient)

//! Represents Sampler Tree of IDs used as a pattern for recovering
//! domain-specific connectivity between Data Nodes.
class ActData_SamplerTreeNode : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_SamplerTreeNode, Standard_Transient)

public:

  //! Iterator for ID tree.
  class Iterator
  {
  public:

    //! Constructor accepting the root node of the tree to iterate over.
    //! \param theNode [in] the root node.
    //! \param isAllLevels [in] indicates whether the full LEFT traversal
    //!        must be performed (TRUE) or only the direct children of the
    //!        target root are the subject of iteration.
    Iterator(const ActData_SamplerTreeNode& theNode,
             const Standard_Boolean isAllLevels = Standard_False)
    {
      this->Init(theNode, isAllLevels);
    }

    //! Initializes iterator with the root node of the tree.
    //! \param theNode [in] the root node.
    //! \param isAllLevels [in] indicates whether the full LEFT traversal
    //!        must be performed (TRUE) or only the direct children of the
    //!        target root are the subject of iteration.
    void Init(const ActData_SamplerTreeNode& theNode,
              const Standard_Boolean isAllLevels = Standard_False)
    {
      m_pRoot = &theNode;
      m_bAllLevels = isAllLevels;
      m_pCurrent = const_cast<ActData_SamplerTreeNode*>(m_pRoot);
    }

    //! Checks whether next item exists.
    //! \return true/false.
    Standard_Boolean More() const
    {
      return m_pCurrent != NULL;
    }

    //! Moves iterator to the next item in the tree.
    void Next()
    {
      // Move down if it is ALLOWED and POSSIBLE
      if ( m_bAllLevels && !m_pCurrent->Children.IsEmpty() )
      {
        m_pCurrent = &m_pCurrent->Children.ChangeValue(1);
        return;
      }

      // Move forward if possible (bottom level is already reached)
      if ( m_pCurrent->NextSiblingPtr )
      {
        m_pCurrent = m_pCurrent->NextSiblingPtr;
      }
      // If the ultimate child in a branch is reached, rollback to
      // the father node attempting to find non-traversed sibling
      else
      {
        do
        {
          m_pCurrent = m_pCurrent->ParentPtr;
        }
        while ( m_pCurrent && !m_pCurrent->NextSiblingPtr );
        if ( m_pCurrent )
          m_pCurrent = m_pCurrent->NextSiblingPtr;
      }
    }

    //! Returns current item.
    const ActData_SamplerTreeNode* Current()
    {
      return m_pCurrent;
    }

  private:

    //! Root node of the tree being iterated.
    const ActData_SamplerTreeNode* m_pRoot;

    //! Currently iterated tree node.
    ActData_SamplerTreeNode* m_pCurrent;

    //! Indicates whether the iterator must visit only the direct children
    //! of the target root (FALSE) or traverse the nested nodes as
    //! well (TRUE).
    Standard_Boolean m_bAllLevels;

  };

public:

  ActData_EXPORT
    ActData_SamplerTreeNode( const ActAPI_DataObjectId& theID = ActAPI_DataObjectId() );

  ActData_EXPORT ActData_SamplerTreeNode&
    NewChild();

public:

  ActData_EXPORT static Handle(ActData_SamplerTreeNode)
    Build(const Handle(ActAPI_INode)& theNode);

public:

  //! Child IDs.
  NCollection_Sequence<ActData_SamplerTreeNode> Children;

  //! Stored ID.
  ActAPI_DataObjectId ID;

  //! Pointer to the parent node.
  ActData_SamplerTreeNode* ParentPtr;

  //! Pointer to the next sibling node.
  ActData_SamplerTreeNode* NextSiblingPtr;

private:

  static void build(const Handle(ActAPI_INode)& theNode,
                    ActData_SamplerTreeNode& theSNode);

};

#endif
