//-----------------------------------------------------------------------------
// Created on: April 2012
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

#ifndef ActAPI_ILogger_HeaderFile
#define ActAPI_ILogger_HeaderFile

// Active Data (API) includes
#include <ActAPI_Variables.h>

// OCCT includes
#include <NCollection_DataMap.hxx>
#include <NCollection_Sequence.hxx>
#include <NCollection_Shared.hxx>
#include <Standard_ProgramError.hxx>
#include <Standard_Type.hxx>
#include <TCollection_AsciiString.hxx>

#define LogInfo(PriorityShort) \
  ActAPI_LogStream(Severity_Information, Priority_##PriorityShort)
#define LogNotice(PriorityShort) \
  ActAPI_LogStream(Severity_Notice, Priority_##PriorityShort)
#define LogWarn(PriorityShort) \
  ActAPI_LogStream(Severity_Warning, Priority_##PriorityShort)
#define LogErr(PriorityShort) \
  ActAPI_LogStream(Severity_Error, Priority_##PriorityShort)

#if defined(ACT_DEBUG)
  #define LogInfo_Deb(PriorityShort) \
    ActAPI_LogStream(Severity_Information, Priority_##PriorityShort)
  #define LogNotice_Deb(PriorityShort) \
    ActAPI_LogStream(Severity_Notice, Priority_##PriorityShort)
  #define LogWarn_Deb(PriorityShort) \
    ActAPI_LogStream(Severity_Warning, Priority_##PriorityShort)
  #define LogErr_Deb(PriorityShort) \
    ActAPI_LogStream(Severity_Error, Priority_##PriorityShort)
#else
  #define LogInfo_Deb(PriorityShort) \
    ActAPI_LogStream()
  #define LogNotice_Deb(PriorityShort) \
    ActAPI_LogStream()
  #define LogWarn_Deb(PriorityShort) \
    ActAPI_LogStream()
  #define LogErr_Deb(PriorityShort) \
    ActAPI_LogStream()
#endif

#define ActAPI_LogStr_True TCollection_AsciiString("true")
#define ActAPI_LogStr_False TCollection_AsciiString("false")

//! \ingroup AD_API
//!
//! Type definition for logging arguments of heterogeneous types.
typedef NCollection_Sequence<Handle(ActAPI_VariableBase)> ActAPI_LogArguments;

//! \ingroup AD_API
//!
//! Priority of logged message.
enum ActAPI_LogMessagePriority
{
  Priority_Normal = 1, //!< Nothing special.
  Priority_High,       //!< Important.
};

//! \ingroup AD_API
//!
//! Severity of logged message.
enum ActAPI_LogMessageSeverity
{
  Severity_Information = 1, //!< Just information message.
  Severity_Notice,          //!< Notice message (can be important).
  Severity_Warning,         //!< Warning message.
  Severity_Error            //!< Error message.
};

//! \ingroup AD_API
//!
//! Generic logging message.
struct ActAPI_LogMessage
{
  //! Priority tag.
  ActAPI_LogMessagePriority Priority;

  //! Severity tag.
  ActAPI_LogMessageSeverity Severity;

  //! Message text. It is ASCII string as we consider it to be the
  //! localization key.
  TCollection_AsciiString MsgKey;

  //! Application-specific timestamp.
  Handle(Standard_Transient) TimeStamp;

  //! Arguments for logging message.
  ActAPI_LogArguments Arguments;

  //! Default constructor.
  ActAPI_LogMessage()
  {}

  //! Complete constructor.
  //! \param thePriority [in] message priority tag.
  //! \param theSeverity [in] message severity tag.
  //! \param theMsgKey [in] message localization key.
  //! \param theArguments [in] arguments for the logging message if any.
  //! \param theTimeStamp [in] application-specific timestamp.
  ActAPI_LogMessage(const ActAPI_LogMessagePriority thePriority,
                    const ActAPI_LogMessageSeverity theSeverity,
                    const TCollection_AsciiString& theMsgKey,
                    const ActAPI_LogArguments& theArguments = ActAPI_LogArguments(),
                    const Handle(Standard_Transient)& theTimeStamp = NULL)
  : Priority(thePriority),
    Severity(theSeverity),
    MsgKey(theMsgKey),
    Arguments(theArguments),
    TimeStamp(theTimeStamp)
  {}

  virtual Standard_Boolean operator>(const ActAPI_LogMessage&) const
  {
    return Standard_False;
  }

  virtual Standard_Boolean operator==(const ActAPI_LogMessage&) const
  {
    return Standard_False;
  }
};

//! \ingroup AD_API
//!
//! Short-cut for list of messages in OCCT thread-unsafe form.
typedef NCollection_Sequence<ActAPI_LogMessage> ActAPI_LogMessageList;

//! \ingroup AD_API
//!
//! Logging tool.
class ActAPI_ILogger : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_ILogger, Standard_Transient)

public:

  ActAPI_EXPORT virtual
    ~ActAPI_ILogger();

// Logging abstract kernel:
public:

  virtual void
    Info(const TCollection_AsciiString& theMessage,
         const ActAPI_LogMessagePriority thePriority = Priority_Normal,
         const ActAPI_LogArguments& theArguments = ActAPI_LogArguments(),
         const Handle(Standard_Transient)& theTimeStamp = NULL) = 0;

  virtual void
    Notice(const TCollection_AsciiString& theMessage,
           const ActAPI_LogMessagePriority thePriority = Priority_Normal,
           const ActAPI_LogArguments& theArguments = ActAPI_LogArguments(),
           const Handle(Standard_Transient)& theTimeStamp = NULL) = 0;

  virtual void
    Warn(const TCollection_AsciiString& theMessage,
         const ActAPI_LogMessagePriority thePriority = Priority_Normal,
         const ActAPI_LogArguments& theArguments = ActAPI_LogArguments(),
         const Handle(Standard_Transient)& theTimeStamp = NULL) = 0;

  virtual void
    Error(const TCollection_AsciiString& theMessage,
          const ActAPI_LogMessagePriority thePriority = Priority_Normal,
          const ActAPI_LogArguments& theArguments = ActAPI_LogArguments(),
          const Handle(Standard_Transient)& theTimeStamp = NULL) = 0;

// Logging kernel:
public:

  ActAPI_EXPORT virtual void
    Dispatch(const ActAPI_LogMessageList& theLogList);

};

//! \ingroup AD_API
//!
//! Convenience tool for message streaming.
class ActAPI_LogStream
{
public:

  //! Default constructor.
  ActAPI_LogStream()
  {
    m_bIsDummy          = Standard_True;
    m_bIsMsgInitialized = Standard_False;
  }

  //! Constructor.
  //! \param theSeverity [in] severity of the Log Message.
  //! \param thePriority [in] priority of the Log Message.
  ActAPI_LogStream(const ActAPI_LogMessageSeverity& theSeverity,
                   const ActAPI_LogMessagePriority& thePriority)
  {
    m_severity          = theSeverity;
    m_priority          = thePriority;
    m_bIsDummy          = Standard_False;
    m_bIsMsgInitialized = Standard_False;
  }

  //! Converter to Log Message.
  //! \return Log Message.
  operator ActAPI_LogMessage()
  {
    return ActAPI_LogMessage(m_priority, m_severity, m_msg, m_args, NULL);
  }

  //! Pushes the passed value to the logging stream.
  //! \param theStr [in] value to stream.
  //! \return this instance for further streaming.
  ActAPI_LogStream& operator<<(Standard_CString theStr)
  {
    return this->operator<<( TCollection_AsciiString(theStr) );
  }

  //! Pushes the passed value to the logging stream.
  //! \param theStr [in] value to stream.
  //! \return this instance for further streaming.
  ActAPI_LogStream& operator<<(const TCollection_AsciiString& theStr)
  {
    if ( m_bIsDummy )
      return *this;

    if ( !m_bIsMsgInitialized )
    {
      m_msg = theStr;
      m_bIsMsgInitialized = Standard_True;
    }
    else
    {
      Handle(ActAPI_VariableString) aTStr = new ActAPI_VariableString(theStr);
      m_args.Append(aTStr);
    }

    return *this;
  }

  //! Pushes the passed value to the logging stream.
  //! \param theVal [in] value to stream.
  //! \return this instance for further streaming.
  ActAPI_LogStream& operator<<(const Standard_Integer theVal)
  {
    if ( m_bIsDummy )
      return *this;

    if ( !m_bIsMsgInitialized )
      Standard_ProgramError::Raise("Message must be initialized first");

    Handle(ActAPI_VariableInt) aTVal = new ActAPI_VariableInt(theVal);
    m_args.Append(aTVal);

    return *this;
  }

  //! Pushes the passed value to the logging stream.
  //! \param theVal [in] value to stream.
  //! \return this instance for further streaming.
  ActAPI_LogStream& operator<<(const Standard_Real theVal)
  {
    if ( m_bIsDummy )
      return *this;

    if ( !m_bIsMsgInitialized )
      Standard_ProgramError::Raise("Message must be initialized first");

    Handle(ActAPI_VariableReal) aTVal = new ActAPI_VariableReal(theVal);
    m_args.Append(aTVal);

    return *this;
  }

  //! Pushes the passed value to the logging stream.
  //! \param theVal [in] value to stream.
  //! \return this instance for further streaming.
  ActAPI_LogStream& operator<<(const Standard_Boolean theVal)
  {
    return this->operator<<(theVal ? ActAPI_LogStr_True : ActAPI_LogStr_False);
  }

  //! Pushes the passed shape to the logging stream.
  //! \param theShape [in] shape to stream.
  //! \return this instance for further streaming.
  ActAPI_LogStream& operator<<(const TopoDS_Shape& theShape)
  {
    if ( m_bIsDummy )
      return *this;

    if ( !m_bIsMsgInitialized )
      Standard_ProgramError::Raise("Message must be initialized first");

    Handle(ActAPI_VariableShape) aTVal = new ActAPI_VariableShape(theShape);
    m_args.Append(aTVal);

    return *this;
  }

  //! Pushes the streamed message to the passed Logger.
  //! \param theLogger [in] target Logger.
  void operator>>(const Handle(ActAPI_ILogger)& theLogger)
  {
    if ( m_bIsDummy )
      return;

    if ( theLogger.IsNull() )
      return;

    if ( m_severity == Severity_Information )
      theLogger->Info(m_msg, m_priority, m_args);
    if ( m_severity == Severity_Notice )
      theLogger->Notice(m_msg, m_priority, m_args);
    else if ( m_severity == Severity_Warning )
      theLogger->Warn(m_msg, m_priority, m_args);
    else if ( m_severity == Severity_Error )
      theLogger->Error(m_msg, m_priority, m_args);
  }

  //! Accessor for severity.
  //! \return message severity.
  inline ActAPI_LogMessageSeverity Severity() const
  {
    return m_severity;
  }

  //! Accessor for priority.
  //! \return message priority.
  inline ActAPI_LogMessagePriority Priority() const
  {
    return m_priority;
  }

  //! Accessor for text.
  //! \return message text.
  inline TCollection_AsciiString Text() const
  {
    return m_msg;
  }

  //! Accessor for arguments.
  //! \return message arguments.
  inline ActAPI_LogArguments Args() const
  {
    return m_args;
  }

private:

  //! Message priority.
  ActAPI_LogMessagePriority m_priority;

  //! Message severity.
  ActAPI_LogMessageSeverity m_severity;

  //! Logging message.
  TCollection_AsciiString m_msg;

  //! Logging arguments.
  ActAPI_LogArguments m_args;

  //! Internal status.
  Standard_Boolean m_bIsMsgInitialized;

  //! Indicates whether Logging Stream is dummy or not.
  Standard_Boolean m_bIsDummy;

};

#endif
