#include <allegro5/allegro5.h>
#include "GameController.h"
#include "SpriteContainer.h"
#include "ControllerInterface.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 600
#define WINDOW_FLAGS ALLEGRO_WINDOWED

GameController::GameController(string fname) {
	frameIndex = 0;
	needsRefresh = true;
	displayChanged = false;
	filename = fname;
	}

GameController::~GameController() {
	spriteSheet->unlink();
	}

void GameController::iniController() {
	spriteSheet = SpriteContainer::loadSpriteSheet(filename);
	}

ControllerReturn* GameController::runEventHandler(ALLEGRO_EVENT_QUEUE *queue) {
	ALLEGRO_EVENT event;

	if (needsRefresh && al_event_queue_is_empty(queue)) {
		drawFrame();
		needsRefresh = false;
		}

	al_wait_for_event(queue, &event);
		
	switch(event.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			return new ControllerReturn(true, NULL);

		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
				return new ControllerReturn(true, NULL);
			break;

		case ALLEGRO_EVENT_TIMER:
			needsRefresh = true;
			break;
		}
	return new ControllerReturn(false, NULL);
	}

void GameController::drawFrame() {
	frameIndex ++;
	al_clear_to_color(al_map_rgb(255, 255, 255));
	
	int animationCount = spriteSheet->getAnimationCount();
	
	SpriteContainer* s = SpriteContainer::loadSpriteSheet(spriteSheet->getFileName());
	s->unlink();

	int currentY = 20;
	int currentX = 30;
	for (int i = 0; i < animationCount; i++) {
		int relFrameIndex = frameIndex % spriteSheet->getAnimationLength(i);
		ALLEGRO_BITMAP* b = spriteSheet->getAnimationFrame(i, relFrameIndex);
		
		if (currentY > WINDOW_HEIGHT) {
			currentY = 20;
			currentX += 100;
			}
		
		al_draw_bitmap(b, currentX - al_get_bitmap_width(b)/2, currentY - al_get_bitmap_height(b)/2, 0);
		currentY += al_get_bitmap_height(b) + 20; 
		}

	al_flip_display();
	}

bool GameController::getDisplaySettingsChanged() {
	bool old = displayChanged;
	displayChanged = false;
	return old;
	}
bool GameController::getDisplayRequired() { return true; }
int GameController::getDisplayWidth() { return WINDOW_WIDTH; }
int GameController::getDisplayHeight() { return WINDOW_HEIGHT; }
int GameController::getDisplayFlags() { return WINDOW_FLAGS; }
int GameController::getDisplayRefreshRate() { return -1; }
string GameController::getDisplayName() { return "SpriteSheet test."; }
int GameController::getDesiredFrameRate() { return 60; }
