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

// ACT algorithmic collection includes
#include <ActAux_ArrayUtils.h>

//! Converts raw array to a handled array.
//! \param theArray [in] raw array to convert.
//! \param theNumElems [in] number of elements in the raw array.
//! \return converted array.
Handle(HRealArray) ActAux_ArrayUtils::ToRealArray(const Standard_Real*   theArray,
                                                  const Standard_Integer theNumElems)
{
  Handle(HRealArray) aResult = new HRealArray(0, theNumElems - 1);
  for ( Standard_Integer i = 0; i < theNumElems; ++i )
    aResult->SetValue(i, theArray[i]);

  return aResult;
}

//! Converts raw array to a handled array.
//! \param theArray [in] raw array to convert.
//! \param theNumElems [in] number of elements in the raw array.
//! \param theResult [out] result array.
void ActAux_ArrayUtils::ToRealArray(const Standard_Real*   theArray,
                                    const Standard_Integer theNumElems,
                                    Handle(HRealArray)&    theResult)
{
  for ( Standard_Integer i = 0; i < theNumElems; ++i )
    theResult->SetValue(i, theArray[i]);
}

//! Initializes the passed array with zeros.
//! \param theArr [in] array to nullify.
void ActAux_ArrayUtils::NullifyArr(const Handle(HRealArray)& theArr)
{
  ValuefyArr<Handle(HRealArray), Standard_Real>(theArr, 0.0);
}

//! Initializes the passed matrix with zeros.
//! \param theMx [in] matrix to nullify.
void ActAux_ArrayUtils::NullifyMx(const Handle(HRealMatrix)& theMx)
{
  for ( Standard_Integer i = theMx->LowerRow(); i <= theMx->UpperRow(); ++i )
    for ( Standard_Integer j = theMx->LowerCol(); j <= theMx->UpperCol(); ++j )
      theMx->SetValue(i, j, 0.0);
}

//! Converts the passed raw array to handled array.
//! \param theArr [in] plain array to convert.
//! \param theNum [in] number of elements in the plain array.
//! \return converted array.
Handle(HRealArray) ActAux_ArrayUtils::Convert(const Standard_Real* theArr,
                                              const Standard_Integer theNum)
{
  Handle(HRealArray) res = new HRealArray(0, theNum - 1);
  for ( Standard_Integer i = 0; i < theNum; ++i )
    res->SetValue(i, theArr[i]);

  return res;
}

//! Converts the passed raw array to handled array.
//! \param theArr [in] plain array to convert.
//! \param theNum [in] number of elements in the plain array.
//! \return converted array.
Handle(HComplexArray) ActAux_ArrayUtils::Convert(const ComplexNumber* theArr,
                                                 const Standard_Integer theNum)
{
  Handle(HComplexArray) res = new HComplexArray(0, theNum - 1);
  for ( Standard_Integer i = 0; i < theNum; ++i )
    res->SetValue(i, theArr[i]);

  return res;
}

//! Extracts amplitudes from the given complex array.
//! \param theArr [in] array of complex values to extract amplitudes for.
//! \return array of amplitudes.
Handle(HRealArray) ActAux_ArrayUtils::Amplitudes(const Handle(HComplexArray)& theArr)
{
  Handle(HRealArray) result = new HRealArray( theArr->Lower(), theArr->Upper() );
  for ( Standard_Integer i = theArr->Lower(); i <= theArr->Upper(); ++i )
  {
    result->ChangeValue(i) = theArr->Value(i).Amp();
  }
  return result;
}
