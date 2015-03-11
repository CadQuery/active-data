//-----------------------------------------------------------------------------
// Created on: April 2014
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
#include <ActData_UniqueNodeName.h>

// ACT Framework includes
#include <ActData_RecordCollectionOwnerAPI.h>

// Active Data (API) includes
#include <ActAPI_Common.h>

//-----------------------------------------------------------------------------
// Provider of sibling Nodes
//-----------------------------------------------------------------------------

//! Creates collection of sibling Nodes when these Nodes are organized as
//! records of the given owner.
//! \param theRecord [in] record to collect siblings for.
//! \param theOwner [in] record's owner.
//! \param theCollectionPID [in] PID of collection Parameter.
//! \return collection of sibling Nodes.
Handle(ActData_SiblingNodes)
  ActData_SiblingNodes::CreateForRecord(const Handle(ActAPI_INode)& theRecord,
                                        const Handle(ActAPI_INode)& theOwner,
                                        const Standard_Integer theCollectionPID)
{
  ActData_RecordCollectionOwnerAPI* OwnerAPI =
    dynamic_cast<ActData_RecordCollectionOwnerAPI*>( theOwner.operator->() );

  ASSERT_RAISE(OwnerAPI, "Owner Node is incompatible with Record Collection Owner API");

  // Create instance of Sibling Nodes tool
  Handle(ActData_SiblingNodes)
    Res = new ActData_SiblingNodes(theRecord, theOwner);
  ActData_SiblingNodes*
    ResPtr = dynamic_cast<ActData_SiblingNodes*>( Res.get() );

  // Collect siblings
  for ( Standard_Integer r = 1; r <= OwnerAPI->NbRecords(theCollectionPID); ++r )
  {
    Handle(ActAPI_INode) Rec = OwnerAPI->GetRecord(theCollectionPID, r);
    if ( Rec.IsNull() || !Rec->IsWellFormed() )
      continue;

    *ResPtr << Rec;
  }

  return Res;
}

//! Creates collection of sibling Nodes when these Nodes are organized as
//! direct children of the given parent.
//! \param theChild [in] item to collect siblings for.
//! \param theOwner [in] items's parent.
//! \return collection of sibling Nodes.
Handle(ActData_SiblingNodes)
  ActData_SiblingNodes::CreateForChild(const Handle(ActAPI_INode)& theChild,
                                       const Handle(ActAPI_INode)& theOwner)
{
  // Create instance of Sibling Nodes tool
  Handle(ActData_SiblingNodes)
    Res = new ActData_SiblingNodes(theChild, theOwner);
  ActData_SiblingNodes*
    ResPtr = dynamic_cast<ActData_SiblingNodes*>( Res.get() );

  // Collect siblings
  for ( Handle(ActAPI_IChildIterator) cit = theOwner->GetChildIterator(); cit->More(); cit->Next() )
  {
    Handle(ActAPI_INode) Child = cit->Value();
    if ( Child.IsNull() || !Child->IsWellFormed() || !Child->IsInstance(theChild->GetTypeName().ToCString()))
      continue;

    *ResPtr << Child;
  }

  return Res;
}

//! Adds the passed sibling to the collection.
//! \param theSibling [in] Node to add as a sibling.
//! \return THIS for subsequent streaming.
ActData_SiblingNodes&
  ActData_SiblingNodes::operator<<(const Handle(ActAPI_INode)& theSibling)
{
  if ( !ActAPI_IDataCursor::IsEqual(m_item, theSibling) )
    m_siblings->Append(theSibling);

  return *this;
}

//! Constructor.
//! \param theItem [in] Node to collect siblings for.
//! \param theOwner [in] owner of siblings.
ActData_SiblingNodes::ActData_SiblingNodes(const Handle(ActAPI_INode)& theItem,
                                         const Handle(ActAPI_INode)& theOwner)
: Standard_Transient()
{
  m_item = theItem;
  m_owner = theOwner;
  m_siblings = new ActAPI_HNodeList;
}

//-----------------------------------------------------------------------------
// Unique name generator
//-----------------------------------------------------------------------------

//! Generates unique Node name trying to choose its numerical index by
//! consulting the provided sibling Nodes. If other Nodes have some numerical
//! indices at the end, the maximal one is chosen and incremented. Otherwise,
//! the generated name gets index 1.
//! \param theNodes [in] sibling Nodes.
//! \param theBaseName [in] base name of the record to choose a name for.
//! \return new unique name.
TCollection_ExtendedString
  ActData_UniqueNodeName::Generate(const Handle(ActData_SiblingNodes)& theNodes,
                                   const TCollection_ExtendedString& theBaseName)
{
  /* =========================================
   *  Select maximal trailing numerical index
   * ========================================= */

  Standard_Integer numMax = -INT_MAX;
  const Standard_Integer nbNodes = theNodes->NumberOfNodes();
  for ( Standard_Integer r = 1; r <= nbNodes; ++r )
  {
    const Handle(ActAPI_INode)& Sibling = theNodes->At(r);

    TCollection_ExtendedString Separator(" \t\n\r");
    TCollection_ExtendedString RecName = Sibling->GetName();
    TCollection_ExtendedString Token;
    Standard_Integer t = 1, t_4num = 0, num = -1;
    do
    {
      Token = RecName.Token(Separator.ToExtString(), t++);
      if ( Token.Length() )
      {
        if ( !Token.IsAscii() )
          continue;

        TCollection_AsciiString AsciiToken(Token);
        if ( !AsciiToken.IsIntegerValue() )
          continue;

        num = AsciiToken.IntegerValue();
        t_4num = t + 1;
      }
    }
    while ( Token.Length() );

    if ( !t_4num || t_4num != t )
      continue;

    numMax = Max(numMax, num);
  }

  /* ===================
   *  Generate new name
   * =================== */

  if ( numMax == -INT_MAX )
    numMax = 0;

  TCollection_ExtendedString ResName(theBaseName);
  ResName = ResName.Cat(ActAux_Macro_WHITESPACE).Cat(numMax + 1);

  /* ===========================
   *  Protect from duplications
   * =========================== */

  // Try to choose a name to prevent name duplication
  Standard_Boolean isNameOk;

  // Choose unique name
  do
  {
    isNameOk = Standard_True;
    for ( Standard_Integer r = 1; r <= nbNodes; ++r )
    {
      const Handle(ActAPI_INode)& Sibling = theNodes->At(r);
      if ( IsEqual(Sibling->GetName(), ResName) )
      {
        isNameOk = Standard_False;
        break;
      }
    }

    // Try to make it unique
    if ( !isNameOk )
      ResName = ResName.Cat(ActAux_Macro_WHITESPACE).Cat(ActAux_Macro_ASTERISK);
  } while ( !isNameOk );

  return ResName;
}
