#ifndef GAME_H
#define GAME_H

#include"MainMenuState.h"

class Game
{
private:


	//Variables
    GraphicsSettings gfxSettings;
    StateData stateData;
	sf::RenderWindow *window;
	sf::Event event;

	sf::Clock dtime_Clock;
	float dtime;
	//State is a pointer bcs is abstract class you cant create objects of state
	std::stack<State*> state;
	std::map<std::string, int> supportedKeys;

    float gridSize;

	//Initialization
	void initVariables();
    void initGraphicsSettings();
	void initWindow();
    void initKeys();
    void initStateData();
	void initState();


public:
	//Constrtuctors/Destructors
	Game();
	virtual ~Game();

	//Functions
	void exitApp();

	void updatedtime();
	void updateEvents();
	void update();


	void render();
	void run();
};

#endif

