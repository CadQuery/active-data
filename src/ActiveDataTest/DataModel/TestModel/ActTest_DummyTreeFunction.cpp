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

// Own include
#include <ActTest_DummyTreeFunction.h>

//-----------------------------------------------------------------------------
// Implementation of Tree Function for testing purposes
//-----------------------------------------------------------------------------

//! Default constructor.
ActTest_DummyTreeFunction::ActTest_DummyTreeFunction()
{}

//! Instantiation routine.
//! \return Tree Function instance.
Handle(ActTest_DummyTreeFunction) ActTest_DummyTreeFunction::Instance()
{
  return new ActTest_DummyTreeFunction();
}

//! Static accessor for the GUID associated with the Tree Function.
//! \return requested GUID.
Standard_CString ActTest_DummyTreeFunction::GUID()
{
  return "A7E0D6DA-AC44-44D8-B9A0-03F0AF6F814B";
}

//! Accessor for the GUID.
//! \return GUID.
Standard_CString ActTest_DummyTreeFunction::GetGUID() const
{
  return GUID();
}

//! Executes the Tree Function.
Standard_Integer
  ActTest_DummyTreeFunction::execute(const Handle(ActAPI_HParameterList)&,
                                     const Handle(ActAPI_HParameterList)&,
                                     const Handle(Standard_Transient)&,
                                     ActAPI_ProgressEntry) const
{
  // Do nothing...
  return 0; // SUCCESS
}

//! Returns signature for validation of INPUT Parameters.
//! \return signature.
ActAPI_ParameterTypeStream
  ActTest_DummyTreeFunction::inputSignature() const
{
  return ActAPI_ParameterTypeStream();
}

//! Returns signature for validation of OUTPUT Parameters.
//! \return signature.
ActAPI_ParameterTypeStream
  ActTest_DummyTreeFunction::outputSignature() const
{
  return ActAPI_ParameterTypeStream();
}
