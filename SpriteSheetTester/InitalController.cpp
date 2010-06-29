#include <iostream>
#include "InitalController.h"
#include "ControllerInterface.h"
#include "GameController.h"

InitalController::InitalController() {
	displayChanged = true;
	}

InitalController::~InitalController() {
	}

void InitalController::iniController() {
	}

ControllerReturn* InitalController::runEventHandler(ALLEGRO_EVENT_QUEUE *queue) {
	cout << "Enter spritesheet to preview: ";
	string s;
	cin >> s;

	if (s.compare("done") == 0) {
		return new ControllerReturn(true, NULL);
		}

	return new ControllerReturn(false, new GameController(s));
	}

bool InitalController::getDisplaySettingsChanged() {
	bool old = displayChanged;
	displayChanged = false;
	return old;	
	}

bool InitalController::getDisplayRequired() { return false; }
int InitalController::getDisplayWidth() { return -1; }
int InitalController::getDisplayHeight() { return -1; }
int InitalController::getDisplayFlags() { return -1; }
int InitalController::getDisplayRefreshRate() { return -1; }
string InitalController::getDisplayName() { return ""; }
int InitalController::getDesiredFrameRate() { return 60; }
