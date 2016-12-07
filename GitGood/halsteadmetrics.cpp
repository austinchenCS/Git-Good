#include "halsteadmetrics.h"

// Default constructor
HalsteadMetrics::HalsteadMetrics()
{
    this->filename = "";
    this->halsteadMetricsScore = 0;
    this->n1 = 0;
    this->n2 = 0;
    this->N1 = 0;
    this->N2 = 0;
    this->programVocabulary = 0;
    this->programLength = 0;
    this->calculatedProgramLength = 0;
    this->volume = 0;
    this->difficulty = 0;
    this->effort = 0;
    this->expectedTime = 0;
    this->expectedBugs = 0;
}

// Parametrized constructor
HalsteadMetrics::HalsteadMetrics(String inputFilename)
{
    this->filename = inputFilename;
    this->halsteadMetricsScore = 0;
    this->n1 = 0;
    this->n2 = 0;
    this->N1 = 0;
    this->N2 = 0;
    this->programVocabulary = 0;
    this->programLength = 0;
    this->calculatedProgramLength = 0;
    this->volume = 0;
    this->difficulty = 0;
    this->effort = 0;
    this->expectedTime = 0;
    this->expectedBugs = 0;
}

// Overloaded assignment operator
HalsteadMetrics& HalsteadMetrics::operator=(HalsteadMetrics& rhs)
{
    this->filename = rhs.filename;

    this->halsteadMetricsScore = rhs.halsteadMetricsScore;

    this->n1 = rhs.n1;
    this->n2 = rhs.n2;
    this->N1 = rhs.N1;
    this->N2 = rhs.N2;

    this->programVocabulary = rhs.programVocabulary;
    this->programLength = rhs.programLength;
    this->calculatedProgramLength = rhs.calculatedProgramLength;
    this->volume = rhs.volume;
    this->difficulty = rhs.difficulty;
    this->effort = rhs.effort;
    this->expectedTime = rhs.expectedTime;
    this->expectedBugs = rhs.expectedBugs;

    return *this;
}

// Public scan file metric
void HalsteadMetrics::scanFile(HashTable<int, bool> commentLinesIn)
{
    this->isCommentLine = commentLinesIn;
    findOperators();
    findOperands();
    updateMetrics();
}

// Find operands; unique and total
void HalsteadMetrics::findOperands()
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
                           "(double[* ]*)([a-zA-Z0-9_]+)|"
                           "long|short|signed|unsigned|void";

    smatch m;
    regex reg1(searchPattern);

    string lineTemp;
    int lineNum = 0;

    AvlTree<string> uniqueOperands;
    int numUniqueOperands = 0;
    Vector<int> operandLocations;

    // Find all operators
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
                    operandLocations.add(lineNum);
                    found = true;
                    iTemp = i;
                    break;
                }
            }

            if (found)
            {
                if (!uniqueOperands.contains(m[iTemp]))
                {
                    uniqueOperands.insert(m[iTemp]);
                    numUniqueOperands++;
                }

                if (!uniqueOperands.contains(m[iTemp+1]))
                {
                    uniqueOperands.insert(m[iTemp+1]);
                    numUniqueOperands++;
                }
            }

            lineTemp = m.suffix().str();
        }
    }
    lineNum--;

    // Remove operators where the line is a comment
    for (int i = 0; i < lineNum; i++)
    {
        if (this->isCommentLine[i])
        {
            operandLocations.remove(i);
        }
    }

    // Set operator values (unique and total number)
    this->n2 = numUniqueOperands;
    this->N2 = operandLocations.size();

    fin.close();
}

// Find all operators
void HalsteadMetrics::findOperators()
{
    ifstream fin(this->filename.c_str());

    if (!fin)
    {
        cerr << "error: Files(s) could not be opened!" << endl;
    }

    string searchPattern = "auto|extern|register|static|typedef|virtual|"
                           "mutable|inline|"
                           "const|friend|volatile|final|"
                           "break|case|continue|default|do|if|else|enum|for|"
                           "goto|if|new|return|asm|operator|private|protected|"
                           "public|sizeof|struct|switch|union|while|this|"
                           "namespace|using|try|catch|throw|abstract|concrete|"
                           "const_cast|static_cast|dynamic_cast|"
                           "reinterpret_cast|typeid|template|explicit|true|"
                           "false|typename|"
                           "[=][=]|[=][&]|[=]|[!][=]|[!]|[%][=]|[%]|[&][&]|"
                           "[&][=]|[&]|[|][|]|[|][=]|[|]|[(]|[)]|[{]|[}]|[[]|"
                           "[\\]]|[*][=]|[*]|[+][=]|[+][+]|[+]|[,]|[-][-]|"
                           "[-][=]|[-][>]|[-]|[.][.][.]|[.]|[/][=]|[/]|[:][:]|"
                           "[:]|[<][<][=]|[>][>][=]|[<][<]|[<][=]|[<]|[=]|"
                           "[>][=]|[>][>]|[>]|[?]|[\\^][=]|[\\^]|[~]|[;]|"
                           "[#][#]|[\']|[\"]|[#][#]|[#]";

    smatch m;
    regex reg1(searchPattern);

    string lineTemp;
    int lineNum = 0;

    AvlTree<string> uniqueOperators;
    int numUniqueOperators = 0;
    Vector<int> operatorLocations;

    // Find all operators
    while (!fin.eof())
    {
        lineNum++;
        getline(fin, lineTemp);

        while (regex_search(lineTemp, m, reg1))
        {
            if (!uniqueOperators.contains(m[0]))
            {
                uniqueOperators.insert(m[0]);
                numUniqueOperators++;
            }
            operatorLocations.add(lineNum);
            lineTemp = m.suffix().str();
        }
    }
    lineNum--;

    // Remove operators where the line is a comment
    for (int i = 0; i < lineNum; i++)
    {
        if (this->isCommentLine[i])
        {
            operatorLocations.remove(i);
        }
    }

    // Set operator values (unique and total number)
    this->n1 = numUniqueOperators;
    this->N1 = operatorLocations.size();

    fin.close();
}

