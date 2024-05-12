/*
 * A GUI library made by me with SFML.
 *
 * This library reunites some of the commonly
 * used Graphical User Interface resources.
 *
 *  Created on: 28 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "GUI.h"

/**********************************************************************************************************
 *
 * BUTTON
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR */

// TEXT BUTTON
gui::Button::Button(float x, float y, float width, float height,
		sf::Font *font, std::string text, unsigned char_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
		short unsigned id)
{
	/**
	 * @constructor
	 *
	 * Creates a button instance WITH TEXT.
	 * -> Sets initial state to idle
	 * -> Sets button shape colors
	 * -> Sets position, size and fil color
	 * -> Sets font and text color
	 * -> Sets text string, character size and text color
	 * -> Sets text position centered in button.
	 */

	this->id = id;
	this->btn_state = BTN_IDLE;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setCharacterSize(char_size);
	this->text.setFillColor(text_idle_color);

	this->text.setPosition(
			this->shape.getPosition().x
					+ (this->shape.getGlobalBounds().width / 2.f)
					- this->text.getGlobalBounds().width / 2.f,
			this->shape.getPosition().y
					+ (this->shape.getGlobalBounds().height / 2.f)
					- this->text.getGlobalBounds().height / 2.f);

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}

// IMAGE BUTTON
gui::Button::Button(float x, float y, float width, float height,
		sf::Texture *texture, float img_w, float img_h,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
		short unsigned id)
{
	/**
	 * @constructor
	 *
	 * Creates a button instance WITH IMAGE.
	 * -> Sets initial state to idle
	 * -> Sets button shape colors
	 * -> Sets position, size and fil color
	 * -> Sets font to nullptr
	 * -> Sets image size, texture and position
	 * -> Sets image position centered in button.
	 */

	this->id = id;
	this->btn_state = BTN_IDLE;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = nullptr;

	this->image.setSize(sf::Vector2f(img_w, img_h));
	this->image.setTexture(texture);
	this->image.setPosition(
			this->shape.getPosition().x
					+ (this->shape.getSize().x / 2.f)
					- this->image.getSize().x / 2.f,
			this->shape.getPosition().y
					+ (this->shape.getSize().y / 2.f)
					- this->image.getSize().y / 2.f);

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
{

}

/* FUNCTIONS */
void gui::Button::update(sf::Vector2f mousePos)
{
	/**
	 * @return void
	 *
	 * Updates buttons states and colors.
	 * -> Sets state to idle
	 * -> Check for new state
	 * -> Set new text and shape fill colors
	 */

	this->btn_state = BTN_IDLE;

	// Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->btn_state = BTN_HOVER;

		// Active
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->btn_state = BTN_ACTIVE;
		}
	}

	// Set text and fill color based on the state
	switch (this->btn_state)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		this->text.setFillColor(this->textIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	}
}

void gui::Button::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the button into a target.
	 * -> Draws the shape into the target
	 * -> Draws the text into the center of the shape
	 */

	target.draw(this->shape);

	if (font)
		target.draw(this->text);
	else
		target.draw(this->image);
}

/* SETTERS */
void gui::Button::setId(const short unsigned id)
{
	/**
	 * @return void
	 *
	 * Sets a new id for a button.
	 */

	this->id = id;
}

void gui::Button::setText(std::string text)
{
	/**
	 * @return void
	 *
	 * Sets a new text string for a button and recenter it.
	 */

	this->text.setString(text);

	this->text.setPosition(
			this->shape.getPosition().x
					+ (this->shape.getGlobalBounds().width / 2.f)
					- this->text.getGlobalBounds().width / 2.f,
			this->shape.getPosition().y
					+ (this->shape.getGlobalBounds().height / 2.f)
					- this->text.getGlobalBounds().height / 2.f);
}

/* ACCESSORS */
const bool gui::Button::isPressed() const
{
	/**
	 * @return const bool
	 *
	 * Returns if the button is pressed.
	 * An active status implies in a pressed button.
	 */

	return this->btn_state == BTN_ACTIVE;
}

const short unsigned gui::Button::getId() const
{
	/**
	 * @return short unsigned
	 *
	 * Return a button's ID.
	 */

	return this->id;
}

const std::string gui::Button::getText() const
{
	/**
	 * @return std::string&
	 *
	 * Returns a button's text string.
	 */

	return this->text.getString();
}

