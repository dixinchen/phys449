#ifndef TestActionInitialization_h
#define TestActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class TestActionInitialization : public G4VUserActionInitialization
{
  public:
    TestActionInitialization();
    virtual ~TestActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif