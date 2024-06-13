#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables()
{
    this->cameraSpeed = 600.f;
}

void EditorState::initEditorStateData()
{
    this->editorStateData.view = &this->view;
    this->editorStateData.font = &this->font;
    this->editorStateData.keytime = &this->keytime;
    this->editorStateData.keytimeMax = &this->keytimeMax;
    this->editorStateData.keybinds = &this->keybinds;
    this->editorStateData.mousePositionGrid = &this->mousePositionGrid;
    this->editorStateData.mousePositionScreen = &this->mousePositionScreen;
    this->editorStateData.mousePositionView = &this->mousePositionView;
    this->editorStateData.mousePositionWindow = &this->mousePositionWindow;
}

void EditorState::initView()
{
    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->StataData->gfxSettings->resolution.width),
        static_cast<float>(this->StataData->gfxSettings->resolution.height)));
    this->view.setCenter(
        static_cast<float>(this->StataData->gfxSettings->resolution.width) / 2.f,
        static_cast<float>(this->StataData->gfxSettings->resolution.height) / 2.f);
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/alagard.ttf"))
	{
		throw("could not load font");
	}
}

void EditorState::initKeybinds()
{

	std::ifstream ifs("Config/editorstate_keybinds.ini");

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


void EditorState::initPauseMenu()
{
    const sf::VideoMode& vm = this->StataData->gfxSettings->resolution;
    this->pmenu = new PauseMenu(this->StataData->gfxSettings->resolution, this->font);

    this->pmenu->addButton("EXIT", gui::p2pY(78.7037f, vm), gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm), gui::calcCharSize(vm),  "Exit to main menu");
    this->pmenu->addButton("SAVE", gui::p2pY(69.4f, vm), gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm), gui::calcCharSize(vm), "Save");
    this->pmenu->addButton("LOAD", gui::p2pY(60.185f, vm), gui::p2pX(7.8125f, vm), gui::p2pY(6.0185f, vm), gui::calcCharSize(vm), "Load map");
}

void::EditorState::initButtons()
{

}

void EditorState::initGui()
{

}

void EditorState::initTileMap()
{
    this->tileMap = new TileMap(this->StataData->gridSize, 100, 100, "Resources/Images/Tiles/Tile1ch.png");
}

void EditorState::initModes()
{
    this->modes.push_back(new DefaultEditorMode(this->StataData, this->tileMap, &this->editorStateData));
    this->modes.push_back(new EnemyEditorMode(this->StataData, this->tileMap, &this->editorStateData));

    this->activeMode = EditorModes::DEFAULT_EDITOR_MODE;
}

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
    this->initEditorStateData();
    this->initView();
	this->initFonts();
	this->initKeybinds();
    this->initPauseMenu();
	this->initButtons();
    this->initTileMap();
    this->initGui();

    this->initModes();
}

EditorState::~EditorState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}

    delete this->pmenu;

    delete this->tileMap;

    for (size_t i = 0; i < this->modes.size(); i++)
    {
        delete this->modes[i];
    }
}

void EditorState::updateKeybinds(const float& dtime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
    {
        if (!this->paused)
            this->pauseState();
        else
            this->unpauseState();
    }
}

void EditorState::updateEditorInput(const float& dtime)
{
    //Move view
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
    {
        this->view.move(0.f, -this->cameraSpeed * dtime);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
    {
        this->view.move(0.f, this->cameraSpeed * dtime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
    {
        this->view.move(-this->cameraSpeed * dtime, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
    {
        this->view.move(this->cameraSpeed * dtime, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_UP"))))
    {
        if (this->activeMode < this->modes.size() - 1)
        {
            this->activeMode++;
        }
        else
        {
            std::cout << "ERROR::EDITORSTATE::UPDATEEDITORINPUT mode up error " << "\n";
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_DOWN"))))
    {
        if (this->activeMode > 0)
        {
            this->activeMode--;
        }
        else
        {
            std::cout << "ERROR::EDITORSTATE::UPDATEEDITORINPUT mode down error " << "\n";
        }
    }
}

void EditorState::upadteButtons()
{
	//Update all buttons here
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePositionWindow);
	}
}

void EditorState::updateGui(const float& dtime)
{

}

void EditorState::updatePauseMenuButtons()
{
    if (this->pmenu->isButtonPressed("EXIT"))
        this->endState();

    if (this->pmenu->isButtonPressed("SAVE"))
        this->tileMap->saveToFile("test.slmp");

    if (this->pmenu->isButtonPressed("LOAD"))
        this->tileMap->loadFromFile("test.slmp");
}

void EditorState::updateModes(const float& dtime)
{
    this->modes[this->activeMode]->update(dtime);
}

void EditorState::update(const float& dtime)
{
	this->updateMousePosition(&this->view);
    this->updateKeytime(dtime);
	this->updateKeybinds(dtime);

    if (!this->paused)
    {
        this->upadteButtons();
        this->updateGui(dtime);
        this->updateEditorInput(dtime);
        this->updateModes(dtime);
    }
    else
    {
        this->pmenu->update(this->mousePositionWindow);
        this->updatePauseMenuButtons();
    }

}

void EditorState::renderGui(sf::RenderTarget& target)
{
    
}

void EditorState::renderModes(sf::RenderTarget& target)
{
    this->modes[this->activeMode]->render(target);
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
    target->setView(this->view);
    this->tileMap->render(*target, this->mousePositionGrid, NULL, sf::Vector2f(), true);
    this->tileMap->renderDeferred(*target);

    target->setView(this->window->getDefaultView());
    this->renderButtons(*target);

    this->renderGui(*target);

    this->renderModes(*target);

    if (this->paused)
    {
        target->setView(this->window->getDefaultView());
        this->pmenu->render(*target);
    }

}