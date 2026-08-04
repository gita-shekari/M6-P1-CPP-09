#ifndef BITCOINCHANGE_HPP
#define BITCOINCHANGE_HPP

#include <algorithm>
#include <iostream>
#include <exception>
#include <map>

typedef struct s_date
{
	int day;
	int month;
	int year;
}t_date;

typedef struct s_line
{
	t_date input_date;
	double value;
}t_line;

class BitcoinChange
{
	public:
		BitcoinChange();
		BitcoinChange(const BitcoinChange &other);
		BitcoinChange &operator=(const BitcoinChange &other);
		~BitcoinChange();
		//bool operator<(const Date& lhs, const Date& rhs);

	private:
		std::map<s_date, double> data;

};
#endif
