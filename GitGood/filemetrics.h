#ifndef FILEMETRICS_H
#define FILEMETRICS_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

#include "DSString.h"
#include "Vector.h"
#include "AVLTree.h"
#include "DSHashtable.h"

#include "linemetrics.h"
#include "commentmetrics.h"
#include "filefind.h"
#include "classmetrics.h"
#include "variablemetrics.h"
#include "halsteadmetrics.h"


class FileMetrics
{
private:

    // Key: Line number, Value: commentline true or false
    HashTable<int, bool> commentLines;

public:
    String filename;

    double aggregateFileScore;

    LineMetrics lineData;
    CommentMetrics commentData;
    ClassMetrics classData;
    VariableMetrics variableData;
    HalsteadMetrics halsteadData;

    FileMetrics();
    FileMetrics(String fileIn);

    void generateMetrics();
    void calculateScores();

};

#endif // FILEMETRICS_H
