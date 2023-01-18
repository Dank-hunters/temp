#pragma once
#include <memory>
#include <iostream>

#include <iterator>
#include <algorithm>
#include "../includes/enable_if.hpp"
#include "../includes/compare.hpp"
#include "../includes/reverse_iterator.hpp"
#include "../includes/bidirectional_iterator.hpp"
#include "../includes/const_bidirectional_iterator.hpp"
#include "../includes/pair.hpp"

namespace ft
{

	template <class Pair, class Compare=std::less<typename Pair::first_type>, class Alloc=std::allocator<Node<Pair> > >
	class tree
	{

	public:
		typedef Pair													value_type;
		typedef typename value_type::first_type									key_type;
		typedef typename value_type::second_type									val_type;
		//typedef _K														key_type;
		//typedef _P														val_type;
		typedef Compare													compare_type;
		typedef Alloc													allocator_type;
		typedef Node<Pair>												*node_ptr;
		typedef size_t 													size_type;
		typedef ft::bidirectional_iterator<value_type>					iterator;    
		typedef ft::const_bidirectional_iterator<const value_type>					const_iterator;
        typedef ft::reverse_iterator<iterator>							reverse_iterator;    
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	private:
		allocator_type													_alloc;	
		compare_type													_compare;
		node_ptr														_root;
		size_type														_size;
		node_ptr														_real_end;
		node_ptr														_maxi;
	public :
		
		
		tree(const compare_type &comp = compare_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _compare(comp), _root(NULL), _size(0), _real_end(), _maxi(NULL)
		{
			_real_end = new_node(ft::pair<key_type, val_type>());
		}        

		~tree()
		{
			if (_root)
				clear_all(_root);
			_root = _destroy_node(_root);
			_destroy_node(_real_end);


		}
		node_ptr	minii() const
		{
			node_ptr	current;

			current = _root;
			while (current != NULL && current->left != NULL)
				current = current->left;
			return (current);
		}

		node_ptr	maxii() const
		{
			node_ptr	current;

			current = _root;
			while (current != NULL && current->right != NULL)
				current = current->right;
			return (current);
		}

		iterator	begin() const
		{
			iterator	it(minii());
			if (_root == NULL)
				return(_real_end);
			return (it);
		}

		iterator	end() const
		{
			return (_real_end);
		}
		
		void	clear()
		{
			if (_root != NULL)
				clear_all(_root);
			//_real_end = _destroy_node(_real_end);
			_maxi = NULL;
		}

	private :
		node_ptr	new_node(value_type const &val)
		{
			node_ptr node = _alloc.allocate(sizeof(node_ptr));
			_alloc.construct(node, val);
			node->left = NULL;
			node->right = NULL;
			node->daddy= NULL;
			node->end = NULL;
			node->max = _maxi;
			return(node);
		}

		
		void clear_all(node_ptr	&tmp)
		{
			node_ptr	save = 0;
			if (tmp->left)
				{
					clear_all(tmp->left);
				}
			else if (tmp->right)
				clear_all(tmp->right);
			else
			{
				save = tmp->daddy;
				_alloc.destroy(tmp);
				_alloc.deallocate(tmp, sizeof(node_ptr));
				tmp = NULL;

			}
			if (save != _root)
			{
				clear_all(_root);
			}
			else 
			{
				return;
			}
		}

		node_ptr	_destroy_node(node_ptr node)
		{
			_size--;
			if (_size == 0)
				_root = NULL;
			if (node != NULL)
			{
				_alloc.destroy(node);
				_alloc.deallocate(node, sizeof(node_ptr));
				node = NULL;
			}
			return(NULL);
		}
	
    	void	is_new_max(const value_type &val, node_ptr last_add)
    	{
			(void)val;

			if (last_add == NULL)
				return;
    	    if (size() == 1 || _maxi == NULL)
    	    {
    	        _maxi = last_add;
    	        last_add->end = _real_end;
    	        _real_end->daddy = last_add;
				_real_end->print = 0;
				add_max();
			//	last_add->max = _maxi;
    	    }
    	    else
    	    {
    	        if (_compare(_maxi->val.first, last_add->val.first))
    	        {
					_real_end->print = 0;
    	            _maxi->end  = NULL;
    	            _maxi = last_add;
    	            _maxi->end = _real_end;
    	            _real_end->daddy =  _maxi;
					_maxi->max = _maxi;
					add_max();
    	        }
    	    }
    	}

		void	if_del_max(node_ptr todel,  const key_type &val)
		{
			if (todel == NULL)
				return;
			if (_compare(_maxi->val.first, val))
					return;
			else if (_compare(val, _maxi->val.first))
				return ;
			else 
			{
				_maxi->end = NULL;
				_maxi = _maxi->daddy;
				_maxi->end = _real_end;
				_real_end->daddy = _maxi;
				_maxi->max = _maxi;
				add_max();
			}
		}

		void add_max()
		{
			node_ptr tmp = _root->mini(_root);
			while(tmp != _maxi)
			{
				tmp->end = _real_end;
				tmp->max = _maxi;
				tmp = tmp->next();
			}
			_maxi->max = _maxi;
		}

				//////////			rotating /////////////////
		void	balancing(node_ptr current)
		{
			int		left_height = 0;
			int		right_height = 0;
			int		factor;

			while (current != NULL && current != _real_end)
			{
				left_height = 0;
				right_height = 0;
				if (current->left != NULL)
						left_height = 1 + get_sub_height(current->left);
				if (current->right != NULL)
					right_height = 1 + get_sub_height(current->right);
				factor = left_height - right_height;
				if (factor > 1 || factor < -1)
					choose_rotate(current, factor);
				current = current->daddy;
			}
		}


		void	choose_rotate(node_ptr current, int factor)
    	{
    	    int        left_height;
    	    int        right_height;

    	    left_height = 0;
    	    right_height = 0;
    	    if (factor > 1)
    	    {
    	        if (current->left->left != NULL)
    	            left_height = 1 + get_sub_height(current->left->left);
    	        if (current->left->right != NULL)
    	            right_height = 1 + get_sub_height(current->left->right);
    	        factor = left_height - right_height;
    	        if (factor > 0)
    	            RR_rotate(current, current->left);
    	        else
    	            LR_rotate(current, current->left, current->left->right);

    	    }
    	    else
    	    {
    	        if (current->right->left != NULL)
    	            left_height = 1 + get_sub_height(current->right->left);
    	        if (current->right->right != NULL)
    	            right_height = 1 + get_sub_height(current->right->right);
    	        factor = left_height - right_height;
    	        if (factor > 0)
    	            RL_rotate(current, current->right, current->right->left);
    	        else
    	            LL_rotate(current, current->right);
    	    }
    	}

		void	RR_rotate(node_ptr grandpa, node_ptr parent)
		{
			node_ptr	tie;

			tie = grandpa->daddy;
			grandpa->left = parent->right;
			if (parent->right != NULL)
				parent->right->daddy = grandpa;
			parent->right = grandpa;
			parent->daddy = tie;
			grandpa->daddy = parent;
			if (tie == NULL)
			{
				_root = parent;
				return ;
			}
			if (tie->left == grandpa)
				tie->left = parent;
			else
				tie->right = parent;

		}

		void	LL_rotate(node_ptr grandpa, node_ptr parent)
		{
			node_ptr	tie;

			tie = grandpa->daddy;
			grandpa->right = parent->left;
			if (parent->left != NULL)
				parent->left->daddy = grandpa;
			parent->left = grandpa;
			parent->daddy = tie;
			grandpa->daddy = parent;
			if (tie == NULL)
			{
				_root = parent;
				return ;
			}
			if (tie->left == grandpa)
				tie->left = parent;
			else
				tie->right = parent;

		}

		void	LR_rotate(node_ptr grandpa, node_ptr parent, node_ptr child)
		{
			node_ptr	tie;
			node_ptr	ltmp;
			node_ptr	rtmp;

			tie = grandpa->daddy;
			ltmp = child->left;
			rtmp = child->right;
			child->left = parent;
			child->right = grandpa;
			parent->daddy = child;
			parent->right = ltmp;
			if (ltmp)
				ltmp->daddy = parent;
			grandpa->daddy = child;
			grandpa->left = rtmp;
			if (rtmp)
				rtmp->daddy = grandpa;
			if (tie == NULL)
			{
				_root = child;
				child->daddy = NULL;
				return ;
			}
			if (tie->left == grandpa)
				tie->left = child;
			else
				tie->right = child;
			child->daddy = tie;
		}	

		void	RL_rotate(node_ptr grandpa, node_ptr parent, node_ptr child)
		{
			node_ptr	tie;
			node_ptr	ltmp;
			node_ptr	rtmp;

			tie = grandpa->daddy;
			ltmp = child->left;
			rtmp = child->right;
			child->left = grandpa;
			child->right = parent;
			parent->daddy = child;
			parent->left = rtmp;
			if (rtmp != NULL)
				rtmp->daddy = parent;
			grandpa->daddy = child;
			grandpa->right = ltmp;
			if (ltmp != NULL)
				ltmp->daddy = grandpa;
			if (tie == NULL)
			{
				_root = child;
				child->daddy = NULL;
				return ;
			}
			if (tie->left == grandpa)
				tie->left = child;
			else
				tie->right = child;
			child->daddy = tie;
		}


		int		get_sub_height(node_ptr current)
		{
			int		left_height;
			int		right_height;

			left_height = 0;
			right_height = 0;
			if (current == NULL)
				return (0);
			if (current->right != NULL )
				++right_height += get_sub_height(current->right);
			if (current->left != NULL)
				++left_height += get_sub_height(current->left);
			if (left_height > right_height)
				return (left_height);
			return (right_height);
		}

    	void    single_oblitarate(Node<Pair> &current)
 		{
			node_ptr	prev;
			node_ptr	tmp;
			node_ptr	substitute;
			int			direction;

			prev = current.daddy;
			tmp = &current;
			substitute = current.right;
			if (current.left != NULL)
				substitute = current.left;
			if (prev == NULL)
			{
				_root = substitute;
				substitute->daddy =NULL;
				_destroy_node(&current);
				return ;
			}
			direction = 2;
			if (prev->left->val.first == current.val.first)
				direction = 1;
			tmp = _destroy_node(tmp);
			if (direction == 1)
				prev->left = substitute;
			else
				prev->right = substitute;
			substitute->daddy = prev;
		}



    	void    complex_oblitarate(Node<Pair> &remove)
    	{
    	    node_ptr		substitute;
    	    node_ptr		current;
    	    node_ptr		prev;
			value_type		save_val;

    	    current = &remove;
    	    prev = remove.daddy;
			if (current->right  && current->left && !current->left->left)
				current = current->left;
			else
				current = current->right;
			while (current != NULL)
    	    {
    	        substitute = current;
    	        current = current->left;
    	    }
    	    save_val = substitute->val;
    	    erase(substitute->val.first);
    	    remove.val = save_val; //potentiel problem avec la validite des iterateurs
    	}

    	node_ptr	oblitarate(Node<Pair> &current, const int &direction)
    	{
    	    node_ptr prev;

    	    prev = current.daddy;

    	    if (current.left == NULL && current.right == NULL)
			{
				if (_size != 1)
					(direction == 1) ? prev->left = NULL : prev->right = NULL;
				_destroy_node(&current);
			}
			else if (current.left != NULL && current.right != NULL)
					complex_oblitarate(current);
			else
					single_oblitarate(current);
			return (NULL);
    	}

	public :

		ft::pair<iterator,bool>  insert (const value_type &val)
		{
			node_ptr	cursor = _root;
			node_ptr	prev = NULL;
			int		var = 0;

			while (cursor)
			{
				prev = cursor;
				if (_compare(val.first, cursor->val.first) && (var = 1))
					cursor = cursor->left;
				else if (_compare(cursor->val.first, val.first) && (var = 2))
					cursor = cursor->right;
				else
					return (ft::make_pair(iterator(cursor), false));
			}
			node_ptr node = new_node(val);
			_size++;
			node->daddy = prev;
			if (var == 1)
				prev->left = node;
			else if (var == 2)
				prev->right = node;
			else
				_root = node;
			is_new_max(val ,node);
			balancing(node->daddy);
			return(ft::make_pair(iterator(node), true));
		}


		size_type erase (const key_type& val)
		{
		node_ptr    current;
		node_ptr    current_daddy;

        int            direction;
		current_daddy = NULL; 

        current = _root;
        direction = 0;
        while (current != NULL)
        {
            if (_compare(val, current->val.first) && (direction = 1))
                current = current->left;
            else if (_compare(current->val.first, val) && (direction = 2))
                current = current->right;
            else
                {
					current_daddy = current->daddy;
					if_del_max(current_daddy, val);
					current = oblitarate(*current, direction);
					balancing(current_daddy);
					return(1);
				}
		}
		return(0);
		}
			


  

		size_type size() const
		{
			return(_root->size(_root));
		}
		node_ptr 	get_root() const
		{
			return(_root);
		}

		size_type	is_key_here(const key_type &val) const
		{
			node_ptr	cursor = _root;

			while (cursor)
			{
				if (_compare(val, cursor->val.first))
					cursor = cursor->left;
				else if (_compare(cursor->val.first, val))
					cursor = cursor->right;
				else
					return (1);
			}
			return(0);

		}
		iterator	found_key(const key_type &val) const
		{
			node_ptr	cursor = _root;

			while (cursor)
			{
				if (_compare(val, cursor->val.first))
					cursor = cursor->left;
				else if (_compare(cursor->val.first, val))
					cursor = cursor->right;
				else
					return(iterator(cursor));
			}
			return(end());//iterator(_real_end));

		}

		size_t	max_size() const
		{
			return _alloc.max_size();
		}
		void	swap(tree &x)
		{

			node_ptr root = x._root;
			node_ptr endi = x._real_end;

			x._root = _root;
			x._real_end = _real_end;

			_root = root;
			_real_end = endi;

		}
	};
template<class Content, class Compare, class Alloc>
bool operator<(const tree<Content, Compare, Alloc>& lhs,  const tree<Content, Compare, Alloc>& rhs){
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}
	template<class Content, class Compare, class Alloc>
bool operator>(const tree<Content, Compare, Alloc>& lhs,  const tree<Content, Compare, Alloc>& rhs){
	return (lhs < rhs);
}

template<class Content, class Compare, class Alloc>
bool operator==(const tree<Content, Compare, Alloc>& lhs, const tree<Content, Compare, Alloc>& rhs){
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}
	
}