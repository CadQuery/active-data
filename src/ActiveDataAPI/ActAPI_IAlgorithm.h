//-----------------------------------------------------------------------------
// Created on: April 2016
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

#ifndef ActAPI_IAlgorithm_HeaderFile
#define ActAPI_IAlgorithm_HeaderFile

// Active Data (API) includes
#include <ActAPI_IPlotter.h>
#include <ActAPI_IProgressNotifier.h>

//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActAPI_IAlgorithm, Standard_Transient)

//! \ingroup AD_API
//!
//! Interface for algorithms.
class ActAPI_IAlgorithm : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_IAlgorithm, Standard_Transient)

public:

  ActAPI_EXPORT virtual
    ~ActAPI_IAlgorithm();

public:

  inline ActAPI_ProgressEntry& Progress() const { return m_progress; }
  inline ActAPI_PlotterEntry&  Plotter()  const { return m_plotter; }

protected:

  ActAPI_EXPORT
    ActAPI_IAlgorithm(ActAPI_ProgressEntry progress,
                      ActAPI_PlotterEntry  plotter);

protected:

  mutable ActAPI_ProgressEntry m_progress; //!< Progress Notifier.
  mutable ActAPI_PlotterEntry  m_plotter;  //!< Imperative Plotter.

private:

  ActAPI_IAlgorithm() : Standard_Transient() {}

};

#endif
