//-----------------------------------------------------------------------------
// Created on: July 2012
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

#ifndef ActAPI_IProgressNotifier_HeaderFile
#define ActAPI_IProgressNotifier_HeaderFile

// Active Data (API) includes
#include <ActAPI_ILogger.h>

// OCCT includes
#include <Standard_Type.hxx>

//! \ingroup AD_API
//!
//! Progress status.
enum ActAPI_ProgressStatus
{
  Progress_Undefined = 0, //!< No status defined, no job has been ever started.
  Progress_Running,       //!< Job is currently running.
  Progress_Succeeded,     //!< Job has been performed successfully.
  Progress_Failed,        //!< Job has been failed.
  Progress_Cancelled      //!< Job has been requested for cancellation.
};

//-----------------------------------------------------------------------------
// Progress Notifier
//-----------------------------------------------------------------------------

//! \ingroup AD_API
//!
//! Interface for Progress Notifier concept. Progress Notifier provides
//! messaging mechanism for communications between algorithmic and GUI layers.
//! It is normally used in cases when GUI thread is running separately from
//! the working one, however, it is also suitable in a single-threaded
//! context (actually, it depends on the used implementation). Progress
//! Notifier provides the following services:
//!
//! - It allows the concurrently running algorithmic tasks to cumulate their
//!   progress states independently. For that, each parallel task is suggested
//!   as fully qualified portion of the overall calculation routine which have
//!   uniquely defined ID. The developer should bring the parallelism in his
//!   algorithm in such a way that each TBB task can access its unique ID
//!   and report its progress to the Progress Notifier using that ID. Such an
//!   ID should have essentially logical semantic. E.g. it could be the index
//!   of the first OCCT topological face in the working collection of faces
//!   allocated for processing in the current TBB task (see blocked_range
//!   notion).
//!
//! - It allows to gather the currently cumulated progress value by all
//!   registered tasks.
//!
//! - It allows to set up a progress message describing the currently performed
//!   job. This is normally an ASCII string localization key.
//!
//! - It allows to set up a completeness state for the entire process. The
//!   following states are supported: Not Defined, Running, Succeeded, Failed,
//!   Canceled.
//!
//! - It allows to send specific termination messages such as Completed (the
//!   working thread has finished his job) and Cancel (the working thread gets
//!   a request for cancellation, however, it can still run). Completed message
//!   is an obligatory one and must be sent in any cases.
class ActAPI_IProgressNotifier : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_IProgressNotifier, Standard_Transient)

public:

  ActAPI_EXPORT virtual ~ActAPI_IProgressNotifier();

// Thread-unsafe methods:
public:

  //! Cleans up the internal state of the Progress Notifier, so that it
  //! becomes ready to track another job.
  virtual void
    Reset() = 0;

  //! Initializes the Progress Notifier with the deterministic capacity
  //! value. Capacity represents the unitless overall progress value which
  //! can be ever collected by all running tasks.
  //!
  //! Please note, that by default the progress scale is declared with
  //! infinite capacity. Practically, it means that algorithm is not able
  //! to foresee the number of steps it will need to complete. Be sure that
  //! in such a case your interface reacts adequately (e.g. no percentage is
  //! shown to the user).
  //!
  //! \param theCapacity [in] capacity to set (infinite by default).
  virtual void
    Init(const Standard_Integer theCapacity = INT_MAX) = 0;

  //! Returns the capacity value.
  //! \return requested capacity value.
  virtual Standard_Integer
    Capacity() const = 0;

  //! Returns true if the capacity value is infinite.
  //! \return true/false.
  virtual Standard_Boolean
    IsInfinite() const = 0;

  //! Sets message localization key.
  //! \param theMsgKey [in] localization key to set.
  virtual void
    SetMessageKey(const TCollection_AsciiString& theMsgKey) = 0;

  //! Returns message localization key.
  //! \return localization key.
  virtual TCollection_AsciiString
    MessageKey() const = 0;

  //! Sets the ultimate progress status for the job.
  //! \param theStatus [in] progress status to set.
  virtual void
    SetProgressStatus(const ActAPI_ProgressStatus theStatus) = 0;

  //! Returns current progress status.
  //! \return the ultimate progress status.
  virtual ActAPI_ProgressStatus
    ProgressStatus() const = 0;

  //! Requests job cancellation.
  virtual void
    Cancel() = 0;

  //! Checks whether the job is being canceled.
  //! \return true/false.
  virtual Standard_Boolean
    IsCancelling() = 0;

  //! Checks whether the job is in running state.
  //! \return true/false.
  virtual Standard_Boolean
    IsRunning() = 0;

  //! Checks whether the job is in failed state.
  //! \return true/false.
  virtual Standard_Boolean
    IsFailed() = 0;

  //! Returns the currently cumulated progress value.
  //! \return current cumulative progress.
  virtual Standard_Integer
    SummaryProgress() const = 0;

