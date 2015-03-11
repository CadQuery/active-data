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
#include <ActTest_StubMeshNode.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

//-----------------------------------------------------------------------------
// Implementation of Data Node for testing purposes
//-----------------------------------------------------------------------------

//! Default constructor.
ActTest_StubMeshNode::ActTest_StubMeshNode()
{
  REGISTER_PARAMETER(Name, Param_Name);
  REGISTER_PARAMETER(Mesh, Param_Mesh);
}

//! This method will be called by Nodal Factory in order to allocate
//! Nodes automatically by request (e.g. in Model::FindNode routine).
//! \return new instance of our Dummy Node allocated in heap.
Handle(ActAPI_INode) ActTest_StubMeshNode::Instance()
{
  return new ActTest_StubMeshNode();
}

//! Accessor for the Node's name.
//! \return name of the Node.
TCollection_ExtendedString ActTest_StubMeshNode::GetName()
{
  return ActData_ParameterFactory::AsName( this->Parameter(Param_Name) )->GetValue();
}

//! Sets name for the Node.
//! \param theName [in] name to set.
void ActTest_StubMeshNode::SetName(const TCollection_ExtendedString& theName)
{
  ActData_ParameterFactory::AsName( this->Parameter(Param_Name) )->SetValue(theName);
}

//! InItializes the basic set of Nodal Parameters.
//! \param theMesh [in] mesh to set.
void ActTest_StubMeshNode::Init(const Handle(ActData_Mesh)& theMesh)
{
  ActData_ParameterFactory::AsMesh( this->Parameter(Param_Mesh) )->SetMesh(theMesh);
}

//! Accessor for the stored mesh.
//! \return requested mesh.
Handle(ActData_Mesh) ActTest_StubMeshNode::GetMesh() const
{
  return ActData_ParameterFactory::AsMesh( this->Parameter(Param_Mesh) )->GetMesh();
}
