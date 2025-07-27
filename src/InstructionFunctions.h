#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>

#include "Helpers.h"
#include <unistd.h>

typedef void (*func)(Machine* m, Instruction* i, bool prevalidate, bool prego);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Прототипы функций - инструкций
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void nop(Machine* m, Instruction* i, bool prevalidate, bool prego);
void end(Machine* m, Instruction* i, bool prevalidate, bool prego);
void pause(Machine* m, Instruction* i, bool prevalidate, bool prego);
void sleepf(Machine* m, Instruction* i, bool prevalidate, bool prego);
void var(Machine* m, Instruction* i, bool prevalidate, bool prego);
void print(Machine* m, Instruction* i, bool prevalidate, bool prego);
void free(Machine* m, Instruction* i, bool prevalidate, bool prego);
void label(Machine* m, Instruction* i, bool prevalidate, bool prego);
void jump(Machine* m, Instruction* i, bool prevalidate, bool prego);
void input(Machine* m, Instruction* i, bool prevalidate, bool prego);
void change(Machine* m, Instruction* i, bool prevalidate, bool prego);
void to(Machine* m, Instruction* i, bool prevalidate, bool prego);
void calc(Machine* m, Instruction* i, bool prevalidate, bool prego);
void newtemp(Machine* m, Instruction* i, bool prevalidate, bool prego);
void forget(Machine* m, Instruction* i, bool prevalidate, bool prego);
void tcount(Machine* m, Instruction* i, bool prevalidate, bool prego);
void isset(Machine* m, Instruction* i, bool prevalidate, bool prego);
void typeofv(Machine* m, Instruction* i, bool prevalidate, bool prego);
void comp(Machine* m, Instruction* i, bool prevalidate, bool prego);
void logic(Machine* m, Instruction* i, bool prevalidate, bool prego);
void jif(Machine* m, Instruction* i, bool prevalidate, bool prego);
void jifnot(Machine* m, Instruction* i, bool prevalidate, bool prego);
void dlabel(Machine* m, Instruction* i, bool prevalidate, bool prego);
void swap(Machine* m, Instruction* i, bool prevalidate, bool prego);
void arr(Machine* m, Instruction* i, bool prevalidate, bool prego);
void vtoarr(Machine* m, Instruction* i, bool prevalidate, bool prego);
void pushb(Machine* m, Instruction* i, bool prevalidate, bool prego);
void popb(Machine* m, Instruction* i, bool prevalidate, bool prego);
void pushf(Machine* m, Instruction* i, bool prevalidate, bool prego);
void popf(Machine* m, Instruction* i, bool prevalidate, bool prego);
void erase(Machine* m, Instruction* i, bool prevalidate, bool prego);
void insrt(Machine* m, Instruction* i, bool prevalidate, bool prego);
void clear(Machine* m, Instruction* i, bool prevalidate, bool prego);
void sizearr(Machine* m, Instruction* i, bool prevalidate, bool prego);
void getval(Machine* m, Instruction* i, bool prevalidate, bool prego);
void setval(Machine* m, Instruction* i, bool prevalidate, bool prego);
void slice(Machine* m, Instruction* i, bool prevalidate, bool prego);
void merge(Machine* m, Instruction* i, bool prevalidate, bool prego);
void sort(Machine* m, Instruction* i, bool prevalidate, bool prego);
void unique(Machine* m, Instruction* i, bool prevalidate, bool prego);
void reverse(Machine* m, Instruction* i, bool prevalidate, bool prego);
void equal(Machine* m, Instruction* i, bool prevalidate, bool prego);
void iexist(Machine* m, Instruction* i, bool prevalidate, bool prego);
void in(Machine* m, Instruction* i, bool prevalidate, bool prego);
void inall(Machine* m, Instruction* i, bool prevalidate, bool prego);
void rin(Machine* m, Instruction* i, bool prevalidate, bool prego);
void rinall(Machine* m, Instruction* i, bool prevalidate, bool prego);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Массив с функциями - инструкциями
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct InstructionMap {
	func functions[100] = {
		&nop,
		&end,
		&pause,
		&sleepf,
		&var,
		&print,
		&free,
		&label,
		&jump,
		&input,
		&change,
		&to,
		&calc,
		&newtemp,
		&forget,
		&tcount,
		&isset,
		&typeofv,
		&comp,
		&logic,
		&jif,
		&jifnot,
		&dlabel,
		&swap,
		&arr,
		&vtoarr,
		&pushb,
		&popb,
		&pushf,
		&popf,
		&erase,
		&insrt,
		&clear,
		&sizearr,
		&getval,
		&setval,
		&slice,
		&merge,
		&sort,
		&unique,
		&reverse,
		&equal,
		&iexist,
		&in,
		&inall,
		&rin,
		&rinall
	};
};