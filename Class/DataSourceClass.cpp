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
