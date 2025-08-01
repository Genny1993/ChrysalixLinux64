#include <sstream>
#include <fstream>
#include <codecvt>
#include <fcntl.h>

#include "Helpers.h"
#include "LangLib.h"

std::wstring loadFile(std::wstring filename) {
    std::wstring file_content = L"";
    std::string temp( filename.begin(), filename.end() );
    std::wifstream infile(temp);

    if (infile) {
        infile.imbue(std::locale(std::locale(""), new std::codecvt_utf8<wchar_t>));
        std::wstringstream wss;
        wss << infile.rdbuf();
        file_content = wss.str();
    }
    else {
        throw std::wstring{ filename + LangLib::getTrans(L": Файл не найден\n") };
    }
    infile.close();

    return file_content;
}