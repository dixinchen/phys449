#ifndef TestDetectorConstruction_h
#define TestDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class TestDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    TestDetectorConstruction();
    virtual ~TestDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
