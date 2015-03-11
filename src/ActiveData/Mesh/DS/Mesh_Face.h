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

#ifndef _ActData_MeshFace_HeaderFile
#define _ActData_MeshFace_HeaderFile

// Mesh includes
#include <Mesh_Element.h>
#include <Mesh_ElementType.h>

class ActData_Mesh;

DEFINE_STANDARD_HANDLE(Mesh_Face, Mesh_Element)

class Mesh_Face : public Mesh_Element
{

public:


  //! Query the Mesh object holding this element
  ActData_Mesh* GetMesh() const Standard_OVERRIDE;
  
    virtual Standard_Integer NbEdges() const Standard_OVERRIDE;
  
    virtual Standard_Integer NbFaces() const Standard_OVERRIDE;
  
  //! returns the idnodes of this face. rank is ignored.
  ActData_EXPORT virtual void GetFaceDefinedByNodes (const Standard_Integer rank, const Standard_Address idnode, Standard_Integer& nb) const Standard_OVERRIDE;
  
  ActData_EXPORT virtual void Print (Standard_OStream& OS) const Standard_OVERRIDE;
  
  //! return the mesh element type
    Mesh_ElementType GetType() const Standard_OVERRIDE;


friend class ActData_Mesh;


  DEFINE_STANDARD_RTTI_INLINE(Mesh_Face,Mesh_Element)

protected:

  
    Mesh_Face(const Standard_Integer ID, const Standard_Integer NbConnections);



private:


  ActData_Mesh* myMesh;


};


//=======================================================================
//function : Mesh_Face
//purpose  : 
//=======================================================================

inline Mesh_Face::Mesh_Face (const Standard_Integer ID,
                                       const Standard_Integer nb)
  : Mesh_Element (ID, nb),
    myMesh            (0L)
{}

//=======================================================================
//function : GetMesh
//purpose  : 
//=======================================================================

inline ActData_Mesh * Mesh_Face::GetMesh () const
{
  return myMesh;
}

//=======================================================================
//function : NbEdges
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Face::NbEdges() const
{
  return myNbNodes;
}

//=======================================================================
//function : NbFaces
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Face::NbFaces() const
{
  return 1;
}

//=======================================================================
//function : GetType
//purpose  :
//=======================================================================

inline Mesh_ElementType Mesh_Face::GetType() const
{
  return Mesh_ET_Face;
}

#endif
