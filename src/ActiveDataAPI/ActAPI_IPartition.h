//-----------------------------------------------------------------------------
// Created on: March 2012
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

#ifndef ActAPI_IPartition_HeaderFile
#define ActAPI_IPartition_HeaderFile

// Active Data (API) includes
#include <ActAPI_INode.h>

// OCCT includes
#include <Standard_Type.hxx>

//! \ingroup AD_API
//!
//! Interface for ACT data Partitions.
class ActAPI_IPartition : public ActAPI_IDataCursor
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_IPartition, ActAPI_IDataCursor)

public:

  ActAPI_EXPORT virtual
    ~ActAPI_IPartition();

public:

  //! Iterator for underlying Nodes.
  class Iterator 
  {
  public:

    ActAPI_EXPORT virtual
      ~Iterator();

  public:

    virtual void                 Init  (const Handle(ActAPI_IPartition)& theIP)       = 0;
    virtual Standard_Boolean     More  ()                                       const = 0;
    virtual void                 Next  ()                                             = 0;
    virtual Handle(ActAPI_INode) Value ()                                       const = 0;

  };

public:

  virtual ActAPI_DataObjectId
    AddNode(const Handle(ActAPI_INode)& theNode) = 0;

  virtual Standard_Boolean
    GetNode(const Standard_Integer theNodeNum,
            const Handle(ActAPI_INode)& theNode) const = 0;

  virtual Handle(ActAPI_INode)
    GetNode(const Standard_Integer theNodeNum) const = 0;

  virtual Handle(Standard_Type)
    GetNodeType() const = 0;

};

//! \ingroup AD_API
//!
//! Shortcuts for list of Parameters.
typedef NCollection_Sequence<Handle(ActAPI_IPartition)> ActAPI_PartitionList;
typedef NCollection_Shared<ActAPI_PartitionList> ActAPI_HPartitionList;

#endif
