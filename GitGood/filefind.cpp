#include "filefind.h"

using namespace std;

FileFind::FileFind()
{
    this->beginPath = "";
}

FileFind::FileFind(String dir)
{
//    char buffer[2000];

//    ifstream myFile(textFile.c_str());

//    if (myFile.is_open())
//    {
//        myFile.getline(buffer,2000);
//    }
//    myFile.close();

//    this->beginPath = buffer;
    this->beginPath = dir;
}

void FileFind::traverseDir()
{
    traverseDir(this->beginPath.c_str(),".cpp");
    traverseDir(this->beginPath.c_str(),".c");
    traverseDir(this->beginPath.c_str(),".hpp");
    traverseDir(this->beginPath.c_str(),".h");
}

void FileFind::traverseDir(char* begin, String extension)
{
    if(DIR* pointOfEntry = opendir(begin))
    {
        while (struct dirent* entry = readdir(pointOfEntry))
        {
            if (entry->d_type == DT_DIR && entry->d_name[0] != '.')
            {
                //String fileName = entry->d_name;
                String newDir = entry->d_name;
                String parent = begin;
                newDir = parent + "/" + newDir;
                traverseDir(newDir.c_str(), extension);
            }
            else if (entry->d_type == DT_REG)
            {

                String fileName = entry->d_name;
                char* buffer = new char[PATH_MAX+1];

                fileName = fileName.substring(fileName.size() -
                                              extension.size(),
                                              fileName.size());
                if (fileName == extension)
                {
                    String tempStr = begin;
                    String file = entry->d_name;
                    tempStr = tempStr + "/" + file;
                    this->fileNames.add(tempStr);
                }
                delete[] buffer;
            }
        }
        closedir(pointOfEntry);
    }

    return;
}

String FileFind::getBeginPath()
{
    return beginPath;
}

void FileFind::printVec()
{
    for (int i = 0; i < this->fileNames.size(); i++)
    {
        cout << this->fileNames[i] << endl;
    }
}
