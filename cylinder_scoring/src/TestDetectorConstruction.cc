#include "TestDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh" 
#include "G4Colour.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4PSCellFlux.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh" //material
#include "G4PVPlacement.hh" //location
#include "G4SystemOfUnits.hh" //units

TestDetectorConstruction::TestDetectorConstruction()
: G4VUserDetectorConstruction(),fVolume(0)
{}

TestDetectorConstruction::~TestDetectorConstruction()
{}


G4VPhysicalVolume* TestDetectorConstruction::Construct()  //construct geometry information
{  
  G4NistManager* nist = G4NistManager::Instance();  

  // check overlaps
  G4bool checkOverlaps = true;

  //     
  // world
  //
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld = new G4Box("World", 25.*cm, 25.*cm, 25.*cm);

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
  G4Element* el_C = new G4Element("C","C",6,12.0107*g/mole);
  G4Element* el_H = new G4Element("H","H",1.,1.0079*g/mole);
  G4Material* polythene = new G4Material("polythene",0.945*g/cm3,2,kStateSolid,293.15*kelvin);
  polythene->AddElement(el_H,0.143711);
  polythene->AddElement(el_C,0.856289);

  G4Tubs* solidColumn = new G4Tubs("Polythene", 0, 4.*cm, 3.5*cm, 0, 360.);

  G4LogicalVolume* logicColumn = new G4LogicalVolume(solidColumn, polythene, "Polythene");

  G4ThreeVector posColumn = G4ThreeVector(0*cm, 0*cm, -1.5*cm);
  new G4PVPlacement(0,
                    posColumn,
                    logicColumn,
                    "Polythene",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

  //
  // Copper cylinder
  //
  G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");

  G4Tubs* solidShell = new G4Tubs("Cu shell", 5.*cm, 7.*cm, 4.*cm, 0, 360.);  
  G4Tubs* solidLid = new G4Tubs("Cu lid", 0, 7.*cm, 1.*cm, 0, 360.);

  G4LogicalVolume* logicShell = new G4LogicalVolume(solidShell, copper, "Cu shell");
  G4LogicalVolume* logicLid = new G4LogicalVolume(solidLid, copper, "Cu lid");

  G4ThreeVector posShell = G4ThreeVector(0*cm, 0*cm, -1.*cm);
  new G4PVPlacement(0,
                    posShell,
                    logicShell,
                    "Cu shell",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

  G4ThreeVector posLid = G4ThreeVector(0*cm, 0*cm, 4.001*cm);
  new G4PVPlacement(0,
                    posLid,
                    logicLid,
                    "Cu lid",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

  //     
  // Envelope
  //
  G4Tubs* solidEnv = new G4Tubs("Envelope", 0, 4.*cm, 3.5*cm, 0, 360.);
  
  G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,
                        world_mat,
                        "Envelope");

  new G4PVPlacement(0,
                    G4ThreeVector(),
                    logicEnv,
                    "Envelope",
                    logicColumn,
                    false,
                    0,
                    checkOverlaps);

G4VisAttributes* visWorld = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
visWorld->SetVisibility(true);
logicWorld->SetVisAttributes(visWorld);

G4VisAttributes* visEnv = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
visEnv->SetVisibility(true);
logicEnv->SetVisAttributes(visEnv);

G4VisAttributes* visColumn = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
// visColumn->SetVisibility(true);
visColumn->SetForceSolid(true);
logicColumn->SetVisAttributes(visColumn);

G4VisAttributes* visShell = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
// visShell->SetVisibility(true);
visShell->SetForceSolid(true);
logicShell->SetVisAttributes(visShell);

G4VisAttributes* visLid = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
// visLid->SetVisibility(true);
visLid->SetForceSolid(true);
logicLid->SetVisAttributes(visLid);

fVolume = logicEnv;

return physWorld;
}