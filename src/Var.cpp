#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string_view>

#include "LangLib.h"
#include "Var.h"
#include "Parser.h"

const std::wstring MESSAGE1 = L"Не удалось привести строку к типу ";
const std::wstring MESSAGE2 = L"Невозможно привести массив к типу ";
const std::wstring MESSAGE3 = L"Невозможно привести словарь к типу ";
const std::wstring MESSAGE4 = L"Индекс находится вне диапазона\n";
const std::wstring MESSAGE5 = L"Взятие значения по индексу возможно только для следующих типов: ";
const std::wstring MESSAGE6 = L"Индекс словаря не существует\n";
const std::wstring MESSAGE7 = L"Инструкция используется только для следующих типов: ";
const std::wstring MESSAGE8 = L"Массив не поддерживает данной операции\n";
const std::wstring MESSAGE9 = L"Cловарь не поддерживает данной операции\n";
const std::wstring MESSAGE10 = L"Невозможно привести блок инструкций к типу ";
const std::wstring MESSAGE11 = L"Блок инструкций не поддерживает данной операции\n";

Var::Var() {
    this->type = NIL;
}

Var::Var(unsigned long long int untg) {
    this->type = UNTG;
    this->data.untg = untg;
}

Var::Var(long long int ntg) {
    this->type = NTG;
    this->data.ntg = ntg;
}

Var::Var(long int ntg) {
    this->type = NTG;
    this->data.ntg = (long long int)ntg;
}

Var::Var(int ntg) {
    this->type = NTG;
    this->data.ntg = (long long int)ntg;
}

Var::Var(short int ntg) {
    this->type = NTG;
    this->data.ntg = (long long int)ntg;
}

Var::Var(unsigned short int ntg) {
    this->type = NTG;
    this->data.ntg = (long long int)ntg;
}

Var::Var(unsigned int ntg) {
    this->type = NTG;
    this->data.ntg = (long long int)ntg;
}

Var::Var(unsigned long int ntg) {
    this->type = NTG;
    this->data.ntg = (long long int)ntg;
}

Var::Var(long double dbl) {
    this->type = DBL;
    this->data.dbl = dbl;
}

Var::Var(double dbl) {
    this->type = DBL;
    this->data.dbl = (long double)dbl;
}

Var::Var(float dbl) {
    this->type = DBL;
    this->data.dbl = (long double)dbl;
}

Var::Var(char chr) {
    this->type = CHR;
    this->data.chr = chr;
}

Var::Var(unsigned char uchr) {
    this->type = UCHR;
    this->data.uchr = uchr;
}

Var::Var(bool bln) {
    this->type = BLN;
    this->data.bln = bln;
}

Var::Var(std::wstring str) {
    this->type = STR;
    this->str = str;
}

Var::Var(const wchar_t* str) {
    this->type = STR;
    this->str = str;
}

