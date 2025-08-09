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
	std::vector<Instruction> parse(std::wstring string);
private: 
	Var parseVar(std::wstring val, int instruction);
	std::vector<Lexeme> parseLex(std::wstring val);
	Instruction toInstruction(Lexeme lex, int i);
};

std::wstring showVar(Var var);
std::wstring showLexeme(Lexeme lex);
std::wstring showInstruction(Instruction inst);
