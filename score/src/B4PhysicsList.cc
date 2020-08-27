#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonElasticPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"

#include "B4PhysicsList.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"

B4PhysicsList::B4PhysicsList()
: G4VModularPhysicsList(){
  SetVerboseLevel(1);

  // defaultCutValue = 0.7*CLHEP::mm;  
  // SetCutValue(0, "proton");  

  // EM Physics
  RegisterPhysics( new G4EmStandardPhysics_option4());

  // Synchroton Radiation & GN Physics
  RegisterPhysics( new G4EmExtraPhysics());

  // Decays
  RegisterPhysics( new G4DecayPhysics());
  RegisterPhysics( new G4RadioactiveDecayPhysics());

  // Hadron Elastic scattering
  RegisterPhysics( new G4HadronElasticPhysicsHP());

  // Hadron Physics
  RegisterPhysics(  new G4HadronPhysicsQGSP_BIC_HP());

  // Stopping Physics
  RegisterPhysics( new G4StoppingPhysics());

  // Ion Physics
  RegisterPhysics( new G4IonElasticPhysics());
  RegisterPhysics( new G4IonPhysics());

}

B4PhysicsList::~B4PhysicsList()
{ 
}

void B4PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}  
