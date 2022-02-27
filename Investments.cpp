#pragma once
#include "Investments.h"
Investments::Node* Investments::get_asset_ptr(int pos) const {
		Node* cur = head;
		int i = 0;
		while (cur && i != pos) {
			cur = cur->next;
			i++;
		}
		if (i != pos) return nullptr;
		else return cur;
	}
bool Investments::get_asset(int pos, AssetData& asset) const {
		Node* cur = head;
		int i = 0;
		while (cur && i != pos) {
			cur = cur->next;
			i++;
		}
		if (i != pos) return false;
		asset.set_all(cur->assetdata.get_assetname(), cur->assetdata.get_openprice(),
			cur->assetdata.get_closeprice(), cur->assetdata.get_commission(),
			cur->assetdata.get_count(), cur->assetdata.get_currency());
		return true;
	}
void Investments::clear() {
		Node* temp;
		while (head) {
			temp = head;
			head = head->next;
			delete temp;
		}
		SIZE = 0;
		head = nullptr;
		tail = nullptr;
	}
Investments::Node* Investments::split(Investments::Node* head) {
		Node* fast = head, * slow = head;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		Investments::Node* temp = slow->next;
		slow->next = nullptr;
		return temp;
	}
Investments::Node* Investments::merge(Investments::Node* first, Investments::Node* second) {
		//если один из списков пуст
		if (!first) return second;
		if (!second) return first;
		//выбираем меньший
		if (first->assetdata.get_assetname() < second->assetdata.get_assetname()) {

			first->next = merge(first->next, second);
			first->next->prev = first;
			first->prev = nullptr;
			return first;
		}
		else {
			second->next = merge(first, second->next);
			second->next->prev = second;
			second->prev = nullptr;
			return second;
		}
	}
Investments::Node* Investments::merge_sort(Investments::Node* first) {
		if (!first || !first->next) return first;
		Node* second = split(first);
		//рекурсия для левой и правой половин
		first = merge_sort(first);
		second = merge_sort(second);
		//объединяем 
		return merge(first, second);
	}
Investments::Node* Investments::return_middle(Investments::Node* head) {
		Node* fast = head, * slow = head;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow->next;
	}
Investments::Investments() {head = nullptr; tail = nullptr; }
Investments::Investments(const Investments& const Obj) {
		Node* cur = Obj.head;
		while (cur != nullptr) {
			push(cur->assetdata);
			cur = cur->next;
		}
	}
Investments::~Investments() {
		clear();
	}
void Investments::push(AssetData& const assetdata) {
		Node* newasset = new Node;
		newasset->next = nullptr;
		newasset->prev = nullptr;
		newasset->assetdata = assetdata;
		/*newasset->assetdata.set_all(assetdata.get_assetname(), assetdata.get_openprice(),
			assetdata.get_closeprice(), assetdata.get_commission(), assetdata.get_count(), assetdata.get_currency());*/
		if (!tail && !head) {
			tail = newasset;
			head = newasset;
		}
		else {
			newasset->prev = tail;
			tail->next = newasset;
			tail = newasset;
		}
		++SIZE;
		unite_equals();
	}
bool Investments::pop(AssetData& assetdata) {
		if (head) {
			assetdata = head->assetdata;
			if (head->next) {
				head = head->next;
				delete head->prev;
				head->prev = nullptr;
			}
			else {
				delete head;
				head = nullptr;
				tail = nullptr;
			}
			--SIZE;
			return true;
		}
		return false;
	}
void Investments::print() {
		Node* cur = head;
		std::cout << std::setw(17) << std::setfill(' ') << std::left << " Актив";
		std::cout << std::setw(22) << std::setfill(' ') << std::left <<"Цена открытия" ;
		std::cout << std::setw(22) << std::setfill(' ') << std::left <<"Цена закрытия" ;
		std::cout << std::setw(17) << std::setfill(' ') << std::left <<"Комиссия" ;
		std::cout << std::setw(23) << std::setfill(' ') << std::left <<"Количество лотов" ;
		std::cout << std::setw(10) << std::setfill(' ') << std::left <<"Валюта";
		std::cout << std::setw(111) << std::setfill('-') <<"\n-";
		std::cout << '\n';
		while (cur) {
			std::cout << '|' << std::setw(15) << std::setfill(' ') << std::left << cur->assetdata.get_assetname() << '|';
			std::cout << std::setw(21) << std::setfill(' ') << std::left << std::setprecision(6) << cur->assetdata.get_openprice() << '|';
			std::cout << std::setw(21) << std::setfill(' ') << std::left << std::setprecision(6) << cur->assetdata.get_closeprice() << '|';
			std::cout << std::setw(16) << std::setfill(' ') << std::left << std::setprecision(6) << cur->assetdata.get_commission() << '|';
			std::cout << std::setw(22) << std::setfill(' ') << std::left << cur->assetdata.get_count() << '|';
			switch (cur->assetdata.get_currency()) {
			case 0:
				std::cout << std::setw(9) << std::setfill(' ') << std::left << "USD" << '|';
				std::cout << std::setw(108) << std::setfill(' ') << "\n ";
				std::cout << '\r';
				break;
			case 1:
				std::cout << std::setw(9) << std::setfill(' ') << std::left << "EUR" << '|';
				std::cout << std::setw(108) << std::setfill(' ') << "\n ";
				std::cout << '\r';
				break;
			case 2:
				std::cout << std::setw(9) << std::setfill(' ') << std::left << "RUB" << '|';
				std::cout << std::setw(108) << std::setfill(' ') << "\n ";
				std::cout << '\r';
				break;
			}
			
			cur = cur->next;
		}
		std::cout << std::setw(110) << std::setfill('-') << "-";
		std::cout << '\n';
	}
