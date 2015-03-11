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
#include <ActData_BaseVarNode.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

//-----------------------------------------------------------------------------
// Class: ActData_BaseVarNode
//-----------------------------------------------------------------------------

//! Default constructor.
ActData_BaseVarNode::ActData_BaseVarNode() : ActData_BaseNode()
{
  REGISTER_PARAMETER(Name, Param_Name);
}

//! Accessor for the Node's name.
//! \return name of the Node.
TCollection_ExtendedString ActData_BaseVarNode::GetName()
{
  return ActData_ParameterFactory::AsName( this->Parameter(Param_Name) )->GetValue();
}

//! Sets name for the Node.
//! \param theName [in] name to set.
void ActData_BaseVarNode::SetName(const TCollection_ExtendedString& theName)
{
  ActData_ParameterFactory::AsName( this->Parameter(Param_Name) )->SetValue(theName);
}

//! Sets variable name.
//! \param theName [in] variable name.
void ActData_BaseVarNode::SetVariableName(const TCollection_AsciiString& Name)
{
  this->Parameter(Param_Value)->SetName(Name);
}

//! Accessor for the variable name.
//! \return variable name.
TCollection_AsciiString ActData_BaseVarNode::GetVariableName() const
{
  return TCollection_AsciiString( this->Parameter(Param_Value)->GetName() );
}

//! Renames the variable affecting all dependent Nodes by modifying their
//! evaluation strings. Notice that this method is designed to propagate
//! changes on already connected Parameters only. Those Parameters which
//! refer to the variable with the NewName but not yet connected to it (i.e.
//! those having "dead" evaluation strings) are not affected.
//! \param NewName [in] new name to set.
void ActData_BaseVarNode::RenameConnected(const TCollection_AsciiString& NewName)
{
  TCollection_AsciiString anOldName = this->GetVariableName();

  /* ===========================================================
   *  Make a replacement in evaluation strings of Input Readers
   * =========================================================== */

  this->replaceInEvalStrings(anOldName, NewName);

  /* ================================================
   *  Change actual name of the underlying Parameter
   * ================================================ */

  this->SetVariableName(NewName);
}

//! Cleans up the evaluation strings of the dependent Variable Nodes.
void ActData_BaseVarNode::beforeRemove()
{
  TCollection_AsciiString aName = this->GetVariableName();
  this->replaceInEvalStrings(aName, "", Standard_True);
}

//! Performs string substitutions in the dependent Parameters.
//! \param What [in] what to find & replace.
//! \param With [in] replacement string.
//! \param isCompleteErase [in] forces erasing of the evaluation strings of
//!        the dependent Parameters.
void ActData_BaseVarNode::replaceInEvalStrings(const TCollection_AsciiString& What,
                                               const TCollection_AsciiString& With,
                                               const Standard_Boolean isCompleteErase)
{
  Handle(ActAPI_HParameterList) anInputReaders = this->GetInputReaders();
  ActAPI_ParameterList::Iterator anIt( *anInputReaders.operator->() );
  for ( ; anIt.More(); anIt.Next() )
  {
    const Handle(ActAPI_IUserParameter)& aParam = anIt.Value();
    Handle(ActData_TreeFunctionParameter)
      aTreeFuncParam = Handle(ActData_TreeFunctionParameter)::DownCast(aParam);

    if ( aTreeFuncParam.IsNull() )
      continue;

    Handle(ActAPI_HParameterList) anArgParams = aTreeFuncParam->Arguments();
    ActAPI_ParameterList::Iterator anArgIt( *anArgParams.operator->() );
    for ( ; anArgIt.More(); anArgIt.Next() )
    {
      const Handle(ActAPI_IUserParameter)& anArgParam = anArgIt.Value();
      ActData_Utils::ReplaceEvaluationString(anArgParam, What, With, isCompleteErase);
    }
  }
}
