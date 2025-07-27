#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

union Data {
    long long int ntg = 0;
    unsigned long long int untg;
    long double dbl;
    char chr;
    unsigned char uchr;
    bool bln;
};

enum Type {
    NTG,
    UNTG,
    DBL,
    CHR,
    UCHR,
    BLN,
    STR,
    NIL,
    UNKNOWN,
    ARR,
    MAP
};

class Var {
public:
    Data data;
    std::vector<Var> arr;
    std::map<std::wstring, Var> mp;
    std::wstring str = L"";
    Type type = NIL;
    //Конструкторы для обычны типов данных
    Var();
    Var(unsigned long long int untg);
    Var(long long int ntg);
    Var(long int ntg);
    Var(int ntg);
    Var(short int ntg);
    Var(unsigned long int ntg);
    Var(unsigned int ntg);
    Var(unsigned short int ntg);

    Var(long double dbl);
    Var(double dbl);
    Var(float dbl);

    Var(char chr);
    Var(unsigned char uchr);

    Var(bool bln);

    Var(std::wstring str);
    Var(const wchar_t* str); 
    
    Var(std::wstring t, int i);

    Var(std::vector<Var> v);
    Var(std::map<std::wstring, Var> m);

    //Геттеры обычных типов данных
    long long int getInt() const;
    unsigned long long int getUInt() const;
    long double getDouble() const;
    char getChar() const;
    unsigned char getUChar() const;
    bool getBool() const;
    std::wstring getWStr() const;
    std::vector<Var> getArr() const;
    std::map<std::wstring, Var> getMap() const;

    //Приведение типов
    Var toNTG() const;
    Var toUNTG() const;
    Var toDBL() const;
    Var toCHR() const;
    Var toUCHR() const;
    Var toBLN() const;
    Var toSTR() const;
    Var toARR() const;

    //Вывод данных и типа
    void print();
    std::wstring typeOf();

    //Работа с массивами, словарями и строками
    Var& operator[](int ind);
    Var& operator[](const wchar_t* str);
    Var& operator[](std::wstring str);
    Var& operator[](Var v);

    Var len() const;
    Var rev() const;
    Var in(Var sent) const;
    Var in(const wchar_t* sent) const;
    Var in(std::wstring sent) const;
   
    Var slice(int x, int y);
    Var slice(Var x, Var y);

    Var ltrim() const;
    Var rtrim() const;
    Var trim() const;
    Var repl(Var substr, Var newsubstr) const;
    Var repl(const wchar_t* substr, const wchar_t* newsubstr) const;
    Var repl(std::wstring substr, const std::wstring newsubstr) const;
    Var upper() const;
    Var lower() const;

    void pushb(Var v);
    Var popb();
    void pushf(Var val);
    Var popf();

    void clear();
    void erase(int x);
    Var erase(Var x);
    void erase(std::wstring x);
    void erase(const wchar_t* x);

    void insert_vector(Var x, Var val);
    
    void insert(Var str, Var val);
    void insert(std::wstring str, Var val);
    void insert(const wchar_t* str, Var val);

    Var split(Var delim) const;
    Var split(std::wstring delim) const;
    Var split(const wchar_t* delim) const;
    
    Var join(Var delim);
    Var join(std::wstring delim);
    Var join(const wchar_t* delim);
    
    Var merge(Var val) const;
    Var csize() const;
    //Вывод данных через поток
    friend std::wostream& operator<< (std::wostream& os, const Var& var);

    //Перегрузка присваивания
    Var& operator= (const Var& var);

    Var& operator= (const unsigned long long int& var);
    Var& operator= (const unsigned long int& var);
    Var& operator= (const unsigned int& var);
    Var& operator= (const unsigned short int& var);
    Var& operator= (const long long int& var);
    Var& operator= (const long int& var);
    Var& operator= (const int& var);
    Var& operator= (const short int& var);

    Var& operator= (const long double& var);
    Var& operator= (const double& var);
    Var& operator= (const float& var);

    Var& operator= (const char& var);
    Var& operator= (const unsigned char& var);

    Var& operator= (const bool& var);

    Var& operator= (const std::wstring& var);
    Var& operator= (const wchar_t* var);

    Var& operator= (std::vector<Var> v);
    Var& operator= (std::map<std::wstring, Var> m);

    //Математические операторы
    friend Var operator+(const Var& a, const Var& b);
    friend Var operator-(const Var& a, const Var& b);
    friend Var operator*(const Var& a, const Var& b);
    friend Var operator/(const Var& a, const Var& b);
    friend Var operator%(const Var& a, const Var& b);

    friend Var operator+=(Var& a, const Var& b);
    friend Var operator-=(Var& a, const Var& b);
    friend Var operator*=(Var& a, const Var& b);
    friend Var operator/=(Var& a, const Var& b);
    friend Var operator%=(Var& a, const Var& b);

    //Логичекие операторы
    friend bool operator==(const Var& a, const Var& b);
    friend bool operator!=(const Var& a, const Var& b);
    friend bool operator>(const Var& a, const Var& b);
    friend bool operator<=(const Var& a, const Var& b);
    friend bool operator<(const Var& a, const Var& b);
    friend bool operator>=(const Var& a, const Var& b);
    friend bool operator!(const Var& a);
};
//Обмен значениями
void swap(Var& a, Var& b);
//Строгое рекурсивное сравнение
Var eq(Var a, Var b);
//Нестрогое рекурсивное сравнение
Var deq(Var a, Var b);
//Строгий поиск значения по массиву 
Var in(Var a, Var b);
//Нестрогий поиск значения по массиву 
Var din(Var a, Var b);
//Строгий поиск всех значений по массиву 
Var inall(Var a, Var b);
//Нестрогий поиск всех значений по массиву 
Var dinall(Var a, Var b);
//Строгий рекурсивный поиск значения по массиву 
Var rin(Var a, Var b, std::vector<Var> result = std::vector<Var>());
//Нестрогий рекурсивный поиск значения по массиву 
Var drin(Var a, Var b, std::vector<Var> result = std::vector<Var>());
//Строгий рекурсивный поиск всех значений по массиву 
Var srinall(Var a, Var b, std::vector<Var>* all_results, std::vector<Var> result = std::vector<Var>());
//Нестрогий рекурсивный поиск всех значений по массиву 
Var drinall(Var a, Var b, std::vector<Var>* all_results, std::vector<Var> result = std::vector<Var>());
//Строгий рекурсивный поиск всех значений по массиву, агрегатная функция 
Var rinall(std::wstring type, Var a, Var b);