bool Investments::isempty() {
		if (head) return false;
		else return true;
	}
int Investments::size() {
		return SIZE;
	}
void Investments::search(Investments& const searchassetlist, std::string assetname = "-1", double openprice = -1,
	double closeprice = -1, double commision = -1, double  count = -1, int currency = -1) {
		Node* cur = head;
		while (cur) {
			if (assetname == cur->assetdata.get_assetname() || assetname == "-1") {
				if (openprice == cur->assetdata.get_openprice() || openprice == -1) {
					if (closeprice == cur->assetdata.get_closeprice() || closeprice == -1) {
						if (commision == cur->assetdata.get_commission() || commision == -1) {
							if (count == cur->assetdata.get_count() || count == -1) {
								if (currency == cur->assetdata.get_currency() || currency == -1) {
									searchassetlist.push(cur->assetdata);
								}
							}
						}
					}
				}
			}
			cur = cur->next;
		}
	}
void Investments::del(std::string searchasset = "-1", double openprice = -1,
	double closeprice = -1, double commision = -1, double  count = -1, int currency = -1) {
		Node* cur = head;
		Node* temp;
		while (cur) {
			if (searchasset == cur->assetdata.get_assetname() || searchasset == "-1") {
				if (openprice == cur->assetdata.get_openprice() || openprice == -1) {
					if (closeprice == cur->assetdata.get_closeprice() || closeprice == -1) {
						if (commision == cur->assetdata.get_commission() || commision == -1) {
							if (count == cur->assetdata.get_count() || count == -1) {
								if (currency == cur->assetdata.get_currency() || currency == -1) {
									//удаление элемента
									if (cur == head) {
										if (head->next) {
											temp = cur->next;
											head = head->next;
											delete head->prev;
											head->prev = nullptr;
											cur = head;
										}
										else {
											delete head;
											head = nullptr;
											tail = nullptr;
											cur = nullptr;
										}

									}
									else if (cur == tail) {
										tail->prev->next = nullptr;
										tail = tail->prev;
										delete cur;
										cur = nullptr;
									}
									else {
										temp = cur->next;
										cur->prev->next = cur->next;
										cur->next->prev = cur->prev;
										delete cur;
										cur = temp;
									}
									--SIZE;
									continue;

								}
							}
						}
					}
				}
			}
			cur = cur->next;
		}
	}
void Investments::del(const AssetData& const obj) {
		Node* cur = head;
		Node* temp;
		while (cur) {
			if (obj.get_assetname() == cur->assetdata.get_assetname() || obj.get_assetname() == "-1") {
				if (obj.get_openprice() == cur->assetdata.get_openprice() || obj.get_openprice() == -1) {
					if (obj.get_closeprice() == cur->assetdata.get_closeprice() || obj.get_closeprice() == -1) {
						if (obj.get_commission() == cur->assetdata.get_commission() || obj.get_commission() == -1) {
							if (obj.get_count() == cur->assetdata.get_count() || obj.get_count() == -1) {
								if (obj.get_currency() == cur->assetdata.get_currency() || obj.get_currency() == -1) {
									//удаление элемента
									if (cur == head) {
										if (head->next) {
											temp = cur->next;
											head = head->next;
											delete head->prev;
											head->prev = nullptr;
											cur = head;
										}
										else {
											delete head;
											head = nullptr;
											tail = nullptr;
											cur = nullptr;
										}
									}
									else if (cur == tail) {
										tail->prev->next = nullptr;
										tail = tail->prev;
										delete cur;
										cur = nullptr;
									}
									else {
										temp = cur->next;
										cur->prev->next = cur->next;
										cur->next->prev = cur->prev;
										delete cur;
										cur = temp;
									}
									--SIZE;
									continue;

								}
							}
						}
					}
				}
			}
			cur = cur->next;
		}
	}
void Investments::del(Node* ptr) {
		Node* cur = head, * temp;
		while (cur) {
			if (cur == ptr) {
				if (cur == head) {
					if (head->next) {
						temp = cur->next;
						head = head->next;
						delete head->prev;
						head->prev = nullptr;
						cur = head;
					}
					else {
						delete head;
						head = nullptr;
						tail = nullptr;
						cur = nullptr;
					}
				}
				else if (cur == tail) {
					tail->prev->next = nullptr;
					tail = tail->prev;
					delete cur;
					cur = nullptr;
				}
				else {
					temp = cur->next;
					cur->prev->next = cur->next;
					cur->next->prev = cur->prev;
					delete cur;
					cur = temp;
				}
				--SIZE;
				return;
			}
			cur = cur->next;
		}
	}
