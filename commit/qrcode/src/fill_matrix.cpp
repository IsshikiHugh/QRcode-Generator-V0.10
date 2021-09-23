#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define per(i,a,b) for(int i = (a);i >= (b);--i) 
#define mkp std::make_pair
typedef long long ll;
typedef unsigned long long ull;
using std::string;using std::cin;using std::cout;
inline bool cmp(int x,int y){return x < y;}
/* -fsanitize=undefined  */

#include "table.h"
#include "encode.h"
#include "calculate_ECcode.h"
#include "fill_matrix.h"

void print_matrix( matrix output ){
    // 调试用
    rep(j,0,output.size-1) rep(i,0,output.size-1){
        if(output.a[i][j] == 1) cout << "■ ";
        else if(output.a[i][j] == 0) cout << "□ ";
        else cout << "x ";
        if(i == output.size-1 ) cout << "\n";
    }
}

string combine( string str , a_int a ){
    string output;
    int len = str.length();
    per(i,len-1,0) output += str[i];
    rep(i,0,a.len-1){
        str = decimal_to_binary(a.a[i],8);
        per(i,7,0) output += str[i];
    }
    // cout << output.length() << ' ' << output << "\n";
    return output;
}

matrix draw_finderPatterns( matrix m ){
    int map_MP[8][8] = {
        {1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1},
        {1,0,1,1,1,0,1},
        {1,0,1,1,1,0,1},
        {1,0,1,1,1,0,1},
        {1,0,0,0,0,0,1},
        {1,1,1,1,1,1,1}
    };
    
    rep(i,0,6) rep(j,0,6) m.a[            i ][            j ] = map_MP[i][j];
    rep(i,0,6) rep(j,0,6) m.a[            i ][ m.size-7 + j ] = map_MP[i][j];
    rep(i,0,6) rep(j,0,6) m.a[ m.size-7 + i ][            j ] = map_MP[i][j];
    return m;
}

matrix draw_separators( matrix m ){
    int size = m.size;
    rep(i,0,7){
        m.a[i][7] = 0 ,
        m.a[i][ size-8 ] = 0 ,
        m.a[ size-8 + i ][7] = 0 ;
    }
    rep(j,0,6){
        m.a[7][j] = 0 , 
        m.a[ size-8 ][j] = 0 ,
        m.a[7][ size-7 + j ] = 0 ; 
    }
    return m;
}

matrix draw_timingPatterns( matrix m ){
    int size = m.size;
    rep(i,0,size-17) m.a[ i+8 ][6] = (i+1) % 2;
    rep(j,0,size-17) m.a[6][ j+8 ] = (j+1) % 2;
    return m; 
}

matrix draw_alignmentPattern( matrix m ){
    // 只能绘制 version 2
    int map_AP[8][8] = {
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,1,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1},
    };

    rep(i,0,4) rep(j,0,4) m.a[ i + 16 ][ j + 16 ] = map_AP[i][j];
    return m;
}

matrix draw_stencil( int version ){
    matrix output;
    output.initialize();

    output.size = (version - 1) * 4 + 21;
    
    // 绘制定位标志
    output = draw_finderPatterns( output );

    // 绘制隔离模块
    output = draw_separators( output );

    // 绘制定时标志
    output = draw_timingPatterns( output );

    // 绘制校正标志
    if(version != 1) output = draw_alignmentPattern( output );

    return output; 
}

matrix fill_data( matrix m , string data ){
    int size = m.size;
    
    // 黑点码元
    m.a[8][ size-8 ] = 1;

    return m;
}