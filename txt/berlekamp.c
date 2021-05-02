#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define false 0
#define true !false
typedef enum { TRUE = true, FALSE = false} bool;/**<Boolean type */

typedef long GF2m_el;

/********************************************//**
 * \brief Galois Field Structure, holds a support set and its generator
 ***********************************************/
typedef struct GF{
    GF2m_el T;              /**< The generator */
    GF2m_el *Set;           /**< The elements in the field */
} GF;

/********************************************//**
 * \brief Goppacode Structure, holds a Galois Field, am irreducible polynomial, and a Parity-Check matrix
 ***********************************************/
typedef struct Goppacode{
    GF2m_el *g;             /**< Irreducible polynomial */
    GF L;                   /**< Support set */
    GF2m_el**H;             /**< Parity matrix */
} Goppa;

char *cyphertext, *error;
int m;/**<Degree of the field */
int t;/**<Number of errors the code can correct. Also the degree of the irreducible polynomial g */
int n, k, GFP_SIZE;
Goppa goppa;

void printData(char* m){
    int j, num;
    for(j = 0; j < n-3; j += 4){
            num = 8*m[j] + 4*m[j+1] + 2*m[j+2] + m[j+3];
            printf("%01x", num);
    }
}
void gfp_print(char name[], GF2m_el P[GFP_SIZE]){
    int i;
    printf("(%s: ", name);
    for(i = 0; i <GFP_SIZE; i++)printf("%0*x ",(m + m%4)/4, (int) P[i]);
    printf(")");
}


/********************************************//**
 * \brief Sets dimenision of the code. Also sets values of helper variables n and k.
 *
 * \param _m int degree of the support set
 * \param _t int _t degree of the irreducible polynomial
 * \return void
 *
 ***********************************************/
void setDimensions(int _m, int _t){
    int i;
    m = _m;
    t = _t;

    n = 2;
    for(i = 1; i < m; i++)n *= 2; /**< Iterative implementation of power function   n <-- 2^m */

    k = n - m* t;
   }

/********************************************//**
 * \brief Finds minimum number of bits needed to represent a number in binary
 *
 * \param e, the number which can be represented with at least x bits
 * \return x, the number of bits
 *
 ***********************************************/
int bits(int e){
    int length = 0;
    while(e != 0)
    {
        e/=2;
        length++;
    }
    return length;
}
/********************************************//**
 * \brief Multiplication in a Galois Field between two elements
 *
 * \param x GF2m_el
 * \param y GF2m_el
 * \return GF2m_el x * y (mod T)
 *
 ***********************************************/
GF2m_el gf_mult(GF2m_el x, GF2m_el y){
    GF2m_el z;
    unsigned char i;
    z=((x>>(m-1))&1)? y:0;                   /**<if x_{m-1}=1 then z<-y else z<-0 */

    for(i=m-1; i>=1; i--)
        z=  (z<<1)^                         /**<Shift z, i.e multiply z by 2 */
            (((x>>(i-1))&1)?y:0)^           /**< Add the i'th index  of x * y, (i.e 0 or y) */
            (((z>>(m-1))&1)?goppa.L.T:0);   /**<Add the m-th bit of z * T, (i.e T or 0) */
    return z;
}
/********************************************//**
 * \brief Raises a to the e-th power in the Galois Field
 *
 * \param a GF2m_el
 * \param e int
 * \return GF2m_el a^e (mod T)
 *
 *  Uses the square-multiply modular exponentiation algorithm
 *
 ***********************************************/
GF2m_el gf_pow(GF2m_el a, int e){
    GF2m_el p = a;
    int i = 0, nbits = bits(e);
    for(i = nbits-2; i >= 0; i--)
    {
        p = gf_mult(p,p);
        p = (((e>>(i))& 1)? gf_mult(p,a):gf_mult(p,1));/**< Multiply by a if e_i is 1 else multiply by 1 */
    }
    if(e==0)return 1;
    else return p;
}
/********************************************//**
 * \brief Divides two Galois Field elements by using an inverse identity
 *
 * \param div GF2m_el
 * \param dvd GF2m_el
 * \return GF2m_el dvd/div (mod T)
 *
 * An element g, raised to the n - 2 will produce an inverse 1/g.
 *  This method uses that property two multiply with an inverse.
 *
 ***********************************************/
