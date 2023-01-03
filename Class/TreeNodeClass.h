#ifndef TREENODECLASS_H
#define TREENODECLASS_H

template< typename compareT, typename contentT >
class TreeNodeClass
{
public:
    TreeNodeClass( compareT pcompareValue, contentT pContentValue, bool pFreeContentFlag )
    {
        mCompareValue = pcompareValue;
        mContentValue = pContentValue;
        mFreeContentFlag = pFreeContentFlag;

        mParentObjP = nullptr;
        mRightChildObjP = nullptr;
        mLeftChildObjP = nullptr;
        mLayer = 0;
    }

    virtual ~TreeNodeClass()
    {
        if( mFreeContentFlag )
        {
            //delete mContentValue;
        }
    }

    /**
     * @brief sub_SetLayer
     * @param pLayer
     */
    void sub_SetLayer( int pLayer )
    {
        mLayer = pLayer;
    }

    /**
     * @brief fun_GetLayer
     * @return
     */
    int fun_GetLayer()
    {
        return mLayer;
    }

public:
    bool GetFreeFlag() { return mFreeContentFlag; }
    compareT GetCompareValue() { return mCompareValue; }

public:
    class TreeNodeClass * mParentObjP;
    class TreeNodeClass * mRightChildObjP;
    class TreeNodeClass * mLeftChildObjP;

private:
    compareT mCompareValue;
    contentT mContentValue;
    bool mFreeContentFlag;
    int mLayer;
};

#endif // TREENODECLASS_H
