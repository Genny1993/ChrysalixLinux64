#include <iostream>

#include "Helpers.h"
#include "LangLib.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkExistValue
// Проверяет существование переменной
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkExistValue(Var* val, Machine* m) {
	if ((*val).type == STR && (*val).getWStr()[0] == L'$') {
		if ((*m).heap.find((*val).getWStr()) != (*m).heap.end()) {
			throw std::wstring{ (*val).getWStr() + LangLib::getTrans(L": Переменная уже определена\n") };
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkNotExistValue
// Проверяет отсутствие существования переменной
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkNotExistValue(Var* val, Machine* m) {
	if ((*val).type == STR && (*val).getWStr()[0] == L'$') {
		if ((*m).heap.find((*val).getWStr()) == (*m).heap.end()) {
			throw std::wstring{ (*val).getWStr() + LangLib::getTrans(L": Переменная не определена\n") };
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkExistLabel
// Проверяет существование метки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkExistLabel(Var* val, Machine* m) {
	if ((*val).type == STR && (*val).getWStr()[0] == L'&') {
		if ((*m).jmp_pointers.find((*val).getWStr()) != (*m).jmp_pointers.end()) {
			throw std::wstring{(*val).getWStr() + LangLib::getTrans(L": Метка уже определена\n") };
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkParameterCount
// Проверяет соответствие количества инструкций
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkParameterCount(unsigned char type, int count, Machine* m, std::wstring* name, int stricted, int min, int range[], int variant[]) {
	switch (type) {
	case STRICTED:
		if (count != stricted) {
			throw std::wstring{ *name + LangLib::getTrans(L": Инструкция принимает ") + std::to_wstring(stricted) + LangLib::getTrans(L" параметр(а)(ов)\n")};
		}
		break;
	case MIN:
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
		int sizeofvariants = static_cast<int>(sizeof(variant));
		int size = sizeofvariants / static_cast<int>(sizeof(int));
		bool is_variant = false;
		for (int i = 0; i < size; ++i) {
			if (count == variant[i]) {
				is_variant = true;
				break;
			}
		}
		if (!is_variant) {
			std::wstring params_str = L"";
			for (int i = 0; i < size; ++i) {
				params_str += std::to_wstring(variant[i]);
				if (i + 1 != size) {
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
void requiredVar(Var* val, Machine* m, std::wstring* type, std::wstring num) {
	if ((*val).type != STR || (*val).getWStr()[0] != L'$') {
		throw std::wstring{ (*type) + LangLib::getTrans(L": ") + num + LangLib::getTrans(L" параметр инструкции должен быть именем переменной\n") };
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// requiredLabel
// Проверяет то, что требуется метка
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void requiredLabel(Var* val, Machine* m, std::wstring* type, std::wstring num) {
	if ((*val).type != STR || (*val).getWStr()[0] != L'&') {
		throw std::wstring{ (*type) + LangLib::getTrans(L": ") + num + LangLib::getTrans(L" параметр инструкции должен быть именем метки\n") };
	}
}