Var::Var(std::wstring t, int i) {
    if (t == std::wstring_view(L"array")) {
        this->type = ARR;
        this->arr = std::vector<Var>(i);
    } 
    else if (t == std::wstring_view(L"map") && i == 0) {
        this->type = MAP;
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    else {
        this->type = UNKNOWN;
    }
}

Var::Var(std::vector<Var> v) {
    this->type = ARR;
    this->arr = v;
    if(this->arr.capacity() < 1000) {
        this->arr.reserve(1000);
    }
}

Var::Var(std::unordered_map<std::wstring, Var> m) {
    this->type = MAP;
    if(m.bucket_count() < 1000) {
        m.reserve(1000);
    }
    this->mp = m;
}

long long int Var::getInt() const {
    if (this->type == NTG) {
        return this->data.ntg;
    }
    else {
        throw std::wstring{ LangLib::getTrans(L"Переменная не является знаковой целочисленной\n") };
    }
}

unsigned long long int Var::getUInt() const {
    if (this->type == UNTG) {
        return this->data.untg;
    }
    else {
        throw std::wstring{ LangLib::getTrans(L"Переменная не является беззнаковой целочисленной\n") };
    }
}

long double Var::getDouble() const {
    if (this->type == DBL) {
        return this->data.dbl;
    }
    else {
        throw std::wstring{ LangLib::getTrans(L"Переменная не является числом с плавающей точкой\n") };
    }
}

char Var::getChar() const {
    if (this->type == CHR) {
        return this->data.chr;
    }
    else {
        throw std::wstring{ LangLib::getTrans(L"Переменная не является символьной\n") };
    }
}

unsigned char Var::getUChar() const {
    if (this->type == UCHR) {
        return this->data.uchr;
    }
    else {
        throw std::wstring{ LangLib::getTrans(L"Переменная не является беззнаковой символьной\n") };
    }
}

bool Var::getBool() const {
    if (this->type == BLN) {
        return this->data.bln;
    }
    else {
        throw std::wstring{ LangLib::getTrans(L"Переменная не является булевой\n") };
    }
}

std::wstring Var::getWStr() const {
    if (this->type == STR) {
        return this->str;
    }
    else {
        throw std::wstring{ LangLib::getTrans(L"Переменная не является строкой\n") };
    }
}

std::vector<Var> Var::getArr() const {
    if (this->type == ARR) {
        return this->arr;
    }
    else {
        throw std::wstring{ LangLib::getTrans(L"Переменная не является массивом\n") };
    }
}

std::unordered_map<std::wstring, Var> Var::getMap() const {
    if (this->type == MAP) {
        return this->mp;
    }
    else {
        throw std::wstring{ LangLib::getTrans(L"Переменная не является словарем\n") };
    }
}

Var Var::toNTG() const {
    if (this->type == NTG) {
        Var result = this->data.ntg;
        return result;
    }
    else if (this->type == UNTG) {
        Var result;
        result.type = NTG;
        result.data.ntg = (long long int)this->data.untg;
        return result;
    }
    else if (this->type == DBL) {
        Var result;
        result.type = NTG;
        result.data.ntg = (long long int)this->data.dbl;
        return result;
    }
    else if (this->type == CHR) {
        Var result;
        result.type = NTG;
        result.data.ntg = (long long int)this->data.chr;
        return result;
    }
    else if (this->type == UCHR) {
        Var result;
        result.type = NTG;
        result.data.ntg = (long long int)this->data.uchr;
        return result;
    }
    else if (this->type == BLN) {
        Var result;
        result.type = NTG;
        result.data.ntg = (long long int)this->data.bln;
        return result;
    }
    else if (this->type == STR) {
        try {
            Var result;
            result.type = NTG;
            result.data.ntg = stoll(this->str);
            return result;
        }
        catch (std::exception& err)
        {
            std::string temp = err.what();
            std::wstring error = LangLib::getTrans(MESSAGE1);
            error += L"ntg\n";
            throw std::wstring{ error };
        }
    }
    else if (this->type == NIL) {
        Var result = 0;
        return result;
    }
    else if (this->type == UNKNOWN) {
        Var result = 0;
        return result;
    }
    else if (this->type == ARR) {
        std::wstring error = LangLib::getTrans(MESSAGE2);
        error += L"ntg\n";
        throw std::wstring{ error };
    }
    else if (this->type == MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"ntg\n";
        throw std::wstring{ error };
    } else if (this->type == INST) {
        std::wstring error = LangLib::getTrans(MESSAGE10);
        error += L"ntg\n";
        throw std::wstring{ error };
    }
    return Var();
}

Var Var::toUNTG() const {
    if (this->type == NTG) {
        Var result;
        result.type = UNTG;
        result.data.untg = (unsigned long long int)this->data.ntg;
        return result;
    }
    else if (this->type == UNTG) {
        Var result;
        result.type = UNTG;
        result.data.untg = (unsigned long long int)this->data.untg;
        return result;
    }
    else if (this->type == DBL) {
        Var result;
        result.type = UNTG;
        result.data.untg = (unsigned long long int)this->data.dbl;
        return result;
    }
    else if (this->type == CHR) {
        Var result;
        result.type = UNTG;
        result.data.untg = (unsigned long long int)this->data.chr;
        return result;
    }
    else if (this->type == UCHR) {
        Var result;
        result.type = UNTG;
        result.data.untg = (unsigned long long int)this->data.uchr;
        return result;
    }
    else if (this->type == BLN) {
        Var result;
        result.type = UNTG;
        result.data.untg = (unsigned long long int)this->data.bln;
        return result;
    }
    else if (this->type == STR) {
        try {
            Var result;
            result.type = UNTG;
            result.data.untg = stoull(this->str);
            return result;
        }
        catch (std::exception& err)
        {
            std::string temp = err.what();
            std::wstring error = LangLib::getTrans(MESSAGE1);
            error += L"untg\n";
            throw std::wstring{ error };
        }
    }
    else if (this->type == NIL) {
        Var result = 0ULL;
        return result;
    }
    else if (this->type == UNKNOWN) {
        Var result = 0ULL;
        return result;
    }
    else if (this->type == ARR) {
        std::wstring error = LangLib::getTrans(MESSAGE2);
        error += L"UNTG\n";
        throw std::wstring{ error };
    }
    else if (this->type == MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"UNTG\n";
        throw std::wstring{ error };
    } else if (this->type == INST) {
        std::wstring error = LangLib::getTrans(MESSAGE10);
        error += L"UNTG\n";
        throw std::wstring{ error };
    }
    return Var();
}

Var Var::toDBL() const {
    if (this->type == NTG) {
        Var result;
        result.type = DBL;
        result.data.dbl = (long double)this->data.ntg;
        return result;
    }
    else if (this->type == UNTG) {
        Var result;
        result.type = DBL;
        result.data.dbl = (long double)this->data.untg;
        return result;
    }
    else if (this->type == DBL) {
        Var result;
        result.type = DBL;
        result.data.dbl = (long double)this->data.dbl;
        return result;
    }
    else if (this->type == CHR) {
        Var result;
        result.type = DBL;
        result.data.dbl = (long double)this->data.chr;
        return result;
    }
    else if (this->type == UCHR) {
        Var result;
        result.type = DBL;
        result.data.dbl = (long double)this->data.uchr;
        return result;
    }
    else if (this->type == BLN) {
        Var result;
        result.type = DBL;
        result.data.dbl = (long double)this->data.bln;
        return result;
    }
    else if (this->type == STR) {
        try {
            Var result;
            result.type = DBL;
            result.data.dbl = stold(this->str);
            return result;
        }
        catch (std::exception& err)
        {
            std::string temp = err.what();
            std::wstring error = LangLib::getTrans(MESSAGE1);
            error += L"dbl\n";
            throw std::wstring{ error };
        }
    }
    else if (this->type == NIL) {
        Var result = 0.0;
        return result;
    }
    else if (this->type == UNKNOWN) {
        Var result = 0.0;
        return result;
    }
    else if (this->type == ARR) {
        std::wstring error = LangLib::getTrans(MESSAGE2);
        error += L"DBL\n";
        throw std::wstring{ error };
    }
    else if (this->type == MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"DBL\n";
        throw std::wstring{ error };
    } else if (this->type == INST) {
        std::wstring error = LangLib::getTrans(MESSAGE10);
        error += L"DBL\n";
        throw std::wstring{ error };
    }
    return Var();
}

Var Var::toCHR() const {
    if (this->type == NTG) {
        Var result;
        result.type = CHR;
        result.data.chr = (char)this->data.ntg;
        return result;
    }
    else if (this->type == UNTG) {
        Var result;
        result.type = CHR;
        result.data.chr = (char)this->data.untg;
        return result;
    }
    else if (this->type == DBL) {
        Var result;
        result.type = CHR;
        result.data.chr = (char)this->data.dbl;
        return result;
    }
    else if (this->type == CHR) {
        Var result;
        result.type = CHR;
        result.data.chr = (char)this->data.chr;
        return result;
    }
    else if (this->type == UCHR) {
        Var result;
        result.type = CHR;
        result.data.chr = (char)this->data.uchr;
        return result;
    }
    else if (this->type == BLN) {
        Var result;
        result.type = CHR;
        result.data.chr = (char)this->data.bln;
        return result;
    }
    else if (this->type == STR) {
        try {
            Var result;
            result.type = CHR;
            result.data.chr = (char)stoll(this->str);
            return result;
        }
        catch (std::exception& err)
        {
            std::string temp = err.what();
            std::wstring error = LangLib::getTrans(MESSAGE1);
            error += L"chr\n";
            throw std::wstring{ error };
        }
    }
    else if (this->type == NIL) {
        Var result = (char)0;
        return result;
    }
    else if (this->type == UNKNOWN) {
        Var result = (char)0;
        return result;
    }
    else if (this->type == ARR) {
        std::wstring error = LangLib::getTrans(MESSAGE2);
        error += L"CHR\n";
        throw std::wstring{ error };
    }
    else if (this->type == MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"CHR\n";
        throw std::wstring{ error };
    } else if (this->type == CHR) {
        std::wstring error = LangLib::getTrans(MESSAGE10);
        error += L"NTG\n";
        throw std::wstring{ error };
    }

    return Var();
}

Var Var::toUCHR() const {
    if (this->type == NTG) {
        Var result;
        result.type = UCHR;
        result.data.uchr = (unsigned char)this->data.ntg;
        return result;
    }
    else if (this->type == UNTG) {
        Var result;
        result.type = UCHR;
        result.data.uchr = (unsigned char)this->data.untg;
        return result;
    }
    else if (this->type == DBL) {
        Var result;
        result.type = UCHR;
        result.data.uchr = (unsigned char)this->data.dbl;
        return result;
    }
    else if (this->type == CHR) {
        Var result;
        result.type = UCHR;
        result.data.uchr = (unsigned char)this->data.chr;
        return result;
    }
    else if (this->type == UCHR) {
        Var result;
        result.type = UCHR;
        result.data.uchr = (unsigned char)this->data.uchr;
        return result;
    }
    else if (this->type == BLN) {
        Var result;
        result.type = UCHR;
        result.data.uchr = (unsigned char)this->data.bln;
        return result;
    }
    else if (this->type == STR) {
        try {
            Var result;
            result.type = UCHR;
            result.data.uchr = (unsigned char)stoll(this->str);
            return result;
        }
        catch (std::exception& err)
        {
            std::string temp = err.what();
            std::wstring error = LangLib::getTrans(MESSAGE1);
            error += L"uchr\n";
            throw std::wstring{ error };
        }
    }
    else if (this->type == NIL) {
        Var result = (unsigned char)0;
        return result;
    }
    else if (this->type == UNKNOWN) {
        Var result = (unsigned char)0;
        return result;
    }
    else if (this->type == ARR) {
        std::wstring error = LangLib::getTrans(MESSAGE2);
        error += L"uchr\n";
        throw std::wstring{ error };

    }
    else if (this->type == MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"uchr\n";
        throw std::wstring{ error };
    } else if (this->type == INST) {
        std::wstring error = LangLib::getTrans(MESSAGE10);
        error += L"uchr\n";
        throw std::wstring{ error };
    }
    return Var();
}

Var Var::toBLN() const {
    if (this->type == NTG) {
        Var result;
        result.type = BLN;
        result.data.bln = (bool)this->data.ntg;
        return result;
    }
    else if (this->type == UNTG) {
        Var result;
        result.type = BLN;
        result.data.bln = (bool)this->data.untg;
        return result;
    }
    else if (this->type == DBL) {
        Var result;
        result.type = BLN;
        result.data.bln = (bool)this->data.dbl;
        return result;
    }
    else if (this->type == CHR) {
        Var result;
        result.type = BLN;
        result.data.bln = (bool)this->data.chr;
        return result;
    }
    else if (this->type == UCHR) {
        Var result;
        result.type = BLN;
        result.data.bln = (bool)this->data.uchr;
        return result;
    }
    else if (this->type == BLN) {
        Var result;
        result.type = BLN;
        result.data.bln = (bool)this->data.bln;
        return result;
    }
    else if (this->type == STR) {
        Var result;
        result.type = BLN;

        if (this->str == std::wstring_view(L"")) {
            result.data.bln = false;
        }
        else {
            result.data.bln = true;
        }

        return result;
    }
    else if (this->type == NIL) {
        Var result = (bool)0;
        return result;
    }
    else if (this->type == UNKNOWN) {
        Var result = (bool)0;
        return result;
    }
    else if (this->type == ARR) {
        Var result;
        result.type = BLN;

        if (this->arr.empty()) {
            result.data.bln = false;
        }
        else {
            result.data.bln = true;
        }

        return result;
    }
    else if (this->type == MAP) {
        Var result;
        result.type = BLN;

        if (this->mp.empty()) {
            result.data.bln = false;
        }
        else {
            result.data.bln = true;
        }

        return result;
    } else if (this->type == INST) {
        std::wstring error = LangLib::getTrans(MESSAGE10);
        error += L"bln\n";
        throw std::wstring{ error };
    }
    return Var();
}

Var Var::toSTR() const {
    if (this->type == NTG) {
        Var result;
        result.type = STR;
        result.str = std::to_wstring(this->data.ntg);
        return result;
    }
    else if (this->type == UNTG) {
        Var result;
        result.type = STR;
        result.str = std::to_wstring(this->data.untg);
        return result;
    }
    else if (this->type == DBL) {
        Var result;
        result.type = STR;
        result.str = std::to_wstring(this->data.dbl);
        return result;
    }
    else if (this->type == CHR) {
        Var result;
        result.type = STR;
        result.str = std::to_wstring(this->data.chr);
        return result;
    }
    else if (this->type == UCHR) {
        Var result;
        result.type = STR;
        result.str = std::to_wstring(this->data.uchr);
        return result;
    }
    else if (this->type == BLN) {
        Var result;
        result.type = STR;

        if (this->data.bln) {
            result.str = L"true";
        }
        else {
            result.str = L"false";
        }

        return result;
    }
    else if (this->type == STR) {
        Var result;
        result.type = STR;
        result.str = this->str;
        return result;
    }
    else if (this->type == NIL) {
        Var result = L"nil";
        return result;
    }
    else if (this->type == UNKNOWN) {
        Var result = L"";
        return result;
    }
    else if (this->type == ARR) {
        int size = (int)this->arr.size();
        std::wstring result = L"";
        for (int i = 0; i < size; ++i) {
            if (i == 0) {
                result += L'[';
                result += this->arr[i].toSTR().getWStr();
                if (size != 1) {
                    result += L", ";
                }
                else {
                    result += L"]";
                }
            }
            else if (i + 1 == size) {
                result += this->arr[i].toSTR().getWStr();
                result += L']';
            }
            else {
                result += this->arr[i].toSTR().getWStr();
                result += L", ";
            }
        }
        if (result == std::wstring_view(L"")) {
            return Var(L"[]");
        }
        else {
            return Var(result);
        }
    }
    else if (this->type == MAP) {
        std::wstring str = L"{";
        for (const auto& [key, val] : this->mp) {
            str += L"\"" + key + L"\": " + val.toSTR().getWStr() + L", ";
        }
        if(str != L"{") {
            str.pop_back();
            str.pop_back();
        }
        str+= L"}";
        return Var(str);
    } else if (this->type == INST) {
        std::wstring result = L"";
        int size_i = (int)this->instructions.size();
        for( int i = 0; i < size_i; ++i) {
            result += this->instructions[i].as_string;
            if(i < size_i - 1) {
                if(instructions[i].as_string.at(result.size() - 1) != L';') {
                    result += L"; ";
                } else {
                    if(i != size_i - 1) {
					    result += L" ";
				    }
                }
            }
        }
        return Var(result);
    }
    return Var();
}

Var Var::toARR() const {
    if (this->type == NTG) {
        Var result;
        result.type = ARR;
        result.arr.emplace_back(*this);
        return result;
    }
    else if (this->type == UNTG) {
        Var result;
        result.type = ARR;
        result.arr.emplace_back(*this);
        return result;
    }
    else if (this->type == DBL) {
        Var result;
        result.type = ARR;
        result.arr.emplace_back(*this);
        return result;
    }
    else if (this->type == CHR) {
        Var result;
        result.type = ARR;
        result.arr.emplace_back(*this);
        return result;
    }
    else if (this->type == UCHR) {
        Var result;
        result.type = ARR;
        result.arr.emplace_back(*this);
        return result;
    }
    else if (this->type == BLN) {
        Var result;
        result.type = ARR;
        result.arr.emplace_back(*this);
        return result;
    }
    else if (this->type == STR) {
        Var result;
        result.type = ARR;
        result.arr.emplace_back(*this);
        return result;
    }
    else if (this->type == NIL) {
        Var result;
        result.type = ARR;
        result.arr.emplace_back(*this);
        return result;
    }
    else if (this->type == UNKNOWN) {
        Var result;
        result.type = ARR;
        result.arr.emplace_back(*this);
        return result;
    }
    else if (this->type == ARR) {
        return *this;
    }
    else if (this->type == MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"arr\n";
        throw std::wstring{ error };
    } else if (this->type == INST) {
        std::wstring error = LangLib::getTrans(MESSAGE10);
        error += L"arr\n";
        throw std::wstring{ error };
    }
    return Var();
    
}

Var Var::toINST() const {
    if (this->type == STR) {
        std::vector<Instruction> temp;
        Parser p;
        temp = p.parse(this->str);

        Var result;
        result.type = INST;
        result.instructions.reserve(255);
        
        int size_i = (int)temp.size();
        for(int i = 0; i < size_i; ++i) {
            result.instructions.emplace_back(temp[i]);
        }

        return result;
    } else if (this->type == INST) {
        return *this;
    } else {
        std::wstring error = LangLib::getTrans(L"Только тип STR можно привести к типу INST\n");
    }
    return Var();
}


void Var::print() {
    switch (this->type) {
    case UNTG:
        std::wcout << this->data.untg;
        break;
    case NTG:
        std::wcout << this->data.ntg;
        break;
    case DBL:
        std::wcout << this->data.dbl;
        break;
    case CHR:
        std::wcout << this->data.chr;
        break;
    case UCHR:
        std::wcout << this->data.uchr;
        break;
    case BLN:
        if (this->data.bln) {
            std::wcout << L"true";
        }
        else {
            std::wcout << L"false";
        }
        break;
    case STR:
        std::wcout << this->str;
        break;
    case NIL:
        std::wcout << L"nil";
        break;
    case ARR:
        for (int i = 0; i < (int)this->arr.size(); ++i)
            std::wcout << i << L":\t" << this->arr[i] << L"\n";
        break;
    case MAP:
        for (const auto& elem : this->mp)
        {
            std::wcout << "\"" << elem.first << "\":\t " << elem.second << "\t";
        }
        break;
    case INST: {
        std::wstring result = L"";
        int size_i = (int)this->instructions.size();
        for( int i = 0; i < size_i; ++i) {
            result += this->instructions[i].as_string;
            if(i < size_i - 1) {
                if(instructions[i].as_string.at(result.size() - 1) != L';') {
                    result += L"; ";
                } else {
                    if(i != size_i - 1) {
					    result += L" ";
				    }
                }
            }
        }
        std::wcout << result;
        break;
    }
    default:
        std::wcout << L"unknown";
    }
}

std::wstring Var::typeOf() {
    std::wstring result = L"";
    switch (this->type) {
    case UNTG:
        result = L"untg";
        return result;
        break;
    case NTG:
        result = L"ntg";
        return result;
        break;
    case DBL:
        result = L"dbl";
        return result;
        break;
    case CHR:
        result = L"chr";
        return result;
        break;
    case UCHR:
        result = L"uchr";
        return result;
        break;
    case BLN:
        result = L"bln";
        return result;
        break;
    case STR:
        result = L"str";
        return result;
        break;
    case NIL:
        result = L"nil";
        return result;
        break;
    case ARR:
        result = L"arr";
        return result;
        break;
    case MAP:
        result = L"map";
        return result;
    case INST:
        result = L"inst";
        return result;
    default:
        result = L"unknown";
        return result;
    }
}

Var& Var::operator[](int ind) {
    if (this->type == ARR) {
        try {
            return this->arr.at(ind);
        }
        catch (std::exception& err)
        {
            std::string temp = err.what();
            throw std::wstring{ std::to_wstring(ind) + L": " + LangLib::getTrans(MESSAGE4) };
        }
    }
    else if (this->type == STR) {
        try {
            std::wstring str(1, this->str.at(ind));
            Var* chr = new Var(str);
            return *chr;
        }
        catch (std::exception& err)
        {
            std::string temp = err.what();
            throw std::wstring{ std::to_wstring(ind) + L": " + LangLib::getTrans(MESSAGE4) };
        }
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE5);
        error += L"str, arr, map\n";
        throw std::wstring{ error };
    }
}
Var& Var::operator[](const wchar_t* str) {
    try {
        if (this->type == MAP) {
            return this->mp.at(str);
        }
        else {
            std::wstring error = LangLib::getTrans(MESSAGE5);
            error += L"str, arr, map\n";
            throw std::wstring{ error };
        }
    }
    catch (std::exception& err) {
        std::string temp = err.what();
        throw std::wstring{ std::wstring(str) + L": " + LangLib::getTrans(MESSAGE6) };
    }
}
Var& Var::operator[](std::wstring str) {
    try {
        if (this->type == MAP) {
            return this->mp.at(str);
        }
        else {
            std::wstring error = LangLib::getTrans(MESSAGE5);
            error += L"str, arr, map\n";
            throw std::wstring{ error };
        }
    }
    catch (std::exception& err) {
        std::string temp = err.what();
        throw std::wstring{ str + L": " + LangLib::getTrans(MESSAGE6) };
    }
}
Var& Var::operator[](Var v) {
    if (v.type == NTG || v.type == UNTG) {
        if (this->type == ARR) {
            try {
                return this->arr.at(v.toNTG().getInt());
            }
            catch (std::exception& err)
            {
                std::string temp = err.what();
                throw std::wstring{ v.toSTR().getWStr() + L": " + LangLib::getTrans(MESSAGE4) };
            }
        }
        else if (this->type == STR) {
            try {
                std::wstring str(1, this->str.at(v.toNTG().getInt()));
                Var* chr = new Var(str);
                return *chr;
            }
            catch (std::exception& err)
            {
                std::string temp = err.what();
                throw std::wstring{ v.toSTR().getWStr() + L": " + LangLib::getTrans(MESSAGE4) };
            }
        }
        else {
            std::wstring error = LangLib::getTrans(MESSAGE5);
            error += L"str, arr, map\n";
            throw std::wstring{ error };
        }
    }
    else if (v.type == STR) {
        try {
            if (this->type == MAP) {
                return this->mp.at(v.getWStr());
            }
            else {
                std::wstring error = LangLib::getTrans(MESSAGE5);
                error += L"STR, ARR, MAP\n";
                throw std::wstring{ error };
            }
        }
        catch (std::exception& err) {
            std::string temp = err.what();
            throw std::wstring{ v.toSTR().getWStr() + L": " + LangLib::getTrans(MESSAGE6) };
        }
    }
    else {
        std::wstring error = LangLib::getTrans(L"Взятие значения по индексу использует только следующие типы: ");
        error += L"NTG, UNTG, STR\n";
        throw std::wstring{ error };
    }
    Var* val = new Var(v);
    return *val;
}

