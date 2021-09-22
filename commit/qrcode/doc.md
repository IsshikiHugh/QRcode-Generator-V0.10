## `table.h`

- 该模块内函数主要用于各种已经预先处理好的表或变换规则的查询与变换

------

### `(int)` `TotalNumber_of_DataCodeWords( int version , char level )`

该函数读取两个参数 `(int)version` , `(char)level` ，分别表示qrcode的版本和纠错等级。

将返回规则下该版和纠错等级的qrcode的字码数量上限

------

### `(int)` `ECCodewordsPerBlock( int version , char level )`

该函数读取两个参数 `(int)version` , `(char)level` ，分别表示qrcode的版本和纠错等级。

将返回规则下该版和纠错等级的qrcode所需的纠错码数量

------

### `(int)` `Integer_to_Exponent( int x )`

该函数读取一个参数 `(int)x` ，表示需要转换为指数系数的十进制系数

将返回用 `alpha^p` 表示 `GF(256)` 中元素时 十进制数x 对应的 指数p

------

### `(int)` `Exponent_to_Integer( int p )`

该函数读取一个参数 `(int)p` ，表示需要转换为十进制系数的指数系数

将返回用 `alpha^p` 表示 `GF(256)` 中元素时 `alpha^p` 表示的 十进制数x

------

## `encode.h`

- 该模块主要用于实现字符信息传化为01数据流

------

### `(string)` `encode_make( string msg )`

该函数读取一个参数 `(string)msg` ，表示需要处理的信息字符串

将返回一个按照规则编码的 string 类型的 01数据流，且**最低位在最右侧**

------

### `(string)` `decimal_to_binary( int num , int size )`

该函数读取两个参数 `(int)num` , `(int)size` ，表示 十进制数num 将要被转化为 size位二进制数

将返回一个 string 类型的 01字符串，表示 十进制数num 的二进制表示,且**最低位在最右侧**

------

### `(string)` `fillCapacity( string str , int n )`

该函数读取两个参数 `(string)str` , `(int)n` ，表示要 01数据流str 补足到n字节，后面所要添的字符串

将返回一个 string 类型的 01数据流，表示需要补足在 str 之后的 01字符串

------

## `calculate_ECcode.h`

- 该模块用于生成纠错码
- 该模块下定义如下的结构体：
> ```cpp 
> struct a_int{
>     int a[1024];
>     int len;
> };
> ```

------

### `a_int` `ECcode_make( string bitStream , int num_of_ECcode)`

该函数读取两个参数 `(string)bitStream` , `(int)num_of_ECcode` ，表示要计算 01数据流bitStream 的 num_of_ECcode个纠错码

返回一个 a_int 类型的结构体，其中 `cur.len = num_of_ECcode` 且 `cur.a[0] ~ cur.a[ cur.len - 1 ]` 依次表示从小到大的若干纠错码

------

### `int` `alpha_mul( int x , int y )`

该函数读取两个参数 `(int)x` , `(int)y` ，表示计算 alpha^x 和 alpha^y 的乘积的指数系数

返回一个 int 类型的整数，表示乘积的指数系数

------

### `int` `alpha_plus( int x , int y )`

该函数读取两个参数 `(int)x` , `(int)y` ，表示计算 alpha^x 和 alpha^y 的和的指数系数

返回一个 int 类型的整数，表示和的指数系数

------

### `a_int` `makeMessagePolynomial(string str)`

该函数读取一个参数 `(string)str` ，表示要将 01数据流（最低位在最右侧） 转化为信息码

返回一个 a_int 类型的结构体，其中 `cur.a[0] ~ cur.a[ cur.len - 1 ]` 依次表示信息码多项式系数

------

### `a_int` `a_int_mul(a_int x,a_int y)`

该函数读取两个参数 `(a_int)x` , `(a_int)y` ，表示要对这两个结构体对应的多项式进行域内乘法运算

返回一个 a_int 类型的结构体，其中 `cur.a[i]` 表示运算结果多项式中 x^i 项的指数系数

------

### `a_int` `makeGeneratorPolynomial(int n)`

该函数读取一个参数 `(int)n` ，表示要生成一个 n次生成码多项式

返回一个 a_int 类型的结构体，其中 `cur.len = n+1` , `cur.a[i]` 表示生成码多项式中 x^i 项的指数系数

------

### `a_int` `a_int_mod( a_int x , a_int y )`

该函数读取两个参数 `(a_int)x` , `(a_int)y` ，表示要取 (多项式x) / (多项式y) 的余

返回一个 a_int 类型的结构体，其中 `cur.a[i]` 表示余式里 x^i 项的指数系数

------

### `a_int` `a_int calculateECcode( a_int x , a_int y )`

该函数读取两个参数 `(a_int)x` , `(a_int)y` ，表示要计算 M(p) = x , G(p) = y 的里德-所罗门码

返回一个 a_int 类型的结构体，其中 `cur.a[i]` 表示生成的里所码中 x^i 项的指数系数

------