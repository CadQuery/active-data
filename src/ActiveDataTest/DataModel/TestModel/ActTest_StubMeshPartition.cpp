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
#include <ActTest_StubMeshPartition.h>

// Active Data includes
#include <ActTest_StubMeshNode.h>

//-----------------------------------------------------------------------------
// Implementation of Data Partition for testing purposes
//-----------------------------------------------------------------------------

//! Default constructor.
ActTest_StubMeshPartition::ActTest_StubMeshPartition()
{}

//! Creates new Partition instance in a heap.
//! \return just created instance of Dummy Partition.
Handle(ActTest_StubMeshPartition) ActTest_StubMeshPartition::Instance()
{
  return new ActTest_StubMeshPartition();
}

//! Returns the Data Node type applicable for this Partition.
//! \return applicable Node type.
Handle(Standard_Type) ActTest_StubMeshPartition::GetNodeType() const
{
  return STANDARD_TYPE(ActTest_StubMeshNode);
}
