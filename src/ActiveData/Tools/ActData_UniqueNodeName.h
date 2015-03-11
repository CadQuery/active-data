//-----------------------------------------------------------------------------
// Created on: April 2014
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

#ifndef ActData_UniqueNodeName_HeaderFile
#define ActData_UniqueNodeName_HeaderFile

// Active Data includes
#include <ActData.h>

// Active Data (API) includes
#include <ActAPI_INode.h>

#define NAMEGEN_NONAME "Untitled"

//-----------------------------------------------------------------------------
// Provider of sibling Nodes
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_SiblingNodes, Standard_Transient)

//! \ingroup AD_DF
//!
//! Wraps sibling Nodes for the given one.
class ActData_SiblingNodes : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_SiblingNodes, Standard_Transient)

public:

  ActData_EXPORT static Handle(ActData_SiblingNodes)
    CreateForRecord(const Handle(ActAPI_INode)& theRecord,
                    const Handle(ActAPI_INode)& theOwner,
                    const Standard_Integer theCollectionPID);

  ActData_EXPORT static Handle(ActData_SiblingNodes)
    CreateForChild(const Handle(ActAPI_INode)& theChild,
                   const Handle(ActAPI_INode)& theOwner);

public:

  //! Returns the number of siblings.
  //! \return number of siblings.
  inline Standard_Integer NumberOfNodes() const
  {
    return m_siblings->Length();
  }

  //! Returns sibling Node with the given 1-based index.
  //! \param theIdx [in] 1-based index of sibling to access.
  //! \return requested Node.
  inline const Handle(ActAPI_INode)& At(const Standard_Integer theIdx) const
  {
    return m_siblings->Value(theIdx);
  }

protected:

  ActData_EXPORT ActData_SiblingNodes&
    operator<<(const Handle(ActAPI_INode)& theSibling);

protected:

  ActData_EXPORT
    ActData_SiblingNodes(const Handle(ActAPI_INode)& theItem,
                        const Handle(ActAPI_INode)& theOwner);

protected:

  Handle(ActAPI_INode)    m_owner;    //!< Owner.
  Handle(ActAPI_INode)    m_item;     //!< Selected item to get siblings for.
  Handle(ActAPI_HNodeList) m_siblings; //!< Collection of siblings.

};

//-----------------------------------------------------------------------------
// Generator
//-----------------------------------------------------------------------------

//! \ingroup AD_DF
//!
//! Unique name generator for Nodes.
class ActData_UniqueNodeName
{
public:

  ActData_EXPORT static TCollection_ExtendedString
    Generate(const Handle(ActData_SiblingNodes)& theNodes,
             const TCollection_ExtendedString& theBaseName = NAMEGEN_NONAME);

private:

  ActData_UniqueNodeName() {}
  ActData_UniqueNodeName(const ActData_UniqueNodeName&) {}

};

#endif
