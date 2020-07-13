#ifndef TestRunAction_h
#define TestRunAction_h 1

#include "fstream"
#include "G4UserRunAction.hh"
#include "globals.hh"

using namespace std;
class G4Run;
// class analysis;

class TestRunAction: public G4UserRunAction
{
  public:
   TestRunAction();
   virtual ~TestRunAction();

   virtual void BeginOfRunAction(const G4Run* run );
   virtual void EndOfRunAction(const G4Run* run);

  private:
   ofstream output;
};

#endif