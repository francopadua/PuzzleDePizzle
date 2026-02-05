#include "Button.h"

void Button::load(Image imageButtonUp, Image imageButtonDown, ButtonSize scale)
{
	unloadImage();
	unloadTexture();

	m_buttonUpImage = imageButtonUp;
	m_buttonDownImage = imageButtonDown;
	m_scale = scale;

	m_buttonUpTexture = LoadTextureFromImage(m_buttonUpImage);
	m_buttonDownTexture = LoadTextureFromImage(m_buttonDownImage);
}

void Button::unloadImage()
{
	if (m_buttonUpImage.data != nullptr) {
		UnloadImage(m_buttonUpImage);
		UnloadImage(m_buttonDownImage);
		m_buttonUpImage.data = nullptr;
		m_buttonDownImage.data = nullptr;
	}
}

void Button::unloadTexture()
{
	if (m_buttonUpTexture.id != 0) {
		UnloadTexture(m_buttonUpTexture);
		UnloadTexture(m_buttonDownTexture);
		//m_buttonUpTexture.id = 0;
		//m_buttonDownTexture.id = 0;
		m_buttonUpTexture = {};
		m_buttonDownTexture = {};
	}
}

Button::Button(Image imageButtonUp, Image imageButtonDown, ButtonSize scale)
	: m_buttonUpImage{ imageButtonUp }
	, m_buttonDownImage{ imageButtonDown }
	, m_scale{ scale }
{
	m_buttonUpTexture = LoadTextureFromImage(m_buttonUpImage);
	m_buttonDownTexture = LoadTextureFromImage(m_buttonDownImage);
}

Button::Button(Button&& other) noexcept
	: m_buttonUpImage{ other.m_buttonUpImage }
	, m_buttonDownImage{ other.m_buttonDownImage }
	, m_buttonUpTexture{ other.m_buttonUpTexture }
	, m_buttonDownTexture{ other.m_buttonDownTexture }
	, m_scale{ other.m_scale }
	, m_position{ other.m_position }
	, m_doneClick{ other.m_doneClick }
{
	other.m_buttonUpImage.data = nullptr;
	other.m_buttonDownImage.data = nullptr;
	other.m_buttonUpTexture = {};
	other.m_buttonDownTexture = {};
}

Button& Button::operator=(Button&& other) noexcept
{
	if (this != &other) {
		unloadImage();
		unloadTexture();
		
		// Move assign image
		m_buttonUpImage = other.m_buttonUpImage;
		m_buttonDownImage = other.m_buttonDownImage;

		// Move assign texture
		m_buttonUpTexture = other.m_buttonUpTexture;
		m_buttonDownTexture = other.m_buttonDownTexture;

		// Move assign other members
		m_scale = other.m_scale;
		m_position = other.m_position;
		m_doneClick = other.m_doneClick;

		// Then clear the past
		other.m_buttonUpImage.data = nullptr;
		other.m_buttonDownImage.data = nullptr;
		other.m_buttonUpTexture = {};
		other.m_buttonDownTexture = {};
	}
	return *this;
}

Button::~Button()
{
	std::cout << "Unloaded Button asset!" << '\n';
	unloadImage();
	unloadTexture();
}

Image Button::buttonManipulate(Image* buttonImage, float bgWidth, float bgHeight, ButtonSize buttonSize) 
{
	int Width = buttonImage->width;
	int Height = buttonImage->height;

	// Target size
	float maxWidth{};
	float maxHeight{};

	if (buttonSize == LARGE) {
		maxWidth = bgWidth / 4.0f;
		maxHeight = bgHeight / 4.0f;
	}
	else if (buttonSize == MEDIUM) {
		maxWidth = bgWidth / 7.8f;
		maxHeight = bgHeight / 7.8f;
	}
	else if (buttonSize == SMALL) {
		maxWidth = bgWidth / 9.0f;
		maxHeight = bgHeight / 9.0f;
	}

	float scaleX = maxWidth / Width;
	float scaleY = maxHeight / Height;
	float scale = std::min(scaleX, scaleY); // Keep aspect ratio

	auto newWidth = static_cast<int>(Width * scale);
	auto newHeight = static_cast<int>(Height * scale);

	ImageResize(buttonImage, newWidth, newHeight);

	return *buttonImage;
}

void Button::scaled(float bgWidth, float bgHeight, ButtonSize buttonSize)
{
	unloadTexture();

	Image buttonImageTemp = ImageCopy(m_buttonUpImage);
	m_buttonUpTexture = LoadTextureFromImage(buttonManipulate(&buttonImageTemp, bgWidth, bgHeight, buttonSize));
	UnloadImage(buttonImageTemp);
	buttonImageTemp = ImageCopy(m_buttonDownImage);
	m_buttonDownTexture = LoadTextureFromImage(buttonManipulate(&buttonImageTemp, bgWidth, bgHeight, buttonSize));
	UnloadImage(buttonImageTemp);
}

void Button::draw(Vector2 position, Vector2 mousePos)
{
	// Calculate scaled width/height once (for readability purposes)
	float scaledWidth = m_buttonUpTexture.width * m_scale;
	float scaledHeight = m_buttonUpTexture.height * m_scale;

	// Get the position
	m_position = position;
	Rectangle dest = { m_position.x, m_position.y, scaledWidth, scaledHeight };
	Rectangle source = { 0, 0, static_cast<float>(m_buttonUpTexture.width), static_cast<float>(m_buttonUpTexture.height) };

	// Check collision mouse to the button texture
	bool isHovered = CheckCollisionPointRec(mousePos, dest);

	// Change texture when the mouse button is down (no function at all)
	bool isClicked = isHovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
	Texture2D& texture = isClicked ? m_buttonDownTexture : m_buttonUpTexture;

	DrawTexturePro(texture, source, dest, { 0, 0 }, 0.0f, WHITE);

	// This works last, does not affect the button texture, only for functionality purposes 
	// returns true then button is pressed happened
	if (isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))	m_doneClick = true;
}

// Only one execution to the next functionality 
// e.g. startButton.isPressed() goes to play scene
// e.g. folderButton.isPressed opens tinyfiledialog
// Remember: changing button texture is first executed before this happens
bool Button::isPressed()
{
	if (m_doneClick) {
		m_doneClick = false;
		return true;
	}
	return false;
}