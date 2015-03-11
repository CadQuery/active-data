//-----------------------------------------------------------------------------
// Created on: 04 November 2013
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

#ifndef ActAux_FileDumper_HeaderFile
#define ActAux_FileDumper_HeaderFile

// ActAux includes
#include <ActAux.h>

// STD includes
#include <fstream>

//! Utility class providing functionality for dumping of algorithmic data
//! to ASCII files in different manners.
class ActAux_FileDumper
{
public:

  ActAux_EXPORT
    ActAux_FileDumper();

  ActAux_EXPORT
    ActAux_FileDumper(const std::string& filename);

  ActAux_EXPORT
    ~ActAux_FileDumper();

public:

  ActAux_EXPORT bool
    Open(const std::string& filename);

  ActAux_EXPORT void
    Dump(const std::string& msg);

  ActAux_EXPORT void
    Dump(const int val,
         const std::string& msg = "");

  ActAux_EXPORT void
    Dump(const double val,
         const std::string& msg = "");

  ActAux_EXPORT void
    Dump(const bool val,
         const std::string& msg = "");

  ActAux_EXPORT void
    Dump(const double* arr,
         const int numElems,
         const std::string& msg = "");

  ActAux_EXPORT void
    Dump(const double* mx,
         const int numRows,
         const int numCols,
         const std::string& msg = "");

private:

  std::ofstream m_FILE; //!< File stream.

};

#endif