GF2m_el gf_div(GF2m_el div, GF2m_el dvd){
    return (gf_mult(gf_pow(div, n - 2), dvd));
}
/********************************************//**
 * \brief Evaluates a polynomial p(x) with a given x
 *
 * \param p[GFP_SIZE] GF2m_el
 * \param x GF2m_el
 * \return GF2m_el
 *
 * A polynomial is solved using Horner's Scheme, a left to right (LtR) algorithm.
 *  P(x) = P_(t) * x^(t) + P_(t-1) * x^(t-1) + ... + P_(1) * x + P_(0)
 *
 * Horner's Scheme: (...((P_(t) * x + P_(t-1)) * x + P_(t-2)) ... * x + P_(1) ) * x + P_(0)
 *
 ***********************************************/
GF2m_el gfp_eval(GF2m_el p[GFP_SIZE], GF2m_el x){
    int i;
    GF2m_el res = p[GFP_SIZE-1];
    for(i = (GFP_SIZE-1)-1; i >= 0; i--)
        res = gf_mult(res,x)^p[i];

    return res;
}
/********************************************//**
 * \brief Copies content of polynomial a to polynomial b
 *
 * \param a[GFP_SIZE] GF2m_el
 * \param b[GFP_SIZE] GF2m_el
 * \return void
 *
 ***********************************************/
void copy(GF2m_el a[GFP_SIZE],GF2m_el b[GFP_SIZE]){
    int i;
    for(i = 0; i < GFP_SIZE; i++) b[i] = a[i];
}
/********************************************//**
 * \brief Determines the degree of a polynomial
 *
 * \param f[GFP_SIZE] GF2m_el
 * \return int degree of f
 *
 ***********************************************/
int deg(GF2m_el f[GFP_SIZE]){
    int i;
    for(i = GFP_SIZE-1; i > 0 && f[i] == 0; i--);
    return i;
}
/********************************************//**
 * \brief Assigns r = a (mod goppa.g)
 *
 * \param a[GFP_SIZE] GF2m_el
 * \param r[GFP_SIZE] GF2m_el
 * \return void
 *
 ***********************************************/
void gfp_mod(GF2m_el a[GFP_SIZE], GF2m_el r[GFP_SIZE]){
    int i;
    for(i = 0; i < GFP_SIZE; i++)
        r[i] = gf_mult(a[GFP_SIZE-1],goppa.g[i]) ^ a[i];
}
/********************************************//**
 * \brief Scalar multiplication of polynomial
 *
 * \param s GF2m_el
 * \param p[GFP_SIZE] GF2m_el
 * \param r[GFP_SIZE] GF2m_el
 * \return void
 *
 *  Assigns r = s*a by multiplying each coefficient of a by s
 *
 ***********************************************/
void gf_p_mult(GF2m_el s, GF2m_el p[GFP_SIZE], GF2m_el r[GFP_SIZE]){
    int i;
    for(i = 0; i < GFP_SIZE; i++)
        r[i] = gf_mult(s,p[i]);
}
/********************************************//**
 * \brief Left shift of coefficients by multiplying by x on a
 *
 * \param a[GFP_SIZE] GF2m_el
 * \param r[GFP_SIZE] GF2m_el
 * \return void
 *
 *  r = a*x (mod goppa.g)
 *
 ***********************************************/
void gfp_multx(GF2m_el a[GFP_SIZE], GF2m_el r[GFP_SIZE]){
    GF2m_el p[GFP_SIZE];
    int i;
    gfp_mod(a,p); /**< If deg(a) = t then a (mod goppa.g) < t => shift won't spill over GFP_SIZE */
    for(i = GFP_SIZE-1; i >= 1; i--)r[i] = p[i-1];
    r[0] = 0;
}
/********************************************//**
 * \brief Addition of two polynomials. r = a + b
 *
 * \param a[GFP_SIZE] GF2m_el
 * \param b[GFP_SIZE] GF2m_el
 * \param r[GFP_SIZE] GF2m_el
 * \return void
 *
 ***********************************************/
