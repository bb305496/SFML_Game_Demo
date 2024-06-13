#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/alagard.ttf"))
	{
		throw("could not load font");
	}
}

void SettingsState::initKeybinds()
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

void::SettingsState::initGui()
{
    const sf::VideoMode& vm = this->StataData->gfxSettings->resolution;
    //Background
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

    //Buttons
	this->buttons["BACK"] = new gui::Button(gui::p2pX(83.3f, vm), gui::p2pY(83.3f, vm),
        gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm),
		&this->font, "Exit Settings", gui::calcCharSize(vm),
		sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(gui::p2pX(83.3f, vm), gui::p2pY(76.38f, vm),
        gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm),
		&this->font, "Apply Settings", gui::calcCharSize(vm),
		sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	
    //Modes
	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'X' + std::to_string(i.height));
	}

    //DropDownList
	this->dropdownLists["RESOLUTION"] = new gui::DropDownList(
        gui::p2pX(42.f, vm), gui::p2pY(42.f, vm),
        gui::p2pX(10.4f, vm), gui::p2pY(4.f, vm), 
        font, modes_str.data(), modes_str.size());


    //Text
    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(gui::p2pX(31.25f, vm), gui::p2pY(41.66f, vm)));
    this->optionsText.setCharacterSize(gui::calcCharSize(vm, 80));
    this->optionsText.setOutlineThickness(1.f);
    this->optionsText.setOutlineColor(sf::Color(255, 0, 0, 150));
    this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

    this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiaising \n\n");
}

void SettingsState::resetGui()
{
    auto i = this->buttons.begin();
    for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
    this->buttons.clear();

    auto j = this->dropdownLists.begin();
    for (j = this->dropdownLists.begin(); j != this->dropdownLists.end(); ++j)
    {
        delete j->second;
    }
    this->dropdownLists.clear();

    this->initGui();
}


SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}

	auto i2 = this->dropdownLists.begin();
	for (i2 = this->dropdownLists.begin(); i2 != this->dropdownLists.end(); ++i2)
	{
		delete i2->second;
	}

}


void SettingsState::updateKeybinds(const float& dtime)
{

}

void SettingsState::upadteGui(const float& dtime)
{
	//Update all buttons here
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePositionWindow);
	}


	//Quit game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
	//Apply settings
	if (this->buttons["APPLY"]->isPressed())
	{
		//Test to remove
        this->StataData->gfxSettings->resolution = this->modes[this->dropdownLists["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->StataData->gfxSettings->resolution, this->StataData->gfxSettings->title, sf::Style::Default);

        this->resetGui();
	}

	//Dropdown list
	for (auto& i : this->dropdownLists)
	{
		i.second->update(this->mousePositionWindow, dtime);
	}

}

void SettingsState::update(const float& dtime)
{
	this->updateMousePosition();
	this->updateKeybinds(dtime);

	this->upadteGui(dtime);


}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	for (auto & i : this->dropdownLists)
	{
		i.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->backgroud);

	this->renderGui(*target);

	target->draw(this->optionsText);

	//Remove later
	sf::Text mouseText;
	mouseText.setPosition(this->mousePositionView.x, this->mousePositionView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePositionView.x << " " << this->mousePositionView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
