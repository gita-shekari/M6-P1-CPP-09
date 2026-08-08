
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if(ac != 2)
	{
		std::cout << "input is not valid" << std::endl;
		return 1;
	}
	const std::string fileName = av[1];
	BitcoinExchange *btc = new BitcoinExchange();
	try
	{
		btc->loadData("data.csv");
		btc->processInput(fileName);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
