#ifndef _TILED_BACKGROUND_
#define _TILED_BACKGROUND_

#define TILESHEET_LOCATION "SpriteSheets/tile.png"
#define BACKGROUND_BUFFER_WIDTH 2000
#define BACkGROUND_BUFFER_HEIGHT 2000

#include <allegro5/allegro5.h>
#include <string>

#include "SpriteContainer.h"

using namespace std;

class TiledBackground {
	private: 
		SpriteContainer* tiles;

	public:
		TiledBackground(string s);
		~TiledBackground();

		void draw(int dx, int dy, int sx, int sy, int width, int height);
		
	};

#endif
