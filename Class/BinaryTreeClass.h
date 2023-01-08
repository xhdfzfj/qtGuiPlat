#ifndef BINARYTREECLASS_H
#define BINARYTREECLASS_H

#include <list>
#include <stack>
#include <iostream>
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
        if( !mLayerElementS.empty() )
        {
            mLayerElementS.clear();
        }
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

    /**
     * @brief fun_GetTreeHeight
     * @return
     *      返回树的高度
     */
    int fun_GetTreeHeight()
    {
        int _retValue;
        int _tmpCurrLayer;
        int _tmpMaxLayer;
        std::stack< TreeNodeClass< compareT, contentT > * > _tmpStack;
        TreeNodeClass< compareT, contentT > * _tmpNodeP;

        _retValue = 0;

        _tmpNodeP = mRootObjP;
        if( _tmpNodeP != nullptr )
        {
            _tmpCurrLayer = 1;
            _tmpMaxLayer = _tmpCurrLayer;
            _tmpNodeP->sub_SetLayer( _tmpCurrLayer );
            _tmpStack.push( _tmpNodeP );

            std::cout << "node " << _tmpNodeP->GetCompareValue() << " ";
            while( !_tmpStack.empty() )
            {
                if( _tmpNodeP->mLeftChildObjP == nullptr )
                {
                    _tmpNodeP = _tmpStack.top();
                    _tmpStack.pop();
                    _tmpCurrLayer = _tmpNodeP->fun_GetLayer();

                    _tmpNodeP = _tmpNodeP->mRightChildObjP;
                    while( ( _tmpNodeP == nullptr ) && ( !_tmpStack.empty() ) )
                    {
                        _tmpNodeP = _tmpStack.top();
                        _tmpStack.pop();
                        _tmpCurrLayer = _tmpNodeP->fun_GetLayer();

                        _tmpNodeP = _tmpNodeP->mRightChildObjP;
                    }
                }
                else
                {
                    _tmpNodeP = _tmpNodeP->mLeftChildObjP;
                }

                if( _tmpNodeP != nullptr )
                {
                    _tmpCurrLayer += 1;
                    _tmpNodeP->sub_SetLayer( _tmpCurrLayer );
                    if( _tmpCurrLayer > _tmpMaxLayer )
                    {
                        _tmpMaxLayer = _tmpCurrLayer;
                    }
                    _tmpStack.push( _tmpNodeP );
                    std::cout << "node " << _tmpNodeP->GetCompareValue() << " ";
                }
            }

            _retValue = _tmpMaxLayer;
        }
        std::cout << std::endl;

        return _retValue;
    }

    /**
     * @brief sub_ReadyTransferLayer
     * 准务进行层的遍历
     * @param pLayer
     * 目标层数
     */
    void sub_ReadyTransferLayer( int pLayer )
    {
        int _tmpCurrLayer;

        if( !mLayerElementS.empty() )
        {
            mLayerElementS.clear();
        }

        if( mRootObjP == nullptr )
        {
            return;
        }

        if( pLayer == 1 )
        {
            mLayerElementS.push_back( mRootObjP );
            return;
        }

        std::list< TreeNodeClass< compareT, contentT > * > _tmpList;
        std::list< TreeNodeClass< compareT, contentT > * > _tmpSaveList;
        TreeNodeClass< compareT, contentT > * _tmpNodeP;
        TreeNodeClass< compareT, contentT > * nodeP;

        _tmpNodeP = mRootObjP->mLeftChildObjP;
        if( _tmpNodeP != nullptr )
        {
            _tmpList.push_back( _tmpNodeP );
        }
        _tmpNodeP = mRootObjP->mRightChildObjP;
        if( _tmpNodeP != nullptr )
        {
            _tmpList.push_back( _tmpNodeP );
        }

        _tmpCurrLayer = 2;

        while( !_tmpList.empty() )
        {
            if( _tmpCurrLayer == pLayer )
            {
                mLayerElementS = std::list< TreeNodeClass< compareT, contentT > * >( _tmpList.begin(), _tmpList.end() );
                break;
            }
            else
            {
                _tmpCurrLayer += 1;
                _tmpSaveList.clear();
                typename std::list< TreeNodeClass< compareT, contentT > * >::iterator _tmpIte;
                _tmpIte = _tmpList.begin();
                for( ; _tmpIte != _tmpList.end(); ++_tmpIte )
                {
                    nodeP = *_tmpIte;
                    _tmpNodeP = nodeP->mLeftChildObjP;
                    if( _tmpNodeP != nullptr )
                    {
                        _tmpSaveList.push_back( _tmpNodeP );
                    }
                    _tmpNodeP = nodeP->mRightChildObjP;
                    if( _tmpNodeP != nullptr )
                    {
                        _tmpSaveList.push_back( _tmpNodeP );
                    }
                }
                _tmpList.clear();
                if( !_tmpSaveList.empty() )
                {
                    _tmpList = std::list< TreeNodeClass< compareT, contentT > * >( _tmpSaveList.begin(), _tmpSaveList.end() );
                }
            }
        }
    }

    /**
     * @brief fun_GetLayerElementS
     * @return
     */
    std::list< TreeNodeClass< compareT, contentT > * > fun_GetLayerElementS()
    {
       return  mLayerElementS;
    }

private:
    TreeNodeClass< compareT, contentT > * mRootObjP;
    std::list< TreeNodeClass< compareT, contentT > * > mLayerElementS;
};

#endif // BINARYTREECLASS_H
