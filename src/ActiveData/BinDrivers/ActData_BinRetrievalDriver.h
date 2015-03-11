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

#ifndef ActData_BinRetrievalDriver_HeaderFile
#define ActData_BinRetrievalDriver_HeaderFile

// Active Data includes
#include <ActData_Common.h>

// OCCT includes
#pragma warning(push, 0)
#include <BinDrivers_DocumentRetrievalDriver.hxx>
#include <BinMDF_ADriverTable.hxx>
#include <CDM_MessageDriver.hxx>
#pragma warning(pop)

DEFINE_STANDARD_HANDLE(ActData_BinRetrievalDriver, BinDrivers_DocumentRetrievalDriver)

//! \ingroup AD_DF
//!
//! Retrieval Driver for ACT Document extended with custom Attributes.
class ActData_BinRetrievalDriver : public BinDrivers_DocumentRetrievalDriver
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_BinRetrievalDriver, BinDrivers_DocumentRetrievalDriver)

// Construction:
public:

  ActData_EXPORT ActData_BinRetrievalDriver();

// Kernel:
public:

  ActData_EXPORT virtual Handle(BinMDF_ADriverTable)
    AttributeDrivers(const Handle(CDM_MessageDriver)& theMsgDriver);

};

#endif
