#pragma once
#include "AssetData.h"
AssetData::AssetData() {};
AssetData::~AssetData() {};
bool AssetData::set_assetname(const std::string& const assetname){
	if (assetname.length() > maxAssetnameLength) return false;
	this->assetname = assetname;
	return true;
}
bool AssetData::set_openprice(const double& const openprice) {
	if (openprice < 0) return false;
	this->openprice = openprice;
	return true;
}
bool AssetData::set_closeprice(const double& const closeprice) {
	if (closeprice < 0) return false;
	this->closeprice = closeprice;
	return true;
}
bool AssetData::set_commission(const double& const commission) {
	if (commission < 0) return false;
	this->commission = commission;
	return true;
}
bool AssetData::set_count(const double& const count) {
	if (count < 0) return false;
	this->count = count;
	return true;
}
bool AssetData::set_currency(const int& const currency) {
	if ((currency < 0) || (currency > maxCurrency)) return false;
	this->currency = currency;
	return true;
}
bool AssetData::set_all(const std::string& const assetname, const double& const openprice,
	const double& const closeprice, const double& const commission,
	const double& const count, const int& const currency) {
	if (set_assetname(assetname) && set_openprice(openprice) && set_closeprice(closeprice)
		&& set_commission(commission) && set_count(count) && set_currency(currency)) return true;
	return false;
}
std::string AssetData::get_assetname() const { return assetname;}
const std::string& AssetData::get_assetname_ref() const {return assetname;}
const double& AssetData::get_openprice_ref() const { return openprice; }
const double& AssetData::get_closeprice_ref() const { return closeprice; }
const double& AssetData::get_commission_ref() const { return commission; }
const double& AssetData::get_count_ref() const { return count; }
const int& AssetData::get_currency_ref() const { return currency; }

double AssetData::get_openprice() const { return openprice;}
double AssetData::get_closeprice() const {return closeprice;}
double AssetData::get_commission() const {return commission;}
double AssetData::get_count() const {return count;}
int AssetData::get_currency() const {return currency;}
bool AssetData::is_valid()  {
	if ((assetname.length() > 14) || (openprice < 0) || (closeprice < 0)
		|| (commission < 0) || (count < 0) || (currency < 0)
		|| (currency != (int)currency) || (currency > maxCurrency)) return false;
	return true;
}
bool AssetData::operator==(const AssetData& const obj2) {
	return (this->assetname == obj2.assetname) * (this->closeprice == obj2.closeprice) *
		(this->openprice == obj2.openprice) * (this->commission == obj2.commission) *
		(this->currency == obj2.currency);
}