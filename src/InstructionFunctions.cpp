#include "InstructionFunctions.h"
#include "LangLib.h"

const std::wstring PAR1 = L"Первый";
const std::wstring PAR2 = L"Второй";
const std::wstring PAR3 = L"Третий";
const std::wstring PAR4 = L"Единственный";
const std::wstring PAR5 = L"Четвертый";
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void nop(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"NOP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 0);
	}
	else {
		//Ничего
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// END
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void end(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"END";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
	}
	else {
		//Ничего
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		(*m).ret_data = getValue(&(*i).parameters[0], &(*m).heap);
		(*m).instruct_number = -1;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PAUSE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pause(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"PAUSE";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 0);
	}
	else {
		//Ничего
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		system("pause");
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SLEEP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sleepf(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"SLEEP";
		if (prevalidate) {
			checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		}
	}
	else {
		//Ничего
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		sleep(getValue(&(*i).parameters[0], &(*m).heap).toUNTG().getUInt());
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VAR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void var(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"VAR";
		int v[2]{ 1, 2 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if((int)(*i).parameters.size() == 1) {
			(*m).heap[(*i).parameters[0].toSTR().getWStr()] = Var();
		} else {
			(*m).heap[(*i).parameters[0].toSTR().getWStr()] = getValue(&(*i).parameters[1], &(*m).heap);
		}
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PRINT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"PRINT";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 1);
	}
	else {
		//Ничего
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		for (Var& v : (*i).parameters)
		{
			std::wcout << getValue(&v, &(*m).heap);
		}
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FREE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void free(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"FREE";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 1);
		for (Var& i : (*i).parameters)
		{
			requiredVar(&i, &name, i.toSTR().getWStr());
		}
	}
	else {
		for (Var& i : (*i).parameters)
		{
			checkNotExistValue(&i, m);
		}
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		for (Var& v : (*i).parameters)
		{
			(*m).heap.erase(v.getWStr());
		}
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LABEL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void label(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"LABEL";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		requiredLabel(&(*i).parameters[0], &name, LangLib::getTrans(PAR4));
		checkExistLabel(&(*i).parameters[0], m);
	}
	else {
		//Ничего
	}

	if (prego) {
		(*m).jmp_pointers[(*i).parameters[0].toSTR().getWStr()] = (*m).instruct_number + 1;
		++(*m).instruct_number;
	}
	else {
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JUMP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jump(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"JUMP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
	}
	else {
		//Ничего
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		(*m).instruct_number = (int)getLabel(&(*i).parameters[0], &(*m).jmp_pointers).toUNTG().getUInt();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INPUT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void input(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"INPUT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		std::wstring str;
		getline(std::wcin, str);
		setValue(&(*i).parameters[0], &(*m).heap) = Var(str);
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CHANGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void change(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"CHANGE";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap);
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void to(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"TO";
		int v[2]{ 2, 3 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		std::wstring type = getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr();

		if ((*i).parameters.size() == 2) {
			if (type == std::wstring_view(L"NTG") || type == std::wstring_view(L"ntg")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toNTG();
			}
			else if (type == std::wstring_view(L"UNTG") || type == std::wstring_view(L"untg")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toUNTG();
			}
			else if (type == std::wstring_view(L"DBL") || type == std::wstring_view(L"dbl")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toDBL();
			}
			else if (type == std::wstring_view(L"CHR") || type == std::wstring_view(L"chr")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toCHR();
			}
			else if (type == std::wstring_view(L"UCHR") || type == std::wstring_view(L"uchr")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toUCHR();
			}
			else if (type == std::wstring_view(L"BLN") || type == std::wstring_view(L"bln")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toBLN();
			}
			else if (type == std::wstring_view(L"STR") || type == std::wstring_view(L"str")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toSTR();
			}
			else if (type == std::wstring_view(L"ARR") || type == std::wstring_view(L"arr")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Тип данных неизвестен\n") };
			}
		}
		else if ((*i).parameters.size() == 3) {
			if (type == std::wstring_view(L"NTG") || type == std::wstring_view(L"ntg")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toNTG();
			}
			else if (type == std::wstring_view(L"UNTG") || type == std::wstring_view(L"untg")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toUNTG();
			}
			else if (type == std::wstring_view(L"DBL") || type == std::wstring_view(L"dbl")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toDBL();
			}
			else if (type == std::wstring_view(L"CHR") || type == std::wstring_view(L"chr")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toCHR();
			}
			else if (type == std::wstring_view(L"UCHR") || type == std::wstring_view(L"uchr")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toUCHR();
			}
			else if (type == std::wstring_view(L"BLN") || type == std::wstring_view(L"bln")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toBLN();
			}
			else if (type == std::wstring_view(L"STR") || type == std::wstring_view(L"str")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toSTR();
			}
			else if (type == std::wstring_view(L"ARR") || type == std::wstring_view(L"arr")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toARR();
			}
			else {
				throw std::wstring{ LangLib::getTrans(L": Тип данных неизвестен\n") };
			}
		}
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CALC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void calc(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"CALC";
		int v[2]{ 2, 4 };
		checkParameterCount(RANGE, (int)(*i).parameters.size(), &name, 0, 0, v);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));

	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		std::wstring type = getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr();
		if (type != std::wstring_view(L"+")
			&& type != std::wstring_view(L"-")
			&& type != std::wstring_view(L"*")
			&& type != std::wstring_view(L"/")
			&& type != std::wstring_view(L"%")
			&& type != std::wstring_view(L"^")
			&& type != std::wstring_view(L"INC")
			&& type != std::wstring_view(L"DEC")
			&& type != std::wstring_view(L"LOG")
			&& type != std::wstring_view(L"LN")
			&& type != std::wstring_view(L"FACT")
			&& type != std::wstring_view(L"ROOT")
			&& type != std::wstring_view(L"inc")
			&& type != std::wstring_view(L"dec")
			&& type != std::wstring_view(L"log")
			&& type != std::wstring_view(L"ln")
			&& type != std::wstring_view(L"fact")
			&& type != std::wstring_view(L"root")) {
			throw std::wstring{ type + LangLib::getTrans(L": Математическая операция неизвестна\n") };
		}
		if ((*i).parameters.size() == 2) {
			if (type == std::wstring_view(L"INC") || type == std::wstring_view(L"inc")) {
				setValue(&(*i).parameters[1], &(*m).heap) += Var(1);
			}
			else if (type == std::wstring_view(L"DEC") || type == std::wstring_view(L"dec")) {
				setValue(&(*i).parameters[1], &(*m).heap) -= Var(1);
			}
			else if (type == std::wstring_view(L"FACT") || type == std::wstring_view(L"fact")) {
				int fact = (int)(*m).heap[(*i).parameters[1].getWStr()].toUNTG().getUInt();
				unsigned long long int result = 1;
				for (int i = 1; i <= fact; ++i) {
					result *= i;
				}
				setValue(&(*i).parameters[1], &(*m).heap) = Var(result);
			}
			else if (type == std::wstring_view(L"LN") || type == std::wstring_view(L"ln")) {
				setValue(&(*i).parameters[1], &(*m).heap) = Var(log((*m).heap[(*i).parameters[1].getWStr()].toDBL().getDouble()));
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L"Математическая операция принимает 2 и больше параметров\n") };
			}
		}
		if ((*i).parameters.size() == 3) {
			if (type == std::wstring_view(L"INC") || type == std::wstring_view(L"inc")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) + Var(1);
			}
			else if (type == std::wstring_view(L"DEC") || type == std::wstring_view(L"dec")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) - Var(1);
			}
			else if (type == std::wstring_view(L"FACT") || type == std::wstring_view(L"fact")) {
				long long int fact = getValue(&(*i).parameters[2], &(*m).heap).toUNTG().getUInt();
				unsigned long long int result = 1;
				for (int i = 1; i <= fact; ++i) {
					result *= i;
				}
				setValue(&(*i).parameters[1], &(*m).heap) = Var(result);
			}
			else if (type == std::wstring_view(L"LN") || type == std::wstring_view(L"ln")) {
				setValue(&(*i).parameters[1], &(*m).heap) = Var(log(getValue(&(*i).parameters[2], &(*m).heap).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"+")) {
				setValue(&(*i).parameters[1], &(*m).heap) += getValue(&(*i).parameters[2], &(*m).heap);
			}
			else if (type == std::wstring_view(L"-")) {
				setValue(&(*i).parameters[1], &(*m).heap) -= getValue(&(*i).parameters[2], &(*m).heap);
			}
			else if (type == std::wstring_view(L"*")) {
				setValue(&(*i).parameters[1], &(*m).heap) *= getValue(&(*i).parameters[2], &(*m).heap);
			}
			else if (type == std::wstring_view(L"/")) {
				Var param = getValue(&(*i).parameters[2], &(*m).heap);
				if (param == Var(0)) {
					throw std::wstring{ (*i).parameters[2].toSTR().getWStr() + LangLib::getTrans(L"Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&(*i).parameters[1], &(*m).heap) /= getValue(&(*i).parameters[2], &(*m).heap);
			}
			else if (type == std::wstring_view(L"%")) {
				Var param = getValue(&(*i).parameters[2], &(*m).heap);
				if (param == Var(0)) {
					throw std::wstring{ (*i).parameters[2].toSTR().getWStr() + LangLib::getTrans(L"Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&(*i).parameters[1], &(*m).heap) %= getValue(&(*i).parameters[2], &(*m).heap);
			}
			else if (type == std::wstring_view(L"^")) {
				setValue(&(*i).parameters[1], &(*m).heap) = Var(pow(getValue(&(*i).parameters[1], &(*m).heap).toDBL().getDouble(), getValue(&(*i).parameters[2], &(*m).heap).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"ROOT") || type == std::wstring_view(L"root")) {
				setValue(&(*i).parameters[1], &(*m).heap) = Var(pow(getValue(&(*i).parameters[1], &(*m).heap).toDBL().getDouble(), 1.0 / getValue(&(*i).parameters[2], &(*m).heap).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"LOG") || type == std::wstring_view(L"log")) {
				setValue(&(*i).parameters[1], &(*m).heap) = log(getValue(&(*i).parameters[1], &(*m).heap).toDBL().getDouble()) / log(getValue(&(*i).parameters[2], &(*m).heap).toDBL().getDouble());

			}
		}
		if ((*i).parameters.size() == 4) {
			if (type == std::wstring_view(L"+")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) + getValue(&(*i).parameters[3], &(*m).heap);
			}
			else if (type == std::wstring_view(L"-")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) - getValue(&(*i).parameters[3], &(*m).heap);
			}
			else if (type == std::wstring_view(L"*")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) * getValue(&(*i).parameters[3], &(*m).heap);
			}
			else if (type == std::wstring_view(L"/")) {
				Var param = getValue(&(*i).parameters[3], &(*m).heap);
				if (param == Var(0)) {
					throw std::wstring{ (*i).parameters[3].toSTR().getWStr() + LangLib::getTrans(L"Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) / getValue(&(*i).parameters[3], &(*m).heap);
			}
			else if (type == std::wstring_view(L"%")) {
				Var param = getValue(&(*i).parameters[3], &(*m).heap);
				if (param == Var(0)) {
					throw std::wstring{ (*i).parameters[3].toSTR().getWStr() + LangLib::getTrans(L"Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) % getValue(&(*i).parameters[3], &(*m).heap);
			}
			else if (type == std::wstring_view(L"^")) {
				setValue(&(*i).parameters[1], &(*m).heap) = Var(pow(getValue(&(*i).parameters[2], &(*m).heap).toDBL().getDouble(), getValue(&(*i).parameters[3], &(*m).heap).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"ROOT") || type == std::wstring_view(L"root")) {
				setValue(&(*i).parameters[1], &(*m).heap) = Var(pow(getValue(&(*i).parameters[2], &(*m).heap).toDBL().getDouble(), 1.0 / getValue(&(*i).parameters[3], &(*m).heap).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"LOG") || type == std::wstring_view(L"log")) {
				setValue(&(*i).parameters[1], &(*m).heap) = log(getValue(&(*i).parameters[2], &(*m).heap).toDBL().getDouble()) / log(getValue(&(*i).parameters[3], &(*m).heap).toDBL().getDouble());

			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Математическая операция принимает до 3 параметров\n") };
			}
		}

		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NEWTEMP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void newtemp(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"NEWTEMP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		int start = (*m).tmp_count;
		(*m).tmp_count += (int)getValue(&(*i).parameters[0], &(*m).heap).toUNTG().getUInt();
		for (unsigned int it = start; it < (*m).tmp_count; ++it) {
			(*m).heap[L"$" + std::to_wstring(it)] = Var();
		}
		++(*m).instruct_number;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FORGET
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void forget(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"FORGET";
		int v[2]{ 0, 1 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if ((*i).parameters.size() == 0) {
			int start = (*m).tmp_count - 1;
			(*m).tmp_count = 0;
			for (int it = start; it >= (int)(*m).tmp_count; --it) {
				(*m).heap.erase(L"$" + std::to_wstring(it));
			}
		}
		else if ((*i).parameters.size() == 1) {
			int start = (*m).tmp_count - 1;
			(*m).tmp_count -= (int)getValue(&(*i).parameters[0], &(*m).heap).toUNTG().getUInt();
			for (int it = start; it >= (int)(*m).tmp_count; --it) {
				(*m).heap.erase(L"$" + std::to_wstring(it));
			}
		}
		++(*m).instruct_number;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TCOUNT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tcount(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"TCOUNT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = Var((*m).tmp_count);
		++(*m).instruct_number;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ISSET
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void isset(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"ISSET";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if ((*m).heap.find((*i).parameters[1].toSTR().getWStr()) != (*m).heap.end()) {
			setValue(&(*i).parameters[0], &(*m).heap) = Var(true);
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap) = Var(false);
		}
		++(*m).instruct_number;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TYPEOF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void typeofv(Machine* m, Instruction* i, bool prevalidate, bool prego) {

	if (prevalidate) {
		std::wstring name = L"TYPEOF";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).typeOf();
		++(*m).instruct_number;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void comp(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"COMP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		std::wstring type = getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr();

		if (type == std::wstring_view(L"==")) {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) == getValue(&(*i).parameters[3], &(*m).heap);
		}
		else if (type == std::wstring_view(L"!=")) {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) != getValue(&(*i).parameters[3], &(*m).heap);
		}
		else if (type == std::wstring_view(L">")) {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) > getValue(&(*i).parameters[3], &(*m).heap);
		}
		else if (type == std::wstring_view(L"<")) {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) < getValue(&(*i).parameters[3], &(*m).heap);
		}
		else if (type == std::wstring_view(L">=")) {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) >= getValue(&(*i).parameters[3], &(*m).heap);
		}
		else if (type == std::wstring_view(L"<=")) {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap) <= getValue(&(*i).parameters[3], &(*m).heap);
		}
		else {
			throw std::wstring{ type + LangLib::getTrans(L": Операция сравнения неизвестна\n") };
		}
		++(*m).instruct_number;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LOGIC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void logic(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"LOGIC";
		int v[2]{ 3, 4 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));

	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		std::wstring type = getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr();
		if (type != std::wstring_view(L"NOT")
			&& type != std::wstring_view(L"AND")
			&& type != std::wstring_view(L"OR")
			&& type != std::wstring_view(L"NAND")
			&& type != std::wstring_view(L"NOR")
			&& type != std::wstring_view(L"XOR")
			&& type != std::wstring_view(L"XNOR")
			&& type != std::wstring_view(L"not")
			&& type != std::wstring_view(L"and")
			&& type != std::wstring_view(L"or")
			&& type != std::wstring_view(L"nand")
			&& type != std::wstring_view(L"nor")
			&& type != std::wstring_view(L"xor")
			&& type != std::wstring_view(L"xnor")) {
			throw std::wstring{ type + LangLib::getTrans(L": Логическая операция неизвестна\n") };
		}
		if ((*i).parameters.size() == 3) {
			if (type == std::wstring_view(L"NOT") || type == std::wstring_view(L"not")) {
				setValue(&(*i).parameters[1], &(*m).heap) = !getValue(&(*i).parameters[2], &(*m).heap).toBLN().getBool();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Логическая операция принимет не менее 4 параметров\n") };
			}
		}
		else if ((*i).parameters.size() == 4) {
			if (type == std::wstring_view(L"AND") || type == std::wstring_view(L"and")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toBLN().getBool() && getValue(&(*i).parameters[3], &(*m).heap).toBLN().getBool();
			}
			else if (type == std::wstring_view(L"OR") || type == std::wstring_view(L"or")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toBLN().getBool() || getValue(&(*i).parameters[3], &(*m).heap).toBLN().getBool();
			}
			else if (type == std::wstring_view(L"NAND") || type == std::wstring_view(L"nand")) {
				setValue(&(*i).parameters[1], &(*m).heap) = !(getValue(&(*i).parameters[2], &(*m).heap).toBLN().getBool() && getValue(&(*i).parameters[3], &(*m).heap).toBLN().getBool());
			}
			else if (type == std::wstring_view(L"NOR") || type == std::wstring_view(L"nor")) {
				setValue(&(*i).parameters[1], &(*m).heap) = !(getValue(&(*i).parameters[2], &(*m).heap).toBLN().getBool() || getValue(&(*i).parameters[3], &(*m).heap).toBLN().getBool());
			}
			else if (type == std::wstring_view(L"XOR") || type == std::wstring_view(L"xor")) {
				setValue(&(*i).parameters[1], &(*m).heap) = !(getValue(&(*i).parameters[2], &(*m).heap).toBLN().getBool()) != !(getValue(&(*i).parameters[3], &(*m).heap).toBLN().getBool());
			}
			else if (type == std::wstring_view(L"XNOR") || type == std::wstring_view(L"xnor")) {
				setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toBLN().getBool() == getValue(&(*i).parameters[3], &(*m).heap).toBLN().getBool();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Логическая операция принимет не более 3 параметров\n") };
			}
		}
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JIF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jif(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"JIF";
		int v[2]{ 1, 2 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 1, 2, nullptr, v, 2);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		bool swtch = getValue(&(*i).parameters[0], &(*m).heap).toBLN().getBool();
		if (swtch) {
			(*m).instruct_number = (int)getLabel(&(*i).parameters[1], &(*m).jmp_pointers).toUNTG().getUInt();
		}
		else {
			++(*m).instruct_number;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JIFNOT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jifnot(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"JIFNOT";
		int v[2]{ 1, 2 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 1, 2, nullptr, v, 2);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		bool swtch = getValue(&(*i).parameters[0], &(*m).heap).toBLN().getBool();
		if (swtch) {
			++(*m).instruct_number;
		}
		else {
			(*m).instruct_number = (int)getLabel(&(*i).parameters[1], &(*m).jmp_pointers).toUNTG().getUInt();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DLABEL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void dlabel(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"DLABEL";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		requiredLabel(&(*i).parameters[0], &name, LangLib::getTrans(PAR4));
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		(*m).jmp_pointers[(*i).parameters[0].toSTR().getWStr()] = (*m).instruct_number + 1;
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SWAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void swap(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"SWAP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		Var firstval = getValue(&(*i).parameters[0], &(*m).heap);
		Var secondval = getValue(&(*i).parameters[1], &(*m).heap);
		swap(firstval, secondval);

		setValue(&(*i).parameters[0], &(*m).heap) = firstval;
		setValue(&(*i).parameters[1], &(*m).heap) = secondval;
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRAY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arr(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"ARRAY";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		int dimensions = (int)(*i).parameters.size() - 1;
		Var result = Var();
		for (int iter = dimensions; iter > 0; --iter) {
			int dimension = (int)getValue(&(*i).parameters[iter], &(*m).heap).toUNTG().getUInt();
			std::vector<Var> v;
			v.reserve(1000);
			Var arr = Var(v);
			for (int j = 0; j < dimension; ++j) {
				arr.pushb(result);
			}
			result = arr;
		}

		(*m).heap[(*i).parameters[0].toSTR().str] = result;
		++(*m).instruct_number;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VTOARR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void vtoarr(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"VTOARR";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		int size = (int)(*i).parameters.size() - 1;
		std::vector<Var> v;
		v.reserve(1000);
		Var arr = Var(v);
		for (int iter = 1; iter <= size; ++iter) {
			arr.pushb(getValue(&(*i).parameters[iter], &(*m).heap));
		}

		(*m).heap[(*i).parameters[0].toSTR().str] = arr;
		++(*m).instruct_number;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUSHB
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pushb(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"PUSHB";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));

	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap).pushb(getValue(&(*i).parameters[1], &(*m).heap));
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POPB
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void popb(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"POPB";
		int v[2]{ 1, 2 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		if ((*i).parameters.size() == 2) {
			requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
		}
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		if ((*i).parameters.size() == 2) {
			checkNotExistValue(&(*i).parameters[2], m);
		}
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if ((*i).parameters.size() == 1) {
			setValue(&(*i).parameters[0], &(*m).heap).popb();
			++(*m).instruct_number;
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap) = setValue(&(*i).parameters[1], &(*m).heap).popb();
			++(*m).instruct_number;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUSHF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pushf(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"PUSHF";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap).pushf(getValue(&(*i).parameters[1], &(*m).heap));
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POPF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void popf(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"POPF";
		int v[2]{ 1, 2 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		if ((*i).parameters.size() == 2) {
			requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
		}
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		if ((*i).parameters.size() == 2) {
			checkNotExistValue(&(*i).parameters[1], m);
		}
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if ((*i).parameters.size() == 1) {
			setValue(&(*i).parameters[0], &(*m).heap).popf();
			++(*m).instruct_number;
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap) = setValue(&(*i).parameters[1], &(*m).heap).popf();
			++(*m).instruct_number;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ERASE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void erase(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"ERASE";
		int v[2]{ 2, 3 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		if ((*i).parameters.size() == 3) {
			requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
		}
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		if ((*i).parameters.size() == 3) {
			checkNotExistValue(&(*i).parameters[1], m);
		}
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if ((*i).parameters.size() == 2) {
			setValue(&(*i).parameters[0], &(*m).heap).erase(getValue(&(*i).parameters[1], &(*m).heap));
			++(*m).instruct_number;
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap) = setValue(&(*i).parameters[1], &(*m).heap).erase(getValue(&(*i).parameters[2], &(*m).heap));
			++(*m).instruct_number;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void insrt(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"INSERT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap).insert_vector(getValue(&(*i).parameters[2], &(*m).heap), getValue(&(*i).parameters[1], &(*m).heap));
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLEAR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clear(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"CLEAR";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR4));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap).clear();
		++(*m).instruct_number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SIZE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sizearr(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"SIZE";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[0], &(*m).heap).len();
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GETVAL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getval(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"GETVAL";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 3);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		int dimensions = (int)(*i).parameters.size() - 2;
		Var* result = &((*m).heap[(*i).parameters[1].toSTR().getWStr()]);

		for (int iter = 0; iter < dimensions; ++iter) {
			Var dimension = getValue(&(*i).parameters[(long long int)iter + 2], &(*m).heap);
			Type type = (*result).type;

			if(type == ARR) {
				result = &(*result)[dimension.toUNTG().getUInt()];
			} else if( type == MAP ) {
				result = &(*result)[dimension.toSTR().getWStr()];
			} else {
				throw std::wstring{ (*result).toSTR().getWStr() + L": " + LangLib::getTrans(L"Значение не является массивом или словарем\n") };
			}
		}
		setValue(&(*i).parameters[0], &(*m).heap) = *result;
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SETVAL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setval(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"SETVAL";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 3);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {

		int dimensions = (int)(*i).parameters.size() - 2;
		
		Var* result = &setValue(&(*i).parameters[1], &(*m).heap);

		for (int iter = 0; iter < dimensions; ++iter) {
			Var dimension = getValue(&(*i).parameters[(long long int)iter + 2], &(*m).heap);
			Type type = (*result).type;
			if (iter == dimensions - 1) {
				(*result)[getValue(&(*i).parameters[(long long int)iter + 2], &(*m).heap)] = getValue(&(*i).parameters[0], &(*m).heap);
				break;
			}
			if(type == ARR) {
				result = &(*result)[dimension.toUNTG().getUInt()];
			} else if( type == MAP ) {
				result = &(*result)[dimension.toSTR().getWStr()];
			} else {
				throw std::wstring{ (*result).toSTR().getWStr() + L": " + LangLib::getTrans(L"Значение не является массивом или словарем\n") };
			}
		}
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SLICE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void slice(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"SLICE";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		Var x = getValue(&(*i).parameters[2], &(*m).heap);
		Var y = getValue(&(*i).parameters[3], &(*m).heap);

		if (x < 0) {
			throw std::wstring{ (*i).parameters[2].toSTR().getWStr() + LangLib::getTrans(L": Параметр меньше нуля\n") };
		}
		if (y < 0) {
			throw std::wstring{ (*i).parameters[3].toSTR().getWStr() + LangLib::getTrans(L": Параметр меньше нуля\n") };
		}
		if (x > (*m).heap[(*i).parameters[1].toSTR().getWStr()].csize() - 1) {
			throw std::wstring{ (*i).parameters[2].toSTR().getWStr() + L": " + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
		}
		if (x + y > (*m).heap[(*i).parameters[1].toSTR().getWStr()].csize()) {
			throw std::wstring{ (*i).parameters[3].toSTR().getWStr() + L": " + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
		}

		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().slice(x, y);
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MERGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void merge(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"MERGE";
		int v[2]{ 2, 3 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if ((*i).parameters.size() == 2) {
			Type typeA = getValue(&(*i).parameters[0], &(*m).heap).type;
			Type typeB = getValue(&(*i).parameters[1], &(*m).heap).type;
			if((typeA == MAP && typeB == MAP ) || (typeA == ARR && typeB == ARR )  ) {
				setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[0], &(*m).heap).merge(getValue(&(*i).parameters[1], &(*m).heap));
			} else if((typeA == MAP || typeA == ARR) && (typeB != MAP && typeB != ARR)) {
				setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[0], &(*m).heap).merge(getValue(&(*i).parameters[1], &(*m).heap).toARR());
			} else if((typeA != MAP && typeA != ARR) && (typeB == MAP || typeB == ARR)) {
				setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[0], &(*m).heap).toARR().merge(getValue(&(*i).parameters[1], &(*m).heap));
			} else {
				setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[0], &(*m).heap).toARR().merge(getValue(&(*i).parameters[1], &(*m).heap).toARR());
			}
		}
		else {
			Type typeA = getValue(&(*i).parameters[1], &(*m).heap).type;
			Type typeB = getValue(&(*i).parameters[2], &(*m).heap).type;
			if((typeA == MAP && typeB == MAP ) || (typeA == ARR && typeB == ARR )  ) {
				setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).merge(getValue(&(*i).parameters[2], &(*m).heap));
			} else if((typeA == MAP || typeA == ARR) && (typeB != MAP && typeB != ARR)) {
				setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).merge(getValue(&(*i).parameters[2], &(*m).heap).toARR());
			} else if((typeA != MAP && typeA != ARR) && (typeB == MAP || typeB == ARR)) {
				setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().merge(getValue(&(*i).parameters[2], &(*m).heap));
			} else {
				setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().merge(getValue(&(*i).parameters[2], &(*m).heap).toARR());
			}
		}
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SORT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sort(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"SORT";
		int v[2]{ 2, 3 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {

		if ((*i).parameters.size() == 2) {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().sortarr(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr());
		}
		else {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toARR().sortarr(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr());
		}
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNIQUE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void unique(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"UNIQUE";
		int v[2]{ 2, 3 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if ((*i).parameters.size() == 2) {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).uniq(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr());
		}
		else {
			setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).uniq(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr());
		}
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// REVERSE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void reverse(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"REVERSE";
		int v[2]{ 1, 2 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if ((*i).parameters.size() == 1) {
			setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[0], &(*m).heap).toARR().rev();
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().rev();
		}
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EQUAL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void equal(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"EQUAL";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).eq(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap));
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IEXIST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void iexist(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"IEXIST";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		if (getValue(&(*i).parameters[1], &(*m).heap).type != ARR) {
			throw std::wstring{ LangLib::getTrans(L"Инструкция IEXIST работает только с типом ARR\n") };
		}
		Var size = getValue(&(*i).parameters[1], &(*m).heap).csize();
		if (getValue(&(*i).parameters[2], &(*m).heap).toNTG() >= size || getValue(&(*i).parameters[2], &(*m).heap).toNTG() < 0) {
			setValue(&(*i).parameters[0], &(*m).heap) = Var(false);
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap) = Var(true);
		}
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void in(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"IN";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).in(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap));
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INALL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inall(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"INALL";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).inall(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap));
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rin(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"RIN";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).rin(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap));
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RINALL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rinall(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"RINALL";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).rinall(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap));
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRTOMAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arrtomap(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"ARRTOMAP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		std::vector<Var> arr;
		arr.reserve(1000);
		arr = getValue(&(*i).parameters[1], &(*m).heap).toARR().getArr();
		int size = (int)arr.size();
		std::unordered_map<std::wstring, Var> map;
		map.reserve(1000);
		for(int i = 0; i < size; ++i) {
			map.insert({std::to_wstring(i), arr[i]});
		}
		setValue(&(*i).parameters[0], &(*m).heap) = Var(map);
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTERSECT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void intersect(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"INTERSECT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toARR().intersect(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap).toARR());
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTINTERSECT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void notintersect(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"NOTINTERSECT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).toARR().notintersect(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap).toARR());
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRTOSTR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arrtostr(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"ARRTOSTR";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().arrtostr(getValue(&(*i).parameters[2], &(*m).heap));
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SUM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sum(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"SUM";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().sum();
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AVG
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void avg(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"AVG";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().avg();
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void min(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"MIN";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().min();
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAX
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void max(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"MAX";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().max();
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RANGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void range(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"RANGE";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().range();
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEDIAN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void median(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"MEDIAN";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().median();
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MODE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mode(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"MODE";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().mode();
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STDDEV
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stddev(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"STDDEV";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).toARR().stddev();
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUSH
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void push(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"PUSH";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}	

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap).push(getValue(&(*i).parameters[1], &(*m).heap), getValue(&(*i).parameters[2], &(*m).heap));
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  VTOMAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void vtomap(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"VTOMAP";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 3);
		if((int)(*i).parameters.size() % 2 == 0) {
			throw std::wstring{ LangLib::getTrans(L"Неверное число параметров! Каждый ключ должен иметь пару - значение\n") };
		} 
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkExistValue(&(*i).parameters[0], m);
	}	

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		int size = (int)(*i).parameters.size();
		std::unordered_map<std::wstring, Var> map;
		map.reserve(1000);
		for(int index = 1; index < size; index+=2) {
			map.insert({getValue(&(*i).parameters[index], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[index + 1], &(*m).heap)});
		}
		(*m).heap[(*i).parameters[0].toSTR().str] = map;
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  KEXIST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void kexist(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"KEXIST";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		checkNotExistValue(&(*i).parameters[1], m);
	}	

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap) = getValue(&(*i).parameters[1], &(*m).heap).kexist(getValue(&(*i).parameters[2], &(*m).heap));
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GETVALS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getvals(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"GETVALS";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		checkNotExistValue(&(*i).parameters[1], m);
	}	

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		const Var &map = getValue(&(*i).parameters[1], &(*m).heap);
		if(map.type != MAP) {
			std::wstring error = LangLib::getTrans(L"Инструкция используется только для следующих типов: ");
        	error += L"MAP\n";
        	throw std::wstring{ error };
		}
		std::vector<Var> vals;
		vals.reserve(1000);

		for (const auto& [key, val] : map.mp) {
			vals.emplace_back(val);
		}

		setValue(&(*i).parameters[0], &(*m).heap) = Var(vals);
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GETKEYS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getkeys(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"GETKEYS";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		checkNotExistValue(&(*i).parameters[1], m);
	}	

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		const Var &map = getValue(&(*i).parameters[1], &(*m).heap);
		if(map.type != MAP) {
			std::wstring error = LangLib::getTrans(L"Инструкция используется только для следующих типов: ");
        	error += L"MAP\n";
        	throw std::wstring{ error };
		}
		std::vector<Var> keys;
		keys.reserve(1000);

		for (const auto& [key, val] : map.mp) {
			keys.emplace_back(key);
		}

		setValue(&(*i).parameters[0], &(*m).heap) = Var(keys);
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GETINTERFORM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getinterform(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"GETINTERFORM";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
		checkNotExistValue(&(*i).parameters[1], m);
	}	

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		const Var &map = getValue(&(*i).parameters[1], &(*m).heap);
		if(map.type != MAP) {
			std::wstring error = LangLib::getTrans(L"Инструкция используется только для следующих типов: ");
        	error += L"MAP\n";
        	throw std::wstring{ error };
		}
		std::vector<Var> pairs;
		pairs.reserve(1000);

		for (const auto& [key, val] : map.mp) {
			std::vector<Var> pair;
			pair.reserve(2);
			pair.emplace_back(key);
			pair.emplace_back(val);
			pairs.emplace_back(Var(pair));
		}

		setValue(&(*i).parameters[0], &(*m).heap) = Var(pairs);
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KVINTERSECT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void kvintersect(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"KVINTERSECT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).kvintersect(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap));
		++(*m).instruct_number;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KVNOTINTERSECT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void kvnotintersect(Machine* m, Instruction* i, bool prevalidate, bool prego) {
	if (prevalidate) {
		std::wstring name = L"KVNOTINTERSECT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		++(*m).instruct_number;
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap) = getValue(&(*i).parameters[2], &(*m).heap).kvnotintersect(getValue(&(*i).parameters[0], &(*m).heap).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap));
		++(*m).instruct_number;
	}
}