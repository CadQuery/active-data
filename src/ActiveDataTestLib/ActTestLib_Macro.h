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
