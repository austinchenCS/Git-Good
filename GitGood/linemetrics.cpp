#include "linemetrics.h"

#define DEBUG true

using namespace std;

// Default constructor
LineMetrics::LineMetrics()
{
    this->filename = "";
    this->lineMetricsScore = 0;
    this->numTotalLines = 0;
    this->numLinesOfInstruction = 0;
    this->numLinesOfWhitespace = 0;
    this->numLinesOver80Chars = 0;
    this->ratioCommentsToInstruction = 0;
    this->ratioCommentsToTotalFileLines = 0;
    this->ratioCommentsToInstructionOneTo = 0;
    this->ratioCommentsToTotalFileLinesOneTo = 0;
}

// Parametrized constructor
LineMetrics::LineMetrics(String inputFilename)
{
    this->filename = inputFilename;
    this->lineMetricsScore = 0;
    this->numTotalLines = 0;
    this->numLinesOfInstruction = 0;
    this->numLinesOfWhitespace = 0;
    this->numLinesOver80Chars = 0;
    this->ratioCommentsToInstruction = 0;
    this->ratioCommentsToTotalFileLines = 0;
    this->ratioCommentsToInstructionOneTo = 0;
    this->ratioCommentsToTotalFileLinesOneTo = 0;
}

LineMetrics& LineMetrics::operator=(LineMetrics& rhs)
{
    if (this != &rhs)
    {
        this->filename = rhs.filename;

        this->lineMetricsScore = rhs.lineMetricsScore;

        this->numTotalLines = rhs.numTotalLines;
        this->numLinesOfInstruction = rhs.numLinesOfInstruction;
        this->numLinesOfWhitespace = rhs.numLinesOfWhitespace;
        this->numLinesOver80Chars = rhs.numLinesOver80Chars;

        this->ratioCommentsToInstruction = rhs.ratioCommentsToInstruction;
        this->ratioCommentsToTotalFileLines = rhs.ratioCommentsToTotalFileLines;

        this->ratioCommentsToInstructionOneTo
                = rhs.ratioCommentsToInstructionOneTo;
        this->ratioCommentsToTotalFileLinesOneTo
                = rhs.ratioCommentsToTotalFileLinesOneTo;

        this->locLinesOver80Chars = rhs.locLinesOver80Chars;

        return *this;
    }
}

// Scan file
void LineMetrics::scanFile()
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
        // Flags
        bool contentFound = false;

        // Increment line counters
        this->numTotalLines++;

        // Scans the entire line for analytics
        for (int i = 0; i < currLine.size(); i++)
        {
            if (currLine[i] > 32)
            {
                contentFound = true;
                break;
            }
        }

        // If no content is found, the line is whitespace.
        if (!contentFound)
        {
            this->numLinesOfWhitespace++;
        }

        // Check if line length is over 80 characters
        if (currLine.size()-1 > 80)
        {
            this->numLinesOver80Chars++;
            this->locLinesOver80Chars.add(this->numTotalLines);
        }

    }

    // Update the number of lines that contain C/C++ instruction.
    this->numLinesOfInstruction =
            this->numTotalLines - this->numLinesOfWhitespace;

    fin.close();
}

// Public method to calculate ratios
void LineMetrics::calculateRatios(CommentMetrics commentObjIn)
{
    generateRatios(commentObjIn);
    generateRatiosOneTo(commentObjIn);
}

// Update ratios
void LineMetrics::generateRatios(CommentMetrics commentObjIn)
{
    int sumCommentLines = 0;

    sumCommentLines += commentObjIn.getNumFullLineCommentsCpp();
    sumCommentLines += commentObjIn.getNumFullLineCommentsC();
    sumCommentLines += commentObjIn.getCppMultilinedCommentsTotalSpan();
    sumCommentLines += commentObjIn.getCMultilinedCommentsTotalSpan();

    if (sumCommentLines == 0 || this->numLinesOfInstruction == 0)
    {
        this->ratioCommentsToInstruction = 0;
    }

    else
    {
        this->ratioCommentsToInstruction = (double)sumCommentLines
                / (double)this->numLinesOfInstruction;
    }

    if (sumCommentLines == 0 || this->numTotalLines == 0)
    {
        this->ratioCommentsToTotalFileLines = 0;
    }

    else
    {
        this->ratioCommentsToTotalFileLines = (double)sumCommentLines
                / (double)this->numTotalLines;
    }
}

// Update ratios
void LineMetrics::generateRatiosOneTo(CommentMetrics commentObjIn)
{
    int sumCommentLines = 0;

    sumCommentLines += commentObjIn.getNumFullLineCommentsCpp();
    sumCommentLines += commentObjIn.getNumFullLineCommentsC();
    sumCommentLines += commentObjIn.getCppMultilinedCommentsTotalSpan();
    sumCommentLines += commentObjIn.getCMultilinedCommentsTotalSpan();

    this->ratioCommentsToInstructionOneTo =
            (double)this->numLinesOfInstruction / (double)sumCommentLines;
    this->ratioCommentsToTotalFileLinesOneTo =
            (double)this->numTotalLines / (double)sumCommentLines;
}

// Calculate score
void LineMetrics::calculateScore()
{
    double score = 0.0;

    if (this->ratioCommentsToInstruction < 0.2)
    {

        if (this->ratioCommentsToInstruction > 0.15)
        {
            double penalty = (0.20 - (this->ratioCommentsToInstruction));
            penalty *= 100;
            score += penalty;
        }

        else
        {
            double penalty = (0.20 - (this->ratioCommentsToInstruction));
            penalty *= 100;
            score += (penalty*2);
        }

    }

    if (this->numLinesOver80Chars > 0)
    {
        double ratio = ((double)this->numLinesOver80Chars
                        / (double)this->numTotalLines);
        ratio *= 100;
        score += ratio;
    }

    this->lineMetricsScore = score;
}

// Debug
void LineMetrics::debug()
{
    cout << "Total lines in file: "
         << this->numTotalLines << endl;

    cout << "Total whitespace lines: "
         << this->numLinesOfWhitespace << endl;

    cout << "Total lines with C/C++ instruction: "
         << this->numLinesOfInstruction << endl << endl;

    cout << "Ratio of comment lines to total lines of C/C++ instruction: "
         << this->ratioCommentsToInstruction << endl;

    cout << "Ratio of comment lines to total lines in file: "
         << this->ratioCommentsToTotalFileLines << endl << endl;

    cout << "Ratio of comment lines to total lines of C/C++ instruction: "
         << endl
         << "1 full comment line per " << this->ratioCommentsToInstructionOneTo
         << " lines of C/C++ instruction" << endl;

    cout << "Ratio of comment lines to total lines in file: "
         << endl
         << "1 full comment line per "
         << this->ratioCommentsToTotalFileLinesOneTo
         << " lines in file" << endl;


    cout << endl;

    cout << this->numLinesOver80Chars
         << " line location(s) where line spills over 80 chars: " << endl;
    if (this->locLinesOver80Chars.size() > 0)
    {
        for (int i = 0; i < this->locLinesOver80Chars.size(); i++)
        {
            cout << "  " << this->locLinesOver80Chars[i] << endl;
        }
    }
    else cout << " -None" << endl;

    cout << endl;

}
