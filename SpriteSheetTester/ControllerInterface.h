#ifndef _CONTROLLER_INTERFACE_
#define _CONTROLLER_INTERFACE_
#include <string>
#include <iostream>
#include <allegro5/allegro5.h>

using namespace std;


class ControllerReturn;

class ControllerInterface {
	public:
		virtual ~ControllerInterface() {};
		virtual void iniController() = 0;
		virtual ControllerReturn* runEventHandler(ALLEGRO_EVENT_QUEUE *queue) = 0;

		virtual bool getDisplaySettingsChanged() = 0;
		virtual bool getDisplayRequired() = 0;
		virtual int  getDisplayWidth() = 0;
		virtual int  getDisplayHeight() = 0;
		virtual int  getDisplayFlags() = 0;
		virtual int  getDisplayRefreshRate() = 0;
		virtual string getDisplayName() = 0;

		virtual int  getDesiredFrameRate() = 0;
	};

class ControllerReturn {
	public:
		ControllerReturn(bool f, ControllerInterface* CI) {
			finished = f;
			addController = CI;
			}

		bool finished;
		ControllerInterface* addController;
	};


#endif
