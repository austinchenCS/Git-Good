#include "commentmetrics.h"

using namespace std;

// Default constructor
CommentMetrics::CommentMetrics()
{
    this->filename = "";
    this->commentMetricsScore = 0;
    this->numLinesInFile = 0;
    this->numInlinedCommentsCpp = 0;
    this->numInlinedCommentsC = 0;
    this->numFullLineCommentsCpp = 0;
    this->numFullLineCommentsC = 0;
    this->numMultilinedCommentsCpp = 0;
    this->numMultilinedCommentsC = 0;
}

// Parametrized constructor
CommentMetrics::CommentMetrics(String inputFilename)
{
    this->filename = inputFilename;
    this->commentMetricsScore = 0;
    this->numLinesInFile = 0;
    this->numInlinedCommentsCpp = 0;
    this->numInlinedCommentsC = 0;
    this->numFullLineCommentsCpp = 0;
    this->numFullLineCommentsC = 0;
    this->numMultilinedCommentsCpp = 0;
    this->numMultilinedCommentsC = 0;
}

// Overloaded assignment operator
CommentMetrics& CommentMetrics::operator=(CommentMetrics& rhs)
{
    if (this != &rhs)
    {
        this->filename = rhs.filename;

        this->commentMetricsScore = rhs.commentMetricsScore;

        this->numLinesInFile = rhs.numLinesInFile;

        this->numInlinedCommentsCpp = rhs.numInlinedCommentsCpp;
        this->numInlinedCommentsC = rhs.numInlinedCommentsC;

        this->numFullLineCommentsCpp = rhs.numFullLineCommentsCpp;
        this->numFullLineCommentsC = rhs.numFullLineCommentsC;

        this->numMultilinedCommentsCpp = rhs.numMultilinedCommentsCpp;
        this->numMultilinedCommentsC = rhs.numMultilinedCommentsC;

        this->locInlinedCpp = rhs.locInlinedCpp;
        this->locInlinedC = rhs.locInlinedC;

        this->locFullLineCpp = rhs.locFullLineCpp;
        this->locFullLineC = rhs.locFullLineC;

        this->cppMultilinedComments = rhs.cppMultilinedComments;
        this->cMultilinedComments = rhs.cMultilinedComments;

        this->isCommentLine = rhs.isCommentLine;

        return *this;
    }
}

// Scan file for inlined "//" comments
void CommentMetrics::scanInlinedCpp()
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

        // Scans the entire line for analytics
        for (int i = 0; i < currLine.size(); i++)
        {
            // Check for cpp style comments
            if (currLine[i] == '/' && contentFound)
            {
                if ((i + 1) <= currLine.size()-2)
                {
                    // Check for "//" inlined comments
                    if (currLine[i + 1] == '/'
                            && currLine[currLine.size()-2] != '\\')
                    {
                        this->numInlinedCommentsCpp++;
                        this->locInlinedCpp.add(numLines);
                    }
                }
            }

            // Check for first sighting of content
            if (currLine[i] > 32)
            {
                contentFound = true;
            }
        }
    }

    fin.close();
}

// Scan file for inlined "/* */" comments
void CommentMetrics::scanInlinedC()
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

    // Found a multilined comment flag
    bool commentOpen = false;

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

        // Scans the entire line for analytics
        for (int i = 0; i < currLine.size(); i++)
        {
            // Check for c style comments
            if (currLine[i] == '/' && contentFound)
            {
                if ((i + 1) <= currLine.size()-2)
                {
                    // Check for open comment
                    if (currLine[i + 1] == '*')
                    {
                        commentOpen = true;
                    }
                }
            }

            // Check for first sighting of content
            if (currLine[i] > 32)
            {
                contentFound = true;
            }
        }

        if (commentOpen)
        {
            if (currLine.size() > 3)
            {
                if (currLine[currLine.size()-3] == '*'
                        && currLine[currLine.size()-2] == '/'
                        && currLine[currLine.size()-4] != '/')
                {
                    this->locInlinedC.add(numLines);
                }
            }
            commentOpen = false;
        }
    }

    fin.close();

    this->numInlinedCommentsC = this->locInlinedC.size();
}

// Scan file for full-line "//" comments
void CommentMetrics::scanFullLineCpp()
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

        // Scans the entire line for analytics
        for (int i = 0; i < currLine.size(); i++)
        {
            // Check for cpp style comments
            if (currLine[i] == '/' && !contentFound)
            {
                if ((i + 1) <= currLine.size()-2)
                {
                    // Check for "//" FULL LINE comments
                    if (currLine[i + 1] == '/'
                            && currLine[currLine.size()-2] != '\\')
                    {
                        this->numFullLineCommentsCpp++;
                        this->locFullLineCpp.add(numLines);
                    }
                }
            }

            // Check for first sighting of content
            if (currLine[i] > 32)
            {
                contentFound = true;
            }
        }
    }

    fin.close();
}

