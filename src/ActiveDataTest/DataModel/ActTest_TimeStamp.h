//-----------------------------------------------------------------------------
// Created on: April 2012
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//    * Neither the name of OPEN CASCADE SAS nor the
//      names of all contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Web: http://dev.opencascade.org
//-----------------------------------------------------------------------------

#ifndef ActTest_TimeStamp_HeaderFile
#define ActTest_TimeStamp_HeaderFile

// Active Data unit tests
#include <ActTest_DataFramework.h>

// ACT Algorithmic layer includes
#include <ActAux_TimeStamp.h>

//! \ingroup AD_TEST
//!
//! Test suite for Active Data.
//! This class performs unit testing of TimeStamp class.
class ActTest_TimeStamp : public ActTest_DataFramework
{
public:

  //! Returns Test Case ID.
  //! \return ID of the Test Case.
  static int ID()
  {
    return CaseID_TimeStamp;
  }

  //! Returns filename for the description.
  //! \return filename for the description of the Test Case.
  static std::string DescriptionFn()
  {
    return "ActTest_TimeStamp";
  }

  //! Returns Test Case description directory.
  //! \return description directory for the Test Case.
  static std::string DescriptionDir()
  {
    return "Tools";
  }

  //! Returns pointers to the Test Functions to launch.
  //! \param functions [out] output collection of pointers.
  static void Functions(ActiveDataTestFunctions& functions)
  {
    functions << &cumulTest
              << &accessMTime;
  }

// Test functions:
private:

  static bool cumulTest   (const int funcID);
  static bool accessMTime (const int funcID);

};

#endif
