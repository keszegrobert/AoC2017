#include <fstream>
#include <iostream>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

int evenly_div(string line)
{
    std::vector<string> results;
    boost::split(results, line, boost::is_any_of(" \r\n\t"));
    std::vector<string>::iterator it;
    std::vector<int> numbers;
    for (it = results.begin(); it != results.end(); ++it)
    {
        int num = boost::lexical_cast<int>(*it);
        numbers.push_back(num);
    }
    std::vector<int>::iterator it1,it2;
    int max = 0;

    for (it1 = numbers.begin(); it1 != numbers.end(); ++it1)
    {
        int num1 = *it1;
        for (it2 = it1; it2 != numbers.end(); ++it2)
        {
            int num2 = *it2;
            if (num2 > num1)
            {
                if (num2 % num1)
                    continue;
                int res = num2 / num1;
                max = max > res ? max : res;
            }
            else //num2 <= num1
            {
                if (num1 % num2)
                    continue;
                int res = num1 / num2;
                max = max > res ? max : res;
            }
        }
    }
    return max;
}

int main(void)
{
    cout << evenly_div("5 9 2 8") << " == " << 4 << endl;
    cout << evenly_div("9 4 7 3") << " == " << 3 << endl;
    cout << evenly_div("3 8 6 5") << " == " << 2 << endl;
    int sum = 0;

    std::ifstream infile("input.txt");
    string line;
    map<string, string> parents;
    while (std::getline(infile, line))
    {
        sum += evenly_div(line);
    }
    cout << sum << endl;
}