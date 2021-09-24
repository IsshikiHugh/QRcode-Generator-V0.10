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
using std::map;
inline bool cmp(int x,int y){return x < y;}
/* -fsanitize=undefined  */
map<char,int> mp;

#include "table.h"

// 字符内容转数字编码
void initialize(){
    // 数字部分
    rep(i,0,9) mp[ '0'+i ] = i;
    //alpha
    rep(i,0,25) mp[ 'A'+i ] = i+10;
    //special
    mp[' '] = 36 , mp['$'] = 37 , mp['%'] = 38 ,
    mp['*'] = 39 , mp['+'] = 40 , mp['-'] = 41 ,
    mp['.'] = 42 , mp['/'] = 43 , mp[':'] = 44 ;
    return;
}

// 给出数字num和二进制位数size，输出size位num的二进制字符串
string decimal_to_binary( int num , int size ){
    int len = 0;
    char ch[16] = {};
    string ans = "";
    while(num){
        ch[ ++len ] = '0' + num%2;
        num >>= 1;
    }
    rep(i,len+1,size) ch[i] = '0';
    per(i,size,1) ans += ch[i];
    return ans;
}

// 按照规则将信息转码，返回01数据流
string encode( string str ){
    int tmp[64] = {};
    int len = str.length() - 1;

    if(len % 2){
        rep(i,1,len/2) tmp[i] =  mp[ str[ 2*i-1 ] ] * 45 + mp[ str[ 2*i ] ];
        tmp[ len/2+1 ] = -mp[ str[len] ];
        tmp[0] = len/2+1;
    } else {
        rep(i,1,len/2) tmp[i] =  mp[ str[ 2*i-1 ] ] * 45 + mp[ str[ 2*i ] ];
        tmp[0] = len/2;
    }

    string output = "";

    rep(i,1,tmp[0]){
        if(tmp[i] > 0) output += decimal_to_binary(tmp[i],11);
        else output += decimal_to_binary(-tmp[i],6);
    }

    return output;
}

string encode_make( string msg ){
    // 实现 混合字符串 到 01数据流(字符串形式，从右到左)
    initialize();
    string str = "";
    str = decimal_to_binary( msg.length()-1 , 9);
    string product = "0010" + str + encode(msg);
    return product;
}

string fillCapacity( string str , int n ){
    int now = str.length() / 8;
    string more = "";
    rep(i,1,n-now){
        if(i%2) more += "11101100";
        else more += "00010001";
    }
    return more;
}
