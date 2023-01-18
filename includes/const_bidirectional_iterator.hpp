#pragma once

#include "bidirectional_iterator.hpp"

//#include <utility>
namespace ft
{
	template < class T>
	class const_bidirectional_iterator 
	{
	public :
			typedef	T								value_type;
			typedef const T								*pointer;
			typedef const T								& reference;
			typedef	ptrdiff_t						difference_type;
			typedef	iterator_traits<T>				iterator_category;
			typedef	Node<T>							elem_type;

			//CONSTRUCTORS
			const_bidirectional_iterator();
			const_bidirectional_iterator(const const_bidirectional_iterator &copy);
			const_bidirectional_iterator(const ft::bidirectional_iterator<T> &copy);
			const_bidirectional_iterator(elem_type *copy);
			~const_bidirectional_iterator();

			const_bidirectional_iterator	&operator=(const const_bidirectional_iterator &copy); // avoir si le dereferencement est gerer

			//bool	operator==(const bidirectional_iterator<T>  &rhs) const;
	friend bool	operator==(const bidirectional_iterator<T> &lhs, const const_bidirectional_iterator &rhs) 
	{
		return (lhs.operator->() == rhs.operator->());
		//return (_pair == rhs.operator->());
	}
	friend bool	operator!=(const bidirectional_iterator<T> &lhs, const const_bidirectional_iterator &rhs) 
	{
		return (lhs._it != rhs._it);
	}
			bool	operator==(const const_bidirectional_iterator &rhs) const;
			bool	operator!=(const const_bidirectional_iterator &rhs) const;

			reference	operator*() const;
			pointer		operator->() const;
			const_bidirectional_iterator	&operator++();
			const_bidirectional_iterator	operator++(int);

			const_bidirectional_iterator	&operator--();
			const_bidirectional_iterator	operator--(int);

		//private :

			elem_type	*_it;
			pointer		_pair;
	};
	

	template <class T>
	const_bidirectional_iterator<T>::const_bidirectional_iterator() : _it(NULL), _pair()
	{

	}

	template <class T>
	const_bidirectional_iterator<T>::const_bidirectional_iterator(const const_bidirectional_iterator &copy) : _it(copy._it), _pair(copy._pair)
	{

	}
    	template <class T>
	const_bidirectional_iterator<T>::const_bidirectional_iterator(const ft::bidirectional_iterator<T> &copy)
    {
         _it = copy._it;
        _pair = copy._pair;
	}

	template <class T>
	const_bidirectional_iterator<T>::const_bidirectional_iterator(elem_type *copy) : _it(copy), _pair(copy->get_pair())
	{

	}

	template <class T>
	const_bidirectional_iterator<T>::~const_bidirectional_iterator()
	{
		
	}

	template <class T>
	const_bidirectional_iterator<T> &const_bidirectional_iterator<T>::operator=(const const_bidirectional_iterator<T> &copy)
	{
		_it = copy._it;
     //   std::cout << "copy" << copy._it->val.second << std::endl;
		_pair = copy._pair;
		return (*this);
	}

	template <class T>
	bool	const_bidirectional_iterator<T>::operator==(const const_bidirectional_iterator &rhs) const
	{
		return (&_it->val == rhs.operator->());
		//return (_pair == rhs.operator->());
	}

	/*template <class T>
	bool	operator==(const const_bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs)
	{
		return (rhs.operator->() == lhs.operator->());
		//return (_pair == rhs.operator->());
	}*/

	template <class T>
	bool	const_bidirectional_iterator<T>::operator!=(const const_bidirectional_iterator &rhs) const
	{
		return (_it != rhs._it);
	}

	template <class T>
	typename const_bidirectional_iterator< T>::reference	const_bidirectional_iterator<T>::operator*() const //nop
	{
		return (_it->val);
	}

	template <class T>
	typename const_bidirectional_iterator< T>::pointer const_bidirectional_iterator<T>::operator->() const
	{
		return (&_it->val);

	}

	template <class T>
	const_bidirectional_iterator<T>	&const_bidirectional_iterator<T>::operator++() //it++ //nop
	{
		_it = _it->next();
		return (*this);
	}

	template <class T>
	const_bidirectional_iterator<T>	const_bidirectional_iterator<T>::operator++(int) //++it //nop
	{

		const_bidirectional_iterator	tmp = *this;
		_it = _it->next();
		return (tmp);
	}

	template <class T>
	const_bidirectional_iterator<T>	&const_bidirectional_iterator<T>::operator--() //nop
	{
		_it = _it->prev();
		return (*this);
	}

	template <class T>
	const_bidirectional_iterator<T>	const_bidirectional_iterator<T>::operator--(int) //nop
	{
		const_bidirectional_iterator	tmp = *this;
		_it = _it->prev();
		return (tmp);
	}

};

