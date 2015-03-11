//-----------------------------------------------------------------------------
// Created on: 2012-2015
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
#include <ActAux_ShapeFactory.h>

// OCCT includes
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>

//! Creates BOX solid.
//! \param DX [in] side X.
//! \param DY [in] side Y.
//! \param DZ [in] side Z.
//! \return created solid.
TopoDS_Shape ActAux_ShapeFactory::Box(const Standard_Real DX,
                                      const Standard_Real DY,
                                      const Standard_Real DZ)
{
  return BRepPrimAPI_MakeBox(DX, DY, DZ).Shape();
}

//! Creates SPHERE solid.
//! \param R [in] radius.
//! \return created solid.
TopoDS_Shape ActAux_ShapeFactory::Sphere(const Standard_Real R)
{
  return BRepPrimAPI_MakeSphere(R).Shape();
}

//! Creates SPHERE solid limited by angle variation range.
//! \param R [in] radius.
//! \param A1 [in] first angle value.
//! \param A2 [in] second angle value.
//! \return created solid.
TopoDS_Shape ActAux_ShapeFactory::Sphere(const Standard_Real R,
                                         const Standard_Real A1,
                                         const Standard_Real A2)
{
  return BRepPrimAPI_MakeSphere(R, A1, A2).Shape();
}

//! Creates CONE solid.
//! \param R1 [in] first radius.
//! \param R2 [in] second radius.
//! \param H [in] height.
//! \return created solid.
TopoDS_Shape ActAux_ShapeFactory::Cone(const Standard_Real R1,
                                       const Standard_Real R2,
                                       const Standard_Real H)
{
  return BRepPrimAPI_MakeCone(R1, R2, H).Shape();
}

//! Creates CYLINDER solid.
//! \param R [in] radius.
//! \param H [in] height.
//! \return created solid.
TopoDS_Shape ActAux_ShapeFactory::Cylinder(const Standard_Real R,
                                           const Standard_Real H)
{
  return BRepPrimAPI_MakeCylinder(R, H).Shape();
}

//! Creates TORUS solid.
//! \param R1 [in] first radius.
//! \param R2 [in] second radius.
//! \return created solid.
TopoDS_Shape ActAux_ShapeFactory::Torus(const Standard_Real R1,
                                        const Standard_Real R2)
{
  return BRepPrimAPI_MakeTorus(R1, R2).Shape();
}

//! Creates TORUS solid limited by angle variation range.
//! \param R1 [in] first radius.
//! \param R2 [in] second radius.
//! \param A1 [in] first angle value.
//! \param A2 [in] second angle value.
//! \return created solid.
TopoDS_Shape ActAux_ShapeFactory::Torus(const Standard_Real R1,
                                        const Standard_Real R2,
                                        const Standard_Real A1,
                                        const Standard_Real A2)
{
  return BRepPrimAPI_MakeTorus(R1, R2, A1, A2).Shape();
}

//! Creates a transformed copy of the passed shape.
//! \param theShape [in] shape to copy & transform.
//! \param theTrsf [in] transformation to apply.
//! \param doCopy [in] indicates whether to copy the source shape.
//! \return transformed copy of the passed shape.
TopoDS_Shape ActAux_ShapeFactory::MakeTransform(const TopoDS_Shape& theShape,
                                                const gp_Trsf& theTrsf,
                                                const Standard_Boolean doCopy)
{
  BRepBuilderAPI_Transform aTransformer(theShape, theTrsf, doCopy);
  return aTransformer.Shape();
}
