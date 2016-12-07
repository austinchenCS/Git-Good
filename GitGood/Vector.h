#ifndef VECTOR
#define VECTOR

#include <iostream>

template<class T>
class Vector{

private:

    // T* that will store an array of the specified data payload
    T* arr;

    // Number of contents in the current vector
    int length;
    // Total capacity of the current vector
    int capacity;

    // Internal resize function
    void resize();

public:

    // No-arg constructor
    Vector();
    // Parametrized constructor that takes an int that is the size
    Vector(int);

    // Copy constructor
    Vector(const Vector<T>&);

    // Overloaded assignment operator
    Vector<T>& operator=(Vector<T>&);

    // Add functions
    void add(T);
    void add(T, int);

    // Remove function
    void remove(T obj);

    // Overloaded equality operator
    bool operator==(Vector<T>&);

    // Sort functions
    void sort();
    void sort(int, int);

    // Get size function
    int size() const;

    // Get capacity function
    int getCap();

    // Remove duplicates function
    void dedupe();

    // Overloaded subscript operator
    T& operator[](int) const;

    // Overloaded "+=" operators
    Vector<T>& operator+=(T);
    Vector<T>& operator+=(Vector<T>);

    // Destructor
    ~Vector();
};

// No-arg constructor
template<class T>
Vector<T>::Vector()
{
    length = 0;
    capacity = 10;
    arr = new T[capacity];
}

// Parametrized constructor that takes an int that is the size
template<class T>
Vector<T>::Vector(int cap)
{
    length = 0;
    this->capacity = cap;
    arr = new T[capacity];
}

// Copy constructor
template<class T>
Vector<T>::Vector(const Vector<T>& otherVector)
{
    this->arr = new T[(otherVector.capacity)];
    this->length = otherVector.length;
    this->capacity = otherVector.capacity;

    for(int i = 0; i < length; i++)
    {
        arr[i] = otherVector.arr[i];
    }

}

// Overloaded assignment operator
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>& otherVector)
{
    //same functionality as copy constructor

    if (this->arr != nullptr)
    {
        delete[] arr;
    }

    this->arr = new T[(otherVector.capacity)];
    this->length = otherVector.length;
    this->capacity = otherVector.capacity;

    for(int i = 0; i < length; i++)
    {
        arr[i] = otherVector.arr[i];
    }

    return *this;

}

// Append at the end "Add" function
template<class T>
void Vector<T>::add(T obj)
{
    if(this->length == this->capacity)
    {
        this->resize();
    }

    this->arr[this->length] = obj;
    this->length++;
}

// Overloaded equality operator
template<class T>
bool Vector<T>::operator==(Vector<T>& rhs)
{
    bool returnOption;

    if ( (arr != nullptr) && (rhs.arr != nullptr) )
    {
        if (length != rhs.length) return false;

        for (int i = 0; i < length; i++)
        {
            if (arr[i] != rhs.arr[i])
            {
                returnOption = false;
            }
        }

        returnOption = true;
    }

    return returnOption;
}

// Add at a specified index "Add" function
template<class T>
void Vector<T>::add(T obj, int indexLocation)
{
    // If no room, resize
    if(length == capacity)
    {
        this->resize();
    }

    // Append to end
    if(indexLocation >= length || indexLocation < 0)
    {
       this->arr[length] = obj;
       length++;
    }

    else
    {
        // Copy previously existing data
        for(int i = length; i > indexLocation; i--)
        {
            arr[i] = arr[i-1];
        }

        this->arr[indexLocation] = obj;
        length++;
    }
}

// No-arg sort function
template<class T>
void Vector<T>::sort()
{
    sort(0, (this->length - 1));
}

// Quicksort implementation
template<class T>
void Vector<T>::sort(int left, int right)
{
    int i = left;
    int j = right;
    T temp;
    T pivot = arr[(left + right) / 2];

    while (i <= j)
    {
        while (arr[i] < pivot)
        {
            i++;
        }

        while (arr[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    };

    if (left < j)
    {
        sort(left, j);
    }

    if (i < right)
    {
        sort(i, right);
    }

}

// Get vector size function
template<class T>
int Vector<T>::size() const
{
    return this->length;
}

// Return vector capacity function
template<class T>
int Vector<T>::getCap()
{
    return this->capacity;
}

// Remove function
template<class T>
void Vector<T>::remove(T obj)
{
    Vector<T> temp;
    if (length == 0)
    {
        return;
    }

    else
    {
        int location = 0;
        bool foundObj = false;

        // Check to see if the object exists at least once in the array
        for (int i = 0; i < this->size(); i++)
        {
            if (arr[i] == obj)
            {
                foundObj = true;
                break;
            }
        }

        if (foundObj)
        {
            for(int i = 0; i < this->size(); i++)
            {
                if (arr[i] != obj)
                {
                    temp.add(arr[i]);
                }
            }
        }

        else
        {
            return;
        }
    }

    this->operator=(temp);
}

// Remove duplicates function
template<class T>
void Vector<T>::dedupe()
{
	Vector<T> temp;
	sort();
	if (length == 0)
	{
		return;
	}

    // Add first value
	else
	{
		temp.add(arr[0]);
	}

	for (int i = 1; i < this->size(); i++)
	{
		if (temp[temp.size() - 1] != arr[i])
		{
			temp.add(arr[i]);
		}
	}

	this->operator=(temp);
}

// Overloaded subscript operator
template<class T>
T& Vector<T>::operator[](int indexLocation) const
{
    return this->arr[indexLocation];
}

// Overloaded "+=" operator
template<class T>
Vector<T>& Vector<T>::operator+=(T obj)
{
    this->add(obj);
    return *this;
}

// Overloaded "+=" operator
template<class T>
Vector<T>& Vector<T>::operator+=(Vector<T> otherVec)
{
    for (int i = 0; i < otherVec.size(); i++)
    {
        this->add(otherVec[i]);
    }

    return *this;
}

// Internal resize function
template<class T>
void Vector<T>::resize()
{
    // Resizes by 1.5 times the current capacity
    this->capacity *= 1.5;
    T* ptr = new T[this->capacity];
    for (int i = 0; i < this->length; i++)
    {
        ptr[i] = this->arr[i];
    }

    delete[] this->arr;
    this->arr = ptr;
}

// Destructor
template<class T>
Vector<T>::~Vector()
{
    if(arr != nullptr)
    {
        delete[] arr;
    }
}

#endif
