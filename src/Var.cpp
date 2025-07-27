#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "LangLib.h"

#include "Var.h"

const std::wstring MESSAGE1 = L"Не удалось привести строку к типу ";
const std::wstring MESSAGE2 = L"Невозможно привести массив к типу ";
const std::wstring MESSAGE3 = L"Невозможно привести словарь к типу ";
const std::wstring MESSAGE4 = L"Индекс находится вне диапазона\n";
const std::wstring MESSAGE5 = L"Взятие значения по индексу возможно только для следующих типов: ";
const std::wstring MESSAGE6 = L"Индекс словаря не существует\n";
const std::wstring MESSAGE7 = L"Инструкция используется только для следующих типов: ";
const std::wstring MESSAGE8 = L"Массив не поддерживает данной операции\n";
const std::wstring MESSAGE9 = L"Cловарь не поддерживает данной операции\n";

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
    if (t == L"array") {
        this->type = ARR;
        this->arr = std::vector<Var>(i);
    } 
    else if (t == L"map" && i == 0) {
        this->type = MAP;
        this->mp = std::map<std::wstring, Var>();
    }
    else {
        this->type = UNKNOWN;
    }
}

Var::Var(std::vector<Var> v) {
    this->type = ARR;
    this->arr = v;
}

Var::Var(std::map<std::wstring, Var> m) {
    this->type = MAP;
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

std::map<std::wstring, Var> Var::getMap() const {
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
            error += L"NTG\n";
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
        error += L"NTG\n";
        throw std::wstring{ error };
    }
    else if (this->type == MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"NTG\n";
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
            error += L"UNTG\n";
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
            error += L"DBL\n";
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
            error += L"CHR\n";
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
            error += L"UCHR\n";
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
        error += L"UCHR\n";
        throw std::wstring{ error };

    }
    else if (this->type == MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"UCHR\n";
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

        if (this->str == L"") {
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
            result.str = L"TRUE";
        }
        else {
            result.str = L"FALSE";
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
        Var result = L"NIL";
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
        if (result == L"") {
            return L"[]";
        }
        else {
            return result;
        }
    }
    else if (this->type == MAP) {
        //Сделать рекурсивный вывод как у ARR
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"STR\n";
        throw std::wstring{ error };
    }
    return Var();
}

Var Var::toARR() const {
    if (this->type == NTG) {
        Var result;
        result.type = ARR;
        result.arr.push_back(*this);
        return result;
    }
    else if (this->type == UNTG) {
        Var result;
        result.type = ARR;
        result.arr.push_back(*this);
        return result;
    }
    else if (this->type == DBL) {
        Var result;
        result.type = ARR;
        result.arr.push_back(*this);
        return result;
    }
    else if (this->type == CHR) {
        Var result;
        result.type = ARR;
        result.arr.push_back(*this);
        return result;
    }
    else if (this->type == UCHR) {
        Var result;
        result.type = ARR;
        result.arr.push_back(*this);
        return result;
    }
    else if (this->type == BLN) {
        Var result;
        result.type = ARR;
        result.arr.push_back(*this);
        return result;
    }
    else if (this->type == STR) {
        Var result;
        result.type = ARR;
        result.arr.push_back(*this);
        return result;
    }
    else if (this->type == NIL) {
        Var result;
        result.type = ARR;
        result.arr.push_back(*this);
        return result;
    }
    else if (this->type == UNKNOWN) {
        Var result;
        result.type = ARR;
        result.arr.push_back(*this);
        return result;
    }
    else if (this->type == ARR) {
        return *this;
    }
    else if (this->type == MAP) {
        std::wstring error = LangLib::getTrans(MESSAGE3);
        error += L"ARR\n";
        throw std::wstring{ error };
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
            std::wcout << L"TRUE";
        }
        else {
            std::wcout << L"FALSE";
        }
        break;
    case STR:
        std::wcout << this->str;
        break;
    case NIL:
        std::wcout << L"NIL";
        break;
    case ARR:
        for (int i = 0; i < this->arr.size(); ++i)
            std::wcout << i << L":\t" << this->arr[i] << L"\n";
        break;
    case MAP:
        for (const auto& elem : this->mp)
        {
            std::wcout << "\"" << elem.first << "\":\t " << elem.second << "\t";
        }
        break;
    default:
        std::wcout << L"UNKNOWN";
    }
}

