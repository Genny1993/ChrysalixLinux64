#pragma once

#include "CTable.h"
#include "Var.h"

class Var;

struct Instruction {
	OP_CODE opCode = NOP;
	std::vector<Var> parameters;
	std::wstring as_string;
	int alias;
	
	Instruction() {
		parameters.reserve(100);
	}
};
