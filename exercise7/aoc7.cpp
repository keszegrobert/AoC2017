#include <fstream>
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <string>
#include <map>

using namespace std;

int main() 
{
    std::ifstream infile("input.txt");
    string line;
    map<string, string> parents;
    while (std::getline(infile, line))
    {
        std::vector<string> results;
        boost::split(results, line, [](char c){
            return c == ' ' || c == ',' || c == '(' 
                || c == ')' || c == '-' || c == '>';
        });
        int i = 0;
        for (auto name : results)
        {
            i++;
            if (i <= 3) continue;
            if (name == "") continue;
            parents.insert(pair<string,string>(name, results[0]));
        }
    }

    string bottom = parents.begin()->first;
    while (parents.find(bottom) != parents.end())
        bottom = parents[bottom];
    cout << bottom << endl;
    return 0;
}
