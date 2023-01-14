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

public:
    bool GetFreeFlag() { return mFreeContentFlag; }
    compareT GetCompareValue() { return mCompareValue; }
    contentT GetContentValue() { return mContentValue; }
    int GetLayer()  { return mLayer; }

    /**
     * @brief GetParent
     * @return
     */
    TreeNodeClass< compareT, contentT > * GetParent()
    {
        TreeNodeClass< compareT, contentT > * _retP;

        _retP = mParentObjP;

        return _retP;
    }

    /**
     * @brief JudgeLeftOrRight
     * @param pChildP
     * @return
     *         1 左子
     *         2 右子
     */
    int JudgeLeftOrRight( TreeNodeClass< compareT, contentT > * pChildP )
    {
        int _retValue;

        _retValue = 0;

        if( mLeftChildObjP == pChildP )
        {
            _retValue = 1;
        }
        else if( mRightChildObjP == pChildP )
        {
            _retValue = 2;
        }

        return _retValue;
    }

    bool IsLeafNode()
    {
        bool _retFlag;

        _retFlag = false;
        if( ( mRightChildObjP == nullptr ) && ( mLeftChildObjP == nullptr ) )
        {
            _retFlag = true;
        }

        return _retFlag;
    }

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
