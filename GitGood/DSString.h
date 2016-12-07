#ifndef STRING
#define STRING

#include <iostream>
#include <cstring>

class String
{

private:

    // char* that will store the String data payload
    char* charArray;

    // integer that represents the length of the string
    int sizeOf;

public:

    // No-arg constructor
    String();
    // Parametrized constructor that takes a char*
    String(const char*);

    // Copy constructor
    String(const String&);

    // Overloaded assignment operators
    String& operator=(const char*);
    String& operator=(const String&);

    // Overloaded concatenation operator
    String operator+(const String&);

    // Overloaded equality operator
    bool operator==(const char*) const;
    bool operator==(const String&) const;

    // Overloaded inequality operator
    bool operator!=(const char*);
    bool operator!=(const String&);

    // Overloaded comparison operators
    bool operator>(const String&) const;
    bool operator<(const String&) const;

    // Overloaded subscript operator
    char& operator[] (const int);

    // Get size function
    int size() const;

    // Substring function
    String substring(int, int);

    // cstring conversion function
    char* c_str() const;

    // Convert string to uppercase function
    void toUpper();
    // Convert string to lowercase function
    void toLower();

    // Overloaded stream insertion operator
    friend std::ostream& operator<<(std::ostream&, const String&);
    // Overloaded stream extraction operator
    friend std::istream& operator>>(std::istream&, const String&);

    // Destructor
    ~String();

};

#endif
