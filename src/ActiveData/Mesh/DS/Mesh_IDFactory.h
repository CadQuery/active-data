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
