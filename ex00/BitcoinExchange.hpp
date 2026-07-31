#ifndef BITCOINCHANGE_HPP
#define BITCOINCHANGE_HPP

#include <algorithm>
#include <iostream>
#include <exception>
#include <map>

typedef struct s_date
{
	int day,
	int month;
	int year;
}t_date;

typedef struct s_line
{
	t_date input_date;
	unsigned int price;
}t_line;

class BitcoinChange
{
	public:
		BitcoinChange();
		BitcoinChange(const BitcoinChange &other);
		BitcoinChange &operator=(const BitcoinChange &other);
		~BitcoinChange();

	private:
		std::multimap<t_date, unsigned int> data;

}
#endif
