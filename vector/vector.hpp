#pragma once 
#include <vector>
#include <iostream>
#include <iterator>
#include <limits>
#include "../includes/random_acces_iterator.hpp"
#include "../includes/enable_if.hpp"
#include "../includes/compare.hpp"
#include "../includes/reverse_iterator.hpp"
namespace ft
{
	template < class T, class Alloc = std::allocator<T> > 
		class vector
		{
			public:

				typedef T                                                   										value_type;
				typedef Alloc                                               										allocator_type;

				typedef typename allocator_type::reference                  										reference;
				typedef typename allocator_type::const_reference            										const_reference;
				typedef typename allocator_type::pointer                    										pointer;
				typedef typename allocator_type::const_pointer              										const_pointer;

				typedef  ft::random_access_iterator<value_type, value_type&, value_type*>							iterator;
				typedef  ft::random_access_iterator<const value_type, const value_type&, const value_type*> 		const_iterator;
				typedef  ft::reverse_iterator<iterator>                     										reverse_iterator;    
				typedef  ft::reverse_iterator<const_iterator>               										const_reverse_iterator;

				typedef size_t                                              										size_type;
				typedef typename ft::iterator_traits<iterator>::difference_type 									difference_type;
			private:
				allocator_type  _alloc;
				pointer         _end;
				pointer         _start;
				pointer         _end_of_storage;

				void    del_storage(size_type n)
				{
					size_type i = 0;

					while (i < n && _end >= _start)
					{
						if (_end == _start)
							_alloc.destroy(_start);
						else
							_alloc.destroy(--_end);	
						++i;
					}
				}

				void    set_new_block(size_type n, const value_type& val)
				{
					size_t i = 0;
					if (_end == _start)
					{
						_alloc.construct(_end++, val);
						++i;
					}
					while ( i < n && (_end) < _end_of_storage)
					{
						_alloc.construct(_end++, val);
						i++;
					}
				}

				template <class Itt>
					void    set_new_range(Itt first, Itt last)
					{
						while (first != last)
						{
							_alloc.construct(_end++, (*first++));
						}
					}


				void    delete_block(pointer _del, size_t n)
				{
					if (_start)
					{
						for (size_t i = 0; i < n; i++)
						{
							_alloc.destroy(&_del[i]);
						}
						_alloc.deallocate(_del, n);
					}
				}

				void	clear_memory(size_type n)
				{
					size_type i = 0;
					while (i < n && _end >= _start)
					{
						if (_end == _start)
							_alloc.destroy(_start);
						else 
							_alloc.destroy(--_end);
						i++;
					}
				}

				void    add_memory(size_type n)
				{
					pointer tmp = _alloc.allocate(n);
					iterator start = begin();
					size_type      i = 0;
					size_type sized = size();

					_end = tmp;
					while(i != sized)
					{
						_alloc.construct(_end++, *start++);
						i++;
					}
					_end_of_storage = _end;
					while ( i < n)
					{
						++_end_of_storage;
						i++;
					}
					pointer cpy = _start;
					_start = tmp;
					delete_block(cpy, sized);
				}

				iterator remove_block(iterator first, iterator last)
				{
							iterator tmp = first;

					if (first == last)
						return (first);
					while (tmp != last)
					{
						_alloc.destroy(&(*tmp));
						tmp++;
						_end--;
					}
					tmp = first;
					size_type i = 0;
					while(tmp != _end)
					{
						_alloc.construct(&(*tmp), *(last + i));
						_alloc.destroy(&(*(last + i)));
						tmp++;
						i++;
					}
					return(first);
				}
			public :

				//                      constructeur/destructeur

				explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc) , _end(NULL), _start(NULL), _end_of_storage(NULL)
			    {}

				explicit vector (size_type n, 
						const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) :_alloc(alloc) , _end(NULL), _start(NULL), _end_of_storage(NULL)
			    {   
				    assign(n, val);
			    }

