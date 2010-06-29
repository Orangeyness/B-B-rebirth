Beast : objs/main.o objs/SpriteContainer.o objs/GameController.o objs/InitalController.o
	g++ objs/main.o objs/SpriteContainer.o objs/GameController.o objs/InitalController.o $$(pkg-config --libs allegro-4.9) $$(pkg-config --libs allegro_primitives-4.9) $$(pkg-config --libs allegro_image-4.9) -o Beast 

objs/main.o : main.cpp
	g++ -c main.cpp -o objs/main.o

objs/SpriteContainer.o : SpriteContainer.cpp
	g++ -c SpriteContainer.cpp -o objs/SpriteContainer.o

objs/GameController.o : GameController.cpp ControllerInterface.h
	g++ -c GameController.cpp -o objs/GameController.o

objs/InitalController.o : InitalController.cpp 
	g++ -c InitalController.cpp -o objs/InitalController.o
