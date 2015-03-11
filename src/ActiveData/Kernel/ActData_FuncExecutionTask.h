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

#ifndef ActData_FuncExecutionTask_HeaderFile
#define ActData_FuncExecutionTask_HeaderFile

// Active Data includes
#include <ActData_Common.h>

// Active Data (API) includes
#include <ActAPI_IModel.h>
#include <ActAPI_IProgressNotifier.h>

// Intel TBB includes
#include <parallel_for.h>
#include <tbb_thread.h>

//! \ingroup AD_DF
//!
//! Specific invocation mechanism used to execute the dependency graph
//! in a distinct enqueued TBB task. Normally, you use this mechanism
//! in order to fork the algorithm's working thread from the GUI one.
class ActData_FuncExecutionTask : public tbb::task
{
public:

  ActData_EXPORT static ActData_FuncExecutionTask*
    Launch(const Handle(ActAPI_IProgressNotifier)& thePNotifier,
           const Handle(ActAPI_IModel)& theModel,
           const ActAPI_TxData& theData);

private:

  ActData_FuncExecutionTask(const Handle(ActAPI_IProgressNotifier)& thePNotifier,
                            const Handle(ActAPI_IModel)& theModel,
                            const ActAPI_TxData& theData);

  virtual tbb::task* execute();

// Input data for task:
private:

  //! Progress Notifier.
  Handle(ActAPI_IProgressNotifier) m_PNotifier;

  //! Data Model instance.
  Handle(ActAPI_IModel) m_model;

  //! Transaction data.
  ActAPI_TxData m_txData;

};

#endif