Var Var::len() const {
    if (this->type == STR) {
        return Var(this->str.length());
    }
    else if (this->type == ARR) {
        return Var(this->arr.size());
    }
    else if (this->type == MAP) {
        return Var(this->mp.size());
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str, arr, map\n";
        throw std::wstring{ error };
    }
}

Var Var::rev() const {
    if (this->type == STR) {
        std::wstring str = this->str;
        reverse(str.begin(), str.end());
        return Var(str);
    }
    else if (this->type == ARR) {
        
        std::vector<Var> v = this->arr;
        if(this->arr.size() < 1000) {
            v.reserve(1000);
        }
        reverse(v.begin(), v.end());
        Var result;
        result.type = ARR;
        result.arr = v;
        return result;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str, arr\n";
        throw std::wstring{ error };
    }
}

Var Var::slice(const int &x, const int &y) const {
    if (this->type == STR) {
        return Var(this->str.substr(x, y));
    }
    else if (this->type == ARR) {
        auto start = arr.begin() + x;
        auto end = arr.begin() + x + y;
        std::vector<Var> result(y);
        if(result.capacity() < 1000) {
            result.reserve(1000);
        }
        copy(start, end, result.begin());
        
        Var res;
        res.type = ARR;
        res.arr = result;

        return res;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str, arr\n";
        throw std::wstring{ error };
    }
}
Var Var::slice(const Var &x, const Var &y) const {
    if (this->type == STR) {
        return this->slice((int)x.data.ntg, (int)y.data.ntg);
    }
    else if (this->type == ARR) {
        return this->slice((int)x.data.ntg, (int)y.data.ntg);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str, arr\n";
        throw std::wstring{ error };
    }
}

Var Var::sortarr(const std::wstring &type) const{
    if (type != std::wstring_view(L"asc")
		&& type != std::wstring_view(L"desc")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сортировки неизвестен\n")};
	}

    std::vector<Var> clear_arr = this->arr;

    if (type == std::wstring_view(L"asc")) {
		sort(clear_arr.begin(), clear_arr.end());
	}
	else if (type == std::wstring_view(L"desc")) {
		sort(clear_arr.begin(), clear_arr.end(), std::greater<Var>());
	}
    return Var(clear_arr);
}

Var Var::eq(const std::wstring &type, const Var &b) const {
    if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}

    return eq_recursive(type, *this, b);
}

Var Var::eq_recursive(const std::wstring &type, const Var &a, const Var &b) const {
    if (a.type == ARR && b.type == ARR) {
        const std::vector<Var>& arr_a = a.arr;
        const std::vector<Var>& arr_b = b.arr;

        int size_a = (int)arr_a.size();
        int size_b = (int)arr_b.size();

        if (size_a != size_b) { Var(false); }

        bool is_equal = true;
        for (int i = 0; i < size_a; ++i) {
            if (this->eq_recursive(type, arr_a[i], arr_b[i]) == false) {
                is_equal = false;
                break;
            }
        }
        return Var(is_equal);
    } else if (a.type == MAP && b.type == MAP) {
        const std::unordered_map<std::wstring, Var> map_a = a.mp;
        const std::unordered_map<std::wstring, Var>& map_b = b.mp;

        int size_a = (int)map_a.size();
        int size_b = (int)map_b.size();

        if (size_a != size_b) { Var(false); }

        bool is_equal = true;
        for (const auto& [key, val] : map_a) {
            try {
                if (this->eq_recursive(type, map_a.at(key), map_b.at(key)) == false) {
                    is_equal = false;
                    break;
                }
            } catch(std::exception& err) {
                std::string temp = err.what();
                return Var(false);
            }
        }
        return Var(is_equal);
    }
    else if ((a.type == ARR && b.type != ARR) || (a.type != ARR && b.type == ARR)) {
        return Var(false);
    }  else if ((a.type == MAP && b.type != MAP) || (a.type != MAP && b.type == MAP)) {
        return Var(false);
    }
    else {
        if(type == std::wstring_view(L"strict")) {
            if (a.type == b.type && a == b) { return Var(true); }
            else { return Var(false); }
        } else {
            if (a == b) { return Var(true); }
            else { return Var(false); }
        }
    }
    return Var(false);
}

Var Var::uniq(const std::wstring &type) const {
    if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}
    
    std::vector<Var> result;
    result.reserve(1000);
    std::vector<Var> arr;
    if(this->type == ARR) {
        arr = this->arr;
    } else if(this->type == MAP) {
        const std::unordered_map<std::wstring, Var>& map = this->mp;
        for (const auto& [key, val] : map) {
           arr.emplace_back(val);
        }
    } else {
        arr =this->toARR().arr;
    }

    if (type == std::wstring_view(L"strict")) {
        int size = (int)arr.size();
        for (int i = 0; i < size; ++i) {
            const Var& arr_i = arr[i];
            bool is_unique = true;
            for (int j = i; j < size; ++j) {
                const Var& arr_j = arr[j];
                if (j == i) { continue; }
                if (arr_i.type == arr_j.type && arr_i == arr_j) {
                    if (arr_i.type == ARR && arr_j.type == ARR) {
                        is_unique = !arr_i.eq(type, arr_j).data.bln;
                    }
                    else {
                        is_unique = false;
                    }
                    break;
                }
            }
            if (is_unique) {
                result.emplace_back(arr_i);
            }
        }
    } else {
        int size = (int)arr.size();
        for (int i = 0; i < size; ++i) {
            const Var& arr_i = arr[i];
            bool is_unique = true;
            for (int j = i; j < size; ++j) {
                const Var& arr_j = arr[j];
                if (j == i) { continue; }
                if (arr_i.eq(type, arr_j).data.bln) {
                    is_unique = false;
                    break;
                }
            }
            if (is_unique) {
                result.emplace_back(arr_i);
            }
        }
    }

    return Var(result);
 }

 Var Var::in(const std::wstring &type, const Var &b) const {
    if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}

    if(this->type != MAP) {
         const std::vector<Var>& arr = this->type != ARR ? this->toARR().arr : this->arr;

        int size = (int)arr.size();
        int result = -1;

        for (int i = 0; i < size; ++i) {
            if (arr[i].eq(type, b).data.bln) {
                result = i;
                break;
            }
        }
        return Var(result);
    } else {
        const std::unordered_map<std::wstring, Var>&  map = this->mp;
        Var result = -1;

        for (const auto& [key, val] : map) {
            if (map.at(key).eq(type, b).data.bln) {
                result = key;
                break;
            }
        }
        return result;
    }
}

Var Var::inall(const std::wstring &type, const Var &b) const {
    if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}
    if(this->type != MAP) {
        const std::vector<Var>& arr = this->type != ARR ? this->toARR().arr : this->arr;

        int size = (int)arr.size();

        std::vector<Var> result;
        result.reserve(1000);

        for (int i = 0; i < size; ++i) {
            if (arr[i].eq(type, b).data.bln) {
                result.emplace_back(Var(i));
            }
        }
        return Var(result);
    } else {
        const std::unordered_map<std::wstring, Var>&  map = this->mp;
        std::vector<Var> result;
        result.reserve(1000);

        for (const auto& [key, val] : map) {
            if (map.at(key).eq(type, b).data.bln) {
                result.emplace_back(Var(key));
            }
        }
        return result;
    }
}

Var Var::rin(const std::wstring &type, const Var &b, std::vector<Var> result) const {
    if(result.capacity() < 1000) {
        result.reserve(1000);
    }
    if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}

    rin_recursive(type, *this, b, result);
    if(result.size() > 0) {
        result.pop_back();
    }
    return Var(result);
}

