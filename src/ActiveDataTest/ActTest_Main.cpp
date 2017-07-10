//-----------------------------------------------------------------------------
// Created on: October 2012
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

// Active Data unit tests
#include <ActTest_AsciiStringParameter.h>
#include <ActTest_BaseModel.h>
#include <ActTest_BoolArrayParameter.h>
#include <ActTest_BoolParameter.h>
#include <ActTest_CAFConversionCtx.h>
#include <ActTest_ComplexArrayParameter.h>
#include <ActTest_CopyPasteEngine.h>
#include <ActTest_ExtTransactionEngine.h>
#include <ActTest_GroupParameter.h>
#include <ActTest_IntArrayParameter.h>
#include <ActTest_IntParameter.h>
#include <ActTest_MeshAttr.h>
#include <ActTest_MeshParameter.h>
#include <ActTest_NameParameter.h>
#include <ActTest_RealArrayParameter.h>
#include <ActTest_RealParameter.h>
#include <ActTest_ReferenceListParameter.h>
#include <ActTest_ReferenceParameter.h>
#include <ActTest_SelectionParameter.h>
#include <ActTest_ShapeParameter.h>
#include <ActTest_StringArrayParameter.h>
#include <ActTest_TimeStamp.h>
#include <ActTest_TimeStampParameter.h>
#include <ActTest_TreeFunctionParameter.h>
#include <ActTest_TreeNodeParameter.h>
#include <ActTest_TriangulationParameter.h>

// ActTestLib includes
#include <ActTestLib_Launcher.h>

DEFINE_TEST_VARIABLES

//! Entry point to unit tests.
int main(int ActTestLib_NotUsed(argc), char* ActTestLib_NotUsed(argv)[])
{
  /* ==============================
   *  Accumulate test cases to run
   * ============================== */

  std::vector< ActTestLib_CaseLauncherAPI* > CaseLaunchers;

  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_AsciiStringParameter>   );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_BaseModelPersistence>   );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_BaseModelStructure>     );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_BaseModelEvaluation>    );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_BoolArrayParameter>     );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_BoolParameter>          );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_ComplexArrayParameter>  );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_GroupParameter>         );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_IntArrayParameter>      );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_IntParameter>           );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_MeshParameter>          );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_NameParameter>          );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_RealArrayParameter>     );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_RealParameter>          );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_ReferenceListParameter> );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_ReferenceParameter>     );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_SelectionParameter>     );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_ShapeParameter>         );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_StringArrayParameter>   );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_TimeStampParameter>     );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_TreeFunctionParameter>  );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_TreeNodeParameter>      );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_CAFConversionCtx>       );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_TimeStamp>              );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_MeshAttrBean>           );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_MeshAttrTransactional>  );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_MeshAttrPersistent>     );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_ExtTransactionEngine>   );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_CopyPasteEngine>        );
  CaseLaunchers.push_back( new ActTestLib_CaseLauncher<ActTest_TriangulationParameter> );

  // Launcher of entire test suite
  ActTestLib_Launcher Launcher;
  for ( int c = 0; c < (int) CaseLaunchers.size(); ++c )
    Launcher << CaseLaunchers[c];

  /* ================
   *  Run unit tests
   * ================ */

  PRINT_DECOR;
  int res_flag;
  if ( !Launcher.Launch(&std::cout) ) // Launch Test Cases
  {
    std::cout << "\t***\n\tTests FAILED" << std::endl;
    res_flag = 1;
  }
  else
  {
    std::cout << "\t***\n\tTests SUCCEEDED" << std::endl;
    res_flag = 0;
  }

  /* ==========
   *  Finalize
   * ========== */

  // Release resources
  for ( size_t i = 0; i < CaseLaunchers.size(); ++i )
    delete CaseLaunchers[i];

  PRINT_DECOR;
  return res_flag;
}
