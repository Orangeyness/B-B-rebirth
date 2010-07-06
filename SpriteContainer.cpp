#include "SpriteContainer.h"
#include <list>
#include <allegro5/allegro5.h>

using namespace std;

list<SpriteContainer*> SpriteContainer::instanceList;

SpriteContainer::SpriteContainer(string filepath) {
	spriteSheet = al_load_bitmap(filepath.c_str());
	
	if (spriteSheet == NULL) throw "SPRITE CONTAINER: could not load sprite. (" + filepath + ").";
	
	unsigned char a, temp;
	al_unmap_rgb(al_get_pixel(spriteSheet, 0 , 0), &a, &temp, &temp);
	animationCount = a;

	frameCount = new int[animationCount];
	frames = new ALLEGRO_BITMAP**[animationCount];

	int currentY = 0;
	for (int i = 0; i < animationCount; i++) {
		unsigned char r, g, width, height;
		al_unmap_rgba(al_get_pixel(spriteSheet, 0, currentY), &r, &g, &width, &height);
		frameCount[i] = g;
		frames[i] = new ALLEGRO_BITMAP*[frameCount[i]];
		
		for (int j = 0; j < frameCount[i]; j++) {
			frames[i][j] = al_create_sub_bitmap(spriteSheet, width * j + 1, currentY, width, height);
			if (frames[i] == NULL) throw "SPRITE CONTAINER: spritesheet does not match spec. (" + filepath + ").";
			}

		currentY += height;
		}

	linkCount = 1;
	filename = filepath;
	}

SpriteContainer::~SpriteContainer() {
	SpriteContainer::instanceList.remove(this);

	for (int i = 0; i < animationCount; i++) {
		for (int j = 0; j < frameCount[i]; j++) {
			al_destroy_bitmap(frames[i][j]);
			}
		delete [] frames[i];
		}
	delete [] frames;
	delete [] frameCount;

	al_destroy_bitmap(spriteSheet);
	}

SpriteContainer* SpriteContainer::loadSpriteSheet(string filepath) {
	list<SpriteContainer*>::iterator it;

	for (it = SpriteContainer::instanceList.begin(); it != SpriteContainer::instanceList.end(); it++) {
		if ((*it)->getFileName().compare(filepath) == 0) {
			(*it)->link();
			return *it;
			}
		}

	SpriteContainer* newSpriteContainer = new SpriteContainer(filepath);
	
	SpriteContainer::instanceList.push_back(newSpriteContainer);
	return newSpriteContainer;
	}

void SpriteContainer::unlink() {
	if (--linkCount == 0) delete this;
	}

void SpriteContainer::link() {
	linkCount ++;
	}

int SpriteContainer::getAnimationCount() {
	return animationCount;
	}

int SpriteContainer::getAnimationLength(int i) {
	if (i >= animationCount) throw "SPRITECONTAINER: animation index out of bounds. (" + filename + " ).";
	return frameCount[i];
	}

ALLEGRO_BITMAP* SpriteContainer::getAnimationFrame(int i, int j) {
	if (i >= animationCount) throw "SPRITECONTAINER: animation index out of bounds. (" + filename + " ).";
	if (j >= frameCount[i]) throw  "SPRITECONTAINER: frame index out of bounds. (" + filename + " ).";

	return frames[i][j];
	}

string SpriteContainer::getFileName() {
	return filename;
	}

void SpriteContainer::destroyAll() {
	while (!instanceList.empty()) {
		if (instanceList.front() != NULL) delete instanceList.front();
		instanceList.pop_front();
		}
	}
