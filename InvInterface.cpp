#pragma once
#include "InvInterface.h"
#include <iomanip>
#include <conio.h>
void InvInterface::start() {
	int button;
	while (true) {
		std::cout << " -------------------------------------- \n";
		std::cout << "|                 ����                 |\n";
		std::cout << "| 1. ������� �������������� ��������   |\n";
		std::cout << "| 2. �������� �����                    |\n";
		std::cout << "| 3. ������� �����                     |\n";
		std::cout << "| 4. ������������� �����               |\n";
		std::cout << "| 5. ����� �����                       |\n";
		std::cout << "| 6. ������������� ������ �� ��������  |\n";
		std::cout << "| 7. ������� �������������� ��������   |\n";
		std::cout << "| 8. ��������� �������������� �������� |\n";
		std::cout << "| 9. ��������� �������������� �������� |\n";
		std::cout << "| 10. �������� �������������� �������� |\n";
		std::cout << "| 0. �����                             |\n";
		std::cout << " -------------------------------------- \n";
		button = correct_input("������� ����� ������: ", true);
		switch (button) {
		case 1:
			create();
			break;
		case 2:
			add();
			break;
		case 3:
			del();
			break;
		case 4:
			edit();
			break;
		case 5:
			search();
			break;
		case 6:
			sort();
			break;
		case 7:
			print();
			break;
		case 8:
			save();
			break;
		case 9:
			load();
			break;
		case 10:
			clear();
			break;
		case 0:
			return;
		default:
			break;
		}
	}
}
void InvInterface::create() {
	int i, n;
	AssetData elem;
	n = correct_input("\n������� ���������� ������� ��� ���������� � ������: ", true);
	for (i = 0; i < n; ++i) {
		add();
	}
	std::cout << "���������� ��������.\n";
}
double InvInterface::correct_input(std::string msg) {
	double value;
	std::cout << msg;
	std::cin >> value;
	while ((!(std::cin.good())) || (std::cin.peek() != '\n') || (std::cin.peek() == EOF) || std::cin.fail() || (value < 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
		std::cout << "������� ������������ ��������. ��������� ����: ";
		std::cin >> value;
	}
	return value;
}
int InvInterface::correct_input(std::string msg, bool par) {
	double value;
	std::cout << msg;
	std::cin >> value;
	while ((!(std::cin.good())) || (std::cin.peek() != '\n') || (std::cin.peek() == EOF) 
		|| std::cin.fail() || (round(value) != value) || (value < 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
		std::cout << "������� ������������ ��������. ��������� ����: ";
		std::cin >> value;
	}
	return value;
}
void InvInterface::add() {
	AssetData newasset;
	std::string assetname;
	double openprice, closeprice, commission, count, currency = 0.129998;
	do {
		if (currency != 0.129998) std::cout << "�������� ������ ������! ��������� ����.\n";
		std::cout << "\n������� �������� ������: ";
		std::cin >> assetname;
		openprice = correct_input("\n������� ���� �������� �������: ");
		closeprice = correct_input("\n������� ���� �������� �������: ");
		commission = correct_input("\n������� �������� �������: ");
		count = correct_input("\n������� ���������� ��������� �����: ");
		do
		currency = correct_input("\n������:\n0. USD\n1. EUR\n2. RUB\n������� ������: \n ", true);
		while (currency < 0 || currency > AssetData::maxCurrency);
	} while (!newasset.set_all(assetname, openprice, closeprice, commission, count, currency));
	Inv.push(newasset);
	std::cout << "����� ��������.\n";
}
void InvInterface::del() {
	if (Inv.isempty()) {
		std::cout << "�������� ����.\n";
		return;
	}
	int currency = -1, numInp = 1;
	bool flag = false;
	unsigned char num = 0;
	std::string assetname = "-1";
	double openprice = -1, closeprice = -1, commission = -1, count = -1;
	std::cout << "���������\n";
	std::cout << "0. �������� ������\n";
	std::cout << "1. ���� �������� �������\n";
	std::cout << "2. ���� �������� �������\n";
	std::cout << "3. �������� �������\n";
	std::cout << "4. ���������� ��������� �����\n";
	std::cout << "5. ������\n";
	std::cout << "�� ����� ���������� ������� �������?\n";
	while (num != (1 | 2 | 4 | 8 | 16 | 32)) {
		if (!numInp) break;
		do
			numInp = correct_input("������� ����� ���������: ", true);
		while (numInp > 5 || numInp < 0);
		num |= (1 << numInp);
		numInp = correct_input("������ ��� ���� ��������? (1/0): ", true);
	}
	std::cout << "\n������� �������� ����������.\n";
	if (num & 1) std::cout << "������� �������� ������: ", std::cin >> assetname;
	if (num & 2) openprice = correct_input("������� ���� �������� �������: ");
	if (num & 4) closeprice = correct_input("������� ���� �������� �������: ");
	if (num & 8) commission = correct_input("������� �����c�� �������: ");
	if (num & 16) count = correct_input("������� ���������� ��������� �����: ");
	if (num & 32) currency = correct_input("������� ������: ");
	Inv.del(assetname, openprice, closeprice, commission, count, currency);
	std::cout << "�������� ��������.\n";
}
void InvInterface::edit() {
	if (Inv.isempty()) {
		std::cout << "�������� ����.\n";
		return;
	}
	int numInp = 1, currency, newcurrency = -1;
	std::string assetname, newassetname = "-1";
	unsigned char num = 0;
	double openprice, closeprice, commission, count,
		newopenprice = -1, newcloseprice = -1, newcommission = -1, newcount = -1;
	std::cout << "\n������� �������� ������: ";
	do
		std::cin >> assetname;
	while (assetname.length() > AssetData::maxAssetnameLength);
	openprice = correct_input("\n������� ���� �������� �������: ");
	closeprice = correct_input("\n������� ���� �������� �������: ");
	commission = correct_input("\n������� �������� �������: ");
	count = correct_input("\n������� ���������� ��������� �����: ");
	do
		currency = correct_input("\n������:\n0. USD\n1. EUR\n2. RUB\n������� ������: \n ", true);
	while (currency > AssetData::maxCurrency);
	Investments searchedlist;
	Inv.search(searchedlist, assetname, openprice, closeprice, commission, count, currency);
	if (!searchedlist.size()) {
		std::cout << "������� �� ������\n";
		return;

	}
	std::cout << "���������\n";
	std::cout << "0. �������� ������\n";
	std::cout << "1. ���� �������� �������\n";
	std::cout << "2. ���� �������� �������\n";
	std::cout << "3. �������� �������\n";
	std::cout << "4. ���������� ��������� �����\n";
	std::cout << "5. ������\n";
	std::cout << "����� ��������� ����� ��������?\n";
	while (num != (1 | 2 | 4 | 8 | 16 | 32)) {
		if (!numInp) break;
		do
			numInp = correct_input("������� ����� ���������: ", true);
		while (numInp > 5 || numInp < 0);
		num |= (1 << numInp);
		numInp = correct_input("������ ��� ���� ��������? (1/0): ", true);
	}
	if (num != 0) std::cout << "\n������� �������� ����������.\n";
	if (num & 1) std::cout << "������� �������� ������: ", std::cin >> newassetname;
	if (num & 2) newopenprice = correct_input("������� ���� �������� �������: ");
	if (num & 4) newcloseprice = correct_input("������� ���� �������� �������: ");
	if (num & 8) newcommission = correct_input("������� ����c��� �������: ");
	if (num & 16) newcount = correct_input("������� ���������� ��������� �����: ");
	if (num & 32) {
		do newcurrency = correct_input("������� ������: ", true);
		while (newcurrency > AssetData::maxCurrency);
	}
	if (Inv.edit(assetname, openprice, closeprice, commission, count, currency,
		newassetname, newopenprice, newcloseprice, newcommission, newcount, newcurrency))
		std::cout << "�������������� ��������. ����� �������.\n";
	else std::cout << "�������������� ��������. ����� �� �������.\n��������� ������������ ��������� ������.\n";
}
void InvInterface::sort() {
	if (Inv.isempty()) {
		std::cout << "�������� ����.\n";
		return;
	}
	Inv.sort();
	std::cout << "���������� ��������.\n";
}
void InvInterface::search() {
	if (Inv.isempty()) {
		std::cout << "�������� ����.\n";
		return;
	}
	int numInp = 1, currency = -1;
	std::string assetname = "-1";
	unsigned char num = 0;
	double openprice = -1, closeprice = -1, commision = -1, count = -1;
	std::cout << "���������\n";
	std::cout << "0. �������� ������\n";
	std::cout << "1. ���� �������� �������\n";
	std::cout << "2. ���� �������� �������\n";
	std::cout << "3. �������� �������\n";
	std::cout << "4. ���������� ��������� �����\n";
	std::cout << "5. ������\n";
	std::cout << "�� ����� ���������� ������ �������?\n";
	while (num != (1 | 2 | 4 | 8 | 16 | 32)) {
		if (!numInp) break;
		do
			numInp = correct_input("������� ����� ���������: ", true);
		while (numInp > 5 || numInp < 0);
		num |= (1 << numInp);
		numInp = correct_input("������ ��� ���� ��������? (1/0): ", true);
	}
	std::cout << "\n������� �������� ����������.\n";
	if (num & 1) std::cout << "������� �������� ������: ", std::cin >> assetname;
	if (num & 2) openprice = correct_input("������� ���� �������� �������: ");
	if (num & 4) closeprice = correct_input("������� ���� �������� �������: ");
	if (num & 8) commision = correct_input("������� ����c��� �������: ");
	if (num & 16) count = correct_input("������� ���������� ��������� �����: ");
	if (num & 32) currency = correct_input("������� ������: ");
	Investments searchedlist;
	Inv.search(searchedlist,assetname, openprice, closeprice, commision, count, currency);
	if (!searchedlist.isempty()) {
		std::cout << "��������� ������:\n\n";
		searchedlist.print();
		searchedlist.~Investments();
	}
	else std::cout << "������ �� �������\n\n";
	std::cout << "����� �������.\n";
}
void InvInterface::print() {
	if (!Inv.isempty()) {
		std::cout << "���� ������:\n\n";
		Inv.print();
	}
	else std::cout << "�������� ����.\n";
}
void InvInterface::save() {
	if (Inv.isempty()) {
		std::cout << "�������� ����.\n";
		return;
	}
	if (Inv.save("2.txt")) std::cout << "���� ������� ��������!\n";
	else std::cout << "���� �� ��������!\n";
	}
void InvInterface::load() {
	if (Inv.load("1.txt")) std::cout << "���� ������� ��������!\n";
	else std::cout << "���� �� ��������!\n";
}
void InvInterface::clear() {
	if (Inv.isempty()) {
		std::cout << "�������� ����.\n";
		return;
	};
	Inv.Investments::clear();
	std::cout << "�������������� �������� ������.\n";
}
InvInterface::InvInterface() {
	
}
InvInterface::~InvInterface() {
	Inv.~Investments();
}