#include <iostream>

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
    std::vector<Lexeme> lexemes = parseLex(this->file_content);

    //Парсим параметры, превращая литералы в объект VAR со значением
    int size = (int)lexemes.size();
    for (int i = 0; i < size; ++i) {
        try {
            int params_size = (int)lexemes[i].lex_parameters.size();
            for (int j = 0; j < params_size; ++j) {
                Var parsed = parseVar(lexemes[i].lex_parameters[j].content, i);
                lexemes[i].parameters.emplace_back(parsed);
            }
        }
        catch (const std::wstring& error_message) {
            std::wstring str_instr = L"";
            str_instr += lexemes[i].content + L": ";
            int params_size = (int)lexemes[i].lex_parameters.size();
            for (int j = 0; j < params_size; ++j) {
                str_instr += lexemes[i].lex_parameters[j].content;
                if(j < params_size - 1) {
                    str_instr += L", ";
                } else {
                    str_instr += L";";
                }
            }
            throw std::wstring{ LangLib::getTrans(L"Синтаксическая ошибка в инструкции ") + std::to_wstring(i + 1) + L" (" + str_instr + L")" + LangLib::getTrans(L": ") + error_message };
        }
    }
    
    int i = 1;
    Instruction inst;

    //Таблица опкодов
    CTable table;

    for (Lexeme& lexeme : lexemes) {
        try {
            inst.opCode = table.opCodeMap.at(lexeme.content);
            inst.as_string = lexeme.content + L":";
        }
        catch (std::out_of_range& ex) {
            std::string temp = ex.what();
            std::wstring str_instr = L"";
            str_instr += lexeme.content + L": ";
            int params_size = (int)lexeme.lex_parameters.size();
            for (int j = 0; j < params_size; ++j) {
                str_instr += lexeme.lex_parameters[j].content;
                if(j < params_size - 1) {
                    str_instr += L", ";
                } else {
                    str_instr += L";";
                }
            }
            throw std::wstring{ LangLib::getTrans(L"Синтаксическая ошибка в инструкции ") + std::to_wstring(i) + L" (" + str_instr + L")" + LangLib::getTrans(L": ") + lexeme.content + LangLib::getTrans(L": Неизвестная инструкция\n") };
        }
        
        int size = (int)lexeme.parameters.size();
        for(int i = 0; i < size; ++i) {
            inst.parameters.emplace_back(lexeme.parameters[i]);
        }
        int max_size = (int)lexeme.lex_parameters.size();
        for (int param = 0; param < max_size; ++param) {
            inst.as_string += lexeme.lex_parameters[param].content;
            if (param != max_size - 1) {
                inst.as_string += L",";
            }
        }
        inst.as_string += L";";
        m.instructions.emplace_back(inst);
        inst.opCode = NOP;
        inst.as_string.clear();
        inst.parameters.clear();
        ++i;
    }
}

