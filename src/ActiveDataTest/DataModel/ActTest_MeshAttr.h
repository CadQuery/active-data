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

#ifndef ActTest_MeshAttr_HeaderFile
#define ActTest_MeshAttr_HeaderFile

// ACT Unit Test Suite includes
#include <ActTest_DataFramework.h>

// Active Data includes
#include <ActData_MeshAttr.h>

//! \ingroup AD_TEST
//!
//! Base class providing common functionality for unit tests on
//! Mesh Attribute.
class ActTest_MeshAttrBase : public ActTest_DataFramework
{
public:

  static Standard_Real    NODES[][3];       //!< Collection of nodal co-ordinates.
  static Standard_Integer TRIANGLES[][3];   //!< Collection of triangles.
  static Standard_Integer QUADRANGLES[][4]; //!< Collection of quadrangles.

  static Standard_Integer NB_NODES;       //!< Number of mesh nodes.
  static Standard_Integer NB_TRIANGLES;   //!< Number of triangle mesh elements.
  static Standard_Integer NB_QUADRANGLES; //!< Number of quadrangle mesh elements.

protected:

  //! Type definition for collection of mesh element IDs.
  typedef NCollection_Sequence<Standard_Integer> DatumIdList;

protected:

  static bool
    initializeMeshAttr(const Handle(TDocStd_Document)& doc,
                       TDF_Label& meshLab,
                       const Standard_Boolean isImplictTrans = Standard_True);

  static bool
    populateMeshData(const Handle(TDocStd_Document)& doc,
                     TDF_Label& meshLab,
                     DatumIdList& NODE_IDS,
                     DatumIdList& TRIANGLE_IDS,
                     DatumIdList& QUADRANGLE_IDS,
                     const Standard_Boolean isImplictTrans = Standard_True);

  static bool
    populateMeshNodes(TDF_Label& meshLab,
                      DatumIdList& NODE_IDS);

  static bool
    populateMeshTriangles(TDF_Label& meshLab,
                          DatumIdList& TRIANGLE_IDS);

  static bool
    populateMeshQuadrangles(TDF_Label& meshLab,
                            DatumIdList& QUADRANGLE_IDS);

};

//! \ingroup AD_TEST
//!
//! Test suite for Active Data.
//! This class performs unit testing of Mesh CAF Attribute class in its
//! transient use cases. This includes creation of a new CAF Label and
//! manipulation with the attached data in a single transaction.
class ActTest_MeshAttrBean : public ActTest_MeshAttrBase
{
public:

  //! Returns Test Case ID.
  //! \return ID of the Test Case.
  static int ID()
  {
    return CaseID_MeshAttrBean;
  }

  //! Returns filename for the description.
  //! \return filename for the description of the Test Case.
  static std::string DescriptionFn()
  {
    return "ActTest_MeshAttrBean";
  }

  //! Returns Test Case description directory.
  //! \return description directory for the Test Case.
  static std::string DescriptionDir()
  {
    return "Mesh";
  }

  //! Returns pointers to the Test Functions to launch.
  //! \param functions [out] output collection of pointers.
  static void Functions(QrTestFunctions& functions)
  {
    functions << &meshBeanTest;
  }

// Test functions:
private:

  static bool meshBeanTest(const int funcID);

};

//! \ingroup AD_TEST
//!
//! Test suite for Active Data.
//! This class performs unit testing of Mesh CAF Attribute class in its
//! transactional perspective.
class ActTest_MeshAttrTransactional : public ActTest_MeshAttrBase
{
public:

  //! Returns Test Case ID.
  //! \return ID of the Test Case.
  static int ID()
  {
    return CaseID_MeshAttrTransactional;
  }

  //! Returns filename for the description.
  //! \return filename for the description of the Test Case.
  static std::string DescriptionFn()
  {
    return "ActTest_MeshAttrTransactional";
  }

  //! Returns Test Case description directory.
  //! \return description directory for the Test Case.
  static std::string DescriptionDir()
  {
    return "Mesh";
  }

  //! Returns pointers to the Test Functions to launch.
  //! \param functions [out] output collection of pointers.
  static void Functions(QrTestFunctions& functions)
  {
    functions << &meshTransUndoRedoTest1
              << &meshTransAbortTest1
              << &meshTransAbortTest2;
  }

// Test functions:
private:

  static bool meshTransUndoRedoTest1 (const int funcID);
  static bool meshTransAbortTest1    (const int funcID);
  static bool meshTransAbortTest2    (const int funcID);

};

//! \ingroup AD_TEST
//!
//! Test suite for Active Data.
//! This class performs unit testing of Mesh CAF Attribute class in its
//! persistence perspective.
class ActTest_MeshAttrPersistent : public ActTest_MeshAttrBase
{
public:

  //! Returns Test Case ID.
  //! \return ID of the Test Case.
  static int ID()
  {
    return CaseID_MeshAttrPersistent;
  }

  //! Returns filename for the description.
  //! \return filename for the description of the Test Case.
  static std::string DescriptionFn()
  {
    return "ActTest_MeshAttrPersistent";
  }

  //! Returns Test Case description directory.
  //! \return description directory for the Test Case.
  static std::string DescriptionDir()
  {
    return "Mesh";
  }

  //! Returns pointers to the Test Functions to launch.
  //! \param functions [out] output collection of pointers.
  static void Functions(QrTestFunctions& functions)
  {
    functions << &meshSaveOpenTest;
  }

// Test functions:
private:

  static bool meshSaveOpenTest(const int funcID);

};

#endif
