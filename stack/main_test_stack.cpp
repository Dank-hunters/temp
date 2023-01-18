#include "stack.hpp"
#include <iostream>
#include "../vector/vector.hpp"

void	printStack(TESTED_NAMESP::stack<int, TESTED_NAMESP::vector<int> >	to_print)
{

	while (to_print.empty() == 0)
	{
		std::cout << "-" << to_print.top() << std::endl;
		to_print.pop();
	}
}

int main()
{
	TESTED_NAMESP::vector<int>	vector_test;
	
	std::cout << "insert 5, 10, 15, 20 to stack_test" << std::endl;

	vector_test.insert(vector_test.end(), 5);
	vector_test.insert(vector_test.end(), 10);
	vector_test.insert(vector_test.end(), 15);
	vector_test.insert(vector_test.end(), 20);


	std::cout << std::endl;
	std::cout << "Is my vector is empty ? " << std::endl << "- " << vector_test.empty() << std::endl;
	
	std::cout << std::endl;
	std::cout << "test copy constructor " << std::endl;
	std::cout << std::endl;

	TESTED_NAMESP::stack<int, TESTED_NAMESP::vector<int> >	stack_copy_test(vector_test);
	TESTED_NAMESP::vector<int>::iterator ite = vector_test.end();
	TESTED_NAMESP::vector<int>::iterator it = vector_test.begin();
	
	std::cout << "my vector :" << std::endl;
    std::cout << std::endl;
	while (ite != it)
	{
		ite--;
		std::cout << "-" << *ite << std::endl;
	}
	std::cout << std::endl;
	std::cout << "my copy stack : " << std::endl;
	std::cout << std::endl;

	printStack(stack_copy_test);

	TESTED_NAMESP::stack<int, TESTED_NAMESP::vector<int> >	test1(vector_test);
	std::cout << std::endl;

	std::cout << "size : " << test1.size() << std::endl;
	std::cout << std::endl;

	std::cout << "test push for stack, adding 3 element " << std::endl;

	test1.push(17);
	test1.push(19);
	test1.push(25);

	std::cout << "new size : " << test1.size() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

 	TESTED_NAMESP::vector<int>	vector_test2;
	vector_test2.insert(vector_test2.end(), 12);
	vector_test2.insert(vector_test2.end(), 50);
	vector_test2.insert(vector_test2.end(), 18);
	vector_test2.insert(vector_test2.end(), 12);
	vector_test2.insert(vector_test2.end(), 54);
	TESTED_NAMESP::stack<int, TESTED_NAMESP::vector<int> >	test2(vector_test2);

	std::cout << "###################    TESTING RELATIONAL OPERATOR    ###################" << std::endl;
	std::cout << std::endl;

	std::cout << "Operator == : " << (test1 == test2) << "| Operator != : " << (test1 != test2) << std::endl;
	std::cout << "Operator <= : " << (test1 <= test2) << "| Operator >= : " << (test1 >= test2) << std::endl;
	std::cout << "Operator < :" << (test1 < test2) << "| Operator > : " << (test1 < test2) << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;





	return(0);
}

