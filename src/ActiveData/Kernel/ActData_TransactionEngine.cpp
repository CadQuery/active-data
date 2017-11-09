//-----------------------------------------------------------------------------
// Created on: July 2012
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

// Own include
#include <ActData_TransactionEngine.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

// OCCT includes
#include <TDF_Delta.hxx>
#include <TDF_LabelList.hxx>
#include <TDF_ListIteratorOfAttributeDeltaList.hxx>
#include <TDF_ListIteratorOfDeltaList.hxx>
#include <TDF_ListIteratorOfLabelList.hxx>

#define ERR_TRANSACTION_DEPLOYMENT_OFF "Transactions are OFF"
#define ERR_NULL_DOC "Document is NULL"
#define ERR_TR_ALREADY_OPENED "Command is already opened"

#undef COUT_DEBUG

//-----------------------------------------------------------------------------
// Construction & initialization
//-----------------------------------------------------------------------------

//! Creates a new instance of Transaction Engine charged with the CAF Document.
//! \param Doc [in] CAF Document corresponding to the actual Data Model.
//! \param UndoLimit [in] Undo limit to set.
ActData_TransactionEngine::ActData_TransactionEngine(const Handle(TDocStd_Document)& Doc,
                                                     const Standard_Integer UndoLimit)
: Standard_Transient()
{
  m_iUndoLimit = UndoLimit;
  m_bIsActiveTransaction = Standard_False;
  this->init(Doc);
}

//! Initializes the Transaction Engine with the given CAF Document.
//! \param Doc [in] CAF Document corresponding to the actual Data Model.
void ActData_TransactionEngine::init(const Handle(TDocStd_Document)& Doc)
{
  m_doc = Doc;
  m_doc->SetUndoLimit(m_iUndoLimit);

  this->EnableTransactions();
}

//-----------------------------------------------------------------------------
// Service functionality:
//-----------------------------------------------------------------------------

void ActData_TransactionEngine::Release()
{
  if ( !m_doc.IsNull() )
    m_doc.Nullify();

  m_bIsActiveTransaction = Standard_False;
}

//-----------------------------------------------------------------------------
// Kernel methods
//-----------------------------------------------------------------------------

//! Disables the fundamental requirement to perform any modification in a
//! transactional scope.
void ActData_TransactionEngine::DisableTransactions()
{
  m_doc->SetModificationMode(Standard_False);
}

//! Enables the fundamental requirement to perform any modification in a
//! transactional scope.
void ActData_TransactionEngine::EnableTransactions()
{
  m_doc->SetModificationMode(Standard_True);
}

//! Starts new transactional scope.
void ActData_TransactionEngine::OpenCommand()
{
  if ( this->isTransactionModeOff() )
    Standard_ProgramError::Raise(ERR_TRANSACTION_DEPLOYMENT_OFF);

  if ( m_doc.IsNull() )
    Standard_ProgramError::Raise(ERR_NULL_DOC);

  if ( m_bIsActiveTransaction )
    Standard_ProgramError::Raise(ERR_TR_ALREADY_OPENED);

  m_doc->OpenCommand();
  m_bIsActiveTransaction = Standard_True;
}

//! Commits current transaction.
void ActData_TransactionEngine::CommitCommand()
{
  if ( this->isTransactionModeOff() )
    Standard_ProgramError::Raise(ERR_TRANSACTION_DEPLOYMENT_OFF);

  if ( m_doc.IsNull() )
    Standard_ProgramError::Raise(ERR_NULL_DOC);

  m_doc->CommitCommand();
  m_bIsActiveTransaction = Standard_False;
}

//! Returns true if any command is opened, false -- otherwise.
//! \return true/false.
Standard_Boolean ActData_TransactionEngine::HasOpenCommand() const
{
  if ( this->isTransactionModeOff() )
    Standard_ProgramError::Raise(ERR_TRANSACTION_DEPLOYMENT_OFF);

  if ( m_doc.IsNull() )
    Standard_ProgramError::Raise(ERR_NULL_DOC);

  return m_bIsActiveTransaction;
}

