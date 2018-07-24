#include <fstream>
#include <iostream>

using namespace std;

int produce_sum(string seq)
{
    if (seq.length() == 0)
        return 0;
    int sum = 0;
    char previous = seq[seq.length()-1];
    for (int i=0; i <seq.length(); ++i)
    {
        char a = seq[i];
        if (a == previous)
            sum += a - '0';
        previous = a;
    }
    return sum;
}


int main() 
{
    std::ifstream infile("input.txt");
    string line;
    std::getline(infile, line);
    cout << produce_sum(line) << endl;
    cout << produce_sum("1122") << "==" << 3 << endl;
    cout << produce_sum("1111") << "=="  << 4 << endl;
    cout << produce_sum("1234") << "=="  << 0 << endl;
    cout << produce_sum("91212129") << "=="  << 9 << endl;
    return 0;
}
