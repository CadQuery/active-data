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