// Update metrics
void HalsteadMetrics::updateMetrics()
{
    // Set program vocabulary
    this->programVocabulary = this->n1 + this->n2;

    // Set program length
    this->programLength = this->N1 + this->N2;

    // Set calculated program length
    if (this->n1 == 0 && this->n2 == 0)
    {
        this->calculatedProgramLength = 0;
    }

    else if (this->n1 == 0)
    {
        this->calculatedProgramLength = log2((double)this->n2)*(double)this->n2;
    }

    else if (this->n2 == 0)
    {
        this->calculatedProgramLength = log2((double)this->n1)*(double)this->n1;
    }

    else
    {
        this->calculatedProgramLength = log2((double)this->n1)*(double)this->n1
                + log2((double)this->n2)*(double)this->n2;
    }

    // Set volume
    if (this->programVocabulary > 0)
    {
        this->volume = (double)this->programLength *
            log2((double)this->programVocabulary);
    }

    else
    {
        this->volume = 0;
    }

    // Set difficulty
    if (this->N2 == 0 || this->n2 == 0)
    {
        this->difficulty = ((double)this->n1/2) * 1;
    }

    else
    {
        this->difficulty = ((double)this->n1/2) *
                ((double)this->N2/(double)this->n2);
    }

    // Set effort
    this->effort = this->volume * this->difficulty;

    // Set expected time
    this->expectedTime = this->effort/18;

    // Set expected bugs
    this->expectedBugs = (pow(this->effort, 0.666666))/3000;
}

// Calculate score
void HalsteadMetrics::calculateScore()
{

    if (this->difficulty == 0 || this->effort == 0 || this->volume == 0)
    {
        this->halsteadMetricsScore = 0.0;
    }
    else
    {
        this->halsteadMetricsScore = log2(this->effort);
    }

}

// Get pathname
String HalsteadMetrics::getFilename()
{
    return this->filename;
}

// Get distinct operators
int HalsteadMetrics::getDistinctOperators()
{
    return this->n1;
}

// Get distinct operands
int HalsteadMetrics::getDistinctOperands()
{
    return this->n2;
}

// Get total operators
int HalsteadMetrics::getTotalOperators()
{
    return this->N1;
}

// Get total operands
int HalsteadMetrics::getTotalOperands()
{
    return this->N2;
}

// Get program vocabulary
int HalsteadMetrics::getProgramVocabulary()
{
    return this->programVocabulary;
}

// Get program length
int HalsteadMetrics::getProgramLength()
{
    return this->programLength;
}

// Get calculated program length
double HalsteadMetrics::getCalculatedProgramLength()
{
    return this->calculatedProgramLength;
}

// Get volume
double HalsteadMetrics::getVolume()
{
    return this->volume;
}

// Get difficulty
double HalsteadMetrics::getDifficulty()
{
    return this->difficulty;
}

// Get effort
double HalsteadMetrics::getEffort()
{
    return this->effort;
}

// Get expected time
double HalsteadMetrics::getExpectedTime()
{
    return this->expectedTime;
}

// Get expected bugs
double HalsteadMetrics::getExpectedBugs()
{
    return this->expectedBugs;
}

// Set filename
void HalsteadMetrics::setFilename(String in)
{
    this->filename = in;
}

// Set distinct operators
void HalsteadMetrics::setDistinctOperators(int in)
{
    this->n1 = in;
}

// Set distinct operands
void HalsteadMetrics::setDistinctOperands(int in)
{
    this->n2 = in;
}

// Set total operators
void HalsteadMetrics::setTotalOperators(int in)
{
    this->N1 = in;
}

// Set total operands
void HalsteadMetrics::setTotalOperands(int in)
{
    this->N2 = in;
}

// Set program vocabulary
void HalsteadMetrics::setProgramVocabulary(int in)
{
    this->programVocabulary = in;
}

// Set program length
void HalsteadMetrics::setProgramLength(int in)
{
    this->programLength = in;
}

// Set calculated program length
void HalsteadMetrics::setCalculatedProgramLength(double in)
{
    this->calculatedProgramLength = in;
}

// Set volume
void HalsteadMetrics::setVolume(double in)
{
    this->volume = in;
}

// Set difficulty
void HalsteadMetrics::setDifficulty(double in)
{
    this->difficulty = in;
}

// Set effort
void HalsteadMetrics::setEffort(double in)
{
    this->effort = in;
}

// Set expected time
void HalsteadMetrics::setExpectedTime(double in)
{
    this->expectedTime = in;
}

// Set expected bugs
void HalsteadMetrics::setExpectedBugs(double in)
{
    this->expectedBugs = in;
}












