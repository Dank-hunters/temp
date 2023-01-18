#pragma once 

#include "tree.hpp"


namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
	class map
	{
		public:
			typedef Key																		key_type;
			typedef T 																		mapped_type;
			typedef	ft::pair<const key_type, mapped_type>									value_type; //sa mere la pute ca pue sa mere les const
			typedef	ft::pair<key_type, mapped_type>											used_value_type; //sa mere la pute ca pue sa mere les const
			typedef Compare 																key_compare;
			key_compare																		comp;

			class value_compare
			{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				  friend class map<key_type, mapped_type, key_compare, Alloc>;
				protected:
	  				key_compare comp;
	  				value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:

	  				bool operator() (const value_type& x, const value_type& y) const
	 				 {
	 				   return comp(x.first, y.first);
	 				 }
			};

			typedef Alloc																	allocator_type;
			allocator_type	_alloc;

			typedef typename allocator_type::reference										reference;
			typedef typename allocator_type::const_reference            					const_reference;
			typedef typename allocator_type::pointer                    					pointer;
			typedef typename allocator_type::const_pointer              					const_pointer;

			typedef bidirectional_iterator<used_value_type >									iterator;
			typedef const_bidirectional_iterator<used_value_type >									const_iterator;
			typedef reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;

			typedef typename ft::iterator_traits<iterator>::difference_type 				difference_type;
			typedef size_t                                              					size_type;

			typedef	tree<used_value_type, key_compare>								tree_type;
			typedef	Node<used_value_type>								trees_type;
		private:

			tree_type																		Avl;

		public:

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): comp(comp), _alloc(alloc){}

			template <class InputIterator>  
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare() ,const allocator_type& alloc = allocator_type()):  comp(comp), _alloc(alloc)
			{
				insert(first, last);
			}

			map (const map& x): comp(x.comp), _alloc(x._alloc)
			{
				insert(x.begin(), x.end());
			}

			~map()
			{
				clear();
			}

			iterator begin()
			{
				return(Avl.begin());
			}

			const_iterator begin() const
			{
				return(const_iterator(Avl.begin()));
			}

			iterator end()
			{
				return(Avl.end());
			}

			const_iterator end() const
			{
				return(const_iterator(Avl.end()));
			}

			reverse_iterator rbegin()
			{
				iterator	it(Avl.end());
				return(reverse_iterator(it));
			}

			reverse_iterator rend()
			{

				iterator	it(Avl.begin());
				return(reverse_iterator(it));
			}

			trees_type	*get_root()
			{
				return Avl.get_root();
			}

								////////////////////capacity /////////////////////////////
			bool empty() const
			{
				if (Avl.get_root() == NULL)
					return(true);
				return false;
			}

			size_type size() const
			{
				return Avl.size();
			}

			size_type max_size() const
			{
				//return _alloc.max_size();
				return Avl.max_size();
			}

									////////////////// modificateur ///////////////


			template <class InputIterator>  
			void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
			{
				InputIterator tmp = first;

				while(tmp != last)
				{
					Avl.insert(ft::make_pair<key_type, mapped_type>(tmp->first, tmp->second));
					tmp++;
				}
			}

			pair<iterator,bool> insert (const value_type& val)
			{
				return(Avl.insert(val));
			}

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return(insert(val).first);
			}

			size_type erase(const key_type &val)
			{
				return (Avl.erase(val));
			}

			void erase (iterator position)
			{
				Avl.erase(position->first);
			}

			void erase (iterator first, iterator last)
			{
				iterator tmp = first;

				while(first != last)
				{
					first++;
					//if (tmp != end())
						this->erase(tmp);
					//else 
					//	return;
					tmp = first;
				}
			}

			void	clear()
			{
				Avl.clear();
			}


			//////////////////////observer ////////////////////////////

			value_compare value_comp() const 
			{
				return(value_compare(Compare()));
			}

			key_compare key_comp() const
			{
				return (key_compare());
			}

	  		iterator find (const key_type& k)
	  		{
				return(Avl.found_key(k));

	  		}

	  		const_iterator find (const key_type& k) const
			{
				iterator it = Avl.found_key(k);

				return(const_iterator(it));
			}

	  		iterator lower_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (comp((*beg).first, k) == false)
						return(beg);//break;
					beg++;
				}
				return (this->end());
			}

			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
				{
					if (comp((*beg).first, k) == false)
						return(beg);
					beg++;
				}
				return(this->end());
				}


			iterator upper_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (comp(k, (*beg).first))
						return(beg);//break;
					beg++;
				}
				return (this->end());
			}


			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
				{
					if (comp(k, (*beg).first))
						return(beg);//break;
					beg++;
				}
				return (this->end());
			}

			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{ 
				const_iterator f = lower_bound(k);
				const_iterator s = upper_bound(k);
				return (ft::make_pair<const_iterator, const_iterator>(f, s)); 
			}


			ft::pair<iterator,iterator>  
			equal_range (const key_type& k)
			{
				iterator f = lower_bound(k);
				iterator s = upper_bound(k);
				return (ft::make_pair<iterator, iterator>(f, s)); 
			}

			allocator_type get_allocator() const
			{
				return(_alloc);
			}
			size_type count (const key_type& k) const
			{
				return (Avl.is_key_here(k));
			}


			/////////////////////operator

			 map& operator= (const map& x)
			 {
				if (&x == this)
					return *this;
				if (this->empty() == 0)
					this->clear();
				insert(x.begin(), x.end());

				return *this;
			 }
			 mapped_type& operator[] (const key_type& k)
			 {
				iterator i = lower_bound(k);
				if (i == end() || key_comp()(k, (*i).first))
					i = insert(i, value_type(k, mapped_type()));
				return ((*i).second);
			 }

			 //////////////////////swap /////////////////////////

			void swap(map &other)
			{
				Avl.swap(other.Avl);
			}
			 ///////////relational op ////////////////////////////

			 		template<class _Key, class _T, class _Compare, class _Alloc>
			friend bool operator==(const map<_Key, _T, _Compare, _Alloc> & lhs,
					const map<_Key, _T, _Compare, _Alloc>& rhs);

			template<class _Key, class _T, class _Compare, class _Alloc>
			friend bool operator<(const map<_Key, _T, _Compare, _Alloc> & lhs,
					const map<_Key, _T, _Compare, _Alloc>& rhs);

			template <class _Key, class _T, class _Compare, class _Alloc>  
				friend void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y);
	};
			template <class Key, class T, class Compare, class Alloc>  bool operator== ( const map<Key,T,Compare,Alloc>& lhs,                    
			const map<Key,T,Compare,Alloc>& rhs )
			{
				return (lhs.Avl == rhs.Avl);
			}
			template <class Key, class T, class Compare, class Alloc>  bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,                    
			const map<Key,T,Compare,Alloc>& rhs )
			{
					return !(lhs == rhs);

			}
			template <class Key, class T, class Compare, class Alloc>  bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,                    
			const map<Key,T,Compare,Alloc>& rhs )
			{
					return (lhs.Avl < rhs.Avl);

			}
			template <class Key, class T, class Compare, class Alloc>  bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,                    
			const map<Key,T,Compare,Alloc>& rhs )
			{
					return !(lhs > rhs);

			}
			template <class Key, class T, class Compare, class Alloc>  bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,                    
			const map<Key,T,Compare,Alloc>& rhs )
			{
					return (rhs < lhs);

			}
			template <class Key, class T, class Compare, class Alloc>  bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,                    
			const map<Key,T,Compare,Alloc>& rhs )
			{
					return !(lhs < rhs);

			}

			template <class Key, class T, class Compare, class Alloc>  
			void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
			{
				x.swap(y);
			}
}
