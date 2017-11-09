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

// Windows includes
#include <windows.h>

// Own include
#include <ActTestLib_Launcher.h>

// ActTestLib includes
#include <ActTestLib_DescriptionProc.h>
#include <ActTestLib_ReportRenderer.h>
#include <ActTestLib_ReportStyleFactory.h>

// ActAux includes
#include <ActAux_Env.h>
#include <ActAux_TimeStamp.h>

// STD includes
#include <fstream>

// Initialize static variable used to store current temp dir name
std::string ActTestLib_Launcher::current_temp_dir;

//! Adds the passed Test Case Launcher to the internal collection.
//! \param CaseLauncher [in] Test Case Launcher to add.
//! \return this for subsequent streaming.
ActTestLib_Launcher&
  ActTestLib_Launcher::operator<<(ActTestLib_CaseLauncherAPI* CaseLauncher)
{
  m_launchers.push_back(CaseLauncher);
  return *this;
}

//! Launches all managed Test Cases.
//! \param out [in, optional] output stream.
//! \return true if all Cases have succeeded, false -- otherwise.
bool ActTestLib_Launcher::Launch(std::ostream* out) const
{
  /* =============================
   *  Prepare temporary directory
   * ============================= */

  std::string dirName = std::string("ut_") + this->uniqueDirName();

  if ( out )
    *out << "\tTemporary directory: " << dirName.c_str() << "\n";

  // Prepare full name of the temporary directory
  current_temp_dir = ActAux::slashed( ActAux_Env::ActDumping() ) + dirName;

  // TODO: for Windows only (!!!)
  // Create temporary directory
  if ( !CreateDirectory(current_temp_dir.c_str(), NULL) )
  {
    if ( out )
      *out << "\tFailed to create directory: " << current_temp_dir.c_str() << "\n";
    return false;
  }

  // TODO: for Windows only (!!!)
  // Create temporary directory for files
  if ( !CreateDirectory(current_temp_dir_files().c_str(), NULL) )
  {
    if ( out )
      *out << "\tFailed to create directory: " << current_temp_dir_files().c_str() << "\n";
    return false;
  }

  /* ==============================
   *  Launch Test Cases one by one
   * ============================== */

  bool isOk = true;
  int numTotal = 0, numFailed = 0;
  for ( int l = 0; l < (int) m_launchers.size(); ++l )
  {
    ActTestLib_CaseLauncherAPI* CaseLauncher = m_launchers.at(l);
    const bool nextOk = CaseLauncher->Launch();

    PRINT_DECOR

    // Put message to output stream
    if ( out )
    {
      *out << "\tCase " << CaseLauncher->CaseID() << ": " << (nextOk ? "Ok" : "Failed");
      *out << "; (Total / Failed) = (" << CaseLauncher->NumberOfExecuted() << " / "
                                       << CaseLauncher->NumberOfFailed() << ")\n";
    }

    numTotal += CaseLauncher->NumberOfExecuted();
    numFailed += CaseLauncher->NumberOfFailed();

    if ( !nextOk && isOk )
      isOk = false;
  }

  if ( out )
  {
    *out << "\t***\n";
    *out << "\tTotal executed: " << numTotal << "\n";
    *out << "\tTotal failed: " << numFailed << "\n";
  }

  /* ================
   *  Prepare report
   * ================ */

  if ( out )
    *out << "\t***\n";
  if ( this->generateReport(out) )
  {
    if ( out )
      *out << "\tReport generation succeeded\n";
  }
  else
  {
    if ( out )
      *out << "\tReport generation failed (!!!)\n";
  }

  return isOk;
}