std::wstring Var::typeOf() {
    std::wstring result = L"";
    switch (this->type) {
    case UNTG:
        result = L"UNTG";
        return result;
        break;
    case NTG:
        result = L"NTG";
        return result;
        break;
    case DBL:
        result = L"DBL";
        return result;
        break;
    case CHR:
        result = L"CHR";
        return result;
        break;
    case UCHR:
        result = L"UCHR";
        return result;
        break;
    case BLN:
        result = L"BLN";
        return result;
        break;
    case STR:
        result = L"STR";
        return result;
        break;
    case NIL:
        result = L"NIL";
        return result;
        break;
    case ARR:
        result = L"ARR";
        return result;
        break;
    case MAP:
        result = L"MAP";
        return result;
    default:
        result = L"UNKNOWN";
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
            throw std::wstring{ LangLib::getTrans(MESSAGE4) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE4) };
        }
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE5);
        error += L"STR, ARR, MAP\n";
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
            error += L"STR, ARR, MAP\n";
            throw std::wstring{ error };
        }
    }
    catch (std::exception& err) {
        std::string temp = err.what();
        throw std::wstring{ LangLib::getTrans(MESSAGE6) };
    }
}
Var& Var::operator[](std::wstring str) {
    try {
        if (this->type == MAP) {
            return this->mp.at(str);
        }
        else {
            std::wstring error = LangLib::getTrans(MESSAGE5);
            error += L"STR, ARR, MAP\n";
            throw std::wstring{ error };
        }
    }
    catch (std::exception& err) {
        std::string temp = err.what();
        throw std::wstring{ LangLib::getTrans(MESSAGE6) };
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
                throw std::wstring{ LangLib::getTrans(MESSAGE4) };
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
                throw std::wstring{ LangLib::getTrans(MESSAGE4) };
            }
        }
        else {
            std::wstring error = LangLib::getTrans(MESSAGE5);
            error += L"STR, ARR, MAP\n";
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
            throw std::wstring{ LangLib::getTrans(MESSAGE6) };
        }
    }
    else {
        std::wstring error = LangLib::getTrans(L"Взятие значения по индексу использует только следующие типы: ");
        error += L"NTG, UNTG, STR\n";
        throw std::wstring{ error };
    }
    return v;
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
        error += L"STR, ARR, MAP\n";
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
        reverse(v.begin(), v.end());
        Var result;
        result.type = ARR;
        result.arr = v;
        return result;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"STR, ARR\n";
        throw std::wstring{ error };
    }
}

Var Var::slice(int x, int y) {
    if (this->type == STR) {
        return Var(this->str.substr(x, y));
    }
    else if (this->type == ARR) {
        auto start = arr.begin() + x;
        auto end = arr.begin() + x + y;
        std::vector<Var> result(y);

        copy(start, end, result.begin());
        
        Var res;
        res.type = ARR;
        res.arr = result;

        return res;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"STR, ARR\n";
        throw std::wstring{ error };
    }
}
Var Var::slice(Var x, Var y) {
    if (this->type == STR) {
        return this->slice((int)x.getInt(), (int)y.getInt());
    }
    else if (this->type == ARR) {
        return this->slice((int)x.getInt(), (int)y.getInt());
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"STR, ARR\n";
        throw std::wstring{ error };
    }
}

Var Var::in(Var sent) const {
    if(this->type == STR) {
        bool exists = this->str.find(sent.str) != std::string::npos;
        return Var(exists);
    } 
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"STR\n";
        throw std::wstring{ error };
    }
}
Var Var::in(const wchar_t* sent) const {
    if (this->type == STR) {
        bool exists = this->str.find(sent) != std::string::npos;
        return Var(exists);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"STR\n";
        throw std::wstring{ error };
    }
}
Var Var::in(std::wstring sent) const {
    if (this->type == STR) {
        bool exists = this->str.find(sent) != std::string::npos;
        return Var(exists);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"STR\n";
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
        error += L"STR\n";
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
        error += L"STR\n";
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
        error += L"STR\n";
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
        error += L"STR\n";
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
        error += L"STR\n";
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
        error += L"STR\n";
        throw std::wstring{ error };
    }
}

