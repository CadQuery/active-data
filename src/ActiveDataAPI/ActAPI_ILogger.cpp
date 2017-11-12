//-----------------------------------------------------------------------------
// Created on: March 2012
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
