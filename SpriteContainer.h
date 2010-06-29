#ifndef _SPRITE_CONTAINER_
#define _SPRITE_CONTAINER_

#include <string>
#include <list>
#include <allegro5/allegro5.h>
using namespace std;

class SpriteContainer {
	private:
		static list<SpriteContainer*> instanceList;
		int linkCount;
		ALLEGRO_BITMAP* spriteSheet; 
		int animationCount;
		int* frameCount;
		ALLEGRO_BITMAP*** frames;
		string filename;

	public:
		SpriteContainer(string filepath);
		~SpriteContainer();
		void unlink();
		void link();
		static SpriteContainer* loadSpriteSheet(string filepath);
		int getAnimationCount();
		int getAnimationLength(int i);
		ALLEGRO_BITMAP* getAnimationFrame(int i, int j);
		string getFileName();
		static void destroyAll();
	};

#endif
