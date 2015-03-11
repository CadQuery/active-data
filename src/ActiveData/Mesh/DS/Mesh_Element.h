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

#ifndef Mesh_Element_HeaderFile
#define Mesh_Element_HeaderFile

// Mesh includes
#include <Mesh_Direction.h>
#include <Mesh_ElementType.h>
#include <Mesh_Object.h>

// OCCT includes
#include <NCollection_IndexedMap.hxx>
#include <NCollection_List.hxx>
#include <NCollection_Map.hxx>
#include <NCollection_Vector.hxx>

class ActData_Mesh;

DEFINE_STANDARD_HANDLE(Mesh_Element, Mesh_Object)

//-----------------------------------------------------------------------------

//! \ingroup AD_DF
//!
//! Convenience type definition for linked list.
typedef NCollection_List<Handle(Mesh_Element)> Mesh_ListOfElements;

//-----------------------------------------------------------------------------

//! \ingroup AD_DF
//!
//! Base class for all mesh elements.
class Mesh_Element : public Mesh_Object
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(Mesh_Element, Mesh_Object)

public:

  class Hasher
  {
  public:

    //! Returns a HasCode value  for  the  Key <K>  in the
    //! range 0..Upper.
    inline static int HashCode(const Handle(Mesh_Element)& ME, const int Upper)
    {
      return ME->HashCode(Upper);
    }

    //! Returns True  when the two  keys are the same. Two
    //! same  keys  must   have  the  same  hashcode,  the
    //! contrary is not necessary.
    inline static unsigned IsEqual(const Handle(Mesh_Element)& ME1, const Handle(Mesh_Element)& ME2)
    {
      return ME1->IsSame(ME2);
    }

  };

  class OrientedHasher
  {
  public:

    //! Returns a HasCode value  for  the  Key <K>  in the
    //! range 0..Upper.
    inline static int HashCode(const Handle(Mesh_Element)& ME, const int Upper)
    {
      return ME->HashCode(Upper);
    }

    //! Returns True  when the two  keys are the same. Two
    //! same  keys  must   have  the  same  hashcode,  the
    //! contrary is not necessary.
    inline static unsigned IsEqual(const Handle(Mesh_Element)& ME1, const Handle(Mesh_Element)& ME2)
    {
      return ME1->IsEqual(ME2);
    }

  };

