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

#ifndef Mesh_MeshEdge_HeaderFile
#define Mesh_MeshEdge_HeaderFile

// Mesh includes
#include <Mesh_Element.h>

class ActData_Mesh;

DEFINE_STANDARD_HANDLE(Mesh_Edge, Mesh_Element)

class Mesh_Edge : public Mesh_Element
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(Mesh_Edge, Mesh_Element)

public:

  Mesh_Edge(const Standard_Integer ID, const Standard_Integer idnode1, const Standard_Integer idnode2);

  //! Query the Mesh object holding this element
  ActData_Mesh* GetMesh() const Standard_OVERRIDE;

  ActData_EXPORT Standard_Integer GetKey() const Standard_OVERRIDE;

  Standard_Address GetConnections() const Standard_OVERRIDE;

  Standard_Integer GetConnection (const Standard_Integer rank) const Standard_OVERRIDE;

  virtual Standard_Integer NbEdges() const Standard_OVERRIDE;

  //! returns the idnodes of this edge. rank is ignored.
  virtual void GetEdgeDefinedByNodes (const Standard_Integer rank, Standard_Integer& idnode1, Standard_Integer& idnode2) const Standard_OVERRIDE;

  ActData_EXPORT void Print (Standard_OStream& OS) const Standard_OVERRIDE;

  //! return the mesh element type
  Mesh_ElementType GetType() const Standard_OVERRIDE;

  //! creates a copy of me
  virtual Handle(Mesh_Element) Copy (const Standard_Integer theID) const Standard_OVERRIDE;

friend class ActData_Mesh;


private:

  ActData_EXPORT void SetConnections (const Standard_Integer idnode1, const Standard_Integer idnode2);

  ActData_Mesh* myMesh;
  Standard_Integer myNodes[2];


};


//=======================================================================
//function : Mesh_Edge
//purpose  : 
//=======================================================================

inline Mesh_Edge::Mesh_Edge(const Standard_Integer ID,
                                      const Standard_Integer idnode1, 
                                      const Standard_Integer idnode2)
  : Mesh_Element (ID, 2),
    myMesh            (0L)
{
  SetConnections(idnode1,idnode2);
}

//=======================================================================
//function : GetMesh
//purpose  : 
//=======================================================================

inline ActData_Mesh * Mesh_Edge::GetMesh () const
{
  return myMesh;
}

//=======================================================================
//function : GetConnections
//purpose  : 
//           
//=======================================================================

inline Standard_Address Mesh_Edge::GetConnections() const
{
  return (Standard_Address)&myNodes;
}

//=======================================================================
//function : GetConnection
//purpose  : 
//           
//=======================================================================

inline Standard_Integer Mesh_Edge::GetConnection(const Standard_Integer rank) const
{
  return myNodes[rank-1];
}

//=======================================================================
//function : NbEdges
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Edge::NbEdges() const
{
  return 1;
}

//=======================================================================
//function : GetEdgeDefinedByNodes
//purpose  : 
//=======================================================================

inline void Mesh_Edge::GetEdgeDefinedByNodes(const Standard_Integer /*rank*/, 
                                                  Standard_Integer& idnode1,
                                                  Standard_Integer& idnode2) const
{
  idnode1 = myNodes[0];
  idnode2 = myNodes[1];
}

//=======================================================================
//function : GetType
//purpose  :
//=======================================================================

inline Mesh_ElementType Mesh_Edge::GetType() const
{
  return Mesh_ET_Edge;
}

//=======================================================================
//function : Copy
//purpose  : creates a copy of me
//=======================================================================

inline Handle(Mesh_Element) Mesh_Edge::Copy(const Standard_Integer theID) const
{
  return new Mesh_Edge(theID, myNodes[0], myNodes[1]);
}

#endif
