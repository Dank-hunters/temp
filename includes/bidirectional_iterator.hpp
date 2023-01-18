#pragma once
#include "../map/node.hpp"
//#include "const_bidirectional_iterator.hpp"
//#include <utility>
namespace ft
{
	template <class T>
	class bidirectional_iterator
	{
	public :
			typedef	T								value_type;
			typedef	T								*pointer;
			typedef	T								&reference;
			typedef	ptrdiff_t						difference_type;
			typedef	iterator_traits<T>				iterator_category;
			typedef bidirectional_iterator<const T>	const_it;
			typedef	Node<T>							elem_type;

			//CONSTRUCTORS
			bidirectional_iterator();
			bidirectional_iterator(const bidirectional_iterator &copy);
			bidirectional_iterator(elem_type *copy);
			~bidirectional_iterator();

			bidirectional_iterator	&operator=(const bidirectional_iterator &copy); // avoir si le dereferencement est gerer

			bool	operator==(const bidirectional_iterator &rhs) const;
			bool	operator!=(const bidirectional_iterator &rhs) const;

			reference	operator*() const;
			pointer		operator->() const;
			bidirectional_iterator	&operator++();
			bidirectional_iterator	operator++(int);

			bidirectional_iterator	&operator--();
			bidirectional_iterator	operator--(int);

	//	private :

			elem_type	*_it;
			pointer		_pair;
	};
	

	template <class T>
	bidirectional_iterator<T>::bidirectional_iterator() : _it(NULL), _pair()
	{

	}

	template <class T>
	bidirectional_iterator<T>::bidirectional_iterator(const bidirectional_iterator &copy) : _it(copy._it), _pair(copy._pair)
	{

	}

	template <class T>
	bidirectional_iterator<T>::bidirectional_iterator(elem_type *copy) : _it(copy), _pair(&copy->val)
	{

	}

	template <class T>
	bidirectional_iterator<T>::~bidirectional_iterator()
	{
		
	}

	template <class T>
	bidirectional_iterator<T> &bidirectional_iterator<T>::operator=(const bidirectional_iterator<T> &copy)
	{
		_it = copy._it;
		_pair = copy._pair;
		return (*this);
	}

	template <class T>
	bool	bidirectional_iterator<T>::operator==(const bidirectional_iterator &rhs) const
	{
		return (&_it->val == rhs.operator->());
	}

	template <class T>
	bool	bidirectional_iterator<T>::operator!=(const bidirectional_iterator &rhs) const
	{
		return (_it != rhs._it);
	}

	template <class T>
	typename bidirectional_iterator<T>::reference	bidirectional_iterator<T>::operator*() const //nop
	{

			return (_it->val);

	}

	template <class T>
	typename bidirectional_iterator<T>::pointer	bidirectional_iterator<T>::operator->() const
	{

		return (&_it->val);
	}

	template <class T>
	bidirectional_iterator<T>	&bidirectional_iterator<T>::operator++() //it++ //nop
	{
		_it = _it->next();
		return (*this);
	}

	template <class T>
	bidirectional_iterator<T>	bidirectional_iterator<T>::operator++(int) //++it //nop
	{


		bidirectional_iterator	tmp = *this;
	
		_it = _it->next();
		return (tmp);
	}

	template <class T>
	bidirectional_iterator<T>	&bidirectional_iterator<T>::operator--() //nop
	{
		_it = _it->prev();
		
		return (*this);
	}

	template <class T>
	bidirectional_iterator<T>	bidirectional_iterator<T>::operator--(int) //nop
	{
		bidirectional_iterator	tmp = *this;
		_it = _it->prev();
		return (tmp);
	}

};

