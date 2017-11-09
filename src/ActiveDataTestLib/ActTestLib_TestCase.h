//-----------------------------------------------------------------------------
// Created on: 11 June 2013
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

#ifndef ActTestLib_TestCase_HeaderFile
#define ActTestLib_TestCase_HeaderFile

// ActTestLib includes
#include <ActTestLib_Macro.h>

// ActAux includes
#include <ActAux.h>

// STD includes
#include <map>
#include <vector>

//-----------------------------------------------------------------------------
// Auxiliary definitions
//-----------------------------------------------------------------------------

#define DEFINE_TEST_VARIABLES \
  ActTestLib_TestCase::StrStrMap ActTestLib_TestCase::m_varExpansion;

//! Pointer to Test Function.
//! Please note that {funcID} should be normally passed by Test Case. The
//! convention is to have {funcID} as 1-based integer number.
typedef bool (*QrTestFunction)(const int funcID);

//! Collection of pointers to Test Functions
class ActiveDataTestFunctions
{
public:

  //! Default constructor.
  ActiveDataTestFunctions() {}

public:

  //! Adds the passed function pointer to the collection of pointers to
  //! Test Functions.
  //! \param funcPtr [in] function pointer to add.
  //! \return this reference for subsequent streaming.
  ActiveDataTestFunctions& operator<<(const QrTestFunction& funcPtr)
  {
    m_testFunctions.push_back(funcPtr);
    return*this;
  }

  //! Returns size of the collection of function pointers.
  //! \return requested size.
  inline size_t Size() const
  {
    return m_testFunctions.size();
  }

  //! Returns function pointer for the given index.
  //! \param idx [in] index of the function pointer to access.
  //! \return requested function pointer.
  const QrTestFunction& Func(const int idx) const
  {
    return m_testFunctions.at(idx);
  }

private:

  //! Internal collection of pointers to Test Functions.
  std::vector<QrTestFunction> m_testFunctions;

};

//-----------------------------------------------------------------------------
// Base class for Test Cases
//-----------------------------------------------------------------------------

//! Base class for Test Cases.
class ActTestLib_TestCase
{
public:

  //! Short-cut for variable expansion maps.
  typedef std::map<std::string, std::string> StrStrMap;

  //! Short-cut for string-string pairs.
  typedef std::pair<std::string, std::string> StrStrPair;

// Verification:
public:

  //! Compares two matrices on exact equaility of their elements in the
  //! given 2-dimensional range. Notice that safety of such comparison is
  //! not guaranteed, so make sure that the compared matrices have equal
  //! dimensions.
  //! \param mx [in] first matrix to compare.
  //! \param mx_ref [in] second matrix to compare.
  //! \param nRows [in] number of rows to compare.
  //! \param nCols [in] number of columns to compare.
  //! \return true in case of equality, false -- otherwise.
  static bool CompareExact(double** mx,
                           double** mx_ref,
                           const int nRows,
                           const int nCols)
  {
    for ( int i = 0; i < nRows; ++i )
      for ( int j = 0; j < nCols; ++j )
        if ( mx[i][j] != mx_ref[i][j] )
          return false;

    return true;
  }

// Expansion of variables:
public:

  //! Expands variable with the given name to the given value.
  //! \param varName [in] variable name.
  //! \param varValue [in] variable value.
  //! \param caseID [in] ID of the Test Case.
  //! \param funcID [in] 1-based ID of Test Function to be used as a namespace
  //!        for its own local variables mapping.
  static void SetVarDescr(const std::string& varName,
                          const std::string& varValue,
                          const int caseID,
                          const int funcID)
  {
    std::string vName = generateVarName(varName, caseID, funcID);

    if ( m_varExpansion.find(vName) != m_varExpansion.end() )
      m_varExpansion.erase(vName);

    m_varExpansion.insert( StrStrPair(vName, varValue) );
  }

  //! Overloaded variable setter for integer values.
  //! \param varName [in] variable name.
  //! \param val [in] variable value.
  //! \param caseID [in] ID of the Test Case.
  //! \param funcID [in] 1-based ID of Test Function to be used as a namespace
  //!        for its own local variables mapping.
  static void SetVarDescr(const std::string& varName,
                          const int val,
                          const int caseID,
                          const int funcID)
  {
    SetVarDescr(varName, ActAux::to_string(val), caseID, funcID);
  }

