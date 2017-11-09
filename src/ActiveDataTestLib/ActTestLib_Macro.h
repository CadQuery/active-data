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

#ifndef ActTestLib_Macro_HeaderFile
#define ActTestLib_Macro_HeaderFile

// ActTestLib includes
#include <ActTestLib.h>

#define ActTestLib_Macro_NAMESPACE    "::"
#define ActTestLib_Macro_BUFLEN       256
#define ActTestLib_Macro_VAR_MARKER   "%%"
#define ActTestLib_Macro_SEC_TITLE    "[TITLE]"
#define ActTestLib_Macro_SEC_OVERVIEW ":OVERVIEW]"
#define ActTestLib_Macro_SEC_DETAILS  ":DETAILS]"
#define ActTestLib_Macro_DOT          '.'
#define ActTestLib_Macro_SLASH        '/'
#define ActTestLib_Macro_RSLASH       '\\'
#define ActTestLib_Macro_WHITESPACE   ' '
#define ActTestLib_Macro_COLON        ':'
#define ActTestLib_Macro_NL           '\n'
#define ActTestLib_Macro_NL_STR       "\n"
#define ActTestLib_Macro_MINUS        '-'
#define ActTestLib_Macro_BR           "<br>"
#define ActTestLib_Macro_SUBSEC_PRE_O "<pre>"
#define ActTestLib_Macro_SUBSEC_PRE_C "</pre>"
#define ActTestLib_Macro_REPORT_FN    "report"
#define ActTestLib_Macro_REPORT_EXT   "html"
#define ActTestLib_Macro_DESCR_EXT    "descr"
#define ActTestLib_Macro_RESULT       "Result"
#define ActTestLib_Macro_TEST         "Test"
#define ActTestLib_Macro_FAILED       "Failed"
#define ActTestLib_Macro_OK           "Ok"

//-----------------------------------------------------------------------------
// Asserts
//-----------------------------------------------------------------------------

#define ACT_VERIFY(x) \
  { \
    if ( !(x) ) return false; \
  }

//-----------------------------------------------------------------------------
// Formatted printing
//-----------------------------------------------------------------------------

#define PRINT_DECOR \
  std::cout << "------------------------------------------------------------" << std::endl;

#define TEST_STRONG_LINE_DECORATOR \
  printf("================================================================\
===============\n"); \

#define TEST_LINE_DECORATOR \
  printf("----------------------------------------------------------------\
---------------\n");

#define TEST_FUNC_DECORATOR_BEGIN(FuncName) \
  printf("\n"); \
  TEST_STRONG_LINE_DECORATOR \
  printf("Executing test function: "); printf(FuncName); \
  printf("\n"); \
  TEST_LINE_DECORATOR

#define TEST_FUNC_DECORATOR_END \
  TEST_LINE_DECORATOR \
  printf("\n");

#define TEST_PRINT(Msg) \
  printf(Msg);

#define TEST_PRINT_DOUBLE(Val) \
  printf("%0.6f", Val);

#define TEST_PRINT_L(Msg) \
  TEST_PRINT(Msg); TEST_PRINT("\n");

#define TEST_PRINT_DECOR(Msg) \
  TEST_PRINT("*** "); TEST_PRINT(Msg);

#define TEST_PRINT_DECOR_L(Msg) \
  TEST_PRINT_DECOR(Msg); TEST_PRINT("\n");

#endif
