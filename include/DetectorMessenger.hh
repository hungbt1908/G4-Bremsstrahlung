#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class DetectorConstruction;

class DetectorMessenger : public G4UImessenger
{
public:
    DetectorMessenger(DetectorConstruction* );
    ~DetectorMessenger();
    void SetNewValue(G4UIcommand*, G4String);

private:
    G4UIdirectory* geometryDir;
    G4UIcmdWithADoubleAndUnit* targetXYDimCmd;
    G4UIcmdWithADoubleAndUnit* targetZThickCmd;
    
    DetectorConstruction* fDetectorConstruction;
};

#endif