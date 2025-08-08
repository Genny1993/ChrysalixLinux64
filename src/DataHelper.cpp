#include <iostream>

#include "Helpers.h"
#include "LangLib.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// getValue 
// Возвращает значение параметра по имени переменной или литералу
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Var getValue(Var* val, std::unordered_map<std::wstring, Var>* heap) {
	if ((*val).type == STR && (*val).getWStr()[0] == L'$') {
		if((int)val->arr.size() > 0) {
			int size = (int)val->arr.size();
			Var *value;
			try{
				value = &(heap->at(val->str));
			}
			catch (std::out_of_range& ex) {
				std::string temp = ex.what();
				throw std::wstring{ val->str + LangLib::getTrans(L": Переменная не определена\n") };
			}
			for(int i = 0; i < size; ++i) {
				if(val->type == STR && (val->arr[i]).toSTR().getWStr()[0] == L'$') {
					if((int)val->arr.size() > 0) {
						Var index = getValue(&(val->arr[i]), heap);
						if(value->type == ARR) {
							try {
								value = &(value->arr.at(index.toNTG().data.ntg));
							} catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ index.toSTR().str + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
							}
						} else if(value->type == MAP) {
							try {
								value = &(value->mp.at(index.toSTR().str));
							} catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ index.toSTR().str + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс словаря не существует\n") };
							}
							
						} else {
							throw std::wstring{ index.toSTR().str + LangLib::getTrans(L": Переменная не является массивом или словарем\n") };
						}
					} else {
						if(value->type == ARR) {
							int index = 0;
							try{
								index = heap->at(val->arr[i].toSTR().str).toNTG().data.ntg;
							}
							catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ val->arr[i].toSTR().str + LangLib::getTrans(L": Переменная не определена\n") };
							}
							try {
								value = &(value->arr.at(index));
							} 
							catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ std::to_wstring(index) + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
							}
						} else if(value->type == MAP) {
							std::wstring index;
							try{
								index = heap->at(val->arr[i].toSTR().str).toSTR().str;
							}
							catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ val->arr[i].toSTR().str + LangLib::getTrans(L": Переменная не определена\n") };
							}
							try {
								value = &(value->mp.at(index));
							} 
							catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ index + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс словаря не существует\n") };
							}
						} else {
							throw std::wstring{ value->getWStr() + LangLib::getTrans(L": Переменная не является массивом или словарем\n") };
						}
					}
				} else {
					if(value->type == ARR) {
						try {
							value = &(value->arr.at(val->arr[i].toNTG().data.ntg));
						}
						catch (std::out_of_range& ex) {
							std::string temp = ex.what();
							throw std::wstring{ std::to_wstring(val->arr[i].toNTG().data.ntg) + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
						}
					} else if(value->type == MAP) {
						try{
							value = &(value->mp.at(val->arr[i].toSTR().str));
						}
						catch (std::out_of_range& ex) {
							std::string temp = ex.what();
							throw std::wstring{ val->arr[i].toSTR().str + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс словаря не существует\n") };
						}
					} else {
						throw std::wstring{ value->toSTR().getWStr() + LangLib::getTrans(L": Переменная не является массивом или словарем\n") };
					}
				}
			}
			return *value;
		} else {
			try {
				return (*heap).at(val->getWStr());
			}
			catch (std::out_of_range& ex) {
				std::string temp = ex.what();
				throw std::wstring{ val->getWStr() + LangLib::getTrans(L": Переменная не определена\n") };
			}
		}
	}
	else {
		return *val;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// getLabel
// Возвращает значение параметра по имени переменной или литералу
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Var getLabel(Var* val,std::unordered_map<std::wstring, int>* pointers) {
	if ((*val).type == STR && (*val).getWStr()[0] == L'&') {
		try {
			return (*pointers).at((*val).getWStr());
		}
		catch (std::out_of_range& ex) {
			std::string temp = ex.what();
			throw std::wstring{ (*val).getWStr() + LangLib::getTrans(L": Метка не определена\n") };
		}
	}
	else {
		return *val;
	}
	return 0;
}