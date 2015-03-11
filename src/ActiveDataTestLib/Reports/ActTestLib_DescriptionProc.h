//-----------------------------------------------------------------------------
// Created on: 30 November 2013
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
