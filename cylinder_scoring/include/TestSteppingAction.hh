#ifndef TestSteppingAction_h
#define TestSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class TestEventAction;
class G4LogicalVolume;

class TestSteppingAction : public G4UserSteppingAction
{
  public:
    TestSteppingAction(TestEventAction* EventAction);
    virtual ~TestSteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    TestEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

#endif
