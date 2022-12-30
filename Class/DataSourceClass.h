#ifndef DATASOURCECLASS_H
#define DATASOURCECLASS_H

#include <iostream>

#include "FileDisplayClass.h"

typedef enum __DataSourceType_e
{
    NothingType = -1,
    FileDataType = 0,
}DataSourceType_e;

class DataSourceClass
{
public:
    DataSourceClass();
    virtual ~DataSourceClass();

    void sub_SetFileDataSource( std::string pPath );
    int GetData( unsigned char * pSaveBufP, int pLen );
    int GetAllDataLen( void );
    DataSourceType_e GetDataSourceType() { return mDataSourceType; }
    void sub_SetDataOffset( int pNewOffset );

private:
    DataSourceType_e mDataSourceType;
    FileDisplayClass * mFileDataObjP;

private:
    void sub_ClearDataSource();
};

#endif // DATASOURCECLASS_H
