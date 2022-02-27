#pragma once
#ifndef INVESTMENTS_H
#define INVESTMENTS_H
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <iomanip>
#include "AssetData.h"

class Investments {
private:
	struct Node {
		AssetData assetdata;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
	int SIZE;
	Node* split(Node* head);
	Node* merge(Node* first, Node* second);
	Node* merge_sort(Node* first);
	Node* return_middle(Node* head);
protected:
	Node* get_asset_ptr(int pos) const;
	bool get_asset(int pos, AssetData& asset) const;
	void unite_equals();
public:
	void operator=(Investments& obj);
	void clear();
	Investments();
	Investments(const Investments& const Obj);
	~Investments();
	void push(AssetData& const assetdata);
	bool pop(AssetData& assetdata);
	void print();
	bool isempty();
	int size();
	void search(Investments& const searchassetlist, std::string assetname , double openprice ,
		double closeprice, double commision, double  count, int currency);
	void del(std::string searchasset, double openprice,
		double closeprice, double commision, double  count, int currency);
	void del(const AssetData& const obj);
	void del(Node* ptr);
	bool edit(std::string assetname, double openprice,
		double closeprice, double commision, double count, int currency,
		std::string newassetname, double newopenprice,
		double newcloseprice, double newcommision, double  newcount, int newcurrency);
	void sort();
	bool save(std::string ofile_name);
	bool load(std::string ifile_name);
};
#endif