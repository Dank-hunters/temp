#include <map>
#include <list>
#include <iostream>
#include "common.hpp"


#define T1 int
#define T2 std::string
typedef _pair<const T1, T2> T3;

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "ret: " << mp.erase(param) << std::endl;
	printSize(mp);
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 6;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));

	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	//std::cout << mp.end()->first << std::endl;
		std::cout << "heu gt pas au courrant de cette merde ptn" << std::endl;

/*	printSize(mp);
	mp.erase(mp.begin(), mp.end());
	mp.insert(TESTED_NAMESPACE::make_pair<T1, T2>(1, "ss"));
	mp.insert(TESTED_NAMESPACE::make_pair<T1, T2>(2, "sqs"));
	mp.insert(TESTED_NAMESPACE::make_pair<T1, T2>(3, "sas"));
	mp.insert(TESTED_NAMESPACE::make_pair<T1, T2>(4, "sss"));
	mp.erase(mp.begin(), mp.end());
	mp.insert(TESTED_NAMESPACE::make_pair<T1, T2>(3, "sas"));
//	mp.insert(TESTED_NAMESPACE::make_pair<T1, T2>(2, "sqs"));
	TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin();*/
	
	
	
	//mp.insert(TESTED_NAMESPACE::make_pair<T1, T2>(1, "ss"));
	//mp.insert(TESTED_NAMESPACE::make_pair<T1, T2>(2, "sqs"));


	for (int i = 2; i < 4; ++i)
		ft_erase(mp, i);
	///TESTED_NAMESPACE::map<T1, T2>::const_iterator cit = mp.begin();
	//if (cit != it)

	ft_erase(mp, mp.begin()->first);
	ft_erase(mp, (--mp.end())->first);

	mp[-1] = "Hello";
	mp[10] = "Hi there";
	mp[10] = "Hi there";
	printSize(mp);

	ft_erase(mp, 0);
	ft_erase(mp, 1);

	return (0);
}
