//-----------------------------------------------------------------------------
// Created on: March 2015
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
#include <ActData_GraphToDot.h>

// ACT Data includes
#include <ActData_BaseModel.h>
#include <ActData_DependencyGraph.h>
#include <ActData_RealVarNode.h>

//! Converts Execution Graph to DOT format.
//! \param M [in] Data Model to convert Execution Graph for.
//! \return string representation of the Execution Graph.
TCollection_AsciiString ActData_GraphToDot::Convert(const Handle(ActAPI_IModel)& M)
{
  TCollection_AsciiString result = TCollection_AsciiString("digraph G {") + ActAux_Macro_NL;

  /* ================================================
   *  Populate graph data from Model Execution Graph
   * ================================================ */

  Handle(ActData_BaseModel)       MBase = Handle(ActData_BaseModel)::DownCast(M);
  Handle(ActData_DependencyGraph) G     = new ActData_DependencyGraph(MBase);

  // Get graph data
  const ActData_DependencyGraph::VertexDataMap& Vertices = G->Vertices();
  const ActData_DependencyGraph::EdgeMap&       Links    = G->Edges();

  // Populate graph data with specification of links
  for ( ActData_DependencyGraph::EdgeMap::Iterator eIt(Links); eIt.More(); eIt.Next() )
  {
    const ActData_DependencyGraph::OriEdge& E = eIt.Value();
    Handle(ActAPI_INode) V1_Node = Vertices.Find(E.V1).Parameter->GetNode();
    Handle(ActAPI_INode) V2_Node = Vertices.Find(E.V2).Parameter->GetNode();

    // Name of the first vertex
    TCollection_AsciiString V1_name;
    if ( V1_Node->IsKind( STANDARD_TYPE(ActData_BaseVarNode) ) )
      V1_name = Handle(ActData_BaseVarNode)::DownCast(V1_Node)->GetVariableName();
    else
      V1_name = Vertices.Find(E.V1).Parameter->GetNode()->GetId();

    // Name of the last vertex
    TCollection_AsciiString V2_name;
    if ( V2_Node->IsKind( STANDARD_TYPE(ActData_BaseVarNode) ) )
      V2_name = Handle(ActData_BaseVarNode)::DownCast(V2_Node)->GetVariableName();
    else
      V2_name = Vertices.Find(E.V2).Parameter->GetNode()->GetId();

    // Prepare string descriptor for the link
    result  = result + "\"" + Vertices.Find(E.V1).TreeFunction->GetName() + " (" + V1_name + ")\"";
    result += " -> ";
    result  = result + "\"" + Vertices.Find(E.V2).TreeFunction->GetName() + " (" + V2_name + ")\"";
    result += ";";
    result += ActAux_Macro_NL;
  }

  /* ==========
   *  Finalize
   * ========== */

  result = result + "}" + ActAux_Macro_NL;

  return result;
}
