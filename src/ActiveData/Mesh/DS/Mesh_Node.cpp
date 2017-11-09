//-----------------------------------------------------------------------------
// Created on: June 2016
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the OPEN CASCADE SAS.
// 4. Neither the name of the OPEN CASCADE SAS nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY OPEN CASCADE SAS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL OPEN CASCADE SAS BE LIABLE FOR ANY
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
