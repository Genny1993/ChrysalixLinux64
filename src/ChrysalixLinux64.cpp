#include <iostream>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <fcntl.h>
#include <chrono>
#include <cstring>
#include <sys/resource.h>
#include <sched.h>
#include <unistd.h>

#include "Machine.h"
#include "Parser.h"
#include "Helpers.h"
#include "LangLib.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "en_US.UTF-8");
    //Установка локализации интерпретатора
    LangLib::setLang(LANGUAGES::EN);

    struct sched_param sch_params;

    // максимальный приоритет
    sch_params.sched_priority = sched_get_priority_max(SCHED_FIFO);

    if (sched_setscheduler(0, SCHED_FIFO, &sch_params) == -1) {
        if (setpriority(PRIO_PROCESS, 0, 0) == -1) {
            std::wcout << LangLib::getTrans(L"Приоритет не смог быть установленным\n");
            return 1;
        }
    }

    std::wstring filename = L"";
    if (argc < 2) {
        //Если не передан параметр при запуске, смотрим файл настроек
        try {
            filename = loadFile(L"autoexec.ini");
        }
        catch (const std::wstring& error_message) {
            std::wstring temp = error_message;
            std::wcout << L"😽1.1.0 alpha😽";
            return 0;
        }
    }

    //берем параметр при вызове, это имя файла скрипта для запуска
    if (filename == std::wstring_view(L"")) {
        filename = std::wstring(argv[1], argv[1] + strlen(argv[1]));
    }

    try {

        std::unordered_map<std::wstring, Var> map;
        map.reserve(100);
        
        Machine mchn(map, false);

        //Загружаем и парсим исходный код
        auto begin = std::chrono::high_resolution_clock::now();
        Parser p = Parser();
        p.fileLoad(filename);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::wcout << L"📂📄" << LangLib::getTrans(L"Время загрузки файла с исходным кодом: ") << std::to_wstring((double)elapsed_ms.count() / 1000000.0) << LangLib::getTrans(L" сек") << L"\n";

        begin = std::chrono::high_resolution_clock::now();
        std::vector<Instruction> instructions = p.parse(p.file_content);
        int size = (int)instructions.size();
        for(int i = 0; i < size; ++i) {
            mchn.instructions.emplace_back(instructions[i]);
        }
        end = std::chrono::high_resolution_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::wcout <<  L"⚙️ 🎀" + LangLib::getTrans(L"Время обработки исходного кода: ") << std::to_wstring((double)elapsed_ms.count() / 1000000.0) << LangLib::getTrans(L" сек") <<L"\n";

        //Выполняем код
        begin = std::chrono::high_resolution_clock::now();
        mchn.prepare();
        mchn.go();
        end = std::chrono::high_resolution_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::wcout << L"💫🧠" << LangLib::getTrans(L"Время выполнения кода: ") << std::to_wstring((double)elapsed_ms.count() / 1000000.0) << LangLib::getTrans(L" сек") << L"\n";
        
        //Пик по используемой памяти
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        std::wcout << L"🧺🌸" << LangLib::getTrans(L"Пиковое использование памяти: ") << usage.ru_maxrss << L" KB\n";
    }
    catch (const std::wstring& error_message) {
        std::wcout << std::endl << error_message;
    }
    
    return 0;
}

