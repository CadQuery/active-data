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

#ifndef ActData_MeshEdgesIterator_HeaderFile
#define ActData_MeshEdgesIterator_HeaderFile

#include <Mesh_ElementsIterator.h>
#include <Mesh_Edge.h>

///  Iterator on mesh edges, as specialisation of the general purpose iterator

class ActData_MeshEdgesIterator : public Mesh_ElementsIterator
{
 public:
  // ---------- PUBLIC METHODS ----------

  /// Empty constructor
  ActData_MeshEdgesIterator () {}

  /// Constructor
  ActData_MeshEdgesIterator (const Handle(ActData_Mesh)& theMesh)
    : Mesh_ElementsIterator (theMesh, Mesh_ET_Edge)
  {}

  /// Query the Value
  Handle(Mesh_Edge) Value () const
  { return Handle(Mesh_Edge)::DownCast(GetValue()); }
};

#endif