Var Var::split(Var delim) const {
    if (this->type == STR) {
        std::vector<Var> tokens;
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
                tokens.push_back(token);
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
        error += L"STR\n";
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
        for (int i = 0; i < this->arr.size(); ++i) {
            str += this->arr[i].toSTR().getWStr();
            if (i != this->arr.size() - 1) {
                str += delim.getWStr();
            }
        }
        return Var(str);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"ARR\n";
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
        error += L"STR\n";
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
        error += L"STR\n";
        throw std::wstring{ error };
    }
}

void Var::pushb(Var v) {
    if (this->type == ARR) {
        this->arr.push_back(v);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"ARR\n";
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
        error += L"ARR\n";
        throw std::wstring{ error };
    }
}

void Var::pushf(Var val) {
    if (this->type == ARR) {
        this->arr.insert(this->arr.begin(), val);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"ARR\n";
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
        error += L"ARR\n";
        throw std::wstring{ error };;
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
        error += L"ARR, MAP\n";
        throw std::wstring{ error };
    }

}

void Var::erase(int x) {
    if (this->type == ARR) {
        std::vector<Var>::iterator it;
        it = this->arr.begin() + x;
        this->arr.erase(it);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"ARR\n";
        throw std::wstring{ error };
    }
}
Var Var::erase(Var x) {
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
            this->mp.erase(x.toSTR().getWStr());
            return result;
        }
        catch (std::out_of_range& ex) {
            std::string temp = ex.what();
            throw std::wstring{ x.toSTR().getWStr() + LangLib::getTrans(L": ") + LangLib::getTrans(MESSAGE6) };
        }
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"ARR, MAP\n";
        throw std::wstring{ error };
    }
}
void Var::erase(std::wstring x) {
    if (this->type == MAP) {
        this->mp.erase(x);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"MAP\n";
        throw std::wstring{ error };
    }
}
void Var::erase(const wchar_t* x) {
    if (this->type == MAP) {
        this->mp.erase(x);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"MAP\n";
        throw std::wstring{ error };
    }
}

void Var::insert_vector(Var x, Var val) {
    if (this->type == ARR) {
        if (x < 0 || x > arr.size()) {
            throw std::wstring{ x.toSTR().getWStr() + LangLib::getTrans(L": ") + LangLib::getTrans(MESSAGE4) };
        }
        this->arr.insert(this->arr.begin() + x.toNTG().getInt(), val);
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"ARR\n";
        throw std::wstring{ error };
    }
}

void Var::insert(Var str, Var val) {
    if (this->type == MAP) {
        this->mp[str.getWStr()] = val;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"MAP\n";
        throw std::wstring{ error };
    }
}
void Var::insert(std::wstring str, Var val) {
    if (this->type == MAP) {
        this->mp[str] = val;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"MAP\n";
        throw std::wstring{ error };
    }
}
void Var::insert(const wchar_t* str, Var val) {
    if (this->type == MAP) {
        this->mp[str] = val;
    }
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"MAP\n";
        throw std::wstring{ error };
    }
}

Var Var::merge(Var val) const {
    if (this->type == ARR && val.type == ARR) {
        std::vector<Var> result = this->arr;
        result.insert(result.end(), val.arr.begin(), val.arr.end());
        return Var(result);
    }
    else if (this->type == MAP && val.type == MAP) {
        std::map<std::wstring, Var> result = this->mp;
        result.insert(val.mp.begin(), val.mp.end());
        return Var(result);
    } 
    else {
        std::wstring error = LangLib::getTrans(MESSAGE7);
        error += L"ARR, MAP\n";
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
        error += L"ARR, MAP\n";
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
            return wos << L"TRUE";
        }
        else {
            return wos << L"FALSE";
        }
        break;
    case STR:
        return wos << var.str;
        break;
    case NIL:
        return wos << L"NIL";
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
        if (str == L"") {
            return wos << L"[]";
        }
        else {
            return wos << str;
        }
        break;
    }
    case MAP:
        return wos << L"MAP";
    default:
        return wos << L"UNKNOWN";
    }
}

