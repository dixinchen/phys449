#ifndef B4dDetectorConstruction_h
#define B4dDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

class B4dDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B4dDetectorConstruction();
    virtual ~B4dDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:
    // methods
    //
    G4VPhysicalVolume* DefineVolumes();

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

#endif

