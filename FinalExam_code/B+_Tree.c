#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX 3

typedef struct _NODE{

    int IS_LEAF;
    int key[MAX];
    int del[MAX];
    int size;
    struct _NODE* ptr[MAX+1];
} NODE;

NODE* root = NULL;


NODE* newNode(){

    NODE* ret = (NODE *)malloc(sizeof(NODE));
    return ret;
}

int search(int x, NODE** outNode, int* outPos){

    *outNode = NULL;
    if(root == NULL){
        //
    } else {
        NODE* cursor = root;
        while(cursor->IS_LEAF == FALSE){
            for(int i = 0; i < cursor->size; i++){
                if(x < cursor->key[i]){
                    cursor = cursor->ptr[i];
                    break;
                }
                if(i == cursor->size - 1){
                    cursor = cursor->ptr[i+1];
                    break;
                }
            }
        }
        for(int i = 0; i < cursor->size; i++){
            if(cursor->key[i] == x){
                *outNode = cursor;
                *outPos = i;
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

int delValue(NODE* node, int value){

    NODE* cursor = node;
    if(node == NULL){
        return 1;
    }
    for(int i = 0; i < cursor->size; i++){
        int vv;
        vv = cursor->key[i];
        if(vv == value){
            if(cursor->del[i] == 0){
                cursor->del[i] = 1;
            }
        }
        if(i == cursor->size - 1){
            if(cursor->ptr == NULL){
                break;
            }
            if(delValue(cursor->ptr[i+1], value)){
                return 1;
            }
            cursor = cursor->ptr[i+1];
            if(cursor == NULL){
                return 1;
            }
        }
    }
    return 0;
}

void range_search( FILE *output , NODE* node , int ll , int rr )
{

	NODE* ppBuf[1024] = { 0 };
	int bbCount = 0;
	NODE* cursor = node;

	if( cursor == NULL )
		return;
	while( cursor->IS_LEAF == FALSE )
	{
		for( int i = 0; i < cursor->size; i++ )
		{
			int vv = cursor->key[i];
			if( ll < cursor->key[i] )
			{
				ppBuf[bbCount] = cursor;
				bbCount++;
				cursor = cursor->ptr[i];

				break;
			}
			if( i == cursor->size - 1 ) {
				ppBuf[bbCount] = cursor;
				bbCount++;
				cursor = cursor->ptr[i + 1];
				break;
			}


		}
	}
	if( cursor == NULL )
		return;
	ppBuf[bbCount] = cursor;
	bbCount++;
	printNode( output , cursor , 0 , ll , rr );
	return;
	for( bbCount; bbCount > 0; )
	{
		bbCount--;
		cursor = ppBuf[bbCount];
		for( int i = 0; i < cursor->size; i++ )
		{
			int vv;
			vv = cursor->key[i];
			if( ( vv >= ll ) && ( vv <= rr ) )
				if( cursor->del[i] == 0 )
				{
					printf( "%d " , vv );

				}
			if( i == cursor->size - 1 ) {
				i = 0;
				if( bbCount == 0 )
					i = 0;
				if( cursor->ptr[0] == NULL )
				{
					break;
				}
				if( cursor->key[i] == 23 )
					vv = vv;
				if( ( vv >= ll ) && ( vv <= rr ) )
					if( cursor->del[i] == 0 )
					{
						printf( "%d " , vv );
					}
				cursor = cursor->ptr[i + 1];
				if( cursor == NULL )
					break;
			}
		}
	}
}

void insert( int x )
{

	if( root == NULL ) {
		root = newNode();
		root->key[0] = x;
		root->IS_LEAF = TRUE;
		root->size = 1;
	}

	else {
		NODE* cursor = root;
		NODE* parent = NULL;

		while( cursor->IS_LEAF	== FALSE ) {

			parent = cursor;

			for( int i = 0;	i < cursor->size;i++ ) {
				if( x < cursor->key[i] ){
					cursor = cursor->ptr[i];
					break;
				}
				if( i == cursor->size - 1 ) {
					cursor = cursor->ptr[i + 1];
					break;
				}
			}
		}

		if( cursor->size < MAX ) {
			int i = 0;
			while( x > cursor->key[i] && i < cursor->size ) {
				i++;
			}

			for( int j = cursor->size; j > i; j-- ){
				cursor->key[j] = cursor->key[j - 1];
			}
			cursor->key[i] = x;
			cursor->size++;
			cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
			cursor->ptr[cursor->size - 1] = NULL;
		}  else {
			NODE* newLeaf = newNode();
			int virtualNode[MAX + 1];
			for( int i = 0; i < MAX; i++ ) {				
                virtualNode[i] = cursor->key[i];
			}
			int i = 0 , j;

			while( x > virtualNode[i] && i < MAX ) {
				i++;
			}

			for( int j = MAX + 1;j > i; j-- ) {
				virtualNode[j] = virtualNode[j - 1];
			}

			virtualNode[i] = x;
			newLeaf->IS_LEAF = TRUE;

			cursor->size = ( MAX + 1 ) / 2;
			newLeaf->size = MAX + 1 - ( MAX + 1 ) / 2;

			cursor->ptr[cursor->size] = newLeaf;

			newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
			cursor->ptr[MAX] = NULL;

			for( i = 0;	 i < cursor->size; i++ ) {
				cursor->key[i] = virtualNode[i];
			}

			for( i = 0 , j = cursor->size;	i < newLeaf->size;i++ , j++ ) {
				newLeaf->key[i]	= virtualNode[j];
			}

			if( cursor == root ) {

				NODE* newRoot = newNode();

				newRoot->key[0] = newLeaf->key[0];
				newRoot->ptr[0] = cursor;
				newRoot->ptr[1] = newLeaf;
				newRoot->IS_LEAF = FALSE;
				newRoot->size = 1;
				root = newRoot;
			} else {
				insertInternal(newLeaf->key[0],parent ,newLeaf );
			}
		}
	}
}

void insertInternal( int x ,NODE* cursor ,NODE* child ){

	if( cursor->size < MAX ) {
		int i = 0;

		while( x > cursor->key[i] && i < cursor->size ) {
			i++;
		}

		for( int j = cursor->size; j > i; j--) {
			cursor->key[j] = cursor->key[j - 1];
		}

		for( int j = cursor->size + 1; j > i + 1; j-- ) {
			cursor->ptr[j] = cursor->ptr[j - 1];
		}
		cursor->key[i] = x;
		cursor->size++;
		cursor->ptr[i + 1] = child;
	} else {

		NODE* newInternal = newNode();
		int virtualKey[MAX + 1];
		NODE* virtualPtr[MAX + 2];

		for( int i = 0; i < MAX; i++ ) {
			virtualKey[i] = cursor->key[i];
		}

		for( int i = 0; i < MAX + 1; i++ ) {
			virtualPtr[i] = cursor->ptr[i];
		}

		int i = 0 , j;

		while( x > virtualKey[i] && i < MAX ) {
			i++;
		}

		for( int j = MAX + 1; j > i; j-- ) {
			virtualKey[j] = virtualKey[j - 1];
		}

		virtualKey[i] = x;

		for( int j = MAX + 2; j > i + 1; j-- ) {
			virtualPtr[j] = virtualPtr[j - 1];
		}

		virtualPtr[i + 1] = child;
		newInternal->IS_LEAF = FALSE;

		cursor->size = ( MAX + 1 ) / 2;

		newInternal->size = MAX - ( MAX + 1 ) / 2;

		for( i = 0 , j = cursor->size + 1;i < newInternal->size; i++ , j++ ) {
			newInternal->key[i] = virtualKey[j];
		}

		for( i = 0 , j = cursor->size + 1; i < newInternal->size + 1;i++ , j++ ) {
			newInternal->ptr[i] = virtualPtr[j];
		}

		if( cursor == root ) {

			NODE* newRoot = newNode();
			newRoot->key[0] = cursor->key[cursor->size];
			newRoot->ptr[0] = cursor;
			newRoot->ptr[1] = newInternal;
			newRoot->IS_LEAF = FALSE;
			newRoot->size = 1;
			root = newRoot;
		} else {
			insertInternal( cursor->key[cursor->size] ,findParent(root ,cursor ), newInternal);
		}
	}
}

NODE* findParent( NODE* cursor ,NODE* child ){

    NODE* parent = NULL;
	if( cursor->IS_LEAF || ( cursor->ptr[0] )->IS_LEAF ) {
		return NULL;
	}

	for( int i = 0; i < cursor->size + 1; i++ ) {
		if( cursor->ptr[i] == child ) {
			parent = cursor;
			return parent;
		} else {
			parent = findParent( cursor->ptr[i] ,child );
			if( parent != NULL ) return parent;
		}
	}

	return parent;
}