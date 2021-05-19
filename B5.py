
relations = [(3,12),(2,6),(5,7),(5,12),(2,8),(1,2),(1,9),(1,10),(4,11),(4,10),(10,12)]
vertices = [1,2,3,4,5,6,7,8,9,10,11,12]

class vertex:
    def __init__(self, value, color, start_time, end_time, parent):
        self.value = value
        self.color = color
        self.start_time = start_time
        self.end_time = end_time
        self.parent = parent

graph = []
for i in range(len(vertices)):
    graph.append(vertex(vertices[i], 'balta', 0, 0, None))
laikas = 0
depth = [] # apdorojimo eiles tvarka rastos virsunes

def visit(u, laikas):
    u.color = 'pilka'
    laikas += 1
    u.start_time = laikas
    v = findRelatedVertices(relations, u.value)
    for j in range(len(v)):
        if v[j].color == 'balta':
            v[j].parent = u.value
            laikas, v[j] = visit(v[j], laikas)
    u.color = 'juoda'
    depth.append(u.value)
    laikas += 1
    u.end_time = laikas
    return laikas, u

def findRelatedVertices(rel, x):
    ver = []
    tarp = 0
    for i in range(len(rel)):
        if rel[i][0] == x:
            tarp = rel[i][1]
        elif rel[i][1] == x:
            tarp = rel[i][0]
        for j in range(len(graph)):
            if tarp == graph[j].value:
                ver.append(graph[j])
    return ver



for i in range(len(vertices)):
    if graph[i].color == 'balta':
        laikas, graph[i] = visit(graph[i], laikas)

print(depth)

#for i in range(len(vertices)):
    # print(depth[i])
    # print(graph[i].value, graph[i].parent, graph[i].end_time-graph[i].start_time, graph[i].color)