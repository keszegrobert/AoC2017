import unittest


def produce_sum(seq):
    if len(seq) == 0:
        return 0
    offset = int(len(seq) / 2)
    sum = 0
    for i in range(0, offset):
        second = i + offset
        if second > len(seq):
            second -= len(seq)
        if seq[i] == seq[second]:
            sum += 2 * (ord(seq[i]) - ord('0'))
    return sum


class TestProduceSum(unittest.TestCase):
    def test_produce_sum(self):
        self.assertEqual(produce_sum('1212'), 6)
        self.assertEqual(produce_sum('1221'), 0)
        self.assertEqual(produce_sum('123425'), 4)
        self.assertEqual(produce_sum('123123'), 12)
        self.assertEqual(produce_sum('12131415'), 4)


if __name__ == '__main__':
    with open('input.txt', 'r') as f:
        data = f.read()
        print produce_sum(data)
    unittest.main()