void gfp_xor(GF2m_el a[GFP_SIZE] ,GF2m_el b[GFP_SIZE], GF2m_el r[GFP_SIZE]){
    int i;
    for(i = 0; i < GFP_SIZE; i++)r[i] = a[i] ^ b[i];
}
/********************************************//**
 * \brief Multiplication of two polynomials r = a*b
 *
 * \param a[GFP_SIZE] GF2m_el
 * \param b[GFP_SIZE] GF2m_el
 * \param res[GFP_SIZE] GF2m_el
 * \return void
 *
 ***********************************************/
void gfp_mult(GF2m_el a[GFP_SIZE], GF2m_el b[GFP_SIZE], GF2m_el res[GFP_SIZE]){
    int i;
    GF2m_el r[GFP_SIZE], h[GFP_SIZE], h2[GFP_SIZE];

    gf_p_mult(a[GFP_SIZE-1],b,r);                /**<Initialises result with a scalar multiplication of a[t] and b */
    for(i = GFP_SIZE - 2; i >= 0; i--){
        gfp_multx(r, h);                /**< I) Multiplies r by X (shifts all coeffients to the right) */
        gf_p_mult(a[i], b, h2);         /**< II) Takes a[i] * b */
        gfp_xor(h,h2,r);                /**< Adds I) with II) */
    }
    copy(r,res);
}
/********************************************//**
 * \brief Determines whether a polynomial is 0
 *
 * \param p[GFP_SIZE] GF2m_el
 * \return bool
 *
 ***********************************************/
bool gfp_isZero(GF2m_el p[GFP_SIZE]){
    int i = 0;
    for(i = 0; i < GFP_SIZE; i++)
        if(p[i] != 0)return FALSE;
    return TRUE;
}
/********************************************//**
 * \brief Performs a division of two polynomials assigning Q to be the quotient and R, the remainder.
 *
 * \param div[GFP_SIZE] GF2m_el
 * \param dvd[GFP_SIZE] GF2m_el
 * \param Q[GFP_SIZE] GF2m_el
 * \param R[GFP_SIZE] GF2m_el
 * \return void
 *
 *  Division is performed coefficient by coefficient. Div will be multiplied such that its leading coefficient will be equal to dvd's
 *      The result is subtracted from dvd and the process repeats until dvd has degree < div or dvd is 0.
 *
 *      dvd's content does not actually change during the process it is copied to a helper variable first.
 *
 *      Quotient should never be referenced by div or dvd
 *
 *      Computes Q,R such that: dvd = Q * div + R
 *
 ***********************************************/
void gfp_div(GF2m_el div[GFP_SIZE], GF2m_el dvd[GFP_SIZE], GF2m_el Q[GFP_SIZE], GF2m_el R[GFP_SIZE]){
    GF2m_el dvdc[GFP_SIZE], /**<copy of dvd, that will have its contents changed during runtime */
            helper[GFP_SIZE],/**<polynomial used as a placeholder between steps */
            empty[GFP_SIZE];/**<monomial which will only hold the current multiplier. Coefficients of Q are from here. */
    int deg_dvd, deg_div, i;

    copy(dvd,dvdc);
    for(i = 0; i < GFP_SIZE; i++){ /**< Initialise arrays */
        empty[i] = 0;
        Q[i] = 0;        /**<Be careful. If Q is a reference to dvd or div this will wipe the coefficients in those arrays too */
    }

    deg_dvd = deg(dvdc);
    deg_div = deg(div);

    while(deg_div <= deg_dvd && !gfp_isZero(dvdc)) /**<Run until degree of dvdc < div and while dvdc is non-zero */
    {
        /**<In each iteration the largest coefficient of dvdc divided by the largest coefficient of div
            the result is placed into empty at the (deg(dvdc) - deg(div)) index as a coefficient

            empty is then multiplied with divisor and the result is subtracted from dvdc
            degree of dvdc is updated, and empty is reset to 0

            Process is repeated until div has a larger degree than dvdc
        */
        empty[deg_dvd - deg_div] = gf_div(div[deg_div], dvdc[deg_dvd]);
        Q[deg_dvd - deg_div] = empty[deg_dvd - deg_div];        /**<Add empty to Q */

        gfp_mult(empty, div, helper);
        gfp_xor(dvdc , helper, dvdc);

        empty[deg_dvd - deg_div] = 0;   /**< Clear empty */
        deg_dvd = deg(dvdc);    /**< Recompute deg(dvdc) */

    }

    copy(dvdc, R);
}
/********************************************//**
 * \brief Returns the r = gcd(a,b)
 *
 * \param a[GFP_SIZE] GF2m_el
 * \param b[GFP_SIZE] GF2m_el
 * \param r[GFP_SIZE] GF2m_el
 * \return void
 *
 *  This is just a shortened version of the extended euclidean algorithm.
 *
 ***********************************************/
