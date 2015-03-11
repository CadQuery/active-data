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

#ifndef ActTestLib_Common_HeaderFile
#define ActTestLib_Common_HeaderFile

// ACT Unit Test Suite includes
#include <ActTestLib.h>

// ACT algorithmic collection includes
#include <ActAux_Common.h>

// OCCT includes
#include <TopoDS_Shape.hxx>

//! Auxiliary data types and functions for any test suite.
namespace ActTestLib_Common
{
  ActTestLib_EXPORT TopoDS_Shape
    RandomShape();

  ActTestLib_EXPORT Standard_Integer
    RandomInteger();

  ActTestLib_EXPORT Standard_Boolean
    RandomBoolean();

  ActTestLib_EXPORT Standard_Real
    RandomReal();

  ActTestLib_EXPORT Handle(HIntArray)
    RandomIntegerArray(const Standard_Integer theLower,
                       const Standard_Integer theUpper);

  ActTestLib_EXPORT Handle(HBoolArray)
    RandomBooleanArray(const Standard_Integer theLower,
                       const Standard_Integer theUpper);

  ActTestLib_EXPORT Handle(HRealArray)
    RandomRealArray(const Standard_Integer theLower,
                    const Standard_Integer theUpper);

  ActTestLib_EXPORT Standard_Boolean
    FuzzyCompare(const Standard_Real val1,
                 const Standard_Real val2,
                 const Standard_Real diff_percent,
                 const Standard_Real resolution = 1.0e-4);
};

#endif
