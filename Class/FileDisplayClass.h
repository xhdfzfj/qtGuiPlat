#ifndef FILEDISPLAYCLASS_H
#define FILEDISPLAYCLASS_H

#include <cstddef>
#include <iostream>
#include <fstream>

class FileDisplayClass
{
public:
    FileDisplayClass( std::string pFilePath );
    ~FileDisplayClass();

    bool fun_StartFileData();
    int GetData( unsigned char * pSaveBufP, int pLen, int pDriect );

private:
    std::string mFilePath;
    std::ifstream mInFile;
    bool mActiveFlag;

    int mFileLen;
    int mCurrentPos;
};

#endif // FILEDISPLAYCLASS_H
