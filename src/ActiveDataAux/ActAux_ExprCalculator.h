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

#ifndef ActAux_ExprCalculator_HeaderFile
#define ActAux_ExprCalculator_HeaderFile

// Active Data (auxiliary) includes
#include <ActAux_Common.h>

// Active Data (API) includes
#include <ActAPI_IProgressNotifier.h>
#include <ActAPI_Variables.h>

// OCCT includes
#include <NCollection_Handle.hxx>

DEFINE_STANDARD_HANDLE(ActAux_ExprCalculator, Standard_Transient)

//! \ingroup AD_ALGO
//!
//! Calculates mathematical expressions passing the list of variables to apply.
class ActAux_ExprCalculator : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAux_ExprCalculator, Standard_Transient)

public:

  virtual Standard_Real
    CalcAsReal(const TCollection_AsciiString& theExpr,
               const ActAPI_VariableList& theVars,
               TCollection_AsciiString& theError,
               TCollection_AsciiString& theErrorArg,
               Standard_Integer& theOffset,
               ActAPI_ProgressEntry PEntry = 0) = 0;

  virtual Standard_Boolean
    CalcAsBool(const TCollection_AsciiString& theExpr,
               const ActAPI_VariableList& theVars,
               TCollection_AsciiString& theError,
               TCollection_AsciiString& theErrorArg,
               Standard_Integer& theOffset,
               ActAPI_ProgressEntry PEntry = 0) = 0;

};

#endif
