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

matrix apply_mask( matrix output , matrix mask ){
    int size = output.size;
    rep(i,0,size-1) rep(j,0,size-1){
        if(mask.a[i][j] < 0) continue;
        output.a[i][j] ^= mask.a[i][j]; 
    }
    return output;
}

int condition1( matrix m ){
    int ans = 0 , size = m.size , pre , cnt ;
    
    rep(j,0,size-1){
        pre = m.a[0][j] , cnt = 1;
        rep(i,1,size-1){
            if(m.a[i][j] == pre) ++cnt;
            else {
                if(cnt >= 5) ans += cnt-2;
                pre = m.a[i][j] , cnt = 1;
            }
        }
        if(cnt >= 5) ans += cnt-2;
        // cout << ans << "\n";
    }

    rep(i,0,size-1){
        pre = m.a[i][0] , cnt = 1;
        rep(j,1,size-1){
            if(m.a[i][j] == pre) ++cnt;
            else {
                if(cnt >= 5) ans += cnt-2;
                pre = m.a[i][j] , cnt = 1;
            }
        }
        if(cnt >= 5) ans += cnt-2;
        // cout << ans << "\n";
    }

    return ans;
}

int condition2( matrix m ){
    int ans = 0 , size = m.size , color;
    rep(i,0,size-2) rep(j,0,size-2){
        color = m.a[i][j];
        if(
            color == m.a[i+1][j] &&
            color == m.a[i][j+1] &&
            color == m.a[i+1][j+1]
        ) ans += 3;
    }
    // cout << ans << "\n";
    return ans;
}

int condition3( matrix m ){
    int ans = 0 , size = m.size;
    rep(j,0,size-1){
        rep(i,0,size-11){
            if(
                // 00001011101
                m.a[i][j]    == 0 &&
                m.a[i+1][j]  == 0 &&
                m.a[i+2][j]  == 0 &&
                m.a[i+3][j]  == 0 &&
                m.a[i+4][j]  == 1 &&
                m.a[i+5][j]  == 0 &&
                m.a[i+6][j]  == 1 &&
                m.a[i+7][j]  == 1 &&
                m.a[i+8][j]  == 1 &&
                m.a[i+9][j]  == 0 &&
                m.a[i+10][j] == 1
            ) ans += 40;
            else if(
                // 10111010000
                m.a[i][j]    == 1 &&
                m.a[i+1][j]  == 0 &&
                m.a[i+2][j]  == 1 &&
                m.a[i+3][j]  == 1 &&
                m.a[i+4][j]  == 1 &&
                m.a[i+5][j]  == 0 &&
                m.a[i+6][j]  == 1 &&
                m.a[i+7][j]  == 0 &&
                m.a[i+8][j]  == 0 &&
                m.a[i+9][j]  == 0 &&
                m.a[i+10][j] == 0
            ) ans += 40;
        }
    }

    rep(i,0,size-1){
        rep(j,0,size-11){
            if(
                // 00001011101
                m.a[i][j]    == 0 &&
                m.a[i][j+1]  == 0 &&
                m.a[i][j+2]  == 0 &&
                m.a[i][j+3]  == 0 &&
                m.a[i][j+4]  == 1 &&
                m.a[i][j+5]  == 0 &&
                m.a[i][j+6]  == 1 &&
                m.a[i][j+7]  == 1 &&
                m.a[i][j+8]  == 1 &&
                m.a[i][j+9]  == 0 &&
                m.a[i][j+10] == 1
            ) ans += 40;
            else if(
                // 10111010000
                m.a[i][j]    == 1 &&
                m.a[i][j+1]  == 0 &&
                m.a[i][j+2]  == 1 &&
                m.a[i][j+3]  == 1 &&
                m.a[i][j+4]  == 1 &&
                m.a[i][j+5]  == 0 &&
                m.a[i][j+6]  == 1 &&
                m.a[i][j+7]  == 0 &&
                m.a[i][j+8]  == 0 &&
                m.a[i][j+9]  == 0 &&
                m.a[i][j+10] == 0
            ) ans += 40;
        }
    }

    return ans;
}

int condition4( matrix m ){
    int ans , cnt[2] = {0,0} , size = m.size , ppt , upper , lower;
    rep(i,0,size-1) rep(j,0,size-1) ++cnt[ m.a[i][j] ];
    ppt = cnt[1] * 100 / ( cnt[0] + cnt[1] );
    upper = (ppt / 5 + 1),
    lower = (ppt / 5    );
    ans = 10 * std::min( std::abs( 10-upper ) , std::abs( 10-lower ) );

    // 调试
    // cout << "proportion = " << ppt << " , from " << lower << " to " << upper << " , ans = " << ans << "\n";

    return ans;
}

int evaluate( matrix m ){
    int ans = 0 , ans1 = 0 , ans2 = 0 , ans3 = 0 , ans4 = 0;

    ans1 = condition1(m);
    ans2 = condition2(m);
    ans3 = condition3(m);
    ans4 = condition4(m);

    ans = ans1 + ans2 + ans3 + ans4;

    return ans;
}

