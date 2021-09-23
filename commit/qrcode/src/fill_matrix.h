#pragma once
#include "calculate_ECcode.h"

struct matrix{
    int a[64][64];
    int size;
    void initialize(){rep(i,0,31) rep(j,0,31) a[i][j] = -1;}
};

// 用于首尾连接生成最终信息编码的01字符串(左到右)
string combine( string str , a_int a );

// 用于绘制二维码矩阵模板
matrix draw_stencil( int version );

// 用于填充数据
matrix fill_data( matrix m , string data );

void print_matrix( matrix output );