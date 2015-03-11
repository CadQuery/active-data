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

#ifndef ActData_ExtTransactionEngine_HeaderFile
#define ActData_ExtTransactionEngine_HeaderFile

// Active Data includes
#include <ActData_TransactionEngine.h>

// Active Data (API) includes
#include <ActAPI_TxData.h>

// OCCT includes
#include <NCollection_Sequence.hxx>
#include <TCollection_ExtendedString.hxx>

DEFINE_STANDARD_HANDLE(ActData_ExtTransactionEngine, ActData_TransactionEngine)

//! \ingroup AD_DF
//!
//! Transaction manager for transactions extended by custom user data.
class ActData_ExtTransactionEngine : public ActData_TransactionEngine
{
public:

  DEFINE_STANDARD_RTTI_INLINE(ActData_ExtTransactionEngine, ActData_TransactionEngine)

// Construction:
public:

  ActData_EXPORT
    ActData_ExtTransactionEngine(const Handle(TDocStd_Document)& Doc,
                                 const Standard_Integer UndoLimit = DEFAULT_UNDO_LIMIT);

// Kernel methods:
public:

  ActData_EXPORT virtual void
    Undo(const Standard_Integer theNbUndoes);

  ActData_EXPORT virtual void
    Redo(const Standard_Integer theNbRedoes);

  ActData_EXPORT virtual void
    CommitCommandExt(const ActAPI_TxData& theData);

// Auxiliary methods:
public:

  //! Accessor for the sequence of user data associated with Undo Modification
  //! Deltas. This collection is ordered from the most fresh transaction to
  //! the most long-standing one from the left to the right.
  //! \return collection of user data for Undo Modification Deltas.
  inline const ActAPI_TxDataSeq& GetUndoData() const
  {
    return m_undoData;
  }

  //! Accessor for the sequence of user data associated with Redo Modification
  //! Deltas. This collection is ordered from the most fresh transaction to
  //! the most long-standing one from the left to the right.
  //! \return collection of user data for Redo Modification Deltas.
  inline const ActAPI_TxDataSeq& GetRedoData() const
  {
    return m_redoData;
  }

  ActData_EXPORT Handle(ActAPI_HTxDataSeq)
    GetUndoData(const Standard_Integer theDepth) const;

  ActData_EXPORT Handle(ActAPI_HTxDataSeq)
    GetRedoData(const Standard_Integer theDepth) const;

private:

  //! Collection of user data extending the managed Modification Deltas
  //! for Undoes.
  ActAPI_TxDataSeq m_undoData;

  //! Collection of user data extending the managed Modification Deltas
  //! for Redoes.
  ActAPI_TxDataSeq m_redoData;

};

#endif
