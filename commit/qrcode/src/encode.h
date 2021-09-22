#include<cstring>
using std::string;

// 按照规则进行 信息 -> 01数据流(字符串，右到左)
string encode_make( string msg );

// 十进制转二进制(字符串，右到左)
string decimal_to_binary( int num , int size );

// 根据版本和纠错等级补充位数
string fillCapacity( string str , int n );