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

#include "fill_matrix.h"

matrix extract_base( matrix m ){
    matrix output;
    int size = output.size = m.size;
    output.initialize();
    rep(i,0,size-1) rep(j,0,size-1){
        if(m.a[i][j] < 0) output.a[i][j] = 0;
    }
    return output;
}

matrix make_mask( matrix m , int mode ){
    int size = m.size;
    if(mode == 0){
        rep(i,0,size-1) rep(j,0,size-1){
            if((i+j) % 2 == 0 && m.a[i][j] == 0) m.a[i][j] = 1;
        }
    } else if(mode == 1){
        rep(i,0,size-1) rep(j,0,size-1){
            if(j % 2 == 0 && m.a[i][j] == 0) m.a[i][j] = 1;
        }
    } else if(mode == 2){
        rep(i,0,size-1) rep(j,0,size-1){
            if(i % 3 == 0 && m.a[i][j] == 0) m.a[i][j] = 1;
        }
    } else if(mode == 3){
        rep(i,0,size-1) rep(j,0,size-1){
            if((i+j) % 3 == 0 && m.a[i][j] == 0) m.a[i][j] = 1;
        }
    } else if(mode == 4){
        rep(i,0,size-1) rep(j,0,size-1){
            if((i/3+j/2) % 2 == 0 && m.a[i][j] == 0) m.a[i][j] = 1;
        }
    } else if(mode == 5){
        rep(i,0,size-1) rep(j,0,size-1){
            if((i*j) % 2 + (i*j) % 3 == 0 && m.a[i][j] == 0) m.a[i][j] = 1;
        }
    } else if(mode == 6){
        rep(i,0,size-1) rep(j,0,size-1){
            if( ((i*j)%2 + (i*j)%3) % 2 == 0 && m.a[i][j] == 0) m.a[i][j] = 1;
        }
    } else if(mode == 7){
        rep(i,0,size-1) rep(j,0,size-1){
            if( ((i+j)%2 + (i*j)%3) % 2 == 0 && m.a[i][j] == 0) m.a[i][j] = 1;
        }
    }
    return m;
}

int score_mask( matrix mask , matrix qrcode ){
    int ans = 0;

    return ans;
}

