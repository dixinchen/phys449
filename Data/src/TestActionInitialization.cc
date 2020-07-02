
#include "TestActionInitialization.hh"
#include "TestPrimaryGeneratorAction.hh"  //**
#include "TestRunAction.hh"
#include "TestEventAction.hh"
#include "TestSteppingAction.hh"
#include "analysis.hh"

TestActionInitialization::TestActionInitialization()
 : G4VUserActionInitialization()
{}

TestActionInitialization::~TestActionInitialization()
{}

void TestActionInitialization::BuildForMaster() const
{
  analysis* A_analy = new analysis();
  TestRunAction* runAction = new TestRunAction(A_analy);
  SetUserAction(runAction);
}

void TestActionInitialization::Build() const
{
  SetUserAction(new TestPrimaryGeneratorAction);

  analysis *A_analy = new analysis();

  TestRunAction* runAction = new TestRunAction(A_analy);
  SetUserAction(runAction);

  TestEventAction* eventAction = new TestEventAction;
  SetUserAction(eventAction);

  SetUserAction(new TestSteppingAction(eventAction, A_analy));

}  
