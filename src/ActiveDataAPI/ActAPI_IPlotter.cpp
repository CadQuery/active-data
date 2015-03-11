//-----------------------------------------------------------------------------
// Created on: April 2016
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
#include <ActAPI_IPlotter.h>

//-----------------------------------------------------------------------------

//! Returns a "good" color index for the passed "some" index. This method
//! attempts to choose the least continuous colors, so that to make them
//! highly distinguishable.
//! \param index [in] your "some" index.
//! \return our "good" color index for you.
Quantity_NameOfColor ActAPI_IPlotter::Color_Sparse(const int index)
{
  switch ( index )
  {
    case 0:  return Quantity_NOC_RED;
    case 1:  return Quantity_NOC_GREEN;
    case 2:  return Quantity_NOC_BLUE1;
    case 3:  return Quantity_NOC_YELLOW;
    case 4:  return Quantity_NOC_GOLD;
    case 5:  return Quantity_NOC_ORANGE;
    case 6:  return Quantity_NOC_MAGENTA1;
    case 7:  return Quantity_NOC_SNOW;
    case 8:  return Quantity_NOC_SKYBLUE;
    case 9:  return Quantity_NOC_PINK;
    case 10: return Quantity_NOC_VIOLET;
    case 11: return Quantity_NOC_CYAN1;
    case 12: return Quantity_NOC_SPRINGGREEN;
    case 13: return Quantity_NOC_TOMATO3;
    case 14: return Quantity_NOC_DARKVIOLET;
    case 15: return Quantity_NOC_DODGERBLUE3;
    case 16: return Quantity_NOC_IVORY;
    case 17: return Quantity_NOC_ROYALBLUE;
    default: break;
  };

  return (Quantity_NameOfColor) index;
}

//-----------------------------------------------------------------------------

//! Destructor.
ActAPI_IPlotter::~ActAPI_IPlotter()
{}
