#pragma once
#include <iterator>
#include "iterator_traits.hpp"

namespace ft
{
        template < class _T, class Ref, class Pointer >
        class random_access_iterator
        {
        public:
                typedef _T value_type;
                typedef _T *pointer;
                typedef _T &reference;
                typedef ptrdiff_t difference_type;
                typedef ft::iterator_traits<_T> iterator_category;
                typedef random_access_iterator<const _T, const _T&, const _T*> _const;
        private:
                pointer _it;
        public:
                random_access_iterator() : _it(NULL) {}
                random_access_iterator(pointer ptr) : _it(ptr) {}
                random_access_iterator(const random_access_iterator &copy) : _it(copy._it) {}
                ~random_access_iterator() {}

                random_access_iterator &operator=(const random_access_iterator &copy)
                {
                        _it = copy._it;
                        return *this;
                }
                operator _const() const { return _const(_it);}


                pointer operator->() const { return _it; }
                reference operator*() const { return *_it; }

                bool operator==(const _const &it) const { return _it == it.operator->(); }
                bool operator!=(const _const &it) const { return _it != it.operator->(); }

                bool operator<(const _const &it) const { return _it < it.operator->(); }
                bool operator>(const _const &it) const { return _it > it.operator->(); }
                bool operator<=(const _const &it) const { return _it <= it.operator->(); }
                bool operator>=(const _const &it) const { return _it >= it.operator->(); }

                random_access_iterator &operator++()
                {
                        ++_it;
                        return *this;
                }

                random_access_iterator operator++(int)
                {
                        random_access_iterator tmp(*this);
                        ++_it;
                        return tmp;
                }

                random_access_iterator &operator--()
                {
                        --_it;
                        return *this;
                }

                random_access_iterator operator--(int)
                {
                        random_access_iterator tmp(*this);
                        --_it;
                        return tmp;
                }

                random_access_iterator operator+(const difference_type &n) const
                {
                        return random_access_iterator(_it + n);
                };
               /* difference_type operator+(const random_access_iterator &it)
                {
                        return _it + it.operator->();
                };*/
	        friend random_access_iterator operator+(const difference_type n, const random_access_iterator &x) { return random_access_iterator(x._it + n); }
                //patch du cpp 98 pour pouvoir comparer des const et des non const, pas inscrit dans la 98 mais explicitement reparer par les devs

                difference_type	operator - (const _const &other) const
		{
			return _it - other.operator->();
		}

                random_access_iterator operator-(const difference_type &n) const
                {
                        return random_access_iterator(_it - n);
                };
                random_access_iterator &operator+=(difference_type n)
                {
                        _it += n;
                        return *this;
                }
                random_access_iterator &operator-=(difference_type n)
                {
                        _it -= n;
                        return *this;
                }
                reference operator[](difference_type n) const
                {
                        return _it[n];
                };

        };
      /*  template < class _T>
        bool operator!=(const random_access_iterator<_T, _T&, _T*> &lhs, const random_access_iterator<_T, _T&, _T*> &rhs) { return lhs != rhs; }*/
}