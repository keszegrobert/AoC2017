#include <fstream>
#include <iostream>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

int checksum(string line)
{
    std::vector<string> results;
    boost::split(results, line, boost::is_any_of(" \r\n\t"));
    std::vector<string>::iterator it;
    int max = 0;
    int min = INT_MAX;
    for (it = results.begin(); it != results.end(); ++it)
    {
        int num = boost::lexical_cast<int>(*it);
        if (num > max)
            max = num;
        if (num < min)
            min = num;
    }
    return max - min;
}

int main(void)
{
    cout << checksum("5 1 9 5") << " == " << 8 << endl;
    cout << checksum("7 5 3") << " == " << 4 << endl;
    cout << checksum("2 4 6 8") << " == " << 6 << endl;
    int sum = 0;

    std::ifstream infile("input.txt");
    string line;
    map<string, string> parents;
    while (std::getline(infile, line))
    {
        sum += checksum(line);
    }
    cout << sum << endl;
}