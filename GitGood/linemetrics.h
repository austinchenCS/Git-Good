#ifndef LINEMETRICS_H
#define LINEMETRICS_H

#include <iostream>
#include <fstream>

#include "DSString.h"
#include "Vector.h"

#include "commentmetrics.h"

class LineMetrics
{
private:
    // Filename to be opened:
    String filename;

public:
    double lineMetricsScore;

    // # of total lines in file
    int numTotalLines;
    // # of lines containing code
    int numLinesOfInstruction;
    // # of whitespace lines
    int numLinesOfWhitespace;
    // # of lines over 80 characters
    int numLinesOver80Chars;

    // Ratio of comments to lines containing code
    double ratioCommentsToInstruction;
    // Ratio of comments to total file liness
    double ratioCommentsToTotalFileLines;

    // Ratio of comments to lines containing code
    double ratioCommentsToInstructionOneTo;
    // Ratio of comments to total file liness
    double ratioCommentsToTotalFileLinesOneTo;

    // Vector containing line numbers where line length exceeds 80 characters
    Vector<int> locLinesOver80Chars;

    void generateRatios(CommentMetrics commentObjIn);
    void generateRatiosOneTo(CommentMetrics commentObjIn);

public:
    // Constructors
    LineMetrics();
    LineMetrics(String inputFilename);

    // Scan file
    void scanFile();
    void calculateRatios(CommentMetrics commentObjIn);
    void debug();

    void calculateScore();

    LineMetrics& operator=(LineMetrics& rhs);

};

#endif // LINEMETRICS_H


