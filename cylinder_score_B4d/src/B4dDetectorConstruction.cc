//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B4dDetectorConstruction.cc
/// \brief Implementation of the B4dDetectorConstruction class

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
#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSCellFlux.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* B4dDetectorConstruction::fMagFieldMessenger = 0; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4dDetectorConstruction::B4dDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4dDetectorConstruction::~B4dDetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4dDetectorConstruction::Construct()
{
  // Define materials 
  // DefineMaterials();
  
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
  // Calorimeter
  //  
  G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");
  auto calorimeterS
    = new G4Tubs("Calorimeter", 5.*cm, 7.*cm, 4.*cm, 0, 360.);   

  auto calorLV
    = new G4LogicalVolume(
                 calorimeterS,    // its solid
                 copper, // its material
                 "Calorimeter");  // its name

  G4ThreeVector posShell = G4ThreeVector(0*cm, 0*cm, -1.*cm);          
  new G4PVPlacement(
                 0,                // no rotation
                 posShell,  // at (0,0,0)
                 calorLV,          // its logical volume                         
                 "Calorimeter",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //                                 
  // Layer
  //
  auto layerS 
    = new G4Tubs("Layer", 0, 7.*cm, 1.*cm, 0, 360.); 
                   
  G4ThreeVector posLid = G4ThreeVector(0*cm, 0*cm, 4.001*cm);    
  auto layerLV
    = new G4LogicalVolume(
                 layerS,           // its solid
                 copper,  // its material
                 "Layer");         // its name

  new G4PVPlacement(
                 0,                // no rotation
                 posLid,  // at (0,0,0)
                 layerLV,          // its logical volume                         
                 "Layer",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // witdth of replica
  
  //                               
  // Absorber
  //
  G4Element* el_C = new G4Element("C","C",6,12.0107*g/mole);
  G4Element* el_H = new G4Element("H","H",1.,1.0079*g/mole);
  G4Material* polythene = new G4Material("polythene",0.945*g/cm3,2,kStateSolid,293.15*kelvin);
  polythene->AddElement(el_H,0.143711);
  polythene->AddElement(el_C,0.856289);
  
  auto absorberS 
    = new G4Tubs("column", 0, 4.*cm, 3.5*cm, 0, 360.);

  auto absorberLV
    = new G4LogicalVolume(
                 absorberS,        // its solid
                 polythene, // its material
                 "AbsoLV");          // its name
    
   G4ThreeVector posColumn = G4ThreeVector(0*cm, 0*cm, -1.5*cm);                            
   new G4PVPlacement(
                 0,                // no rotation
                 posColumn,        //  its position
                 absorberLV,       // its logical volume                         
                 "Abso",           // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                               
  // Gap
  //
  auto gapS 
    = new G4Tubs("Gap", 4.001*cm, 4.999*cm, 3.5*cm, 0, 360.);
                         
  auto gapLV
    = new G4LogicalVolume(
                 gapS,             // its solid
                 defaultMaterial,      // its material
                 "GapLV");      // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 posColumn, //  its position
                 gapLV,            // its logical volume                         
                 "Gap",            // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  

  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  // auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  // simpleBoxVisAtt->SetVisibility(true);
  // calorLV->SetVisAttributes(simpleBoxVisAtt);

  auto visColumn = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  // visColumn->SetVisibility(true);
  visColumn->SetForceSolid(true);
  absorberLV->SetVisAttributes(visColumn);

  auto visShell = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  // visShell->SetVisibility(true);
  visShell->SetForceSolid(true);
  layerLV->SetVisAttributes(visShell);

  auto visLid = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  // visLid->SetVisibility(true);
  visLid->SetForceSolid(true);
  calorLV->SetVisAttributes(visLid); 

  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4dDetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  // 
  // Scorers
  //

  // declare Absorber as a MultiFunctionalDetector scorer
  //  
  auto absDetector = new G4MultiFunctionalDetector("Absorber");
  G4SDManager::GetSDMpointer()->AddNewDetector(absDetector);

  G4VPrimitiveScorer* primitive;
  primitive = new G4PSCellFlux("Edep");
  absDetector->RegisterPrimitive(primitive);

  primitive = new G4PSTrackLength("TrackLength");
  auto charged = new G4SDChargedFilter("chargedFilter");
  primitive ->SetFilter(charged);
  absDetector->RegisterPrimitive(primitive);  

  SetSensitiveDetector("AbsoLV",absDetector);

  // declare Gap as a MultiFunctionalDetector scorer
  //  
  auto gapDetector = new G4MultiFunctionalDetector("Gap");
  G4SDManager::GetSDMpointer()->AddNewDetector(gapDetector);

  primitive = new G4PSEnergyDeposit("Edep");
  gapDetector->RegisterPrimitive(primitive);
  
  primitive = new G4PSTrackLength("TrackLength");
  primitive ->SetFilter(charged);
  gapDetector->RegisterPrimitive(primitive);  
  
  SetSensitiveDetector("GapLV",gapDetector);  

  // 
  // Magnetic field
  //
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
