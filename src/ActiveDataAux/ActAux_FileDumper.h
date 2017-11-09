//-----------------------------------------------------------------------------
// Created on: 04 November 2013
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
