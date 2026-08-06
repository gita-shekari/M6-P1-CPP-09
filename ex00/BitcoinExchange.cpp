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

void BitcoinExchange::checkFormat(const std::string &raw)
{
	if(raw.length() != 10)
		throw runtime_error("Wrong format of date!");
	if (raw[4] != '-' || raw[7] != '-')
		throw std::runtime_error("Wrong format of date!");
	for(size_t i = 0; i < raw.length(); i++)
	{
		if(i == 4 || i == 7)
			continue;
		if(!isdigit(raw[i]))
			throw std::runtime_error("Wrong format of date!");
	}
}
t_date BitcoinExchange::extractDate(const std::string &raw)
{
	std::string y = raw.substr(0 , 4);
	std::string m = raw.substr(5 , 2);
	std::string d = raw.substr(8 , 2);
	t_date _date;
	_date.year = std::atoi(y.c_str());
	_date.month = std::atoi(m.c_str());
	_date.day = std::atoi(d.c_str());
	return _date;
}
bool BitcoinExchange::isLeapyaer(int year)
{
	if (year % 4 != 0)
		return false;
	if (year % 100 != 0)
		return true;
	if (year % 400 == 0)
		return true;
	return false;
}
void BitcoinExchange::validateDate(const t_date &_date)
{
	if(_date.year <= 0)
		throw std::runtime_error("Invalid year!");
	if(_date.month > 12 || _date.month  < 1)
		throw std::runtime_error("Invalid month!");
	if(_date.day > 31 || _date.day  < 1)
		throw std::runtime_error("Invalid month!");
	if((_date.month == 4 || _date.month == 6 || _date.month == 9 || _date.month == 11)
			&& (_date.day > 30))
		throw std::runtime_error("Invalid day!");
	if(_date.month == 2)
		if(isLeapyaer(_date.year))
			if(day > 28)
				throw std::runtime_error("Invalid day!");
	}

t_date BitcoinExchange::parseDate(const std::string &raw)
{
	checkFormat(raw);
	t_date d = extractDate(raw);
	validateDate(d);
	return d;

}
double BitcoinExchange::parseValue(const std::string &raw)
{
	double d = std::
}
t_record BitcoinExchange::parse_record(const std::string &line)
{
	t_record rec;
	size_t pos = line.find(',');
	if(pos == std::string::npos)
		throw std::runtime_error("Wrong format of data!");
	try
	{
		rec.date = parseDate(line.substr(0, pos));
		rec.value = parseValue(line.substr(pos + 1));
		return rec;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
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
