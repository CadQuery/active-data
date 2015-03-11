//-----------------------------------------------------------------------------
// Created on: May 2013
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

#ifndef ActAux_Utils_HeaderFile
#define ActAux_Utils_HeaderFile

// ACT algorithmic collection includes
#include <ActAux_Common.h>

// OCCT includes
#include <OSD_File.hxx>
#include <TCollection_AsciiString.hxx>

//! \ingroup AD_ALGO
//!
//! Function to filter strings.
typedef Standard_Boolean (*ActAux_StrFilter)(const TCollection_AsciiString& theString);

//! \ingroup AD_ALGO
//!
//! Function to compare strings.
typedef Standard_Boolean (*ActAux_StrComparator)(const TCollection_AsciiString& theString1,
                                                 const TCollection_AsciiString& theString2);

//! \ingroup AD_ALGO
//!
//! Auxiliary functionality.
namespace ActAux_Utils
{
  //! String utilities.
  namespace Str
  {
    //! Formats the passed value according to the passed format string.
    //! This is actually a standard sprintf functionality.
    //! \param theFormat [in] format string.
    //! \param theVal [in] value to format.
    //! \return formatted string.
    template<typename EType>
    TCollection_AsciiString Formatted(const Standard_CString theFormat,
                                      const EType theVal)
    {
      Standard_Character Buff[100];
      sprintf_s(Buff, theFormat, theVal);
      return Buff;
    }

    ActAux_EXPORT TCollection_AsciiString
      Space(const Standard_Integer theNum);

    ActAux_EXPORT TCollection_AsciiString
      BaseFilename(const TCollection_AsciiString& theFilename,
                   const Standard_Boolean doKeepExt = Standard_False);

    ActAux_EXPORT TCollection_AsciiString
      BasePath(const TCollection_AsciiString& theFilename,
               const Standard_Boolean keepSlash = Standard_False);

    ActAux_EXPORT Standard_Real
      RealAt(const TCollection_AsciiString& theStr,
             const Standard_Integer theStart,
             const Standard_Integer theEnd,
             Standard_Boolean& isOk);

    ActAux_EXPORT Standard_Integer
      IntAt(const TCollection_AsciiString& theStr,
            const Standard_Integer theStart,
            const Standard_Integer theEnd,
            Standard_Boolean& isOk);

    ActAux_EXPORT TCollection_AsciiString
      Trim(const TCollection_AsciiString& theStr);

    ActAux_EXPORT Standard_Boolean
      FetchLine(OSD_File& FILE,
                TCollection_AsciiString& theLine,
                ActAux_StrFilter theFilter);

    ActAux_EXPORT Standard_Boolean
      NextToken(TCollection_AsciiString& theLine,
                Standard_Integer& theIdx,
                TCollection_AsciiString& theToken,
                OSD_File& FILE,
                const TCollection_AsciiString& theSeparator,
                ActAux_StrFilter theFilter);

    ActAux_EXPORT void
      Split(const TCollection_AsciiString& theLine,
            const TCollection_AsciiString& theSeparator,
            NCollection_Sequence<TCollection_AsciiString>& theChunks);

    ActAux_EXPORT TCollection_AsciiString
      Slashed(const TCollection_AsciiString& theStr);

  };
};

#endif
