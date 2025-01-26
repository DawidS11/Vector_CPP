#include <iostream>
#include <string>
#include <optional>

template <typename T>
class Vector
{
private:
    T* arr;
    int capacity;
    int num_elements;

public:
    Vector()
    : capacity(1), num_elements(0)
    {
        arr = new T[1];
    }

    ~Vector()
    {
        delete[] arr;
    }

    void reserve(int new_capacity)
    {
        if (capacity < new_capacity)
        {
            capacity = new_capacity;
            T* tmp = new T[capacity];

            for (int i = 0; i < capacity; ++i)
            {
                tmp[i] = arr[i];
            }
            delete[] arr;
            arr = tmp;
        }
        else
        {
            std::cout << "reserve(): New capacity is not greater than the current one. No changes have been made." << std::endl;
        }
    }

    void push_back(const T& data)
    {
        if (num_elements == capacity)
        {
            reserve(capacity * 2);
        }
        arr[num_elements++] = data;
    }

    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        if (num_elements == capacity)
        {
            reserve(capacity * 2);
        }
        new (&arr[num_elements++]) T(std::forward<Args>(args)...);
    }

    T& front()
    {
        if (num_elements > 0)
        {
            return arr[0];
        }
        else
        {
            throw std::runtime_error("front(): The vector is empty.");
        }
    }

    T& back()
    {
        if (num_elements > 0)
        {
            return arr[num_elements-1];
        }
        else
        {
            throw std::runtime_error("back(): The vector is empty.");
        }
    }

    T get(int index)
    {
        if (index < num_elements)
        {
            return arr[index];   
        }
        else
        {
            std::cout << "get(): Index is not within range." << std::endl;
        }
    }

    void pop_back()
    {
        if (num_elements > 0)
        {
            --num_elements;
            arr[num_elements].~T();
        }
        else
        {
            throw std::runtime_error("pop_back(): The vector is empty.");
        }
    }

    int size()
    {
        return num_elements;
    }

    bool empty()
    {
        return num_elements == 0;
    }

    int get_capacity()
    {
        return capacity;
    }

    T& operator[](int index)
    {
        if (index >= num_elements) {
            throw std::out_of_range("[]: Index out of range");
        }
        return arr[index];
    }

    const T& operator[](int index) const
    {
        if (index >= num_elements) {
            throw std::out_of_range("[]: Index out of range");
        }
        return arr[index];
    }

    void print() const
    {
        for (int i = 0; i < num_elements; ++i)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    class Iterator 
    {
    private:
        T* ptr_;
    public:
        Iterator(T* ptr)
        : ptr_(ptr)
        {}

        // Dereferencing operator
        T& operator*() { return *ptr_; }
        const T& operator*() const { return *ptr_; }

        // Pointer dereference operator
        T* operator->() { return ptr_; }
        const T* operator->() const { return ptr_; }

        Iterator& operator++() { ++ptr_; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++ptr_; return tmp; }

        Iterator& operator--() { --ptr_; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --ptr_; return tmp; }

        bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }
    };

    Iterator begin() { return Iterator(arr); }
    Iterator end() { return Iterator(arr + num_elements); }
};