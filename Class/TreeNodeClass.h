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
    }

    virtual ~TreeNodeClass()
    {
        if( mFreeContentFlag )
        {
            delete mContentValue;
        }
    }

public:
    class TreeNodeClass * mParentObjP;
    class TreeNodeClass * mRightChildObjP;
    class TreeNodeClass * mLeftChildObjP;

private:
    compareT mCompareValue;
    contentT mContentValue;
    bool mFreeContentFlag;
};

#endif // TREENODECLASS_H
