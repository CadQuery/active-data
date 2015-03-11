//-----------------------------------------------------------------------------
// Created on: November 2012
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

#ifndef ActData_SequentialFuncIterator_HeaderFile
#define ActData_SequentialFuncIterator_HeaderFile

// Active Data includes
#include <ActData.h>

// OCCT includes
#include <TDF_Label.hxx>
#include <TDF_LabelList.hxx>
#include <TFunction_ExecutionStatus.hxx>
#include <TFunction_Scope.hxx>

//! \ingroup AD_DF
//!
//! Iterator returning independent Functions available for execution at each
//! stage of Dependency Graph processing. Note that conceptually this
//! iterator is similar to standard TFunction_Iterator, however, it has
//! one important difference. Unlike the standard one, this iterator is
//! NOT designed for cases when parallel processing is required for the
//! list of currently available Functions. Indeed, this iterator sorts
//! the returned collection so that to have lower-priority Functions
//! preceeding the higher-priority ones. In fact, this iterator implements
//! prioritization mechanism for INDEPENDENT Tree Functions.
//!
//! If you do not need any priorities for your independent Functions (e.g.
//! if you would like to follow the "normal" way of execution when dependencies
//! are always expressed with inputs/outputs correspondence) and if you do not
//! want to loose parallelism possibilities at this level, prefer using
//! the standard TFunction_Iterator instead.
class ActData_SequentialFuncIterator
{
public:

  ActData_EXPORT
    ActData_SequentialFuncIterator();

  ActData_EXPORT
    ActData_SequentialFuncIterator(const TDF_Label& theAccess);

public:

  ActData_EXPORT virtual void
    Init(const TDF_Label& theAccess);

  ActData_EXPORT virtual void
    Next();

  ActData_EXPORT virtual Standard_Boolean
    More() const;

  ActData_EXPORT virtual const TDF_LabelList&
    Current() const;

  ActData_EXPORT virtual TFunction_ExecutionStatus
    GetStatus(const TDF_Label& theFunc) const;

  ActData_EXPORT virtual void
    SetStatus(const TDF_Label& theFunc,
              const TFunction_ExecutionStatus theStatus) const;

protected:

  Standard_Boolean isHighPriority(const TDF_Label& theFunc) const;

protected:

  TDF_LabelList           m_currentFunctions; //!< Current Functions.
  Handle(TFunction_Scope) m_scope;            //!< Function Scope.

};

#endif
