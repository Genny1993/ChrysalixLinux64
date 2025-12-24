#include <random>
#include <ctime>
#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <thread>

#include "InstructionFunctions.h"
#include "LangLib.h"

const std::wstring PAR1 = L"Первый";
const std::wstring PAR2 = L"Второй";
const std::wstring PAR3 = L"Третий";
const std::wstring PAR4 = L"Единственный";
const std::wstring PAR5 = L"Четвертый";

const std::vector<std::wstring> emp = {};
const std::vector<std::wstring> par1 = {
	PAR1
};
const std::vector<std::wstring> par2 = {
	PAR2
};
const std::vector<std::wstring> par3 = {
	PAR3
};
const std::vector<std::wstring> par4 = {
	PAR4
};
const std::vector<std::wstring> par5 = {
	PAR5
};
const std::vector<std::wstring> par1_2 = {
	PAR1,
	PAR2
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void nop(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"nop", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// END
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void end(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"end", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		m->ret_data = getValue(&i->parameters[0], &m->heap, m);
		m->instruct_number = -2147483648;
		++m->executed_count;
		throw Var(L"END");
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SLEEP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sleepf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"sleep", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::this_thread::sleep_for(std::chrono::milliseconds(getValue(&i->parameters[0], &m->heap, m).toUNTG().getUInt()));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VAR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void var(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"var", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if((int)i->parameters.size() == 1) {
			m->heap[i->parameters[0].toSTR().getWStr()] = Var();
		} else {
			m->heap[i->parameters[0].toSTR().getWStr()] = getValue(&i->parameters[1], &m->heap, m);
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PRINT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"print", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		for (Var& v : i->parameters)
		{
			std::wcout << getValue(&v, &m->heap, m);
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FREE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void free(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"free", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		for (Var& v : i->parameters)
		{
			if(v.getWStr() == L"$") {
				throw std::wstring{ LangLib::getTrans(L"Невозможно удалить нулевой регистр '$'\n") };
			}
			m->heap.erase(v.getWStr());
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LABEL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void label(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"label", par4);

	if (prego) {
		m->jmp_pointers[i->parameters[0].toSTR().getWStr()] = m->instruct_number;
		if(iterate){++m->instruct_number;}
	}
	else {
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JUMP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jump(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"jump", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		m->instruct_number = (int)getLabel(&i->parameters[0], &m->jmp_pointers).toUNTG().getUInt();
		++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INPUT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void input(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"input", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::wstring str;
		getline(std::wcin, str);
		setValue(&i->parameters[0], &m->heap, m) = Var(str);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CHANGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void change(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"change", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void to(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"to", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::wstring type = getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr();

		if (i->parameters.size() == 2) {
			if (type == std::wstring_view(L"ntg")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toNTG();
			}
			else if (type == std::wstring_view(L"untg")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toUNTG();
			}
			else if (type == std::wstring_view(L"dbl")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toDBL();
			}
			else if (type == std::wstring_view(L"chr")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toCHR();
			}
			else if (type == std::wstring_view(L"uchr")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toUCHR();
			}
			else if (type == std::wstring_view(L"bln")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toBLN();
			}
			else if (type == std::wstring_view(L"str")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toSTR();
			}
			else if (type == std::wstring_view(L"arr")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR();
			}
			else if (type == std::wstring_view(L"inst")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toINST();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Тип данных неизвестен\n") };
			}
		}
		else if (i->parameters.size() == 3) {
			if (type == std::wstring_view(L"ntg")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toNTG();
			}
			else if (type == std::wstring_view(L"untg")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toUNTG();
			}
			else if (type == std::wstring_view(L"dbl")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toDBL();
			}
			else if (type == std::wstring_view(L"chr")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toCHR();
			}
			else if (type == std::wstring_view(L"uchr")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toUCHR();
			}
			else if (type == std::wstring_view(L"bln")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toBLN();
			}
			else if (type == std::wstring_view(L"str")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toSTR();
			}
			else if (type == std::wstring_view(L"arr")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toARR();
			}
			else if (type == std::wstring_view(L"inst")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toINST();
			}
			else {
				throw std::wstring{ LangLib::getTrans(L": Тип данных неизвестен\n") };
			}
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CALC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void calc(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"calc", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::wstring type = getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr();
		if (type != std::wstring_view(L"+")
			&& type != std::wstring_view(L"-")
			&& type != std::wstring_view(L"*")
			&& type != std::wstring_view(L"/")
			&& type != std::wstring_view(L"%")
			&& type != std::wstring_view(L"^")
			&& type != std::wstring_view(L"inc")
			&& type != std::wstring_view(L"dec")
			&& type != std::wstring_view(L"log")
			&& type != std::wstring_view(L"ln")
			&& type != std::wstring_view(L"fact")
			&& type != std::wstring_view(L"root")
			&& type != std::wstring_view(L"abs")
			&& type != std::wstring_view(L"round")
			&& type != std::wstring_view(L"floor")
			&& type != std::wstring_view(L"ceil")) {
			throw std::wstring{ type + LangLib::getTrans(L": Математическая операция неизвестна\n") };
		}
		if (i->parameters.size() == 2) {
			if (type == std::wstring_view(L"inc")) {
				setValue(&i->parameters[1], &m->heap, m) += Var(1);
			}
			else if (type == std::wstring_view(L"dec")) {
				setValue(&i->parameters[1], &m->heap, m) -= Var(1);
			}
			else if (type == std::wstring_view(L"fact")) {
				int fact = getValue(&i->parameters[1], &m->heap, m).toUNTG().getUInt();
				unsigned long long int result = 1;
				for (int i = 1; i <= fact; ++i) {
					result *= i;
				}
				setValue(&i->parameters[1], &m->heap, m) = Var(result);
			}
			else if (type == std::wstring_view(L"ln")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(log(getValue(&i->parameters[1], &m->heap, m).toDBL().getDouble()));
			} else if (type == std::wstring_view(L"abs")) {
				const Var &temp = getValue(&i->parameters[1], &m->heap, m);
				if(temp.type == UCHR || temp.type == UNTG) {
					setValue(&i->parameters[1], &m->heap, m) = temp;
				} else if(temp.type == STR) {
					setValue(&i->parameters[1], &m->heap, m) = temp.toDBL() < 0.0 ? temp.toDBL() * -1.0 : temp.toDBL();
				} else if(temp.type == DBL) {
					setValue(&i->parameters[1], &m->heap, m) = temp < 0.0 ? temp * -1.0 : temp;
				} else {
					setValue(&i->parameters[1], &m->heap, m) = Var(std::llabs(temp.toNTG().data.ntg));
				}
			} else if (type == std::wstring_view(L"round")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(std::round(getValue(&i->parameters[1], &m->heap, m).toDBL().data.dbl));
			} else if (type == std::wstring_view(L"ceil")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(std::ceil(getValue(&i->parameters[1], &m->heap, m).toDBL().data.dbl));
			} else if (type == std::wstring_view(L"floor")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(std::floor(getValue(&i->parameters[1], &m->heap, m).toDBL().data.dbl));
			}
			else {
				throw std::wstring{ type + L" " + LangLib::getTrans(L"Математическая операция принимает 2 и больше параметров\n") };
			}
		}
		if (i->parameters.size() == 3) {
			if (type == std::wstring_view(L"inc")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) + Var(1);
			}
			else if (type == std::wstring_view(L"dec")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) - Var(1);
			}
			else if (type == std::wstring_view(L"fact")) {
				long long int fact = getValue(&i->parameters[2], &m->heap, m).toUNTG().getUInt();
				unsigned long long int result = 1;
				for (int i = 1; i <= fact; ++i) {
					result *= i;
				}
				setValue(&i->parameters[1], &m->heap, m) = Var(result);
			}
			else if (type == std::wstring_view(L"ln")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(log(getValue(&i->parameters[2], &m->heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"+")) {
				setValue(&i->parameters[1], &m->heap, m) += getValue(&i->parameters[2], &m->heap, m);
			}
			else if (type == std::wstring_view(L"-")) {
				setValue(&i->parameters[1], &m->heap, m) -= getValue(&i->parameters[2], &m->heap, m);
			}
			else if (type == std::wstring_view(L"*")) {
				setValue(&i->parameters[1], &m->heap, m) *= getValue(&i->parameters[2], &m->heap, m);
			}
			else if (type == std::wstring_view(L"/")) {
				const Var& param = getValue(&i->parameters[2], &m->heap, m);
				if (param == Var(0)) {
					throw std::wstring{ i->parameters[2].toSTR().getWStr() + LangLib::getTrans(L" Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&i->parameters[1], &m->heap, m) /= param;
			}
			else if (type == std::wstring_view(L"%")) {
				const Var& param = getValue(&i->parameters[2], &m->heap, m);
				if (param == Var(0)) {
					throw std::wstring{ i->parameters[2].toSTR().getWStr() + LangLib::getTrans(L" Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&i->parameters[1], &m->heap, m) %= param;
			}
			else if (type == std::wstring_view(L"^")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(pow(getValue(&i->parameters[1], &m->heap, m).toDBL().getDouble(), getValue(&i->parameters[2], &m->heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"root")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(pow(getValue(&i->parameters[1], &m->heap, m).toDBL().getDouble(), 1.0 / getValue(&i->parameters[2], &m->heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"log")) {
				setValue(&i->parameters[1], &m->heap, m) = log(getValue(&i->parameters[1], &m->heap, m).toDBL().getDouble()) / log(getValue(&i->parameters[2], &m->heap, m).toDBL().getDouble());

			} else if (type == std::wstring_view(L"abs")) {
				const Var& temp = getValue(&i->parameters[2], &m->heap, m);
				if(temp.type == UCHR || temp.type == UNTG) {
					setValue(&i->parameters[1], &m->heap, m) = temp;
				} else if(temp.type == STR) {
					setValue(&i->parameters[1], &m->heap, m) = temp.toDBL() < 0.0 ? temp.toDBL() * -1.0 : temp.toDBL();
				} else if(temp.type == DBL) {
					setValue(&i->parameters[1], &m->heap, m) = temp < 0.0 ? temp * -1.0 : temp;
				} else {
					setValue(&i->parameters[1], &m->heap, m) = Var(std::llabs(temp.toNTG().data.ntg));
				}
			} else if (type == std::wstring_view(L"round")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(std::round(getValue(&i->parameters[2], &m->heap, m).toDBL().data.dbl));
			} else if (type == std::wstring_view(L"ceil")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(std::ceil(getValue(&i->parameters[2], &m->heap, m).toDBL().data.dbl));
			} else if (type == std::wstring_view(L"floor")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(std::floor(getValue(&i->parameters[2], &m->heap, m).toDBL().data.dbl));
			}
		}
		if (i->parameters.size() == 4) {
			if (type == std::wstring_view(L"+")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) + getValue(&i->parameters[3], &m->heap, m);
			}
			else if (type == std::wstring_view(L"-")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) - getValue(&i->parameters[3], &m->heap, m);
			}
			else if (type == std::wstring_view(L"*")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) * getValue(&i->parameters[3], &m->heap, m);
			}
			else if (type == std::wstring_view(L"/")) {
				const Var& param = getValue(&i->parameters[3], &m->heap, m);
				if (param == Var(0)) {
					throw std::wstring{ i->parameters[3].toSTR().getWStr() + LangLib::getTrans(L" Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) / param;
			}
			else if (type == std::wstring_view(L"%")) {
				const Var& param = getValue(&i->parameters[3], &m->heap, m);
				if (param == Var(0)) {
					throw std::wstring{ i->parameters[3].toSTR().getWStr() + LangLib::getTrans(L" Деление на 0. Параметр равен нулю\n") };
				}
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) % param;
			}
			else if (type == std::wstring_view(L"^")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(pow(getValue(&i->parameters[2], &m->heap, m).toDBL().getDouble(), getValue(&i->parameters[3], &m->heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"root")) {
				setValue(&i->parameters[1], &m->heap, m) = Var(pow(getValue(&i->parameters[2], &m->heap, m).toDBL().getDouble(), 1.0 / getValue(&i->parameters[3], &m->heap, m).toDBL().getDouble()));
			}
			else if (type == std::wstring_view(L"log")) {
				setValue(&i->parameters[1], &m->heap, m) = log(getValue(&i->parameters[2], &m->heap, m).toDBL().getDouble()) / log(getValue(&i->parameters[3], &m->heap, m).toDBL().getDouble());

			}
			else {
				throw std::wstring{ type + L" " + LangLib::getTrans(L": Математическая операция принимает до 3 параметров\n") };
			}
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NEWTEMP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void newtemp(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"newtemp", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		int start = m->tmp_count;
		m->tmp_count += (int)getValue(&i->parameters[0], &m->heap, m).toUNTG().getUInt();
		for (unsigned int it = start; it < m->tmp_count; ++it) {
			m->heap[L"$" + std::to_wstring(it)] = Var();
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FORGET
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void forget(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"forget", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if (i->parameters.size() == 0) {
			int start = m->tmp_count - 1;
			m->tmp_count = 0;
			for (int it = start; it >= (int)m->tmp_count; --it) {
				m->heap.erase(L"$" + std::to_wstring(it));
			}
		}
		else if (i->parameters.size() == 1) {
			int start = m->tmp_count - 1;
			m->tmp_count -= (int)getValue(&i->parameters[0], &m->heap, m).toUNTG().getUInt();
			for (int it = start; it >= (int)m->tmp_count; --it) {
				m->heap.erase(L"$" + std::to_wstring(it));
			}
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TCOUNT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tcount(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"tcount", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = Var(m->tmp_count);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ISSET
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void isset(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"isset", par1_2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		try{
			getValue(&i->parameters[1], &m->heap, m);
			setValue(&i->parameters[0], &m->heap, m) = Var(true);
		}
		catch(const std::wstring& error_message) {
			setValue(&i->parameters[0], &m->heap, m) = Var(false);
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TYPEOF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void typeofv(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"typeof", par1);
	
	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).typeOf();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void comp(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"comp", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::wstring type = getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr();

		if (type == std::wstring_view(L"==")) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) == getValue(&i->parameters[3], &m->heap, m);
		} 
		else if(type == std::wstring_view(L"===")) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).eq(L"strict", getValue(&i->parameters[3], &m->heap, m));
		}
		else if(type == std::wstring_view(L"!==")) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).eq(L"strict", getValue(&i->parameters[3], &m->heap, m));
		}
		else if (type == std::wstring_view(L"!=")) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) != getValue(&i->parameters[3], &m->heap, m);
		}
		else if (type == std::wstring_view(L">")) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) > getValue(&i->parameters[3], &m->heap, m);
		}
		else if (type == std::wstring_view(L"<")) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) < getValue(&i->parameters[3], &m->heap, m);
		}
		else if (type == std::wstring_view(L">=")) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) >= getValue(&i->parameters[3], &m->heap, m);
		}
		else if (type == std::wstring_view(L"<=")) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m) <= getValue(&i->parameters[3], &m->heap, m);
		}
		else {
			throw std::wstring{ type + LangLib::getTrans(L": Операция сравнения неизвестна\n") };
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LOGIC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void logic(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"logic", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::wstring type = getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr();
		if (type != std::wstring_view(L"not")
			&& type != std::wstring_view(L"and")
			&& type != std::wstring_view(L"or")
			&& type != std::wstring_view(L"nand")
			&& type != std::wstring_view(L"nor")
			&& type != std::wstring_view(L"xor")
			&& type != std::wstring_view(L"xnor")) {
			throw std::wstring{ type + LangLib::getTrans(L": Логическая операция неизвестна\n") };
		}
		if (i->parameters.size() == 3) {
			if (type == std::wstring_view(L"not")) {
				setValue(&i->parameters[1], &m->heap, m) = !getValue(&i->parameters[2], &m->heap, m).toBLN().getBool();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Логическая операция принимет не менее 4 параметров\n") };
			}
		}
		else if (i->parameters.size() == 4) {
			if (type == std::wstring_view(L"and")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toBLN().getBool() && getValue(&i->parameters[3], &m->heap, m).toBLN().getBool();
			}
			else if (type == std::wstring_view(L"or")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toBLN().getBool() || getValue(&i->parameters[3], &m->heap, m).toBLN().getBool();
			}
			else if (type == std::wstring_view(L"nand")) {
				setValue(&i->parameters[1], &m->heap, m) = !(getValue(&i->parameters[2], &m->heap, m).toBLN().getBool() && getValue(&i->parameters[3], &m->heap, m).toBLN().getBool());
			}
			else if (type == std::wstring_view(L"nor")) {
				setValue(&i->parameters[1], &m->heap, m) = !(getValue(&i->parameters[2], &m->heap, m).toBLN().getBool() || getValue(&i->parameters[3], &m->heap, m).toBLN().getBool());
			}
			else if (type == std::wstring_view(L"xor")) {
				setValue(&i->parameters[1], &m->heap, m) = !(getValue(&i->parameters[2], &m->heap, m).toBLN().getBool()) != !(getValue(&i->parameters[3], &m->heap, m).toBLN().getBool());
			}
			else if (type == std::wstring_view(L"xnor")) {
				setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toBLN().getBool() == getValue(&i->parameters[3], &m->heap, m).toBLN().getBool();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Логическая операция принимет не более 3 параметров\n") };
			}
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JIF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jif(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"jif", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		bool swtch = getValue(&i->parameters[0], &m->heap, m).toBLN().getBool();
		if (swtch) {
			m->instruct_number = (int)getLabel(&i->parameters[1], &m->jmp_pointers).toUNTG().getUInt();
		}
		else {
			if(iterate){++m->instruct_number;} ++m->executed_count;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JIFNOT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jifnot(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"jifnot", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		bool swtch = getValue(&i->parameters[0], &m->heap, m).toBLN().getBool();
		if (swtch) {
			if(iterate){++m->instruct_number;} ++m->executed_count;
		}
		else {
			m->instruct_number = (int)getLabel(&i->parameters[1], &m->jmp_pointers).toUNTG().getUInt();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DLABEL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void dlabel(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"dlabel", par4);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		m->jmp_pointers[i->parameters[0].toSTR().getWStr()] = m->instruct_number;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SWAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void swap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"swap", par1_2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		Var firstval = getValue(&i->parameters[0], &m->heap, m);
		Var secondval = getValue(&i->parameters[1], &m->heap, m);
		swap(firstval, secondval);

		setValue(&i->parameters[0], &m->heap, m) = firstval;
		setValue(&i->parameters[1], &m->heap, m) = secondval;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRAY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"array", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		int dimensions = (int)i->parameters.size() - 1;
		Var result = Var();
		for (int iter = dimensions; iter > 0; --iter) {
			int dimension = (int)getValue(&i->parameters[iter], &m->heap, m).toUNTG().getUInt();
			std::vector<Var> v;
			v.reserve(1000);
			Var arr = Var(v);
			for (int j = 0; j < dimension; ++j) {
				arr.pushb(result);
			}
			result = arr;
		}
		if(m->heap.find(i->parameters[0].toSTR().str)== m->heap.end()) {
			m->heap[i->parameters[0].toSTR().str] = result;
		} else {
			setValue(&i->parameters[0], &m->heap, m) = result;
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VTOARR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void vtoarr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"vtoarr", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		int size = (int)i->parameters.size() - 1;
		std::vector<Var> v;
		v.reserve(1000);
		Var arr = Var(v);
		for (int iter = 1; iter <= size; ++iter) {
			arr.pushb(getValue(&i->parameters[iter], &m->heap, m));
		}

		if(m->heap.find(i->parameters[0].toSTR().str)== m->heap.end()) {
			m->heap[i->parameters[0].toSTR().str] = arr;
		} else {
			setValue(&i->parameters[0], &m->heap, m) = arr;
		}

		if(iterate){++m->instruct_number;} ++m->executed_count;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUSHB
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pushb(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"pushb", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m).pushb(getValue(&i->parameters[1], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POPB
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void popb(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"popb", par1_2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if (i->parameters.size() == 1) {
			setValue(&i->parameters[0], &m->heap, m).popb();
			if(iterate){++m->instruct_number;} ++m->executed_count;
		}
		else {
			setValue(&i->parameters[0], &m->heap, m) = setValue(&i->parameters[1], &m->heap, m).popb();
			if(iterate){++m->instruct_number;} ++m->executed_count;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUSHF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pushf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"pushf", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m).pushf(getValue(&i->parameters[1], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POPF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void popf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"popf", par1_2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if (i->parameters.size() == 1) {
			setValue(&i->parameters[0], &m->heap, m).popf();
			if(iterate){++m->instruct_number;} ++m->executed_count;
		}
		else {
			setValue(&i->parameters[0], &m->heap, m) = setValue(&i->parameters[1], &m->heap, m).popf();
			if(iterate){++m->instruct_number;} ++m->executed_count;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ERASE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void erase(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"erase", par1_2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if (i->parameters.size() == 2) {
			setValue(&i->parameters[0], &m->heap, m).erase(getValue(&i->parameters[1], &m->heap, m));
			if(iterate){++m->instruct_number;} ++m->executed_count;
		}
		else {
			setValue(&i->parameters[0], &m->heap, m) = setValue(&i->parameters[1], &m->heap, m).erase(getValue(&i->parameters[2], &m->heap, m));
			if(iterate){++m->instruct_number;} ++m->executed_count;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void insrt(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"insert", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m).insert_vector(getValue(&i->parameters[2], &m->heap, m), getValue(&i->parameters[1], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLEAR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clear(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"clear", par4);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m).clear();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SIZE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sizearr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"size", par1_2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).len();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SLICE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void slice(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"slice", par1_2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		const Var& x = getValue(&i->parameters[2], &m->heap, m);
		const Var& y = getValue(&i->parameters[3], &m->heap, m);

		if (x < 0) {
			throw std::wstring{ i->parameters[2].toSTR().getWStr() + LangLib::getTrans(L": Параметр меньше нуля\n") };
		}
		if (y < 0) {
			throw std::wstring{ i->parameters[3].toSTR().getWStr() + LangLib::getTrans(L": Параметр меньше нуля\n") };
		}
		if (x > m->heap[i->parameters[1].toSTR().getWStr()].csize() - 1) {
			throw std::wstring{ i->parameters[2].toSTR().getWStr() + L": " + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
		}
		if (x + y > m->heap[i->parameters[1].toSTR().getWStr()].csize()) {
			throw std::wstring{ i->parameters[3].toSTR().getWStr() + L": " + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
		}

		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().slice(x, y);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MERGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void merge(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"merge", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if (i->parameters.size() == 2) {
			Type typeA = getValue(&i->parameters[0], &m->heap, m).type;
			Type typeB = getValue(&i->parameters[1], &m->heap, m).type;
			if((typeA == MAP && typeB == MAP ) || (typeA == ARR && typeB == ARR )  ) {
				setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[0], &m->heap, m).merge(getValue(&i->parameters[1], &m->heap, m));
			} else if((typeA == MAP || typeA == ARR) && (typeB != MAP && typeB != ARR)) {
				setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[0], &m->heap, m).merge(getValue(&i->parameters[1], &m->heap, m).toARR());
			} else if((typeA != MAP && typeA != ARR) && (typeB == MAP || typeB == ARR)) {
				setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[0], &m->heap, m).toARR().merge(getValue(&i->parameters[1], &m->heap, m));
			} else {
				setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[0], &m->heap, m).toARR().merge(getValue(&i->parameters[1], &m->heap, m).toARR());
			}
		}
		else {
			Type typeA = getValue(&i->parameters[1], &m->heap, m).type;
			Type typeB = getValue(&i->parameters[2], &m->heap, m).type;
			if((typeA == MAP && typeB == MAP ) || (typeA == ARR && typeB == ARR )  ) {
				setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).merge(getValue(&i->parameters[2], &m->heap, m));
			} else if((typeA == MAP || typeA == ARR) && (typeB != MAP && typeB != ARR)) {
				setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).merge(getValue(&i->parameters[2], &m->heap, m).toARR());
			} else if((typeA != MAP && typeA != ARR) && (typeB == MAP || typeB == ARR)) {
				setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().merge(getValue(&i->parameters[2], &m->heap, m));
			} else {
				setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().merge(getValue(&i->parameters[2], &m->heap, m).toARR());
			}
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SORT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sort(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"sort", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {

		if (i->parameters.size() == 2) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().sortarr(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr());
		}
		else {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toARR().sortarr(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr());
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNIQUE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void unique(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"unique", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if (i->parameters.size() == 2) {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).uniq(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr());
		}
		else {
			setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).uniq(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr());
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// REVERSE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void reverse(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"reverse", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if (i->parameters.size() == 1) {
			setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[0], &m->heap, m).toARR().rev();
		}
		else {
			setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().rev();
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EQUAL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void equal(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"equal", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).eq(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[3], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void in(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"in", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).in(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[3], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INALL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inall(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"inall", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).inall(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[3], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rin(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"rin", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).rin(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[3], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RINALL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rinall(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"rinall", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).rinall(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[3], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRTOMAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arrtomap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"arrtomap", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::vector<Var> arr;
		arr.reserve(1000);
		arr = getValue(&i->parameters[1], &m->heap, m).toARR().getArr();
		int size = (int)arr.size();
		std::unordered_map<std::wstring, Var> map;
		map.reserve(1000);
		for(int i = 0; i < size; ++i) {
			map.insert({std::to_wstring(i), arr[i]});
		}
		
		setValue(&i->parameters[0], &m->heap, m) = Var(map);

		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"inters", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toARR().intersect(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[3], &m->heap, m).toARR());
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTINTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void notinters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"notinters", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).toARR().notintersect(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[3], &m->heap, m).toARR());
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRTOSTR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arrtostr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"arrtostr", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().arrtostr(getValue(&i->parameters[2], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SUM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sum(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"sum", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().sum();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AVG
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void avg(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"avg", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().avg();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void min(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"min", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().min();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAX
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void max(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"max", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().max();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RANGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void range(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"range", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().range();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEDIAN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void median(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"median", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().median();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MODE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mode(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"mode", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().mode();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STDDEV
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stddev(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"stddev", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = getValue(&i->parameters[1], &m->heap, m).toARR().stddev();
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUSH
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void push(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"push", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m).push(getValue(&i->parameters[1], &m->heap, m), getValue(&i->parameters[2], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  VTOMAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void vtomap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"vtomap", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		int size = (int)i->parameters.size();
		std::unordered_map<std::wstring, Var> map;
		map.reserve(1000);
		for(int index = 1; index < size; index+=2) {
			map.insert({getValue(&i->parameters[index], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[index + 1], &m->heap, m)});
		}

		if(m->heap.find(i->parameters[0].toSTR().str)== m->heap.end()) {
			m->heap[i->parameters[0].toSTR().str] = map;
		} else {
			setValue(&i->parameters[0], &m->heap, m) = map;
		}

		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GETVALS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getvals(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"getvals", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		const Var &map = getValue(&i->parameters[1], &m->heap, m);
		if(map.type != MAP) {
			std::wstring error = LangLib::getTrans(L"Инструкция используется только для следующих типов: ");
        	error += L"map\n";
        	throw std::wstring{ error };
		}
		std::vector<Var> vals;
		vals.reserve(1000);

		for (const auto& [key, val] : map.mp) {
			vals.emplace_back(val);
		}

		setValue(&i->parameters[0], &m->heap, m) = Var(vals);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GETKEYS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getkeys(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"getkeys", par1);	

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		const Var &map = getValue(&i->parameters[1], &m->heap, m);
		if(map.type != MAP) {
			std::wstring error = LangLib::getTrans(L"Инструкция используется только для следующих типов: ");
        	error += L"map\n";
        	throw std::wstring{ error };
		}
		std::vector<Var> keys;
		keys.reserve(1000);

		for (const auto& [key, val] : map.mp) {
			keys.emplace_back(key);
		}

		setValue(&i->parameters[0], &m->heap, m) = Var(keys);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GETINTERF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getinterf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"getinterf", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		const Var &map = getValue(&i->parameters[1], &m->heap, m);
		if(map.type != MAP) {
			std::wstring error = LangLib::getTrans(L"Инструкция используется только для следующих типов: ");
        	error += L"map\n";
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

		setValue(&i->parameters[0], &m->heap, m) = Var(pairs);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KVINTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void kvinters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"kvinters", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).kvintersect(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[3], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KVNOTINTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void kvnotinters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"kvnotinters", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[1], &m->heap, m) = getValue(&i->parameters[2], &m->heap, m).kvnotintersect(getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr(), getValue(&i->parameters[3], &m->heap, m));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLEARC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clearc(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"clearc", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		system("clear");
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TOINTERF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tointerf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"tointerf", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::vector<Var> keyarr = getValue(&i->parameters[1], &m->heap, m).toARR().arr;
		std::vector<Var> valarr = getValue(&i->parameters[2], &m->heap, m).toARR().arr;
		std::vector<Var> result;
		result.reserve(1000);

		if(keyarr.size() != valarr.size()) {
			throw std::wstring{ LangLib::getTrans(L"Массивы дожны быть одинакового размера\n")};
		}
		int size = (int)keyarr.size();
		std::vector<Var> pair;
		pair.reserve(2);
		for(int i = 0; i < size; ++i) {
			pair.emplace_back(getValue(&keyarr[i], &m->heap, m).toSTR().str);
			pair.emplace_back(getValue(&valarr[i], &m->heap, m));
			result.emplace_back(pair);
			pair.clear();
		}
		setValue(&i->parameters[0], &m->heap, m) = Var(result);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNINTERF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void uninterf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"uninterf", par1_2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::vector<Var> keyarr;
		std::vector<Var> valarr;
		keyarr.reserve(1000);
		valarr.reserve(1000);
		const std::vector<Var> &interform = getValue(&i->parameters[2], &m->heap, m).toARR().arr;

		int size = (int)interform.size();
		for (int i = 0; i < size; ++i) {
			if((int)interform[i].toARR().arr.size() != 2) {
				throw std::wstring{ LangLib::getTrans(L"Некорректный массив\n")};
			}
			keyarr.emplace_back(interform[i].arr[0].toSTR());
			valarr.emplace_back(interform[i].arr[1]);
		}
		setValue(&i->parameters[0], &m->heap, m) = Var(keyarr);
		setValue(&i->parameters[1], &m->heap, m) = Var(valarr);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTERFTOMAP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void interftomap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"interftomap", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::unordered_map<std::wstring, Var> result;
		result.reserve(1000);

		std::vector<Var> interform = getValue(&i->parameters[1], &m->heap, m).toARR().arr;

		int size = (int)interform.size();
		for (int i = 0; i < size; ++i) {
			if((int)interform[i].toARR().arr.size() != 2) {
				throw std::wstring{ LangLib::getTrans(L"Некорректный массив\n")};
			}
			Var a = interform[i].arr[0];
			Var b = interform[i].arr[1];
			result.insert({getValue(&a, &m->heap, m).toSTR().getWStr(), getValue(&b, &m->heap, m)});
		}
		setValue(&i->parameters[0], &m->heap, m) = Var(result);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RAND
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rand(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"rand", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if((int)i->parameters.size() == 1) {
			std::uniform_real_distribution<> dis(0.0, 1.0);
			setValue(&i->parameters[0], &m->heap, m) = Var(dis(m->mersenne_twister));
		} else {
			std::uniform_int_distribution randomizer{ getValue(&i->parameters[1], &m->heap, m).toUNTG().data.untg, getValue(&i->parameters[2], &m->heap, m).toUNTG().data.untg };
			setValue(&i->parameters[0], &m->heap, m) = Var(randomizer(m->mersenne_twister));
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// T
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void t(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"t", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = Var((unsigned long long int)std::time(nullptr));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HRT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void hrt(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"hrt", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = Var(static_cast<unsigned long long int>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()));
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BETWEEN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void between(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"between", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		const Var& result = getValue(&i->parameters[1], &m->heap, m) >= getValue(&i->parameters[2], &m->heap, m) && getValue(&i->parameters[1], &m->heap, m) <= getValue(&i->parameters[3], &m->heap, m);
		setValue(&i->parameters[0], &m->heap, m) = result;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JIFELSE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jifelse(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"jifelse", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		bool swtch = getValue(&i->parameters[0], &m->heap, m).toBLN().getBool();
		if (swtch) {
			m->instruct_number = (int)getLabel(&i->parameters[1], &m->jmp_pointers).toUNTG().getUInt();
		}
		else {
			m->instruct_number = (int)getLabel(&i->parameters[2], &m->jmp_pointers).toUNTG().getUInt();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JSWITCH
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jswitch(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"jswitch", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		const Var& swtch = getValue(&i->parameters[0], &m->heap, m);
		int size = i->parameters.size();
		for(int is = 1; is < size - 2; is+=2) {
			if(swtch.eq(L"strict", getValue( &i->parameters[is], &m->heap, m)).data.bln) {
				m->instruct_number = (int)getLabel(&i->parameters[is+1], &m->jmp_pointers).toUNTG().getUInt();
				return;
			}
		}
		m->instruct_number = (int)getLabel(&i->parameters[i->parameters.size() - 1], &m->jmp_pointers).toUNTG().getUInt();
		++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FORMAT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fmt(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"format", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {

		std::wstring type = getValue( &i->parameters[2], &m->heap, m).toSTR().str;
		const Var& parameter = getValue( &i->parameters[1], &m->heap, m);
		const Var& width = getValue( &i->parameters[3], &m->heap, m).toNTG();
		const Var& precision = getValue( &i->parameters[4], &m->heap, m).toNTG();
		const Var& align = getValue( &i->parameters[5], &m->heap, m).toSTR();
		Var lead = getValue( &i->parameters[6], &m->heap, m).toSTR();

		if(parameter.type != CHR && parameter.type != UCHR &&
			parameter.type != NTG && parameter.type != UNTG &&
			parameter.type != BLN && parameter.type != DBL && parameter.type != STR
		) {
			std::wstring error = type + LangLib::getTrans(L"Инструкция используется только для следующих типов: ");
			error += L"chr, uchr, ntg, untg, bln, dbl, str";
			throw std::wstring{ type + error };
		}

		if(type != std::wstring_view(L"dec") &&
			type != std::wstring_view(L"oct") &&
			type != std::wstring_view(L"hex") &&
			type != std::wstring_view(L"bin")) {
			throw std::wstring{ type + LangLib::getTrans( L": Неизвестное представление числа\n") };
		}

		if(align.str != std::wstring_view(L"left") &&
		align.str != std::wstring_view(L"right") && 
		align.str != std::wstring_view(L"default")
		) {
			throw std::wstring{ align.str + LangLib::getTrans(L": Неизвестный тип выравнивания\n") };
		}
		
		std::wostringstream woss;

		if(align.str != std::wstring_view(L"left")) {
			woss << std::left;
		}

		if(align.str != std::wstring_view(L"right")) {
			woss << std::right;
		}
		if(width.data.ntg > 0) {
			woss << std::setw(width.data.ntg);
			if(lead.str == L"") {
				lead.str = L" ";
			}
			woss << std::setfill(lead.str.at(0));
		}


		if(precision.data.ntg > -1) {
			woss << std::fixed << std::setprecision(precision.data.ntg);
		}
	
		if(type == std::wstring_view(L"oct") ) {
			woss << std::oct;
		} else if (type == std::wstring_view(L"hex") ) {
			woss << std::hex;
		} else if (type == std::wstring_view(L"bin") ) {
			if(parameter.type == NTG ||  parameter.type == CHR) {
				woss << std::bitset<64>(parameter.toNTG().data.ntg);
			} else if(parameter.type == UCHR || parameter.type == UNTG || parameter.type == BLN) {
				woss << std::bitset<64>(parameter.toNTG().data.untg);
			} else if(parameter.type == DBL || parameter.type == STR) {
				woss << std::bitset<64>(parameter.toDBL().data.dbl);
			}
			
		}

		if(type != std::wstring_view(L"bin")) {
			if(parameter.type == NTG ||  parameter.type == CHR) {
				woss << parameter.toNTG().data.ntg;
			} else if(parameter.type == UCHR || parameter.type == UNTG || parameter.type == BLN) {
				woss << parameter.toUNTG().data.untg;
			} else if(parameter.type == DBL || parameter.type == STR) {
				woss << parameter.toDBL().data.dbl;
			}
		}

		Var result = woss.str();
		if(type == L"bin") {
			std::wstring str = result.str;
			std::wstring newstr = L"";

			bool lz_end = false;
			int size = str.size();
			for(int iter = 0; iter < size; ++iter) {
				if(lz_end) {
					newstr += str[iter];
				} else {
					if(str[iter] != L'0') {
						lz_end = true;
						newstr += str[iter];
					}
				}
			}
			if(newstr == L"") {
				newstr = L"0";
			}
			result = newstr;
		}
		setValue(&i->parameters[0], &m->heap, m) = result;

		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRIGON
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void trigon(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"trigon", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {

		std::wstring type = getValue( &i->parameters[0], &m->heap, m).toSTR().str;

		if(type == std::wstring_view(L"sin")) {
			setValue(&i->parameters[1], &m->heap, m) = std::sinl(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
		} else if(type == std::wstring_view(L"cos")) {
			setValue(&i->parameters[1], &m->heap, m) = std::cosl(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
		} else if(type == std::wstring_view(L"tan")) {
			setValue(&i->parameters[1], &m->heap, m) = std::tanl(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
		} else if(type == std::wstring_view(L"ctg")) {
			long double val = std::tan(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
			if(val == 0.0 ){
				val = 0.0000000000000000000000000001L;
			}
			setValue(&i->parameters[1], &m->heap, m) = 1.0 / val;
		} else if(type == std::wstring_view(L"asin")) {
			setValue(&i->parameters[1], &m->heap, m) = std::asinl(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
		} else if(type == std::wstring_view(L"acos")) {
			setValue(&i->parameters[1], &m->heap, m) = std::acosl(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
		} else if(type == std::wstring_view(L"atan")) {
			setValue(&i->parameters[1], &m->heap, m) = std::atanl(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
		} else if(type == std::wstring_view(L"actg")) {
			setValue(&i->parameters[1], &m->heap, m) = (M_PI / 2.0) - std::atanl(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
		} else if(type == std::wstring_view(L"sec")) {
			long double val = std::cos(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
			if(val == 0.0 ){
				val = 0.0000000000000000000000000001L;
			}
			setValue(&i->parameters[1], &m->heap, m) = 1.0 /  val;
		} else if(type == std::wstring_view(L"csc")) {
			long double val = std::sin(getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl);
			if(val == 0.0 ){
				val = 0.0000000000000000000000000001L;
			}
			setValue(&i->parameters[1], &m->heap, m) = 1.0 / val;
		} else if(type == std::wstring_view(L"asec")) {
			long double val = getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl;
			if(val == 0.0 ){
				val = 0.0000000000000000000000000001L;
			}
			setValue(&i->parameters[1], &m->heap, m) = std::acosl(1.0 / val);
		} else if(type == std::wstring_view(L"acsc")) {
			long double val = getValue( &i->parameters[2], &m->heap, m).toDBL().data.dbl;
			if(val == 0.0 ){
				val = 0.0000000000000000000000000001L;
			}
			setValue(&i->parameters[1], &m->heap, m) = std::asinl(1.0 / val);
		} else {
			throw std::wstring{ type + LangLib::getTrans( L": Неизвестная тригонометрическая функция\n") };
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEGTORAD
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void degtorad(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"degtorad", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = Var(getValue( &i->parameters[1], &m->heap, m).toDBL().data.dbl * M_PI / 180.0);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RADTODEG
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void radtodeg(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"radtodeg", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = Var(getValue( &i->parameters[1], &m->heap, m).toDBL().data.dbl * 180.0 / M_PI);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIANCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void variance(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"variance", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = std::pow(getValue(&i->parameters[1], &m->heap, m).toARR().stddev().toDBL().data.dbl, 2);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CASTCHK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void castchk(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"castchk", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::wstring type = getValue(&i->parameters[0], &m->heap, m).toSTR().getWStr();
		try {
			if (type == std::wstring_view(L"ntg")) {
				getValue(&i->parameters[2], &m->heap, m).toNTG();
			}
			else if (type == std::wstring_view(L"untg")) {
				getValue(&i->parameters[2], &m->heap, m).toUNTG();
			}
			else if (type == std::wstring_view(L"dbl")) {
				getValue(&i->parameters[2], &m->heap, m).toDBL();
			}
			else if (type == std::wstring_view(L"chr")) {
				getValue(&i->parameters[2], &m->heap, m).toCHR();
			}
			else if (type == std::wstring_view(L"uchr")) {
				getValue(&i->parameters[2], &m->heap, m).toUCHR();
			}
			else if (type == std::wstring_view(L"bln")) {
				getValue(&i->parameters[2], &m->heap, m).toBLN();
			}
			else if (type == std::wstring_view(L"str")) {
				getValue(&i->parameters[2], &m->heap, m).toSTR();
			}
			else if (type == std::wstring_view(L"arr")) {
				getValue(&i->parameters[2], &m->heap, m).toARR();
			}
			else {
				throw std::wstring{ type + LangLib::getTrans(L": Тип данных неизвестен\n") };
			}
			setValue(&i->parameters[1], &m->heap, m) = Var(true);
		}
		catch(const std::wstring& error_message) {
			setValue(&i->parameters[1], &m->heap, m) = Var(false);
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FINALIZE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void finalize(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"finalize", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if(i->parameters[0].toSTR().str == std::wstring_view(L"$")) {
			throw std::wstring{ LangLib::getTrans(L"Нулевой регистр невозможно сделать константой!\n") };
		}
		setValue(&i->parameters[0], &m->heap, m).is_const = true;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void constv(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"const", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		m->heap[i->parameters[0].toSTR().getWStr()] = getValue(&i->parameters[1], &m->heap, m);
		m->heap[i->parameters[0].toSTR().getWStr()].is_const = true;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ISCONST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void isconst(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"isconst", par2);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::wstring type = getValue(&i->parameters[0], &m->heap, m).toSTR().str;
		if(type == std::wstring_view(L"const")) {
			m->heap[i->parameters[1].toSTR().getWStr()] = Var(getValue(&i->parameters[2], &m->heap, m).is_const);
		} else if(type == std::wstring_view(L"sconst")) {
			m->heap[i->parameters[1].toSTR().getWStr()] = Var(getValue(&i->parameters[2], &m->heap, m).is_superconst);
		} else {
			throw std::wstring{ type + L": " + LangLib::getTrans(L"Неизвестный тип константы\n") };
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inst(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"inst", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if(i->parameters[1].type != Type::INST) {
			throw std::wstring{ LangLib::getTrans(L"INST: Инструкция принимает только блок инструкций\n") };
		}
		m->heap[i->parameters[0].toSTR().getWStr()] = i->parameters[1];
		m->heap[i->parameters[0].toSTR().getWStr()].deactivate = true;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// E
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void e(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"e", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		Var temp = getValue(&i->parameters[1], &m->heap, m);
		temp.deactivate = false;
		setValue(&i->parameters[0], &m->heap, m) = getValue(&temp, &m->heap, m);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PARSE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void parse(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"parse", par1);


	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		Var temp = getValue(&i->parameters[1], &m->heap, m).toSTR().toINST();
		temp.deactivate = true;

		int size = temp.instructions.size();
		for( int i = 0; i < size; ++i) {
			validateInstruction(temp.instructions[i], m, true);	
		}

		if(m->heap.find(i->parameters[0].toSTR().str)== m->heap.end()) {
			m->heap[i->parameters[0].toSTR().str] = temp;
		} else {
			setValue(&i->parameters[0], &m->heap, m) = temp;
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNPARSE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void unparse(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"unparse", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		const Var& temp = getValue(&i->parameters[1], &m->heap, m).toINST();
		std::wstring result = L"";
        int size_i = (int)temp.instructions.size();
        for( int i = 0; i < size_i; ++i) {
            result += temp.instructions[i].as_string;
            if(i < size_i - 1) {
				if(temp.instructions[i].as_string.at(result.size() - 1) != L';') {
                    result += L"; ";
				} else {
					if(i != size_i - 1) {
						result += L" ";
					}
				}
            }
        }
		setValue(&i->parameters[0], &m->heap, m)  = Var(result);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pe(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"pe", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		Var temp = getValue(&i->parameters[1], &m->heap, m).toSTR().toINST();

		int size = temp.instructions.size();
		for( int i = 0; i < size; ++i) {
			validateInstruction(temp.instructions[i], m, true);	
		}
		setValue(&i->parameters[0], &m->heap, m) = getValue(&temp, &m->heap, m);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ifi(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"if", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		const Var& condition = getValue(&i->parameters[0], &m->heap, m).toBLN();
		Var truecond = i->parameters[1];
		Var falsecond;
		falsecond.type = INST;
		if(i->parameters.size() == 3) {
			falsecond = i->parameters[2];
		}
		if(truecond.type != INST || falsecond.type != INST) {
			throw std::wstring{ LangLib::getTrans(L"if: Второй и третий параметр должны быть блоками инструкций\n") };
		}

		if(condition.toBLN().data.bln) {
			getValue(&truecond, &m->heap, m);
		} else {
			if(i->parameters.size() == 3) {
				getValue(&falsecond, &m->heap, m);
			}
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FOR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fori(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"for", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		Var init = i->parameters[0];
		Var condition = i->parameters[1];
		Var increment = i->parameters[2];
		Var postcycle = i->parameters[3];
		Var body = i->parameters[4];

		if(init.type != INST || increment.type != INST || postcycle.type != INST || body.type != INST) {
			throw std::wstring{ L"for: " + LangLib::getTrans(L"Все параметры должны быть блоками инструкций\n") };
		}

		getValue(&init, &m->heap, m);
		while(true) {
			if(!getValue(&condition, &m->heap, m).toBLN().data.bln) {
				getValue(&postcycle, &m->heap, m);
				break;
			}
			try{
				getValue(&body, &m->heap, m);
			}
			catch(std::vector<int>& e) {
				if(e[0] == 0) {
					getValue(&postcycle, &m->heap, m);
					if(e[1] <= 1) {
						break;
					} else {
						e[1] -= 1;
						throw e;
					}
				}
				if(e[0] == 1) {
					if(e[1] <= 1) {
						getValue(&increment, &m->heap, m);
						continue;
					}  else {
						e[1] -= 1;
						getValue(&postcycle, &m->heap, m);
						throw e;
					}
				}
			}				
			getValue(&increment, &m->heap, m);
		}

		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BREAK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void breaki(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"break", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::vector<int> bstruct;
		bstruct.emplace_back(0);
		if(i->parameters.size() == 1) {
			bstruct.emplace_back(getValue(&i->parameters[0], &m->heap, m).toNTG().data.ntg);
		} else {
			bstruct.emplace_back(1);
		}
		throw bstruct;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONTINUE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void continuei(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"continue", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::vector<int> cstruct;
		cstruct.emplace_back(1);
		if(i->parameters.size() == 1) {
			cstruct.emplace_back(getValue(&i->parameters[0], &m->heap, m).toNTG().data.ntg);
		} else {
			cstruct.emplace_back(1);
		}
		throw cstruct;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WHILE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void whilei(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"while", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		Var condition = i->parameters[0];
		Var body = i->parameters[1];

		if(body.type != INST) {
			throw std::wstring{ L"while: " + LangLib::getTrans(L"Все параметры должны быть блоками инструкций\n") };
		}

		while(true) {
			if(!getValue(&condition, &m->heap, m).toBLN().data.bln) {
				break;
			}
			try{
				getValue(&body, &m->heap, m);
			}
			catch(std::vector<int>& e) {
				if(e[0] == 0) {
					if(e[1] <= 1) {
						break;
					} else {
						e[1] -= 1;
						throw e;
					}
				}
				if(e[0] == 1) {
					if(e[1] <= 1) {
						continue;
					}  else {
						e[1] -= 1;
						throw e;
					}
				}
			}				
		}

		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DOWHILE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void dowhile(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"dowhile", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		Var condition = i->parameters[0];
		Var body = i->parameters[1];

		if(body.type != INST) {
			throw std::wstring{ L"dowhile: " + LangLib::getTrans(L"Все параметры должны быть блоками инструкций\n") };
		}

		while(true) {
			try{
				getValue(&body, &m->heap, m);
			}
			catch(std::vector<int>& e) {
				if(e[0] == 0) {
					if(e[1] <= 1) {
						break;
					} else {
						e[1] -= 1;
						throw e;
					}
				}
				if(e[0] == 1) {
					if(e[1] <= 1) {
						continue;
					}  else {
						e[1] -= 1;
						throw e;
					}
				}
			}		
			if(!getValue(&condition, &m->heap, m).toBLN().data.bln) {
				break;
			}		
		}

		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SWITCH
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void switchi(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"switch", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		const Var& swtch = getValue(&i->parameters[0], &m->heap, m);
		int size = i->parameters.size();
		for(int is = 1; is < size - 2; is+=2) {
			if(swtch.eq(L"strict", getValue( &i->parameters[is], &m->heap, m)).data.bln) {
				Var temp = i->parameters[is+1];
				if(temp.type != INST) {
					throw std::wstring{ L"switch: " + LangLib::getTrans(L"Каждый нечетный параметр кроме первого должны быть блоком инструкций\n") };
				}
				getValue(&temp, &m->heap, m);
				if(iterate){++m->instruct_number;} ++m->executed_count;
				return;
			}
		}
		Var tempdefault = i->parameters[i->parameters.size() - 1];
		if(tempdefault.type != INST) {
			throw std::wstring{ L"switch: " + LangLib::getTrans(L"Последний параметр должен быть блоком инструкций\n") };
		}
		getValue( &tempdefault, &m->heap, m);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ISCODE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void iscode(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"iscode", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		try{	
			Var temp = getValue(&i->parameters[1], &m->heap, m).toSTR().toINST();
			temp.deactivate = true;

			int size = temp.instructions.size();
			for( int i = 0; i < size; ++i) {
				validateInstruction(temp.instructions[i], m, true);	
			}
			setValue(&i->parameters[0], &m->heap, m) = Var(true);
		}
		catch(const std::wstring& e) {
			setValue(&i->parameters[0], &m->heap, m) = Var(false);
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SCONST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sconst(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"sconst", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		m->heap[i->parameters[0].toSTR().getWStr()] = getValue(&i->parameters[1], &m->heap, m);
		m->heap[i->parameters[0].toSTR().getWStr()].is_superconst = true;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SFINALIZE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sfinalize(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"sfinalize", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		if(i->parameters[0].toSTR().str == L"$") {
			throw std::wstring{ LangLib::getTrans(L"Нулевой регистр невозможно сделать константой!\n") };
		}
		setValue(&i->parameters[0], &m->heap, m).is_superconst = true;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLZDONTCRASH
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void plzdontcrash(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"plzdontcrash", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		bool mode = getValue(&i->parameters[0], &m->heap, m).toBLN().data.bln;
		if(mode) {
			m->softerrors = true;
		} else {
			m->softerrors = false;
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLZSHUTUP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void plzshutup(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"plzshutup", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		bool mode = getValue(&i->parameters[0], &m->heap, m).toBLN().data.bln;
		if(mode) {
			m->silence = true;
		} else {
			m->silence = false;
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tryi(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"try", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		Var temp = i->parameters[0];
		Var catchblock = i->parameters[1];
		if(temp.type != INST || catchblock.type != INST) {
			throw std::wstring{ L"try: " + LangLib::getTrans(L"Все параметры должны быть блоками инструкций\n") };
		}
		try{
			getValue(&temp, &m->heap, m);
		} 
		catch(const std::wstring error) {
			std::wstring temp = error;
			if(temp.at(0) == L'$') {
				temp.erase(0, 1);
			}
			m->heap[L"$"] = Var(temp);
			getValue(&catchblock, &m->heap, m);
		} 
		catch (const std::vector<int>& error) {
			m->heap[L"$"] = Var(std::to_wstring(error[0]) + L":" + std::to_wstring(error[1]));
			getValue(&catchblock, &m->heap, m);
		}
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THROW
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void throwi(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"throw", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		Var temp = i->parameters[0];
		std::wstring str = L"";
		for (Var& v : i->parameters)
		{
			str += getValue(&v, &m->heap, m).toSTR().str;
		}
		throw str;
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PARALLEL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void parallel(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"parallel", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::vector<std::thread> threads;
		int size = i->parameters.size();
		Var result;
		for(int indx = 0; indx < size; ++indx) {
			Var* inst = &i->parameters[indx];
			threads.emplace_back(
				[inst, m]() {
				getValue(inst,  &m->heap, m);
			});
		}

		for(std::thread &t : threads) {
			t.join();
		}
		
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GETCHAR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getchar(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"getchar", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) =  getValue(&i->parameters[1], &m->heap, m).toSTR()[getValue(&i->parameters[2], &m->heap, m).toUNTG()];
		
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SETCHAR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setchar(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"setchar", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		std::wstring temp = getValue(&i->parameters[0], &m->heap, m).toSTR().str;
		temp.replace(getValue(&i->parameters[2], &m->heap, m).toUNTG().getUInt(), 1, 1, getValue(&i->parameters[1], &m->heap, m).toSTR().str[0]);
		setValue(&i->parameters[0], &m->heap, m) = temp;
		
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARROW
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arrow(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L">", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		m->heap[L"$"] = getValue(&i->parameters[0], &m->heap, m);
		if(iterate){++m->instruct_number;} ++m->executed_count;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CHEVRON
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void chevron(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L">>", emp);

	if(prego){}
	if(iterate){++m->instruct_number;} ++m->executed_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLZTRUSTME
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void plztrustme(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"plztrustme", emp);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		bool mode = getValue(&i->parameters[0], &m->heap, m).toBLN().data.bln;
		if(mode) {
			m->validate = false;
		} else {
			m->validate = true;
		}
		if(iterate){++m->instruct_number;}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ICOUNT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void icount(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate) {
	validateCurrentInstruction(m, *i, prevalidate, L"icount", par1);

	if (prego) {
		if(iterate){++m->instruct_number;}
	}
	else {
		setValue(&i->parameters[0], &m->heap, m) = Var(m->executed_count);
		if(iterate){++m->instruct_number;}
	}
}