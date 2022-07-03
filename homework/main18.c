#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#if( 1 )
struct LINE
{
    int from , to ;
    int cost ;
};

//
void sortLine2( struct LINE ** lBuf , int E )
{
    int i ;
    struct LINE * tt ;
    int ok ;
    while( E > 1 )
    {
        ok = 0 ;
        for( i = 1 ; i < E ; ++i )
            if( lBuf[i-1]->cost > lBuf[i]->cost )
            {
                tt = lBuf[i-1] ;
                lBuf[i-1] = lBuf[i] ;
                lBuf[i] = tt ;
                ok = 1 ;
            }
        if( ok == 0 )
            return ;
        if(( E % 1000 ) == 0 )
        printf( "e:%d" , E );
        E -- ;
    }
}


//
void sortLine( struct LINE ** lBuf , int E )
{
    int i ;
    struct LINE * tt ;
    int ok ;
    int cost ;
    int sortId ;
    while( E >= 1 )
    {
        ok = 0 ;
        E -- ; 
        cost = lBuf[E]->cost ;
        sortId = E ; 
        for( i = 0 ; i < E ; ++i )
            if( lBuf[i]->cost > cost )
            {
                cost = lBuf[i]->cost ;
                sortId = i ;
    
            }
        // sort
        if( sortId != E )
        {
            tt = lBuf[sortId] ;
            lBuf[sortId] = lBuf[E] ;
            lBuf[E] = tt ;
        }
        if(( E % 100 ) == 0 )
            printf( " e:%d,%d\n" , E , cost );
    }
}
//
void swap( struct LINE ** lBuf , int a , int b ) {
    struct LINE * t = lBuf[a];
    lBuf[a]= lBuf[b];
    lBuf[b] = t ; 
}

void quick_sort_recursive( struct LINE ** lBuf , int start, int end) {
    if (start >= end)
        return;
    int mid = lBuf[end]->cost;
    int left = start, right = end - 1;
    while (left < right) {
        while (lBuf[left]->cost < mid && left < right)
            left++;
        while (lBuf[right]->cost >= mid && left < right)
            right--;
        swap( lBuf , left,  right );
    }
    if (lBuf[left]->cost >= lBuf[end]->cost)
        swap( lBuf , left,  end );
    else
        left++;
    if (left)
        quick_sort_recursive(lBuf, start, left - 1);
    quick_sort_recursive(lBuf, left + 1, end);
}
//
//
long long find( long long * vBuf , int i)
{
    if (vBuf[i]  != i)
        vBuf[i]  = find( vBuf, vBuf[i] );

    return vBuf[i] ;
}


long long Union( long long * vBuf , long long * vCost , int cost  , int x, int y)
{
    int xroot = find(vBuf, x);
    int yroot = find(vBuf, y);

    /*
    if (vCost[xroot] < vCost[yroot] )
    vBuf[xroot]  = yroot;
    else if (vCost[xroot] > vCost[yroot] )
    vBuf[yroot]  = xroot;/
    */
    if( xroot != yroot )
        //  else
    {
        vBuf[yroot] = xroot;
        vCost[xroot] += cost ;
        //    printf( "%d %d %d\n" , x , y , cost );
        return cost ;
    }
    return 0 ;
}


/*
7 9
0 1 28
0 5 10
1 2 16
5 4 25
6 4 24
1 6 14
3 4 22
2 3 12
3 6 18
*/
int main( )
{
    int V , E ;
    int i ;

    struct LINE * lBuf ;
    struct LINE **plBuf ;
    long long *vBuf ;
    long long *vCost ;

    FILE *input = stdin ; //fopen( "testcases\\homework_18\\input_03.txt" , "r" );
	FILE* output = stdout ;//fopen( "testcases\\homework_18\\my_output_01.txt" , "w" );
	int a , b  ;
    long long outCost ;


    //  scanf( "%d %d" , &V , &E );
    fscanf( input , "%d %d" , &V , &E );

    lBuf = (struct LINE*)malloc( sizeof( struct LINE ) * E );
    plBuf = (struct LINE**)malloc( sizeof( struct LINE *) * E );
    // load
    for( i = 0 ; i < E ; ++i )
    {
     //   if(( i % 100 ) == 0 )
     //       printf( "%d\n" , i );
        fscanf( input , "%d %d %d"
            , &a
            , &b
            , &( lBuf + i )->cost );

        //    if( a < b )
        if( 1 )
        {
            ( lBuf + i )->from = a ;
            ( lBuf + i )->to = b ;
        }else
        {
            ( lBuf + i )->from = b ;
            ( lBuf + i )->to = a ;
        }
        plBuf[i] = lBuf + i ;
    }

//    printf( "sortLine\n" , i );
    // sort
  //  sortLine( plBuf , E );
    quick_sort_recursive( plBuf , 0 , E - 1 );
    //
    //
    vBuf = (long long *) malloc( sizeof( long long ) * ( V + 1 ));
    vCost = (long long *) malloc( sizeof( long long ) * ( V + 1 ));

 //   printf( "start\n" , i );


    // init
    for( i = 0 ; i < V ; ++i )
    {
        vBuf[i] = i ;
        vCost[i] = 0 ;
    }
    // run
    outCost = 0 ;
    for( i = 0 ; i < E ; ++i )
        outCost += Union( vBuf , vCost , plBuf[i]->cost , plBuf[i]->from , plBuf[i]->to );
    fprintf( output , "%lld\n" , outCost );
    // end
    free( lBuf );
    free( plBuf );
    free( vBuf );
    free( vCost );

//	system( "pause" );
    return 0;
}


#endif