#include <iostream>

int gcd(int,int);
bool test(int num, int den, int n, int d);
void winner(int num, int den, int digit);

using namespace std;

/*
 * Get the GCD, which is required for many tests
 */
int gcd(int a, int b) {
    int temp;
    while(b) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/*
 * If a fraction less than 1 and both are equivalent, then
 * this would be 1 of the 4 winners.
 */
bool test(int num, int den, int n, int d)
{
    int f;
    if( num >= den ) {
        return false;
    }
    f = gcd(num,den);
    num /= f;
    den /= f;
    f = gcd(n,d);
    n /= f;
    d /= f;
    return ( (num==n) && (den==d) );
}

/*
 * We need to track the product of the winners, so we use
 * static variables here to simplify the main function.
 * This prints the winners and running simplified product.
 */
void winner(int num, int den, int digit)
{
    static int numer = 1;
    static int denom = 1;
    int f;
    numer *= num;
    denom *= den;
    f = gcd(numer, denom);
    numer /= f;
    denom /= f;
    cout << num << "/" << den << " :: " << digit << "\t";
    cout << "CURRENT PRODUCT: " << numer << "/" << denom << endl;
}

int main()
{
    int n,d,j;

    /*
     * Generate all the fraction combinations, and test for a winner.
     * This does more work than it needs to, but the problem set is
     * small enough to brute force.
     */
    for(n = 1; n <= 9; ++n) {
        for(d = 1; d <= 9; ++d) {
            for(j = 1; j <= 9; ++j) {
                if( test((n*10)+j, (d*10)+j, n, d ) )
                        winner((n*10)+j, (d*10)+j, j);
                if( test((n*10)+j, (j*10)+d, n, d ) )
                        winner((n*10)+j, (j*10)+d, j);
                if( test((j*10)+n, (d*10)+j, n, d ) )
                        winner((j*10)+n, (d*10)+j, j);
                if( test((j*10)+n, (j*10)+d, n, d ) )
                        winner((j*10)+n, (j*10)+d, j);
            }
        }
    }

    return 0;
}
