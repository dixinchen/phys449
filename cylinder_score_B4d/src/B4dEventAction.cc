#include "B4dEventAction.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>
#include <string>
#include <iostream>

B4dEventAction::B4dEventAction()
 : G4UserEventAction(),
   fFluxHCID(-1)
{}

B4dEventAction::~B4dEventAction()
{}

G4THitsMap<G4double>* 
B4dEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection 
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4dEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

G4double B4dEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0.;
  for ( auto it : *hitsMap->GetMap() ) {
    // hitsMap->GetMap() returns the map of std::map<G4int, G4double*>
    sumValue += *(it.second);
  }
  return sumValue;  
}  

void B4dEventAction::PrintEventStatistics(G4double flux) const
{
  // Print event statistics
  //
  G4cout
     << "   Cylinder: flux: " 
     << std::setw(7) << G4BestUnit(analysisManager->GetH1(0)->mean(),  "Surface")  /*std::to_string(flux)*/
     << G4endl;
}

void B4dEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

void B4dEventAction::EndOfEventAction(const G4Event* event)
{  
   // Get hist collections IDs
  if ( fFluxHCID == -1 ) {
    fFluxHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("Cylinder/Flux");
  }
  
  // Get sum values from hits collections
  //
  auto flux = GetSum(GetHitsCollection(fFluxHCID, event));

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  //  
  analysisManager->FillH1(0, flux);
  
  //print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     
    PrintEventStatistics(flux);
  }
}  
