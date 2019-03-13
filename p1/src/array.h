#pragma once

#include <iostream>

//students should not change this

using size_t = std::size_t;

template<typename T> class array_iterator;

template<typename T>
class array {
public:
    //default constructor
    array() : m_size(0), m_reserved_size(0), m_elements(nullptr) {}
    
    //initialize array with elements in initializer
    array(std::initializer_list<T> list) : m_size(list.size()), m_reserved_size(list.size())
    {   
        //Alocate space for the new array elements, then copy them over from the init_list
        m_elements = (T*)calloc(m_reserved_size, sizeof(T));
        auto it = list.begin();
        for (u_int i = 0; i < m_size; i++)
            new (m_elements + i) T(*(it + i));  
    }

    //copy constructor
    array(const array& cpy): m_size(cpy.m_size), m_reserved_size(cpy.m_reserved_size)
    {
        //Alocate space for the array and copy the elements
        m_elements = (T*)calloc(cpy.m_reserved_size, sizeof(T));
        for (u_int i = 0; i < m_size; i++)
            new (m_elements + i) T(cpy[i]);    
    }

    //move constructor
    array(array&& rval) : m_size(rval.m_size), m_reserved_size(rval.m_reserved_size)
    {
        m_elements = rval.m_elements;
        rval.m_elements = nullptr;
    }

    //construct with initial "reserved" size
    array(size_t n) : m_size(0), m_reserved_size(n) {m_elements = (T*)calloc(m_reserved_size, sizeof(T));}

    //construct with n copies of t
    array(size_t n, const T& t) : m_size(n), m_reserved_size(n)
    {
        m_elements = (T*)calloc(m_reserved_size, sizeof(T));
        for (u_int i = 0; i < m_size; i++)
            new (m_elements+i) T(t);
    }

    //destructor
    ~array()
    {
        //Call the destructor for all elements in the array then free up the space
        if (m_elements != nullptr) {
            for (int i = 0; i < m_size; i++) {
                (*(m_elements + i)).~T();
            }
            free (m_elements);
        }
    }

    //ensure enough memory for n elements
    void reserve(size_t n)
    {
         if (n > m_reserved_size) {
            //Set the new size, allocate new space for the array (according to updated reserved space)
            m_reserved_size = n;
            T* tmp = m_elements;
            m_elements = (T*)calloc(n, sizeof(T));
            //Move construct over all the elements then free up the old space
            for (u_int i = 0; i < m_size; i++) {
                new (m_elements + i) T(std::move(*(tmp+i)));
                (*(tmp + i)).~T();
            } 
            free(tmp);
        }
    }

    //add to end of vector
    void push_back(const T& t) 
    {
        //Make sure theres enough space, copy the element to the end of the array, increment size
        if (m_reserved_size == 0) {
            reserve(1);
        } else if (m_size == m_reserved_size) {
            reserve(m_reserved_size * 2);
        }
        new (m_elements + m_size ) T(t);
        ++m_size;
    }

    //add to front of vector
    void push_front(const T& t)
    {
        // if the array is empty, reserve space for on
        if (m_size == 0) {
            reserve(1);     
        } else if (m_size == m_reserved_size) {
            //Double the size, allocate new space for the array
            m_reserved_size *= 2;
            T* tmp = m_elements;
            m_elements = (T*)calloc(m_reserved_size, sizeof(T));
            //move construct everything over shifted down one, free up old space
            for (u_int i = 0; i < m_size; i++) {
                new (m_elements + i + 1) T(std::move(*(tmp+i)));
                (*(tmp + i)).~T();
            } 
            free(tmp);
        } else { 
            //Move construct (shift) the last element
            new (m_elements + m_size ) T(std::move(*(m_elements + m_size - 1)));  
            (*(m_elements + m_size - 1)).~T();
            //Move assign (shift) the rest
            for (u_int i = m_size - 1; i > 0; i--) 
                *(m_elements + i) = std::move(*(m_elements + i - 1));  
        }
        //Copy construct the new element on the front, increment size
        new (m_elements) T(t);
        ++m_size;       
    }

    //remove last element
    void pop_back()
    {
        //Destruct the last element and decrement the size
        (*(m_elements + m_size - 1)).~T();
        --m_size;
    }

    //remove first element
    void pop_front()
    {   
        --m_size;
        for (u_int i = 0; i < m_size; i++)
            *(m_elements + i) = std::move(*(m_elements + i + 1));
        (*(m_elements + m_size - 1)).~T();
    }

