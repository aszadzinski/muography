
#include "muography_DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "muography_DetectorMessenger.hh"
#include "G4Orb.hh"
#include "G4Box.hh"

#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "cmath"

muography_DetectorConstruction::muography_DetectorConstruction()
: G4VUserDetectorConstruction(),
  fEdA(0), fEdB(0), fEdR(0), fEdTC(0), fEdT(0)
{ fMessenger = new muography_DetectorMessenger(this);}

muography_DetectorConstruction::~muography_DetectorConstruction()
{
delete fMessenger;}

G4VPhysicalVolume* muography_DetectorConstruction::Construct()
{  G4NistManager* man = G4NistManager::Instance();
    //Materials
    //G4double a, z, density;
    G4double da, daz, dadensity;
    G4double db, dbz, dbdensity;
    G4String name, symbol;
    G4int ncomponents, natoms;

    da = 12.011*g/mole;
    G4bool isotopes = false;
    G4Element*  O = man->FindOrBuildElement("O" , isotopes);
    G4Element* Si = man->FindOrBuildElement("Si", isotopes);
    G4Element* Lu = man->FindOrBuildElement("Lu", isotopes);
    G4Material* LSO = new G4Material("Lu2SiO5", 7.4*g/cm3, 3);
    LSO->AddElement(Lu, 2);
    LSO->AddElement(Si, 1);
    LSO->AddElement(O , 5);

    G4Element* elC = new G4Element(name="Carbon", symbol="C", daz=6., da);
    da = 1.0079*g/mole;
    G4Element* elH = new G4Element(name="Hydrogen", symbol="H", daz=1.,da);

    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

    // Plastic scintillator BC-408 (vinyltoluene based)
    dadensity = 1.032*g/cm3;
    G4Material* BC408 = new G4Material(name="BC-408", dadensity, ncomponents = 2);
    BC408->AddElement(elC, natoms = 1000);
    BC408->AddElement(elH, natoms = 1103);
    G4bool checkOverlaps = true;
    G4Material* cryst_mat   = nist->FindOrBuildMaterial("Lu2SiO5");

    //Geometry
    G4double worldXY = 3100*m, worldZ = 3100*m;

    G4ThreeVector posDA = G4ThreeVector(-fDetX-fRockX/2, 0, 0);
    G4ThreeVector posDB = G4ThreeVector(fDetX+fRockX/2, 0, 0);
    G4ThreeVector posTC = G4ThreeVector(fTrainX, fTrainY, fTrainZ);

    //G4RotationMatrix* rotS = new G4RotationMatrix;
    //rotS->rotateY(M_PI/2*rad);

    //World
    G4Box* worldShape = new G4Box("World", worldXY, worldXY, worldZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(worldShape, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,  "World", 0, false, 0, checkOverlaps);

    //Train chamber
    G4double tubePhi = 2.*M_PI;
    G4Orb* tchamberShape = new G4Orb("TChamber",fTChamberR);
    G4LogicalVolume* logicTChamber = new G4LogicalVolume(tchamberShape, air, "TChamber");
    G4PVPlacement* physTChamber =  new G4PVPlacement(0, posTC, logicTChamber, "TChamber", logicWorld, false, 0, checkOverlaps);
    fEdTC = logicTChamber;

    //Train
    G4Orb* trainShape = new G4Orb("Train",fTrainR);
    G4LogicalVolume* logicTrain = new G4LogicalVolume(trainShape, BC408, "Train");
    G4PVPlacement* physTrain =  new G4PVPlacement(0, posTC, logicTrain, "Train", logicWorld, false, 0, checkOverlaps);
    fEdT = logicTrain;

    //Rock
    G4Box* rockShape = new G4Box("Rock", fRockX/2, fRockYZ/2, fRockYZ/2);
    G4LogicalVolume* logicRock = new G4LogicalVolume(rockShape, BC408, "Rock");
    G4VPhysicalVolume* physRock = new G4PVPlacement(0, G4ThreeVector(), logicRock,  "Rock", logicWorld, false, 0, checkOverlaps);
    fEdR = logicRock;

    //Detectors
    G4Box* detectorShapeA = new G4Box("DetectorA", fDetX/2, fDetYZ/2, fDetYZ/2);
    G4LogicalVolume* logicDetectorA = new G4LogicalVolume(detectorShapeA, BC408, "ADetector");
    G4PVPlacement *physDetectorA =  new G4PVPlacement(0, posDA, logicDetectorA, "ADetector", logicWorld, false, 0, checkOverlaps);
    fEdA = logicDetectorA;

    G4Box* detectorShapeB = new G4Box("DetectorA", fDetX/2, fDetYZ/2, fDetYZ/2);
    G4LogicalVolume* logicDetectorB = new G4LogicalVolume(detectorShapeB, BC408, "BDetector");
    G4PVPlacement *physDetectorB =  new G4PVPlacement(0, posDB, logicDetectorB, "BDetector", logicWorld, false, 0, checkOverlaps);
    fEdB = logicDetectorB;

    return physWorld;
}
