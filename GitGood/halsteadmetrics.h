#ifndef HALSTEADMETRICS_H
#define HALSTEADMETRICS_H

#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>

#include "AVLTree.h"
#include "DSString.h"
#include "Vector.h"
#include "DSHashtable.h"

class HalsteadMetrics
{
private:
    String filename;

    HashTable<int, bool> isCommentLine;

    int halsteadScore;

    // Number of distinct operators
    int n1;
    // Number of distinct operands
    int n2;

    // Total number of operators
    int N1;
    // Total number of operands
    int N2;

    // Halstead metrics
    int programVocabulary;
    int programLength;
    double calculatedProgramLength;
    double volume;
    double difficulty;
    double effort;
    double expectedTime;
    double expectedBugs;

    void findOperators();
    void findOperands();
    void updateMetrics();
public:
    double halsteadMetricsScore;

public:
    HalsteadMetrics();
    HalsteadMetrics(String inputFilename);

    // Overloaded assignment operator
    HalsteadMetrics& operator=(HalsteadMetrics& rhs);

    // Scan file
    void scanFile(HashTable<int, bool> commentLinesIn);

    // Calculate score
    void calculateScore();

    // Accessors
    String getFilename();
    int getDistinctOperators();
    int getDistinctOperands();
    int getTotalOperators();
    int getTotalOperands();

    int getProgramVocabulary();
    int getProgramLength();
    double getCalculatedProgramLength();
    double getVolume();
    double getDifficulty();
    double getEffort();
    double getExpectedTime();
    double getExpectedBugs();

    // Mutators
    void setFilename(String in);
    void setDistinctOperators(int in);
    void setDistinctOperands(int in);
    void setTotalOperators(int in);
    void setTotalOperands(int in);

    void setProgramVocabulary(int in);
    void setProgramLength(int in);
    void setCalculatedProgramLength(double in);
    void setVolume(double in);
    void setDifficulty(double in);
    void setEffort(double in);
    void setExpectedTime(double in);
    void setExpectedBugs(double in);



};

#endif // HALSTEADMETRICS_H
