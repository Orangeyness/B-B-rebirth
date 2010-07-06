#include "TiledBackground.h"
#include <allegro5/allegro5.h>
#include <string>
#include <iostream>

#include "SpriteContainer.h"


using namespace std;

TiledBackground::TiledBackground(string filename) {
	tiles = SpriteContainer::loadSpriteSheet(filename);
	}

TiledBackground::~TiledBackground() {
	tiles->unlink();
	}

void TiledBackground::draw(int dx, int dy, int sx, int sy, int width, int height) {
	ALLEGRO_BITMAP* tile = tiles->getAnimationFrame(0, 0);

	for (int xx = sx; xx < width; xx += al_get_bitmap_width(tile)) {
		for (int yy = sy; yy < height; yy += al_get_bitmap_height(tile)) {
			al_draw_bitmap(tile, xx, yy, 0);
			al_draw_bitmap(tile, xx - 39, yy - 20, 0);
			}
		}
	} 
