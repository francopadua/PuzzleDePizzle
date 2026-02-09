#include "ToggleButton.h"

void ToggleButton::load(Image imageButtonUp, Image imageButtonDown, Image imageButtonDisabled, ButtonSize scale, bool withTimeDuration, float targetDuration)
{
	unloadImage();
	unloadTexture();

	Button::load(imageButtonUp, imageButtonDown, scale);
	m_imageButtonDisabled = imageButtonDisabled;
	m_imageButtonDisabledTexture = LoadTextureFromImage(m_imageButtonDisabled);

	if (withTimeDuration) {
		m_targetDuration = targetDuration;
		m_remaining = m_targetDuration;
	}
}

void ToggleButton::unloadImage()
{
	Button::unloadImage();
	if (m_imageButtonDisabled.data != nullptr) {
		UnloadImage(m_imageButtonDisabled);
		m_imageButtonDisabled.data = nullptr;
	}
}

void ToggleButton::unloadTexture()
{
	Button::unloadTexture();
	if (m_imageButtonDisabledTexture.id != 0) {
		UnloadTexture(m_imageButtonDisabledTexture);
		m_imageButtonDisabledTexture = {};
	}
}

ToggleButton::ToggleButton(Image imageButtonUp, Image imageButtonDown, Image imageButtonDisabled, ButtonSize scale)
	: Button{ imageButtonUp, imageButtonDown, scale }
	, m_imageButtonDisabled{ imageButtonDisabled }
{
	m_imageButtonDisabledTexture = LoadTextureFromImage(m_imageButtonDisabled);
}

ToggleButton::ToggleButton(ToggleButton&& other) noexcept
	: Button(std::move(other))
	, m_imageButtonDisabled{ other.m_imageButtonDisabled }
	, m_imageButtonDisabledTexture{ other.m_imageButtonDisabledTexture }
	, m_toggled{ other.m_toggled }
{
	other.m_imageButtonDisabled.data = nullptr;
	other.m_imageButtonDisabledTexture = {};
}

ToggleButton& ToggleButton::operator=(ToggleButton&& other) noexcept
{
	if (this != &other) {
		Button::operator=(std::move(other));

		unloadImage();
		unloadTexture();

		m_imageButtonDisabled = other.m_imageButtonDisabled;
		m_imageButtonDisabledTexture = other.m_imageButtonDisabledTexture;
		m_toggled = other.m_toggled;

		other.m_imageButtonDisabled.data = nullptr;
		other.m_imageButtonDisabledTexture = {};
	}

	return *this;
}

ToggleButton::~ToggleButton()
{
	std::cout << "Unloaded ToggleButton asset!" << '\n';
	unloadImage();
	unloadTexture();
}

void ToggleButton::scaled(float bgWidth, float bgHeight, ButtonSize buttonSize) 
{
	unloadTexture();

	Button::scaled(bgWidth, bgHeight, buttonSize);

	Image toggleButtonTemp = ImageCopy(m_imageButtonDisabled);
	m_imageButtonDisabledTexture = LoadTextureFromImage(buttonManipulate(&toggleButtonTemp , bgWidth, bgHeight, buttonSize));
	UnloadImage(toggleButtonTemp);
}

void ToggleButton::update()
{
	m_remaining -= Game::getFrame();
	if (m_remaining < 0.0f) {
		m_remaining = 0.0f;
		m_disabled = false;
		m_toggled = m_disabled;
	}
	else
		m_disabled = true;
}

void ToggleButton::reset()
{
	m_remaining = 0.0f;
	m_disabled = false;
	m_toggled = m_disabled;
}

void ToggleButton::handleInput()
{
	if (m_remaining == 0.0f) {
		m_toggled = false;
		m_disabled = m_toggled;
		m_remaining = m_targetDuration;
	}
}

void ToggleButton::draw(Vector2 position, Vector2 mousePos)
{
	// Calculate scaled width/height once (for readability purposes)
	float scaledWidth = m_buttonUpTexture.width * m_scale;
	float scaledHeight = m_buttonUpTexture.height * m_scale;

	// Get the position
	m_position = position;
	Rectangle dest = { m_position.x, m_position.y, scaledWidth, scaledHeight };
	Rectangle source = { 0, 0, static_cast<float>(m_buttonUpTexture.width), static_cast<float>(m_buttonUpTexture.height) };

	// Check collision mouse to the button texture
	bool isHovered{ false };

	if (!m_disabled)
		isHovered = CheckCollisionPointRec(mousePos, dest);

	// Change texture when the mouse button is down (no function at all)
	bool isClicked = isHovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
	Texture2D& texture = isClicked ? m_buttonDownTexture : m_buttonUpTexture;

	if (!m_disabled) {
		if (!m_toggled) {
			DrawTexturePro(texture, source, dest, { 0, 0 }, 0.0f, WHITE);
		}
	}

	if (m_toggled)
		DrawTexture(m_imageButtonDisabledTexture, m_position.x, m_position.y, WHITE);

	// This works last, does not affect the button texture, only for functionality purposes 
	// returns true then button is pressed happened
	if (isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		m_doneClick = true;
		m_toggled = !m_toggled;
	}
}

bool ToggleButton::isToggled()
{
	if (m_withTimeDuration) {
		m_disabled = true;
	}
	return m_toggled;
}
