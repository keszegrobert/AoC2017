import unittest


def produce_sum(seq):
    if len(seq) == 0:
        return 0

    previous = seq[-1]
    sum = 0
    for i in range(0, len(seq)):
        if seq[i] == previous:
            sum += ord(seq[i]) - ord('0')
        previous = seq[i]

    return sum


class TestProduceSum(unittest.TestCase):
    def test_produce_sum(self):
        self.assertEqual(produce_sum('1122'), 3)
        self.assertEqual(produce_sum('1111'), 4)
        self.assertEqual(produce_sum('1234'), 0)
        self.assertEqual(produce_sum('91212129'), 9)


if __name__ == '__main__':
    with open('input.txt', 'r') as f:
        data = f.read()
        print produce_sum(data)
    unittest.main()
