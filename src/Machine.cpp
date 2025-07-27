#include "Machine.h"
#include "InstructionFunctions.h"
#include "LangLib.h"

Machine::Machine(std::map<std::wstring, Var> in, bool dbg) {
	this->in_data = in;
	this->debug = dbg;
	this->instruct_number = 0;
	this->tmp_count = 0;
}

void Machine::prepare() {
	InstructionMap inst;
	this->instruct_count = (int)instructions.size();
	this->instruct_number = 0;
	for (unsigned int i = 0; i < this->instruct_count; ++i) {
		try {
			inst.functions[this->instructions[i].opCode](this, &instructions[i], true, true);
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
			inst.functions[this->instructions[this->instruct_number].opCode](this, &instructions[this->instruct_number], false, false);
		}
		catch (const std::wstring& error_message) {
				throw std::wstring{ LangLib::getTrans(L"Ошибка выполнения инструкции ") + std::to_wstring(this->instruct_number + 1) + L" (" + this->instructions[this->instruct_number].as_string + L"): " + error_message };
		}
	}
	return this->ret_data;
}