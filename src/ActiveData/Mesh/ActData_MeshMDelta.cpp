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
#include <ActData_MeshMDelta.h>

// Active Data includes
#include <ActData_MeshAttr.h>

//-----------------------------------------------------------------------------
// Construction routines
//-----------------------------------------------------------------------------

//! Constructor accepting an instance of Mesh Attribute as a ground data
//! for modification requests.
//! \param ActualAttr [in] modification ground data.
ActData_MeshMDelta::ActData_MeshMDelta(const Handle(ActData_MeshAttr)& ActualAttr)
: TDF_DeltaOnModification(ActualAttr)
{
}

//-----------------------------------------------------------------------------
// Kernel routines
//-----------------------------------------------------------------------------

//! Applies recorded modifications to ground data.
void ActData_MeshMDelta::Apply()
{
  Handle(ActData_MeshAttr) aMeshAttr = Handle(ActData_MeshAttr)::DownCast( this->Attribute() );
  Handle(ActData_Mesh)& aMesh = aMeshAttr->GetMesh();

  // Iterate over the chain of requests to apply them
  ActData_DeltaMQueue::Iterator anIt(m_queue);
  for ( ; anIt.More(); anIt.Next() )
  {
    const ActData_DeltaMRequest& aNextReq = anIt.Value();
    if ( aNextReq.Type == DeltaMType_Added )
    {
      aNextReq.Entity->AddTo(aMesh);
    }
    else if ( aNextReq.Type == DeltaMType_Removed )
    {
      aNextReq.Entity->RemoveFrom(aMesh);
    }
  }
}

//! Cleans up the modification delta.
void ActData_MeshMDelta::Clean()
{
  m_queue.Clear();
}

//! Creates a full copy of Modification Delta.
//! \return full copy.
Handle(ActData_MeshMDelta) ActData_MeshMDelta::DeepCopy() const
{
  Handle(ActData_MeshMDelta) aCopy =
    new ActData_MeshMDelta( Handle(ActData_MeshAttr)::DownCast( this->Attribute() ) );

  // Copy the queue of modification requests
  ActData_DeltaMQueue::Iterator anIt(m_queue);
  for ( ; anIt.More(); anIt.Next() )
  {
    const ActData_DeltaMRequest& aNextReq = anIt.Value();
    aCopy->m_queue.Append(aNextReq);
  }
  
  return aCopy;
}

//! Inverts recorded Modification Requests and puts them in a reversed order.
//! E.g. if the recorded chain was
//!
//! <pre>
//!   [1]          [2]              [3]               [4]           [5]
//! AddNode -> AddTriangle -> RemoveQuadrangle -> RemoveNode -> RemoveNode,
//! </pre>
//!
//! the corresponding inverted sequence would be the following:
//!
//! <pre>
//!   [5]        [4]           [3]              [2]              [1]
//! AddNode -> AddNode -> AddQuadrangle -> RemoveTriangle -> RemoveNode.
//! </pre>
//!
//! Therefore, this method is used to apply the Modification Delta to the
//! actual Attribute with conceptual negation sign. Think of this method
//! as a basis for UNDO functionality.
void ActData_MeshMDelta::Invert()
{
  // Reverse order
  m_queue.Reverse();

  // Reverse modifications
  ActData_DeltaMQueue::Iterator anIt(m_queue);
  for ( ; anIt.More(); anIt.Next() )
  {
    ActData_DeltaMRequest& aNextReq = anIt.ChangeValue();
    if ( aNextReq.Type == DeltaMType_Added )
      aNextReq.Type = DeltaMType_Removed;
    else if ( aNextReq.Type == DeltaMType_Removed )
      aNextReq.Type = DeltaMType_Added;
  }
}

//-----------------------------------------------------------------------------
// Recording modification requests
//-----------------------------------------------------------------------------

//! Informs Delta that the entire mesh has been exchanged with a new one. In
//! such case all previous modification requests are erased as they are
//! redundant in the current transactional scope.
//! \param OldMesh [in] old mesh DS.
//! \param NewMesh [in] new mesh DS.
void ActData_MeshMDelta::ReplacedMesh(const Handle(ActData_Mesh)& OldMesh,
                                      const Handle(ActData_Mesh)& NewMesh)
{
  Handle(ActData_DeltaMMesh) aMMesh = new ActData_DeltaMMesh();
  aMMesh->OldMesh = OldMesh;
  aMMesh->NewMesh = NewMesh;

  this->Clean();
  m_queue.Append( ActData_DeltaMRequest(DeltaMType_Added, aMMesh) );
}

