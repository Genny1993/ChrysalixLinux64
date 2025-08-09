#pragma once

#include <string_view>

#include "Var.h"
#include "Machine.h"


class Lexeme {
public:
	std::wstring type;
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
	void parse(Machine& m);
private: 
	Var parseVar(std::wstring val, int instruction);
};

std::wstring showVar(Var var);