// Tread-safe methods to be used by algorithms:
public:

  //! Thread-safe method used to increment the progress value associated with
  //! the given task ID by the passed step.
  //! \param theTaskID [in] ID of the task to increment the progress for.
  //! \param theProgressStep [in] progress value to increment by.
  virtual void
    StepProgress(const Standard_Integer theTaskID,
                 const Standard_Integer theProgressStep) = 0;

  //! Thread-safe method used to send a logging message. Normally, this is
  //! not GUI directly as Progress Notifier is designed for usage in
  //! multi-threaded environment.
  //! \param theMessage [in] message string (normally it is i18n key).
  //! \param theSeverity [in] message severity (info, warning, error).
  //! \param thePriority [in] message priority (normal, high).
  //! \param theArguments [in] message arguments (if any).
  virtual void
    SendLogMessage(const TCollection_AsciiString& theMessage,
                   const ActAPI_LogMessageSeverity theSeverity,
                   const ActAPI_LogMessagePriority thePriority = Priority_Normal,
                   const ActAPI_LogArguments& theArguments = ActAPI_LogArguments()) = 0;

  //! Thread-safe method used to send a logging message in a stream form.
  //! Normally, this is not GUI directly as Progress Notifier is designed for
  //! usage in multi-threaded environment.
  //! \param theLogStream [in] logging stream.
  virtual void
    SendLogMessage(const ActAPI_LogStream& theLogStream) = 0;

};

//-----------------------------------------------------------------------------
// Progress Entry
//-----------------------------------------------------------------------------

//! \ingroup AD_API
//!
//! Convenient way to work with Progress Notifier. This class is mostly
//! useful due to its NULL-safe approach to working with the underlying
//! Progress Notifier.
class ActAPI_ProgressEntry
{
// Methods to use in single-threaded context:
public:

  //! Default constructor.
  ActAPI_ProgressEntry() {}

  //! Dummy conversion constructor.
  ActAPI_ProgressEntry(Standard_Integer) {}

  //! Copy constructor.
  //! \param Entry [in] instance to copy.
  ActAPI_ProgressEntry(const ActAPI_ProgressEntry& Entry)
  {
    m_PNotifier = Entry.m_PNotifier;
  }

  //! Complete constructor.
  //! \param thePNotifier [in] Progress Notifier instance to set.
  ActAPI_ProgressEntry(const Handle(ActAPI_IProgressNotifier)& thePNotifier)
  {
    m_PNotifier = thePNotifier;
  }

// Thread-unsafe methods:
public:

  //! Null-safe Reset method for Progress Notifier.
  void Reset()
  {
    if ( !m_PNotifier.IsNull() )
      m_PNotifier->Reset();
  }

  //! Null-safe Init() method for Progress Notifier.
  //! \param theCapacity [in] capacity to set.
  void Init(const Standard_Integer theCapacity = INT_MAX)
  {
    if ( !m_PNotifier.IsNull() )
      m_PNotifier->Init(theCapacity);
  }

  //! Null-safe accessor for the capacity value.
  //! \return requested capacity value.
  Standard_Integer Capacity() const
  {
    if ( !m_PNotifier.IsNull() )
      return m_PNotifier->Capacity();

    return 0;
  }

