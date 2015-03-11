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

// Own include
#include <ActData_FuncExecutionTask.h>

// OCCT includes
#include <Standard_ProgramError.hxx>

#undef COUT_DEBUG

//! Initializing constructor.
//! \param thePNotifier [in] Progress Notifier instance.
//! \param theModel [in] Data Model instance.
//! \param theData [in] optional transaction data.
ActData_FuncExecutionTask::ActData_FuncExecutionTask(const Handle(ActAPI_IProgressNotifier)& thePNotifier,
                                                     const Handle(ActAPI_IModel)& theModel,
                                                     const ActAPI_TxData& theData)
  : m_PNotifier(thePNotifier),
    m_model(theModel),
    m_txData(theData)
{}

//! Forks the new TBB non-waitable task for multiplication algorithm.
//! \param thePNotifier [in] Progress Notifier instance.
//! \param theModel [in] Data Model instance.
//! \param theData [in] optional transaction data.
ActData_FuncExecutionTask*
  ActData_FuncExecutionTask::Launch(const Handle(ActAPI_IProgressNotifier)& thePNotifier,
                                    const Handle(ActAPI_IModel)& theModel,
                                    const ActAPI_TxData& theData)
{
  ActAPI_ProgressEntry aPEntry(thePNotifier);
  aPEntry.Reset();

  // It is necessary to indicate that the background job
  // is about to start to ensure correct GUI state transitions.
  // This should be done still by the main thread, otherwise
  // GUI receives corresponding signal with fatally long delay.
  aPEntry.SetProgressStatus(Progress_Running);

  ActData_FuncExecutionTask*
    aTask = new( tbb::task::allocate_root() ) ActData_FuncExecutionTask(thePNotifier, theModel, theData);

  if ( theModel->FuncExecutionFlags() & ActAPI_IModel::ExecFlags_ForceNoDetach )
  {
    tbb::task::spawn_root_and_wait(*aTask);
  }
  else
  {
    tbb::task::enqueue(*aTask); // Non-blocking fork
  }

  return aTask;
}

//! Performs actual executing routine. Note that the code of this
//! method is executed in a distinct thread. Moreover, this code creates
//! additional TBB tasks (threads).
//! \return next task to execute -- NULL in our case.
tbb::task* ActData_FuncExecutionTask::execute()
{
  // Execute dependency graph
  Standard_Integer aRes = ActAPI_IModel::Execution_Undefined;
  try
  {
    m_model->FuncProgressNotifierOn();
    m_model->FuncExecuteAll(Standard_False, m_txData);
    m_model->FuncProgressNotifierOff();
  }
  catch ( ... )
  {
    aRes = ActAPI_IModel::Execution_Failed;
  }

  // Set resulting status of the parallel job and notify implicitly.
  // NOTE: Progress_Running status should be forced by the main thread
  // before the parallel job is started, to ensure that GUI prepares
  // for background job execution.
  // See also Launch() method.
  ActAPI_ProgressEntry aPEntry(m_PNotifier);
  if ( aPEntry.IsCancelling() ) // Cancellation requested
    aPEntry.SetProgressStatus(Progress_Cancelled);
  else if ( ActAPI_IModel::IsExecutionFailed(aRes) )
    aPEntry.SetProgressStatus(Progress_Failed);
  else
    aPEntry.SetProgressStatus(Progress_Succeeded);

  return NULL; // No next task to execute
}
