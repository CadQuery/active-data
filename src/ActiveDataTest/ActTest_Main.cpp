//-----------------------------------------------------------------------------
// Created on: October 2012
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the OPEN CASCADE SAS.
// 4. Neither the name of the OPEN CASCADE SAS nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY OPEN CASCADE SAS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL OPEN CASCADE SAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
