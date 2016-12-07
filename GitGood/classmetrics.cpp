#include "classmetrics.h"

#include <cctype>

using namespace std;

// Default constructor
ClassMetrics::ClassMetrics()
{
    this->filename = "";
    this->classMetricsScore = 0;
    this->numImproperClassNames = 0;
}

// Parametrized constructor
ClassMetrics::ClassMetrics(String inputFilename)
{
    this->filename = inputFilename;
    this->classMetricsScore = 0;
    this->numImproperClassNames = 0;
}

// Overloaded assignment operator
ClassMetrics& ClassMetrics::operator=(ClassMetrics& rhs)
{
    // Prevent self assignment
    if (this != &rhs)
    {
        this->filename = rhs.filename;
        this->classMetricsScore = rhs.classMetricsScore;
        this->numImproperClassNames = rhs.numImproperClassNames;
        this->locImproperClassNames = rhs.locImproperClassNames;

        return *this;
    }
}

// Scan file for capital name class declarations
void ClassMetrics::scanClassNames()
{
    // Count the number of lines in the file
    ifstream fcount(this->filename.c_str());
    // Error handling with file opening
    if (!fcount)
    {
        cerr << "error: File(s) could not be opened!" << endl;
    }

    string tempLine;
    int numLinesCheck = 0;

    while (getline(fcount, tempLine))
    {
        numLinesCheck++;
    }

    fcount.close();

    ifstream fin(this->filename.c_str());

    // Error handling with file opening
    if (!fin)
    {
        cerr << "error: File(s) could not be opened!" << endl;
    }

    // Buffer that reads file character by character
    char buffer;

    // Number of lines in file
    int numLines = 0;

    Vector<char> tempClassnames;

    // Loop traverses file character by character, but ANALYZES line by line.
    while (fin.get(buffer))
    {
        // Increment counter
        numLines++;

        // Initialize vector that will store the current line
        Vector<char> currLine;

        // Iterate on the last loop in case the file does not have a newline
        // at the end of the program
        if (numLinesCheck == numLines)
        {
            currLine.add(buffer);
            while (!fin.eof())
            {
                fin.get(buffer);
                if (fin.eof()) break;
                currLine.add(buffer);
            }

            if (currLine[currLine.size()-1] != '\n')
            {
                currLine.add('\n');
            }
        }

        else
        {
            // Load the contents of the line in
            while (buffer != '\n')
            {
                currLine.add(buffer);
                fin.get(buffer);
            }
            // Can't forget to add the newline character to the end
            currLine.add(buffer);
        }

        // Flags that reset each new line
        bool contentFound = false;
        bool inlinedCommentFound = false;

        // Scans the entire line for analytics
        for (int i = 0; i < currLine.size(); i++)
        {

            // Check for first sighting of content
            if (currLine[i] > 32 && !contentFound)
            {
                contentFound = true;
            }

            // If content is found:
            if (contentFound)
            {
                bool potentialClass = false;

                // Check for comments
                if (currLine[i] == '/')
                {
                    if ((i + 1) <= currLine.size()-2)
                    {
                        if (currLine[i + 1] == '/' || currLine[i + 1] == '*')
                        {
                            inlinedCommentFound = true;
                        }
                    }
                }

                // Check for a class declaration
                if (currLine[i] == 'c' && (currLine.size() - i) >= 8)
                {
                    if (currLine[i + 1] == 'l'
                     && currLine[i + 2] == 'a'
                     && currLine[i + 3] == 's'
                     && currLine[i + 4] == 's'
                     && currLine[i + 5] == ' ')
                    {
                        potentialClass = true;
                    }

                    // The "!inlinedCommentFound" prevents any class declaration
                    // within a comment to treated like a real declared class
                    if (potentialClass && !inlinedCommentFound)
                    {
                        if (!isupper(currLine[i + 6]))
                        {
                            this->numImproperClassNames++;
                            this->locImproperClassNames.add(numLines);
                        }
                    }
                }
            }
        }
    }

    fin.close();
}

// Remove false positives function
void ClassMetrics::removeFalsePositives(HashTable<int, bool> commentLocationsIn)
{
    Vector<int> tempVec;

    bool wentThrough = false;

    for (int i = 0; i < this->locImproperClassNames.size(); i++)
    {
        wentThrough = true;
        if (!commentLocationsIn[this->locImproperClassNames[i]])
        {
            tempVec.add(this->locImproperClassNames[i]);
        }
    }

    if (wentThrough)
    {
        this->locImproperClassNames = tempVec;
        this->numImproperClassNames = this->locImproperClassNames.size();
    }

}

// Public scan file function
void ClassMetrics::scanFile(HashTable<int, bool> commentLocationsIn)
{
    scanClassNames();
    removeFalsePositives(commentLocationsIn);
}

// Calculate score
void ClassMetrics::calculateScore()
{
    double score = 0.0;

    if (this->numImproperClassNames > 0)
    {
        score+=this->numImproperClassNames;
    }

    this->classMetricsScore = score;
}

// Debug function
void ClassMetrics::debug()
{
    // Lists line numbers where first letter of class name is not capitalized
    cout << this->locImproperClassNames.size()
         <<" line location(s) where improperly named classes occur: " << endl;
    if (this->locImproperClassNames.size() > 0)
    {
        for (int i = 0; i < this->locImproperClassNames.size(); i++)
        {
            cout << this->locImproperClassNames[i] << endl;
        }
    }
    else cout << "- None" << endl;

    cout << endl;
}
