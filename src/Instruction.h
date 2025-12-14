#pragma once

#include "CTable.h"
#include "Var.h"

class Var;

struct Instruction {
	OP_CODE opCode = OP_CODE::NOP;
	std::vector<Var> parameters;
	std::wstring as_string;
	int alias;
	std::unordered_map<std::wstring, std::unordered_map<std::wstring, std::unordered_map<std::wstring, std::vector<int>>>> VRule;

	Instruction() {
		parameters.reserve(100);
	}
};
