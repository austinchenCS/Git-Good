#include "codeanalyzer.h"

#define DEBUG false

// No-arg constructor
CodeAnalyzer::CodeAnalyzer()
{
//    this->directoryPathName = '\0';
//    this->outputName = '\0';
    this->finalScore = 0.0;
}

// Parametrized constructor
CodeAnalyzer::CodeAnalyzer(char* pathIn, char* outNameIn)
{
    this->directoryPathName = pathIn;
    this->outputName = outNameIn;
    ifstream fin(this->outputName);
    if (fin) remove(this->outputName);
    this->finalScore = 0.0;
}

// Set final score
void CodeAnalyzer::setFinalScore(double in)
{
    this->finalScore = in;
}

// Get final score
double CodeAnalyzer::getFinalScore()
{
    return this->finalScore;
}

// Analyze function
void CodeAnalyzer::analyze()
{
    // Overall averages for each category
    double commentAverage = 0;
    double lineAverage = 0;
    double classAverage = 0;
    double variableAverage = 0;
    double halsteadAverage = 0;

    if (!DEBUG)
    {
        FileFind directory(this->directoryPathName);
        directory.traverseDir();

        for (int i = 0; i < directory.fileNames.size(); i++)
        {
            String tempString = directory.fileNames[i];

            FileMetrics tempFileMetric(directory.fileNames[i]);
            tempFileMetric.generateMetrics();
            tempFileMetric.calculateScores();

            this->fileScores.add(tempFileMetric.aggregateFileScore);

            generateReport(tempFileMetric);

            // Calculate the overall component metric scores of each metric
            // category
            commentAverage += tempFileMetric.commentData.commentMetricsScore;
            lineAverage += tempFileMetric.lineData.lineMetricsScore;
            classAverage += tempFileMetric.classData.classMetricsScore;
            variableAverage += tempFileMetric.variableData.variableMetricsScore;
            halsteadAverage += tempFileMetric.halsteadData.halsteadMetricsScore;
        }

        // Calculate the final score of the entire code base
        double average = 0.0;

        for (int i = 0; i < this->fileScores.size(); i++)
        {
            average += fileScores[i];
        }

        // Compute the average for everything
        average = average / fileScores.size();
        commentAverage = commentAverage / fileScores.size();
        lineAverage = lineAverage / fileScores.size();
        classAverage = classAverage / fileScores.size();
        variableAverage = variableAverage / fileScores.size();
        halsteadAverage = halsteadAverage / fileScores.size();

        this->finalScore = floor(average);

        // Open the file to append the overall score to the end of the file
        ofstream fout;

        fout.open(this->outputName, ios::app);

        fout << "Overall Codebase Score: " << (int)(round(this->finalScore))
             << " (rounded)" << endl;
        fout << "Overall Line Metrics Score: " << lineAverage << endl;
        fout << "Overall Variable Metrics Score: " << variableAverage  << endl;
        fout << "Overall Class Metrics Score: " << classAverage << endl;
        fout << "Overall Comment Metrics Score: " << commentAverage << endl;
        fout << "Overall Halstead Metrics Score: " << halsteadAverage << endl;

        fout.close();
    }

}

