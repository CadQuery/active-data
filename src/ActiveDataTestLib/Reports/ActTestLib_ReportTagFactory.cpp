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

// Own include
#include <ActTestLib_ReportTagFactory.h>

//! Default constructor.
ActTestLib_ReportTagFactory::ActTestLib_ReportTagFactory()
{
}

//! Destructor.
ActTestLib_ReportTagFactory::~ActTestLib_ReportTagFactory()
{
}

//! Returns HTML tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Html(const bool isOpen)
{
  setPairedTag(m_tag, "html", isOpen);
  return m_tag;
}

//! Returns HEAD tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Head(const bool isOpen)
{
  setPairedTag(m_tag, "head", isOpen);
  return m_tag;
}

//! Returns META tag.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Meta()
{
  setUnpairedTag(m_tag, "meta");
  return m_tag;
}

//! Returns BODY tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Body(const bool isOpen)
{
  setPairedTag(m_tag, "body", isOpen);
  return m_tag;
}

//! Returns P tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::P(const bool isOpen)
{
  setPairedTag(m_tag, "p", isOpen);
  return m_tag;
}

//! Returns B tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::B(const bool isOpen)
{
  setPairedTag(m_tag, "b", isOpen);
  return m_tag;
}

//! Returns SUB tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Sub(const bool isOpen)
{
  setPairedTag(m_tag, "sub", isOpen);
  return m_tag;
}

//! Returns BR tag.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Br()
{
  setUnpairedTag(m_tag, "br");
  return m_tag;
}

//! Returns TABLE tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Table(const bool isOpen)
{
  setPairedTag(m_tag, "table", isOpen);
  return m_tag;
}

//! Returns TBODY tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::TBody(const bool isOpen)
{
  setPairedTag(m_tag, "tbody", isOpen);
  return m_tag;
}

//! Returns TR tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Tr(const bool isOpen)
{
  setPairedTag(m_tag, "tr", isOpen);
  return m_tag;
}

//! Returns TD tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Td(const bool isOpen)
{
  setPairedTag(m_tag, "td", isOpen);
  return m_tag;
}

//! Returns TH tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Th(const bool isOpen)
{
  setPairedTag(m_tag, "th", isOpen);
  return m_tag;
}

//! Returns FONT tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Font(const bool isOpen)
{
  setPairedTag(m_tag, "font", isOpen);
  return m_tag;
}

//! Returns H1 tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::H1(const bool isOpen)
{
  setPairedTag(m_tag, "h1", isOpen);
  return m_tag;
}

//! Returns H2 tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::H2(const bool isOpen)
{
  setPairedTag(m_tag, "h2", isOpen);
  return m_tag;
}

//! Returns H3 tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::H3(const bool isOpen)
{
  setPairedTag(m_tag, "h3", isOpen);
  return m_tag;
}

//! Returns H4 tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::H4(const bool isOpen)
{
  setPairedTag(m_tag, "h4", isOpen);
  return m_tag;
}

//! Returns HR tag.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Hr()
{
  setUnpairedTag(m_tag, "hr");
  return m_tag;
}

//! Returns Style tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Style(const bool isOpen)
{
  setPairedTag(m_tag, "style", isOpen);
  return m_tag;
}

//! Returns Center tag, opening or closing, depending on the passed
//! parameter.
//! \param isOpen [in] indicates whether the resulting tag is opening or
//!        closing.
//! \return requested tag.
ActTestLib_ReportTag& ActTestLib_ReportTagFactory::Center(const bool isOpen)
{
  setPairedTag(m_tag, "center", isOpen);
  return m_tag;
}

//! Prepares the passed tag as a paired one with the given name and
//! openness indicator.
//! \param tag [in/out] tag to prepare.
//! \param baseName [in] base name to set for the tag being prepared.
//! \param isOpen [in] indicates whether the tag being prepared is opening
//!        or closing.
void ActTestLib_ReportTagFactory::setPairedTag(ActTestLib_ReportTag& tag,
                                              const char* baseName,
                                              const bool isOpen)
{
  tag.Release();
  tag.SetIsPaired(true);
  tag.SetIsClosed(!isOpen);
  tag.SetBase(baseName);
}

//! Prepares the passed tag as single (non-paired) one with the given name.
//! \param tag [in/out] tag to prepare.
//! \param baseName [in] base name to set for the tag being prepared.
void ActTestLib_ReportTagFactory::setUnpairedTag(ActTestLib_ReportTag& tag,
                                                const char* baseName)
{
  tag.Release();
  tag.SetIsPaired(false);
  tag.SetBase(baseName);
}
