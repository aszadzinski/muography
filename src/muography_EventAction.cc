#include "muography_EventAction.hh"
#include "muography_RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
std::ofstream file,file2;



muography_EventAction::muography_EventAction(muography_RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  EdepA(0.), EdepB(0.),EntA(0),EntB(0)
{
  file.open("./output.dat");
  file2.open("./output2.dat");
}

muography_EventAction::~muography_EventAction()
{
  file.close();
  file2.close();
}

void muography_EventAction::BeginOfEventAction(const G4Event* env)
{

  if (!(env->GetEventID()%1000)) G4cout << "\n--> Begin of event: " << env->GetEventID() <<G4endl;

  EdepA = 0.;
  posAX = 0.;
  posAY = 0.;
  posAZ = 0.;
  dFlagA = 0;
  EdepB = 0.;
  posBX = 0.;
  posBY = 0.;
  posBZ = 0.;
  dFlagB = 0;
  EntA = 0;
  EntB = 0;

}

void muography_EventAction::EndOfEventAction(const G4Event*)
{
  if (dFlagA == 1 && dFlagB == 1)
  {
    file<<fGunE<<" "<<fPosX<<" "<<fPosZ<<G4endl;
  }
    file2<<fGunE<<" "<<fPosX<<" "<<fPosZ<<" "<<dFlagA<<" "<<dFlagB<<G4endl;
  fRunAction->AddEdep(EdepA);
  //G4cout<<"Edep="<<EdepA<<G4endl;
}
