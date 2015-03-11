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

// Own include
#include <ActData_RefClassifier.h>

// OCCT includes
#include <TDF_ChildIterator.hxx>
#include <TDF_Tool.hxx>

//! Performs the classification of the given reference against the passed
//! Sampler Tree.
//! \param theReference [in] reference to classify.
//! \param theSTree [in] Sampler Tree reference.
//! \return classification result.
ActData_RefClassifier::RefScope
  ActData_RefClassifier::Classify(const TDF_Label& theReference,
                                  const Handle(ActData_SamplerTreeNode)& theSTree)
{
  const ActData_SamplerTreeNode* aSTreePtr = reinterpret_cast<const ActData_SamplerTreeNode*>( theSTree.get() );
  return Classify(theReference, *aSTreePtr);
}

//! Performs the classification of the given reference against the passed
//! Sampler Tree.
//! \param theReference [in] reference to classify.
//! \param theSTree [in] Sampler Tree instance.
//! \return classification result.
ActData_RefClassifier::RefScope
  ActData_RefClassifier::Classify(const TDF_Label& theReference,
                                  const ActData_SamplerTreeNode& theSTree)
{
  Standard_Boolean isInScoped = Standard_False;
  for ( ActData_SamplerTreeNode::Iterator it(theSTree, Standard_True); it.More(); it.Next() )
  {
    const ActData_SamplerTreeNode* aSIDPtr = it.Current();
    TDF_Label aSLabel;
    TDF_Tool::Label(theReference.Data(), aSIDPtr->ID, aSLabel, Standard_False);

    if ( IsSameOrSubLabelOf(theReference, aSLabel) )
    {
      isInScoped = Standard_True;
      break;
    }
  }

  return (isInScoped ? RefScope_IN : RefScope_OUT);
}

//! Checks whether the first given Label is a sub-Label of the second one
//! inclusively.
//! \param theFirst [in] first Label.
//! \param theSecond [in] second Label.
//! \return true/false.
Standard_Boolean
  ActData_RefClassifier::IsSameOrSubLabelOf(const TDF_Label& theFirst,
                                            const TDF_Label& theSecond)
{
  TCollection_AsciiString aFirstEntry = ActData_Utils::GetEntry(theFirst);
  TCollection_AsciiString aSecondEntry = ActData_Utils::GetEntry(theSecond);

  if ( ::IsEqual(aFirstEntry, aSecondEntry) )
    return Standard_True;

  for ( TDF_ChildIterator it(theSecond, Standard_True); it.More(); it.Next() )
  {
    TCollection_AsciiString aSecondSubEntry = ActData_Utils::GetEntry( it.Value() );
    if ( ::IsEqual(aFirstEntry, aSecondSubEntry) )
      return Standard_True;
  }

  return Standard_False;
}
