//-----------------------------------------------------------------------------
// Created on: August 2012
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

// Active Data (Draw plug-in) includes
#include <ActDraw_Commands.h>
#include <ActDraw_Common.h>
#include <ActDraw_DrawTestSuite.h>

// Active Data includes
#include <ActData_Application.h>
#include <ActData_CAFDumper.h>
#include <ActData_NodeFactory.h>
#include <ActData_ParameterFactory.h>

// OCCT includes
#include <Draw_Interpretor.hxx>
#include <Standard_ProgramError.hxx>
#include <TCollection_HExtendedString.hxx>

//! Common data containers and utilities.
namespace DUMPER
{
  //! Type shortcut for repository of Models.
  typedef NCollection_DataMap<TCollection_AsciiString, Handle(ActAPI_IModel)> ModelMap;

  ModelMap Models; //!< Data Model instance.
  ActData_CAFDumper::Verbosity Verbosity = ActData_CAFDumper::Verbosity_Details; //!< Dumping verbosity.
  ActData_CAFDumper::Content Content = ActData_CAFDumper::Content_Plain; //!< Dumping content.

  //! Prints currently defined verbosity mode for Dumper.
  void PrintVerbosityMode()
  {
    cout << "Current verbosity mode: ";
    switch ( DUMPER::Verbosity )
    {
      case ActData_CAFDumper::Verbosity_StructureNodesOnly:
        cout << "Nodes only" << endl;
        break;
      case ActData_CAFDumper::Verbosity_StructureOnly:
        cout << "Nodes & Parameters" << endl;
        break;
      case ActData_CAFDumper::Verbosity_Details:
        cout << "detailed" << endl;
        break;
    }
  }

  //! Prints currently defined content mode for Dumper.
  void PrintContentMode()
  {
    cout << "Current content mode: ";
    switch ( DUMPER::Content )
    {
      case ActData_CAFDumper::Content_Plain:
        cout << "plain" << endl;
        break;
      case ActData_CAFDumper::Content_TreeNodes:
        cout << "Tree Nodes" << endl;
        break;
      case ActData_CAFDumper::Content_DependencyGraph:
        cout << "Dependency Graph" << endl;
        break;
    }
  }
};

//=======================================================================
// Function : DUMPER_SetContent
// Purpose  : Sets dumping content.
//=======================================================================

static int DUMPER_SetContent(Draw_Interpretor&,
                             Standard_Integer argc, const char** argv)
{
  if ( argc != 2 )
  {
    cout << "Usage: dump_setcontent mode {0 - plain, 1 - Tree Nodes, 2 - Execution Graph}\n";
    cout << "Example: dump_setcontent 1\n";
    return 1;
  }

  Standard_Integer aMode = atoi(argv[1]);
  if ( aMode < 1 || aMode > 3 )
  {
    cout << "Invalid mode passed. Use 0, 1 or 2" << endl;
    return 1;
  }

  DUMPER::Content = ActData_CAFDumper::Content(aMode);
  DUMPER::PrintContentMode();

  return 0;
}

//=======================================================================
// Function : DUMPER_SetVerbose
// Purpose  : Sets verbosity level.
//=======================================================================

static int DUMPER_SetVerbose(Draw_Interpretor&,
                             Standard_Integer argc, const char** argv)
{
  if ( argc != 2 )
  {
    cout << "Usage: dump_setverbose mode {1 - Nodes only, 2 - Nodes & Parameters, 3 - Detailed}\n";
    cout << "Example: dump_setverbose 2\n";
    return 1;
  }

  Standard_Integer aMode = atoi(argv[1]);
  if ( aMode < 1 || aMode > 3 )
  {
    cout << "Invalid mode passed. Use 1, 2 or 3" << endl;
    return 1;
  }

  DUMPER::Verbosity = ActData_CAFDumper::Verbosity(aMode);
  DUMPER::PrintVerbosityMode();

  return 0;
}

//=======================================================================
// Function : DUMPER_Do
// Purpose  : Performs actual dumping.
//=======================================================================

static int DUMPER_Do(Draw_Interpretor&,
                     Standard_Integer argc, const char** argv)
{
  if ( argc != 3 )
  {
    cout << "Usage: dump_do model_name filename\n";
    cout << "Example: dump_do m1 m1.log\n";
    return 1;
  }

  TCollection_AsciiString aModelName(argv[1]);
  TCollection_AsciiString aFilename(argv[2]);

  if ( !DUMPER::Models.IsBound(aModelName) )
  {
    cout << "Model " << aModelName.ToCString() << " does not exist" << endl;
    return 1;
  }

  Handle(ActAPI_IModel) aModel = DUMPER::Models.Find(aModelName);

  DUMPER::PrintContentMode();
  DUMPER::PrintVerbosityMode();

  if ( !ActData_CAFDumper::Dump(aFilename, aModel, DUMPER::Content, DUMPER::Verbosity) )
  {
    cout << "Failed to dump file..." << endl;
    return 1;
  }

  return 0;
}

//=======================================================================
// Function : CAFDumperCommands
// Purpose  : Adds CAF Dumper commands to Draw interpretor.
//=======================================================================

void ActDraw_Commands::CAFDumperCommands(Draw_Interpretor& theCommands)
{
  // ------------------------------------------------------------------------
  // Sample scenario:
  // ------------------------------------------------------------------------
  //
  // > dump_load project.cbf m1   # Load Data Model from CBF project file
  //
  // > dump_setcontent 2          # Set content mode to "Tree Nodes"
  //
  // > dump_setverbose 1          # Dump Nodes only
  //
  // > dump_do m1 filename.log    # Dump Model to log
  //
  // ------------------------------------------------------------------------

  const char *grp = "Commands for CAF Dumper functionality";

  theCommands.Add("dump_setcontent", "dump_setcontent mode",
                  __FILE__, DUMPER_SetContent, grp);

  theCommands.Add("dump_setverbose", "dump_setverbose mode",
                  __FILE__, DUMPER_SetVerbose, grp);

  theCommands.Add("dump_do", "dump_do model_name filename",
                  __FILE__, DUMPER_Do, grp);
}
