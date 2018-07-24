#include <fstream>
#include <iostream>

using namespace std;

int produce_sum(const string seq)
{
    if (seq.length() == 0)
        return 0;
    int offset = seq.length() / 2;
    int sum = 0;
    for (int i=0; i < offset; ++i)
    {
        int second = i + offset;
        if (second > seq.length())
            second -= seq.length();
        if (seq[i] == seq[second])
            sum += 2*(seq[i] - '0');
    }
    return sum;
}


int main() 
{
    std::ifstream infile("input.txt");
    string line;
    std::getline(infile, line);
    cout << produce_sum(line) << endl;
    cout << produce_sum("1212") << "==" << 6 << endl;
    cout << produce_sum("1221") << "=="  << 0 << endl;
    cout << produce_sum("123425") << "=="  << 4 << endl;
    cout << produce_sum("123123") << "=="  << 12 << endl;
    cout << produce_sum("12131415") << "=="  << 4 << endl;
    return 0;
}
