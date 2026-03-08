#pragma once

#include <iostream>
#include <raylib.h>
#include <string>
#include "Save.h"

class LevelResult
{
public:
	LevelResult() = default;
	LevelResult(float opacity, int slice=0);

	void setStar(int starImage, float opacity) { 
		// To check and update new best score
		// If same level is completed, update only the opacity (low/no hint used, higher opacity) 
		if (starImage == m_slice) {
			if (opacity > m_starOpacity) {
				m_starOpacity = opacity;
				m_percent = opacity * 100;
				m_newBest = "New Best!";
				return;
			}
			m_newBest = "";
		}

		// Update the star image if higher level is completed
		if (starImage > m_slice) {
			m_slice = starImage;
			m_starOpacity = opacity;
			m_percent = opacity * 100;
			m_newBest = "New High Score!";
			return;
		}
		m_newBest = "";
	}

	int getStar() const { return m_slice; }
	float getOpacity() const { return m_starOpacity; }
	float getPercent() const { return m_percent; }
	std::string getScore() const { return m_newBest; }

	//void solved() { m_solved = true; }
	//bool isSolved() const { return m_solved; }

	void applySaveData(const LevelResultData& data) {
		m_slice = data.slice;
		m_starOpacity = data.starOpacity;
		m_percent = data.percent;
		//m_solved = data.solved;
	}

private:
	int m_slice{ 0 };					// sliced image (e.g. if 3 where 3 is (3x3), 4 where 4 is (4x4), etc., the star image is also 3 stars, 4 stars, etc.
	float m_starOpacity{ 1.0f };		// star texture opacity decreases when too many hints used.
	float m_percent{ 0.0f };			// percent progress
	//bool m_solved{ false };
	std::string m_newBest{};
};
