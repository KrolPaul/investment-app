#pragma once
#ifndef INVINTERFACE_H
#define INVNTERFACE_H
#include "Investments.h"

class InvInterface  {
private:
	void create();
	void add();
	void del();
	void sort();
	void search();
	void print();
	void save();
	void load();
	void clear();
	void edit();
	double correct_input(std::string msg);
	int correct_input(std::string msg, bool par);
	Investments Inv;
public:
	InvInterface();
	void start();
	~InvInterface();
};

#endif