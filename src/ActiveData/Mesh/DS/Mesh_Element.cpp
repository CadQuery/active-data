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
#include <Mesh_Element.h>

// Mesh includes
#include <Mesh_Direction.h>

// OCCT includes
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <gp_VectorWithNullMagnitude.hxx>
#include <Standard_OutOfRange.hxx>
#include <Standard_Type.hxx>

//! Constructor for a mesh element with the given ID and number of nodes.
//! \param ID [in] ID of the mesh element.
//! \param nb [in] number of nodes to set.
Mesh_Element::Mesh_Element(const int ID, const int nb)
: myID(ID), myNbNodes(nb), myNormals(0L)
{}

//=======================================================================
//function : Destruct
//purpose  : desctructor
//=======================================================================

inline void Mesh_Element::Destruct ()
{
  if (myNormals) {
    Standard::Free(myNormals);
    myNormals = 0L;
  }
}

//=======================================================================
//function : HashCode
//purpose  : 
//=======================================================================

inline int Mesh_Element::HashCode(const int Upper) const
{
  const int aKey = GetKey();
  return ( (aKey >= 0 ? aKey : -aKey) % Upper );
}

//=======================================================================
//function : GetEdgeDefinedByNodes
//purpose  : 
//=======================================================================

inline void Mesh_Element::GetEdgeDefinedByNodes(const Standard_Integer /*rank*/,
                                                     Standard_Integer& idnode1,
                                                     Standard_Integer& idnode2) const
{
  idnode1 = 0;
  idnode2 = 0;
}

//=======================================================================
//function : GetFaceDefinedByNodes
//purpose  : 
//=======================================================================

inline void Mesh_Element::GetFaceDefinedByNodes(const Standard_Integer /*rank*/,
                                                       const Standard_Address /*idnode*/,
                                                       Standard_Integer& idface) const
{
  idface = 0;
}

//=======================================================================
//function : GetConnections
//purpose  : 
//=======================================================================

inline Standard_Address Mesh_Element::GetConnections() const
{
  return (Standard_Address) &myID;
}

//=======================================================================
//function : GetConnection
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Element::GetConnection(const Standard_Integer /*rank*/) const
{
  return myID;
}

//=======================================================================
//function : AddInverseElement
//purpose  : 
//=======================================================================

inline void Mesh_Element::AddInverseElement(const Handle(Mesh_Element)& /*elem*/)
{
}

//=======================================================================
//function : ClearInverseElements
//purpose  : 
//=======================================================================

inline void Mesh_Element::ClearInverseElements()
{
}

//=======================================================================
//function : NbNodes
//purpose  : 
//           
//=======================================================================

inline Standard_Integer Mesh_Element::NbNodes() const
{
  return myNbNodes;
}

//=======================================================================
//function : NbEdges
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Element::NbEdges() const
{
  return 0;
}

//=======================================================================
//function : NbFaces
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Element::NbFaces() const
{
  return 0;
}

//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Element::GetID() const
{
  return myID;
}

//=======================================================================
//function : GetMesh
//purpose  : 
//=======================================================================

inline ActData_Mesh * Mesh_Element::GetMesh() const
{
  return 0L;
}

//=======================================================================
//function : SetNormal
//purpose  : 
//=======================================================================

inline void Mesh_Element::SetNormal(const Standard_Integer rank, const gp_Vec& V)
{
  SetNormal (rank, V.X(), V.Y(), V.Z());
}

//=======================================================================
//function : IsSame
//purpose  : 
//=======================================================================
Standard_Boolean Mesh_Element::IsSame(const Handle(Mesh_Element)& other) const
{
  if (this->NbNodes()!=other->NbNodes())
    return Standard_False;
  Standard_Integer n = this->NbNodes();
  const Standard_Integer *c1 = (Standard_Integer *)this->GetConnections();
  const Standard_Integer *c2 = (Standard_Integer *)other->GetConnections();
  if (*c1 != *c2)
    return Standard_False;

  n--;
  c1++;
  c2++;

  Standard_Integer off = n-1;

  for (;n--; c1++,c2++) {
    if (*c1 != *c2 && *c1 != *(c2+off))
      return Standard_False;
    off -= 2;
  }

  return Standard_True;
}

//=======================================================================
//function : IsEqual
//purpose  : 
//=======================================================================

