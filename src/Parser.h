#pragma once

#include <string_view>

#include "Var.h"
#include "Machine.h"

enum LEXTYPE {
	INSTR,
	PAR,
	INSTBLOCK
};

class Lexeme {
public:
	LEXTYPE type;
	std::wstring content;
	std::vector<Lexeme> lex_parameters;
	std::vector<Var> parameters;

	Lexeme() {
		parameters.reserve(100);
	}
};

class Parser {
public:
	std::wstring file;
	std::wstring file_content;
	
	void fileLoad(std::wstring file_name);
	std::vector<Instruction> parse(const std::wstring& string);
	std::wstring showInstruction(const Instruction& inst);
private: 
	Var parseVar(const std::wstring& val, const int& instruction);
	std::vector<Lexeme> parseLex(const std::wstring& val);
	Instruction toInstruction(const Lexeme& lex);
	std::wstring showVar(const Var& var);
	std::wstring showLexeme(const Lexeme& lex);
	std::wstring getInstBlockAsString(const Lexeme& block);
};