				template <class Itt>         
					vector (Itt first, Itt last, 
							const allocator_type& alloc = allocator_type()) : _alloc(alloc) , _end(NULL), _start(NULL), _end_of_storage(NULL)
			    {
				    assign(first, last);
			    }

				vector (const vector& x) :  _alloc(x._alloc), _end(NULL), _start(NULL), _end_of_storage(NULL)
			    {
				    *this = x;
			    }

				~vector()
				{
					if (_start)
					{
						delete_block(_start, size());
					}
				}

				vector& operator= (const vector& x)
				{
					clear();

					if (capacity() > x.capacity())
						insert(begin(), x.begin(), x.end());
					else
						assign(x.begin(), x.end());
					return (*this);
				}

				//                      Iterator                
				iterator begin()
				{
					return iterator(_start);
				}
				const_iterator begin() const
				{
					return const_iterator(_start);
				}
				reverse_iterator rbegin()
				{
					iterator i = end();
					return reverse_iterator(i);
				}
				const_reverse_iterator rbegin() const
				{
					const_iterator i = end();
					return const_reverse_iterator(i);
				}

				iterator end()
				{
					return iterator(_end);
				}
				const_iterator end() const
				{
					return const_iterator(_end);
				}
				reverse_iterator rend()
				{
					iterator i = begin();
					return reverse_iterator(i);
				}
				const_reverse_iterator rend() const
				{
					const_iterator i = begin();
					return const_reverse_iterator(i);
				}
				//      Capacity
				
                size_type capacity(void) const 
                {
                     return static_cast<size_type>(_end_of_storage - _start);
                }
				size_type size(void) const 
                {
                     return static_cast<size_type>(_end - _start); 
                }
				size_type max_size() const
				{
					return std::numeric_limits<size_type>::max() / sizeof(T); 	
					//return std::numeric_limits<difference_type>::max() / sizeof(T); 	
				}
				bool empty() const
				{
					return (_start == _end);
				}
				void reserve (size_type n)
				{
					if (n > capacity())
					add_memory(n);
				}
				void resize (size_type n, value_type val = value_type())
				{
					if (n == size())
						return;
					if (n < size())
						del_storage(size() - n);
					else if (n > size())
					{
						if (n > capacity())
						{
							if (capacity() * 2 < n)
								add_memory(n);
							else
								add_memory(capacity() * 2);
							set_new_block(n - size(), val);
						}
						else
							set_new_block(n - size(), val);
					}
				}
				//      Modifier

				template <class InputIterator>
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
					assign (InputIterator first, InputIterator last)
					{
						size_type n = 0;
						for (InputIterator itf = first; itf != last; itf++)
						{
							n++;
							// dprintf(1, "%zu\n", n);
						}
						if (n > capacity())
						{
							clear_memory(size());
							_start = _alloc.allocate(n);
							_end = _start;
							_end_of_storage = _end;
							size_type m = n;
							while (m != 0)
							{
								++_end_of_storage;
								--m;
							}
						}
						else
							del_storage(size());
						set_new_range(first, last);
					}

				void assign (size_type n, const value_type& val)
				{
					if (n == 0)
						return;
					if (n > capacity())
					{
						delete_block(_start, size());
						_start = _alloc.allocate(n);
						_end = _start;
						_end_of_storage = _end;
						size_type m = n;
						while (m != 0)
						{
							++_end_of_storage;
							--m;
						}
					}
					else
						del_storage(size());
					set_new_block(n, val);
				}

				void push_back (const value_type& val)
				{
					if (size() + 1 > capacity())
					{
						if (!(capacity()))
							add_memory(1);
						else
							add_memory(capacity() * 2);
					}
					set_new_block(1, val);
				}

				void pop_back()
				{
					del_storage(1);
				}

				void clear()
				{
					clear_memory(size());
				}

