#include "B4dDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"
#include "G4SDParticleFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSCellFlux.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

B4dDetectorConstruction::B4dDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
{
}

B4dDetectorConstruction::~B4dDetectorConstruction()
{ 
}

G4VPhysicalVolume* B4dDetectorConstruction::Construct()
{ 
  // Define volumes
  return DefineVolumes();
}

G4VPhysicalVolume* B4dDetectorConstruction::DefineVolumes()
{
  //     
  // World
  //
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* defaultMaterial = nist->FindOrBuildMaterial("G4_Galactic");
  auto worldS 
    = new G4Box("World", 25.*cm, 25.*cm, 25.*cm);
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //                               
  // Copper shell
  //  
  G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");
  auto shellS
    = new G4Tubs("Shell", 5.*cm, 7.*cm, 4.*cm, 0, 360.);   

  auto shellLV
    = new G4LogicalVolume(
                 shellS,    // its solid
                 copper, // its material
                 "Shell");  // its name

  G4ThreeVector posShell = G4ThreeVector(0*cm, 0*cm, -1.*cm);          
  new G4PVPlacement(
                 0,                // no rotation
                 posShell,  // at (0,0,0)
                 shellLV,          // its logical volume                         
                 "Shell",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //                                 
  // Copper lid
  //
  auto lidS 
    = new G4Tubs("Lid", 0, 7.*cm, 1.*cm, 0, 360.); 
                   
  G4ThreeVector posLid = G4ThreeVector(0*cm, 0*cm, 4.001*cm);    
  auto lidLV
    = new G4LogicalVolume(
                 lidS,           // its solid
                 copper,  // its material
                 "Lid");         // its name

  new G4PVPlacement(
                 0,                // no rotation
                 posLid,  // at (0,0,0)
                 lidLV,          // its logical volume                         
                 "Lid",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // witdth of replica
  
  //                               
  // Polythene cylinder
  //
  G4Element* el_C = new G4Element("C","C",6,12.0107*g/mole);
  G4Element* el_H = new G4Element("H","H",1.,1.0079*g/mole);
  G4Material* polythene = new G4Material("polythene",0.945*g/cm3,2,kStateSolid,293.15*kelvin);
  polythene->AddElement(el_H,0.143711);
  polythene->AddElement(el_C,0.856289);
  
  auto cylinderS 
    = new G4Tubs("Cylinder", 0, 4.*cm, 3.5*cm, 0, 360.);

  auto cylinderLV
    = new G4LogicalVolume(
                 cylinderS,        // its solid
                 polythene, // its material
                 "cyldLV");          // its name
    
   G4ThreeVector posCy = G4ThreeVector(0*cm, 0*cm, -1.5*cm);                            
   new G4PVPlacement(
                 0,                // no rotation
                 posCy,        //  its position
                 cylinderLV,       // its logical volume                         
                 "Cylinder",           // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto visCylinder = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  // visCylinder->SetVisibility(true);
  visCylinder->SetForceSolid(true);
  cylinderLV->SetVisAttributes(visCylinder);

  auto visShell = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  // visShell->SetVisibility(true);
  visShell->SetForceSolid(true);
  lidLV->SetVisAttributes(visShell);

  auto visLid = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  // visLid->SetVisibility(true);
  visLid->SetForceSolid(true);
  shellLV->SetVisAttributes(visLid); 

  //
  // Always return the physical World
  //
  return worldPV;
}

void B4dDetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  // 
  // Scorers
  //

  // declare Cylinder as a MultiFunctionalDetector scorer
  //  
  auto cylDetector = new G4MultiFunctionalDetector("Cylinder");
  G4SDManager::GetSDMpointer()->AddNewDetector(cylDetector);

  G4VPrimitiveScorer* primitive;
  primitive = new G4PSCellFlux("Flux");
  auto neutronFilter = new G4SDParticleFilter("neutronFilter", "neutron");
  primitive ->SetFilter(neutronFilter);
  cylDetector->RegisterPrimitive(primitive);  

  SetSensitiveDetector("cyldLV",cylDetector);

}
