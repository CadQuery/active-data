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

#ifndef Mesh_TypeOfPosition_HeaderFile
#define Mesh_TypeOfPosition_HeaderFile

//! defines the type of position of a node (see Mesh_Position)
//! TOP_UNSPEC   : node position not specfied
//! TOP_3DSPACE  : just a 3d point in space not related
//! to a CAD geometry
//! TOP_VERTEX   : to characterize a node with a CAD vertex
//! TOP_EDGE     : to characterize a node with a CAD edge
//! TOP_FACE     : to characterize a node with a CAD face
enum Mesh_TypeOfPosition
{
  Mesh_TOP_UNSPEC,
  Mesh_TOP_3DSPACE,
  Mesh_TOP_VERTEX,
  Mesh_TOP_EDGE,
  Mesh_TOP_FACE
};

#endif // _ActData_TypeOfPosition_HeaderFile
