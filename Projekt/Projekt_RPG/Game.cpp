#include "stdafx.h"
#include "Game.h"
//Static functions

//Initializer functions
void Game::initVariables()
{
	this->window = nullptr;

	this->dtime = 0.f;

    this->gridSize = 100.f;
}

void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/graphics.ini");
}



void Game::initWindow()
{
	/*Create a window*/

	
	if (this->gfxSettings.fullscreen)
	{
		this->window = new sf::RenderWindow(
            this->gfxSettings.resolution, 
            this->gfxSettings.title, 
            sf::Style::Fullscreen, 
            this->gfxSettings.contextSettings);
	}
	else
	{
		this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Titlebar | sf::Style::Close, 
            this->gfxSettings.contextSettings);
	}
	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);

}

void Game::initState()
{
	this->state.push(new MainMenuState(&this->stateData));
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supproted_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	


	//Remove later its for private purpose
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
	
}

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->state;
    this->stateData.gridSize = this->gridSize;
}

//Constructos/Destructors
Game::Game()
{
    this->initVariables();
    this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
    this->initStateData();
	this->initState();
}

Game::~Game()
{
	delete this->window;
	//Remove data and pointer from the top of the stack
	while (!this->state.empty())
	{
		delete this->state.top();
		this->state.pop();
	}
}

//Functions
void Game::exitApp()
{
	std::cout << "Ending app" << "\n";
}
void Game::updatedtime()
{
	//Updates the dtime with the time which takes to update and render one frame
	this->dtime = this->dtime_Clock.restart().asSeconds();

}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed) 
		{
			this->window->close();
		}
	}
}

void Game::update()
{
	this->updateEvents();

	if (!this->state.empty())
	{
        if (this->window->hasFocus())
        {
            this->state.top()->update(this->dtime);

            if (this->state.top()->getExit())
            {
                this->state.top()->endState();
                delete this->state.top();
                this->state.pop();
            }
        }
	}
	//Exiting
	else
	{
		this->exitApp();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	//Render items
	if (!this->state.empty()) 
	{
		this->state.top()->render();
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatedtime();
		this->update();
		this->render();
	}
}