void CodeAnalyzer::generateReport(FileMetrics& allMetrics)
{
    ofstream fout;

    fout.open(this->outputName, ios::app);

    // Print file path:
    fout << "File: " << endl;
    fout << allMetrics.filename << endl;

    fout << endl;
    fout << "FILE SCORE: " << allMetrics.aggregateFileScore << endl;
    fout << "Line Metrics Score: " <<
            allMetrics.lineData.lineMetricsScore << endl;
    fout << "Variable Metrics Score: " <<
            allMetrics.variableData.variableMetricsScore << endl;
    fout << "Class Metrics Score: "
         << allMetrics.classData.classMetricsScore << endl;
    fout << "Comment Metrics Score: "
         << allMetrics.commentData.commentMetricsScore << endl;
    fout << "Halstead Metrics Score: "
         << allMetrics.halsteadData.halsteadMetricsScore << endl;

    fout << endl;
    fout << "Verbose File Details: " << endl;
    fout << "---------------------" << endl;

    fout << endl;
    // Line Metrics
    fout << "LINE METRICS: " << endl;
    fout << "Total number of lines in file: "
         << allMetrics.lineData.numTotalLines << endl;
    fout << "Total lines with C/C++ instruction: "
         << allMetrics.lineData.numLinesOfInstruction << endl;
    fout << "Total whitespace lines: "
         << allMetrics.lineData.numLinesOfWhitespace << endl;
    fout << endl;
    fout << "Ratio of comment lines to total lines of C/C++ instruction: "
         << allMetrics.lineData.ratioCommentsToInstruction << endl;
    fout << "Ratio of comment lines to total lines in file: "
         << allMetrics.lineData.ratioCommentsToTotalFileLines << endl;
    fout << endl;
    fout << allMetrics.lineData.numLinesOver80Chars
         << " line location(s) where line spills over 80 chars: " << endl;
    if (allMetrics.lineData.locLinesOver80Chars.size() > 0)
    {
        for (int j = 0; j < allMetrics.lineData.locLinesOver80Chars.size(); j++)
        {
            fout << "  " << allMetrics.lineData.locLinesOver80Chars[j] << endl;
        }
    }
    else fout << " -None" << endl;

    fout << endl;
    // Variable Metrics
    fout << "VARIABLE METRICS: " << endl;
    fout << "Average variable length: "
         << allMetrics.variableData.getAverageVariableLength() << endl;
    fout << "Median variable length: "
         << allMetrics.variableData.getMedianVariableLength() << endl;

    fout << endl;
    // Class Metrics
    fout << "CLASS METRICS: " << endl;
    fout << allMetrics.classData.locImproperClassNames.size()
         <<" line location(s) where the"
           " class name does not start with a capital letter: " << endl;
    if (allMetrics.classData.locImproperClassNames.size() > 0)
    {
        for (int j = 0; j < allMetrics.classData.locImproperClassNames.size();
             j++)
        {
            fout << allMetrics.classData.locImproperClassNames[j] << endl;
        }
    }
    else fout << "- None" << endl;

    fout << endl;
    // Halstead Metrics
    fout << "HALSTEAD COMPLEXITY METRICS: " << endl;
    fout << "Program Vocabulary: "
         << allMetrics.halsteadData.getProgramVocabulary() << endl;
    fout << "Program Length: "
         << allMetrics.halsteadData.getProgramLength() << endl;
    fout << "Calculated Program Length: "
         << allMetrics.halsteadData.getCalculatedProgramLength() << endl;
    fout << "Volume: " << allMetrics.halsteadData.getVolume() << endl;
    fout << "Difficulty: " << allMetrics.halsteadData.getDifficulty() << endl;
    fout << "Effort: " << allMetrics.halsteadData.getEffort() << endl;
    fout << "Expected time: "
         << allMetrics.halsteadData.getExpectedTime() << " seconds" << endl;
    fout << "Expected bugs: "
         << allMetrics.halsteadData.getExpectedBugs() << endl;

    fout << endl;
    // Comment Metrics:
    fout << "COMMENT METRICS: " << endl;
    fout << allMetrics.commentData.numFullLineCommentsCpp
         << " line location(s) with full line \"//\" style comments: " << endl;
    if (allMetrics.commentData.locFullLineCpp.size() > 0)
    {
        for (int j = 0; j < allMetrics.commentData.locFullLineCpp.size(); j++)
        {
            fout << "  " << allMetrics.commentData.locFullLineCpp[j] << endl;
        }
    }
    else fout << " -None" << endl;

    fout << allMetrics.commentData.numFullLineCommentsC
         << " line location(s) with full line  \"/* */\" style comments: "
         << endl;
    if (allMetrics.commentData.locFullLineC.size() > 0)
    {
        for (int j = 0; j < allMetrics.commentData.locFullLineC.size(); j++)
        {
            fout << "  " << allMetrics.commentData.locFullLineC[j] << endl;
        }
    }
    else fout << " -None" << endl;

    fout << allMetrics.commentData.numInlinedCommentsCpp
         << " line location(s) with inlined \"//\" style comments: " << endl;
    if (allMetrics.commentData.locInlinedCpp.size() > 0)
    {
        for (int j = 0; j < allMetrics.commentData.locInlinedCpp.size(); j++)
        {
            fout << "  " <<  allMetrics.commentData.locInlinedCpp[j] << endl;
        }
    }
    else fout << " -None" << endl;

    fout << allMetrics.commentData.numInlinedCommentsC
         << " line location(s) with inlined  \"/* */\" style comments: "
         << endl;
    if (allMetrics.commentData.locInlinedC.size() > 0)
    {
        for (int j = 0; j < allMetrics.commentData.locInlinedC.size(); j++)
        {
            fout << "  " << allMetrics.commentData.locInlinedC[j] << endl;
        }
    }
    else fout << " -None" << endl;

    fout << allMetrics.commentData.numMultilinedCommentsCpp
         << " line location(s) with multilined \"//\" style comments: " << endl;
    if (allMetrics.commentData.cppMultilinedComments.size() > 0)
    {
        for (int j = 0; j < allMetrics.commentData.cppMultilinedComments.size();
             j++)
        {
            fout << "  ";
            fout << allMetrics.commentData.cppMultilinedComments[j].
                    getFirstLine();
            fout << '-';
            fout << allMetrics.commentData.cppMultilinedComments[j].
                    getLastLine();
            fout << endl;
        }
    }
    else fout << " -None" << endl;

    fout << allMetrics.commentData.numMultilinedCommentsC
         << " line location(s) with multi-line \"/* */\" style comments: "
         << endl;
    if (allMetrics.commentData.cMultilinedComments.size() > 0)
    {
        for (int j = 0; j < allMetrics.commentData.cMultilinedComments.size();
             j++)
        {
            fout << "  ";
            fout << allMetrics.commentData.cMultilinedComments[j].
                    getFirstLine();
            fout << '-';
            fout << allMetrics.commentData.cMultilinedComments[j].
                    getLastLine();
            fout << endl;
        }
    }
    else fout << " -None" << endl;

    fout << "-----------------------------------------"
        "---------------------------------------" << endl;

    fout.close();
}
