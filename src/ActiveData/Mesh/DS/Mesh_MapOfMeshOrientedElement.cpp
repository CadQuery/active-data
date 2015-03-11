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
#include <Mesh_MapOfMeshOrientedElement.h>

//=======================================================================
//function : Find
//purpose  : 
//=======================================================================

const Handle(Mesh_Element)& Mesh_MapOfMeshOrientedElement::Find(const Handle(Mesh_Element)& K) const
{
  if (IsEmpty()) {
    Standard_NoSuchObject::Raise("Mesh_MapOfMeshOrientedElement::Find");
  }
//  Standard_NoSuchObject_Raise_if(IsEmpty(),"Mesh_MapOfMeshOrientedElement::Find");
  Mesh_MapOfOrientedElements::MapNode** data = (Mesh_MapOfOrientedElements::MapNode**) myData1;
  Mesh_MapOfOrientedElements::MapNode* p = data[Mesh_Element::OrientedHasher::HashCode(K,NbBuckets())];
  while (p) {
    if (Mesh_Element::OrientedHasher::IsEqual(p->Key(),K))
      return p->Key();
    p = (Mesh_MapOfOrientedElements::MapNode*) p->Next();
  }
  Standard_NoSuchObject::Raise("Mesh_MapOfMeshOrientedElement::Find");
  return p->Key();
}

//=======================================================================
//function : ChangeFind
//purpose  : 
//=======================================================================

Handle(Mesh_Element)& Mesh_MapOfMeshOrientedElement::ChangeFind(const Handle(Mesh_Element)& K)
{
  if (IsEmpty()) {
    Standard_NoSuchObject::Raise("Mesh_MapOfMeshOrientedElement::ChangeFind");
  }
//Standard_NoSuchObject_Raise_if(IsEmpty(),"Mesh_MapOfMeshOrientedElement::ChangeFind");
  Mesh_MapOfOrientedElements::MapNode** data = (Mesh_MapOfOrientedElements::MapNode**) myData1;
  Mesh_MapOfOrientedElements::MapNode* p = data[Mesh_Element::OrientedHasher::HashCode(K,NbBuckets())];
  while (p) {
    if (Mesh_Element::OrientedHasher::IsEqual(p->Key(),K))
      return p->ChangeValue();
    p = (Mesh_MapOfOrientedElements::MapNode*)  p->Next();
  }
  Standard_NoSuchObject::Raise("Mesh_MapOfMeshOrientedElement::ChangeFind");
  return p->ChangeValue();
}


//=======================================================================
//function : FindID
//purpose  : 
//=======================================================================

const Handle(Mesh_Element)& Mesh_MapOfMeshOrientedElement::FindID(const Standard_Integer ID) const
{
  if (IsEmpty()) {
    Standard_NoSuchObject::Raise("Mesh_MapOfMeshOrientedElement::FindID");
  }
//  Standard_NoSuchObject_Raise_if(IsEmpty(),"Mesh_MapOfMeshOrientedElement::Find");
  Mesh_MapOfOrientedElements::MapNode** data = (Mesh_MapOfOrientedElements::MapNode**) myData1;
  Mesh_MapOfOrientedElements::MapNode* p = data[ID % NbBuckets()];
  while (p) {
    if (p->Key()->GetID() == ID)
      return p->ChangeValue();
    p = (Mesh_MapOfOrientedElements::MapNode*) p->Next();
  }
  Standard_NoSuchObject::Raise("Mesh_MapOfMeshOrientedElement::Find");
  return  p->ChangeValue();
}

//=======================================================================
//function : ContainsID
//purpose  : 
//=======================================================================

Standard_Boolean Mesh_MapOfMeshOrientedElement::ContainsID(const Standard_Integer ID) const
{
  if (IsEmpty()) return Standard_False;
  Mesh_MapOfOrientedElements::MapNode** data = (Mesh_MapOfOrientedElements::MapNode**) myData1;
  Mesh_MapOfOrientedElements::MapNode* p = data[ID % NbBuckets()];
  while (p) {
    if (p->Key()->GetID() == ID)
      return Standard_True;
    p = (Mesh_MapOfOrientedElements::MapNode*)p->Next();
  }
  return Standard_False;
}
