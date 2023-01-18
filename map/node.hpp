#pragma once 
#include "../includes/pair.hpp"

namespace ft
{
	template <class Pair> 
	class Node
	{
		public :
			typedef Pair    value_type;
			typedef size_t	size_type;
			Node            *left;    
			Node            *right;    
			Node            *daddy;    
			Node 			*end;
			Node 			*max;
			bool			print;
			value_type      val;
		

			Node():  left(NULL), right(NULL), daddy(NULL), end(NULL), max(NULL),  print(1), val(NULL){}
			
			Node(const value_type &val): left(NULL), right(NULL), daddy(NULL), end(NULL), max(NULL),  print(1), val(val){} 

			value_type *get_pair()
			{
				if (print == 0)
					return(NULL);
				return (&val);
			}

			Node	*mini(Node *search) const
			{
				if (search->left == NULL)
					return (search);
				while (search->left)
					search = search->left;
				return (search);
			}

			Node	*maxi(Node *search)
			{
				if (search->right == NULL)
					return (search);
				while (search->right)
					search = search->right;

				return (search);
			}
		
			Node *next()
			{
				Node *tmp = this;

			//std::cout << (*max)->val.first;
				if (tmp == max)
					return(end);
				if (tmp->right)
					return mini(tmp->right);
				Node* tmpdaddy = tmp->daddy;
				while (tmpdaddy && tmp == tmpdaddy->right)
				{
					tmp = tmpdaddy;
					tmpdaddy = tmpdaddy->daddy;
				}
				return tmpdaddy;
			}

			Node *prev(void)
			{
				Node *tmp = this;
	

				if (tmp->left != NULL)
					return maxi(tmp->left);
				Node* p = tmp->daddy;

				while (p && tmp == p->left)
				{
					tmp = p;
					p = p->daddy;
				}
				return p;
			}

			size_type	size(Node *N) const
			{
				if (N == NULL)
					return(0);
				Node *tmp;
				tmp = mini(N);
				size_type size = 0;
				while (tmp != NULL && tmp != end)
				{
	//std::cout << "hirdbgfskuddbrgsbfhkbcgvhhuxklgrhfgkulvdghf h gsdfiu giudsgivgrsd gd iugdsgoiu giu" << std::endl;

						tmp = tmp->next();
						size++;
				}
				return (size);
			}

	};
}
