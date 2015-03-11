//-----------------------------------------------------------------------------
// Created on: February 2015
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

#ifndef ActAux_SpyLog_HeaderFile
#define ActAux_SpyLog_HeaderFile

// Win API and services
#include <windows.h>
#include <lmcons.h>

// Active Data (auxiliary) includes
#include <ActAux_TimeStamp.h>

// OCCT includes
#include <Standard_Type.hxx>

// STD includes
#include <map>

DEFINE_STANDARD_HANDLE(ActAux_SpyLog, Standard_Transient)

//! \ingroup AD_ALGO
//!
//! Journal for logging of usage statistics.
class ActAux_SpyLog : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAux_SpyLog, Standard_Transient)

public:

  ActAux_EXPORT static Handle(ActAux_SpyLog)
    Instance();

public:

  ActAux_EXPORT void
    Start();

  ActAux_EXPORT void
    CallCount(const std::string& name);

  ActAux_EXPORT void
    Stop();

protected:

  ActAux_EXPORT
    ActAux_SpyLog();

  ActAux_EXPORT
    ~ActAux_SpyLog();

private:

  ActAux_SpyLog(const ActAux_SpyLog&) {}
  void operator=(const ActAux_SpyLog&) {}

private:

  static Handle(ActAux_SpyLog) __instance; //!< Instance.

private:

  std::string                m_username;      //!< User name.
  std::string                m_compname;      //!< Computer name.
  Handle(ActAux_TimeStamp)   m_session_start; //!< Timestamp of session start.
  std::map<std::string, int> m_call_count;    //!< Call counter for analyses.

};


#endif
