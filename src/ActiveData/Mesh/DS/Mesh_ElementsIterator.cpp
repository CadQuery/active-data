//-----------------------------------------------------------------------------
// Created on: June 2016
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
    0x08,                               // OMFAbs_Volume
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
