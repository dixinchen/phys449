#include "B4dActionInitialization.hh"
#include "B4PrimaryGeneratorAction.hh"
#include "B4RunAction.hh"
#include "B4dEventAction.hh"

B4dActionInitialization::B4dActionInitialization()
 : G4VUserActionInitialization()
{}

B4dActionInitialization::~B4dActionInitialization()
{;}


void B4dActionInitialization::BuildForMaster() const
{
  SetUserAction(new B4RunAction);
}

void B4dActionInitialization::Build() const
{
  SetUserAction(new B4PrimaryGeneratorAction);
  SetUserAction(new B4RunAction);
  SetUserAction(new B4dEventAction);
}  
