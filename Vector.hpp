#include <iostream>
#include <string>
#include <optional>

template <typename T>
class Vector
{
private:
    T* arr;
    int capacity;
    int size;

    void grow()
    {
        capacity = capacity == 0 ? 1 : capacity * 2;
        T* tmp = new T[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            tmp[i] = arr[i];
        }
        delete[] arr;
        arr = tmp;
    }

public:
    Vector()
        : arr(new T[0]), capacity(0), size(0)
    {}

    Vector(int n)
	    : arr(new T[n]), capacity(n), size(n)
    {
        for (int i = 0; i < n; ++i)
        {
            arr[i] = T();
        }
    }

    explicit Vector(const Vector& other)
        : arr(new T[other.size]), capacity(other.capacity), size(other.size)
    {
        for (int i = 0; i < other.size; ++i)
        {
            arr[i] = other.arr[i];
        }
    }

    explicit Vector(Vector&& other) noexcept
        : arr(other.arr), capacity(other.capacity), size(other.size)
    {
        other.arr = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    ~Vector()
    {
        delete[] arr;
    }

    void reserve(int new_capacity)
    {
        if (capacity < new_capacity)
        {
            T* tmp = new T[new_capacity];
            for (int i = 0; i < capacity; ++i)
            {
                tmp[i] = arr[i];
            }
            capacity = new_capacity;
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
        if (size == capacity)
        {
            grow();
        }
        arr[size++] = data;
    }

    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        if (size == capacity)
        {
            grow();
        }
        new (&arr[size++]) T(std::forward<Args>(args)...);
    }

    T& front()
    {
        if (size > 0)
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
        if (size > 0)
        {
            return arr[size-1];
        }
        else
        {
            throw std::runtime_error("back(): The vector is empty.");
        }
    }

    T& get(int index)
    {
        if (index < size)
        {
            return arr[index];   
        }
        else
        {
            throw std::runtime_error("get(): Index is not within range.");
        }
    }

    void pop_back()
    {
        if (size > 0)
        {
            --size;
            arr[size].~T();
        }
        else
        {
            throw std::runtime_error("pop_back(): The vector is empty.");
        }
    }

    bool empty()
    {
        return size == 0;
    }

    int get_size()
    {
        return size;
    }

    int get_capacity()
    {
        return capacity;
    }

    T& operator[](int index)
    {
        if (index >= size) {
            throw std::out_of_range("[]: Index out of range");
        }
        return arr[index];
    }

    const T& operator[](int index) const
    {
        if (index >= size) {
            throw std::out_of_range("[]: Index out of range");
        }
        return arr[index];
    }

    void print() const
    {
        for (int i = 0; i < size; ++i)
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
    Iterator end() { return Iterator(arr + size); }
};