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
