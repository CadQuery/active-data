//-----------------------------------------------------------------------------
// Created on: May 2012
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
#include <ActData_FuncExecutionCtx.h>

// Active Data includes
#include <ActData_DependencyAnalyzer.h>
#include <ActData_DependencyGraphIterator.h>
#include <ActData_LogBook.h>
#include <ActData_ParameterFactory.h>
#include <ActData_Utils.h>

// OCCT includes
#include <TColStd_MapIteratorOfMapOfInteger.hxx>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hxx>
#include <TFunction_DoubleMapIteratorOfDoubleMapOfIntegerLabel.hxx>
#include <TFunction_IFunction.hxx>
#include <TFunction_Scope.hxx>

//-----------------------------------------------------------------------------
// Construction methods
//-----------------------------------------------------------------------------

//! Default constructor.
ActData_FuncExecutionCtx::ActData_FuncExecutionCtx()
: Standard_Transient()
{
  this->ProgressNotifierOff();
  this->UnFreezeGraph();
}

//-----------------------------------------------------------------------------
// Custom user data per function type
//-----------------------------------------------------------------------------

//! Binds custom shared user data to the Tree Function TYPE. This allows
//! different kinds of Tree Functions being associated with some standalone
//! data container, e.g. Progress Collector or any other service-layer
//! object.
//! \param theGUID [in] GUID of Tree Function type.
//! \param theUserData [in] actual data container.
void ActData_FuncExecutionCtx::BindUserData(const Standard_GUID& theGUID,
                                            const Handle(Standard_Transient)& theUserData)
{
  if ( m_funcDataMap.IsNull() )
    m_funcDataMap = new HFunctionDataMap();

  if ( m_funcDataMap->IsBound(theGUID) )
    m_funcDataMap->UnBind(theGUID);

  m_funcDataMap->Bind(theGUID, theUserData);
}

//! Nullifies custom shared user data for the given Tree Function TYPE.
//! \param theGUID [in] GUID of Tree Function type.
void ActData_FuncExecutionCtx::UnBindUserData(const Standard_GUID& theGUID)
{
  if ( m_funcDataMap.IsNull() )
    return;

  m_funcDataMap->UnBind(theGUID);
}

//! Returns user data associated with the given Tree Function type.
//! \param theGUID [in] GUID of Tree Function type.
//! \return user data container.
Handle(Standard_Transient)
  ActData_FuncExecutionCtx::AccessUserData(const Standard_GUID& theGUID)
{
  if ( m_funcDataMap.IsNull() || !m_funcDataMap->IsBound(theGUID) )
    return NULL;

  return m_funcDataMap->Find(theGUID);
}

//! Cleans up the user data map.
void ActData_FuncExecutionCtx::ReleaseUserData()
{
  if ( !m_funcDataMap.IsNull() )
    m_funcDataMap->Clear();
}

//-----------------------------------------------------------------------------
// Transaction data
//-----------------------------------------------------------------------------

//! Sets transaction data for execution context.
//! \param theData [in] transaction data to set.
void ActData_FuncExecutionCtx::SetTxData(const ActAPI_TxData& theData)
{
  m_txData = theData;
}

//! Returns transaction data associated with execution context.
//! \return transaction data.
const ActAPI_TxData& ActData_FuncExecutionCtx::AccessTxData() const
{
  return m_txData;
}

//! Cleans up transaction data associated with execution context.
void ActData_FuncExecutionCtx::ReleaseTxData()
{
  m_txData = 0;
}

//-----------------------------------------------------------------------------
// Progress Notification
//-----------------------------------------------------------------------------

//! Sets the global Progress Notifier.
//! \param thePNotifier [in] Progress Notifier instance to set.
void ActData_FuncExecutionCtx::SetProgressNotifier(const Handle(ActAPI_IProgressNotifier)& thePNotifier)
{
  m_PNotifier = thePNotifier;
}

//! Accessor for the global Progress Notifier.
//! \return global Progress Notifier.
Handle(ActAPI_IProgressNotifier) ActData_FuncExecutionCtx::ProgressNotifier() const
{
  return m_PNotifier;
}

//! Returns true if Progress Notification is ENABLED, false -- otherwise.
//! \return true/false.
Standard_Boolean ActData_FuncExecutionCtx::IsProgressNotifierOn() const
{
  return m_bProgressNotifierOn;
}

//! Sets Progress Notification ENABLED.
void ActData_FuncExecutionCtx::ProgressNotifierOn()
{
  m_bProgressNotifierOn = Standard_True;
}

//! Sets Progress Notification DISABLED.
void ActData_FuncExecutionCtx::ProgressNotifierOff()
{
  m_bProgressNotifierOn = Standard_False;
}

//-----------------------------------------------------------------------------
// Graph freezing
//-----------------------------------------------------------------------------

//! Sets Execution Graph to be frozen.
void ActData_FuncExecutionCtx::FreezeGraph()
{
  m_bIsGraphFrozen = Standard_True;
}

//! Checks whether Execution Graph is frozen or not.
//! \return true/false.
Standard_Boolean ActData_FuncExecutionCtx::IsGraphFrozen() const
{
  return m_bIsGraphFrozen;
}

//! Sets Execution Graph to be unfrozen.
void ActData_FuncExecutionCtx::UnFreezeGraph()
{
  m_bIsGraphFrozen = Standard_False;
}

//-----------------------------------------------------------------------------
// Managing dependency graph
//-----------------------------------------------------------------------------