Var Parser::parseVar(std::wstring val, int instruction) {
    std::wstring temp = val;
    temp.erase(0, temp.find_first_not_of(L" \n\r\t"));
    temp.erase(temp.find_last_not_of(L" \n\r\t") + 1);
    if (temp[0] == L'$') {
        size_t is_arr = temp.find(L"[");
        if (is_arr != std::wstring::npos) {
            //Проверка на пустые скобки
            std::wstring check = L"";
            for (wchar_t& c : temp) {
                if(c != L' ' && c != '\n' && c!= L'\t' && c != L'\r') {
                    check += c;
                }
            }
            size_t is_empty_braces = check.find(L"[]");
            if (is_empty_braces != std::wstring::npos) {
                throw std::wstring{ LangLib::getTrans(L"Пустые скобки []\n") };
            }

            std::wstring name;
            std::vector<std::wstring> parts;
            parts.reserve(255);
            bool indexes = false;
            int braces_count = 0;
            bool new_brace = false;
            std::wstring part = L"";
            for (wchar_t& c : temp) {
                if(indexes == false) {
                    if(c == L'[') {
                        indexes = true;
                        ++braces_count;
                    } else {
                        name += c;
                }
                } else {
                    if(braces_count > 0 || (braces_count == 0 && new_brace == true)) {
                        if(c == L'[') {
                            if(braces_count > 0) {
                                part += c;
                            }
                            ++braces_count;
                            new_brace = false;
                        } else if(c == L']') {
                            --braces_count;
                            if(braces_count > 0) {
                                part += c;
                            }
                            if(braces_count == 0){
                                new_brace = true;
                            }
                        } else {
                            if(new_brace && c != L' ' && c != L'\t' && c!= L'\n' && c!= '\r') {
                                throw std::wstring{ LangLib::getTrans(L"Лишний символ между скобок: ") + c + L"\n" };
                            } else {
                                if(c != L' ' && c != L'\t' && c!= L'\n' && c!= '\r') {
                                    part += c;
                                }
                            }
                        }
                    }
                    if(braces_count == 0 && part != L"") {
                        parts.emplace_back(part);
                        part = L"";
                        continue;
                    } 
                    if(braces_count < 0) {
                        throw std::wstring{  LangLib::getTrans(L"Лишняя закрывающая скобка ']'\n") };
                    }
                }
            }
            if(braces_count > 0) {
                throw std::wstring{ LangLib::getTrans(L"Лишняя открывающая скобка '['\n") };
            }
            Var parsed;
            parsed.str = name;
            parsed.type = STR;
            int size = (int)parts.size();
            for(int i = 0; i < size; ++i) {
                Var temp = parseVar(parts[i], instruction);
                parsed.arr.emplace_back(parseVar(parts[i], instruction));
            }
            return parsed; 
        } else {
            return Var(temp);
        }
    }
    else if(temp[0] == L'&') {
        return Var(temp);
    }
    else if (temp.substr(0, 3) == std::wstring_view(L"NTG") || temp.substr(0, 3) == std::wstring_view(L"ntg")) {
        return Var(temp.erase(0, 3)).toNTG();
    }
    else if (temp.substr(0, 4) == std::wstring_view(L"UNTG") || temp.substr(0, 4) == std::wstring_view(L"untg")) {
        return Var(temp.erase(0, 4)).toUNTG();
    }
    else if (temp.substr(0, 3) == std::wstring_view(L"DBL") || temp.substr(0, 3) == std::wstring_view(L"dbl")) {
        return Var(temp.erase(0, 3)).toDBL();
    }
    else if (temp.substr(0, 3) == std::wstring_view(L"CHR") || temp.substr(0, 3) == std::wstring_view(L"chr")) {
        return Var(temp.erase(0, 3)).toCHR();
    }
    else if (temp.substr(0, 4) == std::wstring_view(L"UCHR") || temp.substr(0, 4) == std::wstring_view(L"uchr")) {
        return Var(temp.erase(0, 4)).toUCHR();
    }
    else if (temp == std::wstring_view(L"ARR") || temp == std::wstring_view(L"arr")) {
        std::vector<Var> v;
        v.reserve(1000);
        return Var(v);
    }
    else if (temp == std::wstring_view(L"MAP") || temp == std::wstring_view(L"map")) {
        std::unordered_map<std::wstring, Var> map;
        map.reserve(1000);
        return Var(map);
    }
    else if (temp == std::wstring_view(L"TRUE") || temp == std::wstring_view(L"true")) {
        return Var(true);
    }
    else if (temp == std::wstring_view(L"FALSE") || temp == std::wstring_view(L"false")) {
        return Var(false);
    }
    else if (temp == std::wstring_view(L"NIL") || temp == std::wstring_view(L"nil")) {
        return Var();
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
        return Var(new_str);
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
            return numberntg;
        }
        else {
            return numberdbl;
        }
    }
    else {
        throw std::wstring{temp + LangLib::getTrans(L": Неизвестный литерал\n")};
    }
    return Var();
}

std::vector<Lexeme> Parser::parseLex(std::wstring val) {
    //Перебираем каждый символ в строке
    std::wstring str = L"";
    bool instruction_parameters = false;
    bool first_comment_char = false;
    bool is_long_comment = false;
    bool is_comment = false;
    bool is_string = false;
    bool escape = false;
    bool parenthesis_count = 0;

    Lexeme instruction;
    std::vector<Lexeme> lexemes;
    lexemes.reserve(10000);

    int size_str = (int)val.size();
    for(int i = 0; i < size_str; ++i) {
        wchar_t c = val[i]; 
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
                                instruction.type = L"INST";
                                instruction.content = str;
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
                                    Lexeme temp;
                                    temp.type = L"PAR";
                                    temp.content = str;
                                    instruction.lex_parameters.emplace_back(temp);
                                    str = L"";
                                }
                            }
                            //если точка с запятой или перевод строки или конец строки, инструкция вообще кончилась
                            else if (c == ';' || c == '\n' || i == (size_str - 1)) {
                                if (str != L"") {
                                    Lexeme temp;
                                    temp.type = L"PAR";
                                    if(i == (size_str - 1)) {
                                        temp.content = str + c;
                                    } else {
                                        temp.content = str;
                                    }
                                    instruction.lex_parameters.emplace_back(temp);
                                    str = L"";
                                }
                                lexemes.emplace_back(instruction);
                                instruction.lex_parameters.clear();
                                instruction.type = L"";
                                instruction.content = L"";
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
}

std::wstring showVar(Var var) {
    std::wstring str = L"";
    if(var.arr.size() >0) {
        str += var.str + L": ";
        int sz = var.arr.size();
        for(int i = 0; i < sz; ++i) {
            if(var.arr[i].arr.size() > 0) {
                str += L"(" + showVar(var.arr[i]) + L"), ";
            } else {
                str += var.arr[i].toSTR().str + L", ";
            }
        }
    } else {
        str = var.toSTR().str;
    }
    return str;
}