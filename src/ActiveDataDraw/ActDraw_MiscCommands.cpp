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
#include <ActDraw_CoordNode.h>
#include <ActDraw_DrawableModel.h>
#include <ActDraw_DrawTestSuite.h>
#include <ActDraw_DummyModel.h>
#include <ActDraw_StubANode.h>

// Active Data includes
#include <ActData_Application.h>
#include <ActData_CAFDumper.h>
#include <ActData_NodeFactory.h>
#include <ActData_ParameterFactory.h>

// Active Data (auxiliary) includes
#include <ActAux_Timing.h>

// OCCT includes
#include <Draw.hxx>
#include <Draw_Interpretor.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_Real.hxx>
#include <TDataStd_RealArray.hxx>

// Auxiliary tools and data.
namespace MISC
{
  //! Prepares sample Data Model.
  //! \param M [in] sample Model.
  //! \return true if test is passed, false -- otherwise.
  Standard_Boolean Create_SampleTree(const Handle(ActDraw_DummyModel)& M)
  {
    if ( !M->NewEmpty() )
      return Standard_False;

    // Prepare detached A Node
    Handle(ActDraw_StubANode) A = Handle(ActDraw_StubANode)::DownCast( ActDraw_StubANode::Instance() );

    // Prepare data to initialize the involved A Nodes
    const Standard_Real A_Value = 999.99;

    // Attach data to the CAF Document
    M->OpenCommand();

    // Expand on OCAF
    M->StubAPartition()->AddNode(A);

    // Initialize
    A->SetName("Root A");
    A->Init(A_Value);

    // After initialization the Node should get WELL-FORMED state
    if ( !A->IsWellFormed() )
      return Standard_False;

    M->CommitCommand();
    return Standard_True;
  }

  //! Prepares sample Data Model populating it with n^3 sample points. Each
  //! point is represented by Node, which is not a good idea, but this is
  //! what we actually want to test here.
  //! \param M [in] sample Model.
  //! \param n [in] number of points in one direction (X, Y or Z).
  //! \return true if test is passed, false -- otherwise.
  Standard_Boolean Populate_Coordinates(const Handle(ActDraw_DummyModel)& M,
                                        const Standard_Integer            n)
  {
    // Attach data to the CAF Document
    M->OpenCommand();
    {
      // Create many Nodes for coordinates
      for ( Standard_Integer i = 0; i < n; ++i )
        for ( Standard_Integer j = 0; j < n; ++j )
          for ( Standard_Integer k = 0; k < n; ++k )
          {
            // Create a unique name for Node
            TCollection_AsciiString name("Point [");
            name += i; name += ", ";
            name += j; name += ", ";
            name += k; name += "]";

            // Crate a Node and save it to Model
            Handle(ActDraw_CoordNode) C = Handle(ActDraw_CoordNode)::DownCast( ActDraw_CoordNode::Instance() );
            //
            M->CoordPartition()->AddNode(C);
            C->SetName(name);
            C->Init(i, j, k);
          }
    }
    M->CommitCommand();

    // Success
    return Standard_True;
  }

