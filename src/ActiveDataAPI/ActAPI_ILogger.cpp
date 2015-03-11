//-----------------------------------------------------------------------------
// Created on: March 2012
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
#include <ActAPI_ILogger.h>

//! Destructor.
ActAPI_ILogger::~ActAPI_ILogger()
{
}

//! Iterates over the passed list of messages and puts them to the logging
//! queue taking care of the severity/priority tags for each message.
//! \param theLogList [in] list of messages to dispatch.
void ActAPI_ILogger::Dispatch(const ActAPI_LogMessageList& theLogList)
{
  ActAPI_LogMessageList::Iterator aListIt(theLogList);
  for ( ; aListIt.More(); aListIt.Next() )
  {
    const ActAPI_LogMessage& aMsg = aListIt.Value();
    switch ( aMsg.Severity )
    {
      case Severity_Information:
        this->Info(aMsg.MsgKey, aMsg.Priority, aMsg.Arguments, aMsg.TimeStamp);
        break;
      case Severity_Notice:
        this->Notice(aMsg.MsgKey, aMsg.Priority, aMsg.Arguments, aMsg.TimeStamp);
        break;
      case Severity_Warning:
        this->Warn(aMsg.MsgKey, aMsg.Priority, aMsg.Arguments, aMsg.TimeStamp);
        break;
      case Severity_Error:
        this->Error(aMsg.MsgKey, aMsg.Priority, aMsg.Arguments, aMsg.TimeStamp);
        break;
    }
  }
}
