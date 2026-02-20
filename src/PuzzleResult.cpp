#include "PuzzleResult.h"

namespace PuzzleResult
{
	std::string resultMsg;

	const std::map<int, ResultMessages> resultTable =
	{
		{ 3, {
			{ "Congratulations!", "Perfect!" },
			{ "Good job!", "Not bad!" }
		}},
		{ 4, {
			{ "Victory!", "Well done!" },
			{ "Nice!", "Wow!" }
		}},
		{ 5, {
			{ "Very nice!", "Great play!" },
			{ "Amazing!", "Effortful!" }
		}},
		{ 6, {
			{ "The best!", "Sick awesome!" },
			{ "Incredible!", "Wonderful!" }
		}},
		{ 7, {
			{ "Unbelievable!", "Outstanding!" },
			{ "Excellent!", "Impressive!" }
		}},
		{ 8, {
			{ "Impossible!", "Extraordinary!" },
			{ "Fantastic!", "Brilliant!" }
		}},
		{ 9, {
			{ "The master!", "Legendary!" },
			{ "Remarkable!", "Marvelous!" }
		}},
		{ 10, {
			{ "DePizzle Grandmaster!", "God Tier!" },
			{ "Finally!", "At last!" }
		}},
	};
}

// Result messages
std::string getResult(int gridSize)
{
	const ResultMessages& message_ = PuzzleResult::resultTable.at(gridSize);

	if (Puzzle::Counter::h1 > 0)	return "";		// If hint 1 is used, no message

	int getNum{ Random::get(0, 1) };

	if (Puzzle::Counter::h1 == 0 && Puzzle::Counter::h2 == 0)
		return message_.noHint[getNum];

	return message_.withHint[getNum];
}
