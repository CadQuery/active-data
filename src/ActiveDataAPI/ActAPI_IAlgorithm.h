//-----------------------------------------------------------------------------
// Created on: April 2016
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the OPEN CASCADE SAS.
// 4. Neither the name of the OPEN CASCADE SAS nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY OPEN CASCADE SAS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL OPEN CASCADE SAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
