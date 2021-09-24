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
        else if(output.a[i][j] == 2) cout << "# ";
        else cout << "o ";
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
    len = output.length();
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

    int size = output.size;
    // 黑点码元
    output.a[8][ size-8 ] = 1;

    // 预留格式信息
    rep(i,0,8) if(output.a[i][8] < 0) output.a[i][8] = 2;
    rep(j,0,7) if(output.a[8][j] < 0) output.a[8][j] = 2;
    rep(i,0,7) if(output.a[ size-8 + i ][8] < 0) output.a[ size-8 + i ][8] = 2;
    rep(j,0,6) if(output.a[8][ size-7 + j ] < 0) output.a[8][ size-7 + j ] = 2; 

    return output; 
}

std::pair< int , std::pair<int,int> > next_position( int x , int y , int now , int size){
    int map_NP[4][2] = { {-1,0} , {1,-1} , {-1,0} , {1,1} };
    int map_N[4] = { 1,0,3,2 };

    if(y == 0 && now == 1){
        if(x == 7) x = 5;
        else x = x-1;
        now = 2;
    } else if(y == size-1 && now == 3){
        x = x-1 , now = 0;
    } else {
        x += map_NP[now][0],
        y += map_NP[now][1];
        now = map_N[now];
    }

    return mkp( now , mkp(x,y) );
}

matrix place_data( matrix m , string data ){
    int x , y , now = 0 , size = m.size , len = data.length();
    std::pair< int , std::pair<int,int> > v;
    
    // now 的说明
    // [3] ← [2] ← [1] ← [0]
    //     ↘          ↗ 
    // [3] ← [2]   [1] ← [0]
    //     ↘          ↗ 
    // [3] ← [2]   [1] ← [0]
    //     ↘          ↗     

    x = y = size - 1;
    rep(i,0,len-1){
        
        // 调试
        // cout << i << " " << now << " " << x << " " << y << "\n";

        if(m.a[x][y] < 0) m.a[x][y] = data[i] - '0';
        else --i;
        v = next_position( x , y , now , size);
        now = v.first , x = v.second.first , y = v.second.second;
    }
    return m;
}

matrix fill_data( matrix m , string data ){
    int size = m.size;

    // 填充数据
    m = place_data( m , data );

    // print_matrix(m);

    return m;
}

matrix fill_formatString( matrix m , string str ){
    int size = m.size;

    rep(i,0,5) m.a[i][8] = str[i] -'0';
    m.a[7][8] = str[6] -'0' ,
    m.a[8][8] = str[7] -'0' ,
    m.a[8][7] = str[8] -'0' ;
    rep(j,9,14) m.a[8][14-j] = str[j] -'0';

    rep(j,0,6) m.a[8][size-1-j] = str[j] - '0';
    rep(i,7,14) m.a[size-15+i][8] = str[i] - '0';

    return m;
}

