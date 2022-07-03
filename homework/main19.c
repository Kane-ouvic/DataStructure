
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>


#if(1)
struct LINE
{
    int from , to ;
    int cost ;
    unsigned int nowCost; // 目前值
};

struct VEC
{
    int cost ; 
    int bufCount ;
    int bufMax ;
	struct LINE **buf ;
};

// 小的在後
void sortLine2( struct LINE ** lBuf , int E )
{
    int i ;
    struct LINE * tt ;
    while( E > 1 )
    {
        for( i = 1 ; i < E ; ++i )
            if( lBuf[i-1]->nowCost < lBuf[i]->nowCost )
            {
                tt = lBuf[i-1] ;
                lBuf[i-1] = lBuf[i] ;
                lBuf[i] = tt ;
            }
        E -- ;
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
        while (lBuf[left]->cost < mid && left < right) //
            left++;
        while (lBuf[right]->cost >= mid && left < right)//
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
int sortLine( struct LINE ** lBuf , int inStart , int E )
{
    int i, k  ;
    struct LINE * tt ;
    int ok ;
    int sortId ;
    int nowCost ; 
    int ret = 0 ;

    if(( E - inStart ) <= 1 )
        return 1 ; // lBuf[inStart]->nowCost ;
                   // 找最小
    nowCost = lBuf[inStart]->nowCost ;
    for( i = inStart + 1 ; i < E ; ++i )
        if( lBuf[i]->nowCost < nowCost )
        {
            nowCost = lBuf[i]->nowCost ;
            sortId = i ;

        }
    // 小的往前排
    k = inStart ;
    for( i = inStart ; i < E ; ++i )
    {
        if( lBuf[i]->nowCost == nowCost )
        {
            swap( lBuf , i , k );
            k ++ ;
            ret ++ ; 
        }
    }

    return ret ;

    while( E >=( inStart + 1 ))
    {
        ok = 0 ;
        E -- ;
        nowCost = lBuf[E]->nowCost ;
        sortId = E ;
        for( i = inStart ; i < E ; ++i )
            if( lBuf[i]->nowCost > nowCost )
            {
                nowCost = lBuf[i]->nowCost ;
                sortId = i ;

            }
        // sort
        if( sortId != E )
        {
            if(( nowCost == -1 )||( nowCost >= nowCost ))
            {
                nowCost = nowCost ;
                tt = lBuf[sortId] ;
                lBuf[sortId] = lBuf[E] ;
                lBuf[E] = tt ;
            }else 
                return nowCost ; 

        }
        if(( E % 100 ) == 0 )
            printf( " e:%d,%d\n" , E , nowCost );
    }
    return lBuf[inStart]->nowCost ; 
}
//
int find( unsigned int * vBuf , int i)
{
    if (vBuf[i]  != i)
        vBuf[i]  = find( vBuf, vBuf[i] );

    return vBuf[i] ;
}


int Union( unsigned int * vBuf , unsigned int * vCost , int cost  , int x, int y)
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
10
1 2 110
1 3 150
1 4 100
2 5 50
2 6 80
3 7 120
3 8 150
4 9 200
4 10 400
1
*/

int Max( int a , int b )
{
    return a > b ? a : b ;
}

struct LINE *findLine( struct LINE * buf , int pos , int E )
{
    int i ;
    for( i = 0 ; i < E ; ++i )
        if( buf[i].from == pos )
            return buf + i ;
    return NULL ;
}

//
int addTask( struct LINE **plBuf , struct LINE * lBuf , struct VEC *vBuf , int s , int c , int E , int task )
{
    int i ;
    int n ;
	struct LINE * ll ;
    int t ;
    int k ;
	struct VEC *vv = vBuf + s ;
    n = vv->bufCount ;
    for( i = 0 ; i < n ; ++i )
    {
        ll = vv->buf[i] ;
        // 己走過
        if( ll->nowCost )
            continue ; 
        //
        if( ll->from == s )// to 
        {
            t = ll->to ;
        }else 
        {
            t = ll->from ; 
        }
        //
        if( vBuf[t].cost < 0 )
        {
            vBuf[t].cost = ll->nowCost = c + ll->cost ;
            plBuf[task] = ll ;
            task ++ ; 
        }
    }

    return task ;
}

//
void vecAddTo( struct VEC * v , struct LINE * to )
{
	struct  LINE **buf ;
    int n ;
    if( v->bufCount >= v->bufMax )
    {
        buf = v->buf ; 
        v->bufMax += 10 ;
        n = sizeof( struct  LINE * ) * v->bufMax ;
        v->buf = (struct LINE **)malloc( n );
        if( buf != NULL )
        {
            memcpy( v->buf , buf , sizeof( struct LINE * ) * v->bufCount );
            free( buf );
        }

    }
    //
    v->buf[v->bufCount] = to ; 
    v->bufCount ++ ; 
}

//
int main( )
{

    int V , E ;
    int i ;

    struct LINE * lBuf ;
    struct LINE * nowBuf ;
    struct LINE **plBuf ;
	struct  VEC *vBuf ;
  //  int *vCost ;


    /*
    struct LINE  lBuf[1024] = {0} ;
    struct LINE *plBuf[1024] = {0}  ;
    unsigned int vBuf[1024] = {0}  ;
    unsigned int vCost [1024] = {0} ;*/
    int a , b , c  ;
    int s ;
    int outCost ;
    int task ;
    int k , n ; 
    int costBack ;

	// TODO: 
    FILE *input = stdin ;// fopen( "testcases\\homework_19\\input_03.txt" , "r" );
   // FILE *checkFile = fopen( "testcases\\homework_19\\output_03.txt" , "r" );
	FILE* output = stdout ;// fopen( "testcases\\homework_19\\my_output_01.txt" , "w" );


    fscanf( input , "%d" , &E );

    lBuf = (struct LINE*)malloc( sizeof( struct LINE ) * E );
    plBuf = (struct LINE**)malloc( sizeof( struct LINE *) * E );
    V = 0 ;
    // load
    E-- ;
    for( i = 0 ; i < E ; ++i )
    {
        fscanf( input , "%d %d %d"
            , &a
            , &b
            , &( lBuf + i )->cost );

        //    if( a < b )
        ( lBuf + i )->nowCost = 0 ;
        V = Max( V , a );
        V = Max( V , b );
        if( 1 )
        {
            ( lBuf + i )->from = a ;
            ( lBuf + i )->to = b ;
        }else
        {
            ( lBuf + i )->from = b ;
            ( lBuf + i )->to = a ;
        }
    //    if(( i % 100 ) == 0 )
   //         printf( "%d %d\n" , i , E );
        //   plBuf[i] = lBuf + i ;
    }

    // sort
    //  sortLine( plBuf , E );
    //
    //
    V ++ ;
    k = sizeof( struct VEC ) *  ( V + 1 );
    vBuf = (struct VEC *) malloc( k );
    memset( vBuf , 0 , k );
  //  vCost = (int *) malloc( sizeof( int ) * ( V + 1 ));

    // init line
    for( i = 0 ; i < E ; ++i )
    {
        vecAddTo( vBuf +  ( lBuf + i )->from ,  ( lBuf + i ) );
        vecAddTo( vBuf +  ( lBuf + i )->to ,  ( lBuf + i ) );
    }

    // init cost
    for( i = 0 ; i <= V ; ++i )
        vBuf[i].cost = -1 ; 


    // start
    fscanf( input , "%d" , &s );
    // run
    //  task = 1 ;
    //  plBuf[0] = findLine( lBuf , s , E );
    vBuf[s].cost = 0 ;
    task = addTask( plBuf , lBuf , vBuf, s , 0 , E , 0 );
 //  vBuf[0] = s ;

    outCost = 0 ;

    //   while( task > 0 )
    for( i = 0 ; i < task ; ++i )
    {
        costBack =  sortLine( plBuf , i , task );
        n = costBack + i ;
        //  while( task > 0 )
        for( k = i ; k < n ; ++k )
        {
            //   s = vBuf[task] ;
            nowBuf = plBuf[k] ;
            c = nowBuf->nowCost ; //vCost[nowBuf->from] ;
            s = nowBuf->to ;

            i = k ;
            //   task -- ;
            costBack = c; 

            task = addTask( plBuf , lBuf , vBuf ,nowBuf->to , c , E , task );
            task = addTask( plBuf , lBuf , vBuf , nowBuf->from , c , E , task );


        }
   //     printf( "%d %d , cost %d , task %d \n" , i , n , costBack , task);
    }
    // print
    c = 0 ;
    for( i = 1 ; i < V ; ++i )
    {
		fprintf( output , "%d %d\n" , i , vBuf[i].cost );

    }
 //   printf( "err: %d\n" , c );
    // end
	for( i = 0 ;i  < V ; ++i )
		if( vBuf[i].buf != NULL )
			free( vBuf[i].buf );
    free( lBuf );
    free( plBuf );
    free( vBuf );

    return 0;
}

#endif