void gfp_gcd(GF2m_el a[GFP_SIZE], GF2m_el b[GFP_SIZE], GF2m_el r[GFP_SIZE]){
    GF2m_el old_r[GFP_SIZE], new_r[GFP_SIZE];
    GF2m_el quotient[GFP_SIZE] , h[GFP_SIZE];
    int i = 0;

    for(i = 0; i < GFP_SIZE; i++){      /**<Initialise all helper arrays with 0 */
        r[i] = 0;
        old_r[i] = 0;
        new_r[i] = 0;
    }

    copy(a, r);                         /**< r <- a */
    copy(b, old_r);                     /**< old_r <- b */

    while (!gfp_isZero(old_r)){
        gfp_div(old_r, r, quotient, h); /**<quotient = old_r / r */

        copy(r, new_r);
        copy(old_r, r);

        gfp_mult(quotient, old_r,old_r);
        gfp_xor(old_r, new_r, old_r);
        gfp_mod(old_r,old_r);           /**<old_r = new_r - q * old_r */
    }

}
/********************************************//**
 * \brief Determines all locations of the support set where the polynomial is solved.
 *
 * \param p[GFP_SIZE] GF2m_el
 * \return void
 *
 *  In a brute force method p(x) will be checked with each element in the support.
 *       If x = L[i] solves p, the error will place a 1 at its i-th index.
 *
 ***********************************************/
void calcError(GF2m_el p[GFP_SIZE]){
    int i;
    for(i = 0; i < n; i++){                               /**<Runs for each element in L */
        if(gfp_eval(p, goppa.L.Set[i]) == 0)error[i] = 1; /**<Place a 1 when p(L[i]) = 0 */
        else error[i] = 0;
    }
}
/********************************************//**
 * \brief Using Ben-or's irreducibility test determines whether a polynomial is irreducible
 *
 * \param
 * \return
 *
 *  Currently giving out false positives. Unable to fully implement this feature.
 *
 ***********************************************/
bool isirreducible (GF2m_el g[GFP_SIZE]){
   GF2m_el r[GFP_SIZE], gcd[GFP_SIZE],  h1[GFP_SIZE],  h2[GFP_SIZE];
    int d = 0, i;

    for(d = 0; d <GFP_SIZE;d++)r[d] = 0;
    r[1] = 1; /**< Create r = X */

    for(d = 1; d <= t/2 ;d++){

        for(i = 0; i < m; i++){ /**< r = r^(n) = r^(2^m) */
        gfp_mult(r,r,r);
        gfp_mod(r,r);
        }
        r[1] ^= 1; /**<  r - x */

        gfp_gcd(g,r,gcd);
        gcd[0] ^= 1;/**< If gcd = 1 => gcd - 1 = 0 */
        if(!gfp_isZero(gcd)) return FALSE; /**< If gcd - 1 is not 0 then g is reducible  */

        r[1] ^= 1; /**< r + x, add x back to r */
    }
    return TRUE;    /**< If loop finishes and all tests pass r is irreducible */
}
/********************************************//**
 * \brief Determines whether the error is 0
 *
 * \return TRUE if error = 0
 *
 ***********************************************/
