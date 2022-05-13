#include "Math.h"

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

namespace Math
{
    using namespace std;

    //------------------------------------------------------------------------------------------------------------------------
    // 202. Happy Number (Easy)
    //
    // The crucial part is how to let loop stop. We should break when a number appears again.
    //
    //------------------------------------------------------------------------------------------------------------------------
    bool isHappy( int n )
    {
        unordered_set<int> numbers;

        while( n != 1 )
        {
            int sum = 0;

            while( n != 0 )
            {
                const int temp = n % 10;
                sum += temp * temp;
                n /= 10;
            }

            n = sum;

            if( numbers.find( n ) != numbers.end() )
            {
                break;
            }
            else
            {
                numbers.insert( n );
            }
        }

        return n == 1;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 172. Factorial Trailing Zeroes (Medium)
    //
    // Follow up: Could you write a solution that works in logarithmic time complexity?
    //
    // It is not a good idea to calucate the factorial and count the trailing 0.
    // One trailing 0 means there is a 10 in the chain of calculating the factorial. 10 can be divided to 5*2.
    // So, the anser is equal to the number of 5.
    //------------------------------------------------------------------------------------------------------------------------

    int trailingZeroes( int n )
    {
        int result = 0;
        while( n != 0 )
        {
            result += n / 5;
            n /= 5;
        }
        return result;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 171. Excel Sheet Column Number (Easy)
    //------------------------------------------------------------------------------------------------------------------------

    int titleToNumber( string columnTitle )
    {
        unsigned int result = 0;
        unsigned int multi = 1;
        // Scan from lowest to highest.
        for( int i = static_cast<int>( columnTitle.size() - 1 ); i >= 0; --i )
        {
            result += ( columnTitle[i] - 'A' + 1 ) * multi;
            multi *= 26;
        }
        return result;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 50. Pow( x, n ) (Medium)
    //
    // Note that n could be negative.
    // Idea: x^(n/2) * x^(n/2) = x^n.  (x * x)^(n/2) = x^n.
    // x^-2 = 1 / x^2
    //------------------------------------------------------------------------------------------------------------------------

    double myPow( double x, int n )
    {
        double result = 1;
        for( int i = n; i != 0; i /= 2 )
        {
            if( i % 2 != 0 )
            {
                result *= x;
            }
            x *= x;
        }

        return n < 0 ? 1 / result : result;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 69. Sqrt(x) (Easy)
    // 0 <= x <= 2^31 - 1
    // Use binary search to find the maximum integer n, so that n*n is equal to or less than x.
    //------------------------------------------------------------------------------------------------------------------------

    int mySqrt( int x )
    {
        if( x <= 1 )
        {
            return x;
        }

        int left = 1;
        int right = x;

        while( left < right )
        {
            const int mid = left + ( right - left ) / 2;

            const int temp = x / mid;
            if( temp == mid )
            {
                return mid;
            }

            if( mid < temp )
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }

        return right - 1;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 29. Divide Two Integers
    //
    // Using Subtraction will cause Time Limit Exceeded.
    // We can use Bit Manipulation. The idea is to subtract twice of divisor
    // Need to deal with the special case - dividend is INT_MIN and divisor is -1.
    //------------------------------------------------------------------------------------------------------------------------

    int divide( int dividend, int divisor )
    {
        if( dividend == INT_MIN && divisor == -1 )
        {
            return INT_MAX; // This is the requirement.
        }

        // Decide the final sign of the result. True means negative.
        bool sign = ( dividend < 0 ) ^ ( divisor < 0 );

        // Make them positive
        unsigned int dividendAbs = abs( dividend );
        unsigned int divisorAbs = abs( divisor );

        // Special case.
        if( divisorAbs == 1 )
        {
            return sign ? static_cast<int>( -1 * dividendAbs ) : dividendAbs;
        }

        int result = 0;

        while( dividendAbs >= divisorAbs ) // Must use >=
        {
            // It's crucial to use unsigned int because it will exceed INT_MAX when dividend is INT_MAX.
            unsigned int doubleDivisor = divisorAbs;
            unsigned int tempQuotient = 1;

            while( dividendAbs > doubleDivisor && dividendAbs >= ( doubleDivisor << 1 ) ) // Must use >=
            {
                doubleDivisor <<= 1;
                tempQuotient <<= 1;
            }

            // Assume dividend is 10 and divisor is 3.
            // tempQuotient will be 2, then 1.
            // doubleDivisor will be 6, and 3.
            // If dividend is 10 and divisor is 2.
            // tempQuotient will be 4, then 1.
            // doubleDivisor will be 8, and 2.
            result += tempQuotient;
            dividendAbs -= doubleDivisor;
        }

        return sign ? -result : result;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 166. Fraction to Recurring Decimal
    //
    // -2^31 <= numerator, denominator <= 2^31 - 1
    // denominator != 0
    //
    // There a technique to get the reminder: Mutliply the reminder by 10, and divide by divisor, we will get the next digit
    // of the decimal
    //------------------------------------------------------------------------------------------------------------------------

    string fractionToDecimal( int numerator, int denominator )
    {
        if( numerator == 0 )
        {
            return "0";
        }

        // Decide the final sign of the result. True means negative.
        bool negative = ( numerator < 0 &&  denominator > 0 ) || ( numerator > 0 && denominator < 0 );

        // To avoid integer overflow, we use long long.
        long long numeratorAbs = abs( static_cast<long long>( numerator ) );
        long long denominatorAbs = abs( static_cast<long long>( denominator ) );

        long long quotient = numeratorAbs / denominatorAbs;
        long long reminder = numeratorAbs % denominatorAbs;

        string result( negative ? "-" : "" );
        result.append( to_string( quotient ) );

        // There is no reminder, just return the quotient.
        if( reminder == 0 )
        {
            return result;
        }

        result.append( "." );

        // Mutliply the reminder by 10, and divide by divisor, we will get the next digit of the decimal.
        // So, the reminder determines the digit. If we meet the same reminder again, it means we get a recurring decimal.
        // <reminder, the position when we meed this reminder>
        int pos = 0;
        string decimalString;
        // Use a map to record the position of reminder.
        unordered_map<long long, size_t> decimal;
        while( reminder != 0 )
        {
            if( decimal.find( reminder ) != decimal.end() )
            {
                decimalString.insert( decimal[reminder], "(" );
                decimalString.push_back( ')' );
                break;
            }

            const int digit = reminder * 10 / denominatorAbs;
            decimalString.append( to_string( digit ) );

            decimal[reminder] = pos;
            pos++;
            reminder = reminder * 10 % denominatorAbs;
        }

        result.append( decimalString );

        return result;
    }

    void test_Math()
    {
        cout << "Test Math" << endl;

        cout << "Result of Happy Number: " << isHappy( 2 ) << endl;

        cout << "Result of Factorial Trailing Zeroes: " << trailingZeroes( 15 ) << endl;

        cout << "Result of Excel Sheet Column Number: " << titleToNumber( "FXSHRXW" ) << endl;

        cout << "Result of Pow( x, n ): " << myPow( -2, 31 ) << endl;

        cout << "Result of Sqrt(x): " << mySqrt( 2147395599 ) << endl;

        cout << "Result of Divide Two Integers: " << divide( 2147483647, -1 ) << endl;

        cout << "Result of Fraction to Recurring Decimal: " << fractionToDecimal( -2147483648, 2 ) << endl;
    }
}