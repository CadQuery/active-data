//-----------------------------------------------------------------------------
// Created on: 30 November 2013
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

#ifndef ActTestLib_DescriptionProc_HeaderFile
#define ActTestLib_DescriptionProc_HeaderFile

// ActTestLib includes
#include <ActTestLib_Macro.h>

// STD includes
#include <map>
#include <vector>

//! Utility class for processing of description files corresponding to Test
//! Cases.
class ActTestLib_DescriptionProc
{
public:

  //! Short-cut for variable expansion maps.
  typedef std::map<std::string, std::string> StrStrMap;

  //! Short-cut for string-string pairs.
  typedef std::pair<std::string, std::string> StrStrPair;

  //! Shortcut for ordered collection of strings.
  typedef std::vector<std::string> SeqStr;

public:

  ActTestLib_EXPORT static bool
    Process(const std::string& dir,
            const std::string& filename,
            const StrStrMap& vars,
            const int caseID,
            std::string& title,
            SeqStr& overviewBlocks,
            SeqStr& detailsBlocks);

private:

  static void
    extractBlocks(const std::string& text,
                  std::string& title,
                  SeqStr& overviewBlocks,
                  SeqStr& detailsBlocks);

  static void
    extractIndicesFromTag(const std::string& tag,
                          int& startIdx,
                          int& endIdx);

  static std::string
    expandVariables(const std::string& text,
                    const StrStrMap& vars,
                    const std::string& varsScope);

  static bool
    isVar(const std::string& token,
          int& varStart,
          int& varEnd);

  static bool
    isPre(const std::string& token,
          const bool isOpen);

  static std::string
    varScope(const int caseID,
             const int funcID);

private:

  ActTestLib_DescriptionProc() {};
  ActTestLib_DescriptionProc(const ActTestLib_DescriptionProc&) {};
  void operator=(const ActTestLib_DescriptionProc&) {}

};

#endif
