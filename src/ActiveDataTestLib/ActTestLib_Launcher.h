//-----------------------------------------------------------------------------
// Created on: 11 June 2013
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

#ifndef ActTestLib_Launcher_HeaderFile
#define ActTestLib_Launcher_HeaderFile

// ActTestLib includes
#include <ActTestLib_TestCase.h>

// ActAux includes
#include <ActAux.h>
#include <ActAux_Env.h>

//-----------------------------------------------------------------------------
// Launcher API
//-----------------------------------------------------------------------------

//! Base class for Test Case Launcher.
class ActTestLib_CaseLauncherAPI
{
public:

  virtual bool
    Launch() = 0;

  virtual int
    CaseID() const = 0;

  virtual std::string
    CaseDescriptionDir() const = 0;

  virtual std::string
    CaseDescriptionFn() const = 0;

  virtual int
    NumberOfExecuted() const = 0;

  virtual int
    NumberOfFailed() const = 0;

  virtual QrTestFunction
    TestFunction(const int idx) const = 0;

  virtual const std::map<std::string, std::string>&
    Variables() const = 0;

  virtual bool
    IsPassed(const int idx) const = 0;

};

//-----------------------------------------------------------------------------
// Launcher for single Test Case
//-----------------------------------------------------------------------------

//! Template-based implementation of Launcher mechanism dedicated to certain
//! Test Case.
template <typename CaseType>
class ActTestLib_CaseLauncher : public ActTestLib_CaseLauncherAPI
{
public:

  //! Default constructor.
  ActTestLib_CaseLauncher() : ActTestLib_CaseLauncherAPI()
  {}

public:

  //! Launches the Test Case of the given type. Returns true in case of
  //! success, false -- otherwise.
  //! \return true/false.
  virtual bool Launch()
  {
    // Collect Test Functions to run
    QrTestFunctions functions;
    CaseType::Functions(functions);

    // Run functions one by one
    bool areAllOk = true;
    for ( int f = 0; f < (int) functions.Size(); ++f )
    {
      const QrTestFunction& func = functions.Func(f);
      const bool isOk = (*func)(f + 1);

      m_funcResults.push_back(isOk);
      if ( !isOk && areAllOk )
        areAllOk = false;
    }
    return areAllOk;
  }

  //! Returns ID of the managed Test Case.
  //! \return ID of the managed Test Case.
  virtual inline int CaseID() const
  {
    return CaseType::ID();
  }

  //! Returns description directory for the managed Test Case.
  //! \return description directory for the managed Test Case.
  virtual inline std::string CaseDescriptionDir() const
  {
    return CaseType::DescriptionDir();
  }

  //! Returns description filename for the managed Test Case.
  //! \return description filename for the managed Test Case.
  virtual inline std::string CaseDescriptionFn() const
  {
    return CaseType::DescriptionFn();
  }

  //! Returns the total number of executed Test Functions for the managed
  //! Test Case.
  //! \return number of executed Test Functions
  virtual inline int NumberOfExecuted() const
  {
    return (int) m_funcResults.size();
  }

  //! Returns the total number of failed Test Functions for the managed
  //! Test Case.
  //! \return number of failed Test Functions
  virtual inline int NumberOfFailed() const
  {
    int numFailed = 0;
    for ( int f = 0; f < (int) m_funcResults.size(); ++f )
    {
      if ( !m_funcResults[f] )
        numFailed++;
    }
    return numFailed;
  }

  //! Returns Test Function referred to by the given 0-based index.
  //! \param idx [in] index of the Test Function to access.
  //! \return Test Function.
  virtual QrTestFunction TestFunction(const int idx) const
  {
    // Collect Test Functions to run
    QrTestFunctions functions;
    CaseType::Functions(functions);

    // Access Test Function by index
    return functions.Func(idx);
  }

  //! Returns expansion map for local description variables of Test
  //! Function with the given index.
  //! \return expansion map.
  virtual const std::map<std::string, std::string>& Variables() const
  {
    return CaseType::ExpansionMap();
  }

  //! Returns true if Test Function with the given index has passed, false --
  //! otherwise.
  //! \param idx [in] index of Test Function.
  //! \return true/false.
  virtual bool IsPassed(const int idx) const
  {
    return m_funcResults[idx];
  }

private:

  ActTestLib_CaseLauncher(const ActTestLib_CaseLauncher&) {}
  void operator=(const ActTestLib_CaseLauncher&) {}

private:

  std::vector<bool> m_funcResults; //!< Execution results.

};

//-----------------------------------------------------------------------------
// Launcher for entire test suite
//-----------------------------------------------------------------------------

//! Launcher for entire test suite. The instance of this class should be
//! populated with the actual Test Case Launchers you want to execute.
class ActTestLib_Launcher
{
public:

  //! Default constructor.
  ActTestLib_Launcher() {}

public:

  ActTestLib_EXPORT ActTestLib_Launcher&
    operator<<(ActTestLib_CaseLauncherAPI* CaseLauncher);

  ActTestLib_EXPORT bool
    Launch(std::ostream* out = NULL) const;

protected:

  bool generateReport(std::ostream* out) const;
  std::string uniqueDirName() const;

private:

  ActTestLib_Launcher(const ActTestLib_Launcher&) {}
  void operator=(const ActTestLib_Launcher&) {}

private:

  //! Internal collection of Test Case Launchers.
  std::vector< ActTestLib_CaseLauncherAPI* > m_launchers;

public:

  ActTestLib_EXPORT static std::string current_temp_dir; //!< Current temporary directory.

  //! Returns sub-directory used for dumping files.
  //! \return subdirectory dedicated to temporary files.
  inline static std::string current_temp_dir_files()
  {
    return ActAux::slashed(current_temp_dir) + "files";
  }

  //! Returns sub-directory used for reading source files.
  //! \return subdirectory dedicated to source files.
  inline static std::string current_temp_dir_source()
  {
    return ActAux::slashed( ActAux_Env::ActData() );
  }

};

#endif
