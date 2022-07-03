#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PAUSE system( "pause" );

typedef struct _TREE
{
	struct _TREE *_next[4] ;
	int value ;
} TREE , *LPTREE ;

void initTree( LPTREE tree )
{
	memset( tree , 0 , sizeof( TREE ));
}

LPTREE createTree()
{
	LPTREE ret = ( LPTREE)malloc( sizeof( TREE ));
	memset( ret , 0 , sizeof( TREE ) );
	return ret ;
}

LPTREE addValue( FILE *input , LPTREE tree , int N )
{
	int v = 0;
	// 結束
	if( N <= 0 )
	{
		fscanf( input , "%d" , &v );
		tree->value = v ;
		return tree;
	}
	// 讀二個
	if( N > 0 )
		if( fgetc( input ) == '1' )
			v = 1 ;
	N -- ;
	if( N > 0 )
		if( fgetc( input ) == '1' )
			v += 2 ;
	N -- ;
	if( tree->_next[v] == NULL )
	{
		tree->_next[v] = createTree();
	}else if( N <= 0 ) 
	{
		fscanf( input , "%d" , &v );
		return NULL ; 
	}
	return addValue( input , tree->_next[v] , N );
}

//
//
LPTREE findValue( FILE* input , LPTREE tree , int N )
{
	int v = 0;
	// 結束
	if( N <= 0 )
	{
		return tree ;
	}
	// 讀二個
	if( N > 0 )
		if( fgetc( input ) == '1' )
			v = 1;
	N--;
	if( N > 0 )
		if( fgetc( input ) == '1' )
			v += 2;
	N--;
	if( tree->_next[v] == NULL )
	{
		while( N > 0 )
		{
			fgetc( input );
			N--;
		}
		return NULL ;
	}
	return findValue( input , tree->_next[v] , N );
}

//
LPTREE delValue( LPTREE* outTree , FILE* input , LPTREE tree , int N )
{
	int v = 0;
	// 結束
	if( N <= 0 )
	{
		*outTree = tree ;
		return tree;
	}
	// 讀二個
	if( N > 0 )
		if( fgetc( input ) == '1' )
			v = 1;
	N--;
	if( N > 0 )
		if( fgetc( input ) == '1' )
			v += 2;
	N--;
	if( tree->_next[v] == NULL )
	{
		while( N > 0 )
		{
			fgetc( input );
			N -- ; 
		}
		return NULL ; 
	}

	LPTREE dd = delValue( outTree ,  input , tree->_next[v] , N );
	if( dd != NULL )
	{
		tree->_next[v] = NULL ;
	}
	return NULL ; 
}
//
//
int _main( FILE * input , FILE * output )
{
	// 讀 N 的長度
	int N ; 
	char ch[256] ;
	int i , k , ii ;
	fscanf( input , "%d" , &N );
	int vv ;
	LPTREE fValue;
	char c ;

	TREE buf;

	//
	//
	int memlen = ( N / sizeof( int ) + 1 );

	//
	// 
	initTree( &buf );

	if( output != stdout )printf( "N=%d\n" , N );

	//
	// 
	while( 1 )
	{
		if( feof( input ))
			break ; 
		//

		fscanf( input , "%s" , ch );
		c = fgetc( input  );
		// 抓
		k = 0 ;
		ii = 0 ;
		static int iii = 0 ;
		iii ++ ;
		if( output != stdout )printf( "%4d: %s\n" , iii , ch );
		if( strcmp( ch , "insert" ) == 0 )
		{
			
			fValue = addValue( input , &buf , N );
			if( fValue != NULL )
			{
				fprintf( output , "insert -> %d\n" , fValue->value );
			} else
			{
				fprintf( output , "insert -> conflict\n" );
			}
		} else if( strcmp( ch , "search" ) == 0 )
		{
			fValue = findValue( input , &buf , N );
			if( fValue != NULL )
			{
				fprintf( output , "search -> %d\n" , fValue->value );

			} else
			{
				fprintf( output , "search -> not found\n" );
			}
			
		} else if( strcmp( ch , "delete" ) == 0 )
		{
			fValue = NULL ; 
			delValue( &fValue , input , &buf , N );
			if( fValue != NULL )
			{
				fprintf( output , "delete -> %d\n" , fValue->value );
				free( fValue );
			} else
			{
				fprintf( output , "delete -> not found\n" );
			}
		} else if( strcmp( ch , "quit" ) == 0 )
			break;



	}

	return 0 ; 
}

int main( int args , const char **argv )
{
	FILE * input ;
	FILE * output  ;
	int i ;
	char inputFile[1024] ;
	char outputFile[1024];
	{
		input = stdin;
		if( input == NULL )
		{
			printf( "Not Open Input File:%s\n" , inputFile );
			return 0 ;
		}
		output = stdout ;// fopen( outputFile , "w" );
		_main( input , output );
		if( input != stdin ) printf( "... down\n\n" );
	}
	return 0 ; 
}
