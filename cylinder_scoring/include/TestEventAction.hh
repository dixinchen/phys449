#ifndef TestEventAction_h
#define TestEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class TestEventAction : public G4UserEventAction
{
  public:
    TestEventAction();
    virtual ~TestEventAction();

    virtual void  BeginOfEventAction(const G4Event* );
    virtual void    EndOfEventAction(const G4Event* );
};

#endif
