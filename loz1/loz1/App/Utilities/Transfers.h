#ifndef TRANSFERS_H
#define TRANSFERS_H

#include<string>

namespace Transfer{

	std::string i2s(int);
	std::string d2s(double, int=2);
	int s2i(std::string);
	double s2d(std::string);

}

#endif