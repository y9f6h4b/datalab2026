/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x)|(~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~((~x)&(~y)))&(~(x&y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(x){
        if(y){
            return !((x^y)>>31);
        }
        else{
            return 0;
        }
    }
    else{
        return !y;
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int d4=(v>0xffff)<<4;
    v=v>>d4;
    int d3=(v>0xff)<<3;
    v=v>>d3;
    int d2=(v>0xf)<<2;
    v=v>>d2;
    int d1=(v>3)<<1;
    v=v>>d1;
    int d0=(v>1);
    return d4|d3|d2|d1|d0;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int y=((x>>(n<<3))&0xff)^((x>>(m<<3))&0xff);
    return x^(y<<(n<<3))^(y<<(m<<3));
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned Mask=0xffff;
    for (int i=1;(i-6);i=i+1){
        unsigned n_blk=1u<<i;
        unsigned l_blk=1u<<(5-i);
        unsigned mask=Mask;
        unsigned mask_=~Mask;
        for (unsigned j=0;(j-n_blk);j=j+2){
            mask_=~mask;
            unsigned maask=mask<<l_blk;
            unsigned maask_=~maask;
            unsigned x=(maask&v);
            unsigned y=mask&v;
            v=v&maask_&mask_;
            v=v|(x>>l_blk)|(y<<l_blk);
            mask=(mask<<l_blk)<<l_blk;
            
        }
        Mask=Mask>>(1u<<(4-i));
    }
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int h=!!n;
    int g=(~h+h+h);
    int mask=(1<<(32+(~n+1)))+(~1+1);
    x=x>>n;

    return ((x&mask)&(~g))|(g&x);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int x_=~x;
    int d4=!!(x_&0xffff0000)<<4;
    x_=x_>>d4;
    int d3=!!(x_&0xff00)<<3;
    x_=x_>>d3;
    int d2=!!(x_&0xf0)<<2;
    x_=x_>>d2;
    int d1=!!(x_&12)<<1;
    x_=x_>>d1;
    int d0=!!(x_&2);
    
    return 32+~((d4|d3|d2|d1|d0)+!!(x+1))+1;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if(!x) return 0;
    int sgn=(0x80000000)&x;
    if(sgn) x=-x;
    int log;
    if(x==-2147483648) log=31; else log=logtwo(x);
    
    int e =log+127;
    int m;
    if(log<=23){
        m=(x<<(23-log));
    }
    else{
        int crit=1<<(log-24);
        
        int t=((crit<<1)-1)&x;
        m=x>>(log-23);
        m=m+((t>crit)|((t==crit)&(m&1)));
        if((m&0x1ffffff)==0x1000000) e=e+1;
    }
    return sgn|(e<<23)|(m&(0x7fffff));
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    if((uf&0x7fffffff)==0) return uf;
    int e=(uf&0x7f800000)>>23;
    if(e==0) return ((uf&0x7fffff)<<1)|(uf&0x80000000);
    else if(e==0xff) return uf;
    else return ((e+1)<<23)|(uf&0x807fffff);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int e=(uf2&0x7ff00000)>>20;
    if(e<1023) return 0;
    else if(e>=1054) return 0x80000000;

    e=e-1023;
    int x=(uf2&0x000fffff)|0x00100000;
    int ans;
    if(e<=20) ans= x>>(20-e);
    else {
        int a =e-20;
        int b=32-a;
        ans= (x<<a)|(((uf1&(~((1<<b)-1)))>>b)&((1<<a)-1));
    }
    
    if(uf2&0x80000000) return ~ans+1; else return ans;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
