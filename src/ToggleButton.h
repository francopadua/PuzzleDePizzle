#pragma once

#include "animation.h"
#include "config.h"
#include "Button.h"

class ToggleButton : public Button
{
public:
	// The default
	ToggleButton() = default;
	ToggleButton(Image imageButtonUp, Image imageButtonDown, Image imageButtonDisabled, ButtonSize scale);

	// The rules
	ToggleButton(const ToggleButton&) = delete;
	ToggleButton& operator=(const ToggleButton&) = delete;
	ToggleButton(ToggleButton&& other) noexcept;
	ToggleButton& operator=(ToggleButton&& other) noexcept;
	~ToggleButton();

	// Loading and Unloading
	void load(Image imageButtonUp, Image imageButtonDown, Image imageButtonDisabled, ButtonSize scale, bool withTimeDuration=false, float targetDuration=0.0f);
	void unloadImage() override;
	void unloadTexture() override;

	// Transform button
	void scaled(float bgWidth, float bgHeight, ButtonSize buttonSize) override;

	// The getters
	float getButtonWidth() const override { return m_toggled ? m_imageButtonDisabledTexture.width : Button::getButtonWidth(); }
	float getButtonHeight() const override { return m_toggled ? m_imageButtonDisabledTexture.height : Button::getButtonHeight(); }
	float getDuration() const { return m_remaining; }

	// The setters
	void resetToggle() { m_toggled = false; }
	void resetDisable() { m_disabled = false; }
	void resetRemaining() { m_remaining = m_targetDuration; }

	// The functionality
	void draw(Vector2 position, Vector2 mousePos) override;
	void update();
	void reset();
	void handleInput();
	bool isToggled();
	bool isDisabled() const { return m_disabled; }
	bool isTimeDuration() const { return m_withTimeDuration; }

private:
	Image m_imageButtonDisabled{ nullptr };
	Texture2D m_imageButtonDisabledTexture{ 0 };
	bool m_toggled{ false };
	bool m_disabled{ false };
	bool m_withTimeDuration{ false };
	float m_targetDuration{ 0.0f };
	float m_remaining{ 0.0f };
	float m_frameTime{ 0.0f };
};