  //! Prepares sample Document populating it with n^3 sample points. Each
  //! point is represented by a Label with sub-Labels for each coordinate.
  //! \param n [in] number of points in one direction (X, Y or Z).
  //! \return true if test is passed, false -- otherwise.
  Standard_Boolean Create_Coordinates_ADfree(const Standard_Integer n)
  {
    Handle(TDocStd_Document) doc;
    ActData_Application::Instance()->NewDocument(ACTBinFormat, doc);
    doc->SetModificationMode(Standard_True);
    doc->SetUndoLimit(10);

    TDF_Label rootLab = doc->Main().Root();

    // Attach data to the CAF Document
    doc->OpenCommand();
    {
      // Create many Nodes for coordinates
      for ( Standard_Integer i = 0; i < n; ++i )
        for ( Standard_Integer j = 0; j < n; ++j )
          for ( Standard_Integer k = 0; k < n; ++k )
          {
            TDF_Label pointLab = TDF_TagSource::NewChild(rootLab);

            // Create a unique name for Node
            TCollection_AsciiString name("Point [");
            name += i; name += ", ";
            name += j; name += ", ";
            name += k; name += "]";

            // Crate a Node and save it to Model
            Handle(ActDraw_CoordNode) C = Handle(ActDraw_CoordNode)::DownCast( ActDraw_CoordNode::Instance() );
            //
            TDF_Label xLab = TDF_TagSource::NewChild(pointLab);
            TDataStd_Real::Set(xLab, i);
            //
            TDF_Label yLab = TDF_TagSource::NewChild(pointLab);
            TDataStd_Real::Set(yLab, j);
            //
            TDF_Label zLab = TDF_TagSource::NewChild(pointLab);
            TDataStd_Real::Set(zLab, k);
            //
            TDataStd_Name::Set(pointLab, name);
          }
    }
    doc->CommitCommand();

    // Success
    return Standard_True;
  }

  //! Prepares sample Document populating it with n^3 sample points. There is
  //! only label for the entire point cloud.
  //! \param n [in] number of points in one direction (X, Y or Z).
  //! \return true if test is passed, false -- otherwise.
  Standard_Boolean Create_Coordinates_ADfree_optimized(const Standard_Integer n)
  {
    Handle(TDocStd_Document) doc;
    ActData_Application::Instance()->NewDocument(ACTBinFormat, doc);
    doc->SetModificationMode(Standard_True);
    doc->SetUndoLimit(10);
    //
    TDF_Label rootLab = doc->Main().Root();

    // Attach data to the CAF Document
    doc->OpenCommand();
    {
      // One Label for the entire point cloud
      TDF_Label pointCloudLab = TDF_TagSource::NewChild(rootLab);
      //
      Handle(TDataStd_RealArray)
        coords = TDataStd_RealArray::Set(pointCloudLab, 0, n*n*n*3 - 1);

      // Create many Nodes for coordinates
      for ( Standard_Integer i = 0; i < n; ++i )
        for ( Standard_Integer j = 0; j < n; ++j )
          for ( Standard_Integer k = 0; k < n; ++k )
          {
            const Standard_Integer idx = i*n*n + j*n + k;
            coords->SetValue(idx + 0, i);
            coords->SetValue(idx + 1, j);
            coords->SetValue(idx + 1, k);
          }
    }
    doc->CommitCommand();

    // Success
    return Standard_True;
  }
}

//=======================================================================
// Function : MISC_TestAccess
// Purpose  : Tests accessing Parameters.
//=======================================================================

static int MISC_TestAccess(Draw_Interpretor&,
                           Standard_Integer argc, const char** /*argv*/)
{
  if ( argc != 1 )
  {
    cout << "Invalid number of arguments" << endl;
    return 1;
  }

  Handle(ActDraw_DummyModel) M = new ActDraw_DummyModel;
  if ( !MISC::Create_SampleTree(M) )
  {
    cout << "Cannot prepare sample Model" << endl;
    return 1;
  }

  Handle(ActDraw_StubANode) N = Handle(ActDraw_StubANode)::DownCast( M->GetRootNode() );
  const Standard_Integer num_tests = 1000000;

  // First test is without DownCast
  cout << "-------------------------------------------------------------------" << endl;
  cout << "TEST 1: access Parameter " << num_tests << " times without DownCast" << endl;
  TIMER_NEW
  TIMER_GO
  for ( Standard_Integer i = 0; i < num_tests; ++i )
  {
    Handle(ActAPI_IUserParameter) P = N->Parameter(ActDraw_StubANode::PID_Real);
  }
  TIMER_FINISH
  TIMER_COUT_RESULT

  // Now let us try DownCast
  cout << "-------------------------------------------------------------------" << endl;
  cout << "TEST 2: access Parameter " << num_tests << " times with DownCast" << endl;
  TIMER_RESET
  TIMER_GO
  for ( Standard_Integer i = 0; i < num_tests; ++i )
  {
    Handle(ActData_RealParameter) P = ActParamTool::AsReal( N->Parameter(ActDraw_StubANode::PID_Real) );
  }
  TIMER_FINISH
  TIMER_COUT_RESULT

  return 0;
}

