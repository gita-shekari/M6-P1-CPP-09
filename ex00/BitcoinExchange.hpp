#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

struct t_record
{
	std::string date;
	double		value;
};

class BitcoinExchange
{
	private:
		std::map<std::string, double> _data;

		void		checkFormat(const std::string &raw);
		void		validateDate(const std::string &date);
		bool		isLeapYear(int year);
		double		parseValue(const std::string &raw);
		t_record	parse_record(const std::string &line, const char c);

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		void		loadData(const std::string &filename);
		void		processInput(const std::string &filename);
};

#endif
