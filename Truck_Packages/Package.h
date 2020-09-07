/*
 * Package.h
 *
 *  Created on: Jan 10, 2020
 *      Author: Prof. Lupoli
 */

#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <iostream>
#include <string>
using namespace std;

#include "Address.h"
#include "Dimension.h"

class Package {
public:
	Package();
	Package(Address &a, Dimension &d, string id, float weight);

	const Address& getAddress() const { return address; }
	void setAddress(const Address& address) { this->address = address; }

	const Dimension& getDimension() const { return dimension; }
	void setDimension(const Dimension& dimension) { this->dimension = dimension; }

	const string& getId() const { return ID; }
	void setId(const string& id) { ID = id; }

	float getWeight() const { return weight; }
	void setWeight(float weight) { this->weight = weight; }

	// overloaded cout
	//I was going to put the overloaded cout in Liquid.h since I had assumed that the DisplayLastItenInTruck() function
	//required every parameter, including type and flammable. However, since I saw the "overloaded cout" comment here, I am
	//unsure of whether the DisplayLastItenInTruck() needs to have those two parameters.
	friend const ostream& operator << (ostream& os, const Package pack)
	{
		os << pack.address;
		os << ", ";
		os << pack.dimension;
		os << ", ";
		os << pack.ID;
		os << ", ";
		os << pack.weight;
		os << endl;
		return os;
	}

protected:
	string ID;
	float weight;
	Dimension dimension;
	Address address;

};

inline Package::Package()
{
	ID = "";
	weight = 0.0;
}

inline Package::Package(Address &a, Dimension &d, string id, float weight)
{
	this->address = a;
	this->dimension = d;
	this->ID = id;
	this->weight = weight;
}

#endif /* PACKAGE_H_ */