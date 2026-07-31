
#include "BitcoinExchange.hpp"
#include <fstream>

s_line parse_line(std::string line)
{
	while(line)
	{
		std::find(line.c_str(), '/');
		if()
	}
}
void parse_file(char *fileName)
{
	std::ifstream inFile(fileName.c_str());
	if (!inFile.is_open())
		throw std::runtime_error("File can not be opened!");
	std::string line;
	while(getline(infile, line))
	{
		if(line.empty)
		{
			infile.close();
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
	if(argc != 2)
	{
		std::cout << "No input file" << std::endl;
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
