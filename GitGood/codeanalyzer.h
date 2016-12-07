#ifndef CODEANALYZER_H
#define CODEANALYZER_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <cmath>

#include "DSString.h"
#include "Vector.h"
#include "AVLTree.h"
#include "DSHashtable.h"

#include "linemetrics.h"
#include "commentmetrics.h"
#include "filefind.h"
#include "classmetrics.h"
#include "halsteadmetrics.h"

#include "filemetrics.h"

class CodeAnalyzer
{
private:
    char* directoryPathName;
    char* outputName;

    Vector<double> fileScores;

    double finalScore;

public:
    CodeAnalyzer();
    CodeAnalyzer(char* directoryPathName, char* outputName);

    // Analyze the entire code base
    void analyze();
    // Generate report
    void generateReport(FileMetrics& allMetrics);

    // Print the report to a file
    void printReport();
    // Calculate numerical score
    void calculateScore();

    // Set final score
    void setFinalScore(double in);
    // Get final score
    double getFinalScore();
};

#endif // CODEANALYZER_H
