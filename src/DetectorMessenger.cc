#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* pDetectorConstruction)
    : G4UImessenger(), fDetectorConstruction(pDetectorConstruction)
{
    // create directory
    geometryDir = new G4UIdirectory("/Bremss/Geometry/");
    geometryDir->SetGuidance("............................");

    //
    targetXYDimCmd = new G4UIcmdWithADoubleAndUnit("/Bremss/Geometry/SetTargetXYDim", this);
    targetXYDimCmd->SetGuidance("Set Target Size along X and Y axis.");
    targetXYDimCmd->SetParameterName("TargetXYDim", false);
    targetXYDimCmd->SetUnitCategory("Length");
    targetXYDimCmd->SetRange("TargetXYDim>0.0");
    targetXYDimCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    // 
    targetZThickCmd = new G4UIcmdWithADoubleAndUnit("/Bremss/Geometry/SetTargetZDim", this);
    targetZThickCmd->SetGuidance("Set Target Size along Z axis");
    targetZThickCmd->SetParameterName("TargetZDim", false);
    targetZThickCmd->SetUnitCategory("Length");

}

DetectorMessenger::~DetectorMessenger()
{
    delete geometryDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if(command == targetXYDimCmd)
    {
        fDetectorConstruction->SetTargetXYDimension(targetXYDimCmd->GetNewDoubleValue(newValue));
    }

    if(command == targetZThickCmd)
    {
        fDetectorConstruction->SetTargetZDimension(targetZThickCmd->GetNewDoubleValue(newValue));
    }
}



