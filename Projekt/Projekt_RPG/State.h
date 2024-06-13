#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData 
{
public:
    StateData() {}


    float gridSize;
    sf::RenderWindow* window;
    GraphicsSettings* gfxSettings;
    std::map<std::string, int>* supportedKeys;
    std::stack<State*>* states;
};

class State
{
private:

protected:
    StateData* StataData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool exit;
	bool paused;
	float keytime;
	float keytimeMax;
    float gridSize;

	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
    sf::Vector2i mousePositionGrid;

	std::map<std::string, sf::Texture> texture;

	virtual void initKeybinds() = 0;

public:
    State(StateData* StateData);
	virtual ~State();

	const bool& getExit() const;
	const bool getKeytime();

	void endState();
	void pauseState();
	void unpauseState();


	virtual void updateMousePosition(sf::View* view = nullptr);
	virtual void updateKeytime(const float& dtime);
	virtual void updateKeybinds(const float& dtime) = 0;
	virtual void update(const float& dtime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif