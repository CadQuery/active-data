//-----------------------------------------------------------------------------
// Created on: June 2012
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

#ifndef ActTest_DummyTreeFunction_HeaderFile
#define ActTest_DummyTreeFunction_HeaderFile

// Active Data unit tests
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
