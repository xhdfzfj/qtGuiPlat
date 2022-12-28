#include "DataSourceClass.h"

/**
 * @brief DataSourceClass::DataSourceClass
 */
DataSourceClass::DataSourceClass()
{
    mFileDataObjP = nullptr;
    mDataSourceType = NothingType;
}

/**
 * @brief DataSourceClass::~DataSourceClass
 */
DataSourceClass::~DataSourceClass()
{

}

/**
 * @brief DataSourceClass::sub_SetFileDataSource
 * @param pPath
 */
void DataSourceClass::sub_SetFileDataSource( std::string pPath )
{
    if( mDataSourceType != NothingType )
    {
        sub_ClearDataSource();
    }

    mFileDataObjP = new FileDisplayClass( pPath );
    if( mFileDataObjP->fun_StartFileData() )
    {
        mDataSourceType = FileDataType;
    }
    else
    {
        mDataSourceType = NothingType;
    }
}

/**
 * @brief DataSourceClass::sub_ClearDataSource
 */
void DataSourceClass::sub_ClearDataSource()
{
   if( mDataSourceType == FileDataType )
   {
       delete mFileDataObjP;
       mFileDataObjP = nullptr;
   }
}

/**
 * @brief DataSourceClass::GetData
 * @param pSaveBufP
 * @param pLen
 * @return
 */
int DataSourceClass::GetData( unsigned char * pSaveBufP, int pLen )
{
    int _retValue;

    _retValue = 0;

    if( mDataSourceType == FileDataType )
    {
        _retValue = mFileDataObjP->GetData( pSaveBufP, pLen, 0 );
    }

    return _retValue;
}
