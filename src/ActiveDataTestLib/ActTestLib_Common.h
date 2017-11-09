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
