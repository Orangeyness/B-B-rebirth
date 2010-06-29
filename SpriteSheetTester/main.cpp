#include <iostream>
#include <stack>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "SpriteContainer.h"
#include "GameController.h"
#include "InitalController.h"

using namespace std;

ALLEGRO_DISPLAY* updateDisplay(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* q, ControllerInterface* currentCon) {
	if (currentCon->getDisplayRequired()) {
		int w, h, r, f;
		w = currentCon->getDisplayWidth();
		h = currentCon->getDisplayHeight();
		r = currentCon->getDisplayRefreshRate();
		f = currentCon->getDisplayFlags();
				
		if (w == -1 || h == -1) throw "UPDATE DISPLAY - Could not create display, no width or height to set";
		
		if (r != -1 && r != al_get_display_refresh_rate()) 
			al_set_new_display_refresh_rate(r);
				
		if (f != -1 && f != al_get_display_flags()) 
			al_set_new_display_flags(f);
	
		if (display != NULL) {
			al_unregister_event_source(q, al_get_display_event_source(display));
			al_destroy_display(display);
			}

		ALLEGRO_DISPLAY* newdisplay = al_create_display(w, h);
		
		if (newdisplay == NULL) {
			throw "UPDATE DISPLAY | Allegro: failed to create display";
			}
		
		al_register_event_source(q, al_get_display_event_source(newdisplay));
		
		string n = currentCon->getDisplayName();
		if (n != "") al_set_window_title(n.c_str());

		return newdisplay;
		}

	if (display != NULL) {
		al_unregister_event_source(q, al_get_display_event_source(display));
		al_destroy_display(display);
		}
	return NULL;
	}


int main(int argc, char* argv[]) {
	try {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_KEYBOARD_STATE keystate;
	ALLEGRO_EVENT_QUEUE *events;
	ALLEGRO_TIMER *updateTimer;

	if (!al_init()) {
		cout << "Allegro: failed to init" << endl; 
		return 1;
		}

	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();

	updateTimer = al_install_timer(1.0 / 60);

	events = al_create_event_queue();
	al_register_event_source(events, al_get_keyboard_event_source());
	al_register_event_source(events, al_get_timer_event_source(updateTimer));

	al_start_timer(updateTimer);

	ControllerInterface* currentCon = new InitalController();
	stack<ControllerInterface*> conStack;

	while(currentCon != NULL) {

		if (currentCon->getDisplaySettingsChanged()) display = updateDisplay(display, events, currentCon);
		if (1.0 / currentCon->getDesiredFrameRate() != al_get_timer_speed(updateTimer)) al_set_timer_speed(updateTimer, 1.0 / currentCon->getDesiredFrameRate());

		ControllerReturn* rtn = currentCon->runEventHandler(events);
		
		if (rtn->finished) {
			delete currentCon;
			if (rtn->addController != NULL) {
				currentCon = rtn->addController;
				display = updateDisplay(display, events, currentCon);
				currentCon->iniController();
				}
					else
				{
				if (!conStack.empty()) {
					currentCon = conStack.top();
					display = updateDisplay(display, events, currentCon);
					currentCon->iniController();
					conStack.pop();
					}
						else
					{
					currentCon = NULL;
					}
				}
			}
				else
			{
			if (rtn->addController != NULL) {
				conStack.push(currentCon);
				currentCon = rtn->addController;
				display = updateDisplay(display, events, currentCon);
				currentCon->iniController();
				}
			}

		delete rtn;
		}

	al_destroy_event_queue(events);
	if (display != NULL) al_destroy_display(display);
	al_uninstall_system();
	}
	catch (string str) {
		cout << "Exception occured: " << str << endl;
	}
	catch (char const* str) {
		cout << "Exception occured: " << str << endl;
	}

	return 0;
	}
