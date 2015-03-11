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

#ifndef Mesh_MapOfMeshElement_HeaderFile
#define Mesh_MapOfMeshElement_HeaderFile

// Mesh includes
#include <Mesh_Element.h>

//! Redefinition/definition  of methods of Map from NCollection
class Mesh_MapOfMeshElement : public Mesh_MapOfElements
{
public:

  DEFINE_STANDARD_ALLOC
  
  //! Creates   a Map with  <NbBuckets> buckets. Without
  //! arguments the map is automatically dimensioned.
  Mesh_MapOfMeshElement(const Standard_Integer NbBuckets = 1)
  : Mesh_MapOfElements( NbBuckets )
  {}
  
  //! Returns  the Item stored  with the Key  <K> in the Map.
  Standard_EXPORT const Handle(Mesh_Element)& Find (const Handle(Mesh_Element)& K) const;
  const Handle(Mesh_Element)& operator() (const Handle(Mesh_Element)& K) const
  { return Find(K); }
  
  //! Returns the  Item stored with  the Key  <K> in the
  //! Map. This Item can be   modified with  the  syntax
  //! aMap(K) = newItem;
  Standard_EXPORT Handle(Mesh_Element)& ChangeFind (const Handle(Mesh_Element)& K);
  Handle(Mesh_Element)& operator() (const Handle(Mesh_Element)& K)
  { return ChangeFind(K); }
  
  //! Returns  the Item stored  with the ID in the Map.
  Standard_EXPORT const Handle(Mesh_Element)& FindID (const Standard_Integer ID) const;
  const Handle(Mesh_Element)& operator() (const Standard_Integer ID) const
  { return FindID(ID); }
  
  //! Returns True  if the ID is stored  in the
  //! map <me>.
  Standard_EXPORT Standard_Boolean ContainsID (const Standard_Integer ID) const;
};

#endif