//! Generates HTML report for the Test Cases identified by the managed
//! Launchers.
//! \param out [in] output stream.
//! \return true in case of success, false -- otherwise.
bool ActTestLib_Launcher::generateReport(std::ostream* out) const
{
  /* ===========================
   *  Render header information
   * =========================== */

  ActTestLib_ReportRenderer* Rdr = new ActTestLib_ReportRenderer;

  // Global style for HTML body
  ActTestLib_ReportStyle BodyStyle;
  BodyStyle.SetFontFamily("Verdana");

  // Global style for TD elements
  ActTestLib_ReportStyle CellStyle;
  CellStyle.SetFontSize(11);

  // Global style for header cells
  ActTestLib_ReportStyle HCellStyle;
  HCellStyle.SetBgColor( ActTestLib_ReportStyle::Color(215, 215, 200) );

  // Global style for TD elements for "good" results
  ActTestLib_ReportStyle GoodCellStyle;
  GoodCellStyle.SetBgColor( ActTestLib_ReportStyle::Color(180, 220, 25) );

  // Global style for TD elements for "bad" results
  ActTestLib_ReportStyle BadCellStyle;
  BadCellStyle.SetBgColor( ActTestLib_ReportStyle::Color(255, 0, 0) );

  // Global style for tables
  ActTestLib_ReportStyle TableStyle;
  TableStyle.SetBorder(1);
  TableStyle.SetPadding(5);

  // Generate HTML heading section
  Rdr->AddDoctype()
     ->StartHtml()
     ->StartHeader()
     ->AddMeta()
     ->StartStyle()
     ->AddClass("body_class", BodyStyle)
     ->AddClass("table_class", TableStyle)
     ->AddClass("cell_class", CellStyle)
     ->AddClass("good_cell_class", GoodCellStyle)
     ->AddClass("bad_cell_class", BadCellStyle)
     ->AddClass("header_cell_class", HCellStyle)
     ->EndStyle()
     ->EndHeader()
     ->StartBody("body_class");

  // Generate table header
  Rdr->StartTable("table_class")
     ->StartTableRow()
     ->StartColSpanTableHCell(2, "table_class cell_class")
     ->AddText(ActTestLib_Macro_TEST)
     ->EndTableHCell()
     ->StartTableHCell("table_class cell_class")
     ->AddText(ActTestLib_Macro_RESULT)
     ->EndTableHCell()
     ->EndTableRow();

  /* =======================================
   *  Render information per each Test Case
   * ======================================= */

  // Iterate over Test Cases
  for ( int l = 0; l < (int) m_launchers.size(); ++l )
  {
    const ActTestLib_CaseLauncherAPI* CaseLauncher = m_launchers.at(l);

    // Get filename for description
    std::string descGroupDir = CaseLauncher->CaseDescriptionDir();
    std::string descFilename = CaseLauncher->CaseDescriptionFn() + ActTestLib_Macro_DOT + ActTestLib_Macro_DESCR_EXT;
    std::string descDir      = ActAux::slashed( ActAux_Env::ActDescr() ) + descGroupDir;

    // Description processing tool
    std::string title;
    std::vector<std::string> overviewBlocks, detailBlocks;
    if ( !ActTestLib_DescriptionProc::Process(descDir,
                                              descFilename,
                                              CaseLauncher->Variables(),
                                              CaseLauncher->CaseID(),
                                              title,
                                              overviewBlocks,
                                              detailBlocks) )
    {
      if ( out )
        *out << "\tFailed to read description from \"" << descFilename.c_str() << "\"\n";
      return false;
    }

    // Local statistics
    const int    nTotal        = CaseLauncher->NumberOfExecuted();
    const int    nFailed       = CaseLauncher->NumberOfFailed();
    const double passedPercent = (double) (nTotal-nFailed)/nTotal*100.0;

    // Render header for Test Case
    Rdr->StartTableRow()
       ->StartTableHCell("table_class cell_class header_cell_class")
       ->AddText( CaseLauncher->CaseID() )
       ->EndTableHCell()
       ->StartTableHCell("table_class cell_class header_cell_class")
       ->AddText(title)
       ->EndTableHCell();

    // Finish row with local statistics
    Rdr->StartTableHCell( (nFailed == 0) ? "table_class cell_class good_cell_class"
                                         : "table_class cell_class bad_cell_class" );
    Rdr->AddText(passedPercent)->AddText("%")->EndTableHCell();
    Rdr->EndTableRow();

    // Check number of OVERVIEW blocks
    if ( (int) overviewBlocks.size() < nTotal )
    {
      if ( out )
        *out << "\tNot enough OVERVIEW blocks in \"" << descFilename.c_str() << "\"\n";
      return false;
    }

    // Add rows for Test Functions
    for ( int f = 0; f < nTotal; ++f )
    {
      // Prepare global ID of Test Function
      std::string GID = ActAux::to_string( CaseLauncher->CaseID() ) +
                     ActTestLib_Macro_COLON +
                     ActAux::to_string(f+1);

      // Add table row
      Rdr->StartTableRow()
         ->StartTableCell("table_class cell_class")->AddText(GID)->EndTableCell()
         ->StartTableCell("table_class cell_class")
         ->AddText( overviewBlocks[f] );

      // Add section for details
      if ( ( (int) detailBlocks.size() >= (f+1) ) && !ActAux::is_of_nulls(detailBlocks[f]) )
      {
        std::string details = detailBlocks[f];

        Rdr->BreakRow()->BreakRow()
           ->AddText("<i>Details:</i>")
           ->AddText("<div style='border: 1px dotted rgb(100, 100, 100); "
                     "font-size: 11; background-color: rgb(250, 245, 160); "
                     "padding: 5px; margin: 5px;'>")
           ->AddText(details)
           ->AddText("</div>");
      }

      // Finish description cell
      Rdr->EndTableCell();

      // Result of Test Function
      if ( CaseLauncher->IsPassed(f) )
        Rdr->StartTableCell("table_class cell_class good_cell_class")->AddText(ActTestLib_Macro_OK);
      else
        Rdr->StartTableCell("table_class cell_class bad_cell_class")->AddText(ActTestLib_Macro_FAILED);

      // Finish row
      Rdr->EndTableCell()->EndTableRow();
    }
  }

  // Finish table
  Rdr->EndTable();

  /* ===============
   *  Render footer
   * =============== */

  Rdr->EndBody()->EndHtml();

  /* ==========================
   *  Prepare filesystem stuff
   * ========================== */

  // Filename for HTML report
  std::string
    filename = ActAux::slashed(current_temp_dir) +
               ActTestLib_Macro_REPORT_FN + ActTestLib_Macro_DOT + ActTestLib_Macro_REPORT_EXT;

  // Create file for HTML report
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);
  if ( !file.is_open() )
  {
    if ( out )
      *out << "Cannot open file " << filename.c_str() << " for writing" << "\n";
    return false;
  }

  // Dump rendered information to file
  file << Rdr->Flush();

  // Release file
  file.close();

  // Release renderer
  delete Rdr;

  return true;
}

//! Generates unique name for the directory containing all results for
//! current test session. The used format is as follows:
//! <pre>
//! ut_{week-day}_{month}_{day}_{{hour}{min}{sec}}_{year}
//!
//! E.g:
//!
//! ut_Sat_Dec_07_190744_2013
//!
//! </pre>
//! \return generated unique name.
std::string ActTestLib_Launcher::uniqueDirName() const
{
  Handle(ActAux_TimeStamp) TS = ActAux_TimeStampTool::Generate();
  return TS->ToString(false, true).ToCString();
}
