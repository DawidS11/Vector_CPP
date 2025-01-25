#include <iostream>

template <typename T>
class Vector
{
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
            T tmp = new T[capacity];

            for (int i = 0; i < capacity; ++i)
            {
                tmp[i] = arr[i];
            }
            delete[] arr;
            arr = tmp;
        }
        else
        {
            std::cout << "New capacity is not greater than the current one. No changes have been made." << std::endl;
        }
    }

    void push_back(T data)
    {
        if (num_elements == capacity)
        {
            reserve(capacity * 2);
        }
        arr[num_elements++] = data;
    }

    T pop_back()
    {
        if (num_elements > 0)
        {
            return arr[--num_elements];
        }
        else
        {
            std::cout << "The vector is empty." << std::endl;
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
            std::cout << "Index is not within range." << std::endl;
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

    void print()
    {
        for (T el : arr)
        {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }

private:
    T* arr;
    int capacity;
    int num_elements;
};

int main()
{
    std::cout << "Hello world!" << std::endl;
}