/**********************************************************************************************************
 *
 * DROPDOWNLIST
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR */
gui::DropDownList::DropDownList(float x, float y, float width, float height,
		sf::Font &font, std::string elements_name[], unsigned numOfElements, short unsigned default_index) :
		font(font), showList(false), keytime(0.f), keytimeMax(20.f)
{
	/**
	 * @constructor
	 *
	 * Initializes the drop down list.
	 */

	this->selectedElement = new gui::Button(x, y, width, height,
			&this->font, elements_name[default_index], 16,
			sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
			sf::Color(120, 120, 120, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
			sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

	for (size_t i = 0; i < numOfElements; i++)
	{
		this->list.push_back(
				new gui::Button(x, y + ((i + 1) * height), width, height,
						&this->font, elements_name[i], 16,
						sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
						sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
						sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
						i));
	}
}

gui::DropDownList::~DropDownList()
{
	/**
	 * @destructor
	 *
	 * Frees all memory allocated to the drop down list.
	 */

	delete this->selectedElement;

	for (auto &it : this->list)
	{
		delete it;
	}
}

/* FUNCTIONS */
void gui::DropDownList::update(const sf::Vector2i &mousePosWindow, const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the selected element from the list and
	 * updates the whole list IF show list is true.
	 */

	this->updateKeytime(dt);

	this->selectedElement->update(sf::Vector2f(mousePosWindow));

	if (this->selectedElement->isPressed() && this->hasCompletedKeytimeCicle())
		this->showList = !this->showList;

	if (this->showList)
	{
		for (auto &button : this->list)
		{
			button->update(sf::Vector2f(mousePosWindow));

			if (button->isPressed() && this->hasCompletedKeytimeCicle())
			{
				this->selectedElement->setText(button->getText());
				this->selectedElement->setId(button->getId());

				this->showList = false;
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the selected element from the list and
	 * renders the whole list IF show list is true.
	 */

	if (this->showList)
	{
		for (auto &it : this->list)
		{
			it->render(target);
		}
	}

	this->selectedElement->render(target);
}

void gui::DropDownList::updateKeytime(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the keytime.
	 * The keytime is used for key presses filtering and
	 * debugging.
	 */

	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 100.f * dt;
	}
}

const short unsigned gui::DropDownList::getSelectedElementId() const
{
	/**
	 * @return const short unsigned
	 *
	 *
	 * Returns the selected element's id.
	 */

	return this->selectedElement->getId();
}

/* ACESSORS */
const bool gui::DropDownList::hasCompletedKeytimeCicle()
{
	/**
	 * @return const bool
	 *
	 * Returns if a keytime cicle has completed.
	 * A keytime cicle means that a defined amount of
	 * time has passed after a key was pressed.
	 * -> Restarts keytime after verification.
	 */

	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

/**********************************************************************************************************
 *
 * PAUSEMENU
 *
 *********************************************************************************************************/

/* INITIALIZERS */
void gui::PauseMenu::initButtons()
{
	/**
	 * @return void
	 *
	 * Initializes pause menu buttons.
	 */

	this->addButton("QUIT", 670.f, "Exit");
}

/* CONSTRUCTOR AND DESTRUCTOR */
gui::PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font) :
		font(font)
{
	/**
	 * @constructor
	 *
	 * Creates the pause menu.
	 * -> Sets background
	 * -> Sets container
	 * -> Sets the text
	 * -> Initialize buttons.
	 */

	// Background
	this->background.setSize(sf::Vector2f(window.getSize()));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	// Container
	this->container.setSize(sf::Vector2f(window.getSize().x / 4.f, window.getSize().y - 60.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	this->container.setPosition(sf::Vector2f(
			this->background.getSize().x / 2 - this->container.getSize().x / 2,
			this->background.getSize().y / 2 - this->container.getSize().y / 2));

	// Pause menu text
	this->pmenuText.setFont(this->font);
	this->pmenuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->pmenuText.setCharacterSize(40);
	this->pmenuText.setString("PAUSED");

	this->pmenuText.setPosition(sf::Vector2f(
			this->container.getPosition().x + this->container.getSize().x / 2
					- this->pmenuText.getGlobalBounds().width / 2,
			this->container.getPosition().y + 60.f
					- this->pmenuText.getGlobalBounds().height / 2));

	this->initButtons();
}

gui::PauseMenu::~PauseMenu()
{
	/**
	 * @destructor
	 *
	 * Free allocated memory from the pause menu
	 * and destructs is.
	 */

	for (auto &it : this->buttons)
	{
		delete it.second;
	}
}

/* FUNCIONS */
void gui::PauseMenu::update(const sf::Vector2i &mousePosWindow)
{
	/**
	 * @return void
	 *
	 * Updates the pause menu.
	 * -> Updates all buttons
	 */

	for (auto &it : this->buttons)
		it.second->update(sf::Vector2f(mousePosWindow));
}

void gui::PauseMenu::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the pause menu into a render target.
	 * -> Renders background
	 * -> Renders container
	 * -> Renders text
	 * -> Renders buttons
	 */

	target.draw(this->background);
	target.draw(this->container);
	target.draw(this->pmenuText);

	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void gui::PauseMenu::addButton(std::string key, float y, const std::string text)
{
	/**
	 * @return void
	 *
	 * Adds a button to the pause menu
	 * Parameters: key, y and text.
	 */

	float width = 250.f;

	float x = this->container.getPosition().x + this->container.getSize().x / 2 - width / 2;

	this->buttons[key] = new Button(x, y, width, 50.f,
			&this->font, text, 30,
			sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

const bool gui::PauseMenu::isButtonPressed(const std::string key)
{
	/**
	 * @return const bool&
	 *
	 * Returns if a button is pressed based on its key.
	 */

	return this->buttons[key]->isPressed();
}

/* ACCESSORS */
std::map<std::string, gui::Button*>& gui::PauseMenu::getButtons()
{
	/**
	 * @return std::map<std::string, Button*>&
	 *
	 * Returns the buttons map reference.
	 */

	return this->buttons;
}

/**********************************************************************************************************
 *
 * TEXTURE SELECTOR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR */
gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize,
		const sf::Texture *texture_sheet) :
		mousetime(0.f), mousetimeMax(10.f)
{
	/**
	 * @constructor
	 *
	 * Creates a texture selector.
	 */

	this->gridSize = gridSize;
	this->active = false;
	this->hidden = true;
	float offset = 100.f;

	// Outer box
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));

	this->bounds.setOutlineThickness(2.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	// Texture sheet
	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	// If the sheet is larger than the outer box
	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(
				sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
	}

	// If the sheet is taller than the outer box
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(
				sf::IntRect(0, 0, this->sheet.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
	}

	// Selector
	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);

	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Green);

	// Texture rect
	this->textureRect.width = (int) gridSize;
	this->textureRect.height = (int) gridSize;

	this->hideBtnIcon.loadFromFile("Assets/Images/Icons/texture_selector_icon.png");

	this->hideBtn = new gui::Button(x, y, 50.f, 50.f,
			&this->hideBtnIcon, 50.f, 50.f,
			sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));
}

gui::TextureSelector::~TextureSelector()
{
	delete this->hideBtn;
}

/* FUNCTIONS */
void gui::TextureSelector::update(const float &dt, const sf::Vector2i mousePosWindow)
{
	/**
	 * @return void
	 *
	 * Updates the texture selector if not hidden.
	 * -> Updates mousetime
	 * -> Updates the hide button
	 * -> Updates the active state
	 * -> Changes the selector position
	 * -> Sets the texture rect.
	 */

	this->updateMousetime(dt);

	this->hideBtn->update(sf::Vector2f(mousePosWindow));

	if (this->hideBtn->isPressed() && this->hasCompletedMousetimeCicle())
		this->hidden = !this->hidden;

	if (!this->hidden)
	{
		this->active = this->bounds.getGlobalBounds().contains(sf::Vector2f(mousePosWindow));

		if (this->active)
		{
			this->mousePosGrid.x = (mousePosWindow.x - this->bounds.getPosition().x) / (unsigned) this->gridSize;
			this->mousePosGrid.y = (mousePosWindow.y - this->bounds.getPosition().y) / (unsigned) this->gridSize;

			this->selector.setPosition(
					this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
					this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);

			this->textureRect.left = this->mousePosGrid.x * gridSize;
			this->textureRect.top = this->mousePosGrid.y * gridSize;
		}
	}
}

void gui::TextureSelector::updateMousetime(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the mousetime.
	 * The mousetime is used for key presses filtering and
	 * debugging.
	 */

	if (this->mousetime < this->mousetimeMax)
	{
		this->mousetime += 100.f * dt;
	}
}

void gui::TextureSelector::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the texture selector into a target if
	 * not hidden.
	 * -> Renders the hide button
	 * -> Renders bounds
	 * -> Renders sheet
	 * -> Renders selector if active.
	 */

	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
			target.draw(this->selector);
	}

	this->hideBtn->render(target);
}

/* ACCESSORS */
const bool& gui::TextureSelector::isActive() const
{
	/**
	 * @return const bool&
	 *
	 * Returns if the texture selector is active.
	 */

	return this->active;
}

const bool gui::TextureSelector::hasCompletedMousetimeCicle()
{
	/**
	 * @return const bool
	 *
	 * Returns if a mousetime cicle has completed.
	 * A mousetime cicle means that a defined amount of
	 * time has passed after a mouse button was pressed.
	 * -> Restarts mousetime after verification.
	 */

	if (this->mousetime >= this->mousetimeMax)
	{
		this->mousetime = 0.f;
		return true;
	}

	return false;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	/**
	 * @return const sf::IntRect&
	 *
	 * Returns the texture selector's texture rect.
	 * The texture rect is the texture that is under
	 * the mouse posiitons.
	 */

	return this->textureRect;
}