  //! Overloaded variable setter for real values.
  //! \param varName [in] variable name.
  //! \param val [in] variable value.
  //! \param caseID [in] ID of the Test Case.
  //! \param funcID [in] 1-based ID of Test Function to be used as a namespace
  //!        for its own local variables mapping.
  static void SetVarDescr(const std::string& varName,
                          const double val,
                          const int caseID,
                          const int funcID)
  {
    SetVarDescr(varName, ActAux::to_string(val), caseID, funcID);
  }

  //! Overloaded variable setter for Boolean values.
  //! \param varName [in] variable name.
  //! \param isYes [in] variable value.
  //! \param caseID [in] ID of the Test Case.
  //! \param funcID [in] 1-based ID of Test Function to be used as a namespace
  //!        for its own local variables mapping.
  static void SetVarDescr(const std::string& varName,
                          const bool isYes,
                          const int caseID,
                          const int funcID)
  {
    SetVarDescr(varName, isYes ? std::string("yes") : std::string("no"), caseID, funcID);
  }

  //! Overloaded variable setter for real array.
  //! \param varName [in] variable name.
  //! \param arr [in] array as a value.
  //! \param n [in] number of elements in the array.
  //! \param caseID [in] ID of the Test Case.
  //! \param funcID [in] 1-based ID of Test Function to be used as a namespace
  //!        for its own local variables mapping.
  static void SetVarDescr(const std::string& varName,
                          const double* arr,
                          const int n,
                          const int caseID,
                          const int funcID)
  {
    std::string arrStr("[");
    if ( n )
    {
      for ( int i = 0; i < n; ++i )
      {
        arrStr += ActAux::to_string(arr[i]);
        if ( i != (n - 1) )
          arrStr += ", ";
      }
    }
    arrStr += "]";

    SetVarDescr(varName, arrStr, caseID, funcID);
  }

  //! Overloaded variable setter for real matrix.
  //! \param varName [in] variable name.
  //! \param mx [in] matrix as a value.
  //! \param nRows [in] number of rows in the matrix.
  //! \param nCols [in] number of columns in the matrix.
  //! \param caseID [in] ID of the Test Case.
  //! \param funcID [in] 1-based ID of Test Function to be used as a namespace
  //!        for its own local variables mapping.
  static void SetVarDescr(const std::string& varName,
                          double** mx,
                          const int nRows,
                          const int nCols,
                          const int caseID,
                          const int funcID)
  {
    std::string mxStr;
    if ( nRows )
    {
      for ( int i = 0; i < nRows; ++i )
      {
        mxStr += "[";
        for ( int j = 0; j < nCols; ++j )
        {
          mxStr += ActAux::to_string(mx[i][j]);
          if ( j != (nCols - 1) )
            mxStr += ", ";
        }
        mxStr += "]";
        if ( i != (nRows - 1) )
          mxStr += ", ";
      }
    }

    SetVarDescr(varName, mxStr, caseID, funcID);
  }

  //! Returns variables expansion map.
  //! \return expansion map.
  static const StrStrMap& ExpansionMap()
  {
    return m_varExpansion;
  }

private:

  //! Returns variable name using namespace of the Test Function.
  //! \param varName [in] short name.
  //! \param caseID [in] ID of the Test Case.
  //! \param funcID [in] 1-based ID of Test Function to be used as a namespace
  //!        for its own local variables mapping.
  //! \return long variable name which is unique in scope of Test Function.
  static std::string generateVarName(const std::string& varName,
                                     const int caseID,
                                     const int funcID)
  {
    return ActAux::to_string(caseID) + ActTestLib_Macro_NAMESPACE +
           ActAux::to_string(funcID) + ActTestLib_Macro_NAMESPACE + varName;
  }

private:

  //! Local map for expansion of variables which can be used in
  //! descriptions of the Test Functions.
  static StrStrMap m_varExpansion;

};

#endif
