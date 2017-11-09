//-----------------------------------------------------------------------------
// Created on: March 2012
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
