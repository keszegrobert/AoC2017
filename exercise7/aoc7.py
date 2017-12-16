parents = {}
with open('input.txt', 'r') as f:
    for line in f.readlines():
        nodearr = line.split()
        for node in nodearr[3:]:
            parents[node[:-1]] = nodearr[0]
bottom = parents.itervalues().next()
while bottom in parents:
    bottom = parents[bottom]
print bottom
