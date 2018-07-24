#include <iostream>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;

int process(int state, vector<int>& input)
{
    assert(state < input.size());
    assert(0 <= state );
    int index = state;
    state += input[state];
    if (input[index] >= 3)
        input[index]--;
    else
        input[index]++;  
    return state;   
}

vector<int> instructions;

void check_processing(int start, vector<int>& before, int end, vector<int>& expected)
{
    int pc = process(start, before);
    cout << start << "==>" << end << "(" << pc << ")" << endl;
    assert(pc == end);
    vector<int>::iterator oit = expected.begin();
    assert(before.size() == expected.size());
    for (vector<int>::iterator it=before.begin();it != before.end(); ++it)
    {
        cout << *it << " == " << *oit << endl;
        assert(*it == *oit);
        ++oit;
    }
}


void test_processing()
{
    int states[11][5] = {
        {0,3,0,1,-3},
        {1,3,0,1,-3},
        {2,3,0,1,-3},
        {2,2,0,1,-3},
        {2,2,0,1,-2},
        {2,3,0,1,-2},
        {2,3,0,2,-2},
        {2,3,0,2,-1},
        {2,3,1,2,-1},
        {2,3,2,2,-1},

        {2,3,2,3,-1}
    };

    int starts[11] = {0,0,1,4,1,3,4,2,2,3,5};

    for (int i = 0; i < 10; ++i)
    {
        vector<int> before(states[i],states[i]+5);
        vector<int> after(states[i+1],states[i+1]+5);
        cout << "Checking..." << endl;
        check_processing(starts[i],before, starts[i+1], after);
    }
}



int main(int argc, char const *argv[])
{
    test_processing();
    ifstream f;
    f.open("input.txt");
    char line[256];
    int len=0;
    while (f.getline(line, 256))
    {
        if (strlen(line) == 0)
            continue;
        int instruction = boost::lexical_cast<int>(line); 
        instructions.push_back(instruction);
    }

    int counter = 0;
    int pc = 0;
    while (0 <= pc && pc < instructions.size())
    {
        pc = process(pc,instructions);
        counter++;
    }

    cout << "Steps: " << counter << endl;

    return 0;
}