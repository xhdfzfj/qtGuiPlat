#ifndef FILEDISPLAYCLASS_H
#define FILEDISPLAYCLASS_H

#include <iostream>


class FileDisplayClass
{
public:
    FileDisplayClass( std::string pFilePath );
    ~FileDisplayClass();

    bool fun_StartFileData();

private:
    std::string mFilePath;
};

#endif // FILEDISPLAYCLASS_H
