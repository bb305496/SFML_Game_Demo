#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables()
{

}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/alagard.ttf"))
	{
		throw("could not load font");
	}
}

void MainMenuState::initKeybinds()
{

	std::ifstream ifs("Config/mainmenu_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void::MainMenuState::initGui()
{
    const sf::VideoMode& vm = this->StataData->gfxSettings->resolution;
    //Backgroud
    this->backgroud.setSize(
        sf::Vector2f
        (
            static_cast<float>(vm.width),
            static_cast<float>(vm.height)
        )
    );

    if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg4.png"))
    {
        throw"MainMenuState failed to load background texture";
    }
    this->backgroud.setTexture(&this->backgroundTexture);
    
    //Button background
    this->btnBackground.setSize(
        sf::Vector2f(
            static_cast<float>(vm.width / 5),
            static_cast<float>(vm.height)
        )
    );
    this->btnBackground.setPosition(gui::p2pX(8.f, vm), 0.f);
    this->btnBackground.setFillColor(sf::Color(10, 10, 10, 150));



    //Buttons
	this->buttons["START_GAME"] = new gui::Button(gui::p2pX(14.f, vm), gui::p2pY(37.037f, vm), 
        gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm),
		&this->font, "Start Game", gui::calcCharSize(vm),
		sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button(gui::p2pX(14.f, vm), gui::p2pY(46.2962f, vm),
        gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm),
		&this->font, "Settings", gui::calcCharSize(vm),
		sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(gui::p2pX(14.f, vm), gui::p2pY(55.55f, vm),
        gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm),
		&this->font, "Editor", gui::calcCharSize(vm),
		sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_GAME"] = new gui::Button(gui::p2pX(14.f, vm), gui::p2pY(64.8148f, vm),
        gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm),
		&this->font, "Exit Game", gui::calcCharSize(vm),
		sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));


}

void MainMenuState::initMusic()
{
    if (!this->music.openFromFile("Resources/Music/MainMenu/MainMenuMusic.wav"))
        throw "ERROR::MAINMENUSTATE:: Could not open music file!";
    music.play();
    music.setLoop(true);
}

void MainMenuState::resetGui()
{
    auto i = this->buttons.begin();
    for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
    this->buttons.clear();

    this->initGui();
}


MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
    this->resetGui();
    this->initMusic();
}

MainMenuState::~MainMenuState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

void MainMenuState::updateKeybinds(const float& dtime)
{

}

void MainMenuState::upadteButtons()
{
	//Update all buttons here
	for (auto &i : this->buttons)
	{
		i.second->update(this->mousePositionWindow);
	}
	//Start Game
	if (this->buttons["START_GAME"]->isPressed())
	{
		this->states->push(new GameState(this->StataData));
        this->stopMusic();
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->StataData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->StataData));
	}

	//Quit game
	if (this->buttons["EXIT_GAME"]->isPressed())
	{
        this->stopMusic();
		this->endState();
	}
}

void MainMenuState::playMusic()
{
    this->music.play();
}

void MainMenuState::stopMusic()
{
    this->music.stop();
}

void MainMenuState::update(const float& dtime)
{
	this->updateMousePosition();
	this->updateKeybinds(dtime);
	this->upadteButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->backgroud);

    target->draw(this->btnBackground);

	this->renderButtons(*target);

	//Remove later
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePositionView.x, this->mousePositionView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePositionView.x << " " << this->mousePositionView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
}



