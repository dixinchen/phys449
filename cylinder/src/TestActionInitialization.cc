
#include "TestActionInitialization.hh"
#include "TestPrimaryGeneratorAction.hh"  //**
// #include "TestRunAction.hh"


TestActionInitialization::TestActionInitialization()
 : G4VUserActionInitialization()
{}

TestActionInitialization::~TestActionInitialization()
{}

void TestActionInitialization::BuildForMaster() const
{
  // TestRunAction* runAction = new TestRunAction;
  // SetUserAction(runAction);
}

void TestActionInitialization::Build() const
{
  SetUserAction(new TestPrimaryGeneratorAction);

  // TestRunAction* runAction = new TestRunAction;
  // SetUserAction(runAction);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
