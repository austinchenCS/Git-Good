#ifndef CLASSMETRICS_H
#define CLASSMETRICS_H

#include <fstream>
#include "Vector.h"
#include "DSString.h"
#include "DSHashtable.h"

class ClassMetrics
{
private:
    String filename;

public:
    double classMetricsScore;

    int numImproperClassNames;
    Vector<int> locImproperClassNames;

public:
    // Constructors
    ClassMetrics();
    ClassMetrics(String inputFilename);

    // Overloaded assignment operator
    ClassMetrics& operator=(ClassMetrics& rhs);

    // Public function
    void scanFile(HashTable<int, bool> commentLocationsIn);

    void scanClassNames();
    void removeFalsePositives(HashTable<int, bool> commentLocationsIn);
    void calculateScore();

    // Debug
    void debug();


};

#endif // CLASSMETRICS_H
