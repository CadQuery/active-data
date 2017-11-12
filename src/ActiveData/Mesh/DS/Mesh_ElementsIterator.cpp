//-----------------------------------------------------------------------------
// Created on: June 2016
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//    * Neither the name of OPEN CASCADE SAS nor the
//      names of all contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Web: http://dev.opencascade.org
//-----------------------------------------------------------------------------

// Own include
#include <Mesh_ElementsIterator.h>

// Mesh includes
#include <Mesh.h>
#include <Mesh_IDFactory.h>

//=======================================================================
//function : Mesh_ElementsIterator
//purpose  : Constructor
//=======================================================================
Mesh_ElementsIterator::Mesh_ElementsIterator
                                        (const Handle(ActData_Mesh)&  theMesh,
                                         const Mesh_ElementType theType)
   : myMesh (theMesh)
{
  switch (theType) {
  case Mesh_ET_Node:
    myType = 0x01;
    myIter = theMesh -> myNodeIDFactory -> Iterator();
    break;
  case Mesh_ET_All:
  default:
    myType = 0x02 + 0x04 + 0x08; 
    myIter = theMesh -> myElementIDFactory -> Iterator();
    break;
  case Mesh_ET_Edge:
    myType = 0x02; 
    myIter = theMesh -> myElementIDFactory -> Iterator();
    break;
  case Mesh_ET_Face:
    myType = 0x04; 
    myIter = theMesh -> myElementIDFactory -> Iterator();
    break;
  }
  findNext();
}

//=======================================================================
//function : Mesh_ElementsIterator()
//purpose  : 
//=======================================================================

void Mesh_ElementsIterator::Initialize
                                        (const Handle(ActData_Mesh)&  theMesh,
                                         const Mesh_ElementType theAddType)
{
  myMesh = theMesh;
  if (myType & 0x01)
    myIter = theMesh -> myNodeIDFactory -> Iterator();
  else {
    myIter = theMesh -> myElementIDFactory -> Iterator();
    switch (theAddType) {
    case Mesh_ET_All:
      myType |= (0x02 + 0x04 + 0x08); 
      break;
    case Mesh_ET_Edge:
      myType |= 0x02; 
      break;
    case Mesh_ET_Face:
      myType |= 0x04; 
      break;
    default:;
    }
  }
  findNext();
}

//=======================================================================
//function : findNext
//purpose  : skip empty elements, elements not covered by the iterated type
//           and the elements not belonging to the current Mesh
//=======================================================================

void Mesh_ElementsIterator::findNext()
{
  // Here we make the implicit assumption that the enum ElementType starts
  // from 0, i.e., All == 0, Node == 1, etc.
  static Standard_Integer aTypeMatrix[16] = {
    0x02 + 0x04 + 0x08,                 // Mesh_ET_All
    0x01,                               // Mesh_ET_Node
    0x02,                               // Mesh_ET_Edge
    0x04,                               // Mesh_ET_Face
    0x08,                               // Volume
    0,0,0,0,0,0,0,0,0,0,0
  };
  if (myType & 0x01) {          // Iteration exclusively on nodes
    const TColStd_PackedMapOfInteger& aNodeMap = myMesh -> myNodes;
    while (myIter.More()) {
      const Handle(Mesh_Element)& anElem = myIter.Value();
      if (!anElem.IsNull()) {
        const Standard_Integer anID = anElem -> GetID();
        if (aNodeMap.Contains (anID))
          break;
      }
      myIter.Next();
    }
  } else {                      // Iteration on elements (non-nodes)
    while (myIter.More()) {
      const Handle(Mesh_Element)& anElem = myIter.Value();
      if (!anElem.IsNull())
        if (anElem -> GetMesh() == myMesh.operator->())
          if (aTypeMatrix[anElem->GetType()] & myType)
            break;
      myIter.Next();
    }
  }
}
