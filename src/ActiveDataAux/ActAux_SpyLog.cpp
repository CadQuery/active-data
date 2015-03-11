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

// Own include
#include <ActAux_SpyLog.h>

// Active Data (auxiliary) includes
#include <ActAux_Utils.h>

// OCCT includes
#include <OSD_Environment.hxx>
#include <OSD_File.hxx>
#include <OSD_Protection.hxx>

// STD includes
#include <iostream>
#include <string>

#define SpyLog_Filename "statistics.txt"

Handle(ActAux_SpyLog) ActAux_SpyLog::__instance;

//! Returns instance of the spy logger.
//! \return instance of spy logger.
Handle(ActAux_SpyLog) ActAux_SpyLog::Instance()
{
  if ( __instance.IsNull() )
    __instance = new ActAux_SpyLog();

  return __instance;
}

//! Constructor.
ActAux_SpyLog::ActAux_SpyLog() : Standard_Transient()
{
  this->Start();
}

//! Destructor.
ActAux_SpyLog::~ActAux_SpyLog()
{
  this->Stop();
}

//! Starts logging.
void ActAux_SpyLog::Start()
{
  // Get user name
  CHAR username[UNLEN+1];
  DWORD username_len = UNLEN+1;
  GetUserNameA(username, &username_len);
  m_username = username;

  // Get computer name
  CHAR compname[UNLEN+1];
  DWORD compname_len = UNLEN+1;
  GetComputerNameA(compname, &compname_len);
  m_compname = compname;

  // Session start timestamp
  m_session_start = ActAux_TimeStampTool::Generate();
}

//! Counts the call of analysis of the given name.
//! \param name [in] name of the analysis.
void ActAux_SpyLog::CallCount(const std::string& name)
{
  std::map<std::string, int>::iterator it = m_call_count.find(name);

  if ( it == m_call_count.end() )
    m_call_count.insert( std::pair<std::string, int>(name, 1) );
  else
    it->second += 1;
}

//! Stop logging.
void ActAux_SpyLog::Stop()
{
  TCollection_AsciiString testDumpPath = OSD_Environment("AD_TEST_DUMP").Value();
  TCollection_AsciiString dumpPath     = testDumpPath.ToCString();
  std::string             filename     = ActAux_Utils::Str::Slashed(dumpPath).ToCString() + std::string(SpyLog_Filename);

  // Loop until the file is accessible
  int limit = 1000, attempt = 0;
  ofstream FILE;
  FILE.open(filename, std::ios_base::app);
  while ( !FILE.is_open() && attempt < limit )
  {
    Sleep(100);
    FILE.open(filename, std::ios_base::app);
    ++attempt;
  }

  // Dump header
  std::string dump;
  dump += ( "---\nUser " + m_username
                         + " on " + m_compname
                         + " : started "
                         + m_session_start->ToString(Standard_False, Standard_False).ToCString()
                         + " : ended "
                         + ActAux_TimeStampTool::Generate()->ToString(Standard_False, Standard_False).ToCString()
                         + "\n" );
  for ( std::map<std::string, int>::const_iterator cit = m_call_count.cbegin(); cit != m_call_count.cend(); cit++ )
  {
    std::ostringstream os;
    os << cit->second;
    dump += ("    " + cit->first + " was called " + os.str() + " times\n");
  }

  // Dump results to file
  FILE.write( dump.c_str(), (Standard_Integer) dump.size() );

  // Close file
  FILE.close();
}
