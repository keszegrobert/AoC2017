#include <iostream>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

typedef pair<int,int> POSITION;

class TaxicabGeometry{
    map<POSITION,int> mapPositions;

public:
    TaxicabGeometry()
    {
        mapPositions[POSITION(0,0)]=1;
    }

    int getNum(int up, int right)
    {
        POSITION pos = POSITION(up,right);
        map<POSITION,int>::iterator foundit = mapPositions.find(pos);

        if (foundit != mapPositions.end()) 
            return mapPositions[pos];
        else
            return 0;
    }

    enum STATES {
        ST_RIGHT,
        ST_UP,
        ST_LEFT,
        ST_DOWN
    };

    int next(STATES& state, int& right, int& up)
    {
        // cout << "state:" << state << "\tx:" << right << "\ty:" << up << endl;
        switch (state){
        case ST_RIGHT:
            right++;
            if (-up == right-1)
                state = ST_UP;
            break;
        case ST_UP:
            up++;
            if (up == right)
                state = ST_LEFT;
            break;
        case ST_LEFT:
            right--;
            if (up == -right)
                state = ST_DOWN;
            break;
        case ST_DOWN:
            up--;
            if (up == right)
                state = ST_RIGHT;
            break;
        }
        int res = getNum(right-1,up+1) + getNum(right,up+1) + getNum(right+1,up+1)
                + getNum(right-1,up+0) + getNum(right,up+0) + getNum(right+1,up+0)
                + getNum(right-1,up-1) + getNum(right,up-1) + getNum(right+1,up-1);
        return res;
    }

    int number_on_seq(int input, int& up, int& right)
    {
        if (input <= 0)
            return 0;
        int sum = 0;
        int result = mapPositions[POSITION(0,0)];
        int i = 0;
        right = 0;
        up = 0;
        STATES state = ST_RIGHT;
        for (int i = 1; i < input; ++i)
        {
            result = next(state, right, up);
            mapPositions.insert(pair<POSITION,int>(POSITION(right,up), result));
        }

        return result;
    }

    int get_largest_after(int input)
    {
        if (input <= 0)
            return 0;
        int sum = 0;
        int result = mapPositions[POSITION(0,0)];
        int i = 0;
        int right = 0;
        int up = 0;
        STATES state = ST_RIGHT;
        while (result < input)
        {
            result = next(state, right, up);
            mapPositions.insert(pair<POSITION,int>(POSITION(right,up), result));
        }
        return result;
    }
};

void check_state(
    TaxicabGeometry::STATES in_state, int in_right, int in_up, 
    TaxicabGeometry::STATES exp_state, int exp_right, int exp_up)
{
    TaxicabGeometry::STATES actual_state = in_state;
    int actual_right = in_right;
    int actual_up = in_up;
    TaxicabGeometry tg;
    tg.next(actual_state, actual_right, actual_up);
    assert(exp_state == actual_state);
    assert(exp_up == actual_up);
    assert(exp_right == actual_right);
}

struct STATE{
    TaxicabGeometry::STATES state;
    int right;
    int up;
    STATE(TaxicabGeometry::STATES s, int r, int u){
        state = s;
        right =r;
        up = u;
    }
};

void check_state(STATE& s1,STATE& s2)
{
    TaxicabGeometry::STATES actual_state = s1.state;
    int actual_right = s1.right;
    int actual_up = s1.up;

    TaxicabGeometry tg;
    tg.next(actual_state, actual_right, actual_up);

    assert(s2.state == actual_state);
    assert(s2.up == actual_up);
    assert(s2.right == actual_right);
}

void test_state_machine()
{
    vector<STATE> state_sequence;
    state_sequence.push_back(STATE(TaxicabGeometry::ST_RIGHT, 0, 0));
    state_sequence.push_back(STATE(TaxicabGeometry::ST_UP, 1, 0));
    state_sequence.push_back(STATE(TaxicabGeometry::ST_LEFT, 1, 1));
    state_sequence.push_back(STATE(TaxicabGeometry::ST_LEFT, 0, 1));
    state_sequence.push_back(STATE(TaxicabGeometry::ST_DOWN, -1, 1));
    state_sequence.push_back(STATE(TaxicabGeometry::ST_DOWN, -1, 0));
    state_sequence.push_back(STATE(TaxicabGeometry::ST_RIGHT, -1, -1));
    state_sequence.push_back(STATE(TaxicabGeometry::ST_RIGHT, 0, -1));
    state_sequence.push_back(STATE(TaxicabGeometry::ST_UP, 2, -1));
    vector<STATE>::iterator it;

    for (it = state_sequence.begin(); it+1 != state_sequence.end()-1; ++it)
    {
        check_state(*it, *(it+1));
    }
}

void check_number_on_seq(int input, int expected)
{
    int up = 0;
    int right = 0;
    TaxicabGeometry tg;
    int result = tg.number_on_seq(input, up, right);
    assert(result == expected);    
}

void test_expected_sequence()
{
    int expected_sequence[] = {
        0,1,1,2,4,
        5,10,11,23,25,
        26,54,57,59,122,
        133,142,147,304,330,
        351,362,747,806,880
    };
    for (int i=0; i<25; ++i)
        check_number_on_seq(i, expected_sequence[i]);
}

int main (void)
{
    test_state_machine();
    test_expected_sequence();
    TaxicabGeometry tg;
    cout << "result is: " << tg.get_largest_after(347991) << endl;
}