#include "TestDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh" 
#include "G4Colour.hh"
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

  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  // check overlaps
  G4bool checkOverlaps = true;
  
  G4Orb* solidWorld = new G4Orb("World",200*cm); //full solid sphere of radius 200 cm.

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
  G4Element* el_Al = new G4Element("TS_Aluminium_Metal","Al",13.,26.98*g/mole);
  G4Element* el_Au = new G4Element("Gold", "Au", 79, 196.97*g/mole);
  G4double goldfoil_density = 19.3*g/cm3 ; //obtained from the specification sheet
  G4Material* foil_mat =  new G4Material("foil_mat",goldfoil_density,2);
  foil_mat-> AddElement(el_Au, 99.99*perCent); // Note that we use pure gold foil
  foil_mat-> AddElement(el_Al, 0.01*perCent); // No information about the 0.01% trace metals. Al was an arbitary choice.

  G4Element* el_C = new G4Element("C","C",6,12.0107*g/mole);
  G4Element* el_H = new G4Element("TS_H_of_Polyethylene","H",1.,1.0079*g/mole);
  G4Element* el_O = new G4Element("O","O",8,15.999*g/mole);
  G4Material* Acetal = new G4Material("Acetal",1.42*g/cm3,3,kStateSolid,293.15*kelvin);
  Acetal->AddElement(el_H,2);
  Acetal->AddElement(el_C,1);
  Acetal->AddElement(el_O,1);

  G4double gold_thick=0.01*cm; // real value is 0.01*cm
  G4double gold_rad=0.8*cm; // this is the inner radius of the first shell and of goldfoil
  G4double small_insert_len=2.54*cm;   // 2.54 length of the small part of the whole insert
  G4double big_insert_len = 5.46*cm;  // 5.46, length of the big part of the insert
  // The small insert is used while performing the measurement with bare foil
  G4Tubs* small_insert = new G4Tubs("small_insert",0.0,gold_rad-0.001,small_insert_len/2,0,360);  //length needs to be given as half length. For some weired reason, tube radius shld be smaller than gold for the visualization.
  G4LogicalVolume* small_insert_logic = new G4LogicalVolume(small_insert,Acetal,"small_insert_logic",0,0,0);
  new G4PVPlacement(0,G4ThreeVector(0,0,-1.275*cm),small_insert_logic,"Small_insert",logicWorld,false,0,checkOverlaps);
  G4Tubs* goldfoil                = new G4Tubs("goldfoil",0.0*cm,gold_rad,gold_thick/2,0,360);
  G4LogicalVolume* LogicGold      = new G4LogicalVolume(goldfoil,foil_mat,"goldfoil",0,0,0);
  new G4PVPlacement(0,G4ThreeVector(0,0,0),LogicGold,"goldfoil",logicWorld,false,0);

  // G4double gold_thick = 0.01*cm;
  // G4double gold_rad = 0.75*cm;
  // G4double small_insert_len = 2.54*cm;
  
  // G4RotationMatrix* Rotation = new G4RotationMatrix();
  // Rotation->rotateX(90.*deg);
  // Rotation->rotateY(0.*deg);
  // Rotation->rotateZ(0.*deg);
  // G4Box* goldfoil = new G4Box("goldfoil",gold_rad,gold_rad,gold_thick/2);
  // G4LogicalVolume* LogicGold = new G4LogicalVolume(goldfoil,foil_mat,"goldfoil",0,0,0);
  // new G4PVPlacement(Rotation,G4ThreeVector(0,0,0),LogicGold,"goldfoil",logicWorld,false,0);

  // G4Tubs* small_insert_full = new G4Tubs("small_insert_full",0.0,(0.8-0.001)*cm,small_insert_len/2.,0,360);
  //  G4double groove_thick = gold_thick+0.001*cm;
  //  G4double groove_rad = gold_rad+0.0005*cm;
  //  G4Box* groove = new G4Box("groove",groove_rad,groove_rad,groove_thick/2.);
  //  G4double groove_pm = small_insert_len/2.-groove_rad;
  // G4SubtractionSolid* small_insert = new G4SubtractionSolid("small_insert", 
  //                                                           small_insert_full, 
  //                                                           groove, 
  //                                                           Rotation, 
  //                                                           G4ThreeVector(0.0, 0.0, groove_pm));
  // G4LogicalVolume* small_insert_logic = new G4LogicalVolume(small_insert,Acetal,"small_insert_logic",0,0,0);
  // G4double pm = -(small_insert_len/2.-gold_rad);
  // new G4PVPlacement(0,G4ThreeVector(0,0,pm),small_insert_logic,"Small_insert",logicWorld,false,0,checkOverlaps);
  
  
  //-----------------------------------------------------------------------------------------------------

  G4VisAttributes* visWorld = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  visWorld->SetVisibility(true);
  logicWorld->SetVisAttributes(visWorld);

  G4VisAttributes* visGoldFoil = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  // visGoldFoil->SetVisibility(true);
  visGoldFoil->SetForceSolid(true);
  LogicGold->SetVisAttributes(visGoldFoil);

  G4VisAttributes* visInsert = new G4VisAttributes(G4Colour(1.0,1.0,1.0,0.4));
  // visInsert->SetVisibility(true);
  visInsert->SetForceSolid(true);
  small_insert_logic->SetVisAttributes(visInsert);

  return physWorld;
}