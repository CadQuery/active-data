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

#ifndef ActTest_BaseModel_HeaderFile
#define ActTest_BaseModel_HeaderFile

// Active Data unit tests
#include <ActTest.h>

// ACT Test Library includes
#include <ActTestLib_Common.h>
#include <ActTestLib_TestCase.h>

// Active Data includes
#include <ActData_BaseModel.h>

//! \ingroup AD_TEST
//!
//! Test suite for Active Data.
//! This class performs unit testing of persistence functionality provided
//! by BaseModel class shipped with Data Framework.
class ActTest_BaseModelPersistence : public ActTestLib_TestCase
{
public:

  //! Returns Test Case ID.
  //! \return ID of the Test Case.
  static int ID()
  {
    return CaseID_BaseModelPersistence;
  }

  //! Returns filename for the description.
  //! \return filename for the description of the Test Case.
  static std::string DescriptionFn()
  {
    return "ActTest_BaseModelPersistence";
  }

  //! Returns Test Case description directory.
  //! \return description directory for the Test Case.
  static std::string DescriptionDir()
  {
    return "Model";
  }

  //! Returns pointers to the Test Functions to launch.
  //! \param functions [out] output collection of pointers.
  static void Functions(ActiveDataTestFunctions& functions)
  {
    functions << &testHasOpenCommand
              << &newEmptyModel
              << &loadModel
              << &saveModel
              << releaseModel;
  }

// Test functions:
private:

  static bool testHasOpenCommand (const int funcID);
  static bool newEmptyModel      (const int funcID);
  static bool loadModel          (const int funcID);
  static bool saveModel          (const int funcID);
  static bool releaseModel       (const int funcID);

};

//! Test suite for Active Data.
//! This class performs unit testing of structure management services
//! provided by BaseModel class shipped with Data Framework.
class ActTest_BaseModelStructure : public ActTestLib_TestCase
{
public:

  //! Returns Test Case ID.
  //! \return ID of the Test Case.
  static int ID()
  {
    return CaseID_BaseModelStructure;
  }

  //! Returns filename for the description.
  //! \return filename for the description of the Test Case.
  static std::string DescriptionFn()
  {
    return "ActTest_BaseModelStructure";
  }

  //! Returns Test Case description directory.
  //! \return description directory for the Test Case.
  static std::string DescriptionDir()
  {
    return "Model";
  }

  //! Returns pointers to the Test Functions to launch.
  //! \param functions [out] output collection of pointers.
  static void Functions(ActiveDataTestFunctions& functions)
  {
    functions << &findNode
              << &deleteRootNode
              << &deleteSubTreeNode_D
              << &deleteSubTreeNode_D_AsReferenced
              << deleteSubTreeNode_C
              << accessObservers_D;
  }

private:

  static void init(Handle(ActAPI_IModel)&,
                   NCollection_Sequence<ActAPI_DataObjectId>&);

// Test functions:
private:

  static bool findNode                         (const int funcID);
  static bool deleteRootNode                   (const int funcID);
  static bool deleteSubTreeNode_D              (const int funcID);
  static bool deleteSubTreeNode_D_AsReferenced (const int funcID);
  static bool deleteSubTreeNode_C              (const int funcID);
  static bool accessObservers_D                (const int funcID);

};

//! Test suite for Active Data.
//! This class performs unit testing of Expression Evaluation mechanism.
class ActTest_BaseModelEvaluation : public ActTestLib_TestCase
{
public:

  //! Returns Test Case ID.
  //! \return ID of the Test Case.
  static int ID()
  {
    return CaseID_BaseModelEvaluation;
  }

  //! Returns filename for the description.
  //! \return filename for the description of the Test Case.
  static std::string DescriptionFn()
  {
    return "ActTest_BaseModelEvaluation";
  }

  //! Returns Test Case description directory.
  //! \return description directory for the Test Case.
  static std::string DescriptionDir()
  {
    return "Model";
  }

  //! Returns pointers to the Test Functions to launch.
  //! \param functions [out] output collection of pointers.
  static void Functions(ActiveDataTestFunctions& functions)
  {
    functions << &removeVariable
              << &checkLoops1
              << &checkLoops2
              << &checkLoops3
              << &checkLoops4
              << &checkLoops5
              << &checkLoops6
              << &renameVariable1
              << &renameVariable2
              << &renameVariable3
              << &addVariable;
  }

private:

  static void init(Handle(ActAPI_IModel)&,
                   NCollection_Sequence<ActAPI_DataObjectId>&);

// Test functions:
private:

  static bool removeVariable  (const int funcID);
  static bool checkLoops1     (const int funcID);
  static bool checkLoops2     (const int funcID);
  static bool checkLoops3     (const int funcID);
  static bool checkLoops4     (const int funcID);
  static bool checkLoops5     (const int funcID);
  static bool checkLoops6     (const int funcID);
  static bool renameVariable1 (const int funcID);
  static bool renameVariable2 (const int funcID);
  static bool renameVariable3 (const int funcID);
  static bool addVariable     (const int funcID);

};

#endif
