#ifndef COMMENTMETRICS_H
#define COMMENTMETRICS_H

#include <iostream>
#include <fstream>

#include "AVLTree.h"
#include "DSString.h"
#include "Vector.h"
#include "DSHashtable.h"

#include "cmultilinedcomment.h"
#include "cppmultilinedcomment.h"

class CommentMetrics
{
private:
    // Filename to be opened:
    String filename;

public:
    // Hash table that contains true/false data for whether a line
    // is a "comment line" or not.
    HashTable<int, bool> isCommentLine;

    // Score
    double commentMetricsScore;

    // Numlines in file
    int numLinesInFile;

    // # of inlined "//" comments
    int numInlinedCommentsCpp;
    // # of inlined "/* */" comments
    int numInlinedCommentsC;

    // # of full-lined "//" comments
    int numFullLineCommentsCpp;
    // # of full-lined "/* */" comments
    int numFullLineCommentsC;

    // # of multiline "//" comment (by using \)
    int numMultilinedCommentsCpp;
    // # of multiline "/* */" comments
    int numMultilinedCommentsC;

    // Vector of line numbers of all inlined "//" comments
    Vector<int> locInlinedCpp;
    // Vector of line numbers with an inlined "/* */" comments
    Vector<int> locInlinedC;

    // Vector of line numbers of all full line "//" comments
    Vector<int> locFullLineCpp;
    //Vector of line numbers of all full line "/* */" comments
    Vector<int> locFullLineC;

    // Vector of mutliline "// comment" objects
    Vector<CppMultilinedComment> cppMultilinedComments;
    // Vector of multiline "/* */ comment" objects
    Vector<CMultilinedComment> cMultilinedComments;

public:
    // Constructors
    CommentMetrics();
    CommentMetrics(String inputFilename);

    void scanFile();

    void calculateScore();

    // Individual comment scanners
    void scanInlinedCpp();
    void scanInlinedC();
    void scanFullLineCpp();
    void scanFullLineC();
    void scanMultilinedCpp();
    void scanMultilinedC();

    // Accessors
    int getNumFullLineCommentsCpp();
    int getNumFullLineCommentsC();

    int getCppMultilinedCommentsTotalSpan();
    int getCMultilinedCommentsTotalSpan();

    void debug();

    CommentMetrics& operator=(CommentMetrics& rhs);

    void updateCommentLineHash();

};

#endif // COMMENTMETRICS_H