bool Investments::edit(std::string assetname, double openprice,
	double closeprice, double commision, double count, int currency,
	std::string newassetname = "-1", double newopenprice = -1,
	double newcloseprice = -1, double newcommision = -1, double  newcount = -1, int newcurrency = -1) {
		Node* cur = head;
		try {
			while (cur) {
				if (assetname == cur->assetdata.get_assetname() && openprice == cur->assetdata.get_openprice() &&
					closeprice == cur->assetdata.get_closeprice() && commision == cur->assetdata.get_commission() &&
					count == cur->assetdata.get_count() && currency == cur->assetdata.get_currency()) {

					if (newassetname != "-1")
						if (!cur->assetdata.set_assetname(newassetname)) throw std::exception("Неверный формат имени.");
					if (newopenprice != -1)
						if (!cur->assetdata.set_openprice(newopenprice)) throw std::exception("Неверный формат цены открытия.");
					if (newcloseprice != -1)
						if (!cur->assetdata.set_closeprice(newcloseprice)) throw std::exception("Неверный формат цены открытия.");
					if (newcommision != -1)
						if (!cur->assetdata.set_commission(newcommision)) throw std::exception("Неверный формат комиссии.");
					if (newcount != -1)
						if (!cur->assetdata.set_count(newcount)) throw std::exception("Неверный формат количества.");
					if (newcurrency != -1)
						if (!cur->assetdata.set_currency(newcurrency)) throw std::exception("Неверный формат валюты.");
					unite_equals();
					return true;

				}
				cur = cur->next;
			}
		}
		catch (const std::exception& obj) {
			std::cout << obj.what() << '\n';
		}
		return false;
	}
void Investments::sort() {
		if (!head || !head->next) return;
		head = merge_sort(head);
		tail = head;
		while (tail->next) tail = tail->next;
	}
void Investments::unite_equals() {
		Node* i = head, * j = i->next, * temp;
		while (i) {
			while (j) {
				if (i->assetdata == j->assetdata) {
					i->assetdata.set_count(j->assetdata.get_count() + i->assetdata.get_count());
					temp = j->prev;
					del(j);
					j = temp->next;
				}
				else j = j->next;
			}
			i = i->next;
			if (i && i->next)
				j = i->next;
		}
	}
bool Investments::save(std::string ofile_name) {
		std::ofstream ofile(ofile_name, std::ios::binary | std::ios::out);
		if (!ofile) return false;
		size_t str_size;
		ofile.write((char*)&SIZE, sizeof(SIZE));
		Node* cur = head;
		while (cur) {
			str_size = cur->assetdata.get_assetname().length() + 1;
			ofile.write((char*)&str_size, sizeof(str_size));
			ofile.write((char*)cur->assetdata.get_assetname_ref().c_str(), str_size);
			ofile.write((char*)&cur->assetdata.get_openprice_ref(), sizeof(cur->assetdata.get_openprice()));
			ofile.write((char*)&cur->assetdata.get_closeprice_ref(), sizeof(cur->assetdata.get_closeprice()));
			ofile.write((char*)&cur->assetdata.get_commission_ref(), sizeof(cur->assetdata.get_commission()));
			ofile.write((char*)&cur->assetdata.get_count_ref(), sizeof(cur->assetdata.get_commission()));
			ofile.write((char*)&cur->assetdata.get_currency_ref(), sizeof(cur->assetdata.get_currency()));
			cur = cur->next;
		}
		ofile.close();
		return true;
	}
bool Investments::load(std::string ifile_name) {
		std::ifstream ifile(ifile_name, std::ios::binary | std::ios::in);
		if (!ifile) return false;
		std::string assetname;
		AssetData cur;
		double openprice, closeprice, commission, count;
		size_t str_size;
		int inv_size, currency;
		Investments loadInv;
		try {
			ifile.read((char*)&inv_size, sizeof(inv_size));
			for (int i = 0; i < inv_size; ++i) {
				ifile.read((char*)&str_size, sizeof(str_size));
				char* buf = new char[str_size];
				ifile.read(buf, str_size);
				assetname = buf;
				delete[] buf;
				ifile.read((char*)&openprice, sizeof(cur.get_openprice()));
				ifile.read((char*)&closeprice, sizeof(cur.get_closeprice()));
				ifile.read((char*)&commission, sizeof(cur.get_commission()));
				ifile.read((char*)&count, sizeof(cur.get_count()));
				ifile.read((char*)&currency, sizeof(cur.get_currency()));
				if (cur.set_all(assetname, openprice, closeprice, commission, count, currency))
					loadInv.push(cur);
				else throw std::exception("Некорректные значения параметров AssetData");
			}
			ifile.close();
			
		}
		catch (const std::exception& ex) {
			loadInv.~Investments();
			return false;
		}
		*this = loadInv;
		return true;
	}
void Investments::operator=(Investments& obj) {
		this->head = obj.head;
		this->tail = obj.tail;
		this->SIZE = obj.SIZE;
		obj.head = nullptr;
		obj.tail = nullptr;
		obj.SIZE = 0;
	}