Standard_Boolean Mesh_Element::IsEqual(const Handle(Mesh_Element)& other) const
{
  if (this->NbNodes()!=other->NbNodes())
    return Standard_False;
  Standard_Integer n = this->NbNodes();
  const Standard_Integer *c1 = (Standard_Integer *)this->GetConnections();
  const Standard_Integer *c2 = (Standard_Integer *)other->GetConnections();
  if (*c1 != *c2)
    return Standard_False;

  n--;
  c1++;
  c2++;

  for (;n--; c1++,c2++) {
    if (*c1 != *c2)
      return Standard_False;
  }

  return Standard_True;
}

//=======================================================================
//function : IsNodeInElement
//purpose  : 
//=======================================================================

Standard_Boolean Mesh_Element::IsNodeInElement(const Standard_Integer idnode) const
{
  if (idnode < GetConnection(1))
    return Standard_False;

  const Standard_Integer *c = (Standard_Integer *)this->GetConnections();
  Standard_Integer n = myNbNodes;

  for (;n--; c++) {
    if (*c == idnode)
      return Standard_True;
  }

  return Standard_False;
}

//=======================================================================
//function : InverseElements
//purpose  : 
//=======================================================================

const NCollection_List<Handle(Mesh_Element)>& Mesh_Element::InverseElements() const
{
  static const NCollection_List<Handle(Mesh_Element)> empty;
  return empty;
}

//=======================================================================
//function : SetNormal
//purpose  : 
//=======================================================================

void Mesh_Element::SetNormal(const Standard_Integer rank,
                             const Standard_Real vx,
                             const Standard_Real vy,
                             const Standard_Real vz)
{
  if (rank > 0 && rank <= NbNodes()) {
    Mesh_Direction * aNormals = reinterpret_cast<Mesh_Direction *>(myNormals);
    if (!aNormals) {
      myNormals = Standard::Allocate (NbNodes() * sizeof(Mesh_Direction));
      aNormals = reinterpret_cast<Mesh_Direction *> (myNormals);
      for (Standard_Integer i = 0; i < NbNodes(); i++)
        aNormals[i].Clear();
    }
    aNormals[rank-1].Set (vx, vy, vz);
  }
}

//=======================================================================
//function : ClearNormals
//purpose  : 
//=======================================================================

void Mesh_Element::ClearNormal(const Standard_Integer rank)
{
  if (myNormals) {
    if (rank <= 0)
      Standard::Free (myNormals);
    else if (rank <= NbNodes()) {
      Mesh_Direction * aNormal =
        (reinterpret_cast<Mesh_Direction * const>(myNormals)) + rank-1;
      aNormal->Clear();
    }
  }
}

//=======================================================================
//function : IsNormalDefined
//purpose  : 
//=======================================================================

Standard_Boolean Mesh_Element::IsNormalDefined(const Standard_Integer rank) const
{
  if (myNormals) {
    const Mesh_Direction * const aNormals =
      reinterpret_cast<const Mesh_Direction * const> (myNormals);
    // test for 0 vector
    if (rank > 0)
      return (rank <= NbNodes() && !aNormals[rank-1].IsNull());

    for (Standard_Integer i = 0; i < NbNodes(); i++)
      if (!aNormals[i].IsNull())
        return Standard_True;
  }
  return Standard_False;
}

//=======================================================================
//function : GetNormal
//purpose  : 
//=======================================================================

gp_Dir Mesh_Element::GetNormal(const Standard_Integer rank) const
{
  gp_Dir aResultDir;
  if (myNormals && rank > 0 && rank <= NbNodes()) {
    const Mesh_Direction * aNormal =
      (reinterpret_cast<const Mesh_Direction * const>(myNormals)) + rank-1;
    Standard_Boolean ok = aNormal->Get(aResultDir);
    // test for 0 vector
    gp_VectorWithNullMagnitude_Raise_if(!ok,"Mesh_Element::GetNormal : normal is not defined");
    (void)ok; // avoid compiler warning in Release mode
  }
  return aResultDir;
}

//=======================================================================
//function : GetNDirection
//purpose  : 
//=======================================================================

Mesh_Direction Mesh_Element::GetNDirection(const Standard_Integer rank) const
{
  return (!myNormals || rank <= 0 || rank > NbNodes()) ?
    Mesh_Direction() :
    reinterpret_cast<Mesh_Direction * const>(myNormals) [rank-1];
}

//=======================================================================
//function : Print
//purpose  : 
//=======================================================================

void Mesh_Element::Print(Standard_OStream& OS) const
{
  OS << "dump of mesh element" << endl;
}

Standard_OStream& operator << (Standard_OStream& OS, const Handle(Mesh_Element)& ME)
{
  ME->Print(OS);
  return OS;
}
