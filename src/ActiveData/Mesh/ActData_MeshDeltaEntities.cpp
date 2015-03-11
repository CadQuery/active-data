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
#include <ActData_MeshDeltaEntities.h>

// Active Data includes
#include <ActData_Common.h>

//-----------------------------------------------------------------------------
// Class: ActData_DeltaMNode
//-----------------------------------------------------------------------------

//! Adds the entity represented by Modification Delta Object to the
//! passed Mesh DS.
//! \param theMesh [in] mesh to apply modifications on.
void ActData_DeltaMNode::AddTo(Handle(ActData_Mesh)& theMesh)
{
  theMesh->AddNode(X, Y, Z);
}

//! Removes the entity represented by Modification Delta Object from the
//! passed Mesh DS.
//! \param theMesh [in] mesh to apply modifications on.
void ActData_DeltaMNode::RemoveFrom(Handle(ActData_Mesh)& theMesh)
{
  theMesh->RemoveNode(ID);
}

//-----------------------------------------------------------------------------
// Class: ActData_DeltaMTriangle
//-----------------------------------------------------------------------------

//! Adds the entity represented by Modification Delta Object to the
//! passed Mesh DS.
//! \param theMesh [in] mesh to apply modifications on.
void ActData_DeltaMTriangle::AddTo(Handle(ActData_Mesh)& theMesh)
{
  theMesh->AddFace(Nodes, 3);
}

//! Removes the entity represented by Modification Delta Object from the
//! passed Mesh DS.
//! \param theMesh [in] mesh to apply modifications on.
void ActData_DeltaMTriangle::RemoveFrom(Handle(ActData_Mesh)& theMesh)
{
  Handle(Mesh_Element) anElem = theMesh->FindElement(ID);
  theMesh->RemoveElement(ID);
}

//-----------------------------------------------------------------------------
// Class: ActData_DeltaMQuadrangle
//-----------------------------------------------------------------------------

//! Adds the entity represented by Modification Delta Object to the
//! passed Mesh DS.
//! \param theMesh [in] mesh to apply modifications on.
void ActData_DeltaMQuadrangle::AddTo(Handle(ActData_Mesh)& theMesh)
{
  theMesh->AddFace(Nodes, 4);
}

//! Removes the entity represented by Modification Delta Object from the
//! passed Mesh DS.
//! \param theMesh [in] mesh to apply modifications on.
void ActData_DeltaMQuadrangle::RemoveFrom(Handle(ActData_Mesh)& theMesh)
{
  Handle(Mesh_Element) anElem = theMesh->FindElement(ID);
  theMesh->RemoveElement(ID);
}

//-----------------------------------------------------------------------------
// Class: ActData_DeltaMMesh
//-----------------------------------------------------------------------------

//! Adds the entity represented by Modification Delta Object to the
//! passed Mesh DS.
//! \param theMesh [in] mesh to apply modifications on.
void ActData_DeltaMMesh::AddTo(Handle(ActData_Mesh)& theMesh)
{
  theMesh = this->NewMesh;
}

//! Removes the entity represented by Modification Delta Object from the
//! passed Mesh DS.
//! \param theMesh [in] mesh to apply modifications on.
void ActData_DeltaMMesh::RemoveFrom(Handle(ActData_Mesh)& theMesh)
{
  theMesh = this->OldMesh;
}
