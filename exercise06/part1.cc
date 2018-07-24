#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> history;

int choose(int* arr, int size)
{
    int result = 0;
    int maxarr = -1;
    for (int i=0; i<size; ++i)
    {
        if (maxarr < arr[i]) 
        {
            maxarr = arr[i];
            result = i;
        }
    }
    cout << "selected = " << result << endl;
    return result;
}

string convert(int* arr, int size)
{
    string history_item = "";
    stringstream ss;
    for (int i = 0; i < size; ++i)
    {
        ss << arr[i] << ",";
    }

    history_item = ss.str();
    return history_item;
}

void redistribute(int* arr, int size, int selected)
{
    if (selected < 0 || size <= selected)
        return;

    int to_redistribute = arr[selected];
    arr[selected] = 0;
    for (int i = 1; i < to_redistribute+1; ++i)
    {
        int index = (selected+i)%size; 
        arr[index] = arr[index] + 1;
    }
}

void check_redistribution(int* arr, int size, int selected, int* expected_arr)
{
    int actually_chosen = choose(arr, size);
    assert(selected == actually_chosen);
    redistribute(arr, size, selected);
    for (int i = 0; i < size; ++i)
        assert(arr[i] == expected_arr[i]);
}


void test_memory_example()
{
    int arr[] = {0,2,7,0};

    int expected1[] = {2,4,1,2};
    check_redistribution(arr, 4, 2, expected1);

    int expected2[] = {3,1,2,3};
    check_redistribution(arr, 4, 1, expected2);

    int expected3[] = {0,2,3,4};
    check_redistribution(arr, 4, 0, expected3);

    int expected4[] = {1,3,4,1};
    check_redistribution(arr, 4, 3, expected4);

    int expected5[] = {2,4,1,2};
    check_redistribution(arr, 4, 2, expected5);
}

int redistribution_cycle(int* arr, int size)
{
    history.clear();
    while (true)
    {
        string hi = convert(arr, size);
        cout << hi << endl;
        vector<string>::iterator foundit;
        foundit = find(history.begin(), history.end(), hi);
        if (foundit != history.end())
        {
            cout << "CYCLE LENGTH: " << history.end() - foundit << endl;
            break;
        }

        history.push_back(hi);
        int selected = choose(arr, size);
        redistribute(arr, size, selected);
    }
    cout << history.size()<<endl;
    return history.size();
}
void test_redistribution_cycle()
{
    int arr[]= {0,2,7,0};
    assert(5 == redistribution_cycle(arr, 4));
}

int main(int argc, char const *argv[])
{
    test_memory_example();
    test_redistribution_cycle();
    int eles[] = {4,10,4,1,8,4,9,14,5,1,14,15,0,15,3,5};
    cout << redistribution_cycle(eles,16) <<  endl;
    return 0;
}