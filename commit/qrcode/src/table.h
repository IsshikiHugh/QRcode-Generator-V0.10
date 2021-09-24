#pragma once

#include<iostream>
using std::string;

// 根据版本和纠错等级返回码字容量
int TotalNumber_of_DataCodeWords( int version , char level );

// 根据版本和纠错等级返回需要的纠错码个数
int ECCodewordsPerBlock( int version , char level );

// 整数 -> 指数
int Integer_to_Exponent( int x );

// 指数 -> 整数
int Exponent_to_Integer( int p );

// 返回格式信息码(左到右)
string typeInformationBits( char level , int mode );