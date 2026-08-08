#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other):_data(other._data){}
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
		throw std::runtime_error("Wrong format of date!");
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
bool BitcoinExchange::isLeapYear(int year)
{
	if (year % 4 != 0)
		return false;
	if (year % 100 != 0)
		return true;
	if (year % 400 == 0)
		return true;
	return false;
}
void BitcoinExchange::validateDate(const std::string &date)
{
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (year <= 0)
		throw std::runtime_error("Invalid year!");
	if (month < 1 || month > 12)
		throw std::runtime_error("Invalid month!");
	if (day < 1 || day > 31)
		throw std::runtime_error("Invalid day!");
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		throw std::runtime_error("Invalid day!");
	if (month == 2)
	{
		if (isLeapYear(year))
		{
			if (day > 29)
				throw std::runtime_error("Invalid day!");
		}
		else
		{
			if (day > 28)
				throw std::runtime_error("Invalid day!");
		}
	}
}

double BitcoinExchange::parseValue(const std::string &raw)
{
	char *end;
	double value = std::strtod(raw.c_str(), &end);
	if (end == raw.c_str() || *end != '\0')
		throw std::runtime_error("Invalid value!");
	return value;
}
t_record BitcoinExchange::parse_record(const std::string &line, const char c)
{
	size_t pos = line.find(c);
	if (pos == std::string::npos)
		throw std::runtime_error("missing separator or value!");
	t_record record;
	if (c == ',')
	{
		record.date = line.substr(0, pos);
		record.value = parseValue(line.substr(pos + 1));
	}
	else if (c == '|')
	{
		if (pos == 0 || pos + 1 >= line.size()
			|| line[pos - 1] != ' ' || line[pos + 1] != ' ')
			throw std::runtime_error("Wrong format of input!");
		record.date = line.substr(0, pos - 1);
		record.value = parseValue(line.substr(pos + 2));
		if(record.value < 0)
			throw std::runtime_error("not a positive number.");
		if(record.value > 1000)
			throw std::runtime_error("too large a number.");
	}
	checkFormat(record.date);
	validateDate(record.date);
	return record;
}

void BitcoinExchange::processRecord(t_record rec)
{
	std::map<std::string, double>::iterator it;
	it = _data.upper_bound(rec.date);
	if (it != _data.begin())
		--it;
	std::cout << std::setprecision(10);
	std::cout << rec.date << " => " << rec.value << " = " << rec.value * it->second << std::endl;
}
void BitcoinExchange::loadData(const std::string &filename)
{
	std::ifstream inFile(filename.c_str());
	if (!inFile.is_open())
		throw std::runtime_error("data file can not be opened!");
	std::string line;
	std::getline(inFile, line);
	if(line != "date,exchange_rate")
		throw std::runtime_error("Wrong format of data");
	while (std::getline(inFile, line))
	{
		try
		{
			t_record record = parse_record(line, ',');
			_data.insert(std::make_pair(record.date, record.value));
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << line << " => " << e.what() << std::endl;
		}
	}
	inFile.close();
}
void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream inFile(filename.c_str());
	if (!inFile.is_open())
		throw std::runtime_error("input file can not be opened!");
	std::string line;
	std::getline(inFile, line);
	if(line != "date | value")
		throw std::runtime_error("Wrong format of input");
	while (std::getline(inFile, line))
	{
		try
		{
			t_record input_record = parse_record(line, '|');
			processRecord(input_record);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << line << " => " << e.what() << std::endl;
		}
	}
	inFile.close();
}
