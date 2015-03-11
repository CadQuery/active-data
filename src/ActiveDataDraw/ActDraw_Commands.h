//-----------------------------------------------------------------------------
// Created on: January 2012
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

#ifndef ActDraw_Commands_HeaderFile
#define ActDraw_Commands_HeaderFile

// Active Data (Draw plug-in) includes
#include <ActDraw.h>

// OCCT includes
#include <Standard.hxx>
#include <TCollection_AsciiString.hxx>

// Forward declarations
class Draw_Interpretor;

//! \ingroup AD_DRAW
//!
//! Draw plug-in providing custom commands for functional testing of
//! Active Data.
class ActDraw_Commands
{
// Plug-in interface methods:
public:

  ActDraw_EXPORT static void Factory(Draw_Interpretor&);

// Test commands for AD:
public:

  ActDraw_EXPORT static void CAFDumperCommands(Draw_Interpretor&);
  ActDraw_EXPORT static void MiscCommands(Draw_Interpretor&);

// Auxiliary static methods to support Draw-based tests:
public:

  ActDraw_EXPORT static TCollection_AsciiString GET_DUMP_PATH();

};

#endif
