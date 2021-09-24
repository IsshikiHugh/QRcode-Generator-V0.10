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
#include "calculate_ECcode.h"

// struct a_int{
//     int a[1024];
//     int len;
// };

// 域内乘法
int alpha_mul(int x,int y){
    return (x+y)%255;
}

// 域内加法
int alpha_plus(int x,int y){
    int realVal = Exponent_to_Integer(x) ^ Exponent_to_Integer(y);
    return Integer_to_Exponent(realVal);
}

// 返回信息码（指数系数）
a_int makeMessagePolynomial(string str){
    a_int output;
    int len = str.length() , cur , a[512];
    per(i,len-1,0) a[ ++a[0] ] = str[i] - '0';
    output.len = len/8;
    rep(i,0,output.len-1){
        cur = 0;
        per(j,8,1){
            cur = cur*2 + a[i*8+j];
        }
        output.a[i] = Integer_to_Exponent(cur);
    }
    return output;
}

// 指数系数多项式乘法（每项系数至少为1）
a_int a_int_mul(a_int x,a_int y){
    a_int ans;
    ans.len = x.len + y.len - 1;
    rep(i,0,ans.len-1) ans.a[i] = -1;
    rep(i,0,ans.len-1){
        rep(j,0,i){
            // 防爆
            if(j >= x.len || (i-j) >= y.len) continue;
            if(ans.a[i] < 0){
                ans.a[i] = alpha_mul(x.a[j] , y.a[i-j]);
            } else {
                ans.a[i] = alpha_plus( ans.a[i] , alpha_mul(x.a[j] , y.a[i-j]) );
            }
        }
    }
    return ans;
}

// 返回生成码（指数系数）
a_int makeGeneratorPolynomial(int n){
    a_int base , x;
    base.len = x.len = 2;
    rep(i,0,base.len-1) base.a[i] = 0;
    rep(i,0,x.len-1) x.a[i] = 0;
    
    rep(i,1,n-1){
        x.a[0] = i;

        base = a_int_mul(base,x);
        
        // cout << "debug:\n";
        // rep(i,0,base.len-1) cout << base.a[i] << " ";
        // cout << "\n";
        // rep(i,0,x.len-1) cout << x.a[i] << " ";
        // cout << "\nover\n";
    }
    return base;
}

// 指数系数多项式取余
a_int a_int_mod( a_int x , a_int y ){
    a_int ans;
    int tmp , top = x.len-1 , m = y.len - 1;
    ans.len = m;
    per(i,top,m){
        tmp = x.a[i];
        rep(j,1,m){
            if(x.a[i-j] < 0) x.a[i-j] = alpha_mul( tmp , y.a[m-j] );
            else x.a[i-j] = alpha_plus( x.a[i-j] , alpha_mul( tmp , y.a[m-j] ) );
        }
        // cout << i << "\n";
        // rep(i,0,m) cout << x.a[i] << " ";
        // cout << "\n";
    }
    
    // rep(i,0,m-1) cout << x.a[i] << " ";
    // cout << "\n";

    rep(i,0,m-1) ans.a[i] = x.a[i];
    return ans;
}

// 计算纠正码
a_int calculateECcode( a_int x , a_int y ){
    a_int X;
    int m = y.len - 1;
    X.len = x.len + m;
    rep(i,0,x.len-1) X.a[i+m] = x.a[i];
    rep(i,0,m-1) X.a[i] = -1;

    // cout << "now print x：\n";
    // per(i,x.len-1,0){
    //     cout << x.a[i] << " ";
    // }cout << "\nOver\n";
    
    // cout << "now print X：\n";
    // per(i,X.len-1,0){
    //     cout << X.a[i] << " ";
    // }cout << "\nOver\n";

    // cout << "now print y：\n";
    // per(i,y.len-1,0){
    //     cout << y.a[i] << " ";
    // }cout << "\nOver\n";

    return a_int_mod(X,y);
}

// 生成纠错码
a_int ECcode_make( string bitStream , int num_of_ECcode ){
    a_int ECcode_alpha , messagePol , generatorPol , ECcode;
    // 信息码
    messagePol = makeMessagePolynomial(bitStream);

    // cout << bitStream << "\n";
    // cout << "\n";
    // rep(i,0,messagePol.len-1) cout << ( messagePol.a[i] ) << " ";
    // cout << "\n";

    // 生成码
    generatorPol = makeGeneratorPolynomial(num_of_ECcode);
    
    // cout << "\n";
    // rep(i,0,generatorPol.len-1) cout << ( generatorPol.a[i] ) << " ";
    // cout << "\n";
    
    // 纠错码（指数系数）
    ECcode_alpha = calculateECcode( messagePol , generatorPol);
    ECcode.len = ECcode_alpha.len;

    rep(i,0,ECcode_alpha.len-1) ECcode.a[i] = Exponent_to_Integer(ECcode_alpha.a[i]);

    return ECcode;
}
