#pragma once
#include "InvInterface.h"
#include <iomanip>
#include <conio.h>
void InvInterface::start() {
	int button;
	while (true) {
		std::cout << " -------------------------------------- \n";
		std::cout << "|                 МЕНЮ                 |\n";
		std::cout << "| 1. Создать инвестиционный портфель   |\n";
		std::cout << "| 2. Добавить актив                    |\n";
		std::cout << "| 3. Удалить актив                     |\n";
		std::cout << "| 4. Редактировать актив               |\n";
		std::cout << "| 5. Найти актив                       |\n";
		std::cout << "| 6. Отсортировать активы по названию  |\n";
		std::cout << "| 7. Вывести инвестиционный портфель   |\n";
		std::cout << "| 8. Сохранить инвестиционный портфель |\n";
		std::cout << "| 9. Загрузить инвестиционный портфель |\n";
		std::cout << "| 10. Очистить инвестиционный портфель |\n";
		std::cout << "| 0. Выход                             |\n";
		std::cout << " -------------------------------------- \n";
		button = correct_input("Введите номер пункта: ", true);
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
	n = correct_input("\nВведите количество активов для добавления в список: ", true);
	for (i = 0; i < n; ++i) {
		add();
	}
	std::cout << "Добавление окончено.\n";
}
double InvInterface::correct_input(std::string msg) {
	double value;
	std::cout << msg;
	std::cin >> value;
	while ((!(std::cin.good())) || (std::cin.peek() != '\n') || (std::cin.peek() == EOF) || std::cin.fail() || (value < 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
		std::cout << "Введено некорректное значение. Повторите ввод: ";
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
		std::cout << "Введено некорректное значение. Повторите ввод: ";
		std::cin >> value;
	}
	return value;
}
void InvInterface::add() {
	AssetData newasset;
	std::string assetname;
	double openprice, closeprice, commission, count, currency = 0.129998;
	do {
		if (currency != 0.129998) std::cout << "Неверный формат данных! Повторите ввод.\n";
		std::cout << "\nВведите название актива: ";
		std::cin >> assetname;
		openprice = correct_input("\nВведите цену открытия позиции: ");
		closeprice = correct_input("\nВведите цену закрытия позиции: ");
		commission = correct_input("\nВведите комиссию брокера: ");
		count = correct_input("\nВведите количество купленных лотов: ");
		do
		currency = correct_input("\nВалюты:\n0. USD\n1. EUR\n2. RUB\nВведите валюту: \n ", true);
		while (currency < 0 || currency > AssetData::maxCurrency);
	} while (!newasset.set_all(assetname, openprice, closeprice, commission, count, currency));
	Inv.push(newasset);
	std::cout << "Актив добавлен.\n";
}
void InvInterface::del() {
	if (Inv.isempty()) {
		std::cout << "Портфель пуст.\n";
		return;
	}
	int currency = -1, numInp = 1;
	bool flag = false;
	unsigned char num = 0;
	std::string assetname = "-1";
	double openprice = -1, closeprice = -1, commission = -1, count = -1;
	std::cout << "Параметры\n";
	std::cout << "0. Название актива\n";
	std::cout << "1. Цена открытия позиции\n";
	std::cout << "2. Цена закрытия позиции\n";
	std::cout << "3. Комиссия брокера\n";
	std::cout << "4. Количество купленных лотов\n";
	std::cout << "5. Валюта\n";
	std::cout << "По каким параметрам удалить элемент?\n";
	while (num != (1 | 2 | 4 | 8 | 16 | 32)) {
		if (!numInp) break;
		do
			numInp = correct_input("Введите номер параметра: ", true);
		while (numInp > 5 || numInp < 0);
		num |= (1 << numInp);
		numInp = correct_input("Ввести еще один параметр? (1/0): ", true);
	}
	std::cout << "\nВведите значения параметров.\n";
	if (num & 1) std::cout << "Введите название актива: ", std::cin >> assetname;
	if (num & 2) openprice = correct_input("Введите цену открытия позиции: ");
	if (num & 4) closeprice = correct_input("Введите цену закрытия позиции: ");
	if (num & 8) commission = correct_input("Введите комисcию брокера: ");
	if (num & 16) count = correct_input("Введите количество купленных лотов: ");
	if (num & 32) currency = correct_input("Введите валюту: ");
	Inv.del(assetname, openprice, closeprice, commission, count, currency);
	std::cout << "Удаление окончено.\n";
}
void InvInterface::edit() {
	if (Inv.isempty()) {
		std::cout << "Портфель пуст.\n";
		return;
	}
	int numInp = 1, currency, newcurrency = -1;
	std::string assetname, newassetname = "-1";
	unsigned char num = 0;
	double openprice, closeprice, commission, count,
		newopenprice = -1, newcloseprice = -1, newcommission = -1, newcount = -1;
	std::cout << "\nВведите название актива: ";
	do
		std::cin >> assetname;
	while (assetname.length() > AssetData::maxAssetnameLength);
	openprice = correct_input("\nВведите цену открытия позиции: ");
	closeprice = correct_input("\nВведите цену закрытия позиции: ");
	commission = correct_input("\nВведите комиссию брокера: ");
	count = correct_input("\nВведите количество купленных лотов: ");
	do
		currency = correct_input("\nВалюты:\n0. USD\n1. EUR\n2. RUB\nВведите валюту: \n ", true);
	while (currency > AssetData::maxCurrency);
	Investments searchedlist;
	Inv.search(searchedlist, assetname, openprice, closeprice, commission, count, currency);
	if (!searchedlist.size()) {
		std::cout << "Элемент не найден\n";
		return;

	}
	std::cout << "Параметры\n";
	std::cout << "0. Название актива\n";
	std::cout << "1. Цена открытия позиции\n";
	std::cout << "2. Цена закрытия позиции\n";
	std::cout << "3. Комиссия брокера\n";
	std::cout << "4. Количество купленных лотов\n";
	std::cout << "5. Валюта\n";
	std::cout << "Какие параметры нужно изменить?\n";
	while (num != (1 | 2 | 4 | 8 | 16 | 32)) {
		if (!numInp) break;
		do
			numInp = correct_input("Введите номер параметра: ", true);
		while (numInp > 5 || numInp < 0);
		num |= (1 << numInp);
		numInp = correct_input("Ввести еще один параметр? (1/0): ", true);
	}
	if (num != 0) std::cout << "\nВведите значения параметров.\n";
	if (num & 1) std::cout << "Введите название актива: ", std::cin >> newassetname;
	if (num & 2) newopenprice = correct_input("Введите цену открытия позиции: ");
	if (num & 4) newcloseprice = correct_input("Введите цену закрытия позиции: ");
	if (num & 8) newcommission = correct_input("Введите комиcсию брокера: ");
	if (num & 16) newcount = correct_input("Введите количество купленных лотов: ");
	if (num & 32) {
		do newcurrency = correct_input("Введите валюту: ", true);
		while (newcurrency > AssetData::maxCurrency);
	}
	if (Inv.edit(assetname, openprice, closeprice, commission, count, currency,
		newassetname, newopenprice, newcloseprice, newcommission, newcount, newcurrency))
		std::cout << "Редактирование окончено. Актив изменен.\n";
	else std::cout << "Редактирование окончено. Актив не изменен.\nПроверьте корректность введенных данных.\n";
}
void InvInterface::sort() {
	if (Inv.isempty()) {
		std::cout << "Портфель пуст.\n";
		return;
	}
	Inv.sort();
	std::cout << "Сортировка окончена.\n";
}
void InvInterface::search() {
	if (Inv.isempty()) {
		std::cout << "Портфель пуст.\n";
		return;
	}
	int numInp = 1, currency = -1;
	std::string assetname = "-1";
	unsigned char num = 0;
	double openprice = -1, closeprice = -1, commision = -1, count = -1;
	std::cout << "Параметры\n";
	std::cout << "0. Название актива\n";
	std::cout << "1. Цена открытия позиции\n";
	std::cout << "2. Цена закрытия позиции\n";
	std::cout << "3. Комиссия брокера\n";
	std::cout << "4. Количество купленных лотов\n";
	std::cout << "5. Валюта\n";
	std::cout << "По каким параметрам искать элемент?\n";
	while (num != (1 | 2 | 4 | 8 | 16 | 32)) {
		if (!numInp) break;
		do
			numInp = correct_input("Введите номер параметра: ", true);
		while (numInp > 5 || numInp < 0);
		num |= (1 << numInp);
		numInp = correct_input("Ввести еще один параметр? (1/0): ", true);
	}
	std::cout << "\nВведите значения параметров.\n";
	if (num & 1) std::cout << "Введите название актива: ", std::cin >> assetname;
	if (num & 2) openprice = correct_input("Введите цену открытия позиции: ");
	if (num & 4) closeprice = correct_input("Введите цену закрытия позиции: ");
	if (num & 8) commision = correct_input("Введите комиcсию брокера: ");
	if (num & 16) count = correct_input("Введите количество купленных лотов: ");
	if (num & 32) currency = correct_input("Введите валюту: ");
	Investments searchedlist;
	Inv.search(searchedlist,assetname, openprice, closeprice, commision, count, currency);
	if (!searchedlist.isempty()) {
		std::cout << "Найденные активы:\n\n";
		searchedlist.print();
		searchedlist.~Investments();
	}
	else std::cout << "Активы не найдены\n\n";
	std::cout << "Поиск окончен.\n";
}
void InvInterface::print() {
	if (!Inv.isempty()) {
		std::cout << "Ваши активы:\n\n";
		Inv.print();
	}
	else std::cout << "Портфель пуст.\n";
}
void InvInterface::save() {
	if (Inv.isempty()) {
		std::cout << "Портфель пуст.\n";
		return;
	}
	if (Inv.save("2.txt")) std::cout << "Файл успешно сохранен!\n";
	else std::cout << "Файл не сохранен!\n";
	}
void InvInterface::load() {
	if (Inv.load("1.txt")) std::cout << "Файл успешно загружен!\n";
	else std::cout << "Файл не загружен!\n";
}
void InvInterface::clear() {
	if (Inv.isempty()) {
		std::cout << "Портфель пуст.\n";
		return;
	};
	Inv.Investments::clear();
	std::cout << "Инвестиционный портфель очищен.\n";
}
InvInterface::InvInterface() {
	
}
InvInterface::~InvInterface() {
	Inv.~Investments();
}