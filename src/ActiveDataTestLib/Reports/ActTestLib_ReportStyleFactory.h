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

#ifndef ActTestLib_ReportStyleFactory_HeaderFile
#define ActTestLib_ReportStyleFactory_HeaderFile

// ActTestLib includes
#include <ActTestLib_ReportStyle.h>

//! Factory for commonly used CSS styles.
class ActTestLib_ReportStyleFactory
{
public:

  ActTestLib_EXPORT static ActTestLib_ReportStyle
    Bad();

  ActTestLib_EXPORT static ActTestLib_ReportStyle
    Good();

private:

  ActTestLib_ReportStyleFactory() {}
  ActTestLib_ReportStyleFactory(const ActTestLib_ReportStyleFactory&) {}
  void operator=(const ActTestLib_ReportStyleFactory&) {}

};

#endif
