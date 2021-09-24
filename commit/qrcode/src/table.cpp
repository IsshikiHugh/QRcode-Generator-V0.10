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

// 根据版本和纠错等级返回码字容量
int TotalNumber_of_DataCodeWords( int version , char level){
    int n;
    if(version == 1){
        switch(level){
            case 'L':
                n = 19;
                break;
            case 'M':
                n = 16;
                break;
            case 'Q':
                n = 13;
                break;
            case 'H':
                n = 9;
                break;
        }
    } else if(version == 2){
        switch(level){
            case 'L':
                n = 34;
                break;
            case 'M':
                n = 28;
                break;
            case 'Q':
                n = 22;
                break;
            case 'H':
                n = 16;
                break;
        }
    }
    return n;
}

// 根据版本和纠错等级返回需要的纠错码个数
int ECCodewordsPerBlock( int version , char level ){
    if(version == 1){
        switch(level){
            case 'L':
                return 7;
            case 'M':
                return 10;
            case 'Q':
                return 13;
            case 'H':
                return 17;
        }
    } else if(version == 2){
        switch(level){
            case 'L':
                return 10;
            case 'M':
                return 16;
            case 'Q':
                return 22;
            case 'H':
                return 28;
        }
    }
    return -1;
}

// 整数 -> 指数
int Integer_to_Exponent( int x ){
    int map[512] = {
        -1,0,1,25,2,50,26,198,3,223,51,238,27,104,199,75,
        4,100,224,14,52,141,239,129,28,193,105,248,200,8,76,113,
        5,138,101,47,225,36,15,33,53,147,142,218,240,18,130,69,
        29,181,194,125,106,39,249,185,201,154,9,120,77,228,114,166,
        6,191,139,98,102,221,48,253,226,152,37,179,16,145,34,136,
        54,208,148,206,143,150,219,189,241,210,19,92,131,56,70,64,
        30,66,182,163,195,72,126,110,107,58,40,84,250,133,186,61,
        202,94,155,159,10,21,121,43,78,212,229,172,115,243,167,87,
        7,112,192,247,140,128,99,13,103,74,222,237,49,197,254,24,
        227,165,153,119,38,184,180,124,17,68,146,217,35,32,137,46,
        55,63,209,91,149,188,207,205,144,135,151,178,220,252,190,97,
        242,86,211,171,20,42,93,158,132,60,57,83,71,109,65,162,
        31,45,67,216,183,123,164,118,196,23,73,236,127,12,111,246,
        108,161,59,82,41,157,85,170,251,96,134,177,187,204,62,90,
        203,89,95,176,156,169,160,81,11,245,22,235,122,117,44,215,
        79,174,213,233,230,231,173,232,116,214,244,234,168,80,88,175
    };
    return map[x];
}

// 指数 -> 整数
int Exponent_to_Integer( int p ){
    int map[512] = {
        1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,
        76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,
        157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,
        70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,
        95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,
        253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,
        217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,
        129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,
        133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,
        168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,
        230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,
        227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,
        130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,
        81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,
        18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,
        44,88,176,125,250,233,207,131,27,54,108,216,173,71,142,1
    };
    return map[p];
}

// 返回格式信息码
string typeInformationBits( char level , int mode ){
    string output = "" , tmp;
    if(level == 'L'){
        switch (mode){
        case 0:
            tmp = "111011111000100";
            break;
        case 1:
            tmp = "111001011110011";
            break;
        case 2:
            tmp = "111110110101010";
            break;
        case 3:
            tmp = "111100010011101";
            break;
        case 4:
            tmp = "110011000101111";
            break;
        case 5:
            tmp = "110001100011000";
            break;
        case 6:
            tmp = "110110001000001";
            break;
        case 7:
            tmp = "110100101110110";
            break;
        default:
            break;
        }
    } else if(level == 'M'){
        switch (mode){
        case 0:
            tmp = "101010000010010";
            break;
        case 1:
            tmp = "101000100100101";
            break;
        case 2:
            tmp = "101111001111100";
            break;
        case 3:
            tmp = "101101101001011";
            break;
        case 4:
            tmp = "100010111111001";
            break;
        case 5:
            tmp = "100000011001110";
            break;
        case 6:
            tmp = "100111110010111";
            break;
        case 7:
            tmp = "100101010100000";
            break;
        default:
            break;
        }
    } else if(level == 'Q'){
        switch (mode){
        case 0:
            tmp = "011010101011111";
            break;
        case 1:
            tmp = "011000001101000";
            break;
        case 2:
            tmp = "011111100110001";
            break;
        case 3:
            tmp = "011101000000110";
            break;
        case 4:
            tmp = "010010010110100";
            break;
        case 5:
            tmp = "010000110000011";
            break;
        case 6:
            tmp = "010111011011010";
            break;
        case 7:
            tmp = "010101111101101";
            break;
        default:
            break;
        }
    } else if(level == 'H'){
        switch (mode){
        case 0:
            tmp = "001011010001001";
            break;
        case 1:
            tmp = "001001110111110";
            break;
        case 2:
            tmp = "001110011100111";
            break;
        case 3:
            tmp = "001100111010000";
            break;
        case 4:
            tmp = "000011101100010";
            break;
        case 5:
            tmp = "000001001010101";
            break;
        case 6:
            tmp = "000110100001100";
            break;
        case 7:
            tmp = "000100000111011";
            break;
        default:
            break;
        }
    }

    per(i,14,0) output += tmp[i];
    return output;
}

