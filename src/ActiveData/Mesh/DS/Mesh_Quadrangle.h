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

#ifndef Mesh_MeshQuadrangle_HeaderFile
#define Mesh_MeshQuadrangle_HeaderFile

// Mesh includes
#include <Mesh_Face.h>

DEFINE_STANDARD_HANDLE(Mesh_Quadrangle, Mesh_Face)

class Mesh_Quadrangle : public Mesh_Face
{

public:

  
  //! constructor for a quandrangle
    Mesh_Quadrangle(const Standard_Integer ID, const Standard_Integer idnode1, const Standard_Integer idnode2, const Standard_Integer idnode3, const Standard_Integer idnode4);
  
  ActData_EXPORT Standard_Integer GetKey() const Standard_OVERRIDE;
  
  //! returns the idnodes of the ith edge (rank) of the face
  //! rank must be comprised between 1 and myNbConnections included.
    void GetEdgeDefinedByNodes (const Standard_Integer rank, Standard_Integer& idnode1, Standard_Integer& idnode2) const Standard_OVERRIDE;
  
    Standard_Address GetConnections() const Standard_OVERRIDE;
  
    Standard_Integer GetConnection (const Standard_Integer rank) const Standard_OVERRIDE;
  
  //! creates a copy of me
    virtual Handle(Mesh_Element) Copy (const Standard_Integer theID) const Standard_OVERRIDE;




  DEFINE_STANDARD_RTTI_INLINE(Mesh_Quadrangle,Mesh_Face)

protected:




private:

  
  ActData_EXPORT void SetConnections (const Standard_Integer idnode1, const Standard_Integer idnode2, const Standard_Integer idnode3, const Standard_Integer idnode4);

  Standard_Integer myNodes[4];


};


//=======================================================================
//function : Mesh_Quadrangle
//purpose  : 
//=======================================================================

inline Mesh_Quadrangle::Mesh_Quadrangle(const Standard_Integer ID,
                                                  const Standard_Integer idnode1, 
                                                  const Standard_Integer idnode2, 
                                                  const Standard_Integer idnode3,
                                                  const Standard_Integer idnode4)
  : Mesh_Face (ID, 4)
{
  SetConnections(idnode1,idnode2,idnode3,idnode4);
}

//=======================================================================
//function : GetConnections
//purpose  : 
//=======================================================================

inline Standard_Address Mesh_Quadrangle::GetConnections() const
{
  return (Standard_Address)&myNodes;
}

//=======================================================================
//function : GetConnection
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Quadrangle::GetConnection(const Standard_Integer rank) const
{
  return myNodes[rank-1];
}

//=======================================================================
//function : GetEdgeDefinedByNodes
//purpose  : 
//=======================================================================

inline void Mesh_Quadrangle::GetEdgeDefinedByNodes(const Standard_Integer rank, 
                                                        Standard_Integer& idnode1,
                                                        Standard_Integer& idnode2) const
{
  idnode1 = myNodes[rank-1];
  idnode2 = myNodes[rank % myNbNodes];
}

//=======================================================================
//function : Copy
//purpose  : creates a copy of me
//=======================================================================

inline Handle(Mesh_Element) Mesh_Quadrangle::Copy(const Standard_Integer theID) const
{
  return new Mesh_Quadrangle(theID, myNodes[0], myNodes[1], myNodes[2], myNodes[3]);
}

#endif // _ActData_MeshQuadrangle_HeaderFile
