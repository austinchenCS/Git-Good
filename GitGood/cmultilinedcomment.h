#ifndef CMULTILINEDCOMMENT_H
#define CMULTILINEDCOMMENT_H

#include "Vector.h"

class CMultilinedComment
{
private:

public:
    Vector<int> linesSpanned;
    int firstLine;
    int lastLine;
    int numLinesSpanned;
public:
    // Constructor
    CMultilinedComment();

    // Overloaded assignment operator
    CMultilinedComment& operator=(CMultilinedComment& rhs);

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

#endif // CMULTILINEDCOMMENT_H
