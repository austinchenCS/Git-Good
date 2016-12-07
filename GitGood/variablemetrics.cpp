#include "variablemetrics.h"

// No-arg constructor
VariableMetrics::VariableMetrics()
{
    this->filename = "";
    this->averageVariableLength = 0;
    this->medianVariableLength = 0;
    this->variableMetricsScore = 0;
}

// Parametrized constructor
VariableMetrics::VariableMetrics(String inputFilename)
{
    this->filename = inputFilename;
    this->averageVariableLength = 0;
    this->medianVariableLength = 0;
    this->variableMetricsScore = 0;
}

// Overloaded assignment operator
VariableMetrics& VariableMetrics::operator=(VariableMetrics& rhs)
{
    this->filename = rhs.filename;
    this->averageVariableLength = rhs.averageVariableLength;
    this->medianVariableLength = rhs.medianVariableLength;
    this->variableMetricsScore = rhs.variableMetricsScore;
    this->isCommentLine = rhs.isCommentLine;

    return *this;
}

// Public scan file metric
void VariableMetrics::scanFile(HashTable<int, bool> commentLinesIn)
{
    this->isCommentLine = commentLinesIn;
    findAverageVariableLength();
}

// Find average variable length
void VariableMetrics::findAverageVariableLength()
{
    ifstream fin(this->filename.c_str());

    if (!fin)
    {
        cerr << "error: Files(s) could not be opened!" << endl;
    }

    string searchPattern = "(bool[* ]*)([a-zA-Z0-9_]+)|"
                           "(int[* ]*)([a-zA-Z0-9_]+)|"
                           "(float[* ]*)([a-zA-Z0-9_]+)|"
                           "(char[* ]*)([a-zA-Z0-9_]+)|"
                           "(double[* ]*)([a-zA-Z0-9_]+)";

    smatch m;
    regex reg1(searchPattern);

    string lineTemp;
    int lineNum = 0;

    AvlTree<string> uniqueIdentifiers;
    int numUniqueIdentifiers = 0;

    Vector<int> variableLengths;

    // Find all variable lengths
    while (!fin.eof())
    {
        lineNum++;
        getline(fin, lineTemp);

        while (regex_search(lineTemp, m, reg1))
        {
            bool found = false;
            int iTemp = 0;

            for (int i = 1; i < m.size();i ++)
            {
                if (m[i] != "")
                {
                    found = true;
                    iTemp = i;
                    break;
                }
            }

            if (found)
            {
                if (!uniqueIdentifiers.contains(m[iTemp + 1])
                        && !this->isCommentLine[lineNum])
                {
                    uniqueIdentifiers.insert(m[iTemp + 1]);
                    numUniqueIdentifiers++;
                    variableLengths.add(m[iTemp + 1].length());
                }
            }

            lineTemp = m.suffix().str();
        }
    }
    lineNum--;

    // Calculate average and median
    double averageLen = 0;
    double medianLen = 0;

    if (variableLengths.size() > 0)
    {
        int sumLengths = 0;

        variableLengths.sort();
        for (int i = 0; i < variableLengths.size(); i++)
        {
            sumLengths += variableLengths[i];
        }

        averageLen = (double)sumLengths/(double)variableLengths.size();

        // If even number of variables
        if ((variableLengths.size() % 2) == 0)
        {
            medianLen = ((double)variableLengths[(variableLengths.size()
        / 2)-1]
                    + (double)variableLengths[variableLengths.size() / 2])
        / 2;
        }

        // If odd number of variables
        else if ((variableLengths.size() % 2) == 1)
        {
            medianLen = variableLengths[(variableLengths.size() / 2)];
        }
    }
    // Set average and median
    this->averageVariableLength = averageLen;
    this->medianVariableLength = medianLen;
}

// Calculate score
void VariableMetrics::calculateScore()
{
    double score = 0.0;

    if (this->averageVariableLength < 8.0)
    {

        if (this->averageVariableLength > 6.0)
        {
            double penalty = (8.0 - (this->averageVariableLength));
            penalty *= 1;
            score += penalty;
        }

        else
        {
            double penalty = (8.0 - (this->averageVariableLength));
            penalty *= 1;
            score += (penalty*2);
        }

    }

    this->variableMetricsScore = score;
}

// Get variable score
int VariableMetrics::getVariableScore()
{
    return this->variableMetricsScore;
}

// Get average variable length
double VariableMetrics::getAverageVariableLength()
{
    return this->averageVariableLength;
}

// Get median variable length
double VariableMetrics::getMedianVariableLength()
{
    return this->medianVariableLength;
}

// Set variable score
void VariableMetrics::setVariableScore(int in)
{
    this->variableMetricsScore = in;
}

// Set average variable length
void VariableMetrics::setAverageVariableLength(double in)
{
    this->averageVariableLength = in;
}

// Set average variable length
void VariableMetrics::setMedianVariableLength(double in)
{
    this->medianVariableLength = in;
}
