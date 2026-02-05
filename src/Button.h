#pragma once

#include <algorithm>
#include <iostream>
#include <raylib.h>

enum ButtonSize {
	SMALL,
	MEDIUM,
	LARGE
};

class Button {
public:
	// The default
	Button() = default;
	Button(Image imageButtonUp, Image imageButtonDown, ButtonSize scale);

	// The rules
	Button(const Button&) = delete;
	Button& operator=(const Button&) = delete;
	Button(Button&& other) noexcept;
	Button& operator=(Button&& other) noexcept;
	virtual ~Button();

	// Loading and Unloading
	void load(Image imageButtonUp, Image imageButtonDown, ButtonSize scale);
	virtual void unloadImage();
	virtual void unloadTexture();

	// Transform button
	Image buttonManipulate(Image* buttonImage, float bgWidth, float bgHeight, ButtonSize buttonSize);
	virtual void scaled(float bgWidth, float bgHeight, ButtonSize buttonSize);

	// The getters
	virtual float getButtonWidth() const { return m_buttonUpTexture.width; }
	virtual float getButtonHeight() const { return m_buttonUpTexture.height; }
	Vector2 getPos() const { return m_position; }

	// Then functionality
	virtual void draw(Vector2 position, Vector2 mousePos);
	bool isPressed();

protected:
	Image m_buttonUpImage{ nullptr };
	Image m_buttonDownImage{ nullptr };
	Texture2D m_buttonUpTexture{ 0 };
	Texture2D m_buttonDownTexture{ 0 };

	ButtonSize m_scale{ SMALL };
	Vector2 m_position{ 0 };
	bool m_doneClick{ false };
};