Var& Var::operator= (const Var& var) {
    if (this->type == ARR && var.type != ARR) {
        this->arr = std::vector<Var>();
    }
    if (this->type == MAP && var.type != MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    return *this; 
}

Var& Var::operator= (const unsigned long long int& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = DBL;
    this->data.dbl = (const long double)var;
    return *this;
}

Var& Var::operator= (const char& var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
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
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
    }
    this->type = STR;
    this->str = var;
    return *this;
}

Var& Var::operator= (const wchar_t* var) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
    }
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
    }
    this->type = STR;
    this->str = var;
    return *this;
}

Var& Var::operator= (std::vector<Var> v) {
    if (this->type == MAP) {
        this->mp = std::map<std::wstring, Var>();
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = ARR;
    this->arr = v;
    return *this;
}

Var& Var::operator= (std::map<std::wstring, Var> m) {
    if (this->type == ARR) {
        this->arr = std::vector<Var>();
    }
    if (this->type == STR) {
        this->str = L"";
    }
    this->type = MAP;
    this->mp = m;
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
            return a.data.ntg == b.data.untg;
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
            return a.data.ntg == (const long long int)b.data.bln;
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else {
            return false;
        }
    }
    else if (a.type == UNTG) {
        if (b.type == NTG) {
            return a.data.untg == b.data.ntg;
        }
        else if (b.type == UNTG) {
            return a.data.untg == b.data.untg;
        }
        else if (b.type == DBL) {
            return a.data.untg == b.data.dbl;
        }
        else if (b.type == CHR) {
            return a.data.untg == b.data.chr;
        }
        else if (b.type == UCHR) {
            return a.data.untg == b.data.uchr;
        }
        else if (b.type == BLN) {
            return a.data.untg == (const unsigned long long int)b.data.bln;
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
            return a.data.dbl == (const long double)b.data.bln;
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            return a.data.chr == b.data.untg;
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
            return a.data.chr == (const char)b.data.bln;
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            return a.data.uchr == (const unsigned char)b.data.bln;
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
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else {
            return false;
        }
    }
    else if (a.type == BLN) {
        if (b.type == NTG) {
            return  (const long long int)a.data.bln == b.data.ntg;
        }
        else if (b.type == UNTG) {
            return (const unsigned long long int)a.data.bln == b.data.untg;
        }
        else if (b.type == DBL) {
            return (const int)a.data.bln == (const int)b.data.dbl;
        }
        else if (b.type == CHR) {
            return (const char)a.data.bln == b.data.chr;
        }
        else if (b.type == UCHR) {
            return (const unsigned char)a.data.bln == b.data.uchr;
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            if (a.str == L"") {
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else {
            return false;
        }
    }
    else if (a.type == ARR) {
        if (b.type == ARR) {
            return deq(a, b).getBool();
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
            if ((int)a.arr.size() == 0 && b.str == L"") {
                return true;
            }
            return false;
        }
        else {
            return false;
        }
    }
    else if (a.type == MAP) {
        throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            return a.data.untg > b.data.chr;
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            return a.data.chr > b.data.untg;
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            return 0 > b.data.untg;
        }
        else if (b.type == DBL) {
            return 0 > b.data.dbl;
        }
        else if (b.type == CHR) {
            return 0 > b.data.chr;
        }
        else if (b.type == UCHR) {
            return 0 > b.data.uchr;
        }
        else if (b.type == BLN) {
            return 0 > (int)b.data.bln;
        }
        else if (b.type == STR) {
            return 0 > b.str;
        }
        else if (b.type == NIL) {
            return false;
        }
        else if (b.type == ARR) {
            return false;
        }
        else if (b.type == MAP) {
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else {
            return true;
        }
    }
    else if (a.type == MAP) {
        throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            return a.data.untg < b.data.chr;
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
            return a.data.untg < 0;
        }
        else if (b.type == ARR) {
            return true;
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            return a.data.chr < b.data.untg;
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            return a.data.uchr < 0;
        }
        else if (b.type == ARR) {
            return true;
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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
            throw std::wstring{ LangLib::getTrans(MESSAGE9) };
        }
        else {
            return false;
        }
    }
    else if (a.type == MAP) {
        throw std::wstring{ LangLib::getTrans(MESSAGE9) };
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

Var eq(Var a, Var b) {
    if (a.type == ARR && b.type == ARR) {
        std::vector<Var>arr_a = a.getArr();
        std::vector<Var>arr_b = b.getArr();
        int size_a = (int)arr_a.size();
        int size_b = (int)arr_b.size();

        if (size_a != size_b) { return Var(false); }

        bool is_equal = true;
        for (int i = 0; i < size_a; ++i) {
            if (eq(arr_a[i], arr_b[i]) == false) {
                is_equal = false;
                break;
            }
        }
        return Var(is_equal);
    }
    else if ((a.type == ARR && b.type != ARR) || (a.type != ARR && b.type == ARR)) {
        return Var(false);
    }
    else {
        if (a.type == b.type && a == b) { return Var(true); }
        else { return Var(false); }
    }
    return Var(false);
}

Var deq(Var a, Var b) {
    if (a.type == ARR && b.type == ARR) {
        std::vector<Var>arr_a = a.getArr();
        std::vector<Var>arr_b = b.getArr();
        int size_a = (int)arr_a.size();
        int size_b = (int)arr_b.size();

        if (size_a != size_b) { return Var(false); }

        bool is_equal = true;
        for (int i = 0; i < size_a; ++i) {
            if (deq(arr_a[i], arr_b[i]) == false) {
                is_equal = false;
                break;
            }
        }
        return Var(is_equal);
    }
    else if ((a.type == ARR && b.type != ARR) || (a.type != ARR && b.type == ARR)) {
        return Var(false);
    }
    else {
        if (a == b) {  return Var(true); }
        else { return Var(false); }
    }
    return Var(false);
}

Var in(Var a, Var b) {
    std::vector<Var> arr;
    if (a.type == ARR) {
        arr = a.getArr();
    }
    else {
        arr = a.toARR().getArr();
    }
    int size = (int)arr.size();
    int result = -1;
    for (int i = 0; i < size; ++i) {
        if (eq(arr[i], b).getBool()) {
            result = i;
            break;
        }
    }
    return Var(result);
}

Var din(Var a, Var b) {
    std::vector<Var> arr;
    if (a.type == ARR) {
        arr = a.getArr();
    }
    else {
        arr = a.toARR().getArr();
    }
    int size = (int)arr.size();
    int result = -1;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == b) {
            result = i;
            break;
        }
    }
    return Var(result);
}

Var inall(Var a, Var b) {
    std::vector<Var> arr;
    if (a.type == ARR) {
        arr = a.getArr();
    }
    else {
        arr = a.toARR().getArr();
    }
    int size = (int)arr.size();
    std::vector<Var> result;
    for (int i = 0; i < size; ++i) {
        if (eq(arr[i], b).getBool()) {
            result.push_back(Var(i));
        }
    }
    if ((int)result.size() > 0) {
        return Var(result);
    }
    return Var(-1);
}

Var dinall(Var a, Var b) {
    std::vector<Var> arr;
    if (a.type == ARR) {
        arr = a.getArr();
    }
    else {
        arr = a.toARR().getArr();
    }
    int size = (int)arr.size();
    std::vector<Var> result;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == b) {
            result.push_back(Var(i));
        }
    }
    return Var(result);
}

