#include "stdafx.h"
#include "PlayerGUI.h"

const bool PlayerGUI::getTabsOpen() const
{
    return this->playerTabs->tabsOpen();
}

void PlayerGUI::toggleCharacterTab()
{
    this->playerTabs->toggleTab(PLAYER_TABS::CHARACTER_TAB);
}

void PlayerGUI::initTextureBar()
{
    float x = gui::p2pX(0.52083f, this->vm);
    float y = gui::p2pY(0.462962f, this->vm);

    this->Bar.setPosition(sf::Vector2f(x, y));
    this->Bar.setSize(sf::Vector2f(gui::p2pX(13.020833f, this->vm), gui::p2pY(23.148f, this->vm)));
    this->textureBar.loadFromFile("Resources/Images/Bar/Bar250.png");

    this->Bar.setTexture(&this->textureBar);
}

void PlayerGUI::initFont()
{
    this->font.loadFromFile("Fonts/alagard.ttf");
}

void PlayerGUI::initLevelBar()
{
    float width = gui::p2pX(1.5625f, this->vm);
    float height = gui::p2pY(2.777f, this->vm);
    float x = gui::p2pX(6.40625f, this->vm);
    float y = gui::p2pY(8.3333f, this->vm);


    this->levelBarBack.setSize(sf::Vector2f(width, height));
    this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 0));
    this->levelBarBack.setPosition(x, y);

    this->levelBarText.setFont(this->font);
    this->levelBarText.setOutlineColor(sf::Color::Black);
    this->levelBarText.setOutlineThickness(2.f);
    this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 90));
    this->levelBarText.setPosition(this->levelBarBack.getPosition().x + gui::p2pX(0.2604166f, this->vm), this->levelBarBack.getPosition().y - gui::p2pY(0.37037f, this->vm));
}

void PlayerGUI::initExpBar()
{
    float width = gui::p2pX(9.114584f, this->vm);
    float height = gui::p2pY(1.07f, this->vm);
    float x = gui::p2pX(3.025f, this->vm);
    float y = gui::p2pY(20.64814814f, this->vm);

    this->expBarMaxWidth = width;


    this->expBarBack.setSize(sf::Vector2f(width, height));
    this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    this->expBarBack.setPosition(x, y);

    this->expBarInner.setSize(sf::Vector2f(width, height));
    this->expBarInner.setFillColor(sf::Color(0, 0, 153, 200));
    this->expBarInner.setPosition(this->expBarBack.getPosition());

    this->expBarText.setFont(this->font);
    this->expBarText.setCharacterSize(gui::calcCharSize(this->vm, 220));
    this->expBarText.setPosition(this->expBarInner.getPosition().x + gui::p2pX(0.2604166f, this->vm), this->expBarInner.getPosition().y - gui::p2pY(0.37037f, this->vm));
}

void PlayerGUI::initHpBar()
{
    //this->hpBar = new gui::ProgressBar(
    //    3.025f, 18.4185f, 5.46875f, 0.925925f, 
    //    this->player->getAttributeComponent()->hpMax, 
    //    sf::Color(178, 34, 34, 255), 220,
    //    this->vm, &this->font);

    float width = gui::p2pX(5.468f, this->vm);
    float height = gui::p2pY(0.925f, this->vm);
    float x = gui::p2pX(3.025f, this->vm);
    float y = gui::p2pY(18.4185f, this->vm);

    this->hpBarMaxWidth = width;


    this->hpBarBack.setSize(sf::Vector2f(width, height));
    this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInner.setSize(sf::Vector2f(width, height));
    this->hpBarInner.setFillColor(sf::Color(190, 0, 30, 200));
    this->hpBarInner.setPosition(this->hpBarBack.getPosition());

    this->hpBarText.setFont(this->font);
    this->hpBarText.setCharacterSize(gui::calcCharSize(this->vm, 220));
    this->hpBarText.setPosition(this->hpBarInner.getPosition().x + gui::p2pX(0.2604166f, this->vm), this->hpBarInner.getPosition().y - gui::p2pY(0.37037f, this->vm));
}

void PlayerGUI::initPlayerTabs(sf::VideoMode vm, sf::Font& font, Player& player)
{
    this->playerTabs = new PlayerGUITabs(vm, font, player);
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
    : vm(vm)
{
    this->player = player;

    this->initTextureBar();
    this->initFont();
    this->initLevelBar();
    this->initExpBar();
    this->initHpBar();
    this->initPlayerTabs(vm, font, *player);
}

PlayerGUI::~PlayerGUI()
{
    //delete this->expBar;
    //delete this->hpBar;
    delete this->playerTabs;
}

void PlayerGUI::updateLevelBar()
{
    this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
    this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::updateExpBar()
{
    float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);


    this->expBarInner.setSize(sf::Vector2f(
        static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
        this->expBarInner.getSize().y));

    this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + "/" +
        std::to_string(this->player->getAttributeComponent()->expNext);
    this->expBarText.setString(this->expBarString);
}

void PlayerGUI::updateHpBar()
{
    //this->hpBar->update(this->player->getAttributeComponent()->hp);
    float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);


    this->hpBarInner.setSize(sf::Vector2f(
        static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
        this->hpBarInner.getSize().y));

    this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + "/" +
        std::to_string(this->player->getAttributeComponent()->hpMax);
    this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::updatePlayerTabs()
{
    this->playerTabs->update();
}

void PlayerGUI::update(const float& dtime)
{
    this->updateLevelBar();
    this->updateExpBar();
    this->updateHpBar();
    this->updatePlayerTabs();
}

void PlayerGUI::renderTexureBar(sf::RenderTarget& target)
{
    target.draw(this->Bar);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
    target.draw(this->levelBarBack);
    target.draw(this->levelBarText);
}

void PlayerGUI::renderExpBar(sf::RenderTarget& target)
{
    target.draw(this->expBarBack);
    target.draw(this->expBarInner);
    target.draw(this->expBarText);
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
    //this->hpBar->render(target);
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInner);
    target.draw(this->hpBarText);
}

void PlayerGUI::renderPlayerTabs(sf::RenderTarget& target)
{
    this->playerTabs->render(target);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
    this->renderTexureBar(target);
    this->renderLevelBar(target);
    this->renderExpBar(target);
    this->renderHpBar(target);
    this->renderPlayerTabs(target);
}
