#include <iostream>

#include "Helpers.h"
#include "LangLib.h"
#include "InstructionFunctions.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// getValue 
// Возвращает значение параметра по имени переменной или литералу
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Var getValue( Var* val, std::unordered_map<std::wstring, Var>* heap, Machine* m) {
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
						Var index = getValue(&(val->arr[i]), heap, m);
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
								if(val->arr[i].type == Type::INST) {
									index = heap->at(getValue(&(val->arr[i]), heap, m).toSTR().str).toNTG().data.ntg;
								} else {
									index = heap->at(val->arr[i].toSTR().str).toNTG().data.ntg;
								}
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
								if(val->arr[i].type == Type::INST) {
									index = heap->at(getValue(&(val->arr[i]), heap, m).toSTR().str).toSTR().str;
								} else {
									index = heap->at(val->arr[i].toSTR().str).toSTR().str;
								}
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
							if(val->arr[i].type == Type::INST) {
								value = &(value->arr.at(getValue(&(val->arr[i]), heap, m).toNTG().data.ntg));
							} else {
								value = &(value->arr.at(val->arr[i].toNTG().data.ntg));
							}
						}
						catch (std::out_of_range& ex) {
							std::string temp = ex.what();
							throw std::wstring{ val->arr[i].toSTR().str + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
						}
					} else if(value->type == MAP) {
						try{
							if(val->arr[i].type == Type::INST) {
								value = &(value->mp.at(getValue(&(val->arr[i]), heap, m).toSTR().str));
							} else {
								value = &(value->mp.at(val->arr[i].toSTR().str));
							}
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
				const Var &temp = (*heap).at(val->getWStr());
				if(temp.deactivate == true && temp.type == INST) {
					return temp;
				} else {
					return getValue(&(*heap).at(val->getWStr()), heap, m);
				}
			}
			catch (std::out_of_range& ex) {
				std::string temp = ex.what();
				throw std::wstring{ val->getWStr() + LangLib::getTrans(L": Переменная не определена\n") };
			}
		}
	}
	else if((*val).type == Type::INST) {
		if((*val).deactivate == true) {
			return *val;
		} else {
			InstructionMap inst;
			int size = (int)(*val).instructions.size();
			Var result;
			for(int i = 0; i < size; ++i) {		
				inst.functions[(*val).instructions[i].opCode](m, &(*val).instructions[i], false, false, false);
				result = (*heap)[L"$"];
			}
			return result;
		}
	}
	
	return *val;
}

Var& setValue(Var* val, std::unordered_map<std::wstring, Var>* heap, Machine* m) {
	if(val->is_const || val->is_superconst) {
		throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
	}
	if(val->type == STR && (*val).getWStr()[0] == L'$') {
		if((int)val->arr.size() > 0) {
			int size = (int)val->arr.size();
			Var *value;
			try{
				value = &(heap->at(val->str));
				if(value->is_const || value->is_superconst) {
					throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
				}
			}
			catch (std::out_of_range& ex) {
				std::string temp = ex.what();
				throw std::wstring{ val->str + LangLib::getTrans(L": Переменная не определена\n") };
			}
			for(int i = 0; i < size; ++i) {
				if(val->type == STR && (val->arr[i]).toSTR().getWStr()[0] == L'$') {
					if((int)val->arr.size() > 0) {
						Var index = getValue(&(val->arr[i]), heap, m);
						if(value->type == ARR) {
							try {
								value = &(value->arr.at(index.toNTG().data.ntg));
								if(value->is_const || value->is_superconst) {
									throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
								}
							} catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ index.toSTR().str + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
							}
						} else if(value->type == MAP) {
							try {
								value = &(value->mp.at(index.toSTR().str));
								if(value->is_const || value->is_superconst) {
									throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
								}
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
								if(val->arr[i].type == Type::INST) {
									index = heap->at(getValue(&(val->arr[i]), heap, m).toSTR().str).toNTG().data.ntg;
								} else {
									index = heap->at(val->arr[i].toSTR().str).toNTG().data.ntg;
								}
							}
							catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ val->arr[i].toSTR().str + LangLib::getTrans(L": Переменная не определена\n") };
							}
							try {
								value = &(value->arr.at(index));
								if(value->is_const || value->is_superconst) {
									throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
								}
							} 
							catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ std::to_wstring(index) + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс находится вне диапазона\n") };
							}
						} else if(value->type == MAP) {
							std::wstring index;
							try {
								if(val->arr[i].type == Type::INST) {
									index = heap->at(getValue(&(val->arr[i]), heap, m).toSTR().str).toSTR().data.ntg;
								} else {
									index = heap->at(val->arr[i].toSTR().str).toSTR().str;
								}
							}
							catch (std::out_of_range& ex) {
								std::string temp = ex.what();
								throw std::wstring{ val->arr[i].toSTR().str + LangLib::getTrans(L": Переменная не определена\n") };
							}
							try {
								value = &(value->mp.at(index));
								if(value->is_const || value->is_superconst) {
									throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
								}
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
							if(val->arr[i].type == Type::INST) {
								value = &(value->arr.at(getValue(&(val->arr[i]), heap, m).toNTG().data.ntg));
								if(value->is_const || value->is_superconst) {
									throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
								}
							} else {
								value = &(value->arr.at(val->arr[i].toNTG().data.ntg));
								if(value->is_const || value->is_superconst) {
									throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
								}
							}
						}
						catch (std::out_of_range& ex) {
							std::string temp = ex.what();
							throw std::wstring{ val->arr[i].toSTR().str + LangLib::getTrans(L": ") + LangLib::getTrans(L"Индекс находится вне диапазона\n") };

						}
					} else if(value->type == MAP) {
						try{
							if(val->arr[i].type == Type::INST) {
								value = &(value->mp.at(getValue(&(val->arr[i]), heap, m).toSTR().str));
								if(value->is_const || value->is_superconst) {
									throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
								}
							} else {
								value = &(value->mp.at(val->arr[i].toSTR().str));
								if(value->is_const || value->is_superconst) {
									throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
								}
							}
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
		}
		else {
			try {
				Var &ret = (*heap).at(val->str);
				if(ret.is_const || ret.is_superconst) {
					throw std::wstring{ val->toSTR().str + LangLib::getTrans(L": Константу нельзя изменить\n") };
				}
				return ret;
			}
			catch (std::out_of_range& ex) {
				std::string temp = ex.what();
				throw std::wstring{ val->getWStr() + LangLib::getTrans(L": Переменная не определена\n") };
			}
		}
	} else {
		throw std::wstring{ val->toSTR().getWStr() + LangLib::getTrans(L": Литерал не может быть использован как lavalue\n") };
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