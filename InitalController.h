#ifndef _INITAL_CONTROLLER_
#define _INITAL_CONTROLLER_

#include "ControllerInterface.h"

class InitalController : public ControllerInterface {

	private:
		bool displayChanged;

	public:
		InitalController();
		~InitalController();
		
		void iniController();
		ControllerReturn* runEventHandler(ALLEGRO_EVENT_QUEUE *queue);

		bool getDisplaySettingsChanged();
		bool getDisplayRequired();
		int  getDisplayWidth();
		int  getDisplayHeight();
		int  getDisplayFlags();
		int  getDisplayRefreshRate();
		string getDisplayName();

		int  getDesiredFrameRate();
	};

#endif
