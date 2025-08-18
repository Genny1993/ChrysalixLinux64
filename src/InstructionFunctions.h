#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>

#include "Helpers.h"
#include <unistd.h>

typedef void (*func)(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Прототипы функций - инструкций
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void nop(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void end(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void sleepf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void var(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void print(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void free(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void label(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void jump(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void input(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void change(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void to(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void calc(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void newtemp(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void forget(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void tcount(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void isset(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void typeofv(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void comp(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void logic(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void jif(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void jifnot(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void dlabel(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void swap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void arr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void vtoarr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void pushb(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void popb(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void pushf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void popf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void erase(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void insrt(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void clear(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void sizearr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void slice(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void merge(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void sort(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void unique(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void reverse(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void equal(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void in(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void inall(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void rin(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void rinall(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void arrtomap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void inters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void notinters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void arrtostr(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void sum(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void avg(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void min(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void max(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void range(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void median(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void mode(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void stddev(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void push(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void vtomap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void getvals(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void getkeys(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void getinterf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void kvinters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void kvnotinters(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void clearc(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void tointerf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void uninterf(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void interftomap(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void rand(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void t(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void hrt(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void between(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void jifelse(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void jswitch(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void fmt(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void trigon(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void degtorad(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
void radtodeg(Machine* m, Instruction* i, bool prevalidate, bool prego, bool iterate);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Массив с функциями - инструкциями
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct InstructionMap {
	func functions[100] = {
		&nop,
		&end,
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
		&slice,
		&merge,
		&sort,
		&unique,
		&reverse,
		&equal,
		&in,
		&inall,
		&rin,
		&rinall,
		&arrtomap,
		&inters,
		&notinters,
		&arrtostr,
		&sum,
		&avg,
		&min,
		&max,
		&range,
		&median,
		&mode,
		&stddev,
		&push,
		&vtomap,
		&getvals,
		&getkeys,
		&getinterf,
		&kvinters,
		&kvnotinters,
		&clearc,
		&tointerf,
		&uninterf,
		&interftomap,
		&rand,
		&t,
		&hrt,
		&between,
		&jifelse,
		&jswitch,
		&fmt,
		&trigon,
		&degtorad,
		&radtodeg,
	};
};