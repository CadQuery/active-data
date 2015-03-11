//-----------------------------------------------------------------------------
// Created on: April 2012
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

#ifndef ActAux_ShapeFactory_HeaderFile
#define ActAux_ShapeFactory_HeaderFile

// Active Data (auxiliary) includes
#include <ActAux_Common.h>

//! \ingroup ALGO
//!
//! Provides a set of handy methods constructing different OCCT
//! topological shapes.
class ActAux_ShapeFactory
{
// Primitives:
public:

  ActAux_EXPORT static TopoDS_Shape
    Box(const Standard_Real DX, const Standard_Real DY, const Standard_Real DZ);

  ActAux_EXPORT static TopoDS_Shape
    Sphere(const Standard_Real R);

  ActAux_EXPORT static TopoDS_Shape
    Sphere(const Standard_Real R, const Standard_Real A1, const Standard_Real A2);

  ActAux_EXPORT static TopoDS_Shape
    Cone(const Standard_Real R1, const Standard_Real R2, const Standard_Real H);

  ActAux_EXPORT static TopoDS_Shape
    Cylinder(const Standard_Real R, const Standard_Real H);

  ActAux_EXPORT static TopoDS_Shape
    Torus(const Standard_Real R1, const Standard_Real R2);

  ActAux_EXPORT static TopoDS_Shape
    Torus(const Standard_Real R1, const Standard_Real R2,
          const Standard_Real A1, const Standard_Real A2);

  ActAux_EXPORT static TopoDS_Shape
    MakeTransform(const TopoDS_Shape& theShape,
                  const gp_Trsf& theTrsf,
                  const Standard_Boolean doCopy);

private:

  ActAux_ShapeFactory(); //!< Prohibited.
  ActAux_ShapeFactory(const ActAux_ShapeFactory&); //!< Prohibited.

};

#endif
