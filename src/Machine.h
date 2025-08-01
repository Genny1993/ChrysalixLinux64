#pragma once

#include "Instruction.h"

class Machine {
public:
	bool debug;
	unsigned int tmp_count;
	int instruct_number;

	std::unordered_map<std::wstring, Var> in_data;
	Var ret_data;
	std::vector<Instruction> instructions;
	int instruct_count = 0;

	std::unordered_map<std::wstring, Var> heap;
	std::unordered_map<std::wstring, int> jmp_pointers;

	std::unordered_map<std::wstring, Machine> sub_machines;
	
	Machine(std::unordered_map<std::wstring, Var> in, bool dbg = false);

	void prepare();

	Var go();

};