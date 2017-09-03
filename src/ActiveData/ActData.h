//-----------------------------------------------------------------------------
// Created on: April 2012
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

#ifndef ActData_HeaderFile
#define ActData_HeaderFile

#ifdef ActiveData_EXPORTS
#define ActData_EXPORT __declspec(dllexport)
#else
#define ActData_EXPORT __declspec(dllimport)
#endif

// Define BINARY format to be used for ACT Data persistence. Two formats
// are currently available:
// - BinOcaf -- standard OCCT format understanding any standard OCAF Attribute.
// - ACTBin -- extended standard OCCT format having BinOcaf functionality as a
//   subset and providing persistence (storage/retrieval) drivers for ACT
//   specific Attributes, e.g. Mesh Attribute. Notice that actually we use
//   extension points of TKBin library, not TKBinL (the latter is not
//   suitable for all ACT Parameters).
#define ACTBinFormat "ACTBin" // "ACTBin" or "BinOcaf"

#endif
