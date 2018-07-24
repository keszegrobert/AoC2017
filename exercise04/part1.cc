#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
using namespace std;

int main(int argc, char const *argv[])
{
    ifstream f;
    f.open("input.txt");
    int good_phrases = 0;
    int counter = 0;
    char line[256];
    while (f.getline(line, 256))
    {
        counter++;
        vector<string> strs;
        boost::split(strs,line,boost::is_any_of(" \r\n\t"));
        vector<string>::iterator it;
        set<string> bag;
        bool found = false;
        for (it = strs.begin(); it != strs.end(); ++it)
        {
            if (bag.find(*it) == bag.end())
                bag.insert(*it);
            else
            {
                found = true;
                break;
            }
        }
        if (!found)
            good_phrases++;
    }
    cout << "Phrases:" << counter << "Good phrases: " << good_phrases << endl;
    return 0;
}