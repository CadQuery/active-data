//-----------------------------------------------------------------------------
// Created on: February 2013
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

#ifndef ActTestLib_FileComparator_HeaderFile
#define ActTestLib_FileComparator_HeaderFile

// ACT Test Framework includes
#include <ActTestLib_Common.h>

// Active Data (auxiliary) includes
#include <ActAux.h>
#include <ActAux_Utils.h>

//-----------------------------------------------------------------------------
// Base class for line comparators
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActTestLib_BaseLineComparator, Standard_Transient)

//! \ingroup AD_TEST
//!
//! Base class for line comparators.
class ActTestLib_BaseLineComparator : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActTestLib_BaseLineComparator, Standard_Transient)

public:

  virtual Standard_Boolean
    AreEqual(const TCollection_AsciiString& theString1,
             const TCollection_AsciiString& theString2) = 0;

};

//-----------------------------------------------------------------------------
// Default line comparator
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActTestLib_DefaultLineComparator, ActTestLib_BaseLineComparator)

//! \ingroup AD_TEST
//!
//! Default comparator for lines.
class ActTestLib_DefaultLineComparator : public ActTestLib_BaseLineComparator
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActTestLib_DefaultLineComparator, ActTestLib_BaseLineComparator)

public:

  //! Standard way to compare lines as string values.
  //! \param theString1 [in] first string.
  //! \param theString2 [in] second string.
  //! \return true/false.
  virtual Standard_Boolean AreEqual(const TCollection_AsciiString& theString1,
                                    const TCollection_AsciiString& theString2)
  {
    return theString1.IsEqual(theString2);
  }

};

//-----------------------------------------------------------------------------
// Floating-point line comparator
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActTestLib_FltLineComparator, ActTestLib_BaseLineComparator)

//! \ingroup AD_TEST
//!
//! Comparator for lines containing floating-point values.
class ActTestLib_FltLineComparator : public ActTestLib_BaseLineComparator
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActTestLib_FltLineComparator, ActTestLib_BaseLineComparator)

public:

  //! Constructor accepting precision for comparison. NOTICE: precision is
  //! understood as percentage.
  //! \param deviation [in] allowable deviation for floating-point comparison.
  //! \param resolution [in] this parameter defines resolution of the
  //!        comparator. If the difference between two values is less than
  //!        resolution, then there is no sense to check their relative
  //!        difference. This can be useful if you want to skip small
  //!        numbers like 0.0001 vs 0.000001. While the latter number is
  //!        100 times less than the first values, their difference is
  //!        insignificant from engineering point of view.
  ActTestLib_FltLineComparator(const Standard_Integer deviation,
                               const Standard_Real resolution = 1.0e-3) : ActTestLib_BaseLineComparator()
  {
    m_iDev = deviation;
    m_fResolution = resolution;
  }

public:

  //! Compares the passed lines as floating-point values if possible. If not,
  //! compares them as standard string values. For floating-point comparison
  //! precision value is used.
  //! \param theString1 [in] first string.
  //! \param theString2 [in] second string.
  //! \return true/false.
  virtual Standard_Boolean AreEqual(const TCollection_AsciiString& theString1,
                                    const TCollection_AsciiString& theString2)
  {
    TCollection_AsciiString Token1, Token2;
    Standard_Integer t1 = 1, t2 = 1;
    Standard_Real val1, val2;

    do
    {
      Token1 = theString1.Token(" \t", t1++);
      Token2 = theString2.Token(" \t", t2++);

      Standard_Boolean areEqual;
      if ( Token1.IsRealValue() && Token2.IsRealValue() )
      {
        val1 = Token1.RealValue();
        val2 = Token2.RealValue();

        // Fuzzy comparison
        areEqual = ActTestLib_Common::FuzzyCompare(val1, val2, m_iDev, m_fResolution);
      }
      else
        areEqual = Token1.IsEqual(Token2);

      if ( !areEqual )
        return Standard_False;
    }
    while ( !Token1.IsEmpty() && !Token2.IsEmpty() );

    // If we are here, then every token has passed the check
    return Standard_True;
  }

private:

  //! Allowable deviation for floating-point comparison.
  Standard_Integer m_iDev;

  //! Resolution.
  Standard_Real m_fResolution;

};

//-----------------------------------------------------------------------------
// Comparison utility for files
//-----------------------------------------------------------------------------

//! \ingroup AD_TEST
//!
//! Tool to compare several text files.
class ActTestLib_FileComparator
{
public:

  ActTestLib_EXPORT
    ActTestLib_FileComparator(const TCollection_AsciiString& theFilename1,
                              const TCollection_AsciiString& theFilename2,
                              ActAux_StrFilter theLineFilter = NULL,
                              const Handle(ActTestLib_BaseLineComparator)& theLineComparator = NULL);

public:

  ActTestLib_EXPORT void
    Perform();

public:

  //! Returns true if comparison has been performed.
  //! \return true/false.
  inline Standard_Boolean IsDone() const
  {
    return m_bDone;
  }

  //! Returns true if compared files are the same.
  //! \return true/false.
  inline Standard_Boolean AreSame() const
  {
    return m_bResult;
  }

  //! Returns index of the first line where some differences have been
  //! detected. Returns -1 if no such line found.
  //! \return index of line, starting from 1.
  inline Standard_Integer LineWithDiffs() const
  {
    return m_iLineWithDiffs;
  }

private:

  TCollection_AsciiString               m_filename1;  //!< Filename 1.
  TCollection_AsciiString               m_filename2;  //!< Filename 2.
  ActAux_StrFilter                      m_filter;     //!< Line filter.
  Handle(ActTestLib_BaseLineComparator) m_comparator; //!< Line comparator.

private:

  Standard_Boolean m_bDone;          //!< Completeness indicator.
  Standard_Boolean m_bResult;        //!< Comparison result.
  Standard_Integer m_iLineWithDiffs; //!< First line containing differences.

};

#endif
