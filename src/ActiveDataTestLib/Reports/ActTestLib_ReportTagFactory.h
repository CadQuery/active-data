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

#ifndef ActTestLib_ReportTagFactory_HeaderFile
#define ActTestLib_ReportTagFactory_HeaderFile

// ActTestLib includes
#include <ActTestLib_ReportTag.h>

//! Mark-up factory for reports. Encapsulates routines connected with
//! preparation of tags. As rendering process is kind of streaming, only
//! one tag is accessible at each moment. The tag's working copy is
//! initialized by attributes & styles required in the current report
//! rendering context.
class ActTestLib_ReportTagFactory
{
public:

  ActTestLib_EXPORT
    ActTestLib_ReportTagFactory();

  ActTestLib_EXPORT
    ~ActTestLib_ReportTagFactory();

public:

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Html(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Head(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Meta();

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Body(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    P(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    B(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Sub(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Br();

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Table(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    TBody(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Tr(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Td(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Th(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Font(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    H1(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    H2(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    H3(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    H4(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Hr();

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Style(const bool isOpen = true);

  ActTestLib_EXPORT ActTestLib_ReportTag&
    Center(const bool isOpen = true);

private:

  static void setPairedTag(ActTestLib_ReportTag& tag,
                           const char* baseName,
                           const bool isOpen);

  static void setUnpairedTag(ActTestLib_ReportTag& tag,
                             const char* baseName);

private:

  ActTestLib_ReportTag m_tag; //!< Simple tag for streaming.

};

#endif
