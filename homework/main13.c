
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

//
long long find( int* vBuf , int i )
{
	if( vBuf[i] != i )
		vBuf[i] = find( vBuf , vBuf[i] );

	return vBuf[i];
}


long long Union( int * vBuf , int *vCost , int x , int y )
{
	int xroot = find( vBuf , x );
	int yroot = find( vBuf , y );

	
	if( vCost[xroot] < vCost[yroot] )
		vBuf[xroot] = yroot;
	else if( vCost[xroot] > vCost[yroot] )
		vBuf[yroot] = xroot;

	else if( xroot != yroot )
		//  else
	{
		vBuf[yroot] = xroot;
		vCost[xroot] ++ ;
		//    printf( "%d %d %d\n" , x , y , cost );
		return 1;
	}
	return 0;
}


void run( FILE *file , FILE* output )
{
	char ch[256] ;
	int n ;
	int i ;
	int ops ; 
	int* v;
	int* c;
	int s , t ;


	fscanf( file , "%d %d" , &n , &ops );
	v = (int*) malloc( sizeof( int ) * ( n + 1 ) );
	c = (int*) malloc( sizeof( int ) * ( n + 1 ) );

	memset( c , 0 , sizeof( int ) * ( n + 1 ) );

	for( i = 0 ; i <= n ; ++i )
		v[i] = i ; 
	for( i=  0 ; i < ops ; ++i )
	{
		fscanf( file , "%s" , ch );
		if( strcmp( ch , "union" ) == 0 )
		{
			fscanf( file , "%d %d" , &s , &t );
		//	if( s <= t )
				Union( v , c , s , t );
		//	else
		//		Union( v , t , s );
		}else if( strcmp( ch , "find" ) == 0 )
		{
			fscanf( file , "%d" , &s );
			printf( "%d\n" , find( v , s ) );
			fprintf( output , "%d\n" , find( v , s ) );

		} else if( strcmp( ch , "same" ) == 0 )
		{
			fscanf( file , "%d %d" , &s , &t );
			if( find( v , s ) == find( v , t ))
			{
				printf( "true\n" );
				fprintf( output , "true\n" );
			}else
			{
				printf( "false\n" );
				fprintf( output , "false\n" );
			}
		}
	}
	free( v );
}

int main( int args , const char *argc[] )
{
	int N ; 
	int i ;

	FILE* input = stdin ;//fopen( "testcases\\homework_13\\input_02.txt" , "r" );
	FILE* output = stdout ;//fopen( "testcases\\homework_13\\my_input_02.txt" , "w" );
	fscanf( input , "%d" , &N );
	for( i = 0 ; i < N ; ++i )
	{
		run( input, output );
	}
	return 0 ; 
}