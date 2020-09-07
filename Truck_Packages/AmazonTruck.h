/*
 * AmazonTruck.h
 *
 *  Created on: Jan 9, 2020
 *      Author: Prof. Lupoli
 */

#ifndef AMAZONTRUCK_H_
#define AMAZONTRUCK_H_

#include <iostream>
#include <vector>
#include <ostream>
#include <fstream>
using namespace std;

#include "Package.h"
#include "Liquid.h"
fstream file;
class AmazonTruck {
public:
	AmazonTruck(short v) {volumn = v; }
	~AmazonTruck() { delete truck; }

	bool isFull()
	{
		if (volumn == 1644)
		{
			return true;
		}
		else if (volumn > 1644)
		{
			truck->pop_back();
			return true;
		}
		else
		{
			return false;
		}
		
	}
	// resets truck volumn and packages inside to 0 for every "new" truck
	void makeEmpty()
	{
		volumn = 0;
		truck->clear();
	}
	float totalVolumnSoFar()
	{
		cout << volumn;
		return volumn;
	}

	/*
	 * 1. How will you parse the address from the data file to match address, town, etc...?
	 */
	void fillFromFile(string filename)
	{
		ifstream file(filename);
		string address1, town, state, id, type, conv;
		int zip, width, height, depth, flame, volume;
		float weight;
		bool flammable;
		//iterates through csv file until it hits the volumn limit
		while (volumn < 1644)
		{
			getline(file, address1, ',');
			getline(file, town, ',');
			getline(file,state, ',');
			getline(file, conv, ',');
			zip = stoi(conv);
			getline(file, conv, ',');
			width = stoi(conv);
			getline(file, conv, ',');
			height = stoi(conv);
			getline(file, conv, ',');
			depth = stoi(conv);
			getline(file, id, ',');
			getline(file, conv, ',');
			weight = stof(conv);
			getline(file, type, ',');
			getline(file, conv);
			flame = stoi(conv);
			if (flame == '1')
			{
				flammable = true;
			}
			else {
				flammable = false;
				}
			volume = height * width * depth;
			//The prompt says to not include the packages if they have a negative, but I would also think that if a dimension is 0, 
			//it should also not be included as well?
			if (height >= 0 && width >= 0 && depth >= 0)
			{
				volumn += volume;
				Address * add = new Address(address1, town, state, zip);
				Dimension * dim = new Dimension(width, height, depth);
				Liquid * liq = new Liquid(*add, *dim, id, weight, type, flammable);
				truck->push_back(*liq);
				delete add;
				delete dim;
				delete liq;

				add = nullptr;
				dim = nullptr;
				liq = nullptr;
				isFull();
			}
		}
		

	}
	//displays the last element in the vector
	void displayLastItenInTruck()
	{
		if (truck->size() > 0)
		{
			cout << truck->at(truck->size()-1);
		}
	}



private:

	/*
	 * No other data members are allowed!!!
	 */
	vector <Package> *truck = new vector <Package>;
	short volumn;
	/*
	 * No other data members are allowed!!!
	 */

};

#endif /* AMAZONTRUCK_H_ */