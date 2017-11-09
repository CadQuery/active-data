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
