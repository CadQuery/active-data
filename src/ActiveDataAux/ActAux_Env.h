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

#ifndef ActAux_Env_HeaderFile
#define ActAux_Env_HeaderFile

// Win includes
#include <windows.h>

// ActAux includes
#include <ActAux.h>

#define BUFSIZE 1000

//! Auxiliary functions.
class ActAux_Env
{
public:
  //---------------------------------------------------------------------------
  // Environment

  //! Returns value of ACT_DATA environment variable. This variable is used to
  //! refer to the directory containing all data files playing as inputs for
  //! unit tests.
  //! \return value of ACT_DATA variable.
  static std::string ActData()
  {
    return GetVariable("AD_DATA");
  }

  //! Returns value of ACT_TEST_DUMPING environment variable. This variable is
  //! used to refer to the directory containing all temporary files utilized by
  //! unit tests.
  //! \return value of ACT_TEST_DUMPING variable.
  static std::string ActDumping()
  {
    return GetVariable("AD_TEST_DUMP");
  }

  //! Returns value of ACT_TEST_DESCR environment variable. This variable is used
  //! to refer to the directory containing all temporary files utilized by unit
  //! tests.
  //! \return value of ACT_TEST_DESCR variable.
  static std::string ActDescr()
  {
    return GetVariable("AD_TEST_DESCR");
  }

  //! Returns value of the environment variable with the passed name.
  //! \param VarName [in] variable name.
  //! \return value of the variable.
  static std::string GetVariable(const char* VarName)
  {
    TCHAR chNewEnv[BUFSIZE];
    GetEnvironmentVariable(VarName, chNewEnv, BUFSIZE);
    return chNewEnv;
  }

};

#endif
