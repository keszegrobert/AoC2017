import unittest

ST_RIGHT = 0
ST_UP = 1
ST_LEFT = 2
ST_DOWN = 3


class ManhattanDistance:
    def __init__(self):
        self.positions = {}
        self.positions[(0, 0)] = 1

    def next(self, r):
        (state, right, up) = r
        if state == ST_RIGHT:
            right += 1
            if right == -up + 1:
                state = ST_UP
        elif state == ST_UP:
            up += 1
            if right == up:
                state = ST_LEFT
        elif state == ST_LEFT:
            right -= 1
            if right == -up:
                state = ST_DOWN
        elif state == ST_DOWN:
            up -= 1
            if right == up:
                state = ST_RIGHT

        return (state, right, up)

    def compute(self, input):
        state = (ST_RIGHT, 0, 0)
        for i in xrange(1, input):
            state = self.next(state)
        s, r, u = state
        return abs(r) + abs(u)

    def get_num(self, posx, posy):
        result = self.positions.get((posx, posy), 0)
        return result

    def number_on_seq(self, input):
        if input <= 0:
            return 0
        state = (ST_RIGHT, 0, 0)
        result = 1
        for i in xrange(1, input):
            state = self.next(state)
            s, right, up = state
            result = self.get_num(right - 1, up + 1) + \
                self.get_num(right - 1, up) + \
                self.get_num(right - 1, up - 1) + \
                self.get_num(right, up - 1) + \
                self.get_num(right, up) + \
                self.get_num(right, up + 1) + \
                self.get_num(right + 1, up + 1) + \
                self.get_num(right + 1, up) + \
                self.get_num(right + 1, up - 1)
            self.positions[(right, up)] = result
        s, r, u = state
        return result

    def part1(self, input):
        return self.compute(input)

    def part2(self, input):
        if input <= 0:
            return 0
        state = (ST_RIGHT, 0, 0)
        result = 1
        while result < input:
            state = self.next(state)
            s, right, up = state
            result = self.get_num(right - 1, up + 1) + \
                self.get_num(right - 1, up) + \
                self.get_num(right - 1, up - 1) + \
                self.get_num(right, up - 1) + \
                self.get_num(right, up) + \
                self.get_num(right, up + 1) + \
                self.get_num(right + 1, up + 1) + \
                self.get_num(right + 1, up) + \
                self.get_num(right + 1, up - 1)
            self.positions[(right, up)] = result
        s, r, u = state
        return result


class TestTaxicab(unittest.TestCase):

    def check_state(self, actual, expected):
        md = ManhattanDistance()
        n = md.next(actual)
        self.assertEqual(n, expected)

    def test_next_state(self):
        path = [
            (ST_RIGHT, 0, 0),
            (ST_UP, 1, 0),
            (ST_LEFT, 1, 1),
            (ST_LEFT, 0, 1),
            (ST_DOWN, -1, 1),
            (ST_DOWN, -1, 0),
            (ST_RIGHT, -1, -1),
            (ST_RIGHT, 0, -1),
            (ST_RIGHT, 1, -1),
            (ST_UP, 2, -1),
        ]
        for i in xrange(0, len(path) - 1):
            self.check_state(path[i], path[i + 1])

    def check_manhattan_distance(self, input, expected):
        md = ManhattanDistance()
        self.assertEqual(md.compute(input), expected)

    def test_manhattan_distance(self):
        self.check_manhattan_distance(1, 0)
        self.check_manhattan_distance(12, 3)
        self.check_manhattan_distance(23, 2)
        self.check_manhattan_distance(1024, 31)

    def check_number_on_seq(self, input, expected):
        md = ManhattanDistance()
        self.assertEqual(md.number_on_seq(input), expected)

    def test_expected_sequence(self):
        expected_sequence = [
            0, 1, 1, 2, 4,
            5, 10, 11, 23, 25,
            26, 54, 57, 59, 122,
            133, 142, 147, 304, 330,
            351, 362, 747, 806, 880
        ]
        for i in range(0, 25):
            self.check_number_on_seq(i, expected_sequence[i])

    def test_part1(self):
        md = ManhattanDistance()
        self.assertEqual(md.part1(347991), 480)

    def test_part2(self):
        md = ManhattanDistance()
        self.assertEqual(md.part2(347991), 349975)


if __name__ == '__main__':
    unittest.main()