bool error_is_zero(){
    int i;
    for(i  = 0; i < n; i++)if(error[i] != 0)return FALSE;
    return TRUE;
}
/********************************************//**
 * \brief Creates a parity matrix using goppa.g
 *
 * \return void
 *
 *  If you refer to the article written alongside the code
 *         the definition for the parity matrix of berlekamp-massey algorithm is defined there
 *
 *
 ***********************************************/
void generate_parity(){
    int i, j;

    goppa.H = (GF2m_el**) malloc( (GFP_SIZE - 1) * sizeof(GF2m_el*));

    goppa.H[0] = (GF2m_el*) malloc(n * sizeof(GF2m_el));
    for(j = 0; j < n; j++)goppa.H[0][j] = gf_div(gfp_eval(goppa.g,goppa.L.Set[j]),1); /**<Assign first row of H to be g(L[j])^(-1) = H[0][j] */

    for(i = 1; i < (GFP_SIZE - 1); i++){
        goppa.H[i] = (GF2m_el*) malloc(n * sizeof(GF2m_el));
        for(j = 0; j < n; j++){
            goppa.H[i][j] = gf_mult(goppa.H[i-1][j], goppa.L.Set[j]); /**< Reduces time of computation by using previous row to solve the next row */
        }
    }
}
/********************************************//**
 * \brief Creates the goppa code
 *
 * \return void
 *
 *  Creates elements of the goppa code in the following order
 *      - Irreducible polynomial for support set
 *      - Support set
 *      - Irreducible g -- Note the current implementation does not always create a valid g
 *      - Parity-Check matrix
 *
 *      Future implementation would suggest a generator matrix however I have run out of time at this point.
 *
 ***********************************************/
void keygen() {

    static const GF2m_el irreduciblePolynomials[] = {0,1,7,11,31,55,109,211,379,883,2047,3357,8191,13465,27589,41255};
                                                    /**<Polynomials for 0 <= m <= 15, indexed at m, note: m=0 or m=1 are invalid */
    int i;
    time_t rd;
    srand((unsigned) time(&rd));

    GF *field;
    goppa.L.Set =  (GF2m_el*) calloc(n, n * sizeof(GF2m_el));
    field = &goppa.L;

    /**< Assign T generator for support */
    field->T = irreduciblePolynomials[m];

    /**< Generate support set  */

    field-> Set[0] = 0;
    field-> Set[1] = 1;
    field-> Set[2] = rand() % (n-3) + 2; /**< Random number between 2 to n-1 */

    for(i = 3; i < n; i++){
        field-> Set[i] = gf_mult(field->Set[2], field->Set[i-1]);

        if (field->Set[i] == 1){/**< If Set[2] doesn't generate all of GF(n) then change it so that it does */
            i = 2;
            field->Set[2] = (field->Set[2]+1) % n;
            if(field->Set[2] == 0)field->Set[2]+=2;
        }
    }

    /**<Generate g of degree t */

    GFP_SIZE = 2*t + 1; /**< Polynomials are of size g^2, 2t. */
    goppa.g =  (GF2m_el*) calloc(GFP_SIZE, GFP_SIZE * sizeof(GF2m_el));

    /**< Create a random irreducible polynomial, g, of degree t */
    do{
        for(i = 0; i < GFP_SIZE; i++){
            if(i < t)goppa.g[i] = goppa.L.Set[rand() % n]; /**< Randomly choose coefficients from the support set */
            else goppa.g[i] = 0;
        }
        goppa.g[t] = 1;
        calcError(goppa.g);
    }while( !isirreducible(goppa.g) || !error_is_zero() );

    gfp_mult(goppa.g,goppa.g,goppa.g); /**< Square g for key-generation of Berlekamp*/
    generate_parity();  /**< Create Parity-Check Matrix */
}
/********************************************//**
 * \brief Calculates the syndrome polynomial given a ciphertext c. S = Pol( c * H_transpose)
 *
 * \param S[GFP_SIZE] GF2m_el
 * \return void
 *
 *  Each column i of H where c_i = 1 is added together (note because elements are from galois field addition is an xor)
 *
 ***********************************************/
