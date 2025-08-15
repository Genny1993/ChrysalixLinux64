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
void nop(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"NOP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 0);
	}
	else {
		//Ничего
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// END
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void end(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"END";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
	}
	else {
		//Ничего
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		(*m).ret_data = getValue(&(*i).parameters[0], &(*m).heap, m);
		(*m).instruct_number = -1;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SLEEP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sleepf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		sleep(getValue(&(*i).parameters[0], &(*m).heap, m).toUNTG().getUInt());
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VAR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void var(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		if((int)(*i).parameters.size() == 1) {
			(*m).heap[(*i).parameters[0].toSTR().getWStr()] = Var();
		} else {
			(*m).heap[(*i).parameters[0].toSTR().getWStr()] = getValue(&(*i).parameters[1], &(*m).heap, m);
		}
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PRINT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"PRINT";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 1);
	}
	else {
		//Ничего
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		for (Var& v : (*i).parameters)
		{
			std::wcout << getValue(&v, &(*m).heap, m);
		}
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FREE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void free(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		for (Var& v : (*i).parameters)
		{
			if(v.getWStr() == L"$") {
				throw std::wstring{ LangLib::getTrans(L"Невозможно удалить нулевой регистр '$'\n") };
			}
			(*m).heap.erase(v.getWStr());
		}
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LABEL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void label(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JUMP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jump(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"JUMP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
	}
	else {
		//Ничего
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		(*m).instruct_number = (int)getLabel(&(*i).parameters[0], &(*m).jmp_pointers).toUNTG().getUInt();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INPUT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void input(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"INPUT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		std::wstring str;
		getline(std::wcin, str);
		setValue(&(*i).parameters[0], &(*m).heap, m) = Var(str);
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CHANGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void change(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"CHANGE";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m);
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void to(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		std::wstring type = getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr();

		if ((*i).parameters.size() == 2) {
			if (type == std::wstring_view(L"NTG") || type == std::wstring_view(L"ntg")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toNTG();
			}
			else if (type == std::wstring_view(L"UNTG") || type == std::wstring_view(L"untg")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toUNTG();
			}
			else if (type == std::wstring_view(L"DBL") || type == std::wstring_view(L"dbl")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toDBL();
			}
			else if (type == std::wstring_view(L"CHR") || type == std::wstring_view(L"chr")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toCHR();
			}
			else if (type == std::wstring_view(L"UCHR") || type == std::wstring_view(L"uchr")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toUCHR();
			}
			else if (type == std::wstring_view(L"BLN") || type == std::wstring_view(L"bln")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toBLN();
			}
			else if (type == std::wstring_view(L"STR") || type == std::wstring_view(L"str")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toSTR();
			}
			else if (type == std::wstring_view(L"ARR") || type == std::wstring_view(L"arr")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Тип данных неизвестен\n") };
			}
		}
		else if ((*i).parameters.size() == 3) {
			if (type == std::wstring_view(L"NTG") || type == std::wstring_view(L"ntg")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toNTG();
			}
			else if (type == std::wstring_view(L"UNTG") || type == std::wstring_view(L"untg")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toUNTG();
			}
			else if (type == std::wstring_view(L"DBL") || type == std::wstring_view(L"dbl")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toDBL();
			}
			else if (type == std::wstring_view(L"CHR") || type == std::wstring_view(L"chr")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toCHR();
			}
			else if (type == std::wstring_view(L"UCHR") || type == std::wstring_view(L"uchr")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toUCHR();
			}
			else if (type == std::wstring_view(L"BLN") || type == std::wstring_view(L"bln")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toBLN();
			}
			else if (type == std::wstring_view(L"STR") || type == std::wstring_view(L"str")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toSTR();
			}
			else if (type == std::wstring_view(L"ARR") || type == std::wstring_view(L"arr")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toARR();
			}
			else {
				throw std::wstring{ LangLib::getTrans(L": Тип данных неизвестен\n") };
			}
		}
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CALC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void calc(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		std::wstring type = getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr();
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
				setValue(&(*i).parameters[1], &(*m).heap, m) += Var(1);
			}
			else if (type == std::wstring_view(L"DEC") || type == std::wstring_view(L"dec")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) -= Var(1);
			}
			else if (type == std::wstring_view(L"FACT") || type == std::wstring_view(L"fact")) {
				int fact = (int)(*m).heap[(*i).parameters[1].getWStr()].toUNTG().getUInt();
				unsigned long long int result = 1;
				for (int i = 1; i <= fact; ++i) {
					result *= i;
				}
				setValue(&(*i).parameters[1], &(*m).heap, m) = Var(result);
			}
			else if (type == std::wstring_view(L"LN") || type == std::wstring_view(L"ln")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = Var(log((*m).heap[(*i).parameters[1].getWStr()].toDBL().getDouble()));
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L"Математическая операция принимает 2 и больше параметров\n") };
			}
		}
		if ((*i).parameters.size() == 3) {
			if (type == std::wstring_view(L"INC") || type == std::wstring_view(L"inc")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) + Var(1);
			}
			else if (type == std::wstring_view(L"DEC") || type == std::wstring_view(L"dec")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) - Var(1);
			}
			else if (type == std::wstring_view(L"FACT") || type == std::wstring_view(L"fact")) {
				long long int fact = getValue(&(*i).parameters[2], &(*m).heap, m).toUNTG().getUInt();
				unsigned long long int result = 1;
				for (int i = 1; i <= fact; ++i) {
					result *= i;
				}
				setValue(&(*i).parameters[1], &(*m).heap, m) = Var(result);
			}
			else if (type == std::wstring_view(L"LN") || type == std::wstring_view(L"ln")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = Var(log(getValue(&(*i).parameters[2], &(*m).heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"+")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) += getValue(&(*i).parameters[2], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"-")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) -= getValue(&(*i).parameters[2], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"*")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) *= getValue(&(*i).parameters[2], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"/")) {
				Var param = getValue(&(*i).parameters[2], &(*m).heap, m);
				if (param == Var(0)) {
					throw std::wstring{ (*i).parameters[2].toSTR().getWStr() + LangLib::getTrans(L"Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&(*i).parameters[1], &(*m).heap, m) /= getValue(&(*i).parameters[2], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"%")) {
				Var param = getValue(&(*i).parameters[2], &(*m).heap, m);
				if (param == Var(0)) {
					throw std::wstring{ (*i).parameters[2].toSTR().getWStr() + LangLib::getTrans(L"Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&(*i).parameters[1], &(*m).heap, m) %= getValue(&(*i).parameters[2], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"^")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = Var(pow(getValue(&(*i).parameters[1], &(*m).heap, m).toDBL().getDouble(), getValue(&(*i).parameters[2], &(*m).heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"ROOT") || type == std::wstring_view(L"root")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = Var(pow(getValue(&(*i).parameters[1], &(*m).heap, m).toDBL().getDouble(), 1.0 / getValue(&(*i).parameters[2], &(*m).heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"LOG") || type == std::wstring_view(L"log")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = log(getValue(&(*i).parameters[1], &(*m).heap, m).toDBL().getDouble()) / log(getValue(&(*i).parameters[2], &(*m).heap, m).toDBL().getDouble());

			}
		}
		if ((*i).parameters.size() == 4) {
			if (type == std::wstring_view(L"+")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) + getValue(&(*i).parameters[3], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"-")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) - getValue(&(*i).parameters[3], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"*")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) * getValue(&(*i).parameters[3], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"/")) {
				Var param = getValue(&(*i).parameters[3], &(*m).heap, m);
				if (param == Var(0)) {
					throw std::wstring{ (*i).parameters[3].toSTR().getWStr() + LangLib::getTrans(L"Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) / getValue(&(*i).parameters[3], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"%")) {
				Var param = getValue(&(*i).parameters[3], &(*m).heap, m);
				if (param == Var(0)) {
					throw std::wstring{ (*i).parameters[3].toSTR().getWStr() + LangLib::getTrans(L"Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) % getValue(&(*i).parameters[3], &(*m).heap, m);
			}
			else if (type == std::wstring_view(L"^")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = Var(pow(getValue(&(*i).parameters[2], &(*m).heap, m).toDBL().getDouble(), getValue(&(*i).parameters[3], &(*m).heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"ROOT") || type == std::wstring_view(L"root")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = Var(pow(getValue(&(*i).parameters[2], &(*m).heap, m).toDBL().getDouble(), 1.0 / getValue(&(*i).parameters[3], &(*m).heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"LOG") || type == std::wstring_view(L"log")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = log(getValue(&(*i).parameters[2], &(*m).heap, m).toDBL().getDouble()) / log(getValue(&(*i).parameters[3], &(*m).heap, m).toDBL().getDouble());

			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Математическая операция принимает до 3 параметров\n") };
			}
		}
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NEWTEMP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void newtemp(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"NEWTEMP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		int start = (*m).tmp_count;
		(*m).tmp_count += (int)getValue(&(*i).parameters[0], &(*m).heap, m).toUNTG().getUInt();
		for (unsigned int it = start; it < (*m).tmp_count; ++it) {
			(*m).heap[L"$" + std::to_wstring(it)] = Var();
		}
		if(iterate){++(*m).instruct_number;}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FORGET
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void forget(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"FORGET";
		int v[2]{ 0, 1 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 0, 0, nullptr, v, 2);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
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
			(*m).tmp_count -= (int)getValue(&(*i).parameters[0], &(*m).heap, m).toUNTG().getUInt();
			for (int it = start; it >= (int)(*m).tmp_count; --it) {
				(*m).heap.erase(L"$" + std::to_wstring(it));
			}
		}
		if(iterate){++(*m).instruct_number;}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TCOUNT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tcount(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"TCOUNT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = Var((*m).tmp_count);
		if(iterate){++(*m).instruct_number;}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ISSET
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void isset(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		try{
			Var temp = getValue(&(*i).parameters[1], &(*m).heap, m);
			setValue(&(*i).parameters[0], &(*m).heap, m) = Var(true);
		}
		catch(const std::wstring& error_message) {
			setValue(&(*i).parameters[0], &(*m).heap, m) = Var(false);
		}
		if(iterate){++(*m).instruct_number;}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TYPEOF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void typeofv(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {

	if (prevalidate) {
		std::wstring name = L"TYPEOF";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).typeOf();
		if(iterate){++(*m).instruct_number;}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void comp(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"COMP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		std::wstring type = getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr();

		if (type == std::wstring_view(L"==")) {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) == getValue(&(*i).parameters[3], &(*m).heap, m);
		} 
		else if(type == std::wstring_view(L"===")) {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).eq(L"strict", getValue(&(*i).parameters[3], &(*m).heap, m));
		}
		else if (type == std::wstring_view(L"!=")) {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) != getValue(&(*i).parameters[3], &(*m).heap, m);
		}
		else if (type == std::wstring_view(L">")) {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) > getValue(&(*i).parameters[3], &(*m).heap, m);
		}
		else if (type == std::wstring_view(L"<")) {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) < getValue(&(*i).parameters[3], &(*m).heap, m);
		}
		else if (type == std::wstring_view(L">=")) {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) >= getValue(&(*i).parameters[3], &(*m).heap, m);
		}
		else if (type == std::wstring_view(L"<=")) {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m) <= getValue(&(*i).parameters[3], &(*m).heap, m);
		}
		else {
			throw std::wstring{ type + LangLib::getTrans(L": Операция сравнения неизвестна\n") };
		}
		if(iterate){++(*m).instruct_number;}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LOGIC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void logic(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		std::wstring type = getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr();
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
				setValue(&(*i).parameters[1], &(*m).heap, m) = !getValue(&(*i).parameters[2], &(*m).heap, m).toBLN().getBool();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Логическая операция принимет не менее 4 параметров\n") };
			}
		}
		else if ((*i).parameters.size() == 4) {
			if (type == std::wstring_view(L"AND") || type == std::wstring_view(L"and")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toBLN().getBool() && getValue(&(*i).parameters[3], &(*m).heap, m).toBLN().getBool();
			}
			else if (type == std::wstring_view(L"OR") || type == std::wstring_view(L"or")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toBLN().getBool() || getValue(&(*i).parameters[3], &(*m).heap, m).toBLN().getBool();
			}
			else if (type == std::wstring_view(L"NAND") || type == std::wstring_view(L"nand")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = !(getValue(&(*i).parameters[2], &(*m).heap, m).toBLN().getBool() && getValue(&(*i).parameters[3], &(*m).heap, m).toBLN().getBool());
			}
			else if (type == std::wstring_view(L"NOR") || type == std::wstring_view(L"nor")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = !(getValue(&(*i).parameters[2], &(*m).heap, m).toBLN().getBool() || getValue(&(*i).parameters[3], &(*m).heap, m).toBLN().getBool());
			}
			else if (type == std::wstring_view(L"XOR") || type == std::wstring_view(L"xor")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = !(getValue(&(*i).parameters[2], &(*m).heap, m).toBLN().getBool()) != !(getValue(&(*i).parameters[3], &(*m).heap, m).toBLN().getBool());
			}
			else if (type == std::wstring_view(L"XNOR") || type == std::wstring_view(L"xnor")) {
				setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toBLN().getBool() == getValue(&(*i).parameters[3], &(*m).heap, m).toBLN().getBool();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Логическая операция принимет не более 3 параметров\n") };
			}
		}
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JIF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jif(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"JIF";
		int v[2]{ 1, 2 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 1, 2, nullptr, v, 2);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		bool swtch = getValue(&(*i).parameters[0], &(*m).heap, m).toBLN().getBool();
		if (swtch) {
			(*m).instruct_number = (int)getLabel(&(*i).parameters[1], &(*m).jmp_pointers).toUNTG().getUInt();
		}
		else {
			if(iterate){++(*m).instruct_number;}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JIFNOT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jifnot(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"JIFNOT";
		int v[2]{ 1, 2 };
		checkParameterCount(VARIANTS, (int)(*i).parameters.size(), &name, 1, 2, nullptr, v, 2);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		bool swtch = getValue(&(*i).parameters[0], &(*m).heap, m).toBLN().getBool();
		if (swtch) {
			if(iterate){++(*m).instruct_number;}
		}
		else {
			(*m).instruct_number = (int)getLabel(&(*i).parameters[1], &(*m).jmp_pointers).toUNTG().getUInt();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DLABEL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void dlabel(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"DLABEL";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		requiredLabel(&(*i).parameters[0], &name, LangLib::getTrans(PAR4));
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		(*m).jmp_pointers[(*i).parameters[0].toSTR().getWStr()] = (*m).instruct_number + 1;
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SWAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void swap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		Var firstval = getValue(&(*i).parameters[0], &(*m).heap, m);
		Var secondval = getValue(&(*i).parameters[1], &(*m).heap, m);
		swap(firstval, secondval);

		setValue(&(*i).parameters[0], &(*m).heap, m) = firstval;
		setValue(&(*i).parameters[1], &(*m).heap, m) = secondval;
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRAY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"ARRAY";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		int dimensions = (int)(*i).parameters.size() - 1;
		Var result = Var();
		for (int iter = dimensions; iter > 0; --iter) {
			int dimension = (int)getValue(&(*i).parameters[iter], &(*m).heap, m).toUNTG().getUInt();
			std::vector<Var> v;
			v.reserve(1000);
			Var arr = Var(v);
			for (int j = 0; j < dimension; ++j) {
				arr.pushb(result);
			}
			result = arr;
		}
		if((*m).heap.find((*i).parameters[0].toSTR().str)== (*m).heap.end()) {
			(*m).heap[(*i).parameters[0].toSTR().str] = result;
		} else {
			setValue(&(*i).parameters[0], &(*m).heap, m) = result;
		}
		if(iterate){++(*m).instruct_number;}
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VTOARR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void vtoarr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"VTOARR";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {

	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		int size = (int)(*i).parameters.size() - 1;
		std::vector<Var> v;
		v.reserve(1000);
		Var arr = Var(v);
		for (int iter = 1; iter <= size; ++iter) {
			arr.pushb(getValue(&(*i).parameters[iter], &(*m).heap, m));
		}

		if((*m).heap.find((*i).parameters[0].toSTR().str)== (*m).heap.end()) {
			(*m).heap[(*i).parameters[0].toSTR().str] = arr;
		} else {
			setValue(&(*i).parameters[0], &(*m).heap, m) = arr;
		}

		if(iterate){++(*m).instruct_number;}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUSHB
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pushb(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"PUSHB";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));

	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m).pushb(getValue(&(*i).parameters[1], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POPB
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void popb(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		if ((*i).parameters.size() == 1) {
			setValue(&(*i).parameters[0], &(*m).heap, m).popb();
			if(iterate){++(*m).instruct_number;}
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap, m) = setValue(&(*i).parameters[1], &(*m).heap, m).popb();
			if(iterate){++(*m).instruct_number;}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUSHF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pushf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"PUSHF";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m).pushf(getValue(&(*i).parameters[1], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POPF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void popf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		if ((*i).parameters.size() == 1) {
			setValue(&(*i).parameters[0], &(*m).heap, m).popf();
			if(iterate){++(*m).instruct_number;}
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap, m) = setValue(&(*i).parameters[1], &(*m).heap, m).popf();
			if(iterate){++(*m).instruct_number;}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ERASE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void erase(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		if ((*i).parameters.size() == 2) {
			setValue(&(*i).parameters[0], &(*m).heap, m).erase(getValue(&(*i).parameters[1], &(*m).heap, m));
			if(iterate){++(*m).instruct_number;}
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap, m) = setValue(&(*i).parameters[1], &(*m).heap, m).erase(getValue(&(*i).parameters[2], &(*m).heap, m));
			if(iterate){++(*m).instruct_number;}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void insrt(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"INSERT";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m).insert_vector(getValue(&(*i).parameters[2], &(*m).heap, m), getValue(&(*i).parameters[1], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLEAR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clear(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"CLEAR";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 1);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR4));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m).clear();
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SIZE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sizearr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).len();
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SLICE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void slice(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		Var x = getValue(&(*i).parameters[2], &(*m).heap, m);
		Var y = getValue(&(*i).parameters[3], &(*m).heap, m);

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

		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().slice(x, y);
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MERGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void merge(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		if ((*i).parameters.size() == 2) {
			Type typeA = getValue(&(*i).parameters[0], &(*m).heap, m).type;
			Type typeB = getValue(&(*i).parameters[1], &(*m).heap, m).type;
			if((typeA == MAP && typeB == MAP ) || (typeA == ARR && typeB == ARR )  ) {
				setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[0], &(*m).heap, m).merge(getValue(&(*i).parameters[1], &(*m).heap, m));
			} else if((typeA == MAP || typeA == ARR) && (typeB != MAP && typeB != ARR)) {
				setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[0], &(*m).heap, m).merge(getValue(&(*i).parameters[1], &(*m).heap, m).toARR());
			} else if((typeA != MAP && typeA != ARR) && (typeB == MAP || typeB == ARR)) {
				setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[0], &(*m).heap, m).toARR().merge(getValue(&(*i).parameters[1], &(*m).heap, m));
			} else {
				setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[0], &(*m).heap, m).toARR().merge(getValue(&(*i).parameters[1], &(*m).heap, m).toARR());
			}
		}
		else {
			Type typeA = getValue(&(*i).parameters[1], &(*m).heap, m).type;
			Type typeB = getValue(&(*i).parameters[2], &(*m).heap, m).type;
			if((typeA == MAP && typeB == MAP ) || (typeA == ARR && typeB == ARR )  ) {
				setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).merge(getValue(&(*i).parameters[2], &(*m).heap, m));
			} else if((typeA == MAP || typeA == ARR) && (typeB != MAP && typeB != ARR)) {
				setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).merge(getValue(&(*i).parameters[2], &(*m).heap, m).toARR());
			} else if((typeA != MAP && typeA != ARR) && (typeB == MAP || typeB == ARR)) {
				setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().merge(getValue(&(*i).parameters[2], &(*m).heap, m));
			} else {
				setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().merge(getValue(&(*i).parameters[2], &(*m).heap, m).toARR());
			}
		}
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SORT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sort(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {

		if ((*i).parameters.size() == 2) {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().sortarr(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr());
		}
		else {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toARR().sortarr(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr());
		}
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNIQUE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void unique(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		if ((*i).parameters.size() == 2) {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).uniq(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr());
		}
		else {
			setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).uniq(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr());
		}
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// REVERSE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void reverse(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
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
		if(iterate){++(*m).instruct_number;}
	}
	else {
		if ((*i).parameters.size() == 1) {
			setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[0], &(*m).heap, m).toARR().rev();
		}
		else {
			setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().rev();
		}
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EQUAL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void equal(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"EQUAL";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).eq(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void in(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"IN";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).in(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INALL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inall(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"INALL";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).inall(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rin(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"RIN";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).rin(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RINALL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rinall(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"RINALL";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).rinall(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRTOMAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arrtomap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"ARRTOMAP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		std::vector<Var> arr;
		arr.reserve(1000);
		arr = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().getArr();
		int size = (int)arr.size();
		std::unordered_map<std::wstring, Var> map;
		map.reserve(1000);
		for(int i = 0; i < size; ++i) {
			map.insert({std::to_wstring(i), arr[i]});
		}
		
		setValue(&(*i).parameters[0], &(*m).heap, m) = Var(map);

		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"INTERS";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toARR().intersect(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap, m).toARR());
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTINTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void notinters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"NOTINTERS";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).toARR().notintersect(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap, m).toARR());
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRTOSTR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arrtostr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"ARRTOSTR";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().arrtostr(getValue(&(*i).parameters[2], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SUM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sum(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"SUM";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().sum();
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AVG
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void avg(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"AVG";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().avg();
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void min(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"MIN";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().min();
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAX
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void max(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"MAX";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().max();
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RANGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void range(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"RANGE";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().range();
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEDIAN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void median(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"MEDIAN";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().median();
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MODE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mode(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"MODE";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().mode();
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STDDEV
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stddev(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"STDDEV";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m) = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().stddev();
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUSH
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void push(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"PUSH";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}	

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[0], &(*m).heap, m).push(getValue(&(*i).parameters[1], &(*m).heap, m), getValue(&(*i).parameters[2], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  VTOMAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void vtomap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"VTOMAP";
		checkParameterCount(MINIMAL, (int)(*i).parameters.size(), &name, 0, 3);
		if((int)(*i).parameters.size() % 2 == 0) {
			throw std::wstring{ LangLib::getTrans(L"Неверное число параметров! Каждый ключ должен иметь пару - значение\n") };
		} 
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
	}	

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		int size = (int)(*i).parameters.size();
		std::unordered_map<std::wstring, Var> map;
		map.reserve(1000);
		for(int index = 1; index < size; index+=2) {
			map.insert({getValue(&(*i).parameters[index], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[index + 1], &(*m).heap, m)});
		}

		if((*m).heap.find((*i).parameters[0].toSTR().str)== (*m).heap.end()) {
			(*m).heap[(*i).parameters[0].toSTR().str] = map;
		} else {
			setValue(&(*i).parameters[0], &(*m).heap, m) = map;
		}

		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GETVALS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getvals(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"GETVALS";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}	

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		const Var &map = getValue(&(*i).parameters[1], &(*m).heap, m);
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

		setValue(&(*i).parameters[0], &(*m).heap, m) = Var(vals);
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GETKEYS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getkeys(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"GETKEYS";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}	

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		const Var &map = getValue(&(*i).parameters[1], &(*m).heap, m);
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

		setValue(&(*i).parameters[0], &(*m).heap, m) = Var(keys);
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GETINTERF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getinterf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"GETINTERF";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
		requiredVar(&(*i).parameters[0], &name, LangLib::getTrans(PAR1));
	}
	else {
		checkNotExistValue(&(*i).parameters[0], m);
	}	

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		const Var &map = getValue(&(*i).parameters[1], &(*m).heap, m);
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

		setValue(&(*i).parameters[0], &(*m).heap, m) = Var(pairs);
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KVINTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void kvinters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"KVINTERS";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).kvintersect(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KVNOTINTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void kvnotinters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"KVNOTINTERS";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 4);
		requiredVar(&(*i).parameters[1], &name, LangLib::getTrans(PAR2));
	}
	else {
		checkNotExistValue(&(*i).parameters[1], m);
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		setValue(&(*i).parameters[1], &(*m).heap, m) = getValue(&(*i).parameters[2], &(*m).heap, m).kvnotintersect(getValue(&(*i).parameters[0], &(*m).heap, m).toSTR().getWStr(), getValue(&(*i).parameters[3], &(*m).heap, m));
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLEARC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clearc(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"CLEARC";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 0);
	}
	else {
		//Ничего
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		system("clear");
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TOINTERF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tointerf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"TOINTERF";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
	}
	else {
		//Ничего
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		std::vector<Var> keyarr = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().arr;
		std::vector<Var> valarr = getValue(&(*i).parameters[2], &(*m).heap, m).toARR().arr;
		std::vector<Var> result;
		result.reserve(1000);

		if(keyarr.size() != valarr.size()) {
			throw std::wstring{ LangLib::getTrans(L"Массивы дожны быть одинакового размера\n")};
		}
		int size = (int)keyarr.size();
		std::vector<Var> pair;
		pair.reserve(2);
		for(int i = 0; i < size; ++i) {
			pair.emplace_back(getValue(&keyarr[i], &(*m).heap, m).toSTR().str);
			pair.emplace_back(getValue(&valarr[i], &(*m).heap, m));
			result.emplace_back(pair);
			pair.clear();
		}
		setValue(&(*i).parameters[0], &(*m).heap, m) = Var(result);
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNINTERF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void uninterf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"UNINTERF";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 3);
	}
	else {
		//Ничего
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		std::vector<Var> keyarr;
		std::vector<Var> valarr;
		keyarr.reserve(1000);
		valarr.reserve(1000);
		const std::vector<Var> &interform = getValue(&(*i).parameters[2], &(*m).heap, m).toARR().arr;

		int size = (int)interform.size();
		for (int i = 0; i < size; ++i) {
			if((int)interform[i].toARR().arr.size() != 2) {
				throw std::wstring{ LangLib::getTrans(L"Некорректный массив.\n")};
			}
			keyarr.emplace_back(interform[i].arr[0].toSTR());
			valarr.emplace_back(interform[i].arr[1]);
		}
		setValue(&(*i).parameters[0], &(*m).heap, m) = Var(keyarr);
		setValue(&(*i).parameters[1], &(*m).heap, m) = Var(valarr);
		if(iterate){++(*m).instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTERFTOMAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void interftomap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	if (prevalidate) {
		std::wstring name = L"INTERFTOMAP";
		checkParameterCount(STRICTED, (int)(*i).parameters.size(), &name, 2);
	}
	else {
		//Ничего
	}

	if (prego) {
		if(iterate){++(*m).instruct_number;}
	}
	else {
		std::unordered_map<std::wstring, Var> result;
		result.reserve(1000);

		std::vector<Var> interform = getValue(&(*i).parameters[1], &(*m).heap, m).toARR().arr;

		int size = (int)interform.size();
		for (int i = 0; i < size; ++i) {
			if((int)interform[i].toARR().arr.size() != 2) {
				throw std::wstring{ LangLib::getTrans(L"Некорректный массив.\n")};
			}
			Var a = interform[i].arr[0];
			Var b = interform[i].arr[1];
			result.insert({getValue(&a, &(*m).heap, m).toSTR().getWStr(), getValue(&b, &(*m).heap, m)});
		}
		setValue(&(*i).parameters[0], &(*m).heap, m) = Var(result);
		if(iterate){++(*m).instruct_number;}
	}
}