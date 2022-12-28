#include "FileDisplayClass.h"

FileDisplayClass::FileDisplayClass( std::string pFilePath )
{
    mFilePath = pFilePath;
    mActiveFlag = false;
}

/**
 * @brief FileDisplayClass::~FileDisplayClass
 */
FileDisplayClass::~FileDisplayClass()
{
    if( mActiveFlag )
    {
        mInFile.close();
    }
}

/**
 * @brief FileDisplayClass::fun_StartFileData
 * @return
 */
bool FileDisplayClass::fun_StartFileData()
{
    bool _retFlag;

    _retFlag = false;

#if XHD_WINDOWS
    std::string _tmpFilePath;

    _tmpFilePath = mFilePath.substr( 1, mFilePath.length() - 1 );
#else
    std::string _tmpFilePath;

    _tmpFilePath = mFilePath;
#endif

    if( !mActiveFlag )
    {
        mInFile.open( _tmpFilePath.c_str(), std::ios::binary );
        if( mInFile )
        {
            mActiveFlag = true;
            _retFlag = true;

            mInFile.seekg( 0, std::ios::end );
            mFileLen = mInFile.tellg();
            mInFile.seekg( 0, std::ios::beg );
            mCurrentPos = 0;
        }
        else
        {
            //TODO:打开失败
            std::cout << "open file error" << std::endl;
        }
    }

    return _retFlag;
}

/**
 * @brief FileDisplayClass::GetData
 * @param pSaveBufP
 * @param pLen
 * @param pDriect
 * @return
 */
int FileDisplayClass::GetData( unsigned char * pSaveBufP, int pLen, int pDriect )
{
    int _retValue;

    _retValue = 0;

    if( mActiveFlag )
    {
        if( mCurrentPos < mFileLen )
        {
            _retValue = mCurrentPos + pLen;
            _retValue = mFileLen - _retValue;
            if( _retValue > 0 )
            {
                if( _retValue > pLen )
                {
                    _retValue = pLen;
                }
            }
            else
            {
                _retValue = mFileLen - mCurrentPos;
            }

            mCurrentPos += _retValue;
        }
        mInFile.read( ( char * )pSaveBufP, pLen );
    }

    return _retValue;
}
