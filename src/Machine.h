#pragma once

#include <random>
#include <ctime>
#include <chrono>

#include "Instruction.h"

class Machine {
public:
	unsigned int tmp_count;
	unsigned long long int executed_count;
	int instruct_number;
	bool softerrors;
	bool silence;
	bool validate;
	std::unordered_map<std::wstring, Var> in_data;
	Var ret_data;
	std::vector<Instruction> instructions;
	int instruct_count = 0;

	std::unordered_map<std::wstring, Var> heap;
	std::unordered_map<std::wstring, int> jmp_pointers;

	std::unordered_map<std::wstring, Machine> sub_machines;
	std::mt19937 mersenne_twister;
	
	Machine(std::unordered_map<std::wstring, Var> in, bool soft = false, bool silence = false, bool validate = true);

	void prepare();

	Var go();

};