				iterator erase (iterator position)
				{
					
					return (remove_block(position, position + 1));
				}
				iterator erase (iterator first, iterator last)
				{	
					return (remove_block(first, last));
				}
				
				iterator insert (iterator position, const value_type& val)
    			{
						iterator	it;
						size_type	index;

						index = position - this->begin();
						this->insert(position, 1, val);
						return iterator(this->begin() + index);
				
				}

				void insert (iterator position, size_type n, const value_type& val)
				{
					size_type _n = position - begin();
					if (capacity() < size() + n)
					{
						if (capacity() == 0)
							reserve(n);
						else 
						{
							if ((capacity() * 2) < capacity() + n)
								{
									reserve(((capacity() *2) + n));
								}
							else 	
								reserve(capacity()*2);
						}
					}
					iterator tmp = end() - 1;
					while(tmp >= begin() + _n)
					{
						_alloc.construct(&(*(tmp + n)), *(tmp));
						_alloc.destroy(&(*(tmp)));
						tmp--;
					}
					tmp++;
					for (size_t i = 0; i < n; i++)
					{
						_alloc.construct(&(*tmp), val);
						tmp++;
					}
					_end += n;
				}

		template <class InputIterator>
			typename enable_if<!ft::is_integral<InputIterator>::value, void>::type insert (iterator position, InputIterator first, InputIterator last)
				{		
					InputIterator tmps = first;
					size_type n = 0;
					while(tmps != last)
					{
						n++;
						tmps++;
					}
					size_type _n = &(*position) - _start;
					if (capacity() < size() + n)
					{
						if (capacity() == 0)
							reserve(n);
						else 
						{
							if ((capacity() * 2) < (capacity() + n))
								{
									reserve(((capacity() *2) + n));
								}
							else 	
							{
								reserve(capacity()*2);
							}
						}
					}
					iterator tmp = _end - 1;
					while(tmp >= iterator(_start + _n))
					{
						_alloc.construct(&(*(tmp + n)), *(tmp));
						_alloc.destroy(&(*(tmp)));
						tmp--;
					}
					tmp++;
					for (size_t i = 0; i < n; i++)
					{
						_alloc.construct(&(*tmp), *first);
						tmp++;
					first++;
					}
					_end += n;
				}

				void swap (vector& x)
				{
				pointer         tmp_end = x._end;
				pointer         tmp_start = x._start;
				pointer         tmp_end_of_storage = x._end_of_storage;
				
				x._end = _end;
				x._end_of_storage = _end_of_storage;
				x._start = _start;

				_end = tmp_end;
				_end_of_storage = tmp_end_of_storage;
				_start = tmp_start;
				}
				// acces operator

				reference operator[] (size_type n)
				{
					if (n >= size())
						throw std::out_of_range("vector");
					return _start[n];
				}
				
				const_reference operator[] (size_type n) const
				{
					if (n >= size())
						throw std::out_of_range("vector");
					return _start[n];
				}

				reference at (size_type n)
				{
					if (n >= size())
						throw std::out_of_range("vector");
					return _start[n];

				}
				const_reference at (size_type n) const
				{
					if (n >= size())
						throw std::out_of_range("vector");
					return _start[n];
				}
				reference front()
				{
					return *_start;
				}
				
				const_reference front() const
				{
					return *_start;
				}
				reference back()
				{
					return *(_end - 1);
				}
				const_reference back() const
				{
					return *(_end - 1);
				}

				allocator_type get_allocator() const
				{
					return (_alloc);
				}

		};

		template <class T, class Alloc>  
			bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return(false);
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			}
		template <class T, class Alloc>  
			bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(lhs == rhs);
			}
		template <class T, class Alloc>  
			bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}
		template <class T, class Alloc>  
			bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(rhs < lhs);
			}
		template <class T, class Alloc>  
			bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return rhs < lhs;
			}
		template <class T, class Alloc>  
			bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(lhs < rhs);
			}

}
