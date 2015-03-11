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
#include <Mesh_Node.h>

// Mesh includes
#include <Mesh_Position.h>
#include <Mesh_SpacePosition.h>

// OCCT includes
#include <gp_Pnt.hxx>

//-----------------------------------------------------------------------------

static const Handle(Mesh_Position)& StaticInstancePosition()
{
  static Handle(Mesh_SpacePosition) staticpos;
  if (staticpos.IsNull())
    staticpos = new Mesh_SpacePosition();
  return staticpos;
}

//-----------------------------------------------------------------------------

Mesh_Node::Mesh_Node(const Standard_Integer ID,
                     const Standard_Real    x,
                     const Standard_Real    y,
                     const Standard_Real    z)
: Mesh_Element ( ID, 1 ),
  myPnt        ( x, y, z),
  myPosition   ( StaticInstancePosition() )
{
}

//-----------------------------------------------------------------------------

void Mesh_Node::SetPnt (const gp_Pnt& P, const Standard_Boolean isClearNormals)
{
  myPnt = P;
  if (isClearNormals) {
    ClearNormal();
    Mesh_ListOfElements::Iterator anIter (InverseElements());
    for (; anIter.More(); anIter.Next())
      if (!anIter.Value().IsNull())
        anIter.Value()->ClearNormal();
  }
}

//-----------------------------------------------------------------------------

void Mesh_Node::RemoveInverseElement(const Handle(Mesh_Element)& parent)
{
  // create copy of handle to avoid entity nullifying till the end of cycle
  Handle(Mesh_Element) elem = parent;
  Mesh_ListOfElements::Iterator itLstInvCnx(myInverseElements);
  while (itLstInvCnx.More()) {
    Handle(Mesh_Element)& ME = itLstInvCnx.Value();
    //the same elements can belong to the different meshes in one mesh tree
    //if (ME->IsSame(elem))
    if (ME == elem)
      myInverseElements.Remove(itLstInvCnx);
    else
      itLstInvCnx.Next();
  }
}

//-----------------------------------------------------------------------------

void Mesh_Node::Print(Standard_OStream& OS) const
{
  OS << "Node < " << myID << " > : X = " << myPnt.X() << " Y = " << myPnt.Y() << " Z = " << myPnt.Z() << endl;
}
