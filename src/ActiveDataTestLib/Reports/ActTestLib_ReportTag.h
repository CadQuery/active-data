//-----------------------------------------------------------------------------
// Created on: 26 November 2013
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

#ifndef ActTestLib_ReportTag_HeaderFile
#define ActTestLib_ReportTag_HeaderFile

// ActTestLib includes
#include <ActTestLib.h>

// STD includes
#include <vector>

//! Base class representing HTML tag for test report.
class ActTestLib_ReportTag
{
public:

  ActTestLib_EXPORT
    ActTestLib_ReportTag();

  ActTestLib_EXPORT
    ~ActTestLib_ReportTag();

public:

  ActTestLib_EXPORT inline void
    Release();

  ActTestLib_EXPORT inline void
    SetIsPaired(const bool isPaired);

  ActTestLib_EXPORT inline bool
    IsPaired() const;

  ActTestLib_EXPORT inline void
    SetIsClosed(const bool isClosed);

  ActTestLib_EXPORT inline bool
    IsClosed() const;

  ActTestLib_EXPORT inline void
    SetBase(const char* base);

  ActTestLib_EXPORT inline void
    SetBase(const std::string& base);

  ActTestLib_EXPORT inline void
    AddStyle(const char* styleName,
             const char* styleValue);

  ActTestLib_EXPORT inline void
    AddStyle(const std::string& styleName,
             const std::string& styleValue);

  ActTestLib_EXPORT inline void
    AddAttribute(const char* attrName,
                 const char* attrValue);

  ActTestLib_EXPORT inline void
    AddAttribute(const std::string& attrName,
                 const std::string& attrValue);

  ActTestLib_EXPORT inline std::string
    Result() const;

private:

  static void eraseString(std::string& string);
  static void eraseStrings(std::vector<std::string>& stringList);

private:

  std::string              m_base;           //!< Base name.
  std::string              m_style;          //!< Associated style.
  std::vector<std::string> m_attributes;     //!< Associated attributes.
  bool                     m_bIsInitialized; //!< Indicates whether this tag is initialized or not.
  bool                     m_bIsPaired;      //!< Indicates whether this tag is paired or not.
  bool                     m_bIsStyled;      //!< Indicates whether this tag is styled or not.
  bool                     m_bIsClosed;      //!< Indicates whether this tag is closed or not.

};

#endif
