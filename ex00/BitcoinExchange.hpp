#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <iostream>
#include <exception>
#include <fstream>
#include <cctype>
#include <map>

typedef struct s_date
{
	int day;
	int month;
	int year;
}t_date;

typedef struct s_record
{
	t_date _date;
	double value;
}t_record;

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		void loadData(const std::string& filename);
		void processInput(const std::string& filename);

	private:
		std::map<t_date, double> _data;

};
bool operator<(const t_date& lhs, const t_date& rhs);
#endif
