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

#ifndef Mesh_IDFactory_HeaderFile
#define Mesh_IDFactory_HeaderFile

// Mesh includes
#include <Mesh_Object.h>

// OCCT includes
#include <NCollection_Vector.hxx>
#include <TColStd_PackedMapOfInteger.hxx>

class Mesh_Element;

DEFINE_STANDARD_HANDLE(Mesh_IDFactory, Mesh_Object)

//! \ingroup AD_DF
//!
//! ID factory for mesh objects.
class Mesh_IDFactory : public Mesh_Object
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(Mesh_IDFactory, Mesh_Object)

public:

  ActData_EXPORT Mesh_IDFactory();

  //! returns a free identifier for mesh from
  //! the pool of ID
  ActData_EXPORT Standard_Integer GetFreeID();

  //! free the ID and give it back to the pool of ID
  ActData_EXPORT void ReleaseID (const Standard_Integer ID);

  //! bind the ID with the mesh element
  //! returns False if the ID is already bound.
  //! In this case the element is not replaced
  ActData_EXPORT Standard_Boolean BindID (const Standard_Integer ID, const Handle(Mesh_Element)& elem);

  //! returns the MeshElement associated with ID
  //! Returns NULL handle the ID is not bound
  ActData_EXPORT Handle(Mesh_Element) MeshElement (const Standard_Integer ID) const;

  //! returns the iterator of the whole collection
  //! of mesh entities
  ActData_EXPORT NCollection_Vector<Handle(Mesh_Element)>::Iterator Iterator() const;

private:

  NCollection_Vector<Handle(Mesh_Element)> myElements;
  TColStd_PackedMapOfInteger               myPoolOfID;
  Standard_Integer                         myMaxID;

};

#endif
