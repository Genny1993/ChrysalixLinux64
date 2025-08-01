﻿#include <iostream>

#include "Parser.h"
#include "CTable.h"
#include "Helpers.h"
#include "LangLib.h"

void Parser::fileLoad(std::wstring file_name) {
    //Чтение файла в кодировке UTF-8
    this->file = file_name;
    this->file_content = loadFile(this->file);
}

void Parser::parse(Machine& m) {
    //Перебираем каждый символ в строке
    std::wstring str = L"";
    bool instruction_parameters = false;
    bool first_comment_char = false;
    bool is_long_comment = false;
    bool is_comment = false;
    bool is_string = false;
    bool escape = false;
    Lexeme instruction;
    std::vector<Lexeme> lexemes;
    lexemes.reserve(10000);

    for (wchar_t& c : this->file_content) {
        //Вырезаем комментарии, если они есть, игнорируем сиволы после начала комментария до конца строки
        if (is_comment) {
            //Если предыдущий знак был равен #
            if (first_comment_char == true) {
                //Если у нас многострочный комментарий
                if (is_long_comment == true) {
                    //и попадается знак #, многострочный комментарий заканчивается
                    if (c == L'#') {
                        is_long_comment = false;
                        is_comment = false;
                    }
                }
                else {
                    //Если предыдущий знак был # а многострочный комментарий не начался, начинаем многострочный комментарий
                    if (c == L'#') {
                        is_long_comment = true;
                    }
                }
                //В любом случае сбрасываем флаг первого символа
                first_comment_char = false;
            }
            else {
                //Если предыдущий знак  не был # и у нас длинный комментарий
                if (is_long_comment == true) {
                    //Если текущий знак # ставим флаг первого знака комментария
                    if (c == L'#') {
                        first_comment_char = true;
                    }
                }
                //если это однострочный комментарий, заканчиваем его с момента перевода на другую строку
                else {
                    if (c == L'\n') {
                        is_comment = false;
                        is_long_comment = false;
                        first_comment_char = false;
                    }
                }
            }

        }
        else {
            //Если у нас кавычка ' это значит, началась или кончилась строка. Игнорируем все синтаксические символы
            if (c == L'\'') {
                if (is_string == true) {
                    if (escape == false) {
                        is_string = false;
                    }
                }
                else {
                    is_string = true;
                }
                escape = false;
                str += c;
            }
            else {
                if (is_string == true) {
                    if (c == L'\\') {
                        if (escape == false) {
                            escape = true;
                        }
                        else {
                            escape = false;
                        }
                    }
                    else {
                        escape = false;
                    }
                    str += c;
                }
                else {
                    //Если у нас имеется знак #, у нас начался однострочный или многострочный комментарий
                    if (c == L'#') {
                        if (is_comment == false) {
                            is_comment = true;
                            first_comment_char = true;
                        }
                    }
                    else {
                        //Перебираем символы до тех пор, пока не найдем двоеточие :
                        //Это конец наименования инструкции
                        if (instruction_parameters == false) {
                            if (c == L':') {
                                str.erase(0, str.find_first_not_of(L" \n\r\t"));
                                str.erase(str.find_last_not_of(L" \n\r\t") + 1);
                                instruction.type = str;
                                str = L"";
                                //устанавливаем флаг, что начались параметры инструкции
                                instruction_parameters = true;
                            }
                            else {
                                //Иначе записываем символ в переменную с названием инструкции
                                str += c;
                            }
                        }
                        else {
                            //Парсим параметры инструкции. Если у нас запятая, параметр кончился.
                            if (c == ',') {
                                if (str != L"") {
                                    instruction.str_parameters.emplace_back(str);
                                    str = L"";
                                }
                            }
                            //если точка с запятой, инструкция вообще кончилась
                            else if (c == ';') {
                                if (str != L"") {
                                    instruction.str_parameters.emplace_back(str);
                                    str = L"";
                                }
                                lexemes.emplace_back(instruction);
                                instruction.str_parameters.clear();
                                instruction.type = L"";
                                instruction_parameters = false;
                            }
                            else {
                                str += c;
                            }
                        }
                    }
                }
            }
        }
    }


    //Парсим параметры, превращая литералы в объект VAR со значением
    int size = (int)lexemes.size();
    for (int i = 0; i < size; ++i) {
        try {
            int params_size = (int)lexemes[i].str_parameters.size();
            for (int j = 0; j < params_size; ++j) {
                std::wstring temp = lexemes[i].str_parameters[j];
                temp.erase(0, temp.find_first_not_of(L" \n\r\t"));
                temp.erase(temp.find_last_not_of(L" \n\r\t") + 1);
                if (temp[0] == L'$' || temp[0] == L'&') {
                    lexemes[i].parameters.emplace_back(Var(temp));
                }
                else if (temp.substr(0, 3) == std::wstring_view(L"NTG") || temp.substr(0, 3) == std::wstring_view(L"ntg")) {
                    lexemes[i].parameters.emplace_back(Var(temp.erase(0, 3)).toNTG());
                }
                else if (temp.substr(0, 4) == std::wstring_view(L"UNTG") || temp.substr(0, 4) == std::wstring_view(L"untg")) {
                    lexemes[i].parameters.emplace_back(Var(temp.erase(0, 4)).toUNTG());
                }
                else if (temp.substr(0, 3) == std::wstring_view(L"DBL") || temp.substr(0, 3) == std::wstring_view(L"dbl")) {
                    lexemes[i].parameters.emplace_back(Var(temp.erase(0, 3)).toDBL());
                }
                else if (temp.substr(0, 3) == std::wstring_view(L"CHR") || temp.substr(0, 3) == std::wstring_view(L"chr")) {
                    lexemes[i].parameters.emplace_back(Var(temp.erase(0, 3)).toCHR());
                }
                else if (temp.substr(0, 4) == std::wstring_view(L"UCHR") || temp.substr(0, 4) == std::wstring_view(L"uchr")) {
                    lexemes[i].parameters.emplace_back(Var(temp.erase(0, 4)).toUCHR());
                }
                else if (temp == std::wstring_view(L"ARR") || temp == std::wstring_view(L"arr")) {
                    std::vector<Var> v;
                    v.reserve(1000);
                    lexemes[i].parameters.emplace_back(Var(v));
                }
                else if (temp == std::wstring_view(L"MAP") || temp == std::wstring_view(L"map")) {
                    std::unordered_map<std::wstring, Var> map;
                    map.reserve(1000);
                    lexemes[i].parameters.emplace_back(Var(map));
                }
                else if (temp == std::wstring_view(L"TRUE") || temp == std::wstring_view(L"true")) {
                    lexemes[i].parameters.emplace_back(Var(true));
                }
                else if (temp == std::wstring_view(L"FALSE") || temp == std::wstring_view(L"false")) {
                    lexemes[i].parameters.emplace_back(Var(false));
                }
                else if (temp == std::wstring_view(L"NIL") || temp == std::wstring_view(L"nil")) {
                    lexemes[i].parameters.emplace_back(Var());
                }
                else if (temp[0] == L'\'') {
                    std::wstring s_temp = temp;
                    std::wstring str = s_temp.erase(0, s_temp.find_first_not_of(L"\'"));
                    str = s_temp.erase(s_temp.find_last_not_of(L"\'") + 1);
                   
                    std::wstring new_str = L"";
                    bool escape_ch = false;
                    for (wchar_t& c : str) {
                        if (c != L'\\' && !escape_ch) {
                            new_str += c;
                            continue;
                        }
                        if (c == L'\\' && !escape_ch) {
                            escape_ch = true;
                            continue;
                        }
                        if (escape_ch) {
                            switch (c) {
                            case L't':
                                new_str += L'\t';
                                break;
                            case L'n':
                                new_str += L'\n';
                                break;
                            case L'a':
                                new_str += L'\a';
                                break;
                            case L'q':
                                new_str += L'\'';
                                break;
                            case L'b':
                                new_str += L'\b';
                                break;
                            case L'f':
                                new_str += L'\f';
                                break;
                            case L'r':
                                new_str += L'\r';
                                break;
                            case L'v':
                                new_str += L'\v';
                                break;
                            case L'"':
                                new_str += L'"';
                                break;
                            case L'?':
                                new_str += L'?';
                                break;
                            case L'\'':
                                new_str += L'\'';
                                break;
                            case L'\\':
                                new_str += L'\\';
                            }
                            escape_ch = false;
                            continue;
                        }
                    }
                    lexemes[i].parameters.emplace_back(Var(new_str));
                } //Пытаемся работать с числами, если не указан тип данных
                else if (temp[0] == L'0'
                    || temp[0] == L'1'
                    || temp[0] == L'2'
                    || temp[0] == L'3'
                    || temp[0] == L'4'
                    || temp[0] == L'5'
                    || temp[0] == L'6'
                    || temp[0] == L'7'
                    || temp[0] == L'8'
                    || temp[0] == L'9'
                    || temp[0] == L'+'
                    || temp[0] == L'-') {
                    Var numberdbl = Var(temp).toDBL();
                    Var numberntg = Var(temp).toNTG();
                    if (numberdbl == numberntg) {
                        lexemes[i].parameters.emplace_back(numberntg);
                    }
                    else {
                        lexemes[i].parameters.emplace_back(numberdbl);
                    }
                }
                else {
                    throw std::wstring{temp + LangLib::getTrans(L": Неизвестный литерал\n")};

                }
            }
        }
        catch (const std::wstring& error_message) {
            throw std::wstring{ LangLib::getTrans(L"Синтаксическая ошибка в инструкции ") + std::to_wstring(i + 1) + LangLib::getTrans(L": ") + error_message + LangLib::getTrans(L"\n")};
        }
    }
    
    int i = 1;
    Instruction inst;

    //Таблица опкодов
    CTable table;

    for (Lexeme& lexeme : lexemes) {
        try {
            inst.opCode = table.opCodeMap.at(lexeme.type);
            inst.as_string = lexeme.type + L":";
        }
        catch (std::out_of_range& ex) {
            std::string temp = ex.what();
            throw std::wstring{ LangLib::getTrans(L"Синтаксическая ошибка в инструкции ") + std::to_wstring(i) + LangLib::getTrans(L": ") + lexeme.type + LangLib::getTrans(L": Неизвестная инструкция\n") };
        }

        inst.parameters = lexeme.parameters;
        int max_size = (int)lexeme.str_parameters.size();
        for (int param = 0; param < max_size; ++param) {
            inst.as_string += lexeme.str_parameters[param];
            if (param != max_size - 1) {
                inst.as_string += L",";
            }
        }
        inst.as_string += L";";
        m.instructions.emplace_back(inst);
        ++i;
    }
}