#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Material;
class G4LogicalVolume;
class G4VPhysicalVolume;
class DetectorMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{

public:
	DetectorConstruction();
	~DetectorConstruction();
	
	virtual G4VPhysicalVolume* Construct();
	void DefineMaterial();
	G4VPhysicalVolume* ConstructVolume();

	inline void SetTargetXYDimension(G4double val){targetXYDim = val;}
	inline void SetTargetZDimension(G4double val){tagetZDim = val;}
	inline G4double GetTargetXYDimension(){return targetXYDim;}
	inline G4double GetTargetZDimension(){return tagetZDim;}
	G4LogicalVolume* GetScoringVolume() const {return fScoringVolume;}

private:
	G4bool checkOverlap = true;
	G4Material* Air, * Vacuum, * Al, * Tungsten, * Germanium;
	G4LogicalVolume* logicWorld;
	G4VPhysicalVolume* physWorld;

	G4LogicalVolume* fScoringVolume;

	G4double targetXYDim;
	G4double tagetZDim;
	//G4ThreeVector targetPos();

	DetectorMessenger* fDetMessenger;
};

#endif
