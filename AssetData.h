#pragma once
#ifndef ASSETDATA_H
#define ASSETDATA_H
#include <string>
class AssetData {
private:
	
	std::string assetname;
	double openprice;
	double closeprice;
	double commission;
	double count;
	int currency;
public:
	bool set_all(const std::string& const assetname, const double& const openprice,
		const double& const closeprice, const double& const commission,
		const double& const count, const  int& const currency);
	const static int maxCurrency = 2;
	const static int maxAssetnameLength = 14;
	bool set_assetname(const std::string& const assetname);
	bool set_openprice(const double& const openprice);
	bool set_closeprice(const double& const closeprice);
	bool set_commission(const double& const commission);
	bool set_count(const double& const count);
	bool set_currency(const int& const currency);

	std::string get_assetname() const;
	double get_openprice() const;
	double get_closeprice() const;
	double get_commission() const;
	double get_count() const;
	int get_currency() const;

	const std::string& get_assetname_ref() const;
	const double& get_openprice_ref() const;
	const double& get_closeprice_ref() const;
	const double& get_commission_ref() const;
	const double& get_count_ref() const;
	const int& get_currency_ref() const;

	AssetData() ;
	bool is_valid();
	~AssetData() ;
	bool operator==(const AssetData& const obj2);
}; 
#endif