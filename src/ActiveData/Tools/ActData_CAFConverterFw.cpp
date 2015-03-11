//-----------------------------------------------------------------------------
// Created on: June 2012
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
#include <ActData_CAFConverterFw.h>

// Active Data includes
#include <ActData_BaseModel.h>
#include <ActData_CAFConversionAsset.h>

//! Performs conversion of the passed Data Model from version 0.4.0 to
//! version 0.5.0 from the framework's perspective.
//! \param theModel [in] Data Model to convert.
//! \param theProgress [in] Progress Indicator.
//! \return true in case of success, false -- otherwise.
Standard_Boolean ActData_ConversionLibrary::v040_to_v050(Handle(ActAPI_IModel)& theModel,
                                                         const Handle(Message_ProgressIndicator)& ActData_NotUsed(theProgress))
{
  // Actualize both framework & application versions by setting their actual values
  ActData_CAFConversionAsset(theModel).ActualizeVersions();

  return Standard_True;
}

//! Performs conversion of the passed Data Model from version 0.5.0 to
//! version 0.6.0 from the framework's perspective.
//! \param theModel [in] Data Model to convert.
//! \param theProgress [in] Progress Indicator.
//! \return true in case of success, false -- otherwise.
Standard_Boolean ActData_ConversionLibrary::v050_to_v060(Handle(ActAPI_IModel)& theModel,
                                                         const Handle(Message_ProgressIndicator)& ActData_NotUsed(theProgress))
{
  // Actualize both framework & application versions by setting their actual values
  ActData_CAFConversionAsset(theModel).ActualizeVersions();

  return Standard_True;
}

//! Performs conversion of the passed Data Model from version 0.6.0 to
//! version 0.7.0 from the framework's perspective.
//! \param theModel [in] Data Model to convert.
//! \param theProgress [in] Progress Indicator.
//! \return true in case of success, false -- otherwise.
Standard_Boolean ActData_ConversionLibrary::v060_to_v070(Handle(ActAPI_IModel)& theModel,
                                                         const Handle(Message_ProgressIndicator)& ActData_NotUsed(theProgress))
{
  // Actualize both framework & application versions by setting their actual values
  ActData_CAFConversionAsset(theModel).ActualizeVersions();

  return Standard_True;
}

//! Performs conversion of the passed Data Model from version 0.7.0 to
//! version 0.8.0 from the framework's perspective.
//! \param theModel [in] Data Model to convert.
//! \param theProgress [in] Progress Indicator.
//! \return true in case of success, false -- otherwise.
Standard_Boolean ActData_ConversionLibrary::v070_to_v080(Handle(ActAPI_IModel)& theModel,
                                                         const Handle(Message_ProgressIndicator)& ActData_NotUsed(theProgress))
{
  // Actualize both framework & application versions by setting their actual values
  ActData_CAFConversionAsset(theModel).ActualizeVersions();

  return Standard_True;
}

//! Performs conversion of the passed Data Model from version 0.8.0 to
//! version 1.0.0 from the framework's perspective.
//! \param theModel [in] Data Model to convert.
//! \param theProgress [in] Progress Indicator.
//! \return true in case of success, false -- otherwise.
Standard_Boolean ActData_ConversionLibrary::v080_to_v100(Handle(ActAPI_IModel)& theModel,
                                                         const Handle(Message_ProgressIndicator)& ActData_NotUsed(theProgress))
{
  // Actualize both framework & application versions by setting their actual values
  ActData_CAFConversionAsset(theModel).ActualizeVersions();

  return Standard_True;
}
