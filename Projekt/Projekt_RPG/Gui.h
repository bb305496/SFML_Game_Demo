#ifndef GUI_H
#define GUI_H

enum button_states{BUTTON_IDLE = 0, BUTTON_HOVER, BUTTON_PRESSED};

namespace gui
{
    //Percent to pixel
    const float p2pX(const float perc, const sf::VideoMode& vm);
    const float p2pY(const float perc, const sf::VideoMode& vm);
    const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);

	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape buttonShape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		void setText(const std::string text);
		void setId(const short unsigned id);

		void update(const sf::Vector2i& mousePositionWindow);
		void render(sf::RenderTarget& target);

	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;
		sf::Font& font;
		gui::Button* activeElemnet;
		std::vector<gui::Button*> list;
		bool showList;
		
	public:
		DropDownList(float x, float y, float width, float height,
			sf::Font& font, std::string list[],
			unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		const unsigned short& getActiveElementId() const;


		const bool getKeytime();
		void updateKeytime(const float& dtime);
		void update(const sf::Vector2i& mousePositionWindow, const float& dtime);
		void render(sf::RenderTarget& target);
	};

    class TextureSelector
    {
    private:
        float keytime;
        const float keytimeMax;
        float gridSize;
        bool active;
        bool hidden;
        gui::Button* hide_btn;
        sf::RectangleShape bounds;
        sf::Sprite sheet;
        sf::RectangleShape selector;
        sf::Vector2u mousePositionGrid;
        sf::IntRect textureRect;


    public:
        TextureSelector(float x, float y, float width, float height, 
            float gridSize, const sf::Texture* texture_sheet, 
            sf::Font& font, std::string text);
        ~TextureSelector();

        const bool& getActive() const;
        const sf::IntRect& getTextureRect() const;

        const bool getKeytime();
        void updateKeytime(const float& dtime);
        void update(const sf::Vector2i& mousePositionWindow, const float& dtime);
        void render(sf::RenderTarget& target);
    };

    class ProgressBar
    {
    private:
        std::string barString;
        sf::Text text;
        float maxWidth;
        int maxValue;
        sf::RectangleShape back;
        sf::RectangleShape inner;
    public:
        ProgressBar(float x, float y, float width, float height, int max_value, 
            sf::Color inner_color, unsigned character_size,
            sf::VideoMode& vm, sf::Font* font = nullptr);
        ~ProgressBar();

        void update(const int current_value);
        void render(sf::RenderTarget& target);
    };
}

#endif