#pragma once

#include <map>
#include <string>
#include <vector>

#include "image_puzzle.h"
#include "Random.h"

struct ResultMessages
{
	std::vector<std::string> noHint;
	std::vector<std::string> withHint;
};

namespace PuzzleResult
{
	extern std::string resultMsg;
	extern const std::map<int, ResultMessages> resultTable;
}

std::string getResult(int gridSize);