Var rin(Var a, Var b, std::vector<Var> result) {
    std::vector<Var> arr;
    if (a.type == ARR) {
        arr = a.getArr();
    }
    else {
        arr = a.toARR().getArr();
    }
    int size = (int)arr.size();
    for (int i = 0; i < size; ++i) {
        if (arr[i].type == ARR) {
            if (eq(arr[i], b).getBool()) {
                result.push_back(Var(i));
                result.push_back(Var(true));
                break;
            }
            else {
                result.push_back(Var(i));
                result = rin(arr[i], b, result).arr;
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
            if (eq(arr[i], b).getBool()) {
                result.push_back(Var(i));
                result.push_back(Var(true));
                break;
            }
        }
    }
    if ((int)result.size() == 0) {
        return Var(-1);
    }
    return Var(result);
}

Var drin(Var a, Var b, std::vector<Var> result) {
    std::vector<Var> arr;
    if (a.type == ARR) {
        arr = a.getArr();
    }
    else {
        arr = a.toARR().getArr();
    }
    int size = (int)arr.size();
    for (int i = 0; i < size; ++i) {
        if (arr[i].type == ARR) {
            if (deq(arr[i], b).getBool()) {
                result.push_back(Var(i));
                break;
            }
            else {
                result.push_back(Var(i));
                result = drin(arr[i], b, result).arr;
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
            if (deq(arr[i], b).getBool()) {
                result.push_back(Var(i));
                break;
            }
        }
    }
    return Var(result);
}

Var srinall(Var a, Var b, std::vector<Var>* all_results, std::vector<Var> result) {
    std::vector<Var> arr;
    if (a.type == ARR) {
        arr = a.getArr();
    }
    else {
        arr = a.toARR().getArr();
    }
    int size = (int)arr.size();
    for (int i = 0; i < size; ++i) {
        if (arr[i].type == ARR) {
            if (eq(arr[i], b).getBool()) {
                result.push_back(Var(i));
                result.push_back(Var(true));
                (*all_results).push_back(Var(result));
                result.pop_back();
                result.pop_back();
            }
            else {
                result.push_back(Var(i));
                result = srinall(arr[i], b, all_results, result).arr;
                int size = (int)result.size();
                if (result[(long long int)size - 1].type == BLN && result[(long long int)size - 1].data.bln == true) {
                    (*all_results).push_back(Var(result));
                }
                else {
                    result.pop_back();
                }
            }
        }
        else {
            if (eq(arr[i], b).getBool()) {
                result.push_back(Var(i));
                result.push_back(Var(true));
                (*all_results).push_back(Var(result));
                result.pop_back();
                result.pop_back();
            }
        }
    }
    if ((int)result.size() == 0) {
        return Var(-1);
    }
    return Var(result);
}

Var drinall(Var a, Var b, std::vector<Var>* all_results, std::vector<Var> result) {
    std::vector<Var> arr;
    if (a.type == ARR) {
        arr = a.getArr();
    }
    else {
        arr = a.toARR().getArr();
    }
    int size = (int)arr.size();
    for (int i = 0; i < size; ++i) {
        if (arr[i].type == ARR) {
            if (deq(arr[i], b).getBool()) {
                result.push_back(Var(i));
                result.push_back(Var(true));
                (*all_results).push_back(Var(result));
                result.pop_back();
                result.pop_back();
            }
            else {
                result.push_back(Var(i));
                result = drinall(arr[i], b, all_results, result).arr;
                int size = (int)result.size();
                if (result[(long long int)size - 1].type == BLN && result[(long long int)size - 1].data.bln == true) {
                    (*all_results).push_back(Var(result));
                }
                else {
                    result.pop_back();
                }
            }
        }
        else {
            if (deq(arr[i], b).getBool()) {
                result.push_back(Var(i));
                result.push_back(Var(true));
                (*all_results).push_back(Var(result));
                result.pop_back();
                result.pop_back();
            }
        }
    }
    if ((int)result.size() == 0) {
        return Var(-1);
    }
    return Var(result);
}

Var rinall(std::wstring type, Var a, Var b) {
    std::vector<Var> all_results;
    if (type == L"STRICT" || type == L"strict") {
        srinall(a, b, &all_results);
    }
    else if(type == L"DYNAMIC" || type == L"dynamic"){
        drinall(a, b, &all_results);
    }
    if (all_results.size() == 0) {
        return Var(-1);
    }
    else {
        Var result = Var(std::vector<Var>());
        int size = (int)all_results.size();
        for (int i = 0; i < size; ++i) {
            all_results[i].popb();
            result.pushb(all_results[i]);
        }
        return result;
    }
}