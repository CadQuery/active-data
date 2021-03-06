//-----------------------------------------------------------------------------
// Created on: April 2016
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

#ifndef ActAPI_IAlgorithm_HeaderFile
#define ActAPI_IAlgorithm_HeaderFile

// Active Data (API) includes
#include <ActAPI_IPlotter.h>
#include <ActAPI_IProgressNotifier.h>

//-----------------------------------------------------------------------------

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

  ActAPI_ProgressEntry& GetProgress() const { return m_progress; }
  ActAPI_PlotterEntry&  GetPlotter()  const { return m_plotter; }

public:

  //! Sets status code as an integer.
  //! \param[in] status code to set.
  void SetStatusCode(const Standard_Integer status)
  {
    m_iStatusCode = status;
  }

  //! \return integer status code.
  Standard_Integer GetStatusCode() const
  {
    return m_iStatusCode;
  }

  //! Adds status to the currently stored one. The derived classes take
  //! responsibility to implement status codes as bitmasks like 0x01, 0x02,
  //! 0x04, 0x08, 0x10, 0x20, 0x40, etc. This may we can store several statuses
  //! in one integer variable.
  //! \param[in] statBit status bit to add to the current status.
  void AddStatusCode(const Standard_Integer statBit)
  {
    m_iStatusCode |= statBit;
  }

  //! Checks whether the stored status code contains bits for the passed
  //! status.
  //! \param[in] statBit bits to check.
  //! \return true/false.
  Standard_Boolean HasStatusCode(const Standard_Integer statBit) const
  {
    return (m_iStatusCode & statBit) > 0;
  }

protected:

  ActAPI_EXPORT
    ActAPI_IAlgorithm(ActAPI_ProgressEntry progress,
                      ActAPI_PlotterEntry  plotter);

protected:

  mutable ActAPI_ProgressEntry m_progress; //!< Progress Notifier.
  mutable ActAPI_PlotterEntry  m_plotter;  //!< Imperative Plotter.

  //! Status code which can be an error code, warning code or any other
  //! status which gives more detalisation on algorithm's execution state.
  Standard_Integer m_iStatusCode;

private:

  ActAPI_IAlgorithm() : Standard_Transient() {} //!< Default ctor.

};

#endif
