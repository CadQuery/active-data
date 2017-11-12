//-----------------------------------------------------------------------------
// Created on: February 2013
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

// Own include
#include <ActTestLib_FileComparator.h>

// OCCT includes
#include <OSD_File.hxx>
#include <OSD_Protection.hxx>

#define BUFLEN 1024

//-----------------------------------------------------------------------------
// Comparison utility for files
//-----------------------------------------------------------------------------

//! Complete constructor.
//! \param theFilename1 [in] first filename.
//! \param theFilename2 [in] second filename.
//! \param theLineFilter [in] string filter.
//! \param theLineComparator [in] comparator for lines.
ActTestLib_FileComparator::ActTestLib_FileComparator(const TCollection_AsciiString& theFilename1,
                                                     const TCollection_AsciiString& theFilename2,
                                                     ActAux_StrFilter theLineFilter,
                                                     const Handle(ActTestLib_BaseLineComparator)& theLineComparator)
: m_filename1(theFilename1),
  m_filename2(theFilename2),
  m_filter(theLineFilter),
  m_comparator(theLineComparator.IsNull() ? new ActTestLib_DefaultLineComparator : theLineComparator),
  m_bDone(Standard_False),
  m_bResult(Standard_False),
  m_iLineWithDiffs(-1)
{
}

//! Performs actual comparison of file contents.
void ActTestLib_FileComparator::Perform()
{
  m_bDone = Standard_True;
  m_bResult = Standard_True;

  /* ===========================
   *  Open files for comparison
   * =========================== */

  OSD_File FILE1 = OSD_File( OSD_Path(m_filename1) );
  OSD_File FILE2 = OSD_File( OSD_Path(m_filename2) );

  OSD_Protection aProtection;

  FILE1.Open(OSD_ReadOnly, aProtection);
  FILE2.Open(OSD_ReadOnly, aProtection);

  if ( !FILE1.IsOpen() || !FILE2.IsOpen() )
  {
    m_bDone = Standard_False;
    return;
  }

  /* =================================
   *  Perform line-by-line comparison
   * ================================= */

  // Stuff for streaming
  Standard_Integer NbChar1, NbChar2;
  TCollection_AsciiString Buff1, Buff2;
  Standard_Integer LineIdx = 1;

  while ( !FILE1.IsAtEnd() )
  {
    FILE1.ReadLine(Buff1, BUFLEN, NbChar1);

    if ( FILE2.IsAtEnd() )
    {
      m_bResult = Standard_False;
      m_iLineWithDiffs = LineIdx;
      return;
    }

    FILE2.ReadLine(Buff2, BUFLEN, NbChar2);

    // Check filters. Normally filters are useful to exclude some dedicated
    // lines from comparison process. E.g. we can skip comparison of comment
    // lines so
    if ( m_filter && !(*m_filter)(Buff1) && !(*m_filter)(Buff2) )
    {
      ++LineIdx;
      continue;
    }

    if ( !m_comparator->AreEqual(Buff1, Buff2) )
    {
      m_bResult = Standard_False;
      m_iLineWithDiffs = LineIdx;
      return;
    }

    ++LineIdx;
  }

  /* ==============
   *  Finalization
   * ============== */

  FILE1.Close();
  FILE2.Close();
}
