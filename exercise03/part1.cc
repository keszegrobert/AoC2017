#include <iostream>
#include <cmath>

using namespace std;

int manhattan_distance_from_1(int input)
{
    int sum = 0;
    int result = 0;
    int i = 0;
    int right = 0;
    int up = 0;
    while (sum < input)
    {
        i += 1;
        //right
        if (sum + i >= input)
        {
            right += input - sum;
            break;
        }
        sum += i;
        right += i;
        //up
        if (sum + i >= input)
        {
            up += input - sum;
            break;
        }
        sum += i;
        up += i;

        i += 1;
        //left
        if (sum+i >= input)
        {
            right -= input-sum;
            break;
        }
        sum += i;
        right -= i;

        //down
        if (sum + i >= input)
        {
            up -= input - sum;
            break;
        }
        sum += i;
        up -= i;
    }
    return abs(up) + abs(right) - 1;
}


void check(int input, int expected)
{
    int result = manhattan_distance_from_1(input);
    if (result != expected)
    {
        cout << "Result for " << input 
             << " should be:" << expected 
             << " but returned:" << result << endl;
    }
    else
    {
        cout << "OK" << endl;
    }
}


int main (void)
{
    check(1, 0);
    check(12, 3);
    check(23, 2);
    check(1024, 31);
    cout << "Manhattan distance of:" << 347991 << " from 1 is:" << manhattan_distance_from_1(347991) << endl;
}