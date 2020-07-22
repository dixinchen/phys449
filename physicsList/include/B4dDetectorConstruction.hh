#ifndef B4dDetectorConstruction_h
#define B4dDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In ConstructSDandField() sensitive detectors of G4MultiFunctionalDetector 
/// type with primitive scorers are created and associated with the Absorber 
/// and Gap volumes.  In addition a transverse uniform magnetic field is defined
/// via G4GlobalMagFieldMessenger class.

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

