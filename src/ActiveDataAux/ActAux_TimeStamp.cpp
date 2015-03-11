//-----------------------------------------------------------------------------
// Created on: 2012-2015
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

#include <ActAux_TimeStamp.h>

//! Generates timestamp structure for the current time.
//! \return timestamp structure.
Handle(ActAux_TimeStamp) ActAux_TimeStampTool::Generate()
{
  time_t aTime = -1;
  time(&aTime);

  Standard_Integer anInternal = 0;

#if defined(WIN32) || defined(_WIN32)
  static LONG INTERNAL = 0;
  anInternal = (Standard_Integer) InterlockedIncrement(&INTERNAL);
#else
  static unsigned long INTERNAL = 0;
  static Standard_Mutex MUTEX;

  MUTEX.Lock();
  anInternal = ++INTERNAL
  MUTEX.Unlock();
#endif

  return new ActAux_TimeStamp(aTime, anInternal);
}

//! Converts the passed timestamp structure to the corresponding array of
//! Integer values.
//! \param theUTime [in] timestamp structure to convert.
//! \return correspondent array of integer data chunks.
Handle(HIntArray)
  ActAux_TimeStampTool::AsChunked(const Handle(ActAux_TimeStamp)& theUTime)
{
  Handle(HIntArray) aResult = new HIntArray(0, 9);

  if ( theUTime->Time != -1 )
  {
    tm aTimeInfo;
    localtime_s(&aTimeInfo, &theUTime->Time);

    aResult->ChangeValue(0) = aTimeInfo.tm_sec;
    aResult->ChangeValue(1) = aTimeInfo.tm_min;
    aResult->ChangeValue(2) = aTimeInfo.tm_hour;
    aResult->ChangeValue(3) = aTimeInfo.tm_mday;
    aResult->ChangeValue(4) = aTimeInfo.tm_mon;
    aResult->ChangeValue(5) = aTimeInfo.tm_year;
    aResult->ChangeValue(6) = aTimeInfo.tm_wday;
    aResult->ChangeValue(7) = aTimeInfo.tm_yday;
    aResult->ChangeValue(8) = aTimeInfo.tm_isdst;
    aResult->ChangeValue(9) = theUTime->Internal;
  }
  else
  {
    aResult->ChangeValue(0) = -1;
    aResult->ChangeValue(1) = -1;
    aResult->ChangeValue(2) = -1;
    aResult->ChangeValue(3) = -1;
    aResult->ChangeValue(4) = -1;
    aResult->ChangeValue(5) = -1;
    aResult->ChangeValue(6) = -1;
    aResult->ChangeValue(7) = -1;
    aResult->ChangeValue(8) = -1;
    aResult->ChangeValue(9) = -1;
  }

  return aResult;
}

//! Converts the passed array of integer data chunks to timestamp structure.
//! \param theChunked [in] input array.
//! \return correspondent timestamp structure.
Handle(ActAux_TimeStamp)
  ActAux_TimeStampTool::FromChunked(const Handle(HIntArray)& theChunked)
{
  if ( theChunked.IsNull() )
    return new ActAux_TimeStamp();

  tm aTimeInfo;
  aTimeInfo.tm_sec   = theChunked->Value(0);
  aTimeInfo.tm_min   = theChunked->Value(1);
  aTimeInfo.tm_hour  = theChunked->Value(2);
  aTimeInfo.tm_mday  = theChunked->Value(3);
  aTimeInfo.tm_mon   = theChunked->Value(4);
  aTimeInfo.tm_year  = theChunked->Value(5);
  aTimeInfo.tm_wday  = theChunked->Value(6);
  aTimeInfo.tm_yday  = theChunked->Value(7);
  aTimeInfo.tm_isdst = theChunked->Value(8);
  time_t aTime = mktime(&aTimeInfo);

  return new ActAux_TimeStamp( aTime, theChunked->Value(9) );
}
