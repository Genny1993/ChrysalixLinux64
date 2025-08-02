#pragma once

#include <string_view>

#include "Var.h"
#include "Machine.h"


class Lexeme {
public:
	std::wstring type;
	std::vector<std::wstring> str_parameters;
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

};
