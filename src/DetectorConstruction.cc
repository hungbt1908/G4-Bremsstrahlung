#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4SystemOfUnits.hh"

#include "G4NistManager.hh"
#include "G4VisAttributes.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
	fDetMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
	delete fDetMessenger;
}

G4VPhysicalVolume *DetectorConstruction :: Construct()
{
	DefineMaterial();
	return ConstructVolume();
}

void DetectorConstruction::DefineMaterial()
{
	G4NistManager* nist = G4NistManager::Instance();
	Air = nist->FindOrBuildMaterial("G4_AIR");
	Al = nist->FindOrBuildMaterial("G4_Al");
	Vacuum = nist->FindOrBuildMaterial("G4_Galactic");
	Tungsten = nist->FindOrBuildMaterial("G4_W");
	Germanium = nist->FindOrBuildMaterial("G4_Ge");
}

G4VPhysicalVolume* DetectorConstruction::ConstructVolume()
{
	// Mother World
	G4Box* solidWorld = new G4Box("solidWorld", 50.*cm, 50.*cm, 50.*cm);
	logicWorld = new G4LogicalVolume(solidWorld, Vacuum, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, checkOverlap);
	logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());
	
	// Target
	G4Box* solidTarget = new G4Box("solidTarget", targetXYDim/2.0, targetXYDim/2.0, tagetZDim/2.0);
	G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, Tungsten, "logicTarget");
	new G4PVPlacement(0, G4ThreeVector(), logicTarget, "physTarget", logicWorld, false, 0, checkOverlap);

	// Detector
	G4double detectorXYSize = 2.0*cm;
	G4double detectorZSize = 1.0*cm;

	G4Box* solidDetector = new G4Box("logicDetector", detectorXYSize/2.0, detectorXYSize/2.0, detectorZSize/2.0);
	G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, Germanium, "logicDetector");
	new G4PVPlacement(0, G4ThreeVector(0., 0., 2.0*cm), logicDetector, "physDetector", logicWorld, false, 0, checkOverlap);
	fScoringVolume = logicDetector;

	return physWorld;
}