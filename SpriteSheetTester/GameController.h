#ifndef _GAME_CONTROLLER_
#define _GAME_CONTROLLER_

#include <allegro5/allegro5.h>
#include "ControllerInterface.h"
#include "SpriteContainer.h"

class GameController : public ControllerInterface {

	private:
		string filename;
		SpriteContainer* spriteSheet;
		int frameIndex;
		bool needsRefresh;
		bool displayChanged;

		void drawFrame();

	public:
		GameController(string sprites);
		~GameController();
		
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
