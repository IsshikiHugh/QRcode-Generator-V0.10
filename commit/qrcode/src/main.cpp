/*
 *
 * Qr-code Generator 
 * version 1~2
 * Alphanumeric mode only
 * 2021.9.21
 *  
 */

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

int main(){
    int version;
    char level;
    string input , originalData = " " , bitStream;
    
// 数据读入
// -------------------------------------

    cout << "请输入版本：\n";
    cin >> version;
    cout << "请输入纠错等级：(LMQH)\n";
    cin >> level;
    cout << "请输入您希望 QRcode 应包含的内容：\n";
    // 读入内容;
    getline(cin,input);

// 数据编码
// -------------------------------------

    // 对string类型进行转移和位移，使字符串开头多一个[space]，意义不大
    int len = input.length();
    rep(i,1,len) originalData += input[i-1];
    
    // 得到01数据流（输出字符串形式，从右到左）
    bitStream = encode_make( originalData );
    // 补充长度为 8*n 方便后续切割
    len = bitStream.length();
    rep(i,1,8-(len%8)) bitStream += "0";
    // 填充码字至容量上限
    bitStream += fillCapacity( bitStream , TotalNumber_of_DataCodeWords( version , level ) );

    // 输出01数据流
    // cout << "下面是 version = " << version << " ，level = " << level << " 下 \"" << input << "\" 经过编码后生成的01数据流：\n";
    // len = bitStream.length();
    // rep(i,0,len-1){
    //     cout << bitStream[i];
    //      if(!((i+1)%8)) cout << " ";
    // }cout << "\nOver\n\n";

// 计算纠错码
// -------------------------------------

    a_int ECcode = ECcode_make( bitStream , ECCodewordsPerBlock( version , level ) );

    // 输出纠错码
    // len = ECcode.len;
    // cout << "下面是 version = " << version << " ，level = " << level << " 下 \"" << input << "\" 对应的纠错码：\n";
    // rep(i,0,len-1){
    //     cout << "[#" << i << "]: " << ECcode.a[i] << "\n";
    // }cout << "Over\n\n";

// 填充矩阵
// -------------------------------------

    string combinedData = combine( bitStream , ECcode ); 


// 选择掩码
// -------------------------------------



// 填充格式信息
// -------------------------------------



// 绘图
// -------------------------------------



// -------------------------------------

    return 0;
}