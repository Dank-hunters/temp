#include <map>
#include <vector>
#include "common.hpp"
#include <iostream>

int main()
{
	

	_TN::map<std::string, int>	test;
	_TN::map<std::string, int>::const_iterator it;
	_TN::map<std::string, int>::const_iterator ite;
	
	std::cout <<  "size before add" <<  test.size() << std::endl;
	
	test.insert(_TN::pair<std::string, int>("paa", 5));
	test.insert(_TN::pair<std::string, int>("pax", 10));
	test.insert(_TN::pair<std::string, int>("pas", 15));
	test.insert(_TN::pair<std::string, int>("paw", 20));
	test.insert(_TN::pair<std::string, int>("par", 25));
	test.insert(_TN::pair<std::string, int>("pay", 220));
	std::cout << "size after add dl |" << test.size() << "||" << std::endl;
	
	
	std::cout << "chelouuuuuuuuuu" << std::endl << std::endl;
	//printHelper(test.get_root(), "", true, true);


	_TN::map<std::string, int>::const_iterator itei;
	_TN::map<std::string, int>::const_iterator itee;

	itei = test.begin();
	itee = test.begin();

	itee++;
	itee++;
	itee++;
//	_TN::map<std::string, int>	testi;

//	testi.insert(itei, itee);
//    it = test.begin();
//	printHelper(testi.get_root(), "", true, true);
        it = test.begin();
    ite = test.end();
	//ite--;
	//ite--;
//	ite--;
	//ite--;
	//ite--;
//	std::cout << "ite --  " <<  ite->first << " end "<< std::endl;

	/*std::cout << "size de testi" << testi.size() << "||" <<  std::endl;
*/

    while(it != ite)
	{
	std::cout << "start  " <<  it->first << " end "<< std::endl;
		it++;
	}
	return(0);
}
