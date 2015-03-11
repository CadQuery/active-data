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

#ifndef ActData_RefClassifier_HeaderFile
#define ActData_RefClassifier_HeaderFile

// Active Data includes
#include <ActData_Common.h>
#include <ActData_SamplerTreeNode.h>
#include <ActData_Utils.h>

// Active Data (API) includes
#include <ActAPI_INode.h>

//! Classifier object used to define whether the passed reference is
//! IN-SCOPED or OUT-SCOPED.
class ActData_RefClassifier
{
public:

  //! Enumerates two possible reference statuses regarding to the Sampler
  //! Tree. If reference does not have any pointers out of the Sampler
  //! Tree, it is said to be IN-SCOPED, otherwise -- it is OUT-SCOPED.
  enum RefScope
  {
    RefScope_IN = 1,
    RefScope_OUT
  };

  ActData_EXPORT static RefScope
    Classify(const TDF_Label& theReference,
             const Handle(ActData_SamplerTreeNode)& theSTree);

  ActData_EXPORT static RefScope
    Classify(const TDF_Label& theReference,
             const ActData_SamplerTreeNode& theSTree);

  ActData_EXPORT static Standard_Boolean
    IsSameOrSubLabelOf(const TDF_Label& theFirst,
                       const TDF_Label& theSecond);

};

#endif
