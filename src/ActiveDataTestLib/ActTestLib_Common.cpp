//-----------------------------------------------------------------------------
// Created on: April 2012
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
