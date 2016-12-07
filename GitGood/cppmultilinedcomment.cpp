#include "cppmultilinedcomment.h"

// No-arg constructor
CppMultilinedComment::CppMultilinedComment()
{
    this->firstLine = 0;
    this->lastLine = 0;
    this->numLinesSpanned = 0;
}

// Overloaded assignment operator
CppMultilinedComment& CppMultilinedComment::operator=(CppMultilinedComment& rhs)
{
    if (this != &rhs)
    {
        this->firstLine = rhs.firstLine;
        this->lastLine = rhs.lastLine;
        this->numLinesSpanned = rhs.numLinesSpanned;
        this->linesSpanned = rhs.linesSpanned;

        return *this;
    }
}

// Reset function
void CppMultilinedComment::reset()
{
    // Call the destructor
    this->linesSpanned.~Vector();

    Vector<int> temp;
    this->linesSpanned = temp;
    this->firstLine = 0;
    this->lastLine = 0;
    this->numLinesSpanned = 0;
}

// Set first line function
void CppMultilinedComment::setFirstLine(int lineIn)
{
    this->firstLine = lineIn;
}

// Set last line function
void CppMultilinedComment::setLastLine(int lineIn)
{
    this->lastLine = lineIn;
}

// Add line spanned function
void CppMultilinedComment::addLineSpanned(int lineIn)
{
    this->linesSpanned.add(lineIn);
}

// Get first line function
int CppMultilinedComment::getFirstLine()
{
    return this->linesSpanned[0];
}

// Get last line function
int CppMultilinedComment::getLastLine()
{
    return this->linesSpanned[linesSpanned.size()-1];
}

// Get lines spanned function
Vector<int> CppMultilinedComment::getLinesSpanned()
{
    return this->linesSpanned;
}

// Get number of lines spanned function
int CppMultilinedComment::getNumLinesSpanned()
{
    return this->getLastLine() - this->getFirstLine() + 1;
}