  //! Null-safe checker for infinite capacity.
  //! \return true/false.
  Standard_Boolean IsInfinite() const
  {
    if ( !m_PNotifier.IsNull() )
      return m_PNotifier->IsInfinite();

    return Standard_False;
  }

  //! Null-safe SetMessageKey method for Progress Notifier.
  //! \param theMsgKey [in] localization key to set.
  void SetMessageKey(const TCollection_AsciiString& theMsgKey)
  {
    if ( !m_PNotifier.IsNull() )
      m_PNotifier->SetMessageKey(theMsgKey);
  }

  //! Null-safe accessor for the message localization key.
  //! \return localization key.
  TCollection_AsciiString MessageKey() const
  {
    if ( !m_PNotifier.IsNull() )
      return m_PNotifier->MessageKey();

    return TCollection_AsciiString();
  }

  //! Null-safe SetProgressStatus method for Progress Notifier.
  //! \param theStatus [in] progress status to set.
  void SetProgressStatus(const ActAPI_ProgressStatus theStatus)
  {
    if ( !m_PNotifier.IsNull() )
      m_PNotifier->SetProgressStatus(theStatus);
  }

  //! Null-safe accessor for the current progress status.
  //! \return the ultimately set progress status.
  ActAPI_ProgressStatus ProgressStatus() const
  {
    if ( !m_PNotifier.IsNull() )
      return m_PNotifier->ProgressStatus();

    return Progress_Undefined;
  }

  //! Null-safe Cancel method for Progress Notifier.
  void Cancel()
  {
    if ( !m_PNotifier.IsNull() )
      m_PNotifier->Cancel();
  }

  //! Null-safe IsCancelling checker.
  //! \return true/false.
  Standard_Boolean IsCancelling()
  {
    if ( !m_PNotifier.IsNull() )
      return m_PNotifier->IsCancelling();

    return Standard_False;
  }

  //! Null-safe IsRunning checker.
  //! \return true/false.
  Standard_Boolean IsRunning()
  {
    if ( !m_PNotifier.IsNull() )
      return m_PNotifier->IsRunning();

    return Standard_False;
  }

  //! Null-safe IsFailed checker.
  //! \return true/false.
  Standard_Boolean IsFailed()
  {
    if ( !m_PNotifier.IsNull() )
      return m_PNotifier->IsFailed();

    return Standard_False;
  }

  //! Null-safe accessor for the summary progress.
  //! \return current cumulative progress.
  Standard_Integer SummaryProgress() const
  {
    if ( !m_PNotifier.IsNull() )
      return m_PNotifier->SummaryProgress();

    return 0;
  }

  //! Accessor for the underlying Progress Notifier.
  //! \return Progress Notifier instance.
  Handle(ActAPI_IProgressNotifier) Access() const
  {
    return m_PNotifier;
  }

// Thread-safe methods:
public:

  //! Null-safe StepProgress method for Progress Notifier.
  void StepProgress(const Standard_Integer theTaskID,
                    const Standard_Integer theValue) const
  {
    if ( !m_PNotifier.IsNull() )
      m_PNotifier->StepProgress(theTaskID, theValue);
  }

  //! Null-safe SendLogMessage method for Progress Notifier.
  void SendLogMessage(const TCollection_AsciiString& theMessage,
                      const ActAPI_LogMessageSeverity theSeverity,
                      const ActAPI_LogMessagePriority thePriority = Priority_Normal,
                      const ActAPI_LogArguments& theArguments = ActAPI_LogArguments()) const
  {
    if ( !m_PNotifier.IsNull() )
      m_PNotifier->SendLogMessage(theMessage, theSeverity, thePriority, theArguments);
  }

  //! Null-safe SendLogMessage method for Progress Notifier.
  //! \param theLogStream [in] logging stream.
  void SendLogMessage(const ActAPI_LogStream& theLogStream) const
  {
    if ( !m_PNotifier.IsNull() )
      m_PNotifier->SendLogMessage(theLogStream);
  }

private:

  //! Managed instance of Progress Notifier.
  Handle(ActAPI_IProgressNotifier) m_PNotifier;

};

#endif
