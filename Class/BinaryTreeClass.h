#ifndef BINARYTREECLASS_H
#define BINARYTREECLASS_H

#include <list>
#include "./TreeNodeClass.h"

template< typename compareT, typename contentT >
class BinaryTreeClass
{
public:
    BinaryTreeClass()
    {
        mRootObjP = nullptr;
    }
    ~BinaryTreeClass()
    {

    }

    /**
     * @brief sub_CreateTree
     * @param pCompareValueS
     */
    void sub_CreateTree( std::list< compareT > pCompareValueS )
    {
        typename std::list< compareT >::iterator _itm;

        _itm = pCompareValueS.begin();

        for( ; _itm != pCompareValueS.end(); ++_itm )
        {
            if( mRootObjP == nullptr )
            {
                mRootObjP = new TreeNodeClass< compareT, compareT >( *_itm, *_itm, false );
            }
            else
            {
                sub_InsertNode( *_itm, *_itm, false );
            }
        }
    }

    /**
     * @brief sub_InsertNode
     * @param pCompareValue
     * @param pContentValue
     * @param pFreeFlag
     */
    void sub_InsertNode( compareT pCompareValue, contentT pContentValue, bool pFreeFlag )
    {
        TreeNodeClass< compareT, contentT > * _tmpNodeP;

        _tmpNodeP = new TreeNodeClass< compareT, contentT >( pCompareValue, pContentValue, pFreeFlag );

        sub_AddNodeToTree( mRootObjP, _tmpNodeP );
    }

    /**
     * @brief sub_AddNodeToTree
     * @param pParentP
     * @param pDestNodeP
     */
    void sub_AddNodeToTree( TreeNodeClass< compareT, contentT > * pParentP, TreeNodeClass< compareT, contentT > * pDestNodeP )
    {
        TreeNodeClass< compareT, contentT > * _tmpNodeP;

        if( pParentP->GetCompareValue() > pDestNodeP->GetCompareValue() )
        {
            _tmpNodeP = pParentP->mLeftChildObjP;
            if( _tmpNodeP == nullptr )
            {
                pParentP->mLeftChildObjP = pDestNodeP;
                pDestNodeP->mParentObjP = pParentP;
            }
            else
            {
                sub_AddNodeToTree( _tmpNodeP, pDestNodeP );
            }
        }
        else
        {
            _tmpNodeP = pParentP->mRightChildObjP;
            if( _tmpNodeP == nullptr )
            {
                pParentP->mRightChildObjP = pDestNodeP;
                pDestNodeP->mParentObjP = pParentP;
            }
            else
            {
                sub_AddNodeToTree( _tmpNodeP, pDestNodeP );
            }
        }
    }

private:
    TreeNodeClass< compareT, contentT > * mRootObjP;
};

#endif // BINARYTREECLASS_H
