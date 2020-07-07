#include "TestDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh" //material
#include "G4PVPlacement.hh" //location
#include "G4SystemOfUnits.hh" //units

TestDetectorConstruction::TestDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

TestDetectorConstruction::~TestDetectorConstruction()
{ }

G4VPhysicalVolume* TestDetectorConstruction::Construct()  //construct geometry information
{  
  G4NistManager* nist = G4NistManager::Instance();
  //     
  // world
  //
  // G4double atomicNumber = 1.;
  // G4double massOfMole = 1.01*g/mole;
  // G4double density = 1.e-25*g/cm3;  // universe mean density from PhysicalConstants.h
  // G4double temperature = 0.1*kelvin;
  // G4double pressure = 1.e-19*pascal;
  // G4Material* world_mat = new G4Material("Galactic", atomicNumber,
  //                                     massOfMole, density, kStateGas, temperature, pressure); 

  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  // check overlaps
  G4bool checkOverlaps = true;
  
  G4Box* solidWorld = new G4Box("World", 50.*cm, 50.*cm, 50.*cm);

  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
 
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Plastic column
  //
  G4Material* polythene = new G4Material("Polythene",0.945*g/cm3,2,kStateSolid,293.15*kelvin);

  G4Tubs* solidColumn = new G4Tubs("column", 0, 4.*cm, 3.5*cm, 0, 360.);

  G4LogicalVolume* logicColumn = new G4LogicalVolume(solidColumn, polythene, "column");

  G4ThreeVector posColumn = G4ThreeVector(0, 0, 1.5);
  new G4PVPlacement(0,
                    posColumn,
                    logicColumn,
                    "column",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

  //
  // Copper cylinder
  //
  G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");

  G4Tubs* solidShell = new G4Tubs("shell", 5.*cm, 7.*cm, 4.*cm, 0, 360.);  
  G4Tubs* solidLid = new G4Tubs("lid", 0, 7.*cm, 1.*cm, 0, 360.);

  G4LogicalVolume* logicShell = new G4LogicalVolume(solidShell, copper, "shell");
  G4LogicalVolume* logicLid = new G4LogicalVolume(solidLid, copper, "lid");

  G4ThreeVector posShell = G4ThreeVector(0, 0, 1);
  new G4PVPlacement(0,
                    posShell,
                    logicShell,
                    "shell",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

  G4ThreeVector posLid = G4ThreeVector(0, 0, -4);
  new G4PVPlacement(0,
                    posLid,
                    logicLid,
                    "lid",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

  return physWorld;
}