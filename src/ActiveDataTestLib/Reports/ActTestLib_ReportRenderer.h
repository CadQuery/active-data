//-----------------------------------------------------------------------------
// Created on: 26 November 2013
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

#ifndef ActTestLib_ReportRenderer_HeaderFile
#define ActTestLib_ReportRenderer_HeaderFile

// ActTestLib includes
#include <ActTestLib_ReportStyle.h>
#include <ActTestLib_ReportTagFactory.h>

//! Utility for generating reports in HTML format. Supplies a predefined set
//! of atomic layout portions to be streamed one-by-one, producing the
//! resulting one-string report's content so.
//!
//! HTML 4.01 in XHTML form is supported.
//!
//! This class provides a mechanism to apply CSS on the HTML tags being
//! generated.
class ActTestLib_ReportRenderer
{
public:

  //! Convenient short-cut for this.
  typedef ActTestLib_ReportRenderer* THAT;

  //! Rendering log.
  struct RenderLog
  {
    int NbTables;     //!< Number of rendered tables
    int NbTableRows;  //!< Number of rendered table rows
    int NbTableCells; //!< Number of rendered table cells

    //! Constructor.
    RenderLog()
    {
      this->CleanLog();
    }

    //! Nullifies the logged statistics.
    void CleanLog()
    {
      NbTables = NbTableRows = NbTableCells = 0;
    }
  };

public:

  ActTestLib_EXPORT
    ActTestLib_ReportRenderer();

  ActTestLib_EXPORT
    ~ActTestLib_ReportRenderer();

public:

  ActTestLib_EXPORT std::string
    Flush(const bool isLogDropped = false);

  ActTestLib_EXPORT void
    Reset(const bool isLogDropped = false);

  ActTestLib_EXPORT bool
    DumpToFile(const std::string& filename);

  ActTestLib_EXPORT const RenderLog&
    GetRenderLog() const;

// ADD functions:
public:

  ActTestLib_EXPORT THAT
    AddDoctype();

  ActTestLib_EXPORT THAT
    AddSymboledText(const char* text,
                    const bool isScaled = true);

  ActTestLib_EXPORT THAT
    AddErrorText(const char* text);

  ActTestLib_EXPORT THAT
    AddImportantText(const char* text);

  ActTestLib_EXPORT THAT
    AddImportantText(const std::string& text);

  ActTestLib_EXPORT THAT
    AddImportantText(const int num);

  ActTestLib_EXPORT THAT
    AddImportantText(const double num);

  ActTestLib_EXPORT THAT
    AddText(const char* text,
            const bool doRemoveNewLines = true);

  ActTestLib_EXPORT THAT
    AddText(const std::string& text,
            const bool doRemoveNewLines = true);

  ActTestLib_EXPORT THAT
    AddText(const int num);

  ActTestLib_EXPORT THAT
    AddText(const double num);

  ActTestLib_EXPORT THAT
    AddEquality(const char* var,
                const char* value,
                const char* units = 0);

  ActTestLib_EXPORT THAT
    AddTextWithSubs(const char* text,
                    const char* subs,
                    const bool isTextSymboled = false,
                    const bool isSubsSymboled = false);

  ActTestLib_EXPORT THAT
    AddMeta();

  ActTestLib_EXPORT THAT
    AddEmptyTableCell();

  ActTestLib_EXPORT THAT
    AddEmptyTableHCell();

  ActTestLib_EXPORT THAT
    AddTableHCell(const char* text);

  ActTestLib_EXPORT THAT
    AddTableCell(const char* text);

  ActTestLib_EXPORT THAT
    AddParagraph(const char* text);

  ActTestLib_EXPORT THAT
    AddHr();

  ActTestLib_EXPORT THAT
    AddClass(const std::string& dotName,
             const ActTestLib_ReportStyle& style);

// START/END functions:
public:

  ActTestLib_EXPORT THAT
    StartHtml();

  ActTestLib_EXPORT THAT
    EndHtml();

  ActTestLib_EXPORT THAT
    StartHeader();

  ActTestLib_EXPORT THAT
    EndHeader();

  ActTestLib_EXPORT THAT
    StartBody(const ActTestLib_ReportStyle& style = 0);

  ActTestLib_EXPORT THAT
    StartBody(const std::string& className);

  ActTestLib_EXPORT THAT
    EndBody();

  ActTestLib_EXPORT THAT
    StartTable(const ActTestLib_ReportStyle& style = 0);

  ActTestLib_EXPORT THAT
    StartTable(const std::string& className);

  ActTestLib_EXPORT THAT
    EndTable();

  ActTestLib_EXPORT THAT
    StartTableRow(const ActTestLib_ReportStyle& style = 0);

  ActTestLib_EXPORT THAT
    StartTableRow(const std::string& className);

  ActTestLib_EXPORT THAT
    EndTableRow();

  ActTestLib_EXPORT THAT
    StartTableCell(const ActTestLib_ReportStyle& style = 0);

  ActTestLib_EXPORT THAT
    StartTableCell(const std::string& className);

  ActTestLib_EXPORT THAT
    StartColSpanTableCell(const int colSpan = 1,
                          const ActTestLib_ReportStyle& theStyle = 0);

  ActTestLib_EXPORT THAT
    StartColSpanTableCell(const int colSpan,
                          const std::string& className);

  ActTestLib_EXPORT THAT
    StartColSpanTableHCell(const int colSpan = 1,
                           const ActTestLib_ReportStyle& style = 0);

  ActTestLib_EXPORT THAT
    StartColSpanTableHCell(const int colSpan,
                           const std::string& className);

  ActTestLib_EXPORT THAT
    StartRowSpanTableCell(const int rowSpan = 1,
                          const ActTestLib_ReportStyle& style = 0);

  ActTestLib_EXPORT THAT
    StartRowSpanTableCell(const int rowSpan,
                          const std::string& className);

  ActTestLib_EXPORT THAT
    StartRowSpanTableHCell(const int rowSpan = 1,
                           const ActTestLib_ReportStyle& style = 0);

  ActTestLib_EXPORT THAT
    StartRowSpanTableHCell(const int rowSpan,
                           const std::string& className);

  ActTestLib_EXPORT THAT
    EndTableCell();

  ActTestLib_EXPORT THAT
    StartTableHCell(const ActTestLib_ReportStyle& style = 0);

  ActTestLib_EXPORT THAT
    StartTableHCell(const std::string& className);

  ActTestLib_EXPORT THAT
    EndTableHCell();

  ActTestLib_EXPORT THAT
    StartParagraph(const ActTestLib_ReportStyle& style = 0);

  ActTestLib_EXPORT THAT
    StartParagraph(const std::string& className);

  ActTestLib_EXPORT THAT
    EndParagraph();

  ActTestLib_EXPORT THAT
    StartSubscript();

  ActTestLib_EXPORT THAT
    EndSubscript();

  ActTestLib_EXPORT THAT
    StartH1();

  ActTestLib_EXPORT THAT
    EndH1();

  ActTestLib_EXPORT THAT
    StartStyle();

  ActTestLib_EXPORT THAT
    EndStyle();

  ActTestLib_EXPORT THAT
    StartCenter();

  ActTestLib_EXPORT THAT
    EndCenter();

// Additional functions:
public:

  ActTestLib_EXPORT THAT
    BreakRow();

private:

  static void
    removeInconsistent(std::string& str);

private:

  //! Tag factory to generate HTML mark-up.
  ActTestLib_ReportTagFactory m_tagFactory;

  //! Rendering buffer.
  std::string m_buffer;

  //! Rendering log.
  RenderLog m_log;

};

#endif
