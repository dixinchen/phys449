
#include "TestActionInitialization.hh"
#include "TestPrimaryGeneratorAction.hh"  //**


TestActionInitialization::TestActionInitialization()
 : G4VUserActionInitialization()
{}

TestActionInitialization::~TestActionInitialization()
{}

void TestActionInitialization::BuildForMaster() const
{
}

void TestActionInitialization::Build() const
{
  SetUserAction(new TestPrimaryGeneratorAction);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......