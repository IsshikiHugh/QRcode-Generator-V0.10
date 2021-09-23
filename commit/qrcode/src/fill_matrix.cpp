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

string combine( string str , a_int a ){
    string output;
    int len = str.length();
    per(i,len-1,0) output += str[i];
    rep(i,0,a.len-1){
        str = decimal_to_binary(a.a[i],8);
        per(i,7,0) output += str[i];
    }
    cout << output.length() << ' ' << output << "\n";
    return output;
}