//! Adds the modification request to the internal queue. This request informs
//! Delta that mesh node with the given ID and co-ordinates has been added
//! to the mesh data set.
//! \param ID [in] node ID.
//! \param X [in] node X co-ordinate.
//! \param Y [in] node Y co-ordinate.
//! \param Z [in] node Z co-ordinate.
void ActData_MeshMDelta::AddedNode(const Standard_Integer ID,
                                   const Standard_Real X,
                                   const Standard_Real Y,
                                   const Standard_Real Z)
{
  Handle(ActData_DeltaMNode) aMNode = new ActData_DeltaMNode();
  aMNode->ID = ID;
  aMNode->X = X;
  aMNode->Y = Y;
  aMNode->Z = Z;

  m_queue.Append( ActData_DeltaMRequest(DeltaMType_Added, aMNode) );
}

//! Adds the modification request to the internal queue. This request informs
//! Delta that mesh triangle element with the given ID and underlying nodes
//! has been added to the mesh data set.
//! \param ID [in] element ID.
//! \param Nodes [in] triple of node IDs.
void ActData_MeshMDelta::AddedTriangle(const Standard_Integer ID,
                                       Standard_Address Nodes)
{
  Standard_Integer* aNodeArr = (Standard_Integer*) Nodes;
  Handle(ActData_DeltaMTriangle) aMTri = new ActData_DeltaMTriangle();
  aMTri->ID = ID;
  aMTri->Nodes[0] = aNodeArr[0];
  aMTri->Nodes[1] = aNodeArr[1];
  aMTri->Nodes[2] = aNodeArr[2];

  m_queue.Append( ActData_DeltaMRequest(DeltaMType_Added, aMTri) );
}

//! Adds the modification request to the internal queue. This request informs
//! Delta that mesh quadrangle element with the given ID and underlying nodes
//! has been added to the mesh data set.
//! \param ID [in] element ID.
//! \param Nodes [in] tetrad of node IDs.
void ActData_MeshMDelta::AddedQuadrangle(const Standard_Integer ID,
                                         Standard_Address Nodes)
{
  Standard_Integer* aNodeArr = (Standard_Integer*) Nodes;
  Handle(ActData_DeltaMQuadrangle) aMQuad = new ActData_DeltaMQuadrangle();
  aMQuad->ID = ID;
  aMQuad->Nodes[0] = aNodeArr[0];
  aMQuad->Nodes[1] = aNodeArr[1];
  aMQuad->Nodes[2] = aNodeArr[2];
  aMQuad->Nodes[3] = aNodeArr[3];

  m_queue.Append( ActData_DeltaMRequest(DeltaMType_Added, aMQuad) );
}

//! Adds the modification request to the internal queue. This request informs
//! Delta that mesh node with the given ID has been removed from the mesh
//! data set.
//! \param ID [in] node ID.
void ActData_MeshMDelta::RemovedNode(const Standard_Integer ID)
{
  Handle(ActData_DeltaMNode) aMNode = new ActData_DeltaMNode();
  aMNode->ID = ID;

  m_queue.Append( ActData_DeltaMRequest(DeltaMType_Removed, aMNode) );
}

//! Adds the modification request to the internal queue. This request informs
//! Delta that mesh triangle element with the given ID has been removed from
//! the mesh data set.
//! \param ID [in] element ID.
void ActData_MeshMDelta::RemovedTriangle(const Standard_Integer ID)
{
  Handle(ActData_DeltaMTriangle) aMTri = new ActData_DeltaMTriangle();
  aMTri->ID = ID;

  m_queue.Append( ActData_DeltaMRequest(DeltaMType_Removed, aMTri) );
}

//! Adds the modification request to the internal queue. This request informs
//! Delta that mesh quadrangle element with the given ID has been removed from
//! the mesh data set.
//! \param ID [in] element ID.
void ActData_MeshMDelta::RemovedQuadrangle(const Standard_Integer ID)
{
  Handle(ActData_DeltaMQuadrangle) aMQuad = new ActData_DeltaMQuadrangle();
  aMQuad->ID = ID;

  m_queue.Append( ActData_DeltaMRequest(DeltaMType_Removed, aMQuad) );
}

//-----------------------------------------------------------------------------
// Support for debugging
//-----------------------------------------------------------------------------

//! Dumps the contents of the Modification Delta to the passed output
//! stream.
//! \param theOut [in/out] output stream.
//! \return affected output stream (just for convenience).
Standard_OStream& ActData_MeshMDelta::Dump(Standard_OStream& theOut) const
{
  theOut << "Iterating in default order: from HEAD to TAIL...\n";

  ActData_DeltaMQueue::Iterator anIt(m_queue);
  for ( ; anIt.More(); anIt.Next() )
  {
    const ActData_DeltaMRequest& aNextReq = anIt.Value();
    theOut << " ---> " << aNextReq.Entity->ID;
  }
  theOut << "\n\n";

  return theOut;
}
