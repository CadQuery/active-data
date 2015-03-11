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

#ifndef ActData_CAFConverter_HeaderFile
#define ActData_CAFConverter_HeaderFile

// Active Data includes
#include <ActData_CAFConverterBase.h>
#include <ActData_Common.h>

// Active Data (API) includes
#include <ActAPI_IProgressNotifier.h>

DEFINE_STANDARD_HANDLE(ActData_CAFConverter, Standard_Transient)

//! \ingroup AD_DF
//!
//! Utility class containing conversion methods to support backward
//! compatibility mechanism at the level of the FRAMEWORK.
class ActData_CAFConverter : public Standard_Transient
{
public:

  DEFINE_STANDARD_RTTI_INLINE(ActData_CAFConverter, Standard_Transient)

public:

  ActData_EXPORT
    ActData_CAFConverter(const ActData_ConversionStream& theCStream);

  ActData_EXPORT Standard_Boolean
    Perform(Handle(ActAPI_IModel)& theModel,
            const Standard_Integer theOldVer,
            const Standard_Integer theNewVer,
            const Handle(Message_ProgressIndicator)& theProgress);

private:

  void registerConversionRoutine(const ActData_ConversionTuple& theTuple);

private:

  ActData_ConversionMap m_conversionMap;

};

#endif
