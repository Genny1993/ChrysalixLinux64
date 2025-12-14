#include <iostream>

#include "Helpers.h"
#include "LangLib.h"
#include "InstructionFunctions.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkExistValue
// Проверяет существование переменной
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkExistValue(Var* val, Machine* m) {
	if (val->type == STR && val->getWStr()[0] == L'$') {
		if ((int)val->arr.size() > 0) {
			throw std::wstring{ val->getWStr() + LangLib::getTrans(L":  Переменная не должна иметь индексов доступа\n") };
		}
		if (m->heap.find(val->getWStr()) != m->heap.end()) {
			throw std::wstring{ val->getWStr() + LangLib::getTrans(L": Переменная уже определена\n") };
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkNotExistValue
// Проверяет отсутствие существования переменной
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkNotExistValue(Var* val, Machine* m) {
	if (val->type == STR && val->getWStr()[0] == L'$') {
		if (m->heap.find(val->getWStr()) == m->heap.end()) {
			throw std::wstring{ val->getWStr() + LangLib::getTrans(L": Переменная не определена\n") };
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkExistLabel
// Проверяет существование метки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkExistLabel(Var* val, Machine* m) {
	if (val->type == STR && val->getWStr()[0] == L'&') {
		if (m->jmp_pointers.find(val->getWStr()) != m->jmp_pointers.end()) {
			throw std::wstring{val->getWStr() + LangLib::getTrans(L": Метка уже определена\n") };
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkParameterCount
// Проверяет соответствие количества инструкций
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkParameterCount(unsigned char type, int count, std::wstring* name, int stricted, int min, int range[], int variant[], int size_variants) {
	switch (type) {
	case STRICTED:
		if (count != stricted) {
			throw std::wstring{ *name + LangLib::getTrans(L": Инструкция принимает ") + std::to_wstring(stricted) + LangLib::getTrans(L" параметр(а)(ов)\n")};
		}
		break;
	case MINIMAL:
		if (count < min) {
			throw std::wstring{ *name + LangLib::getTrans(L": Инструкция принимает не менее ") + std::to_wstring(min) + LangLib::getTrans(L" параметр(а)(ов)\n") };
		}
		break;
	case RANGE:
		if (count < range[0] || count > range[1]) {
			throw std::wstring{ *name + LangLib::getTrans(L": Инструкция принимает от ") + std::to_wstring(range[0]) + LangLib::getTrans(L" до ") + std::to_wstring(range[1]) + LangLib::getTrans(L" параметра(ов)\n") };
		}
		break;
	case VARIANTS: {
		bool is_variant = false;
		for (int i = 0; i < size_variants; ++i) {
			if (count == variant[i]) {
				is_variant = true;
				break;
			}
		}
		if (!is_variant) {
			std::wstring params_str = L"";
			for (int i = 0; i < size_variants; ++i) {
				params_str += std::to_wstring(variant[i]);
				if (i + 1 != size_variants) {
					params_str += L", ";
				}
			}
			throw std::wstring{ *name + LangLib::getTrans(L": Инструкция может принимать следующее число параметров: ") + params_str + LangLib::getTrans(L"\n") };
		}
	}
				 break;
	default:
		throw std::wstring{ LangLib::getTrans(L"Указан неверный вариант валидации параметров\n") };
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// requiredVar
// Проверяет то, что требуется переменная
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void requiredVar(Var* val, std::wstring* type, std::wstring num) {
	if (val->type != STR || val->getWStr()[0] != L'$') {
		throw std::wstring{ (*type) + LangLib::getTrans(L": ") + num + LangLib::getTrans(L" параметр инструкции должен быть именем переменной\n") };
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// requiredLabel
// Проверяет то, что требуется метка
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void requiredLabel(Var* val, std::wstring* type, std::wstring num) {
	if (val->type != STR || val->getWStr()[0] != L'&') {
		throw std::wstring{ (*type) + LangLib::getTrans(L": ") + num + LangLib::getTrans(L" параметр инструкции должен быть именем метки\n") };
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// validateInstruction
// Запускает валидацию инструкции и всех инструкций, вложенных в неё. 
// Используется в машине перед запуском кода.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void validateInstruction(Instruction& inst, Machine* m, bool nested) {
	InstructionMap inst_map;
	inst_map.functions[inst.opCode](m, &inst, true, true, !nested);

	int size_param = (int)inst.parameters.size();
	for(int i = 0; i < size_param; ++i) {
		if(inst.parameters[i].type == Type::INST) {
			int size_block = inst.parameters[i].instructions.size();
			for(int j = 0; j < size_block; ++j) {
				validateInstruction(inst.parameters[i].instructions[j], m, true);
			}
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// validateInstruction
// Запускает валидацию конркетной переданной инструкции по правилам валидации, хранящимся в таблице
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void validateCurrentInstruction(Machine *m, Instruction& inst, bool prevalidate, std::wstring name) {
	if(prevalidate) {
		if(inst.alias == 1) {
			name = L">" + name;
		}
		if(inst.alias == 2) {
			name = L">>" + name;
		}
		//Если есть правила превалидации
		if(inst.VRule[L"prevalidate"].size() > 0) {
			//Если указано правило валидации checkParameterCount
			if(inst.VRule[L"prevalidate"].find(L"checkParameterCount") != inst.VRule[L"prevalidate"].end()) {
				std::unordered_map<std::wstring, std::vector<int>> rule = inst.VRule[L"prevalidate"][L"checkParameterCount"];
				//Если режим проверки stricted, вызываем проверку и корректируем число параметров исходя из альясов
				if(rule.find(L"stricted") != rule.end()) {
					int param_count = rule[L"stricted"][0];
					param_count -= inst.alias;
					if(param_count < 0) {
						param_count = 0;
					}
					if(param_count + inst.VRule[L"modeparams"][L"param"][L"count"][0] <= rule[L"stricted"][0]) {
						param_count += inst.VRule[L"modeparams"][L"param"][L"count"][0];
					}
					checkParameterCount(STRICTED, inst.parameters.size(), &name, param_count);
				}
			}
		}
		if(inst.alias == 1) {
			if(inst.VRule[L"arrow"][L"param_replace"][L"number"][0] != -1) {
				inst.parameters.insert(inst.parameters.begin() + inst.VRule[L"arrow"][L"param_replace"][L"number"][0], L"$");
			}
		}
		if(inst.alias == 2) {
			if(inst.VRule[L"chevron"][L"param_replace"][L"number"][0] != -1) {
				inst.parameters.insert(inst.parameters.begin() + inst.VRule[L"chevron"][L"param_replace"][L"number"][0], L"$");
			}
			if(inst.VRule[L"chevron"][L"param_replace"][L"number"][1] != -1) {
				inst.parameters.insert(inst.parameters.begin() + inst.VRule[L"chevron"][L"param_replace"][L"number"][1], L"$");
			}
		}
	} else {
		//Если есть правила валидации
		if(inst.VRule[L"validate"].size() > 0) {

		}
	}
	return;
}