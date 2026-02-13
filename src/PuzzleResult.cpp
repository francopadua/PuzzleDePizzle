#include "PuzzleResult.h"

namespace PuzzleResult
{
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

