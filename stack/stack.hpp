#pragma once
#include "../vector/vector.hpp"
#include <stack>
#include <iostream>


namespace ft
{
    template< class T, class Container = ft::vector<T> > class stack
    {

    public:
        typedef Container   container_type;
        typedef T           value_type;
        typedef size_t      size_type;
    private:
        container_type  _ctnr;
    public:

        explicit stack(const container_type& ctnr = container_type())
        {
            _ctnr = ctnr;
        }

        ~stack()
        {}

        bool                empty() const
        {
            return _ctnr.empty();
        }

        size_type           size() const
        {
            return _ctnr.size();
        }

        value_type&         top()
        {
            return _ctnr.back();
        }
        
        const value_type&   top() const
        {
            return _ctnr.back();
        }

        void                push(const value_type& val)
        {
            _ctnr.push_back(val);
        }
        void                pop()
        {
            _ctnr.pop_back();
        }
    template <class T1, class C1>  
    friend bool operator== (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);
    template <class T1, class C1>  
    friend bool operator!= (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);
    template <class T1, class C1>  
    friend bool operator<  (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);
    template <class T1, class C1>  
    friend bool operator<= (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);
    template <class T1, class C1>  
    friend bool operator>  (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);
    template <class T1, class C1>  
    friend bool operator>= (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);

    };

template <class T1, class C1>  
    bool operator== (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs)
{
    return lhs._ctnr == rhs._ctnr;
}

template <class T1, class C1>    
    bool operator!= (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs)
{
    return lhs._ctnr != rhs._ctnr;
}

template <class T1, class C1>    
    bool operator<  (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs)
{
    return lhs._ctnr < rhs._ctnr;
}

template <class T1, class C1>    
    bool operator<= (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs)
{
    return lhs._ctnr <= rhs._ctnr;
}

template <class T1, class C1>    
    bool operator>  (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs)
{
    return lhs._ctnr > rhs._ctnr;
}

template <class T1, class C1>    
    bool operator>= (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs)
{
    return lhs._ctnr >= rhs._ctnr;
}

//FRIEND IS FOR ACCESS PRIVAITE ELEMENT (LIKE CTNR IN OVERLOAD)

}