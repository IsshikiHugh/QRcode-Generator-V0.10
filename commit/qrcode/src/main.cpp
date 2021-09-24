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
const int inf = 1e9+9;
/* -fsanitize=undefined  */

#include "table.h"
#include "encode.h"
#include "calculate_ECcode.h"
#include "fill_matrix.h"
#include "mask.h"

#include "./tool/svpng.inc"

int main(){
    int version;
    char level;
    string input , originalData = " " , bitStream;
    
// 数据读入
// -------------------------------------

    cout << "请输入您希望 QRcode 应包含的内容：\n";
    cout << "[FYA] 您当前仅能输入 { 阿拉伯数字  大写英文字母  [Space]  $  %  +  -  *  /  .  : } 中的内容 \n";
    getline(cin,input);
    int len = input.length() , max_len;
    cout << len << " " << input << "\n";

    bool isLegal = false;
    while(!isLegal){
        cout << "< 请输入您想要的 QRcode 版本 >\n[ 输入 1 或者 2 ]：  ";
        cin >> version;
        cout << "< 请输入您想要的纠错等级 >\n[ 输入 L 或 M 或 Q 或 H ]：  ";
        cin >> level;
        max_len = TotalNumber_of_DataCodeWords( version , level );
        if(max_len < len){
            cout << "[ERROR] 当前版本&纠错等级可储存的信息字节上限为 " << max_len << " ，而待储存信息字节数量为 " << len << " ，已经超过上限，请重新输入！\n";
        } else {
            isLegal = true;
            cout << "[LEGAL] 开始生成二维码。\n";
        }
    }

// 数据编码
// -------------------------------------

    // 对string类型进行转移和位移，使字符串开头多一个[space]，意义不大
    rep(i,1,len) originalData += input[i-1];
    
    // 得到01数据流（输出字符串形式，从右到左）
    bitStream = encode_make( originalData );
    // 补充长度为 8*n 方便后续切割
    len = bitStream.length();
    if( len <= 8*TotalNumber_of_DataCodeWords( version , level ) - 4 ) bitStream += "0000";
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
    if( version == 2 ) combinedData += "0000000";
    matrix qrCodeMatrix = draw_stencil( version );

    // 调试
    // print_matrix(qrCodeMatrix);
    // int size = qrCodeMatrix.size , oo = 0;
    // rep(i,0,size-1) rep(j,0,size-1) if(qrCodeMatrix.a[i][j] == -1) ++oo;
    // cout << oo <<"\n";

    matrix baseMatrix = qrCodeMatrix;
    qrCodeMatrix = fill_data( qrCodeMatrix , combinedData );
    
    // 调试
    // cout << combinedData << "\n";
    // print_matrix(qrCodeMatrix);

// 选择掩码
// -------------------------------------

    baseMatrix = extract_base( baseMatrix );
    matrix qrCodeMatrix_best , qrCodeMatrix_tmp , maskMatrix;
    
    maskMatrix = make_mask( baseMatrix , 0 );
    qrCodeMatrix_tmp = apply_mask( qrCodeMatrix , maskMatrix );
    qrCodeMatrix_tmp.score = evaluate( qrCodeMatrix_tmp );
    qrCodeMatrix_best = qrCodeMatrix_tmp;

    // 调试
    // cout << "0\n";
    // cout << "罚分 " << qrCodeMatrix_tmp.score << "\n";
    // print_matrix(qrCodeMatrix_tmp);

    // print_matrix( make_mask(baseMatrix , 0) );

    rep(i,1,7){
        maskMatrix = make_mask( baseMatrix , i );
        qrCodeMatrix_tmp = apply_mask( qrCodeMatrix , maskMatrix );
        qrCodeMatrix_tmp.mode = i;
        qrCodeMatrix_tmp.score = evaluate( qrCodeMatrix_tmp );

        // 调试
        // cout << i << soutputMatrix);

        if(qrCodeMatrix_best.score > qrCodeMatrix_tmp.score)
            qrCodeMatrix_best = qrCodeMatrix_tmp;
        
        // 调试
        // cout << i << "\n";
        // cout << "罚分 " << qrCodeMatrix_tmp.score << "\n";
        // print_matrix(qrCodeMatrix_tmp);
    }

    // 调试
    // cout << "罚分最少的掩码序号为 " << qrCodeMatrix_best.mode << " 为 " << qrCodeMatrix_best.score << " \n";
    // print_matrix(qrCodeMatrix_best);

    // 得到已经经过掩码处理的矩阵qrCodeMatrix_best

    // qrCodeMatrix_best = apply_mask( qrCodeMatrix , make_mask( baseMatrix , 6 ) );
    // qrCodeMatrix_best.mode = 6;
// 填充格式信息
// -------------------------------------
    string formatString = typeInformationBits( level , qrCodeMatrix_best.mode );
    matrix outputMatrix = fill_formatString( qrCodeMatrix_best , formatString );

    // 调试
    // cout << formatString << "\n";
    print_matrix(outputMatrix);

// 绘图
// -------------------------------------
    
    FILE *fp = fopen("qrcode.png","wb");
    int p = -1 , size_pic = outputMatrix.size;
    unsigned char pic[ 1000010 ] ;
    rep(j,-40,10*size_pic+39) rep(i,-40,10*size_pic+39){
        if(i < 0 || j < 0 || i > 10*size_pic-1 || j > 10*size_pic-1){
            pic[++p] = 255;
            pic[++p] = 255;
            pic[++p] = 255;
        } else if(outputMatrix.a[i/10][j/10]){
            pic[++p] = 0;
            pic[++p] = 0;
            pic[++p] = 0;
        } else {
            pic[++p] = 255;
            pic[++p] = 255;
            pic[++p] = 255;
        }
    }

    svpng(fp , size_pic*10+80 , size_pic*10+80 , pic , 0 );
    fclose(fp);
    system("qrcode.png");

// -------------------------------------

    return 0;
}