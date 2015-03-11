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

// Own include
#include <Mesh_Direction.h>

// OCCT includes
#include <gp_Dir.hxx>
#include <Precision.hxx>

inline Standard_Integer _REPACK (const Standard_Real aValue) {
  return Standard_Integer(aValue * Standard_Real(IntegerLast()-1) + 0.5);
}

inline Standard_Real _UNPACK (const Standard_Integer iValue) {
  return Standard_Real(iValue) / Standard_Real(IntegerLast() - 1);
}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================

void Mesh_Direction::Set (const Standard_Real theX,
                           const Standard_Real theY,
                           const Standard_Real theZ)
{
  const gp_Dir aDir (theX, theY, theZ);   // normalize
  myCoord[0] = _REPACK(aDir.X());
  myCoord[1] = _REPACK(aDir.Y());
  myCoord[2] = _REPACK(aDir.Z());
}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================

void Mesh_Direction::Set (const gp_XYZ& theXYZ)
{
  const gp_Dir aDir (theXYZ);   // normalize
  myCoord[0] = _REPACK(aDir.X());
  myCoord[1] = _REPACK(aDir.Y());
  myCoord[2] = _REPACK(aDir.Z());
}

//=======================================================================
//function : Get
//purpose  : 
//=======================================================================

Standard_Boolean Mesh_Direction::Get (gp_Dir& outDir) const
{
  if ((myCoord[0] | myCoord[1] | myCoord[2]) != 0) {
    outDir.SetCoord (_UNPACK(myCoord[0]),
                     _UNPACK(myCoord[1]),
                     _UNPACK(myCoord[2]));
    return Standard_True;
  }
  return Standard_False;
}
