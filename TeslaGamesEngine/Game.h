#pragma once

#include <vector>

#include "Object.h"
#include "Renderer.h"

/*
 * Class responsible for actual gameplay and interactions
 */
class Game
{
public:
	Game(Renderer& r);
	void AddObject(Object* obj);
	void Play();
	~Game();

private:
	int players;
	// List of all objects in this world to iterate over
	std::vector<Object*> objects;
	// Renderer to handle all drawing
	Renderer& renderer;
	// Physics engine to handle all physics calculations
	// Sound engine to handle all sounds

};

