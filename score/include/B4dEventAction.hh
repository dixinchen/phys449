#ifndef B4dEventAction_h
#define B4dEventAction_h 1

#include "G4UserEventAction.hh"

#include "G4THitsMap.hh"
#include "globals.hh"

class B4dEventAction : public G4UserEventAction
{
public:
  B4dEventAction();
  virtual ~B4dEventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);
    
private:
  // methods
  G4THitsMap<G4double>* GetHitsCollection(G4int hcID,
                                          const G4Event* event) const;
  G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
  void PrintEventStatistics(G4double flux) const;
  
  // data members                   
  G4int  fFluxHCID;
};

#endif

    
