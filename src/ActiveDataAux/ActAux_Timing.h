//-----------------------------------------------------------------------------
// Created on: July 2013
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

#ifndef ActAux_Timing_HeaderFile
#define ActAux_Timing_HeaderFile

// Active Data (auxiliary) includes
#include <ActAux.h>

// OCCT includes
#include <OSD_Timer.hxx>

/************************************************************************
                           MEASURING PERFORMANCE
 ************************************************************************/

//! Example:
//!
//! #ifdef TIMER_NEW
//!   TIMER_NEW
//!   TIMER_RESET
//!   TIMER_GO
//! #endif
//!
//! ... YOUR AD_ALGO GOES HERE ...
//!
//! #ifdef TIMER_NEW
//!   TIMER_FINISH
//!   TIMER_COUT_RESULT
//! #endif

#define TIMER_NEW \
  OSD_Timer __aux_debug_Timer; \
  Standard_Real __aux_debug_Seconds, __aux_debug_CPUTime; \
  Standard_Integer __aux_debug_Minutes, __aux_debug_Hours;

#define TIMER_RESET \
  __aux_debug_Seconds = __aux_debug_CPUTime = 0.0; \
  __aux_debug_Minutes = __aux_debug_Hours = 0; \
  __aux_debug_Timer.Reset();

#define TIMER_GO \
  __aux_debug_Timer.Start();

#define TIMER_FINISH \
  __aux_debug_Timer.Stop(); \
  __aux_debug_Timer.Show(__aux_debug_Seconds, __aux_debug_Minutes, __aux_debug_Hours, __aux_debug_CPUTime);

#define TIMER_COUT_RESULT \
  { \
    std::cout << "\n=============================================" << endl; \
    std::cout << "Seconds:  " << __aux_debug_Seconds               << endl; \
    std::cout << "Minutes:  " << __aux_debug_Minutes               << endl; \
    std::cout << "Hours:    " << __aux_debug_Hours                 << endl; \
    std::cout << "CPU time: " << __aux_debug_CPUTime               << endl; \
    std::cout << "=============================================\n" << endl; \
  }

#endif
