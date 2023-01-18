#pragma once
#include "iterator_traits.hpp"

namespace ft
{
template<typename _Iterator>
    class reverse_iterator
    {
        public:
   
    typedef _Iterator                                      iterator_type;
    typedef ft::iterator_traits<_Iterator>                     __traits_type;
    typedef typename __traits_type::difference_type        difference_type;
    typedef typename __traits_type::pointer                pointer;
    typedef typename __traits_type::reference              reference;
    typedef typename  __traits_type::iterator_category     iterator_category;
    private:
    iterator_type                                              current;
    public:
    

    reverse_iterator() : current() { }
    
    reverse_iterator(iterator_type _x) : current(_x) { }

    template<typename _Iter>
    reverse_iterator<_Iterator>(const reverse_iterator<_Iter>& _x)
    { 
        *this = _x;
    }
     
   	template < class U >
 			reverse_iterator <_Iterator>& operator=(const reverse_iterator< U >& u)
			{
				current = u.base();
				return *this;
			}

    iterator_type  base() const
        {
            return current; 
        }
    
    reference operator*() const 
        { 
            _Iterator _tmp = current;
            return *--_tmp;
        }
    
    pointer operator->() const
        {
            return &(operator*());
        }

    reverse_iterator& operator++()
        {
            --current;
            return *this;
        }
    reverse_iterator operator++(int)
        {
            reverse_iterator _tmp = *this;
            --current;
            return _tmp;
        }
    reverse_iterator& operator--()
        {
            ++current;
            return *this;
        }
    
    reverse_iterator operator--(int)
        {
            reverse_iterator _tmp = *this;
            ++current;
            return _tmp;
        }
    
    reverse_iterator operator+(difference_type _n) const 
        {
            return reverse_iterator(current - _n);
        }    
    
    reverse_iterator& operator+=(difference_type _n)
        {
            current -= _n;
            return *this;
        }
    
    reverse_iterator operator-(const difference_type _n) const 
        {
            return reverse_iterator(current + _n);
        }
    
    
    reverse_iterator& operator-=(difference_type _n)
        {
            current += _n;
            return *this;
        }
    
    reference operator[](difference_type _n) const 
        {
            return *(*this + _n);
        }
    
};
    template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
	{
		return reverse_iterator<Iterator>(it.base() - n);
	} 
    template <class Iterator, class two>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<two>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

/*template<class _Iterator, class _It>
    bool operator==(const reverse_iterator<_Iterator>& _x,
               const reverse_iterator<_It>& _y) 
    { return _x.base() == _y.base(); }
*/
  template <class A, class B> bool operator<(const reverse_iterator<A> &_x, const reverse_iterator<B> &_y)
    { return _x.base() > (_y.base());}
template <class A, class B> bool operator<=(const reverse_iterator<A> &_x, const reverse_iterator<B> &_y)
    { return (_x.base() >= (_y.base()));}



template <class A, class B> bool operator==(const reverse_iterator<A> &lhs, const reverse_iterator<B> &rhs) { return lhs.base()== (rhs.base()); };
/*
template <class A> bool operator==(const reverse_iterator<A> &lhs, const reverse_iterator<A> &rhs)
{ return lhs.base() == rhs.base(); };
*/
/*
template <class A> bool operator!=(const reverse_iterator<A> &lhs, const reverse_iterator<A> &rhs) 
{ return lhs.base()!= (rhs.base()); };
  */
 	template <class A, class B> bool operator!=(const reverse_iterator<A> &lhs, const reverse_iterator<B> &rhs) { return lhs.base()!= (rhs.base()); };
 /* template<class _Iterator>
    bool operator!=(const reverse_iterator<_Iterator>& _x,
               const reverse_iterator<_Iterator>& _y)
    { return !(_x == _y); }*/

template <class A, class B> bool operator>(const reverse_iterator<A> &_x, const reverse_iterator<B> &_y)
    { return _x.base() < (_y.base()); }


template <class A, class B> bool operator>=(const reverse_iterator<A> &_x, const reverse_iterator<B> &_y)
    { return (_x.base() <= (_y.base())); }
};
