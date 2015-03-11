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
#include <ActData_Plugin.h>

// Active Data includes
#include <ActData_BinStorageDriver.h>
#include <ActData_BinRetrievalDriver.h>

// OCCT includes
#include <BinLDrivers.hxx>
#include <Plugin_Macro.hxx>
#include <Standard_GUID.hxx>

#undef COUT_DEBUG

#pragma warning(disable: 4190)

//! Class exporting the entry point into Active Data for dynamic
//! loading of Storage/Retrieval Drivers.
class ActDataDrivers 
{
public:

  ActData_EXPORT static Handle(Standard_Transient)
    Factory(const Standard_GUID& theGUID);

};

static Standard_GUID BinStorageDriver  ("0ac06b28-65c5-428e-86a5-2a35fbe7c4a4");
static Standard_GUID BinRetrievalDriver("0ac06b28-65c5-428e-86a5-2a35fbe7c4a5");

//! Entry point for Plugin. Returns Storage/Retrieval Driver by the passed
//! GUID.
//! \param theGUID [in] Driver's GUID.
//! \return Driver instance.
Handle(Standard_Transient) ActDataDrivers::Factory(const Standard_GUID& theGUID)
{
  if ( theGUID == BinStorageDriver )
  {
#if defined ACT_DEBUG && defined COUT_DEBUG
    cout << "ActDataDrivers: BINARY Storage Plugin" << endl;
#endif
    static Handle(ActData_BinStorageDriver) DRV_Storage = new ActData_BinStorageDriver();
    return DRV_Storage;
  }

  if ( theGUID == BinRetrievalDriver )
  {
#if defined ACT_DEBUG && defined COUT_DEBUG
    cout << "ActDataDrivers: BINARY Retrieval Plugin" << endl;
#endif
    static Handle(ActData_BinRetrievalDriver) DRV_Retrieval = new ActData_BinRetrievalDriver();
    return DRV_Retrieval;
  }

  return BinLDrivers::Factory(theGUID);
}

// Declare entry point
PLUGIN(ActDataDrivers)

#pragma warning(default: 4190)
