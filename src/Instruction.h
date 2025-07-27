#pragma once

#include "CTable.h"
#include "Var.h"

struct Instruction {
	OP_CODE opCode = NOP;
	std::vector<Var> parameters;
	std::wstring as_string;
};
