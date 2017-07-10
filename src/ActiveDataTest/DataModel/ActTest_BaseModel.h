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