public:

  //! Destructor.
  void Destruct();

  ~Mesh_Element()
  {
    Destruct();
  }

  //! Returns a hashed value denoting <me>. This value is in
  //! the range 1..<Upper>.
  ActData_EXPORT Standard_Integer HashCode (const Standard_Integer Upper) const;

  //! Returns True if two mesh elements are same but not
  //! necessary the same orientation
  ActData_EXPORT Standard_Boolean IsSame (const Handle(Mesh_Element)& other) const;

  //! Returns True if  two mesh  elements are  same and
  //! have same orientation
  ActData_EXPORT Standard_Boolean IsEqual (const Handle(Mesh_Element)& other) const;

  //! returns true or false if idnode is in the list of the
  //! direct connections
  ActData_EXPORT Standard_Boolean IsNodeInElement (const Standard_Integer idnode) const;
  
  //! returns the idnodes of the ith edge (rank) of the element.
  //! rank must be comprised between 1 and NbEdges included.
  ActData_EXPORT virtual void GetEdgeDefinedByNodes (const Standard_Integer rank, Standard_Integer& idnode1, Standard_Integer& idnode2) const;

  //! returns the idnodes of the ith face (rank) of the element.
  //! rank must be comprised between 1 and NbFaces included.
  ActData_EXPORT virtual void GetFaceDefinedByNodes (const Standard_Integer rank, const Standard_Address idnode, Standard_Integer& idface) const;

  ActData_EXPORT virtual Standard_Address GetConnections() const;

  ActData_EXPORT virtual Standard_Integer GetConnection (const Standard_Integer rank) const;

  ActData_EXPORT virtual void AddInverseElement (const Handle(Mesh_Element)& ME);

  ActData_EXPORT virtual const Mesh_ListOfElements& InverseElements() const;

  ActData_EXPORT virtual void ClearInverseElements();

  ActData_EXPORT Standard_Integer NbNodes() const;

  ActData_EXPORT virtual Standard_Integer NbEdges() const;

  ActData_EXPORT virtual Standard_Integer NbFaces() const;

  //! returns identifier of the element
  ActData_EXPORT Standard_Integer GetID() const;

  //! returns key for hashcode
  ActData_EXPORT virtual Standard_Integer GetKey() const = 0;

  //! Returns the mesh holding the mesh element. The method is
  //! not defined for Nodes, in this case it returns NULL.
  ActData_EXPORT virtual ActData_Mesh* GetMesh() const;

  //! set the rank-th normal of the element
  ActData_EXPORT virtual void SetNormal (const Standard_Integer rank, const Standard_Real vx, const Standard_Real vy, const Standard_Real vz);

  //! set the rank-th normal of the element
  ActData_EXPORT virtual void SetNormal (const Standard_Integer rank, const gp_Vec& v);

  //! unset (destroy) normal(s) of all ranks / single rank.
  //! If default value (0) is passed for 'rank', all normals are
  //! cleared. Otherwise the rank-th normal is cleared.
  ActData_EXPORT void ClearNormal (const Standard_Integer rank = 0);

  //! returns TRUE if mesh element has computed normal(s).
  //! If default value (0) is passed for 'rank', the method returns
  //! True if there is at least one valid normal stored for element
  //! nodes. If rank > 0, then True is returned if the normal at that
  //! rank exists.
  ActData_EXPORT Standard_Boolean IsNormalDefined (const Standard_Integer rank = 0) const;

  //! get the rank-th normal of the element. If the normal is not
  //! defined (represented internally by zero vector)
  //! if normals are not defined
  ActData_EXPORT virtual gp_Dir GetNormal (const Standard_Integer rank) const;

  //! get the rank-th normal direction of the element. If the rank is
  //! irrelevant or if the normal is not defined, returns an empty
  //! direction. No exception is raised, so this method does not need
  //! a previous call of 'IsNormalDefined'
  ActData_EXPORT Mesh_Direction GetNDirection (const Standard_Integer rank) const;

  ActData_EXPORT virtual void Print (Standard_OStream& OS) const;

friend ActData_EXPORT Standard_OStream& operator << (Standard_OStream& OS, const Handle(Mesh_Element)& );

  //! return the mesh element type
  ActData_EXPORT virtual Mesh_ElementType GetType() const = 0;

  //! creates a copy of me
  ActData_EXPORT virtual Handle(Mesh_Element) Copy (const Standard_Integer theID) const = 0;

protected:

  Mesh_Element(const Standard_Integer ID, const Standard_Integer NbConnections);

  Standard_Integer myID;
  Standard_Integer myNbNodes;


private:

  void* myNormals;

};

//-----------------------------------------------------------------------------

//! \ingroup AD_DF
//!
//! Convenience type definition for indexed map of non-oriented elements.
typedef NCollection_IndexedMap<Handle(Mesh_Element), Mesh_Element::Hasher> Mesh_IndexedMapOfElements;

//! \ingroup AD_DF
//!
//! Convenience type definition for map of non-oriented elements.
typedef NCollection_Map<Handle(Mesh_Element), Mesh_Element::Hasher> Mesh_MapOfElements;

//! \ingroup AD_DF
//!
//! Convenience type definition for indexed map of oriented elements.
typedef NCollection_IndexedMap<Handle(Mesh_Element), Mesh_Element::OrientedHasher> Mesh_IndexedMapOfOrientedElements;

//! \ingroup AD_DF
//!
//! Convenience type definition for map of oriented elements.
typedef NCollection_Map<Handle(Mesh_Element), Mesh_Element::OrientedHasher> Mesh_MapOfOrientedElements;

//! \ingroup AD_DF
//!
//! Convenience type definition for vector.
typedef NCollection_Vector<Handle(Mesh_Element)> Mesh_VectorOfElements;

#endif
