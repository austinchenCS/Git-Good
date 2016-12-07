#ifndef FILEFIND_H
#define FILEFIND_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

#include "DSString.h"
#include "Vector.h"

class FileFind
{
public:
    FileFind();
    FileFind(String);
    void traverseDir();
    String getBeginPath();
    void printVec();
    Vector<String> fileNames;

private:
    String beginPath;
    //Vector<String> fileNames;
    void traverseDir(char*,String);
};

#endif // FILEFIND_H
