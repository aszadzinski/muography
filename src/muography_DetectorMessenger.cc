#include "muography_DetectorMessenger.hh"

#include "muography_DetectorConstruction.hh"

#include "G4UIdirectory.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"


muography_DetectorMessenger::muography_DetectorMessenger(muography_DetectorConstruction* Det):G4UImessenger(),
myDetector(Det)
{


//////////////////////////////
// Directory
//////////////////////////////

  muographyDir = new G4UIdirectory("/geo/");
  muographyDir->SetGuidance("Simulation control. Geometry");

//////////////////////////////
// Generation Parameters


  fTrainX = new G4UIcmdWithADoubleAndUnit("/geo/fTrainX",this);
  fTrainX->SetGuidance("X Train position [m]");
  fTrainX->SetDefaultUnit("m");
  fTrainY = new G4UIcmdWithADoubleAndUnit("/geo/fTrainY",this);
  fTrainY->SetGuidance("Y Train position [m]");
  fTrainY->SetDefaultUnit("m");
  fTrainZ = new G4UIcmdWithADoubleAndUnit("/geo/fTrainZ",this);
  fTrainZ->SetGuidance("Z Train position [m]");
  fTrainZ->SetDefaultUnit("m");

  fRockX = new G4UIcmdWithADoubleAndUnit("/geo/fRockX",this);
  fRockX->SetGuidance("Rock thickness [m]");
  fRockX->SetDefaultUnit("m");

  fRockYZ = new G4UIcmdWithADoubleAndUnit("/geo/fRockYZ",this);
  fRockYZ->SetGuidance("Rock YZ lenght [m]");
  fRockYZ->SetDefaultUnit("m");

  fDetX = new G4UIcmdWithADoubleAndUnit("/geo/fDetX",this);
  fDetX->SetGuidance("Detectors thickness [m]");
  fDetX->SetDefaultUnit("m");

  fDetYZ = new G4UIcmdWithADoubleAndUnit("/geo/fDetYZ",this);
  fDetYZ->SetGuidance("Detectors YZ lenght [m]");
  fDetYZ->SetDefaultUnit("m");

  fTrainR = new G4UIcmdWithADoubleAndUnit("/geo/fTrainR",this);
  fTrainR->SetGuidance("Train radius [m]");
  fTrainR->SetDefaultUnit("m");

  fTChamberR = new G4UIcmdWithADoubleAndUnit("/geo/fTChamberR",this);
  fTChamberR->SetGuidance("Train Chamber radius [m]");
  fTChamberR->SetDefaultUnit("m");

}

muography_DetectorMessenger::~muography_DetectorMessenger()
{
//////////////////////////////
// Generation Parameters
//////////////////////////////
  delete fTrainX;
  delete fTrainY;
  delete fTrainZ;
  delete fDetX;
  delete fDetYZ;
  delete fTChamberR;
  delete fTrainR;
  delete fRockX;
  delete fRockYZ;

}
void muography_DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{

//////////////////////////////
// Generation Parameters
//////////////////////////////
   if(command==fTrainX) myDetector->SetTrainX(fTrainX->GetNewDoubleValue(newValues));
   else if(command==fTrainY) myDetector->SetTrainY(fTrainY->GetNewDoubleValue(newValues));
   else if(command==fTrainZ) myDetector->SetTrainZ(fTrainZ->GetNewDoubleValue(newValues));
   else if(command==fRockX) myDetector->SetRockX(fRockX->GetNewDoubleValue(newValues));
   else if(command==fRockYZ) myDetector->SetRockYZ(fRockYZ->GetNewDoubleValue(newValues));
   else if(command==fTChamberR) myDetector->SetTChamberR(fTChamberR->GetNewDoubleValue(newValues));
   else if(command==fTrainR) myDetector->SetTrainR(fTrainR->GetNewDoubleValue(newValues));
   else if(command==fDetX) myDetector->SetDetX (fDetX->GetNewDoubleValue(newValues));
   else if(command==fDetYZ) myDetector->SetDetYZ (fDetYZ->GetNewDoubleValue(newValues));

}
