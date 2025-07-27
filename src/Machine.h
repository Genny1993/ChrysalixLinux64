#pragma once

#include "Instruction.h"

class Machine {
public:
	bool debug;
	unsigned int tmp_count;
	unsigned int instruct_number;

	std::map<std::wstring, Var> in_data;
	Var ret_data;
	std::vector<Instruction> instructions;
	unsigned int instruct_count = 0;

	std::map<std::wstring, Var> heap;
	std::map<std::wstring, int> jmp_pointers;

	std::map<std::wstring, Machine> sub_machines;
	
	Machine(std::map<std::wstring, Var> in, bool dbg = false);

	void prepare();

	Var go();

};