#include "EventAction.hh"
#include "G4AnalysisManager.hh"

EventAction::EventAction()
	: G4UserEventAction()
{}

EventAction::~EventAction()
{
	fEdep = 0.0;
}

void EventAction::BeginOfEventAction( const G4Event*)
{
	fEdep = 0.0;
}

void EventAction::EndOfEventAction(const G4Event*)
{
	auto analysisManager = G4AnalysisManager::Instance();
	if(fEdep > 0)
	{
		analysisManager->FillNtupleDColumn(1, 0, fEdep);
		analysisManager->AddNtupleRow(1);
	}
}