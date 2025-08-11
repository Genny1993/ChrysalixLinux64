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

std::vector<Instruction> Parser::parse(std::wstring string) {

    std::vector<Lexeme> lexemes = this->parseLex(string);

    std::vector<Instruction> instructions;

    int size = (int)lexemes.size();
    for(int i = 0; i < size; ++i) {
        try {
            instructions.emplace_back(this->toInstruction(lexemes[i]));
        } catch (const std::wstring& error_message) {
            std::wstring str_instr = getInstBlockAsString(lexemes[i]);
            throw std::wstring{  LangLib::getTrans(L"Синтаксическая ошибка в инструкции ") + std::to_wstring(i + 1) + L" (" + str_instr + L")" + LangLib::getTrans(L": ") + error_message };
        }
    }

    return instructions;
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
        s_temp.erase(0, s_temp.find_first_not_of(L" \n\r\t"));
        s_temp.erase(s_temp.find_last_not_of(L" \n\r\t") + 1);
        s_temp.erase(0, 1);
        s_temp.erase(s_temp.size() - 1);
        std::wstring str = s_temp;
                   
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
    int parenthesis_count = 0;
    bool is_nested = false;

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
                                instruction.type = LEXTYPE::INSTR;
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
                            if(is_nested == false) {
                                //Если скобка, это вложенная инструкция
                                if (c == L'(') {
                                    ++parenthesis_count;
                                    is_nested = true;
                                    std::wstring check = L"";
                                    int size_str = (int)str.size();
                                    for(int i = 0; i < size_str; ++i) {
                                        if(str[i] != L' ' && str[i] != '\n' && str[i] != '\r' && str[i] != L'\t') {
                                            check += c;
                                        }
                                    }
                                    if(check != L"") {
                                        throw std::wstring{ str + LangLib::getTrans(L": Лишняя строка перед вложенной инструкцией\n") };
                                    }
                                    str +=c;
                                }
                                //Парсим параметры инструкции. Если у нас запятая, параметр кончился.
                                else if (c == L',') {
                                    str.erase(0, str.find_first_not_of(L" \n\r\t"));
                                    str.erase(str.find_last_not_of(L" \n\r\t") + 1);
                                    if (str != L"") {
                                        Lexeme temp;
                                        temp.type =  LEXTYPE::PAR;
                                        temp.content = str;
                                        instruction.lex_parameters.emplace_back(temp);
                                        str = L"";
                                    }
                                }
                                //если точка с запятой, инструкция вообще кончилась
                                else if (c == L';') {
                                    str.erase(0, str.find_first_not_of(L" \n\r\t"));
                                    str.erase(str.find_last_not_of(L" \n\r\t") + 1);
                                    if (str != L"") {
                                        Lexeme temp;
                                        temp.type =  LEXTYPE::PAR;
                                        temp.content = str;
                                        instruction.lex_parameters.emplace_back(temp);
                                        str = L"";
                                    }
                                    lexemes.emplace_back(instruction);
                                    instruction.lex_parameters.clear();
                                    instruction.content = L"";
                                    instruction_parameters = false;
                                }
                                else {
                                    str += c;
                                }
                            } else {
                                //если открывающая скобка
                                if(c == L'(') {
                                    str+=c;
                                    if(parenthesis_count > 0) {
                                        ++parenthesis_count;
                                    } else if(parenthesis_count == 0) {
                                        throw std::wstring{ str + LangLib::getTrans(L": Лишняя открывающая скобка '('\n") };
                                    }
                                //Если закрывающая
                                } else if(c == L')') {
                                    str+=c;
                                    --parenthesis_count;
                                    if(parenthesis_count == 0 && i == (size_str - 1)) {
                                        int size = (int)str.size();
                                        std::wstring check = L"";
                                        for(int i = size -1; i >= 0; --i) {
                                            if(str[i] == L')') {
                                                break;
                                            }
                                            if(str[i] != L' ' && str[i] != L'\t' && str[i] != L'\n' && str[i] != L'\r') {
                                                check += str[i];
                                            }
                                        }
                                        if(check != L"") {
                                            reverse(check.begin(), check.end());
                                            throw std::wstring{ check + LangLib::getTrans(L": Лишний символ после вложенной инструкции\n") };
                                        }
                                        str.erase(0, str.find_first_not_of(L" \n\r\t"));
                                        str.erase(str.find_last_not_of(L" \n\r\t") + 1);
                                        str.erase(0, 1);
                                        str.erase(str.size() - 1);
                                        str.erase(0, str.find_first_not_of(L" \n\r\t"));
                                        str.erase(str.find_last_not_of(L" \n\r\t") + 1);
                                        
                                        if(str == L"") {
                                            throw std::wstring{ LangLib::getTrans(L"Пустая вложенная инструкция '()'\n") };
                                        }

                                        Lexeme temp;
                                        temp.type =  LEXTYPE::INSTBLOCK;
                                        //Добавляем конец инструкции ;, чтобы избавиться от излишних ; во вложенных инструкциях
                                        if(str[str.size() - 1] != L';' ) {
                                            str += L';';
                                        }
                                        std::vector<Lexeme> tlexemes = parseLex(str);

                                        int lsize = (int)tlexemes.size();
                                        for(int i = 0; i < lsize; ++i) {
                                            temp.lex_parameters.emplace_back(tlexemes[i]);
                                        }
                                        instruction.lex_parameters.emplace_back(temp);
                                        str = L"";
                                        is_nested = false;
                                        lexemes.emplace_back(instruction);
                                        instruction.lex_parameters.clear();
                                        instruction.content = L"";
                                        instruction_parameters = false;

                                        is_nested = false;
                                        str = L"";
                                    } else if(parenthesis_count < 0) {
                                        throw std::wstring{ str + LangLib::getTrans(L": Лишняя закрывающая скобка ')'\n") };
                                    }

                                //Если символ начала другой команды
                                }  else if(c == L',') {
                                    if(parenthesis_count == 0) {          
                                        int size = (int)str.size();
                                        std::wstring check = L"";
                                        for(int i = size -1; i >= 0; --i) {
                                            if(str[i] == ')') {
                                                break;
                                            }
                                            if(str[i] != L' ' && str[i] != L'\t' && str[i] != L'\n' && str[i] != L'\r') {
                                                check += str[i];
                                            }
                                        }
                                        if(check != L"") {
                                            reverse(check.begin(), check.end());
                                            throw std::wstring{ check + LangLib::getTrans(L": Лишний символ после вложенной инструкции\n") };
                                        }
                                        str.erase(0, str.find_first_not_of(L" \n\r\t"));
                                        str.erase(str.find_last_not_of(L" \n\r\t") + 1);
                                        str.erase(0, 1);
                                        str.erase(str.size() - 1);
                                        str.erase(0, str.find_first_not_of(L" \n\r\t"));
                                        str.erase(str.find_last_not_of(L" \n\r\t") + 1);

                                        if(str == L"") {
                                            throw std::wstring{ LangLib::getTrans(L"Пустая вложенная инструкция '()'\n") };
                                        }

                                        Lexeme temp;
                                        temp.type =  LEXTYPE::INSTBLOCK;
                                        //Добавляем конец инструкции ;, чтобы избавиться от излишних ; во вложенных инструкциях
                                        if(str[str.size() - 1] != L';' ) {
                                            str += L';';
                                        }
                                        std::vector<Lexeme> tlexemes = parseLex(str);

                                        int lsize = (int)tlexemes.size();
                                        for(int i = 0; i < lsize; ++i) {
                                            temp.lex_parameters.emplace_back(tlexemes[i]);
                                        }
                                        instruction.lex_parameters.emplace_back(temp);
                                        str = L"";
                                        is_nested = false;      
                                    } else if (parenthesis_count > 0 ){
                                        str +=c;
                                    } else {
                                        throw std::wstring{ str + LangLib::getTrans(L": Лишняя закрывающая скобка ')'\n") };
                                    }
                                //Если символ конца инструкции
                                } else if (c == L';') {
                                    if(parenthesis_count == 0) {
                                        int size = (int)str.size();
                                        std::wstring check = L"";
                                        for(int i = size -1; i >= 0; --i) {
                                            if(str[i] == ')') {
                                                break;
                                            }
                                            if(str[i] != L' ' && str[i] != L'\t' && str[i] != L'\n' && str[i] != L'\r') {
                                                check += str[i];
                                            }
                                        }
                                        if(check != L"") {
                                            reverse(check.begin(), check.end());
                                            throw std::wstring{ check + LangLib::getTrans(L": Лишний символ после вложенной инструкции\n") };
                                        }

                                        str.erase(0, str.find_first_not_of(L" \n\r\t"));
                                        str.erase(str.find_last_not_of(L" \n\r\t") + 1);
                                        str.erase(0, 1);
                                        str.erase(str.size() - 1);
                                        str.erase(0, str.find_first_not_of(L" \n\r\t"));
                                        str.erase(str.find_last_not_of(L" \n\r\t") + 1);

                                        if(str == L"") {
                                            throw std::wstring{ LangLib::getTrans(L"Пустая вложенная инструкция '()'\n") };
                                        }

                                        Lexeme temp;
                                        temp.type =  LEXTYPE::INSTBLOCK;
                                        //Добавляем конец инструкции ;, чтобы избавиться от излишних ; во вложенных инструкциях
                                        if(str[str.size() - 1] != L';' ) {
                                            str += L';';
                                        }
                                        std::vector<Lexeme> tlexemes = parseLex(str);

                                        int lsize = (int)tlexemes.size();
                                        for(int i = 0; i < lsize; ++i) {
                                            temp.lex_parameters.emplace_back(tlexemes[i]);
                                        }
                                        instruction.lex_parameters.emplace_back(temp);
                                        str = L"";
                                        is_nested = false;
                                        lexemes.emplace_back(instruction);
                                        instruction.lex_parameters.clear();
                                        instruction.content = L"";
                                        instruction_parameters = false;

                                    } else if (parenthesis_count > 0 ){
                                        str += c;
                                    } else {
                                        throw std::wstring{ str + LangLib::getTrans(L": Лишняя закрывающая скобка ')'\n") };
                                    }
                                } else if(parenthesis_count > 0 && i == (size_str - 1)) {
                                    throw std::wstring{ str + LangLib::getTrans(L": Лишняя открывающая скобка '('\n") };
                                } else {
                                    str +=c;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(lexemes.size() == 0) {
        throw std::wstring{ LangLib::getTrans(L"Входная строка не является инструкцией: " + val + L"\n") };
    }
    return lexemes;
}

Instruction Parser::toInstruction(Lexeme lex) {
    CTable table;
    if(lex.type ==  LEXTYPE::INSTR) {
        Instruction inst;
        try {
            inst.opCode = table.opCodeMap.at(lex.content);
            inst.as_string = lex.content + L":";
        }
        catch (std::out_of_range& ex) {
            //вывод инструкции
            std::string temp = ex.what();
            throw std::wstring{ lex.content + LangLib::getTrans(L": Неизвестная инструкция\n") };
        }

        int size = (int)lex.lex_parameters.size();
        const std::vector<Lexeme>& parameters =  lex.lex_parameters;
        for (int i = 0; i < size; ++i) {
            if(parameters[i].type == LEXTYPE::PAR) {
                inst.as_string += parameters[i].content;
            } else if(parameters[i].type == LEXTYPE::INSTBLOCK) {
                 inst.as_string += getInstBlockAsString(parameters[i]);
            }
            if(i < size - 1) {
                inst.as_string += L", ";
            } else {
                 inst.as_string += L";";
            }
            try {
                if(parameters[i].type == LEXTYPE::PAR) {
                    //Сделать инструкцию в строковом виде для вывода ошибок
                    Var parsed = parseVar(parameters[i].content, i);
                    inst.parameters.emplace_back(parsed);
                } else if(parameters[i].type == LEXTYPE::INSTBLOCK) {
                    Var result;
                    result.type = Type::INST;

                    const std::vector<Lexeme>& inst_block = parameters[i].lex_parameters;
                    int block_size = (int)inst_block.size();

                    for(int j = 0; j < block_size; ++j) {
                        result.instructions.emplace_back(toInstruction(inst_block[j]));
                    }
                    inst.parameters.emplace_back(result);
                }
            }
            catch (const std::wstring& error_message) {
                throw std::wstring{ error_message };
            }
        }
        return inst;
    } else  {
        throw std::wstring{ LangLib::getTrans(L"Неверный тип лексемы\n") };
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

std::wstring showLexeme(Lexeme lex) {
    if(lex.type ==  LEXTYPE::INSTR) {
        std::wstring str = L"[INSTR]" + lex.content + L": ";
        int size = (int)lex.lex_parameters.size();
        for(int i = 0; i < size; ++i) {
            str += showLexeme(lex.lex_parameters[i]);
            if(i < size -1) {
                str += L", ";
            }
        }
        return str;
    } else if(lex.type ==  LEXTYPE::PAR) {
        return L"[PAR]" + lex.content;
    } else if(lex.type ==  LEXTYPE::INSTBLOCK) {
        std::wstring str = L"[INSTBLOCK](";
        int size = (int)lex.lex_parameters.size();
        for(int i = 0; i < size; ++i) {
            str += showLexeme(lex.lex_parameters[i]);
            if(i < size -1) {
                str += L", ";
            } else {
                str+= L";";
            }

        }
        str += L")";
        return str;
    } else {
        return L"ERROR";
    }
}

std::wstring showInstruction(Instruction inst) {
    std::wstring str = L"";
    str += std::to_wstring(inst.opCode) + L": ";
    int size = (int)inst.parameters.size();
    for(int i = 0; i < size; ++i) {
        if(inst.parameters[i].type == Type::INST) {
            str += L"(";
            int size_iblock = (int)inst.parameters[i].instructions.size();
            for(int j = 0; j < size_iblock; ++j) {
                str += showInstruction(inst.parameters[i].instructions[j]);
            }
            str += L")";
            if(i < size - 1) {
                str += L", ";
            } else {
                str += L";";
            }
        } else {
            str += inst.parameters[i].toSTR().str;
            if(i < size - 1) {
                str += L", ";
            } else {
                str += L";";
            }
        }
    }
    return str;
}

std::wstring getInstBlockAsString(Lexeme block) {
    if(block.type ==  LEXTYPE::INSTR) {
        std::wstring str = block.content + L": ";
        int size = (int)block.lex_parameters.size();
        for(int i = 0; i < size; ++i) {
            str += getInstBlockAsString(block.lex_parameters[i]);
            if(i < size -1) {
                str += L", ";
            }
        }
        return str;
    } else if(block.type ==  LEXTYPE::PAR) {
        return block.content;
    } else if(block.type ==  LEXTYPE::INSTBLOCK) {
        std::wstring str = L"(";
        int size = (int)block.lex_parameters.size();
        for(int i = 0; i < size; ++i) {
            str += getInstBlockAsString(block.lex_parameters[i]);
            if(i < size -1) {
                str += L", ";
            }
        }
        str += L")";
        return str;
    } else {
        return L"ERROR";
    }
}