#include "stdafx.h"
#include "GraphicsSettings.h"


GraphicsSettings::GraphicsSettings()
{
    this->title = "Default";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->verticalSync = false;
    this->frameRateLimit = 120;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

GraphicsSettings::~GraphicsSettings()
{

}

void GraphicsSettings::saveToFile(const std::string path)
{

    std::ofstream outconffile(path);


    if (outconffile.is_open()) {
        outconffile << this->title;
        outconffile << this->resolution.width << " " << this->resolution.height;
        outconffile << this->fullscreen;
        outconffile << this->frameRateLimit;
        outconffile << this->verticalSync;
        outconffile << this->contextSettings.antialiasingLevel;
    }

    outconffile.close();
}
void GraphicsSettings::loadFromFile(const std::string path)
{

    std::ifstream conffile(path);


    if (conffile.is_open()) {
        std::getline(conffile, this->title);
        conffile >> this->resolution.width >> this->resolution.height;
        conffile >> this->fullscreen;
        conffile >> this->frameRateLimit;
        conffile >> this->verticalSync;
        conffile >> this->contextSettings.antialiasingLevel;
    }

    conffile.close();
}
