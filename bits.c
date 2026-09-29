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
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
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
    if (!x && !y) return 1;
    else if (x && y) return !((x ^ y) >> 31);
    else return 0;
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
    int x;
    int r = 0;

    x = ((v >> 16) > 0) << 4;
    r = r | x;
    v = v >> x;

    x = ((v >> 8) > 0) << 3;
    r = r | x;
    v = v >> x;

    x = ((v >> 4) > 0) << 2;
    r = r | x;
    v = v >> x;

    x = ((v >> 2) > 0) << 1;
    r = r | x;
    v = v >> x;

    x = (v >> 1) > 0;
    return r | x;
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
    int na = n << 3;
    int ma = m << 3;
    int nb = (x >> na) & 0xFF;
    int mb = (x >> ma) & 0xFF;
    int c = nb ^ mb;

    return x ^ ((c << na) | (c << ma));
    
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
    unsigned x = 0;
    int i = 32;
    while(i){
        x = (x << 1) | (v & 1);
        v = v >> 1;
        i -= 1;
    }
    return x;
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
    x = x >> n;
    int y = ~(((1 << 31) >> n) << 1);
    return x & y;
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
    x = ~x;
    int count = 0;
    int y;
    
    y = (!(x >> 16)) << 4;
    count += y;
    x = x << y;

    y = (!(x >> 24)) << 3;
    count += y;
    x = x << y;

    y = (!(x >> 28)) << 2;
    count += y;
    x = x << y;

    y = (!(x >> 30)) << 1;
    count += y;
    x = x << y;

    y = !(x >> 31);
    count += y;
    x = x << y;

    count += (!x);
    return count;
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
    unsigned ux = x;
    unsigned sign = ux & 0x80000000u;
    unsigned exp = 158;
    unsigned frac;
    unsigned tail;

    if (!x) {
        return 0;
    }

    if (sign) {
        ux = ~ux + 1;
    }

    while (!(ux & 0x80000000u)) {
        ux = ux << 1;
        exp = exp - 1;
    }

    frac = (ux >> 8) & 0x7FFFFFu;
    tail = ux & 0xFFu;

    if (tail > 0x80u) {
        frac = frac + 1;
    } else if (tail == 0x80u) {
        if (frac & 1) {
            frac = frac + 1;
        }
    }

    return sign + (exp << 23) + frac;
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
    unsigned sign = uf & 0x80000000u;
    unsigned exp = (uf >> 23) & 0xFFu;
    unsigned frac = uf & 0x7FFFFFu;
    if (exp == 0xFFu){
        return uf;
    }
    
    if (exp == 0){
        frac = frac << 1;
        return sign | frac;
    }
    exp = exp + 1;

    if(exp == 0xFFu){
        frac = 0;
    }

    return sign | (exp << 23) | frac;
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
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FFu;
    unsigned frac2 = (uf2 & 0xFFFFFu) | 0x100000u;
    int e;
    int result;
    if(exp < 1023u){
        return 0;
    }
    e = exp - 1023;
    if(e >= 31){
        return 0x80000000u;
    }
    if(e <= 20){
        result = frac2 >> (20 - e);
    }
    else{
        result = (frac2 << (e - 20)) | (uf1 >> (52 - e));
    }
    if(sign){
        result = -result;
    }
    return result;
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
    if(x < -149){
        return 0;
    }
    if(x < -126){
        return 1u << (x + 149);
    }
    if(x <= 127){
        return (x + 127) << 23;
    }
    return 0x7F800000;
}
