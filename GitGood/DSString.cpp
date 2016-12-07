#include "DSString.h"

using namespace std;

// Default constructor
String::String()
{
    charArray = nullptr;
    sizeOf = 0;
}

// Parametrized constructor that takes a char*
String::String(const char* incomingArray)
{
    int count = 0;
    // Create copy of pointer for the count
    const char* ptr = incomingArray;

    // Iterate over char array to determine length
    while(*ptr++)
    {
        count++;
    }

    // Create char array
    charArray = new char[count + 1];
    sizeOf = count;

    // Iterate over original char array -> assign to destination array
    for(int i = 0; i < count + 1; i++)
    {
        charArray[i] = incomingArray[i];
    }

    // Ensure final char value in array is a null terminator
    charArray[count] = '\0';

    return;
}

// Copy constructor
String::String(const String& incomingString)
{
    int count = 0;

    // Create copy of pointer for the count
    const char* ptr = incomingString.c_str();
    while(*ptr++)
    {
        count++;
    }

    // Create char array
    charArray = new char[count + 1];
    sizeOf = count;

    // Iterate over original char array from String object
    // -> assign to destination array
    for(int i = 0; i < count + 1; i++)
    {
        charArray[i] = incomingString.c_str()[i];
    }

    // Ensure final char value in array is null
    charArray[count] = '\0';

    return;
}

// Overloaded assignment operator that takes a char*
String& String::operator=(const char* incomingArray)
{
    // Remove previous char array to prepare for new char array
    delete [] charArray;
    int count = 0;

    // Copy pointer from incoming char array
    const char* ptr=incomingArray;

    // Iterate over char values to determine length
    while(*ptr++)
    {
        count++;
    }

    charArray = new char[count + 1];
    sizeOf = count;

    // Iterate over original char array -> assign to destination array
    for(int i = 0; i < count + 1; i++)
    {
        charArray[i] = incomingArray[i];
    }

    // Ensure final char value in array is null
    charArray[count] = '\0';

    return *this;
}

// Overloaded assignment operator that takes existing String
String& String::operator=(const String& incomingString)
{
    return operator = (incomingString.c_str());
}

// Overloaded concatenation operator
String String::operator+(const String& incomingString)
{
    // Logic check for empty string object
    if (incomingString.size() == 0)
    {
        return *this;
    }

    // Create length value for current string object + second string
    int newLength = (this->sizeOf + (incomingString.size()));
    char* tempChar = new char[newLength + 1];

    // Copy current char value(s)
    for(int i = 0; i < this->sizeOf; i++)
    {
        tempChar[i] = this->charArray[i];
    }

    // Copy second string object char value(s)
    for(int i = 0 ;i < incomingString.size(); i++)
    {
        tempChar[i + sizeOf] = incomingString.c_str()[i];
    }

    // Ensure final char value in array is null
    tempChar[newLength] = '\0';

    String newStr = tempChar;

    delete[] tempChar;

    return newStr;
}

// Overloaded equality operator that takes a char*
bool String::operator==(const char* incomingArray) const
{
    if((strcmp(charArray,incomingArray)) == 0)
    {
        return true;
    }

    else
    {
        return false;
    }

}

// Overloaded equality operator that takes an existing String
bool String::operator==(const String& incomingString) const
{
    // Call previously defined equivalency operator with String method for char*
    return operator == (incomingString.c_str());
}

// Overloaded inequality operator that takes a char*
bool String::operator!=(const char* incomingArray)
{
    return !(*this == incomingArray);
}

// Overloaded inequality operator that takes an existing String
bool String::operator!=(const String& incomingString)
{
    return !(*this == incomingString);
}

// Overloaded > comparison operator
bool String::operator>(const String& incomingString) const
{
    return std::strcmp(charArray, incomingString.c_str()) > 0;
}

// Overloaded < comparison operator
bool String::operator<(const String& incomingString) const
{
    return std::strcmp(charArray, incomingString.c_str()) < 0;
}

// Overloaded subscript operator
char& String::operator[](const int index)
{
    // Duplicate value due to passing const
    int element = index;

    // Negative index value
    if(element < 0)
    {
        element += sizeOf;
    }

    else if(element > sizeOf)
    {
        element -= sizeOf;
    }

    return charArray[element];
}

// Get size function
int String::size() const
{
    return sizeOf;
}

// Substring function
String String::substring(int start, int end)
{
    // Negative starting index location
    if(start < 0)
    {
        start += sizeOf + 1;
        end += sizeOf + 1;
    }

    // Negative ending index location
    if(end < 0)
    {
        end += sizeOf + 1;
    }

    // Determine length of new String object
    int length = (end - start);
    char* newArray = new char[length + 1];

    // Copy char by char into new String object
    for(int i = 0; i < length; i++)
    {
        newArray[i] = charArray[i + start];
    }

    // Ensure final char value in array is null
    newArray[length] = '\0';

    String temp = newArray;

    delete[] newArray;

    return temp;
}

// cstring converion function
char* String::c_str() const
{
    return charArray;
}

// Convert to uppercase function
void String::toUpper()
{
    if (this->size() > 0)
    {
        for (int i = 0; i < sizeOf; i++)
        {
            if (charArray[i] >= 'a' && charArray[i] <= 'z')
            {
                charArray[i] -= 32;
            }
        }
    }
}

// Convert to lowercase function
void String::toLower()
{
    if (this->size() > 0)
    {
        for (int i = 0; i < sizeOf; i++)
        {
            if (charArray[i] >= 'A' && charArray[i] <= 'Z')
            {
                charArray[i] += 32;
            }
        }
    }
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.charArray;
    return stream;
}

// Overloaded stream extraction operator
std::istream& operator>>(std::istream& stream, const String& string)
{
    stream >> string.charArray;
    return stream;
}

// Destructor
String::~String()
{
    delete [] charArray;
}
