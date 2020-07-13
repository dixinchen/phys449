#include "TestEventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"

TestEventAction::TestEventAction()
: G4UserEventAction()
{}

TestEventAction::~TestEventAction()
{}

void TestEventAction::BeginOfEventAction(const G4Event*)
{}

void TestEventAction::EndOfEventAction(const G4Event*)
{}