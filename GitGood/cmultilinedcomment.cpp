#include "cmultilinedcomment.h"

// No-arg constructor
CMultilinedComment::CMultilinedComment()
{
    this->firstLine = 0;
    this->lastLine = 0;
    this->numLinesSpanned = 0;
}

// Overloaded assignment operator
CMultilinedComment& CMultilinedComment::operator=(CMultilinedComment& rhs)
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
void CMultilinedComment::reset()
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
void CMultilinedComment::setFirstLine(int lineIn)
{
    this->firstLine = lineIn;
}

// Set last line function
void CMultilinedComment::setLastLine(int lineIn)
{
    this->lastLine = lineIn;
}

// Add line spanned function
void CMultilinedComment::addLineSpanned(int lineIn)
{
    this->linesSpanned.add(lineIn);
}

// Get first line function
int CMultilinedComment::getFirstLine()
{
    if (this->linesSpanned.size() > 0)
    {
        return this->linesSpanned[0];
    }

    return 0;
}

// Get last line function
int CMultilinedComment::getLastLine()
{
    if (this->linesSpanned.size() > 0)
    {
        return this->linesSpanned[linesSpanned.size()-1];
    }

    return 0;
}

// Get lines spanned function
Vector<int> CMultilinedComment::getLinesSpanned()
{
    return this->linesSpanned;
}

// Get number of lines spanned function
int CMultilinedComment::getNumLinesSpanned()
{
    return this->getLastLine() - this->getFirstLine() + 1;
}