Var Var::rin_recursive(const std::wstring &type, const Var &a, const Var &b, std::vector<Var> &result) const {

    if (a.type != MAP) {
        const std::vector<Var>& arr = a.type != ARR ? a.toARR().arr : a.arr;
        int size = (int)arr.size();

        for (int i = 0; i < size; ++i) {
            const Var& arr_i = arr[i];
            if (arr_i.type == ARR || arr_i.type == MAP) {
                if (arr_i.eq(type, b).data.bln) {
                    result.emplace_back(Var(i));
                    result.emplace_back(Var(true));
                    break;
                }
                else {
                    result.emplace_back(Var(i));
                    result = this->rin_recursive(type, arr_i, b, result).arr;
                    int size = (int)result.size();
                    if (result[(long long int)size - 1].type == BLN && result[(long long int)size - 1].data.bln == true) {
                        break;
                    }
                    else {
                        result.pop_back();
                    }
                }
            }
            else {
                if (arr_i.eq(type, b).data.bln) {
                    result.emplace_back(Var(i));
                    result.emplace_back(Var(true));
                    break;
                }
            }
        }
	}
	else {
        const std::unordered_map<std::wstring, Var>&  map = a.mp;

        for (const auto& [key, val] : map) {
            const Var& arr_i = val;
            if (arr_i.type == ARR || arr_i.type == MAP) {
                if (arr_i.eq(type, b).getBool()) {
                    result.emplace_back(Var(key));
                    result.emplace_back(Var(true));
                    break;
                }
                else {
                    result.emplace_back(Var(key));
                    result = this->rin_recursive(type, arr_i, b, result).arr;
                    int size = (int)result.size();
                    if (result[(long long int)size - 1].type == BLN && result[(long long int)size - 1].data.bln == true) {
                        break;
                    }
                    else {
                        result.pop_back();
                    }
                }
            }
            else {
                if (arr_i.eq(type, b).getBool()) {
                    result.emplace_back(Var(key));
                    result.emplace_back(Var(true));
                    break;
                }
            }
        }
	}
    return Var(result);
}

Var Var::rinall(const std::wstring &type, const Var &b) const{
    if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}

    std::vector<Var> all_results;
    all_results.reserve(1000);
    this->rinall_recursive(type, *this, b, &all_results);

    if (all_results.size() == 0) {
        return Var(all_results);
    }
    else {
        Var result = Var(std::vector<Var>());
        result.arr.reserve(1000);
        int size = (int)all_results.size();
        for (int i = 0; i < size; ++i) {
            all_results[i].popb();
            result.pushb(all_results[i]);
        }
        return result;
    }
}

Var Var::rinall_recursive(const std::wstring &type, const Var &a, const Var &b, std::vector<Var>* all_results, std::vector<Var> result) const {
    if (a.type != MAP) {
        const std::vector<Var>& arr = a.type != ARR ? a.toARR().arr : a.arr;
        int size = (int)arr.size();
        for (int i = 0; i < size; ++i) {
            const Var& arr_i = arr[i];
            if (arr_i.type == ARR || arr_i.type == MAP) {
                if (arr_i.eq(type, b).data.bln) {
                    result.emplace_back(Var(i));
                    result.emplace_back(Var(true));
                    Var res = Var(result);
                    all_results->emplace_back(res);
                    result.pop_back();
                    result.pop_back();
                }
                else {
                    result.emplace_back(Var(i));
                    result = this->rinall_recursive(type, arr_i, b, all_results, result).arr;
                    int size = (int)result.size();
                    if (result[(long long int)size - 1].type == BLN && result[(long long int)size - 1].data.bln == true) {
                        Var res = Var(result);
                        all_results->emplace_back(res);
                    }
                    else {
                        result.pop_back();
                    }
                }
            }
            else {
                if (arr_i.eq(type, b).getBool()) {
                    result.emplace_back(Var(i));
                    result.emplace_back(Var(true));
                    Var res = Var(result);
                    all_results->emplace_back(res);
                    result.pop_back();
                    result.pop_back();
                }
            }
        }
        return Var(result);
    }
    else {
        const std::unordered_map<std::wstring, Var>&  map = a.mp;

        for (const auto& [key, val] : map) {
            if (val.type == ARR || val.type == MAP) {
                if (val.eq(type, b).data.bln) {
                    result.emplace_back(Var(key));
                    result.emplace_back(Var(true));
                    Var res = Var(result);
                    all_results->emplace_back(res);
                    result.pop_back();
                    result.pop_back();
                }
                else {
                    result.emplace_back(Var(key));
                    result = this->rinall_recursive(type, val, b, all_results, result).arr;
                    int size = (int)result.size();
                    if (result[(long long int)size - 1].type == BLN && result[(long long int)size - 1].data.bln == true) {
                        Var res = Var(result);
                        all_results->emplace_back(res);
                    }
                    else {
                        result.pop_back();
                    }
                }
            }
            else {
                if (val.eq(type, b).getBool()) {
                    result.emplace_back(Var(key));
                    result.emplace_back(Var(true));
                    Var res = Var(result);
                    all_results->emplace_back(res);
                    result.pop_back();
                    result.pop_back();
                }
            }
        }
        return Var(result);
    }
}

Var Var::intersect(const std::wstring &type, const Var &b) const {
    if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}
    const std::vector<Var>& arr = this->type != ARR ? this->toARR().uniq(type).arr : this->uniq(type).arr;
    const std::vector<Var>& arr_b = b.type != ARR ? b.toARR().arr : b.arr;

    Var result = Var(std::vector<Var>());
    if(result.arr.capacity() < 1000) {
        result.arr.reserve(1000);
    }
        
    int size = (int)arr.size();
    int size_b = (int)arr_b.size();

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size_b; ++j) {
            if(arr[i].eq(type, arr_b[j]).data.bln) {
                result.pushb(arr[i]);
                 break;
            }
        }
    }

    return result;
}

Var Var::notintersect(const std::wstring &type, const Var &b) const {
     if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}
    const std::vector<Var>& arr = this->type != ARR ? this->toARR().uniq(type).arr : this->uniq(type).arr;
    const std::vector<Var>& arr_b = b.type != ARR ? b.toARR().uniq(type).arr : b.uniq(type).arr;


    Var result = Var(std::vector<Var>());
    if(result.arr.capacity() < 1000) {
        result.arr.reserve(1000);
    }

    int size = (int)arr.size();
    int size_b = (int)arr_b.size();

    for(int i = 0; i < size; ++i) {
        bool is_unique = true;
        for(int j = 0; j < size_b; ++j) {
            if(arr[i].eq(type, arr_b[j]).data.bln) {
                is_unique = false;
                break;
            }
        }
        if(is_unique) {
            result.pushb(arr[i]);
        }
    }

    for(int i = 0; i < size_b; ++i) {
        bool is_unique = true;
        for(int j = 0; j < size; ++j) {
            if(arr_b[i].eq(type, arr[j]).data.bln) {
                is_unique = false;
                break;
            }
        }
        if(is_unique) {
            result.pushb(arr_b[i]);
        }
    }

    return result;
}

Var Var::kvintersect(const std::wstring &type, const Var &b) const {
    if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}

    if(this->type != MAP || b.type != MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"map\n";
        throw std::wstring{ error };
    }

    Var result = Var(std::unordered_map<std::wstring, Var>());
    if(result.mp.bucket_count() < 1000) {
        result.mp.reserve(1000);
    }

    for (const auto& [key, val] : this->mp) {
        for (const auto& [key_b, val_b] : b.mp) {
            if(key == key_b && val.eq(type, val_b).data.bln) {
                result.push(key, val);
            }
        }
    }

    return result;
}

Var Var::kvnotintersect(const std::wstring &type, const Var &b) const {
     if (type != std::wstring_view(L"strict")
		&& type != std::wstring_view(L"dynamic")) {
		throw std::wstring{ type + LangLib::getTrans(L": Способ сравнения неизвестен\n") };
	}

    if(this->type != MAP || b.type != MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"map\n";
        throw std::wstring{ error };
    }

    Var result = Var(std::unordered_map<std::wstring, Var>());
    if(result.mp.bucket_count() < 1000) {
        result.mp.reserve(1000);
    }

    for (const auto& [key, val] : this->mp) {
        bool is_unique = true;
        for (const auto& [key_b, val_b] : b.mp) {
            if(key == key_b && val.eq(type, val_b).data.bln) {
                is_unique = false;
                break;
            }
        }
        if(is_unique) {
            result.push(key, val);
        }
    }

    for (const auto& [key, val] : b.mp) {
    bool is_unique = true;
        for (const auto& [key_b, val_b] : this->mp) {
            if(key == key_b && val.eq(type, val_b).data.bln) {
                is_unique = false;
                break;
            }
        }
        if(is_unique) {
            result.push(key, val);
        }
    }
    
    return result;
}

Var Var::arrtostr(const Var &delim) const {
    std::wstring str = L"";
    std::wstring delimiter = delim.toSTR().getWStr();
    const std::vector<Var>& arr = this->arr;

    int size = (int)arr.size();
    for(int i = 0; i < size; ++i) {
        if(i < size - 1) {
            str += arr[i].toSTR().getWStr() + delimiter;
        }
        else {
            str += arr[i].toSTR().getWStr();
        }
    }
    return Var(str);
}

Var Var::sum() const{
    double result = 0.0;
    const std::vector<Var>& arr = this->arr;

    int size = (int)arr.size();
    for(int i = 0; i < size; ++i) {
        result += arr[i].toDBL().getDouble();
    }
    return Var(result);
}

Var Var::avg() const {
    double result = 0.0;
    const std::vector<Var>& arr = this->arr;

    int size = (int)arr.size();
    for(int i = 0; i < size; ++i) {
        result += arr[i].toDBL().getDouble();
    }
    if(size > 0) {
        result /= (double)size;
    }
    return Var(result);
}

Var Var::min() const {
    double result = 0.0;
    const std::vector<Var>& arr = this->arr;

    int size = (int)arr.size();
    if(size > 0) {
        result = arr[0].toDBL().getDouble();
    }
    for(int i = 0; i < size; ++i) {
        double val = arr[i].toDBL().getDouble();
        if(val < result) {
            result = val;
        }
    }
    return Var(result);
}

Var Var::max() const {
    double result = 0.0;
    const std::vector<Var>& arr = this->arr;
   
    int size = (int)arr.size();
    if(size > 0) {
        result = arr[0].toDBL().getDouble();
    }
    for(int i = 0; i < size; ++i) {
        double val = arr[i].toDBL().getDouble();
        if(val > result) {
            result = val;
        }
    }
    return Var(result);
}

Var Var::range() const {;
    Var maxval = this->max();
    Var minval = this->min();
    return maxval - minval;
}

Var Var::median() const {
    const std::vector<Var>& arr = this->sortarr(L"asc").arr;
    int size = (int)arr.size();
    if(size == 0) {
        return Var(0.0);
    }
    if(size % 2 == 1) {
        return arr[(int)(size / 2)].toDBL(); 
    } else {
        Var a = arr[(int)(size / 2)];
        Var b = arr[(int)(size / 2) - 1];
        return (a + b) / Var(2.0);
    }
}

Var Var::mode() const {
    std::unordered_map<std::wstring, int> freq;
    freq.reserve(1000);
    std::vector<Var> result;
    result.reserve(1000);
    int max_count = 0;
    if(this->arr.size() == 0) {
        return Var(0.0);
    }
    for (const auto& val : this->arr) {
        int count = ++freq[val.toSTR().str];
        if (count > max_count) {
            max_count = count;
        }
    }

    for (const auto& [val, count] : freq) {
        if (count == max_count) {
            result.push_back(val);
        }
    }

    return Var(result);
}

