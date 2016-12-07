#include "filemetrics.h"

#define DEBUG false

// Default constructor
FileMetrics::FileMetrics()
{
    this->filename = "";
    this->aggregateFileScore = 0;
}

// Parametrized constructor
FileMetrics::FileMetrics(String fileIn)
{
    this->filename = fileIn;
    this->aggregateFileScore = 0;
}

// Generate metrics function
void FileMetrics::generateMetrics()
{
    /* ------- ADD METRIC OBJECTS HERE ------- */
    CommentMetrics tempCommentMetrics(this->filename);
    LineMetrics tempLineMetrics(this->filename);
    ClassMetrics tempClassMetrics(this->filename);
    VariableMetrics tempVariableMetrics(this->filename);
    HalsteadMetrics tempHalsteadMetrics(this->filename);
    /* ------- ADD METRIC OBJECTS HERE ------- */

    // Generate comment metrics for this file
    tempCommentMetrics.scanFile();

    // Generate line metrics for this file
    tempLineMetrics.scanFile();
    tempLineMetrics.calculateRatios(tempCommentMetrics);

    // Generate class metrics for this file
    tempClassMetrics.scanFile(tempCommentMetrics.isCommentLine);

    // Generate variable metrics for this file
    tempVariableMetrics.scanFile(tempCommentMetrics.isCommentLine);

    // Generate Halstead complexity metrics for the file
    tempHalsteadMetrics.scanFile(tempCommentMetrics.isCommentLine);

    if (DEBUG)
    {
        tempLineMetrics.debug();
        tempCommentMetrics.debug();
        tempClassMetrics.debug();
    }

    /* ------- ADD METRIC OBJECTS HERE ------- */
    this->commentData = tempCommentMetrics;
    this->lineData = tempLineMetrics;
    this->classData = tempClassMetrics;
    this->variableData = tempVariableMetrics;
    this->halsteadData = tempHalsteadMetrics;
    /* ------- ADD METRIC OBJECTS HERE ------- */
}

// Calculate aggregate file score function
void FileMetrics::calculateScores()
{
    double temp = 0;

    this->commentData.calculateScore();
    this->lineData.calculateScore();
    this->classData.calculateScore();
    this->variableData.calculateScore();
    this->halsteadData.calculateScore();

    temp += this->commentData.commentMetricsScore;
    temp += this->lineData.lineMetricsScore;
    temp += this->classData.classMetricsScore;
    temp += this->variableData.variableMetricsScore;
    temp += this->halsteadData.halsteadMetricsScore;

    this->aggregateFileScore = temp;
}

