#pragma once

#include<string>
#include<unordered_map>
#include<vector>

enum LANGUAGES {
	RU,
	EN
};
class LangLib {
private:
	static LANGUAGES current_lang;
	static std::vector<std::unordered_map<std::wstring, std::wstring>> library;
public:
	static void setLang(LANGUAGES lang);
	static std::wstring getTrans(std::wstring str);
};


