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
#include <ActData_BinStorageDriver.h>

// Active Data includes
#include <ActData_BinDrivers.h>

// OCCT includes
#include <BinDrivers.hxx>

#undef COUT_DEBUG

//! Default constructor.
ActData_BinStorageDriver::ActData_BinStorageDriver()
: BinDrivers_DocumentStorageDriver()
{
}

//! Extends the standard Driver Table with ACT custom Drivers.
//! \param theMsgDriver [in] Message Driver.
//! \return Driver Table.
Handle(BinMDF_ADriverTable)
  ActData_BinStorageDriver::AttributeDrivers(const Handle(CDM_MessageDriver)& theMsgDriver)
{
  // Standard drivers
  Handle(BinMDF_ADriverTable) aTable = BinDrivers::AttributeDrivers(theMsgDriver);

  // Custom drivers
  ActData_BinDrivers::AddDrivers(aTable, theMsgDriver);

  return aTable;
}
