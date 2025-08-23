#pragma once

#include <random>
#include <ctime>
#include <chrono>

#include "Instruction.h"

class Machine {
public:
	bool debug;
	unsigned int tmp_count;
	int instruct_number;
	bool softerrors;
	std::unordered_map<std::wstring, Var> in_data;
	Var ret_data;
	std::vector<Instruction> instructions;
	int instruct_count = 0;

	std::unordered_map<std::wstring, Var> heap;
	std::unordered_map<std::wstring, int> jmp_pointers;

	std::unordered_map<std::wstring, Machine> sub_machines;
	std::mt19937 mersenne_twister;
	
	Machine(std::unordered_map<std::wstring, Var> in, bool dbg = false, bool soft = false);

	void prepare();

	Var go();

};