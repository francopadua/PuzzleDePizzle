#pragma once

#include <iostream>
#include <raylib.h>

class LevelResult
{
public:
	LevelResult() = default;
	LevelResult(float opacity, int slice=0);

	void setOpacity(float opacity) { m_opacity = opacity; }
	float getOpacity() const { return m_opacity; }
	void setSlice(float slice) { m_slice = slice; }
	float getSlice() const { return m_slice; }
	void solved() { m_solved = true; }
	bool isSolved() const { return m_solved; }

	void setStar(int starImage) { m_slice = starImage; }

	int getStar() const { return m_slice; }

private:
	int m_slice{ 0 };					// sliced image (e.g. if 3 where 3 is (3x3), 4 where 4 is (4x4), etc., the star image is also 3 stars, 4 stars, etc.
	float m_opacity{ 1.0f };			// star texture opacity decreases when too many hints used.
	bool m_solved{ false };
};
