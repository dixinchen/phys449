#include "TestSteppingAction.hh"
#include "TestEventAction.hh"
#include "TestRunAction.hh"
#include "TestDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

TestSteppingAction::TestSteppingAction(TestEventAction* )
:G4UserSteppingAction(),
fEventAction(0), fScoringVolume(0)
{}

TestSteppingAction::~TestSteppingAction()
{}

void TestSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4cout<<"1111111111111111111111111 test :,)"<<G4endl;
  
  if (!fScoringVolume) { 
    const TestDetectorConstruction* detectorConstruction
      = static_cast<const TestDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetVolume(); 
  }

  // get volume of the current step
  // G4LogicalVolume* volume 
  //   = step->GetPreStepPoint()->GetTouchableHandle()
  //     ->GetVolume()->GetLogicalVolume();

  // // get steps
  const G4StepPoint* preStepPoint = step->GetPreStepPoint();
  // // const G4StepPoint* postStepPoint = step->GetPostStepPoint();
  
  G4cout<<"----------------------------- test :,)"<<G4endl;
  G4LogicalVolume* volume 
    = preStepPoint->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  // if(preStepPoint->GetStepStatus()--fGeomBoundary) return;
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;
  // G4cout<<" Volume name"<<fScoringVolume->GetName()<<G4endl;


  const G4Track* track = step->GetTrack();
  const G4ThreeVector&momentum = track->GetMomentum();
  const G4double kinEnergy = track->GetKineticEnergy();
  const G4double eDeposit = step->GetTotalEnergyDeposit();
  const G4double sLength = step->GetStepLength();

  G4cout<<"Momentum = "<<momentum<<G4endl;
  G4cout<<"Ekin = "<<kinEnergy/MeV<<G4endl;
  G4cout<<"eDeposit = "<<eDeposit<<G4endl;
  G4cout<<"sLength = "<<sLength<<G4endl;
}