//! Rolls back current transaction.
void ActData_TransactionEngine::AbortCommand()
{
  if ( this->isTransactionModeOff() )
    Standard_ProgramError::Raise(ERR_TRANSACTION_DEPLOYMENT_OFF);

  if ( m_doc.IsNull() )
    Standard_ProgramError::Raise(ERR_NULL_DOC);

  m_doc->AbortCommand();
  m_bIsActiveTransaction = Standard_False;
}

//! Performs Undo operation.
//! \param theNbUndoes [in] number of Undo operations to perform one-by-one.
void ActData_TransactionEngine::Undo(const Standard_Integer theNbUndoes)
{
  if ( this->isTransactionModeOff() )
    Standard_ProgramError::Raise(ERR_TRANSACTION_DEPLOYMENT_OFF);

  if ( m_doc.IsNull() )
    Standard_ProgramError::Raise(ERR_NULL_DOC);

  // Get Parameters which are going to be affected by Undo operation with
  // the given depth
  Handle(ActAPI_HParameterMap) anAffectedParams = this->parametersToUndo(theNbUndoes);

  // Perform Undoes one-by-one
  for ( Standard_Integer NbDone = 0; NbDone < theNbUndoes; NbDone++ )
  {
    m_doc->Undo();
  }

  // Now touch the affected Parameters so that actualizing their MTime
  this->touchParameters(anAffectedParams);

  m_bIsActiveTransaction = Standard_False;
}

//! Returns the number of available Undo deltas.
//! \return number of available Undo deltas.
Standard_Integer ActData_TransactionEngine::NbUndos() const
{
  if ( this->isTransactionModeOff() )
    Standard_ProgramError::Raise(ERR_TRANSACTION_DEPLOYMENT_OFF);

  if ( m_doc.IsNull() )
    Standard_ProgramError::Raise(ERR_NULL_DOC);

  return m_doc->GetAvailableUndos();
}

//! Performs Redo operation.
//! \param theNbRedoes [in] number of Redo operations to perform one-by-one.
void ActData_TransactionEngine::Redo(const Standard_Integer theNbRedoes)
{
  if ( this->isTransactionModeOff() )
    Standard_ProgramError::Raise(ERR_TRANSACTION_DEPLOYMENT_OFF);

  if ( m_doc.IsNull() )
    Standard_ProgramError::Raise(ERR_NULL_DOC);

  // Get Parameters which are going to be affected by Redo operation with
  // the given depth
  Handle(ActAPI_HParameterMap) anAffectedParams = this->parametersToRedo(theNbRedoes);

  // Perform Redoes one-by-one
  for ( Standard_Integer NbDone = 0; NbDone < theNbRedoes; NbDone++ )
  {
    m_doc->Redo();
  }

  // Now touch the affected Parameters so that actualizing their MTime
  this->touchParameters(anAffectedParams);

  m_bIsActiveTransaction = Standard_False;
}

//! Returns the number of available Redo deltas.
//! \return number of available Redo deltas.
Standard_Integer ActData_TransactionEngine::NbRedos() const
{
  if ( this->isTransactionModeOff() )
    Standard_ProgramError::Raise(ERR_TRANSACTION_DEPLOYMENT_OFF);

  if ( m_doc.IsNull() )
    Standard_ProgramError::Raise(ERR_NULL_DOC);

  return m_doc->GetAvailableRedos();
}

//-----------------------------------------------------------------------------
// Services for internal & friend usage only
//-----------------------------------------------------------------------------

//! Collects the Nodal Parameters which are going to affected by Undo
//! operation with the given depth. This method must be invoked BEFORE
//! actual Undo is launched.
//! \param theNbUndoes [in] Undo depth.
//! \return collection of affected Parameters.
Handle(ActAPI_HParameterMap)
  ActData_TransactionEngine::parametersToUndo(const Standard_Integer theNbUndoes) const
{
  Handle(ActAPI_HParameterMap) aParamMap = new ActAPI_HParameterMap();

  const TDF_DeltaList& aDeltaList = m_doc->GetUndos();
  Standard_Integer aNbDeltas = aDeltaList.Extent();
  Standard_Integer aDeltaIndex = 0;
  Standard_Integer aFirstDeltaIndex = aNbDeltas - theNbUndoes + 1;

  for ( TDF_ListIteratorOfDeltaList it(aDeltaList); it.More(); it.Next() )
  {
    aDeltaIndex++;
    if ( aDeltaIndex < aFirstDeltaIndex )
      continue; // Skip the oldest non-requested Deltas

    this->addParametersByDelta(it.Value(), aParamMap);
  }

  return aParamMap;
}

