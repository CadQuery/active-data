//-----------------------------------------------------------------------------
// Created on: June 2012
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

#ifndef ActTest_DummyTreeFunction_HeaderFile
#define ActTest_DummyTreeFunction_HeaderFile

// ACT Unit Test Suite includes
#include <ActTest.h>

// Active Data includes
#include <ActData_BaseTreeFunction.h>

DEFINE_STANDARD_HANDLE(ActTest_DummyTreeFunction, ActData_BaseTreeFunction)

//! \ingroup AD_TEST
//!
//! Dummy Tree Function doing nothing with data.
class ActTest_DummyTreeFunction : public ActData_BaseTreeFunction
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActTest_DummyTreeFunction, ActData_BaseTreeFunction)

public:

  static Handle(ActTest_DummyTreeFunction)
    Instance();

  static Standard_CString
    GUID();

  virtual Standard_CString
    GetGUID() const;

  //! Returns true if this Tree Function is HEAVY, false -- otherwise.
  //! \return always false.
  inline virtual Standard_Boolean IsHeavy() const
  {
    return Standard_False;
  }

private:

  virtual Standard_Integer
    execute(const Handle(ActAPI_HParameterList)&,
            const Handle(ActAPI_HParameterList)&,
            const Handle(Standard_Transient)&,
            ActAPI_ProgressEntry) const;


  virtual ActAPI_ParameterTypeStream
    inputSignature() const;

  virtual ActAPI_ParameterTypeStream
    outputSignature() const;

private:

  ActTest_DummyTreeFunction();

};

#endif
