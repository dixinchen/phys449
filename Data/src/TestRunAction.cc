#include "TestRunAction.hh"
#include "analysis.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"

// constructor
TestRunAction::TestRunAction(analysis* A_analy)
:G4UserRunAction(),Analysis(A_analy)
{}

// virtual function
TestRunAction::~TestRunAction()
{}

// open & close file
void TestRunAction::BeginOfRunAction(const G4Run*)
{
  // output.open("test.txt",ios::app);
  // output<<"This is a test for run action.";
  Analysis->Book();
}

void TestRunAction::EndOfRunAction(const G4Run*)
{
  // output.close();
  Analysis->Save();
}