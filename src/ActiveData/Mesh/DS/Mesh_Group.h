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

#ifndef Mesh_Group_HeaderFile
#define Mesh_Group_HeaderFile

// Mesh includes
#include <Mesh_Element.h>

class ActData_Mesh;

DEFINE_STANDARD_HANDLE(Mesh_Group, Mesh_Object)

//-----------------------------------------------------------------------------

typedef NCollection_List<Handle(Mesh_Group)> Mesh_ListOfGroups;

//-----------------------------------------------------------------------------

class Mesh_Group : public Mesh_Object
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(Mesh_Group, Mesh_Object)

public:

  //! constructor
  Mesh_Group(const Handle(ActData_Mesh)& aMesh);

  //! create a  sub  group.
  //! uses  a private constructor to create an instance of the
  //! subgroup and attach it the parent group.
  ActData_EXPORT Handle(Mesh_Group) AddSubGroup();

  //! remove aGroup from the list of Children
  //! if the subgroup does not belong to this, it returns False
  //! (True otherwise)
  ActData_EXPORT virtual Standard_Boolean RemoveSubGroup (const Handle(Mesh_Group)& aGroup);

  //! remove this from its parent
  //! if this has no parent then it returns False (True otherwise)
  ActData_EXPORT virtual Standard_Boolean RemoveFromParent();

  //! clear the group
  //! once the group is cleared, the type is set to All
  //! but the referenced mesh remains.
  void Clear();

  //! add an element to the group
  ActData_EXPORT void Add (const Handle(Mesh_Element)& ME);

  //! remove an element from the group
  //! raises if the element is not in the group
  ActData_EXPORT void Remove (const Handle(Mesh_Element)& ME);

  //! check if the group is empty
  Standard_Boolean IsEmpty() const;

  //! return numner of elements in the group
  Standard_Integer Extent() const;

  //! return current element type
  //! if the group is empty, returns All
  Mesh_ElementType Type() const;

  //! check if the group contains the mesh element
  Standard_Boolean Contains (const Handle(Mesh_Element)& ME) const;

  //! check if the group contains the mesh element
  const Mesh_MapOfElements& Elements() const;

private:

  //! constructor used internally to create subgroup
  Mesh_Group(const Handle(Mesh_Group)& parent);

  Handle(ActData_Mesh) myMesh;
  Mesh_ElementType     myType;
  Mesh_MapOfElements   myElements;
  Handle(Mesh_Group)   myParent;
  Mesh_ListOfGroups    myChildren;

};


//=======================================================================
//function : Mesh_Group
//purpose  : 
//=======================================================================

inline Mesh_Group::Mesh_Group(const Handle(ActData_Mesh)& aMesh)
  : myMesh(aMesh),myType(Mesh_ET_All)
{
}

//=======================================================================
//function : Mesh_Group
//purpose  : 
//=======================================================================

inline Mesh_Group::Mesh_Group(const Handle(Mesh_Group)& parent)
  : myMesh(parent->myMesh),myType(Mesh_ET_All),myParent(parent)
{
}

//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================

inline void Mesh_Group::Clear()
{
  myElements.Clear();
  myType = Mesh_ET_All;
}

//=======================================================================
//function : IsEmpty
//purpose  : 
//=======================================================================

inline Standard_Boolean Mesh_Group::IsEmpty() const
{
  return myElements.IsEmpty();
}

//=======================================================================
//function : Extent
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Group::Extent() const
{
  return myElements.Extent();
}

//=======================================================================
//function : Type
//purpose  : 
//=======================================================================

inline Mesh_ElementType Mesh_Group::Type() const
{
  return myType;
}

//=======================================================================
//function : Contains
//purpose  : 
//=======================================================================

inline Standard_Boolean Mesh_Group::Contains(const Handle(Mesh_Element)& ME) const
{
  return myElements.Contains(ME);
}

//=======================================================================
//function : Elements
//purpose  : 
//=======================================================================

inline const Mesh_MapOfElements& Mesh_Group::Elements() const
{
  return myElements;
}

#endif // _ActData_MeshGroup_HeaderFile
