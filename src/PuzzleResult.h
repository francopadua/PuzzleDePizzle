#pragma once

#include <map>
#include <string>
#include <vector>

struct ResultMessages
{
	std::vector<std::string> noHint;
	std::vector<std::string> withHint;
};

namespace PuzzleResult
{
	extern const std::map<int, ResultMessages> resultTable;
}
