//-----------------------------------------------------------------------------
// Created on: February 2013
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