void calcSyndrome(GF2m_el S[GFP_SIZE]){
    int i, j;
    for(i = 0; i < GFP_SIZE - 1; i++){
        S[i] = 0;
        for(j = 0; j < n; j++){
            S[i] ^= gf_mult(cyphertext[j], goppa.H[i][j]); /**< Xor each coefficient of S with each column of H where the position in the c is 1 */
        }
    }
    S[GFP_SIZE - 1] = 0;        /**< Because S is modulo g, its degree should be < t (the coefficient for X^t should be 0) */
}
/********************************************//**
 * \brief Berlekamp-Massey Algorithm (reference article for pseudo)
 *
 * \return void
 *
 *      - Calculates the syndrome polynomial
 *      - Performs the BMA
 *      - Reciproates end polynomial
 *      - Finds roots of error locator polynomial
 *
 ***********************************************/
void berlekamp(){
    int L = 0,_m = -1,i, _k;
    GF2m_el f[GFP_SIZE], g[GFP_SIZE], h[GFP_SIZE], empty[GFP_SIZE],recip[GFP_SIZE],S[GFP_SIZE];
    GF2m_el d_m = 1, d_k;

    for(i = 0; i < GFP_SIZE; i++){
        g[i] = 0;
        f[i] = 0;
        empty[i] = 0;
        recip[i] = 0;
    }
    f[0] = 1;
    g[0] = 1;

    calcSyndrome(S);

    /**< Begin Berlekamp */
    for(_k = 0; _k < GFP_SIZE-1; _k++){
        d_k =  S[_k];
        for(i = 1 ; i <= L; i++)d_k ^= gf_mult(f[i], S[_k-i]);
        if(d_k != 0){
            copy(f,h);
            empty[_k-_m] = gf_div(d_m,d_k);

            gfp_mult(g,empty,f);
            empty[_k-_m] = 0;
            gfp_xor(f,h,f);

            if (L <= _k/2){
                L = _k + 1 - L;
                _m = _k;
                d_m = d_k;
                copy(h,g);
            }
        }
    }
    /**< End Berlekamp */

    /**< Reciprocrate f */
    for(i = 0; i <= deg(f); i++){
        recip[i] = f[deg(f)-i];
    }

    if(deg(f)  < L){
        gfp_multx(recip,recip);
    }

    calcError(recip);
}
/********************************************//**
 * \brief Frees allocated memory of goppa code
 *
 * \return void
 *
 *      Will handle all memory that program allocated for goppa code in keygen.
 *
 ***********************************************/
void freeGoppa(){
    int i;
    free(goppa.L.Set);
    free(goppa.g);

    for(i = 0; i < GFP_SIZE-1; i++)free(goppa.H[i]); //free each row of the variable before freeing the actual variable address
    free(goppa.H);
}


/********************************************//**
 * \brief Sample usage of the code
 *
 * \return int
 *
 *  This method goes through, in order, the function calls to use the software
 *
 *  Two methods have been created to print stated of polynomials and error/ciphertext values
 *      - printData(char*) will print out the value of the error or ciphertext in hexadecimal
 *      - gfp_print(char[], GF2m_el[GFP_SIZE]) will print out the polynomial with least significant coefficient in front (in hexadecimal)
 *              i.e. Poly: 7 6 9 0 means 7 + 6x + x^2 + 0x^3 or [7, 6, 9, 0] in array form
 ***********************************************/
int main(){
    /**< Define Dimensions */

    /**< Assign m = 11 and t = 50 */
    setDimensions(11, 50);

    /**< Create Goppa code */
    keygen(m,t);

    /**< Allocate word and error vector*/

    cyphertext = (char*) calloc(n, n * sizeof(char));
    error = (char*) calloc(n, n * sizeof(char));

    /**< Assign up to t errors in cyphertext */

    /**< Decode Word */
    berlekamp();

    /**< After call to berlekamp error has been assigned values */

    /**< Free dynamic variables */
    free(cyphertext);
    free(error);
    freeGoppa();

    return 0;
}