    //return reference to first element
    T& front() const {return *m_elements;}

    //return reference to last element
    T& back() const {return *(m_elements + m_size - 1);}

    //return reference to specified element
    const T& operator[](size_t n) const {return *(m_elements + n);}

    //return reference to specified element
    T& operator[](size_t n) {return *(m_elements + n);}

    //return number of elements
    size_t length() const {return m_size;}

    //returns true if empty
    bool empty() const
    {
        if (m_size == 0)
            return true;

        return false;
    }

    //remove all elements
    void clear()
    {
        //Destruct all objects in the array, set size to 0
        for (u_int i = 0; i < m_size; i++)
            (*(m_elements + i)).~T();
        m_size = 0;
    }

    //obtain iterator to first element
    array_iterator<T> begin() const {return array_iterator<T>(m_elements);}

    //obtain iterator to one beyond element
    array_iterator<T> end() const {return array_iterator<T>(m_elements + m_size);}

    //remove specified element
    void erase(const array_iterator<T>& it)
    {
        if (it.m_current == m_elements) {
            pop_front();
        } else if (it.m_current == (m_elements + m_size - 1)) {
            pop_back();
        } else {
            (*(it.m_current)).~T();
            int i = 0;
            while (it.m_current + i != m_elements + m_size - 1) {
                *(it.m_current + i) = std::move(*(it.m_current + i + 1));
                ++i;
            }
            //(*(it.m_current + i)).~T();
            --m_size;
        }
    }

    //insert element right before itr
    void insert(const T& t, const array_iterator<T>& it)                                                  //Works
    {
        //Find the index of the iterator (resizing the array trashes the iterator)
        u_int i;
        for (i = 0; i < m_size; i++) {
            if (m_elements + i == it.m_current)
                break;
        }

        //if the size is 0, reserve space for one
        if (m_size == 0) {
            reserve(1);
            new (m_elements) T(t);
            ++m_size;
        //If more space is needed, double the reserve size
        //Go ahead and shift down one when copying to the new space
        } else if (m_size == m_reserved_size) {
            //Double the size, allocate new space for the array
            m_reserved_size *= 2;
            T* tmp = m_elements;
            m_elements = (T*)calloc(m_reserved_size, sizeof(T));
            for (u_int j = 0; j < m_size; j++) {
                if (j < i) {
                    new (m_elements + j) T(std::move(*(tmp + j)));
                } else {
                    new (m_elements + j + 1) T(std::move(*(tmp+j)));
                }
                (*(tmp + j)).~T();
            } 

            free(tmp);
            new (m_elements + i) T(t);
            ++m_size;
        //Otherwise shift down everything after the iterator index
        } else {
            //Move construct (shift) the last element
            new (m_elements + m_size ) T(std::move(*(m_elements + m_size - 1)));  
            (*(m_elements + m_size - 1)).~T();
            //Move assign (shift) the rest
            for (u_int j = m_size - 1; j > i; j--) 
                *(m_elements + j) = std::move(*(m_elements + j - 1));  
            
            new (m_elements + i) T(t);
            ++m_size;    
        }
    }

private:
    T* m_elements;              //points to actual elements
    size_t m_size;              //number of elements
    size_t m_reserved_size;     //number of reserved elements
};

template<typename T>
class array_iterator {
public:
    array_iterator() : m_current(nullptr) {}       //Default constructor                                    Works

    array_iterator(T* t) : m_current(t) {}      //Constructor that points to specified object               Works

    array_iterator(const array_iterator& it) : m_current(it.m_current) {}    //Copy constructor              Works

    T& operator*() const {return *(m_current);}

    array_iterator operator++()                                                                             //Works
    {
        m_current++;
        return *this;
    }

    array_iterator operator++(int __unused)                                                                 //Works
    {
        array_iterator tmp(*this);
        operator++();
        return tmp;
    }

    bool operator != (const array_iterator& it) const                                                       //Works
    {
        if (m_current != it.m_current)
            return true;

        return false;
    }

    bool operator == (const array_iterator& it) const                                                       //Works
    {
        if (m_current == it.m_current)
            return true;
 
        return false;
    }

private:
    T* m_current;
    // I want my array class to be able to access m_current even though it's private
    // 'friend' allows this to happen
    friend class array<T>;
};