#ifndef VARIABLEMETRICS_H
#define VARIABLEMETRICS_H

#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>

#include "AVLTree.h"
#include "DSString.h"
#include "Vector.h"
#include "DSHashtable.h"

class VariableMetrics
{
private:

    String filename;
    HashTable<int, bool> isCommentLine;
    double averageVariableLength;
    double medianVariableLength;

    // Private member functions
    void findAverageVariableLength();

public:
    double variableMetricsScore;

public:
    VariableMetrics();
    VariableMetrics(String inputFilename);

    VariableMetrics& operator=(VariableMetrics& rhs);

    void scanFile(HashTable<int, bool> commentLinesIn);

    void calculateScore();

    int getVariableScore();
    double getAverageVariableLength();
    double getMedianVariableLength();

    void setVariableScore(int in);
    void setAverageVariableLength(double in);
    void setMedianVariableLength(double in);
};

#endif // VARIABLEMETRICS_H