//! Rebuild dependency graph.
//! \param theModel [in] Data Model instance to rebuild the dependency
//!        graph for.
void ActData_FuncExecutionCtx::UpdateDependencies(const Handle(ActData_BaseModel)& theModel)
{
  TDF_Label aRootLab = theModel->RootLabel();
  TFunction_IFunction::UpdateDependencies(aRootLab);
}

//! Checks the pre-built dependency graph (see method UpdateDependencies) on
//! connectivity anomalies and returns the validation result.
//! \param theModel [in] Data Model instance to check the dependency
//!        graph for.
//! \return validation result.
Standard_Integer
  ActData_FuncExecutionCtx::CheckDependencyGraph(const Handle(ActData_BaseModel)& theModel)
{
  Handle(ActAPI_HParameterList) aFaultyLoop = new ActAPI_HParameterList;
  return CheckDependencyGraph(theModel, aFaultyLoop);
}

//! Checks the pre-built dependency graph (see method UpdateDependencies) on
//! connectivity anomalies and returns the validation result.
//! \param theModel [in] Data Model instance to check the dependency
//!        graph for.
//! \param theFaultyParams [out] detected faulty Parameters.
//! \return validation result.
Standard_Integer
  ActData_FuncExecutionCtx::CheckDependencyGraph(const Handle(ActData_BaseModel)& theModel,
                                                 Handle(ActAPI_HParameterList)& theFaultyParams)
{
  Handle(ActData_DependencyAnalyzer) aChecker = new ActData_DependencyAnalyzer(theModel);
  aChecker->DetectLoops();
  theFaultyParams = aChecker->CyclicParameters();
  return aChecker->GetResultStatus();
}

//-----------------------------------------------------------------------------
// Forced execution
//-----------------------------------------------------------------------------

//! Queues the given Parameter for forced execution.
//! \param theParam [in] Nodal Parameter.
void ActData_FuncExecutionCtx::Force(const Handle(ActData_TreeFunctionParameter)& theFuncParam)
{
  TDF_Label aLogBookSection =
    theFuncParam->RootLabel().Root().FindChild(ActData_BaseModel::StructureTag_LogBook);

  ActData_LogBook(aLogBookSection).Force(theFuncParam);
}

//-----------------------------------------------------------------------------
// Heavy deployment
//-----------------------------------------------------------------------------

//! Queues the given Parameter for heavy deployment.
//! \param theParam [in] Nodal Parameter.
void ActData_FuncExecutionCtx::Deploy(const Handle(ActData_TreeFunctionParameter)& theFuncParam)
{
  if ( !theFuncParam->IsHeavyFunction() )
    return;

  TDF_Label aLogBookSection =
    theFuncParam->RootLabel().Root().FindChild(ActData_BaseModel::StructureTag_LogBook);

  ActData_LogBook(aLogBookSection).HeavyDeploy(theFuncParam);
}

//! Grants heavy deployment for sub-graphs starting from the passed roots.
//! Each root is forced for execution. Each heavy Tree Function gets
//! DEPLOYMENT pass.
//! \param theModel [in] Data Model instance.
//! \param PEntry [in] Progress Entry.
void ActData_FuncExecutionCtx::ForceDeployPropagation(const Handle(ActData_BaseModel)& theModel,
                                                      ActAPI_ProgressEntry PEntry)
{
  if ( m_functions2Deploy.IsNull() || m_functions2Deploy->IsEmpty() )
    return; // Nothing to deploy

  // Build graph model
  Handle(ActData_DependencyGraph) Graph = new ActData_DependencyGraph(theModel);

  /* ================================================
   *  Deploy each hook with all its succeeding items
   * ================================================ */

  // Iterate over the root Tree Function Parameters
  for ( ActAPI_ParameterList::Iterator hit( *m_functions2Deploy.operator->() ); hit.More(); hit.Next() )
  {
    Handle(ActData_TreeFunctionParameter) PFunc = ActParamTool::AsTreeFunction( hit.Value() );
    this->Force(PFunc); // Force root for execution

    // Iterate graph in reverse order: from succeeding Function to the
    // preceeding one
    Standard_Boolean proceed = Standard_True;
    ActData_DependencyGraphIterator GraphIt( Graph, Graph->VertexByFunction(PFunc), Standard_True );
    do
    {
      Standard_Integer V = GraphIt.Current();
      Handle(ActAPI_ITreeFunction) TFunc = Graph->DataByVertex(V).TreeFunction;

      if ( TFunc->IsHeavy() )
      {
        Handle(ActData_TreeFunctionParameter) FuncP = Graph->FunctionByVertex(V);

        // Force for execution only if results are in pending state,
        // so let us check that there are some pending data
        Handle(ActAPI_HParameterList) Results = FuncP->Results();
        Standard_Boolean isPending = Standard_False;
        if ( !Results.IsNull() )
        {
          for ( Standard_Integer r = 1; r <= Results->Length(); ++r )
            if ( Results->Value(r)->IsPendingData() )
            {
              isPending = Standard_True;
              break;
            }
        }

        // Force execution in case of pending data
        if ( isPending )
        {
          this->Force(FuncP); // Initiate execution
          this->Deploy(FuncP); // Allow heavy execution
        }

        // Put logging message
        if ( !TFunc.IsNull() )
          PEntry.SendLogMessage( LogInfo(Normal) << "HEAVY_FUNC_DEPLOY_NEXTFUNC" << TFunc->GetName() );
      }

      // Go to the next Function
      if ( GraphIt.More() )
        GraphIt.Next();
      else
        proceed = Standard_False;
    }
    while ( proceed );
  }
}
