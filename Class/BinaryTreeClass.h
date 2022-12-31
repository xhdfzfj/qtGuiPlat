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

    }

private:
    TreeNodeClass< compareT, contentT > * mRootObjP;
};

#endif // BINARYTREECLASS_H