//=======================================================================
// Function : MISC_CreateModel
// Purpose  : Creates sample Data Model.
//=======================================================================

static int MISC_CreateModel(Draw_Interpretor&,
                            Standard_Integer argc, const char** argv)
{
  if ( argc != 2 )
  {
    cout << "Invalid number of arguments" << endl;
    return 1;
  }

  Handle(ActDraw_DummyModel) M = new ActDraw_DummyModel;
  if ( !M->NewEmpty() )
  {
    cout << "Cannot initialize Model" << endl;
    return 1;
  }

  ActDraw_DummyModel::MTime_On = 0;

  // Create sample root Node
  Handle(ActDraw_StubANode) Root = Handle(ActDraw_StubANode)::DownCast( ActDraw_StubANode::Instance() );

  // Attach data to the CAF Document
  M->OpenCommand();
  {
    // Create root Node
    M->StubAPartition()->AddNode(Root); // Expand on OCAF
    Root->SetName("Root");
    Root->Init(0);
  }
  M->CommitCommand();

  // Set to Draw context
  Draw::Set( argv[1], new ActDraw_DrawableModel(M) );
  return 0;
}

//=======================================================================
// Function : MISC_TestCoord
// Purpose  : Performance test.
//=======================================================================

static int MISC_TestCoord(Draw_Interpretor&,
                          Standard_Integer argc, const char** argv)
{
  if ( argc != 3 )
  {
    cout << "Invalid number of arguments" << endl;
    return 1;
  }

  //---------------------------------------------------------------------------
  // Access sample model
  //---------------------------------------------------------------------------

  // Access the Drawable Model
  Handle(ActDraw_DrawableModel)
    DM = Handle(ActDraw_DrawableModel)::DownCast( Draw::Get(argv[1]) );
  //
  if ( DM.IsNull() )
  {
    cout << "Error: there is no Data Model with name " << argv[1] << endl;
    return 1;
  }

  //---------------------------------------------------------------------------
  // Populate sample model
  //---------------------------------------------------------------------------

  // Access the number of points requested
  Standard_Integer n = atoi(argv[2]);
  if ( n < 0 )
    n = 10;

  // First test is without DownCast
  cout << "-------------------------------------------------------------------" << endl;
  cout << "Creating test model with " << (n*n*n + 1) << " Nodes (one for root)" << endl;
  TIMER_NEW
  TIMER_GO
  //
  if ( !MISC::Populate_Coordinates(DM->Model(), n) )
  {
    cout << "Cannot prepare sample Model" << endl;
    return 1;
  }
  TIMER_FINISH
  TIMER_COUT_RESULT

  return 0;
}

//=======================================================================
// Function : MISC_TestPureOcaf
// Purpose  : Performance test.
//=======================================================================

static int MISC_TestPureOcaf(Draw_Interpretor&,
                             Standard_Integer argc, const char** argv)
{
  if ( argc != 2 && argc != 3 )
  {
    cout << "Invalid number of arguments" << endl;
    return 1;
  }

  // Access the number of points requested
  Standard_Integer n = atoi(argv[1]);
  if ( n < 0 )
    n = 10;

  bool isOpt = ( (argc == 3) && ( !strcmp(argv[2], "-opt") ) );

  // First test is without DownCast
  cout << "-------------------------------------------------------------------" << endl;
  cout << "Creating test model with " << (n*n*n + 1) << " Labels (one for root)" << endl;
  TIMER_NEW
  TIMER_GO
  //
  if ( isOpt )
    MISC::Create_Coordinates_ADfree_optimized(n);
  else
    MISC::Create_Coordinates_ADfree(n);
  //
  TIMER_FINISH
  TIMER_COUT_RESULT

  return 0;
}

