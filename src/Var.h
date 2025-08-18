#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <string_view>
#include <cmath>

#include "Instruction.h"

class Instruction;

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
    MAP,
    INST,
};

class Var {
private:
    Var eq_recursive(const std::wstring &type, const Var &a, const Var &b) const;
    Var rin_recursive(const std::wstring &type, const Var &a, const Var &b, std::vector<Var> &result) const;
    Var rinall_recursive(const std::wstring &type, const Var &a, const Var &b, std::vector<Var>* all_results, std::vector<Var> result = std::vector<Var>()) const;
public:
    Data data;
    std::vector<Var> arr;
    std::unordered_map<std::wstring, Var> mp;
    std::wstring str = L"";
    Type type = NIL;
    std::vector<Instruction> instructions;
    bool is_const = false;
    //Конструкторы для обычны типов данных
    Var(const Var&) = default;
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
    Var(std::unordered_map<std::wstring, Var> m);

    //Геттеры обычных типов данных
    long long int getInt() const;
    unsigned long long int getUInt() const;
    long double getDouble() const;
    char getChar() const;
    unsigned char getUChar() const;
    bool getBool() const;
    std::wstring getWStr() const;
    std::vector<Var> getArr() const;
    std::unordered_map<std::wstring, Var> getMap() const;

    //Приведение типов
    Var toNTG() const;
    Var toUNTG() const;
    Var toDBL() const;
    Var toCHR() const;
    Var toUCHR() const;
    Var toBLN() const;
    Var toSTR() const;
    Var toARR() const;
    Var toINST() const;

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
   
    Var slice(const int &x, const int &y) const;
    Var slice(const Var &x, const Var &y) const;
    Var sortarr(const std::wstring &type) const;
    //Проверка на эквивалентность массивов
    Var eq(const std::wstring &type, const Var &b) const;
    //Функция, оставляющая уникальные значения
    Var uniq(const std::wstring &type) const;
    //Поиск значения по массиву 
    Var in(const std::wstring &type, const Var &b) const;
    //Поиск всех значений по массиву 
    Var inall(const std::wstring &type, const Var &b) const;
    //Рекурсивный поиск значения по массиву
    Var rin(const std::wstring &type, const Var &b, std::vector<Var> result = std::vector<Var>()) const;
    //Рекурсивный поиск всех значений по массиву.
    Var rinall(const std::wstring &type, const Var &b) const;
    //Возвращает пересечение значений массивов
    Var intersect(const std::wstring &type, const Var &b) const;
    //Возвращает непересекающиеся значения массивов
    Var notintersect(const std::wstring &type, const Var &b) const;
    //Возвращает пересечение значений словарей
    Var kvintersect(const std::wstring &type, const Var &b) const;
    //Возвращает непересекающиеся значения словарей
    Var kvnotintersect(const std::wstring &type, const Var &b) const;
    //Массив в строку с разделителем
    Var arrtostr(const Var &delim) const;
    //Сумма всех элементов массива
    Var sum() const;
    //Среднее арифметическое массива
    Var avg() const;
    //Минимальное значение массива
    Var min() const;
    //Максимальное значение массива
    Var max() const;
    //Разница между максимальным и минимальным значением
    Var range() const;
    //Поиск медианного значения
    Var median() const;
    //Поиск самых частых значений
    Var mode() const;
    //Стандартное отклонение массива
    Var stddev() const;
    //Проверка ключа на существование
    Var kexist(const Var &key) const;

    Var ltrim() const;
    Var rtrim() const;
    Var trim() const;
    Var repl(Var substr, Var newsubstr) const;
    Var repl(const wchar_t* substr, const wchar_t* newsubstr) const;
    Var repl(std::wstring substr, const std::wstring newsubstr) const;
    Var upper() const;
    Var lower() const;

    //Работа с массивами
    void pushb(const Var &v);
    Var popb();
    void pushf(const Var &val);
    Var popf();
    //Добавление элемента в MAP
    void push(const Var &key, const Var &val);

    void clear();
    void erase(const int &x);
    Var erase(const Var &x);
    void erase(const std::wstring &x);
    void erase(const wchar_t* x);

    void insert_vector(const Var &x, const Var &val);
    
    void insert(Var str, Var val);
    void insert(std::wstring str, Var val);
    void insert(const wchar_t* str, Var val);

    Var split(Var delim) const;
    Var split(std::wstring delim) const;
    Var split(const wchar_t* delim) const;
    
    Var join(Var delim);
    Var join(std::wstring delim);
    Var join(const wchar_t* delim);
    
    Var merge(const Var &val) const;
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
    Var& operator= (std::unordered_map<std::wstring, Var> m);

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

namespace std {
    template <>
    struct hash<Var> {
        std::size_t operator()(const Var& v) const noexcept {
            return  std::hash<std::wstring>{}(v.str);
        }
    };
}