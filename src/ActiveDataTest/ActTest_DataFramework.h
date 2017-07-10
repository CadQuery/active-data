//-----------------------------------------------------------------------------
// Created on: March 2012
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

#ifndef ActTest_DataFramework_HeaderFile
#define ActTest_DataFramework_HeaderFile

// Active Data unit tests
#include <ActTest.h>

// ACT Test Library includes
#include <ActTestLib_Macro.h>
#include <ActTestLib_TestCase.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

// OCCT includes
#include <TDocStd_Document.hxx>

//! \ingroup AD_TEST
//!
//! Convenient base class for Active Data test suites. Provides common
//! functionality and data sources.
class ActTest_DataFramework : public ActTestLib_TestCase
{
protected:

  static Handle(TDocStd_Document)
    initCAFDocument();

  static Standard_Boolean
    saveDocument(const Handle(TDocStd_Document)& doc,
                 const TCollection_AsciiString& filename);

  static Standard_Boolean
    openDocument(const TCollection_AsciiString& filename,
                 Handle(TDocStd_Document)& doc);

  static Handle(ActAPI_IUserParameter)
    createParameter(const Handle(TDocStd_Document)& doc,
                    const ActAPI_ParameterType type);

  static Handle(ActAPI_IUserParameter)
    createParameter(const Handle(TDocStd_Document)& doc,
                    const ActAPI_ParameterType type,
                    TDF_Label& newLabel);

  static TDF_Label
    nextParameterLabel(const Handle(TDocStd_Document)& doc);

  static Standard_Integer
    nextParameterTag();

// Working with graphs and trees:
protected:

  //! Short-cut for a collection of Entries.
  typedef NCollection_Sequence<TCollection_AsciiString> EntryList;

  //! Short-cut for collection of TDF Label entries expected on each level of
  //! the dependency graph being executed.
  typedef NCollection_Sequence<EntryList> EntriesByLevels;

  static Standard_Boolean
    isLabelExpectedByLevel(const Standard_Integer theLevel,
                           const TCollection_AsciiString& theEntry,
                           const EntriesByLevels& theEntriesByLevels);

protected:

  //! CAF Tag for root TDF Labels of Data Parameters.
  static Standard_Integer PARAM_TAG;

};

#endif