//=======================================================================
// Function : MISC_ReleaseModel
// Purpose  : Cleans up the contents of the sample Data Model.
//=======================================================================

static int MISC_ReleaseModel(Draw_Interpretor&,
                             Standard_Integer argc, const char** argv)
{
  if ( argc != 2 )
  {
    cout << "Invalid number of arguments" << endl;
    return 1;
  }

  // Access the Drawable Model
  Handle(ActDraw_DrawableModel)
    DM = Handle(ActDraw_DrawableModel)::DownCast( Draw::Get(argv[1]) );
  //
  if ( DM.IsNull() )
  {
    cout << "Error: there is no Data Model with name " << argv[1] << endl;
    return 1;
  }

  // Release OCAF document
  DM->Model()->Release();
  DM->Model().Nullify();

  // Success
  return 0;
}

//=======================================================================
// Function : MISC_SaveModel
// Purpose  : Saves Data Model to file.
//=======================================================================

static int MISC_SaveModel(Draw_Interpretor&,
                          Standard_Integer argc, const char** argv)
{
  if ( argc != 3 )
  {
    cout << "Invalid number of arguments" << endl;
    return 1;
  }

  // Access the Drawable Model
  Handle(ActDraw_DrawableModel)
    DM = Handle(ActDraw_DrawableModel)::DownCast( Draw::Get(argv[1]) );
  //
  if ( DM.IsNull() )
  {
    cout << "Error: there is no Data Model with name " << argv[1] << endl;
    return 1;
  }

  // Save OCAF document
  if ( !DM->Model()->SaveAs(argv[2]) )
  {
    cout << "Error: failed to save model to " << argv[2] << endl;
    return 1;
  }

  // Success
  return 0;
}

//=======================================================================
// Function : MISC_DumpModel
// Purpose  : Dumps Data Model to file using CAF Dumper.
//=======================================================================

static int MISC_DumpModel(Draw_Interpretor&,
                          Standard_Integer argc, const char** argv)
{
  if ( argc != 3 )
  {
    cout << "Invalid number of arguments" << endl;
    return 1;
  }

  // Access the Drawable Model
  Handle(ActDraw_DrawableModel)
    DM = Handle(ActDraw_DrawableModel)::DownCast( Draw::Get(argv[1]) );
  //
  if ( DM.IsNull() )
  {
    cout << "Error: there is no Data Model with name " << argv[1] << endl;
    return 1;
  }

  // Dump to text file
  ActData_CAFDumper::Dump( TCollection_AsciiString(argv[2]), DM->Model() );

  // Success
  return 0;
}

//=======================================================================
// Function : MiscCommands
// Purpose  : Adds miscellaneous AD commands to Draw interpretor.
//=======================================================================

void ActDraw_Commands::MiscCommands(Draw_Interpretor& theCommands)
{
  const char *grp = "Miscellaneous commands for working with AD";

  theCommands.Add("misc_test_access", "misc_test_access",
                  __FILE__, MISC_TestAccess, grp);

  theCommands.Add("misc_create_model", "misc_create_model name",
                  __FILE__, MISC_CreateModel, grp);

  theCommands.Add("misc_test_coord", "misc_test_coord model_name num_pts_in_row",
                  __FILE__, MISC_TestCoord, grp);

  theCommands.Add("misc_release_model", "misc_release_model name",
                  __FILE__, MISC_ReleaseModel, grp);

  theCommands.Add("misc_save_model", "misc_save_model name filename",
                  __FILE__, MISC_SaveModel, grp);

  theCommands.Add("misc_dump_model", "misc_dump_model name filename",
                  __FILE__, MISC_DumpModel, grp);

  theCommands.Add("misc_test_pure_ocaf", "misc_test_pure_ocaf num_pts_in_row [-opt]",
                  __FILE__, MISC_TestPureOcaf, grp);
}