// Scan file for full-line "/* */" comments
void CommentMetrics::scanFullLineC()
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

    // Found a multilined comment flag
    bool commentOpen = false;

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

        // Scans the entire line for analytics
        for (int i = 0; i < currLine.size(); i++)
        {
            // Check for c style comments
            if (currLine[i] == '/' && !contentFound)
            {
                if ((i + 1) <= currLine.size()-2)
                {
                    // Check for open comment
                    if (currLine[i + 1] == '*')
                    {
                        commentOpen = true;
                    }
                }
            }

            // Check for first sighting of content
            if (currLine[i] > 32)
            {
                contentFound = true;
            }
        }

        if (commentOpen)
        {
            if (currLine.size() > 3)
            {
                if (currLine[currLine.size()-3] == '*'
                        && currLine[currLine.size()-2] == '/'
                        && currLine[currLine.size()-4] != '/')
                {
                    this->locFullLineC.add(numLines);
                }
            }
            commentOpen = false;
        }
    }

    fin.close();

    this->numFullLineCommentsC = this->locFullLineC.size();
}

// Scan file for multilined "//" comments
void CommentMetrics::scanMultilinedCpp()
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

    // Found a multilined comment flag
    bool commentOpen = false;

    Vector<int> multilinesSpanned;

    int indexToStartAt = 0;

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

        bool commentClose = false;

        // Scans the entire line for analytics
        for (int i = 0; i < currLine.size(); i++)
        {
            // Check for cpp style comments
            if (currLine[i] == '/')
            {
                if ((i + 1) <= currLine.size()-2)
                {
                    // Check for "//" comments
                    if (currLine[i + 1] == '/'
                            && currLine[currLine.size()-2] == '\\')
                    {
                        commentOpen = true;
                    }
                }
            }

            if (commentOpen == true)
            {
                if (currLine[currLine.size()-2] != '\\')
                {
                    commentClose = true;
                }
            }
        }

        if (commentOpen)
        {
            multilinesSpanned.add(numLines);
        }

        if (commentClose)
        {
            CppMultilinedComment tempMultiline;
            for (int i = indexToStartAt; i < multilinesSpanned.size(); i++)
            {
                indexToStartAt++;
                tempMultiline.addLineSpanned(multilinesSpanned[i]);
            }
            this->cppMultilinedComments.add(tempMultiline);
            commentOpen = false;
        }
    }

    fin.close();

    this->numMultilinedCommentsCpp = this->cppMultilinedComments.size();
}

// Scan file for multilined "/* */" comments
void CommentMetrics::scanMultilinedC()
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

    // Found a multilined comment flag
    bool commentOpen = false;

    Vector<int> multilinesSpanned;

    int indexToStartAt = 0;

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

        bool commentClose = false;

        // Scans the entire line for analytics
        for (int i = 0; i < currLine.size(); i++)
        {
            // Check for c style comments
            if (currLine[i] == '/')
            {
                if ((i + 1) <= currLine.size()-2)
                {
                    // Check for open comment
                    if (currLine[i + 1] == '*')
                    {
                        commentOpen = true;
                    }
                }
            }

            // Check for closing c style comment
            if (currLine[i] == '*')
            {
                if ((i + 1) <= currLine.size()-2)
                {
                    if (currLine[i + 1] == '/')
                    {
                        commentClose = true;
                    }
                }
            }

            // Check for first sighting of content
            if (currLine[i] > 32)
            {
                contentFound = true;
            }
        }

        if (commentOpen)
        {
            multilinesSpanned.add(numLines);
        }

        if (commentClose)
        {
            CMultilinedComment tempMultiline;

            if (!((multilinesSpanned.size() - indexToStartAt) <= 1))
            {
                for (int i = indexToStartAt; i < multilinesSpanned.size(); i++)
                {
                    indexToStartAt++;
                    tempMultiline.addLineSpanned(multilinesSpanned[i]);
                }
                this->cMultilinedComments.add(tempMultiline);
            }

            else
            {
                indexToStartAt++;
            }

            commentOpen = false;
        }
    }

    fin.close();

    this->numMultilinedCommentsC = this->cMultilinedComments.size();
}

// Update hash table
void CommentMetrics::updateCommentLineHash()
{
    ifstream fin(this->filename.c_str());

    // Error handling with file opening
    if (!fin)
    {
        cerr << "error: File(s) could not be opened!" << endl;
    }

    // Calculate how many lines there are in the current file
    string lineTemp;

    int totalLines = 0;

    while (!fin.eof())
    {
        ++totalLines;
        getline(fin, lineTemp);
    }
    totalLines--;

    // Set private member data
    this->numLinesInFile = totalLines;

    // Set all lines in file to false by default
    for (int i = 1; i < totalLines+1; i++)
    {
        this->isCommentLine[i] = false;
    }

    // After setting all lines to false, we will traverse through all the
    // member data to see which lines should be set to true, and then set them.

    // Traverse through full line C style comments
    for (int i = 0; i < this->locFullLineC.size(); i++)
    {
        this->isCommentLine[this->locFullLineC[i]] = true;
    }
    // Traverse through full line Cpp style comments
    for (int i = 0; i < this->locFullLineCpp.size(); i++)
    {
        this->isCommentLine[this->locFullLineCpp[i]] = true;
    }
    // Traverse through multiline C style comments
    for (int i = 0; i < this->cMultilinedComments.size(); i++)
    {
        for (int j = 0; j < this->cMultilinedComments[i].linesSpanned.size();
             j++)
        {
            this->isCommentLine[this->cMultilinedComments[i].linesSpanned[j]]
                    = true;
        }
    }
    // Traverse through multiline C style comments
    for (int i = 0; i < this->cppMultilinedComments.size(); i++)
    {
        for (int j = 0; j < this->cppMultilinedComments[i].linesSpanned.size();
             j++)
        {
            this->isCommentLine[this->cppMultilinedComments[i].linesSpanned[j]]
                    = true;
        }
    }

}

