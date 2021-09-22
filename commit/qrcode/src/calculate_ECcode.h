struct a_int{
    int a[1024];
    int len;
};

// 生成纠错码
a_int ECcode_make( string bitStream , int num_of_ECcode);

// 域内指数参数乘法
int alpha_mul(int x,int y);

// 域内指数参数加法
int alpha_plus(int x,int y);

// 读取 右到左的01数据流 返回 信息码多项式的指数系数
a_int makeMessagePolynomial(string str);

// 指数系数多项式乘法（每项系数原值不为0）
a_int a_int_mul(a_int x,a_int y);

// 读取 纠错码数量 返回 纠错码多项式指数系数
a_int makeGeneratorPolynomial(int n);

// 取 多项式x 除以 多项式y 的余数
a_int a_int_mod( a_int x , a_int y );

// 计算 M(x) = x , G(x) = y 的里所码
a_int calculateECcode( a_int x , a_int y );