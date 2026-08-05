#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other):data(other._data){}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if(this != &other)
	{
		_data = other._data;
	}
	return *this;
}
BitcoinExchange::~BitcoinExchange(){}

t_record BitcoinExchange::parse_record(std::string const line)
{
	size_t pos = line.find(',');
	
}
void BitcoinExchange::loadData(const std::string& filename)
{
	std::ifstream inFile(fileName);
	if (!inFile.is_open())
		throw std::runtime_error("data can not be opened!");
	std::string line;
	getline(inFile, line);
	if(line != "date,exchange_rate")
	{
		throw std::runtime_error("Wrong format of data");
		return ;
	}
	while(getline(inFile, line))
	{
		t_record record = parse_record(line);
		_data.insert(std::make_pair(record._date, record.value));
	}
}
void BitcoinExchange::processInput(const std::string& filename)
{

}