//! Collects the Nodal Parameters which are going to affected by Redo
//! operation with the given depth. This method must be invoked BEFORE
//! actual Redo is launched.
//! \param theNbRedoes [in] Redo depth.
//! \return collection of affected Parameters.
Handle(ActAPI_HParameterMap)
  ActData_TransactionEngine::parametersToRedo(const Standard_Integer theNbRedoes) const
{
  Handle(ActAPI_HParameterMap) aParamMap = new ActAPI_HParameterMap();

  const TDF_DeltaList& aDeltaList = m_doc->GetRedos();
  Standard_Integer aNbDeltas = aDeltaList.Extent();
  Standard_Integer aDeltaIndex = 0;
  Standard_Integer aLastDeltaIndex = aNbDeltas - theNbRedoes + 1;

  for ( TDF_ListIteratorOfDeltaList it(aDeltaList); it.More(); it.Next() )
  {
    aDeltaIndex++;
    if ( aDeltaIndex > aLastDeltaIndex )
      break; // Skip the oldest non-requested Deltas

    this->addParametersByDelta(it.Value(), aParamMap);
  }

  return aParamMap;
}

//! Iterates over the passed collection of Parameters attempting to touch
//! those of them which are still WELL-FORMED, i.e. were not removed or
//! damaged anyhow.
//! \param theParam [in] Parameters to touch.
void ActData_TransactionEngine::touchParameters(const Handle(ActAPI_HParameterMap)& theParams)
{
  // Now touch the affected Parameters so that actualizing their MTime
  this->DisableTransactions();
  for ( ActAPI_ParameterMap::Iterator it( *theParams.operator->() ); it.More(); it.Next() )
  {
    const Handle(ActAPI_IUserParameter)& aParam = it.Value();

#if defined ACT_DEBUG && defined COUT_DEBUG
    cout << "UNDO: touching Parameter " << aParam->DynamicType()->Name() << "... ";
#endif

    if ( aParam->IsWellFormed() )
    {
      aParam->SetModified();

#if defined ACT_DEBUG && defined COUT_DEBUG
      cout << "WELL-FORMED ["
           << aParam->GetNode()->DynamicType()->Name() << "] --> Modified" << endl;
#endif
    }
#if defined ACT_DEBUG && defined COUT_DEBUG
    else
      cout << "BAD-FORMED <-- Deleted?" << endl;
#endif
  }
  this->EnableTransactions();
}

//! Retrieves Nodal Parameters affected by the given Delta and pushes them
//! into the passed collection.
//! \param theDelta [in] Delta to get Parameters for.
//! \param theMap [out] resulting cumulative map of Parameters. It is not
//!        cleaned up before usage.
void ActData_TransactionEngine::addParametersByDelta(const Handle(TDF_Delta)& theDelta,
                                                     Handle(ActAPI_HParameterMap)& theMap) const
{
  const TDF_AttributeDeltaList& attrDeltas = theDelta->AttributeDeltas();
  for ( TDF_ListIteratorOfAttributeDeltaList it(attrDeltas); it.More(); it.Next() )
  {
    Handle(TDF_AttributeDelta)& attrDelta = it.Value();
    if ( attrDelta.IsNull() )
      continue;

    TDF_Label aLab = attrDelta->Label();

    Handle(ActAPI_IUserParameter)
      aParamByLabel = ActData_ParameterFactory::ParamByChildLabelSettle(aLab);

    if ( !aParamByLabel.IsNull() && aParamByLabel->IsWellFormed() )
      theMap->Add(aParamByLabel);
  }
}

//! Checks whether the transaction deployment requirement is currently
//! enabled.
//! \return true/false.
Standard_Boolean ActData_TransactionEngine::isTransactionModeOn() const
{
  return m_doc->ModificationMode();
}

//! Checks whether the transaction deployment requirement is currently
//! disbled.
//! \return true/false.
Standard_Boolean ActData_TransactionEngine::isTransactionModeOff() const
{
  return !this->isTransactionModeOn();
}
