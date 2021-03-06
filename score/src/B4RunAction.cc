#include "B4RunAction.hh"
#include "B4Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
// #include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

B4RunAction::B4RunAction()
 : G4UserRunAction()
{ 
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  analysisManager->CreateH1("Flux","Flux in cylinder", 100, 0., 8*MeV);
}

B4RunAction::~B4RunAction()
{
  delete G4AnalysisManager::Instance();  
}

void B4RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
}


void B4RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  auto analysisManager = G4AnalysisManager::Instance();
    
  G4cout <<"--------------------------------------------\n"<< " Cell flux : mean = " 
      << analysisManager->GetH1(0)->mean()
      << " rms = " 
      << analysisManager->GetH1(0)->rms()
      <<"\n--------------------------------------------\n"<< G4endl;
}