// Scan file
void CommentMetrics::scanFile()
{
    scanInlinedCpp();
    scanInlinedC();
    scanFullLineCpp();
    scanFullLineC();
    scanMultilinedCpp();
    scanMultilinedC();
    updateCommentLineHash();
}

// Calculate score
void CommentMetrics::calculateScore()
{
    double score = 0.0;
    if (this->numInlinedCommentsC > 0)
    {
        double penalty = (double)this->numInlinedCommentsC /
                (double)this->numLinesInFile;
        penalty *= 100;
        score += penalty;
    }
    if (this->numInlinedCommentsCpp > 0)
    {
        double penalty = (double)this->numInlinedCommentsCpp /
                (double)this->numLinesInFile;
        penalty *= 100;
        score += penalty;
    }
    this->commentMetricsScore = score;
}

// Get number of full line Cpp comments
int CommentMetrics::getNumFullLineCommentsCpp()
{
    return this->numFullLineCommentsCpp;
}

// Get number of full line C comments
int CommentMetrics::getNumFullLineCommentsC()
{
    return this->numFullLineCommentsC;
}

// Get total number of lines that Cpp multiline comments span
int CommentMetrics::getCppMultilinedCommentsTotalSpan()
{
    int sum = 0;

    for (int i = 0; i < this->cppMultilinedComments.size(); i++)
    {
        sum += this->cppMultilinedComments[i].getNumLinesSpanned();
    }

    return sum;
}

// Get total number of lines that Cpp multiline comments span
int CommentMetrics::getCMultilinedCommentsTotalSpan()
{
    int sum = 0;

    for (int i = 0; i < this->cMultilinedComments.size(); i++)
    {
        sum += this->cMultilinedComments[i].getNumLinesSpanned();
    }

    return sum;
}


// Debug
void CommentMetrics::debug()
{
    cout << this->numFullLineCommentsCpp
         << " line location(s) with full line \"//\" style comments: " << endl;
    if (this->locFullLineCpp.size() > 0)
    {
        for (int i = 0; i < this->locFullLineCpp.size(); i++)
        {
            cout << "  " << this->locFullLineCpp[i] << endl;
        }
    }
    else cout << " -None" << endl;

    cout << this->numFullLineCommentsC
         << " line location(s) with full line  \"/* */\" style comments: "
         << endl;
    if (this->locFullLineC.size() > 0)
    {
        for (int i = 0; i < this->locFullLineC.size(); i++)
        {
            cout << "  " << this->locFullLineC[i] << endl;
        }
    }
    else cout << " -None" << endl;

    cout << this->numInlinedCommentsCpp
         << " line location(s) with inlined \"//\" style comments: " << endl;
    if (this->locInlinedCpp.size() > 0)
    {
        for (int i = 0; i < this->locInlinedCpp.size(); i++)
        {
            cout << "  " <<  this->locInlinedCpp[i] << endl;
        }
    }
    else cout << " -None" << endl;

    cout << this->numInlinedCommentsC
         << " line location(s) with inlined  \"/* */\" style comments: "
         << endl;
    if (this->locInlinedC.size() > 0)
    {
        for (int i = 0; i < this->locInlinedC.size(); i++)
        {
            cout << "  " << this->locInlinedC[i] << endl;
        }
    }
    else cout << " -None" << endl;

    cout << this->numMultilinedCommentsCpp
         << " line locations with multilined \"//\" style comments: " << endl;
    if (this->cppMultilinedComments.size() > 0)
    {
        for (int i = 0; i < this->cppMultilinedComments.size(); i++)
        {
            cout << "  ";
            cout << this->cppMultilinedComments[i].getFirstLine();
            cout << '-';
            cout << this->cppMultilinedComments[i].getLastLine();
            cout << endl;
        }
    }
    else cout << " -None" << endl;

    cout << this->numMultilinedCommentsC
         << " line locations with multi-line \"/* */\" style comments: "
         << endl;
    if (this->cMultilinedComments.size() > 0)
    {
        for (int i = 0; i < this->cMultilinedComments.size(); i++)
        {
            cout << "  ";
            cout << this->cMultilinedComments[i].getFirstLine();
            cout << '-';
            cout << this->cMultilinedComments[i].getLastLine();
            cout << endl;
        }
    }
    else cout << " -None" << endl;

    cout << endl;
}
