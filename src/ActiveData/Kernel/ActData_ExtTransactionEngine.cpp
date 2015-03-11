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
#include <ActData_ExtTransactionEngine.h>

//! Creates a new instance of Transaction Engine charged with the CAF Document.
//! \param Doc [in] CAF Document corresponding to the actual Data Model.
//! \param UndoLimit [in] Undo Limit to set.
ActData_ExtTransactionEngine::ActData_ExtTransactionEngine(const Handle(TDocStd_Document)& Doc,
                                                           const Standard_Integer UndoLimit)
: ActData_TransactionEngine(Doc, UndoLimit)
{
}

//! Customized Undo method for extended transactions.
//! \param theNbUndoes [in] number of Undo operations to perform one-by-one.
void ActData_ExtTransactionEngine::Undo(const Standard_Integer theNbUndoes)
{
  if ( m_undoData.IsEmpty() )
    return; // There is nothing to Undo

  // Perform actual Undo
  ActData_TransactionEngine::Undo(theNbUndoes);

  // Juggle naming stack
  for ( Standard_Integer NbDone = 0; NbDone < theNbUndoes; NbDone++ )
  {
    m_redoData.Prepend( m_undoData.First() );
    m_undoData.Remove(1);
  }
}

//! Customized Redo method for extended transactions.
//! \param theNbRedoes [in] number of Redo operations to perform one-by-one.
void ActData_ExtTransactionEngine::Redo(const Standard_Integer theNbRedoes)
{
  if ( m_redoData.IsEmpty() )
    return; // There is nothing to Redo

  // Perform actual Redo
  ActData_TransactionEngine::Redo(theNbRedoes);

  // Juggle naming stack
  for ( Standard_Integer NbDone = 0; NbDone < theNbRedoes; NbDone++ )
  {
    m_undoData.Prepend( m_redoData.First() );
    m_redoData.Remove(1);
  }
}

//! Commits current transaction.
//! \param theData [in] user-data to bind to transaction being committed.
void ActData_ExtTransactionEngine::CommitCommandExt(const ActAPI_TxData& theData)
{
  // Perform general commit first, so that Modification Delta is passed to
  // OCCT native stack
  ActData_TransactionEngine::CommitCommand();

  // Juggle TxData stack
  m_undoData.Prepend(theData);
  m_redoData.Clear();

  // Proceed with Undo Limit
  Standard_Integer UndoLimit = m_doc->GetUndoLimit();
  if ( m_undoData.Length() > UndoLimit )
    m_undoData.Remove( m_undoData.Length() );
}

//! Accessor for the sequence of user data associated with Undo Modification
//! Deltas. This method returns only those Data containers which lie within
//! the given depth.
//! \param theDepth [in] depth to limit the collection of data items
//!        being accessed.
//! \return collection of user data for Undo Modification Deltas.
Handle(ActAPI_HTxDataSeq)
  ActData_ExtTransactionEngine::GetUndoData(const Standard_Integer theDepth) const
{
  Handle(ActAPI_HTxDataSeq) aResult = new ActAPI_HTxDataSeq();
  for ( Standard_Integer i = 1; i <= Min(m_undoData.Length(), theDepth); ++i )
    aResult->Append( m_undoData.Value(i) );

  return aResult;
}

//! Accessor for the sequence of user data associated with Redo Modification
//! Deltas. This method returns only those Data containers which lie within
//! the given depth.
//! \param theDepth [in] depth to limit the collection of data items
//!        being accessed.
//! \return collection of user data for Undo Modification Deltas.
Handle(ActAPI_HTxDataSeq)
  ActData_ExtTransactionEngine::GetRedoData(const Standard_Integer theDepth) const
{
  Handle(ActAPI_HTxDataSeq) aResult = new ActAPI_HTxDataSeq();
  for ( Standard_Integer i = 1; i <= theDepth; ++i )
    aResult->Append( m_redoData.Value(i) );

  return aResult;
}
