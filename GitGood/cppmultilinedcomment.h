#ifndef CPPMULTILINEDCOMMENT_H
#define CPPMULTILINEDCOMMENT_H

#include "Vector.h"

class CppMultilinedComment
{

private:
public:
    Vector<int> linesSpanned;
    int firstLine;
    int lastLine;
    int numLinesSpanned;
public:
    // Constructor
    CppMultilinedComment();

    // Overloaded assignment operator
    CppMultilinedComment& operator=(CppMultilinedComment& rhs);

    // Reset function
    void reset();

    // Mutator functions
    void setFirstLine(int lineIn);
    void setLastLine(int lineIn);
    void addLineSpanned(int lineIn);

    // Accessor functions
    int getFirstLine();
    int getLastLine();
    Vector<int> getLinesSpanned();
    int getNumLinesSpanned();

};

#endif // CPPMULTILINEDCOMMENT_H
