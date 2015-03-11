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

// Own include
#include <ActTestLib_Common.h>

// OCCT includes
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>

//! Returns "some topological shape" for you. Useful if you do not care
//! of the actual topological data but do need to have something valid.
//! \return OCCT topological shape.
TopoDS_Shape ActTestLib_Common::RandomShape()
{
  Standard_Integer RAND_INDX = rand() % 10;
  TopoDS_Shape aResult;
  switch ( RAND_INDX )
  {
    case 0:
      aResult = BRepPrimAPI_MakeBox(100, 100, 100);
      break;
    case 1:
      aResult = BRepPrimAPI_MakeBox(5, 20, 40);
      break;
    case 2:
      aResult = BRepPrimAPI_MakeCone(10, 5, 10);
      break;
    case 3:
      aResult = BRepPrimAPI_MakeCone(5, 25, 20);
      break;
    case 4:
      aResult = BRepPrimAPI_MakeCylinder(10, 20);
      break;
    case 5:
      aResult = BRepPrimAPI_MakeSphere(10, 2*M_PI / 3);
      break;
    case 6:
      aResult = BRepPrimAPI_MakeSphere(10, 7*M_PI / 8);
      break;
    case 7:
      aResult = BRepPrimAPI_MakeTorus(5, 10);
      break;
    case 8:
      aResult = BRepPrimAPI_MakeTorus(10, 15, M_PI / 3);
      break;
    case 9:
      aResult = BRepPrimAPI_MakeTorus(10, 15, M_PI / 2);
      break;
  }
  return aResult;
}

//! Returns "some Boolean value" for you.
//! \return Boolean value.
Standard_Boolean ActTestLib_Common::RandomBoolean()
{
  Standard_Integer RAND_INDX = rand() % 10;

  if ( RAND_INDX < 5 )
    return Standard_True;

  return Standard_False;
}

//! Returns "some integer value" for you.
//! \return integer value.
Standard_Integer ActTestLib_Common::RandomInteger()
{
  Standard_Integer RAND_INDX = rand() % 10;
  return RAND_INDX;
}

//! Returns "some real value" for you.
//! \return real value.
Standard_Real ActTestLib_Common::RandomReal()
{
  Standard_Integer RAND_INDX = rand() % 10;
  Standard_Real aResult = RAND_INDX * 1.5;
  return aResult;
}

//! Returns "some integer array" for you.
//! \param theLower [in] lower index.
//! \param theUpper [in] upper index.
//! \return integer array.
Handle(HIntArray) ActTestLib_Common::RandomIntegerArray(const Standard_Integer theLower,
                                                        const Standard_Integer theUpper)
{
  Handle(HIntArray) aResArr = new HIntArray(theLower, theUpper);
  for ( Standard_Integer i = theLower; i <= theUpper; ++i )
    aResArr->SetValue( i, RandomInteger() );

  return aResArr;
}

//! Returns "some Boolean array" for you.
//! \param theLower [in] lower index.
//! \param theUpper [in] upper index.
//! \return Boolean array.
Handle(HBoolArray) ActTestLib_Common::RandomBooleanArray(const Standard_Integer theLower,
                                                         const Standard_Integer theUpper)
{
  Handle(HBoolArray) aResArr = new HBoolArray(theLower, theUpper);
  for ( Standard_Integer i = theLower; i <= theUpper; ++i )
    aResArr->SetValue( i, RandomBoolean() );

  return aResArr;
}

//! Returns "some real array" for you.
//! \param theLower [in] lower index.
//! \param theUpper [in] upper index.
//! \return real array.
Handle(HRealArray) ActTestLib_Common::RandomRealArray(const Standard_Integer theLower,
                                                      const Standard_Integer theUpper)
{
  Handle(HRealArray) aResArr = new HRealArray(theLower, theUpper);
  for ( Standard_Integer i = theLower; i <= theUpper; ++i )
    aResArr->SetValue( i, RandomReal() );

  return aResArr;
}

//! Compares two passed floating point values.
//! \param val1 [in] first value.
//! \param val2 [in] second value.
//! \param diff_percent [in] allowed difference in percentage regarding to
//!        average value.
//! \param resolution [in] resolution for very small numbers (which are
//!        impractical to compare: e.g. 0.0001 is 100% different from
//!        0.0002, but both values are too small to consider this
//!        difference as significant).
//! \return true in case of such fuzzy equality, false -- otherwise.
Standard_Boolean
  ActTestLib_Common::FuzzyCompare(const Standard_Real val1,
                                  const Standard_Real val2,
                                  const Standard_Real diff_percent,
                                  const Standard_Real resolution)
{
  if ( Abs(val1 - val2) < resolution )
    return Standard_True;

  const Standard_Real avg = (val1 + val2)/2.0;
  const Standard_Real actDev = Abs( (val1 - val2)/avg )*100.0;
  return actDev < diff_percent;
}
