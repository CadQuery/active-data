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
