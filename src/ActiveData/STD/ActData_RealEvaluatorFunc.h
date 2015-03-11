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

#ifndef ActData_RealEvaluatorFunc_HeaderFile
#define ActData_RealEvaluatorFunc_HeaderFile

// Active Data includes
#include <ActData_BaseTreeFunction.h>
#include <ActData_Common.h>

DEFINE_STANDARD_HANDLE(ActData_RealEvaluatorFunc, ActData_BaseTreeFunction)

//! \ingroup AD_DF
//!
//! Tree Function performing evaluation of mathematical expressions associated with
//! Nodal Parameters of Real & Integer types. Notice, however, that in both
//! cases the Tree Function asks evaluator to return a Real value. If the input
//! Parameter is of an Integer type, the explicit conversion (without any
//! rounding) will be applied.
//!
//! This Tree Function is designed for the following parameterization scheme:
//! <pre>
//! INPUT Parameters:              ________________OPTIONAL_________________
//!                               |                                         |
//! +=======================+     +=============+             +=============+
//! | Target Real Parameter | --> | Var Param 1 | --> ... --> | Var Param N |
//! +=======================+     +=============+             +=============+
//!                               |                                         |
//!                               |__________DEFINED_BY_APPLICATION_________|
//!
//!                              ||
//!                              || 
//!                             _||_  EVALUATION OF PYTHON EXPRESSION
//!                             \  /
//!                              \/
//!
//!                    +=======================+
//! OUTPUT Parameters: | Target Real Parameter |
//!                    +=======================+
//! </pre>
//! This evaluator function is a ready-to-use custom implementation of
//! Tree Function concept dedicated for supporting of Variables mechanism
//! shipped with Active Data.
class ActData_RealEvaluatorFunc : public ActData_BaseTreeFunction
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_RealEvaluatorFunc, ActData_BaseTreeFunction)

public:

  ActData_EXPORT static Handle(ActData_RealEvaluatorFunc)
    Instance();

  ActData_EXPORT virtual Standard_CString
    GetName() const;

  ActData_EXPORT static Standard_CString
    GUID();

  ActData_EXPORT virtual Standard_CString
    GetGUID() const;

  ActData_EXPORT static Standard_Boolean
    IS_HEAVY();

  ActData_EXPORT virtual Standard_Boolean
    IsHeavy() const;

  ActData_EXPORT virtual Standard_Integer
    Priority() const;

private:

  virtual Standard_Integer
    execute(const Handle(ActAPI_HParameterList)& theArgsIN,
            const Handle(ActAPI_HParameterList)& theArgsOUT,
            const Handle(Standard_Transient)& theUserData = NULL,
            ActAPI_ProgressEntry PEntry = NULL) const;

  virtual ActAPI_ParameterTypeStream
    inputSignature() const;

  virtual ActAPI_ParameterTypeStream
    outputSignature() const;

  virtual Standard_Boolean
    validateInput(const Handle(ActAPI_HParameterList)& theArgsIN) const;

private:

  ActData_RealEvaluatorFunc();

};

#endif
