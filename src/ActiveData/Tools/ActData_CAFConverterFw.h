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

#ifndef ActData_CAFConverterFw_HeaderFile
#define ActData_CAFConverterFw_HeaderFile

// Active Data includes
#include <ActData_CAFConverterBase.h>

//! \ingroup AD_DF
//!
//! Versions supported by converter.
enum ActData_VersionLog
{
  VersionLog_Lot1Iteration4 = 0x00400,
  VersionLog_Lot2Iteration1 = 0x00500,
  VersionLog_Lot2Iteration2 = 0x00600,
  VersionLog_Lot2Iteration3 = 0x00700,
  VersionLog_Production1    = 0x00800,
  VersionLog_Production2    = 0x10000,
  VersionLog_Current = VersionLog_Production1
};

//! \ingroup AD_DF
//!
//! Namespace for all available conversion routines.
namespace ActData_ConversionLibrary
{
  Standard_Boolean v040_to_v050(Handle(ActAPI_IModel)& theModel,
                                const Handle(Message_ProgressIndicator)& theProgress);

  Standard_Boolean v050_to_v060(Handle(ActAPI_IModel)& theModel,
                                const Handle(Message_ProgressIndicator)& theProgress);

  Standard_Boolean v060_to_v070(Handle(ActAPI_IModel)& theModel,
                                const Handle(Message_ProgressIndicator)& theProgress);

  Standard_Boolean v070_to_v080(Handle(ActAPI_IModel)& theModel,
                                const Handle(Message_ProgressIndicator)& theProgress);

  Standard_Boolean v080_to_v100(Handle(ActAPI_IModel)& theModel,
                                const Handle(Message_ProgressIndicator)& theProgress);
};

#endif