Var Var::stddev() const {
    double result = 0.0;
    if(this->arr.size() == 0) {
        return Var(result);
    }
    double mean = this->avg().data.dbl;

    double sq_sum = 0.0;
    for (const Var& v : this->arr) {
        double diff = v.toDBL().data.dbl - mean;
        sq_sum += diff * diff;
    }

    result = std::sqrt(sq_sum / arr.size());
    return Var(result);
}

 Var Var::kexist(const Var &key) const {
    if(this->type != MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"map\n";
        throw std::wstring{ error };
    }
    if (this->mp.find(key.toSTR().getWStr()) == this->mp.end()) {
        return Var(false);
    } else {
        return Var(true);
    }
 }

Var Var::in(Var sent) const {
    if(this->type == STR) {
        bool exists = this->str.find(sent.str) != std::wstring::npos;
        return Var(exists);
    } 
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}
Var Var::in(const wchar_t* sent) const {
    if (this->type == STR) {
        bool exists = this->str.find(sent) != std::wstring::npos;
        return Var(exists);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}
Var Var::in(std::wstring sent) const {
    if (this->type == STR) {
        bool exists = this->str.find(sent) != std::wstring::npos;
        return Var(exists);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}



Var Var::ltrim() const {
    if (this->type == STR) {
        std::wstring str = this->str;
        str.erase(0, str.find_first_not_of(' '));
        return Var(str);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}
Var Var::rtrim() const {
    if (this->type == STR) {
        std::wstring str = this->str;
        str.erase(str.find_last_not_of(' ') + 1);
        return Var(str);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}
Var Var::trim() const {
    if (this->type == STR) {
        std::wstring str = this->str;
        str.erase(0, str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
        return Var(str);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}

Var Var::repl(Var substr, Var newsubstr) const {
    if (this->type == STR) {
        std::wstring s = this->getWStr();
        size_t pos = 0;
        while ((pos = s.find(substr.str, pos)) != std::wstring::npos) {
            s.replace(pos, substr.str.length(), newsubstr.str);
            pos += newsubstr.str.length();
        }
        return Var(s);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}
Var Var::repl(const wchar_t* substr, const wchar_t* newsubstr) const {
    std::wstring ss = substr;
    std::wstring nss = newsubstr;
    if (this->type == STR) {
        std::wstring s = this->getWStr();
        size_t pos = 0;
        while ((pos = s.find(ss, pos)) != std::wstring::npos) {
            s.replace(pos, ss.length(), nss);
            pos += nss.length();
        }
        return Var(s);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}
Var Var::repl(std::wstring substr, const std::wstring newsubstr) const {
    if (this->type == STR) {
        std::wstring s = this->getWStr();
        size_t pos = 0;
        while ((pos = s.find(substr, pos)) != std::wstring::npos) {
            s.replace(pos, substr.length(), newsubstr);
            pos += newsubstr.length();
        }
        return Var(s);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}

Var Var::split(Var delim) const {
    if (this->type == STR) {
        std::vector<Var> tokens;
        tokens.reserve(1000);
        size_t pos = 0;
        std::wstring str = this->str;
        while (pos < str.length())
        {
            size_t next = str.find(delim.str, pos);
            if (next == std::string::npos)
            {
                next = str.length();
            }

            Var token = str.substr(pos, next - pos);

            if (!token.str.empty())
            {
                tokens.emplace_back(token);
            }
            pos = next + delim.len().getUInt();
        }

        Var result;
        result.type = ARR;
        result.arr = tokens;
        return result;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}
Var Var::split(std::wstring delim) const {
    return split(Var(delim));
}
Var Var::split(const wchar_t* delim) const {
    return split(Var(delim));
}

Var Var::join(Var delim) {
    if (this->type == ARR) {
        std::wstring str;
        for (int i = 0; i < (int)this->arr.size(); ++i) {
            str += this->arr[i].toSTR().getWStr();
            if (i != (int)this->arr.size() - 1) {
                str += delim.getWStr();
            }
        }
        return Var(str);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr\n";
        throw std::wstring{ error };
    }
}
Var Var::join(std::wstring delim) {
    return this->join(Var(delim));
}
Var Var::join(const wchar_t* delim) {
    return this->join(Var(delim));
}

Var Var::upper() const {
    if (this->type == STR) {
        std::wstring str = this->str;
        for (auto& c : str) c = toupper(c);
        return Var(str);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}

Var Var::lower() const {
    if (this->type == STR) {
        std::wstring str = this->str;
        for (auto& c : str) c = tolower(c);
        return Var(str);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"str\n";
        throw std::wstring{ error };
    }
}

void Var::pushb(const Var &v) {
    if (this->type == ARR) {
        this->arr.emplace_back(v);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr\n";
        throw std::wstring{ error };
    }
}

Var Var::popb() {
    if (this->type == ARR) {
        Var result;
        result = arr.back();
        this->arr.pop_back();
        return result;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr\n";
        throw std::wstring{ error };
    }
}

void Var::pushf(const Var &val) {
    if (this->type == ARR) {
        this->arr.insert(this->arr.begin(), val);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr\n";
        throw std::wstring{ error };
    }
}

Var Var::popf() {
    if (this->type == ARR) {
        Var result;
        result = this->arr[0];
        this->arr.erase(this->arr.begin());
        return result;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr\n";
        throw std::wstring{ error };
    }
}

void Var::push(const Var &key, const Var &val) {
    if (this->type == MAP) {
        this->mp.insert({key.toSTR().getWStr(), val});
    } else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"map\n";
        throw std::wstring{ error };
    }
}

void Var::clear() {
    if (this->type == ARR) {
        this->arr.clear();
    }
    else if (this->type == MAP) {
        this->mp.clear();
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr, map\n";
        throw std::wstring{ error };
    }

}

void Var::erase(const int &x) {
    if (this->type == ARR) {
        std::vector<Var>::iterator it;
        it = this->arr.begin() + x;
        this->arr.erase(it);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr\n";
        throw std::wstring{ error };
    }
}
Var Var::erase(const Var &x) {
    if (this->type == ARR) {
        try {
            Var result = this->arr.at((int)x.toNTG().getInt());
            this->erase((int)x.toNTG().getInt());
            return result;
        }
        catch (std::out_of_range& ex) {
            std::string temp = ex.what();
            throw std::wstring{ x.toSTR().getWStr() + LangLib::getTrans(L": ") + LangLib::getTrans(MESSAGE4) };
        }
    }
    else if (this->type == MAP) {
        try {
            Var result = this->mp.at(x.toSTR().getWStr());
            this->erase(x.toSTR().getWStr());
            return result;
        }
        catch (std::out_of_range& ex) {
            std::string temp = ex.what();
            throw std::wstring{ x.toSTR().getWStr() + LangLib::getTrans(L": ") + LangLib::getTrans(MESSAGE6) };
        }
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr, map\n";
        throw std::wstring{ error };
    }
}
void Var::erase(const std::wstring &x) {
    if (this->type == MAP) {
        this->mp.erase(x);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"map\n";
        throw std::wstring{ error };
    }
}
void Var::erase(const wchar_t* x) {
    if (this->type == MAP) {
        this->mp.erase(x);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"map\n";
        throw std::wstring{ error };
    }
}

void Var::insert_vector(const Var &x, const Var &val) {
    if (this->type == ARR) {
        if (x < 0 || x > arr.size()) {
            throw std::wstring{ x.toSTR().getWStr() + LangLib::getTrans(L": ") + LangLib::getTrans(MESSAGE4) };
        }
        this->arr.insert(this->arr.begin() + x.toNTG().getInt(), val);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr\n";
        throw std::wstring{ error };
    }
}

void Var::insert(Var str, Var val) {
    if (this->type == MAP) {
        this->mp[str.getWStr()] = val;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"map\n";
        throw std::wstring{ error };
    }
}
void Var::insert(std::wstring str, Var val) {
    if (this->type == MAP) {
        this->mp[str] = val;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"map\n";
        throw std::wstring{ error };
    }
}
void Var::insert(const wchar_t* str, Var val) {
    if (this->type == MAP) {
        this->mp[str] = val;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"map\n";
        throw std::wstring{ error };
    }
}

Var Var::merge(const Var &val) const {
    if (this->type == ARR && val.type == ARR) {
        std::vector<Var> result = this->arr;
        if(result.capacity() < 1000) {
            result.reserve(1000);
        }
        result.insert(result.end(), val.arr.begin(), val.arr.end());
        return Var(result);
    }
    else if (this->type == MAP && val.type == MAP) {
        std::unordered_map<std::wstring, Var> result = this->mp;
        if(this->mp.bucket_count() < 1000) {
            result.reserve(1000);
        }
        result.insert(val.mp.begin(), val.mp.end());
        return Var(result);
    } 
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr, map\n";
        throw std::wstring{ error };
    }
}

Var Var::csize() const {
    if (this->type == ARR) {
        Var sz = this->arr.size();
        return sz;
    }
    else if (this->type == MAP) {
        Var sz = this->mp.size();
        return sz;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"arr, map\n";
        throw std::wstring{ error };
    }
}

std::wostream& operator<< (std::wostream& wos, const Var& var)
{
    switch (var.type) {
    case UNTG:
        return wos << var.data.untg;
        break;
    case NTG:
        return wos << var.data.ntg;
        break;
    case DBL:
        return wos << var.data.dbl;
        break;
    case CHR:
        return wos << var.data.chr;
        break;
    case UCHR:
        return wos << var.data.uchr;
        break;
    case BLN:
        if (var.data.bln) {
            return wos << L"true";
        }
        else {
            return wos << L"false";
        }
        break;
    case STR:
        return wos << var.str;
        break;
    case NIL:
        return wos << L"nil";
        break;
    case ARR: 
    {
        int size = (int)var.arr.size();
        std::wstring str = L"";
        for (int i = 0; i < size; ++i) {
            if (i == 0) {
                str += L'[';
                str += var.arr[i].toSTR().getWStr();
                if (size != 1) {
                    str += L", ";
                }
                else {
                    str += L"]";
                }
            }
            else if (i + 1 == size) {
                str += var.arr[i].toSTR().getWStr();
                str += L']';
            }
            else {
                str += var.arr[i].toSTR().getWStr();
                str += L", ";
            }
        }
        if (str == std::wstring_view(L"")) {
            return wos << L"[]";
        }
        else {
            return wos << str;
        }
        break;
    }
    case MAP:
    {
        std::wstring str = L"{";
        for (const auto& [key, val] : var.mp) {
            str += L"\"" + key + L"\": " + val.toSTR().getWStr() + L", ";
        }
        if(str != L"{") {
            str.pop_back();
            str.pop_back();
        }
        str+= L"}";
        return wos << str;
        break;
    }
    case INST: 
    {
        std::wstring result = L"";
        int size_i = (int)var.instructions.size();
        for( int i = 0; i < size_i; ++i) {
            result += var.instructions[i].as_string;
            if(i < size_i - 1) {
                result += L"; ";
            }
        }
        return wos << result;
        break;
    }
    default:
        return wos << L"unknown";
    }
}

Var& Var::operator= (const Var& var) {
    if (this->type == ARR && var.type != ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP && var.type != MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR && var.type != STR) {
        this->str = L"";
    }

    this->type = var.type;

    if (this->type == UNTG) {
        this->data.untg = var.data.untg;
    }
    if (this->type == NTG) {
        this->data.ntg = var.data.ntg;
    }
    if (this->type == DBL) {
        this->data.dbl = var.data.dbl;
    }
    if (this->type == CHR) {
        this->data.chr = var.data.chr;
    }
    if (this->type == UCHR) {
        this->data.uchr = var.data.uchr;
    }
    if (this->type == BLN) {
        this->data.bln = var.data.bln;
    }
    if (this->type == STR) {
        this->str = var.str;
    }
    if (this->type == ARR) {
        this->arr = var.arr;
    }
    if (this->type == MAP) {
        this->mp = var.mp;
    }
    if(this->type == INST) {
        this->instructions = var.instructions;
    }
    //Обычная константность не наследуется
    //this->is_const = var.is_const;
    this->is_superconst = var.is_superconst;
    this->deactivate = var.deactivate;
    return *this; 
}

Var& Var::operator= (const unsigned long long int& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = UNTG;
    this->data.untg = var;
    return *this;
}

Var& Var::operator= (const unsigned long int& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = NTG;
    this->data.ntg = var;

    return *this;
}

Var& Var::operator= (const unsigned int& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = NTG;
    this->data.ntg = var;
    return *this;
}

Var& Var::operator= (const unsigned short int& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = NTG;
    this->data.ntg = var;
    return *this;
}

Var& Var::operator= (const long long int& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = NTG;
    this->data.ntg = var;
    return *this;
}

Var& Var::operator= (const long int& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = NTG;
    this->data.ntg = var;
    return *this;
}

Var& Var::operator= (const int& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = NTG;
    this->data.ntg = var;
    return *this;
}

Var& Var::operator= (const short int& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = NTG;
    this->data.ntg = var;
    return *this;
}

Var& Var::operator= (const long double& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = DBL;
    this->data.dbl = var;
    return *this;
}

Var& Var::operator= (const double& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = DBL;
    this->data.dbl = (long double)var;
    return *this;
}

Var& Var::operator= (const float& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = DBL;
    this->data.dbl = (long double)var;
    return *this;
}

Var& Var::operator= (const char& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = CHR;
    this->data.chr = var;
    return *this;
}

Var& Var::operator= (const unsigned char& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = UCHR;
    this->data.uchr = var;
    return *this;
}

Var& Var::operator= (const bool& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = BLN;
    this->data.bln = var;
    return *this;
}

Var& Var::operator= (const std::wstring& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    this->type = STR;
    this->str = var;
    return *this;
}

Var& Var::operator= (const wchar_t* var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    this->type = STR;
    this->str = var;
    return *this;
}

Var& Var::operator= (std::vector<Var> v) {
    if (this->type == MAP) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        this->mp = map;
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = ARR;
    this->arr = v;
    if (this->arr.capacity() < 1000) {
        this->arr.reserve(1000);
    }
    return *this;
}

Var& Var::operator= (std::unordered_map<std::wstring, Var> m) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
        this->arr.reserve(1000);
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = MAP;
    this->mp = m;
    if(m.bucket_count() < 1000) {
        this->mp.reserve(1000);
    }
    return *this;
}

Var operator+(const Var& a, const Var& b)
{
    if (a.type == NTG) {
        if (b.type == NTG) {
            Var result(a.data.ntg + b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.ntg + b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.ntg + b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.ntg + b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.ntg + b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.ntg + b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.ntg + b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        } 
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UNTG) {
        if (b.type == NTG) {
            Var result(a.data.untg + b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.untg + b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.untg + b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.untg + b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.untg + b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.untg + b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.untg + b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == DBL) {
        if (b.type == NTG) {
            Var result(a.data.dbl + b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.dbl + b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.dbl + b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.dbl + b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.dbl + b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.dbl + b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.dbl + b.toDBL().getDouble());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == CHR) {
        if (b.type == NTG) {
            Var result(a.data.chr + b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.chr + b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.chr + b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.chr + b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.chr + b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.chr + b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.chr + b.toCHR().getChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UCHR) {
        if (b.type == NTG) {
            Var result(a.data.uchr + b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.uchr + b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.uchr + b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.uchr + b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.uchr + b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.uchr + b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.uchr + b.toUCHR().getUChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == BLN) {
        if (b.type == NTG) {
            Var result(a.data.bln + b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.bln + b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.bln + b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.bln + b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.bln + b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.bln + b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.bln + b.toBLN().getBool());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == STR) {
        if (b.type == NTG) {
            
            Var result(a.toNTG().getInt() + b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.toUNTG().getUInt() + b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.toDBL().getDouble() + b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.toCHR().getChar() + b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.toUCHR().getUChar() + b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.toBLN().getBool() + b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.str + b.str);
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == NIL) {
        Var result;
        return result;
    }
    else if (a.type == ARR) {
        throw std::wstring{ LangLib::getTrans(MESSAGE8) };
    }
    else if (a.type == MAP) {
        throw std::wstring{ LangLib::getTrans(MESSAGE9) };
    }
    else if (a.type == INST) {
        throw std::wstring{ LangLib::getTrans(MESSAGE11) };
    }
    else {
        Var result;
        return result;
    }

}

Var operator-(const Var& a, const Var& b)
{
    if (a.type == NTG) {
        if (b.type == NTG) {
            Var result(a.data.ntg - b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.ntg - b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.ntg - b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.ntg - b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.ntg - b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.ntg - b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.ntg - b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UNTG) {
        if (b.type == NTG) {
            Var result(a.data.untg - b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.untg - b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.untg - b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.untg - b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.untg - b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.untg - b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.untg - b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == DBL) {
        if (b.type == NTG) {
            Var result(a.data.dbl - b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.dbl - b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.dbl - b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.dbl - b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.dbl - b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.dbl - b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.dbl - b.toDBL().getDouble());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == CHR) {
        if (b.type == NTG) {
            Var result(a.data.chr - b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.chr - b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.chr - b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.chr - b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.chr - b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.chr - b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.chr - b.toCHR().getChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UCHR) {
        if (b.type == NTG) {
            Var result(a.data.uchr - b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.uchr - b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.uchr - b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.uchr - b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.uchr - b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.uchr - b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.uchr - b.toUCHR().getUChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == BLN) {
        if (b.type == NTG) {
            Var result(a.data.bln - b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.bln - b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.bln - b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.bln - b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.bln - b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.bln - b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.bln - b.toBLN().getBool());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == STR) {
        if (b.type == NTG) {

            Var result(a.toNTG().getInt() - b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.toUNTG().getUInt() - b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.toDBL().getDouble() - b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.toCHR().getChar() - b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.toUCHR().getUChar() - b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.toBLN().getBool() - b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.toDBL().getDouble() - b.toDBL().getDouble());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == NIL) {
        Var result;
        return result;
    }
    else if (a.type == ARR) {
        throw std::wstring{ LangLib::getTrans(MESSAGE8) };
    }
    else if (a.type == MAP) {
        throw std::wstring{ LangLib::getTrans(MESSAGE9) };
    }
    else if (a.type == INST) {
        throw std::wstring{ LangLib::getTrans(MESSAGE11) };
    }
    else {
        Var result;
        return result;
    }
}

Var operator*(const Var& a, const Var& b)
{
    if (a.type == NTG) {
        if (b.type == NTG) {
            Var result(a.data.ntg * b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.ntg * b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.ntg * b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.ntg * b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.ntg * b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.ntg * b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.ntg * b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UNTG) {
        if (b.type == NTG) {
            Var result(a.data.untg * b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.untg * b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.untg * b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.untg * b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.untg * b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.untg * b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.untg * b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == DBL) {
        if (b.type == NTG) {
            Var result(a.data.dbl * b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.dbl * b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.dbl * b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.dbl * b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.dbl * b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.dbl * b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.dbl * b.toDBL().getDouble());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == CHR) {
        if (b.type == NTG) {
            Var result(a.data.chr * b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.chr * b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.chr * b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.chr * b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.chr * b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.chr * b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.chr * b.toCHR().getChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UCHR) {
        if (b.type == NTG) {
            Var result(a.data.uchr * b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.uchr * b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.uchr * b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.uchr * b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.uchr * b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.uchr * b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.uchr * b.toUCHR().getUChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == BLN) {
        if (b.type == NTG) {
            Var result(a.data.bln * b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.bln * b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.bln * b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.bln * b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.bln * b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.bln * b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.bln * b.toBLN().getBool());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == STR) {
        if (b.type == NTG) {

            Var result(a.toNTG().getInt() * b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.toUNTG().getUInt() * b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.toDBL().getDouble() * b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.toCHR().getChar() * b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.toUCHR().getUChar() * b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.toBLN().getBool() * b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.toDBL().getDouble() * b.toDBL().getDouble());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else  {
            Var result;
            return result;
        }
    }
    else if (a.type == NIL) {
        Var result;
        return result;
    }
    else if (a.type == ARR) {
        throw std::wstring{ LangLib::getTrans(MESSAGE8) };
    }
    else if (a.type == MAP) {
        throw std::wstring{ LangLib::getTrans(MESSAGE9) };
    }
    else if (a.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
    else {
        Var result;
        return result;
    }
}

Var operator/(const Var& a, const Var& b)
{
    if (a.type == NTG) {
        if (b.type == NTG) {
            Var result(a.data.ntg / b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.ntg / b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.ntg / b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.ntg / b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.ntg / b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.ntg / (long long int)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.ntg / b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UNTG) {
        if (b.type == NTG) {
            Var result(a.data.untg / b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.untg / b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.untg / b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.untg / b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.untg / b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.untg / (unsigned long long int)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.untg / b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == DBL) {
        if (b.type == NTG) {
            Var result(a.data.dbl / b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.dbl / b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.dbl / b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.dbl / b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.dbl / b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.dbl / (double)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.dbl / b.toDBL().getDouble());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == CHR) {
        if (b.type == NTG) {
            Var result(a.data.chr / b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.chr / b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.chr / b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.chr / b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.chr / b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.chr / (char)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.chr / b.toCHR().getChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UCHR) {
        if (b.type == NTG) {
            Var result(a.data.uchr / b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.uchr / b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.uchr / b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.uchr / b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.uchr / b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.uchr / (unsigned char)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.uchr / b.toUCHR().getUChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == BLN) {
        if (b.type == NTG) {
            Var result((int)a.data.bln / b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result((unsigned long long int)a.data.bln / b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result((int)a.data.bln / (int)b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result((char)a.data.bln / b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result((unsigned char)a.data.bln / b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result((int)a.data.bln / (int)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result((int)a.data.bln / (int)b.toBLN().getBool());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == STR) {
        if (b.type == NTG) {

            Var result(a.toNTG().getInt() / b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.toUNTG().getUInt() / b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.toDBL().getDouble() / b.data.dbl);
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.toCHR().getChar() / b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.toUCHR().getUChar() / b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result((int)a.toBLN().getBool() / (int)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.toDBL().getDouble() / b.toDBL().getDouble());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == NIL) {
        Var result;
        return result;
    }
    else if (a.type == ARR) {
        throw std::wstring{ LangLib::getTrans(MESSAGE8) };
    }
    else if (a.type == MAP) {
        throw std::wstring{ LangLib::getTrans(MESSAGE9) };
    }
    else if (a.type == INST) {
        throw std::wstring{ LangLib::getTrans(MESSAGE11) };
    }
    else {
        Var result;
        return result;
    }
}

Var operator%(const Var& a, const Var& b)
{
    if (a.type == NTG) {
        if (b.type == NTG) {
            Var result(a.data.ntg % b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.ntg % b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.ntg % b.toNTG().getInt());
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.ntg % b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.ntg % b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.ntg % (long long int)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.ntg % b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UNTG) {
        if (b.type == NTG) {
            Var result(a.data.untg % b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.untg % b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.untg % b.toUNTG().getInt());
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.untg % b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.untg % b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.untg % (unsigned long long int)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.untg % b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == DBL) {
        if (b.type == NTG) {
            Var result(a.toNTG().getInt() % b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.toUNTG().getUInt() % b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.toNTG().getInt() % b.toNTG().getInt());
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.toNTG().getInt() % b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.toNTG().getInt() % b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.toNTG().getInt() % (long long int)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.toNTG().getInt() % b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == CHR) {
        if (b.type == NTG) {
            Var result(a.data.chr % b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.chr % b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.chr % b.toNTG().getInt());
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.chr % b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.chr % b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.chr % (char)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.chr % b.toCHR().getChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == UCHR) {
        if (b.type == NTG) {
            Var result(a.data.uchr % b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.data.uchr % b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.data.uchr % b.toNTG().getInt());
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.data.uchr % b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.data.uchr % b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result(a.data.uchr % (unsigned char)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.data.uchr % b.toUCHR().getUChar());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == BLN) {
        if (b.type == NTG) {
            Var result((long long int)a.data.bln % b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result((unsigned long long int)a.data.bln % b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result((int)a.data.bln % (int)b.toBLN().getBool());
            return result;
        }
        else if (b.type == CHR) {
            Var result((char)a.data.bln % b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result((unsigned char)a.data.bln % b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result((int)a.data.bln % (int)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result((int)a.data.bln % (int)b.toBLN().getBool());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == STR) {
        if (b.type == NTG) {

            Var result(a.toNTG().getInt() % b.data.ntg);
            return result;
        }
        else if (b.type == UNTG) {
            Var result(a.toUNTG().getUInt() % b.data.untg);
            return result;
        }
        else if (b.type == DBL) {
            Var result(a.toNTG().getInt() % b.toNTG().getInt());
            return result;
        }
        else if (b.type == CHR) {
            Var result(a.toCHR().getChar() % b.data.chr);
            return result;
        }
        else if (b.type == UCHR) {
            Var result(a.toUCHR().getUChar() % b.data.uchr);
            return result;
        }
        else if (b.type == BLN) {
            Var result((int)a.toBLN().getBool() % (int)b.data.bln);
            return result;
        }
        else if (b.type == STR) {
            Var result(a.toNTG().getInt() % b.toNTG().getInt());
            return result;
        }
        else if (b.type == NIL) {
            Var result;
            return result;
        }
        else if (b.type == ARR) {
            throw std::wstring{ LangLib::getTrans(MESSAGE8) };
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            Var result;
            return result;
        }
    }
    else if (a.type == NIL) {
        Var result;
        return result;
    }
    else if (a.type == ARR) {
        throw std::wstring{ LangLib::getTrans(MESSAGE8) };
    }
    else if (a.type == MAP) {
        throw std::wstring{ LangLib::getTrans(MESSAGE9) };
    }
    else if (a.type == INST) {
        throw std::wstring{ LangLib::getTrans(MESSAGE11) };
    }
    else {
        Var result;
        return result;
    }
}

Var operator+=(Var& a, const Var& b) {
    a = a + b;
    return a;
}

Var operator-=(Var& a, const Var& b) {
    a = a - b;
    return a;
}

Var operator*=(Var& a, const Var& b) {
    a = a * b;
    return a;
}

Var operator/=(Var& a, const Var& b) {
    a = a / b;
    return a;
}

Var operator%=(Var& a, const Var& b) {
    a = a % b;
    return a;
}

bool operator==(const Var& a, const Var& b) {
    if (a.type == NTG) {
        if (b.type == NTG) {
            return a.data.ntg == b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.ntg == (long long int)b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.ntg == b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.ntg == b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.ntg == b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.ntg == (long long int)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.ntg == b.toNTG().getInt();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.ntg) == b;
            }
        }
        else if (b.type == NIL) {
            if (a.data.ntg == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == ARR) {
            if (a.data.ntg == 0 && (int)b.arr.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == MAP) {
            if (a.data.ntg == 0 && (int)b.mp.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == UNTG) {
        if (b.type == NTG) {
            return a.data.untg == (unsigned long long int)b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.untg == b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.untg == b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.untg == (unsigned long long int)b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.untg == b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.untg == ( unsigned long long int)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.untg == b.toUNTG().getUInt();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.untg) == b;
            }
        }
        else if (b.type == NIL) {
            if (a.data.untg == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == ARR) {
            if (a.data.untg == 0 && (int)b.arr.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == INST) {
            if (a.data.untg == 0 && (int)b.mp.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else {
            return false;
        }
    }
    else if (a.type == DBL) {
        if (b.type == NTG) {
            return a.data.dbl == b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.dbl == b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.dbl == b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.dbl == b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.dbl == b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.dbl == (long double)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.dbl == b.toDBL().getDouble();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.dbl) == b;
            }
        }
        else if (b.type == NIL) {
            if (a.data.dbl == (long double)0) {
                return true;
            }
            return false;
        }
        else if (b.type == ARR) {
            if (a.data.dbl == (long double)0 && (int)b.arr.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == MAP) {
            if (a.data.dbl == (long double)0 && (int)b.mp.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == CHR) {
        if (b.type == NTG) {
            return a.data.chr == b.data.ntg;
        }
        else if (b.type == UNTG) {
            return (unsigned long long int)a.data.chr == b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.chr == b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.chr == b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.chr == b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.chr == (char)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.chr == b.toCHR().getChar();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.chr) == b;
            }
        }
        else if (b.type == NIL) {
            if (a.data.chr == (char)0) {
                return true;
            }
            return false;
        }
        else if (b.type == ARR) {
            if (a.data.chr == (char)0 && (int)b.arr.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == MAP) {
            if (a.data.chr == (char)0 && (int)b.mp.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == UCHR) {
        if (b.type == NTG) {
            return a.data.uchr == b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.uchr == b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.uchr == b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.uchr == b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.uchr == b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.uchr == (unsigned char)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.uchr == b.toUCHR().getUChar();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.uchr) == b;
            }
        }
        else if (b.type == NIL) {
            if (a.data.uchr == (unsigned char)0) {
                return true;
            }
            return false;
        }
        else if (b.type == ARR) {
            if (a.data.uchr == (unsigned char)0 && (int)b.arr.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == INST) {
            if (a.data.uchr == (unsigned char)0 && (int)b.mp.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else {
            return false;
        }
    }
    else if (a.type == BLN) {
        if (b.type == NTG) {
            return  (long long int)a.data.bln == b.data.ntg;
        }
        else if (b.type == UNTG) {
            return (unsigned long long int)a.data.bln == b.data.untg;
        }
        else if (b.type == DBL) {
            return (int)a.data.bln == (int)b.data.dbl;
        }
        else if (b.type == CHR) {
            return (char)a.data.bln == b.data.chr;
        }
        else if (b.type == UCHR) {
            return (unsigned char)a.data.bln == b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.bln == b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.bln == b.toBLN().getBool();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.bln) == b;
            }
        }
        else if (b.type == NIL) {
            if ((int)a.data.bln == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == ARR) {
            if ((int)a.data.bln == 0 && (int)b.arr.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == MAP) {
            if ((int)a.data.bln == 0 && (int)b.mp.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == STR) {
        if (b.type == NTG) {
            try {
                return a.toNTG().getInt() == b.data.ntg;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str == std::to_wstring(b.data.ntg);
            }
        }
        else if (b.type == UNTG) {
            try {
                return a.toUNTG().getUInt() == b.data.untg;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str == std::to_wstring(b.data.untg);
            }
        }
        else if (b.type == DBL) {
            try {
                return a.toDBL().getDouble() == b.data.dbl;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str == std::to_wstring(b.data.dbl);
            }
        }
        else if (b.type == CHR) {
            try {
                return a.toCHR().getChar() == b.data.chr;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str == std::to_wstring(b.data.chr);
            }
        }
        else if (b.type == UCHR) {
            try {
                return a.toUCHR().getUChar() == b.data.uchr;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str == std::to_wstring(b.data.uchr);
            }
        }
        else if (b.type == BLN) {
            try {
                return a.toBLN().getBool() == b.data.bln;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str == std::to_wstring(b.data.bln);
            }
        }
        else if (b.type == STR) {
            return a.str == b.str;
        }
        else if (b.type == NIL) {
            if (a.str == std::wstring_view(L"")) {
                return true;
            }
            return false;
        }
        else if (b.type == ARR) {
            if ((int)a.str.size() == 0 && (int)b.arr.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == MAP) {
            if (a.str.size() == 0 && (int)b.mp.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == NIL) {
        if (b.type == NTG) {
            return 0 == b.data.ntg;
        }
        else if (b.type == UNTG) {
            return 0 == b.data.untg;
        }
        else if (b.type == DBL) {
            return (long double)0 == b.data.dbl;
        }
        else if (b.type == CHR) {
            return (char)0 == b.data.chr;
        }
        else if (b.type == UCHR) {
            return (unsigned char)0 == b.data.uchr;
        }
        else if (b.type == BLN) {
            return (bool)0 == b.data.bln;
        }
        else if (b.type == STR) {
            return L"" == b.str;
        }
        else if (b.type == NIL) {
            return true;
        }
        else if (b.type == ARR) {
            if (0 == (int)b.arr.size()) {
                return true;
            }
            return false;
        }
        else if (b.type == MAP) {
            if (0 == (int)b.mp.size()) {
                return true;
            }
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == ARR) {
        if (b.type == ARR) {
            return a.eq(L"strict", b).data.bln;
        }
        else if (b.type == NIL) {
            if ((int)a.arr.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == BLN) {
            if ((int)a.arr.size() == 0 && b.data.bln == false) {
                return true;
            }
            return false;
        }
        else if (b.type == STR) {
            if ((int)a.arr.size() == 0 && b.str == std::wstring_view(L"")) {
                return true;
            }
            return false;
        }
        else {
            return false;
        }
    }
    else if (a.type == MAP) {
        if (b.type == MAP) {
            return a.eq(L"strict", b).data.bln;
        }
        else if (b.type == NIL) {
            if ((int)a.mp.size() == 0) {
                return true;
            }
            return false;
        }
        else if (b.type == BLN) {
            if ((int)a.mp.size() == 0 && b.data.bln == false) {
                return true;
            }
            return false;
        }
        else if (b.type == STR) {
            if ((int)a.mp.size() == 0 && b.str == std::wstring_view(L"")) {
                return true;
            }
            return false;
        }
        else {
            return false;
        }
    }
    else if (a.type == INST) {
            if( b.type == INST) {

                int size_a = (int)a.instructions.size();
                int size_b = (int)b.instructions.size();

                if(size_a != size_b) {
                    return false;
                }
                Parser p;
                std::wstring a_str = L"";
                std::wstring b_str = L"";

                for( int i = 0; i < size_a; ++i) {
                    a_str += p.showInstruction(a.instructions[i]);
                    if(i < size_a - 1) {
                        a_str += L"; ";
                    } else {
                        a_str += L";";
                    }
                }

                for( int i = 0; i < size_b; ++i) {
                    b_str += p.showInstruction(b.instructions[i]);
                    if(i < size_b - 1) {
                        b_str += L"; ";
                    } else {
                        b_str += L";";
                    }
                }

                return a_str == b_str;
            }
            else {
                throw std::wstring{ LangLib::getTrans(MESSAGE11) };
            }
        }
    else {
        return false;
    }
}

bool operator!=(const Var& a, const Var& b) {
    return !(a == b);
}

bool operator>(const Var& a, const Var& b) {
    if (a.type == NTG) {
        if (b.type == NTG) {
            return a.data.ntg > b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.ntg > (long long int)b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.ntg > b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.ntg > b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.ntg > b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.ntg > (long long int)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.ntg > b.toNTG().getInt();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.ntg) > b;
            }
        }
        else if (b.type == NIL) {
            return a.data.ntg > 0;
        }
        else if (b.type == ARR) {
            return false;
        }
        else if (b.type == MAP) {
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == UNTG) {
        if (b.type == NTG) {
            return a.data.untg > (unsigned long long int)b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.untg > b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.untg > b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.untg > (unsigned long long int)b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.untg > b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.untg > (unsigned long long int)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.untg > b.toUNTG().getUInt();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.untg) > b;
            }
        }
        else if (b.type == NIL) {
            return a.data.untg > 0;
        }
        else if (b.type == ARR) {
            return false;
        }
        else if (b.type == MAP) {
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == DBL) {
        if (b.type == NTG) {
            return a.data.dbl > b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.dbl > b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.dbl > b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.dbl > b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.dbl > b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.dbl > (long double)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.dbl > b.toDBL().getDouble();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.dbl) > b;
            }
        }
        else if (b.type == NIL) {
            return a.data.dbl > 0;
        }
        else if (b.type == ARR) {
            return false;
        }
        else if (b.type == MAP) {
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == CHR) {
        if (b.type == NTG) {
            return a.data.chr > b.data.ntg;
        }
        else if (b.type == UNTG) {
            return (unsigned long long int)a.data.chr > b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.chr > b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.chr > b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.chr > b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.chr > (char)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.chr > b.toCHR().getChar();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.chr) > b;
            }
        }
        else if (b.type == NIL) {
            return a.data.chr > 0;
        }
        else if (b.type == ARR) {
            return false;
        }
        else if (b.type == MAP) {
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == UCHR) {
        if (b.type == NTG) {
            return a.data.uchr > b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.uchr > b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.uchr > b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.uchr > b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.uchr > b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.uchr > (unsigned char)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.uchr > b.toUCHR().getUChar();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.uchr) > b;
            }
        }
        else if (b.type == NIL) {
            return a.data.uchr > 0;
        }
        else if (b.type == ARR) {
            return false;
        }
        else if (b.type == MAP) {
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == BLN) {
        if (b.type == NTG) {
            return (long long int)a.data.bln > b.data.ntg;
        }
        else if (b.type == UNTG) {
            return (unsigned long long int)a.data.bln > b.data.untg;
        }
        else if (b.type == DBL) {
            return (long double)a.data.bln > b.data.dbl;
        }
        else if (b.type == CHR) {
            return (char)a.data.bln > b.data.chr;
        }
        else if (b.type == UCHR) {
            return (unsigned char)a.data.bln > b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.bln > b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.bln > b.toBLN().getBool();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.bln) > b;
            }
        }
        else if (b.type == NIL) {
            return (int)a.data.bln > 0;
        }
        else if (b.type == ARR) {
            return false;
        }
        else if (b.type == MAP) {
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == STR) {
        if (b.type == NTG) {
            try {
                return a.toNTG().getInt() > b.data.ntg;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str > std::to_wstring(b.data.ntg);
            }
        }
        else if (b.type == UNTG) {
            try {
                return a.toUNTG().getUInt() > b.data.untg;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str > std::to_wstring(b.data.untg);
            }
        }
        else if (b.type == DBL) {
            try {
                return a.toDBL().getDouble() > b.data.dbl;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str > std::to_wstring(b.data.dbl);
            }
        }
        else if (b.type == CHR) {
            try {
                return a.toCHR().getChar() > b.data.chr;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str > std::to_wstring(b.data.chr);
            }
        }
        else if (b.type == UCHR) {
            try {
                return a.toUCHR().getUChar() > b.data.uchr;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str > std::to_wstring(b.data.uchr);
            }
        }
        else if (b.type == BLN) {
            try {
                return a.toBLN().getBool() > b.data.bln;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str > std::to_wstring(b.data.bln);
            }
        }
        else if (b.type == STR) {
            return a.str > b.str;
        }
        else if (b.type == NIL) {
            return a.str > L"";
        }
        else if (b.type == ARR) {
            return false;
        }
        else if (b.type == MAP) {
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == NIL) {
        if (b.type == NTG) {
            return 0 > b.data.ntg;
        }
        else if (b.type == UNTG) {
            return false;
        }
        else if (b.type == DBL) {
            return 0 > b.data.dbl;
        }
        else if (b.type == CHR) {
            return 0 > b.data.chr;
        }
        else if (b.type == UCHR) {
            return false;
        }
        else if (b.type == BLN) {
            return 0 > (int)b.data.bln;
        }
        else if (b.type == STR) {
            return false;
        }
        else if (b.type == NIL) {
            return false;
        }
        else if (b.type == ARR) {
            return false;
        }
        else if (b.type == MAP) {
            return false;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == ARR) {
        if (b.type == ARR) {
            return a.getArr().size() > b.getArr().size();
        }
        else if (b.type == MAP) {
           return a.getArr().size() > b.getMap().size();
        } 
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return true;
        }
    }
    else if (a.type == MAP) {
        if (b.type == ARR) {
            return a.getMap().size() > b.getArr().size();
        }
        else if (b.type == MAP) {
           return a.getMap().size() > b.getMap().size();
        } 
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return true;
        }
    } else if (a.type == INST) {
        throw std::wstring{ LangLib::getTrans(MESSAGE11) };
    }
    else {
        return false;
    }
}

bool operator<=(const Var& a, const Var& b) {
    return !(a > b);
}

bool operator<(const Var& a, const Var& b) {
    if (a.type == NTG) {
        if (b.type == NTG) {
            return a.data.ntg < b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.ntg < (long long int)b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.ntg < b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.ntg < b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.ntg < b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.ntg < (long long int)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.ntg < b.toNTG().getInt();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.ntg) < b;
            }
        }
        else if (b.type == NIL) {
            return a.data.ntg < 0;
        }
        else if (b.type == ARR) {
            return true;
        }
        else if (b.type == MAP) {
            return true;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == UNTG) {
        if (b.type == NTG) {
            return a.data.untg < (unsigned long long int)b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.untg < b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.untg < b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.untg < (unsigned long long int)b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.untg < b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.untg < (unsigned long long int)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.untg < b.toUNTG().getUInt();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.untg) < b;
            }
        }
        else if (b.type == NIL) {
            return false;
        }
        else if (b.type == ARR) {
            return true;
        }
        else if (b.type == MAP) {
            return true;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == DBL) {
        if (b.type == NTG) {
            return a.data.dbl < b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.dbl < b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.dbl < b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.dbl < b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.dbl < b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.dbl < (long double)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.dbl < b.toDBL().getDouble();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.dbl) < b;
            }
        }
        else if (b.type == NIL) {
            return a.data.dbl < 0;
        }
        else if (b.type == ARR) {
            return true;
        }
        else if (b.type == MAP) {
            return true;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == CHR) {
        if (b.type == NTG) {
            return a.data.chr < b.data.ntg;
        }
        else if (b.type == UNTG) {
            return (unsigned long long int)a.data.chr < b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.chr < b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.chr < b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.chr < b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.chr < (char)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.chr < b.toCHR().getChar();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.chr) < b;
            }
        }
        else if (b.type == NIL) {
            return a.data.chr < 0;
        }
        else if (b.type == ARR) {
            return true;
        }
        else if (b.type == MAP) {
            return true;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == UCHR) {
        if (b.type == NTG) {
            return a.data.uchr < b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.uchr < b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.uchr < b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.uchr < b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.uchr < b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.uchr < (unsigned char)b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.uchr < b.toUCHR().getUChar();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.uchr) < b;
            }
        }
        else if (b.type == NIL) {
            return false;
        }
        else if (b.type == ARR) {
            return true;
        }
        else if (b.type == MAP) {
            return true;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == BLN) {
        if (b.type == NTG) {
            return (long long int)a.data.bln < b.data.ntg;
        }
        else if (b.type == UNTG) {
            return (unsigned long long int)a.data.bln < b.data.untg;
        }
        else if (b.type == DBL) {
            return (long double)a.data.bln < b.data.dbl;
        }
        else if (b.type == CHR) {
            return (char)a.data.bln < b.data.chr;
        }
        else if (b.type == UCHR) {
            return (unsigned char)a.data.bln < b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.bln < b.data.bln;
        }
        else if (b.type == STR) {
            try {
                return a.data.bln < b.toBLN().getBool();
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return std::to_wstring(a.data.bln) < b;
            }
        }
        else if (b.type == NIL) {
            return (int)a.data.bln < 0;
        }
        else if (b.type == ARR) {
            return true;
        }
        else if (b.type == MAP) {
            return true;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == STR) {
        if (b.type == NTG) {
            try {
                return a.toNTG().getInt() < b.data.ntg;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str < std::to_wstring(b.data.ntg);
            }
        }
        else if (b.type == UNTG) {
            try {
                return a.toUNTG().getUInt() < b.data.untg;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str < std::to_wstring(b.data.untg);
            }
        }
        else if (b.type == DBL) {
            try {
                return a.toDBL().getDouble() < b.data.dbl;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str < std::to_wstring(b.data.dbl);
            }
        }
        else if (b.type == CHR) {
            try {
                return a.toCHR().getChar() < b.data.chr;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str < std::to_wstring(b.data.chr);
            }
        }
        else if (b.type == UCHR) {
            try {
                return a.toUCHR().getUChar() < b.data.uchr;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str < std::to_wstring(b.data.uchr);
            }
        }
        else if (b.type == BLN) {
            try {
                return a.toBLN().getBool() < b.data.bln;
            }
            catch (const std::wstring& error_message) {
                std::wstring temp = error_message;
                return a.str < std::to_wstring(b.data.bln);
            }
        }
        else if (b.type == STR) {
            return a.str < b.str;
        }
        else if (b.type == NIL) {
            return a.str < L"";
        }
        else if (b.type == ARR) {
            return true;
        }
        else if (b.type == MAP) {
            return true;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == NIL) {
        if (b.type == NTG) {
            return 0 < b.data.ntg;
        }
        else if (b.type == UNTG) {
            return 0 < b.data.untg;
        }
        else if (b.type == DBL) {
            return 0 < b.data.dbl;
        }
        else if (b.type == CHR) {
            return 0 < b.data.chr;
        }
        else if (b.type == UCHR) {
            return 0 < b.data.uchr;
        }
        else if (b.type == BLN) {
            return 0 < (int)b.data.bln;
        }
        else if (b.type == STR) {
            return L"" < b.str;
        }
        else if (b.type == NIL) {
            return false;
        }
        else if (b.type == ARR) {
            return true;
        }
        else if (b.type == MAP) {
            return true;
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == ARR) {
        if (b.type == ARR) {
            return a.getArr().size() < b.getArr().size();
        }
        else if (b.type == MAP) {
            return a.getArr().size() < b.getMap().size();
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == MAP) {
        if (b.type == ARR) {
            return a.getMap().size() < b.getArr().size();
        }
        else if (b.type == MAP) {
            return a.getMap().size() < b.getMap().size();
        }
        else if (b.type == INST) {
            throw std::wstring{ LangLib::getTrans(MESSAGE11) };
        }
        else {
            return false;
        }
    }
    else if (a.type == INST) {
        throw std::wstring{ LangLib::getTrans(MESSAGE11) };
    }
    else {
        return false;
    }
}

bool operator>=(const Var& a, const Var& b) {
    return !(a < b);
}

bool operator!(const Var& a) {
    return !(a.toBLN().getBool());
}

void swap(Var& a, Var& b) {
    Var tmp = a;
    a = b;
    b = tmp;
}