#pragma once

#include "Var.h"
#include "Machine.h"

class Lexeme {
public:
	std::wstring type;
	std::vector<std::wstring> str_parameters;
	std::vector<Var> parameters;
};

class Parser {
public:
	std::wstring file;
	std::wstring file_content;
	
	void fileLoad(std::wstring file_name);
	void parse(Machine& m);

};
