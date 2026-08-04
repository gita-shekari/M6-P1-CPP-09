
#include "BitcoinExchange.hpp"
#include <fstream>

bool vlaidate_title(std::string line)
{
	if (line == "date | value")
		return true;
	return false;
}
void parse_line(const std::string& line)
{
	size_t pos = line.find(" | ");

	if (pos == std::string::npos)
		throw std::runtime_error("Bad input");

	std::string date = line.substr(0, pos);
	std::string value = line.substr(pos + 3);
	char *end;
	double v = std::strtod(value.c_str(), &end);
	if (*end != '\0')
		throw std::runtime_error("Invalid number");
	std::cout << "Date : " << date << std::endl;
	std::cout << "Value: " << v << std::endl;
}
void parse_file(char *fileName)
{
	std::ifstream inFile(fileName);
	if (!inFile.is_open())
		throw std::runtime_error("File can not be opened!");
	std::string line;
	getline(inFile, line);
	if(!vlaidate_title(line))
	{
		inFile.close();
		throw std::runtime_error("No valid data!");
		return ;
	}
	while(getline(inFile, line))
	{
		if(line.empty())
		{
			inFile.close();
			throw std::runtime_error("No valid data!");
		}
		else
		{
			parse_line(line);
		}
	}
}

int main(int ac, char **av)
{
	if(ac != 2)
	{
		std::cout << "input is not valid" << std::endl;
		return 1;
	}
	
	try
	{
		parse_file(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
