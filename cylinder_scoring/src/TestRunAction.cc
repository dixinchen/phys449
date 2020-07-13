#include "TestRunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"

// constructor
TestRunAction::TestRunAction()
:G4UserRunAction()
{}

// virtual function
TestRunAction::~TestRunAction()
{}

// open & close file
void TestRunAction::BeginOfRunAction(const G4Run*)
{
  output.open("test.txt",ios::app);
  output<<"This is a test for run action.";
}

void TestRunAction::EndOfRunAction(const G4Run*)
{
  output.close();
}