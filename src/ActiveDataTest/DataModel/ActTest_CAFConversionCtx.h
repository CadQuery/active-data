//-----------------------------------------------------------------------------
// Created on: March 2013
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

#ifndef ActTest_CAFConversionCtx_HeaderFile
#define ActTest_CAFConversionCtx_HeaderFile

// ACT Unit Test Suite includes
#include <ActTest_DummyModel.h>
#include <ActTest_StubCNode.h>

// ACT Test Library includes
#include <ActTestLib_Common.h>
#include <ActTestLib_TestCase.h>

// Active Data includes
#include <ActData_CAFConversionCtx.h>

//! \ingroup AD_TEST
//!
//! Test suite for Active Data.
//! This class performs unit testing of CAF Conversion Context tool.
class ActTest_CAFConversionCtx : public ActTestLib_TestCase
{
public:

  //! Returns Test Case ID.
  //! \return ID of the Test Case.
  static int ID()
  {
    return CaseID_CAFConversionCtx;
  }

  //! Returns filename for the description.
  //! \return filename for the description of the Test Case.
  static std::string DescriptionFn()
  {
    return "ActTest_CAFConversionCtx";
  }

  //! Returns Test Case description directory.
  //! \return description directory for the Test Case.
  static std::string DescriptionDir()
  {
    return "Tools";
  }

  //! Returns pointers to the Test Functions to launch.
  //! \param functions [out] output collection of pointers.
  static void Functions(QrTestFunctions& functions)
  {
    functions << &insert_001
              << &insert_002a
              << &insert_002b
              << &insert_002c
              << &insert_002d
              << &insert_002e
              << &insert_002f
              << &insert_002g
              << &insert_002h
              << &insert_002i
              << &insert_002j
              << &insert_002k
              << &insert_003
              << &insert_004
              << &modify_001
              << &modify_002
              << &remove_001
              << &remove_002
              << &remove_003
              << &remove_004
              << &remove_005
              << &complex_001;
  }

// Test functions:
private:

  static bool insert_001  (const int funcID);
  static bool insert_002a (const int funcID);
  static bool insert_002b (const int funcID);
  static bool insert_002c (const int funcID);
  static bool insert_002d (const int funcID);
  static bool insert_002e (const int funcID);
  static bool insert_002f (const int funcID);
  static bool insert_002g (const int funcID);
  static bool insert_002h (const int funcID);
  static bool insert_002i (const int funcID);
  static bool insert_002j (const int funcID);
  static bool insert_002k (const int funcID);
  static bool insert_003  (const int funcID);
  static bool insert_004  (const int funcID);

  static bool modify_001  (const int funcID);
  static bool modify_002  (const int funcID);

  static bool remove_001  (const int funcID);
  static bool remove_002  (const int funcID);
  static bool remove_003  (const int funcID);
  static bool remove_004  (const int funcID);
  static bool remove_005  (const int funcID);

  static bool complex_001 (const int funcID);

private:

  static void init_ABC01(Handle(ActTest_DummyModel)& M,
                         Handle(ActTest_StubCNode)& N);

private:

  static TCollection_AsciiString
    dumpPath();

  static TCollection_AsciiString
    sourcePath();

  static TCollection_AsciiString
    filenameActualDump(const TCollection_AsciiString& theBaseName,
                       const Standard_Integer theIdx);

  static TCollection_AsciiString
    filenameRefDump(const TCollection_AsciiString& theBaseName,
                    const Standard_Integer theIdx);

  static Standard_Boolean
    verifyResults(const TCollection_AsciiString& theActualFn,
                  const TCollection_AsciiString& theRefFn);

  static Handle(ActData_ParameterDTO)
    dtoByType(const ActAPI_ParameterType theType,
              const ActAPI_ParameterGID& theGID);

  static Handle(HRealArray)
    testRealArray(const Standard_Real theMultCoeff);

  static Handle(HIntArray)
    testIntArray(const Standard_Integer theMultCoeff);

  static Handle(HBoolArray)
    testBoolArray();

  static Handle(HStringArray)
    testStringArray(const TCollection_AsciiString& theSuffix);

  static Handle(HComplexArray)
    testComplexArray(const Standard_Real theMultCoeff);

};

#endif
