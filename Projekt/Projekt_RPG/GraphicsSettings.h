#ifndef GRAPHICSETTINGS_H
#define GRAPHICSETTINGS_H

class GraphicsSettings
{
public:
    GraphicsSettings();
    ~GraphicsSettings();

    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    void saveToFile(const std::string path);
    void loadFromFile(const std::string path);

};

#endif
