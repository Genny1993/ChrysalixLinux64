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
void validateCurrentInstruction(Machine *m, Instruction& inst, bool prevalidate, std::wstring name, std::vector<std::wstring> message) {
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
					if(param_count < inst.VRule[L"modeparams"][L"param"][L"count"][0]) {
						param_count = inst.VRule[L"modeparams"][L"param"][L"count"][0];
					}
					checkParameterCount(STRICTED, (int)inst.parameters.size(), &name, param_count);
				}
				//Вызываем проверку variants
				if(rule.find(L"variants") != rule.end()) {
					std::unordered_map<std::wstring, std::vector<int>> rule = inst.VRule[L"prevalidate"][L"checkParameterCount"];
					int array_size = rule[L"variants"][0];
					int* arr = new int[array_size];
					for(int i = 0; i < array_size; ++i) {
						int param_count = rule[L"variants"][i + 1];
						param_count -= inst.alias;
						if(param_count < inst.VRule[L"modeparams"][L"param"][L"count"][0]) {
							param_count = inst.VRule[L"modeparams"][L"param"][L"count"][0];
						}
						arr[i] = param_count;
					}
					checkParameterCount(VARIANTS,(int)inst.parameters.size(), &name, 0, 0, nullptr, arr, array_size);
					delete[] arr;
					arr = nullptr;
				}
				//Вызываем проверку minimal
				if(rule.find(L"minimal") != rule.end()) {
					std::unordered_map<std::wstring, std::vector<int>> rule = inst.VRule[L"prevalidate"][L"checkParameterCount"];
					int min_count = rule[L"minimal"][0];
					min_count -= inst.alias;
					if(min_count < inst.VRule[L"modeparams"][L"param"][L"count"][0]) {
						min_count = inst.VRule[L"modeparams"][L"param"][L"count"][0];
					}
					checkParameterCount(MINIMAL, (int)inst.parameters.size(), &name, 0, min_count);
				}
				if(rule.find(L"range") != rule.end()) {
					std::unordered_map<std::wstring, std::vector<int>> rule = inst.VRule[L"prevalidate"][L"checkParameterCount"];
					int min_count = rule[L"range"][0];
					int max_count = rule[L"range"][1];
					min_count -= inst.alias;
					if(min_count < inst.VRule[L"modeparams"][L"param"][L"count"][0]) {
						min_count = inst.VRule[L"modeparams"][L"param"][L"count"][0];
					}
					max_count -= inst.alias;
					if(max_count < inst.VRule[L"modeparams"][L"param"][L"count"][0]) {
						max_count = inst.VRule[L"modeparams"][L"param"][L"count"][0];
					}
					int v[2]{min_count, max_count};
					checkParameterCount(RANGE, (int)inst.parameters.size(), &name, 0, 0, v);
				}
			}
		}
		//Подставляем нулевой регистр в параметры исходя из оператора стрелка/шеврон
		if(inst.alias == 1) {
			int size = inst.parameters.size();
			if(inst.VRule[L"arrow"][L"param_replace"][L"number"][0] != -1) {
				if(inst.VRule[L"arrow"][L"param_replace"][L"number"][0] <= size + 1) {
					inst.parameters.insert(inst.parameters.begin() + inst.VRule[L"arrow"][L"param_replace"][L"number"][0], L"$");
				}
			}
		}
		if(inst.alias == 2) {
			int size = inst.parameters.size();
			if(inst.VRule[L"chevron"][L"param_replace"][L"number"][0] != -1) {
				if(inst.VRule[L"chevron"][L"param_replace"][L"number"][0] <= size) {
					inst.parameters.insert(inst.parameters.begin() + inst.VRule[L"chevron"][L"param_replace"][L"number"][0], L"$");
				}
			}
			if(inst.VRule[L"chevron"][L"param_replace"][L"number"][1] != -1) {
				int size = inst.parameters.size();
				if(inst.VRule[L"chevron"][L"param_replace"][L"number"][1] <= size) {
					inst.parameters.insert(inst.parameters.begin() + inst.VRule[L"chevron"][L"param_replace"][L"number"][1], L"$");
				}
			}
		}
		if(inst.VRule[L"prevalidate"].size() > 0) {
			//Если валидация, что подставленный параметр - переменная
			if(inst.VRule[L"prevalidate"].find(L"requiredVar") != inst.VRule[L"prevalidate"].end()) {
				std::unordered_map<std::wstring, std::vector<int>> rule = inst.VRule[L"prevalidate"][L"requiredVar"];
				if(rule[L"param_nums"][0] == -1) {
					unsigned start = rule[L"param_nums"][1];
					unsigned size = inst.parameters.size();
					for(unsigned i = start; i < size; ++i) {
						std::wstring mess = std::to_wstring(i);
						requiredVar(&inst.parameters[i], &name, LangLib::getTrans(mess));
					}
				} else {
					unsigned size = rule[L"param_nums"].size();
					for(unsigned i = 0; i < size; ++i) {
						std::wstring mess = L"";
						if(i < message.size()) {
							mess = message[i];
						}
						requiredVar(&inst.parameters[rule[L"param_nums"][i]], &name, LangLib::getTrans(mess));
					}
				}
			}
			if(inst.VRule[L"prevalidate"].find(L"requiredLabel") != inst.VRule[L"prevalidate"].end()) {
				std::unordered_map<std::wstring, std::vector<int>> rule = inst.VRule[L"prevalidate"][L"requiredLabel"];
				if(rule[L"param_nums"][0] == -1) {
					unsigned start = rule[L"param_nums"][1];
					unsigned size = inst.parameters.size();
					for(unsigned i = start; i < size; ++i) {
						std::wstring mess = std::to_wstring(i);
						requiredLabel(&inst.parameters[i], &name, LangLib::getTrans(mess));
					}
				} else {
					unsigned size = rule[L"param_nums"].size();
					for(unsigned i = 0; i < size; ++i) {
						std::wstring mess = L"";
						if(i < message.size()) {
							mess = message[i];
						}
						requiredLabel(&inst.parameters[rule[L"param_nums"][i]], &name, LangLib::getTrans(mess));
					}
				}
			}
			//Если указано правило проверки на существование метки
			if(inst.VRule[L"prevalidate"].find(L"checkExistLabel") != inst.VRule[L"prevalidate"].end()) {
				std::unordered_map<std::wstring, std::vector<int>> rule = inst.VRule[L"prevalidate"][L"checkExistLabel"];
				if(rule[L"param_nums"][0] == -1) {
					unsigned start = rule[L"param_nums"][1];
					unsigned size = inst.parameters.size();
					for(unsigned i = start; i < size; ++i) {
						checkExistLabel(&inst.parameters[i], m);
					}
				} else {
					unsigned size = rule[L"param_nums"].size();
					for(unsigned i = 0; i < size; ++i) {
						checkExistLabel(&inst.parameters[rule[L"param_nums"][i]], m);
					}
				}
			}
		}

	} else {
		//Если есть правила валидации
		if(inst.VRule[L"validate"].size() > 0) {
			//Если указано правило проверки на существование переменной
			if(inst.VRule[L"validate"].find(L"checkExistValue") != inst.VRule[L"validate"].end()) {
				std::unordered_map<std::wstring, std::vector<int>> rule = inst.VRule[L"validate"][L"checkExistValue"];
				if(rule[L"param_nums"][0] == -1) {
					unsigned start = rule[L"param_nums"][1];
					unsigned size = inst.parameters.size();
					for(unsigned i = start; i < size; ++i) {
						checkExistValue(&inst.parameters[i], m);
					}
				} else {
					unsigned size = rule[L"param_nums"].size();
					for(unsigned i = 0; i < size; ++i) {
						checkExistValue(&inst.parameters[rule[L"param_nums"][i]], m);
					}
				}
			}
			if(inst.VRule[L"validate"].find(L"checkNotExistValue") != inst.VRule[L"validate"].end()) {
				std::unordered_map<std::wstring, std::vector<int>> rule = inst.VRule[L"validate"][L"checkNotExistValue"];
				if(rule[L"param_nums"][0] == -1) {
					unsigned start = rule[L"param_nums"][1];
					unsigned size = inst.parameters.size();
					for(unsigned i = start; i < size; ++i) {
						checkNotExistValue(&inst.parameters[i], m);
					}
				} else {
					unsigned size = rule[L"param_nums"].size();
					for(unsigned i = 0; i < size; ++i) {
						checkNotExistValue(&inst.parameters[rule[L"param_nums"][i]], m);
					}
				}
			}
		}
	}
	return;
}