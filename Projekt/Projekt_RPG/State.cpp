#include "stdafx.h"
#include "State.h"

State::State(StateData *state_data)
{
    this->StataData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->exit = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
    this->gridSize = state_data->gridSize;
}

State::~State()
{

}

const bool& State::getExit() const
{
	return this->exit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void State::endState()
{
	this->exit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePosition(sf::View* view)
{
	this->mousePositionScreen = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);

    if(view)
        this->window->setView(*view);

	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    this->mousePositionGrid = 
        sf::Vector2i(
        static_cast<int>(this->mousePositionView.x) / static_cast<int>(this->gridSize),
        static_cast<int>(this->mousePositionView.y) / static_cast<int>(this->gridSize)
    );

    this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float& dtime)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 50.f * dtime;
}
