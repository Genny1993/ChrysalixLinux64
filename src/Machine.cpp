#include "Machine.h"
#include "InstructionFunctions.h"
#include "LangLib.h"
#include "Helpers.h"

Machine::Machine(std::unordered_map<std::wstring, Var> in, bool dbg) {
	this->in_data = in;
	this->debug = dbg;
	this->instruct_number = 0;
	this->tmp_count = 0;
	this->instructions.reserve(10000);
	this->heap.reserve(1000);
	this->jmp_pointers.reserve(1000);
	this->sub_machines.reserve(1000);
	this->in_data.reserve(100);
	this->heap[L"$"] = Var();
	unsigned long long int timestamp = static_cast<unsigned long long int>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
	this->mersenne_twister = std::mt19937 { static_cast<std::mt19937::result_type>(timestamp) };
}

void Machine::prepare() {
	this->instruct_count = (int)instructions.size();
	this->instruct_number = 0;
	for (int i = 0; i < this->instruct_count; ++i) {
		try {
			validateInstruction(this->instructions[i], this);
		}
		catch (const std::wstring& error_message) {
			throw std::wstring{ LangLib::getTrans(L"Ошибка выполнения инструкции ") + std::to_wstring(this->instruct_number + 1) + L" (" + this->instructions[i].as_string + L"): " + error_message };
		}
	}
	this->instruct_number = 0;
}

Var Machine::go() {
	InstructionMap inst;
	while (this->instruct_number != -1) {
		if (this->instruct_number >= this->instruct_count) {
			throw std::wstring{ LangLib::getTrans(L"Ошибка после выполнения инструкции ") + std::to_wstring(this->instruct_number) + L" (" + this->instructions[(long long int)this->instruct_number - 1].as_string + LangLib::getTrans(L"): Неожиданный конец программы. Пропущена инструкция END\n") };
		}

		try {
			inst.functions[this->instructions[this->instruct_number].opCode](this, &instructions[this->instruct_number], false, false, true);
		}
		catch (const std::wstring& error_message) {
				throw std::wstring{ LangLib::getTrans(L"Ошибка выполнения инструкции ") + std::to_wstring(this->instruct_number + 1) + L" (" + this->instructions[this->instruct_number].as_string + L"): " + error_message };
		}
	}
	return this->ret_data;
}