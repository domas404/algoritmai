import operator

relations = [(1,10),(1,6),(1,2),(2,8),(2,3),(3,4),(4,5),(4,7),(6,7),(6,9),(7,8),(8,9),(5,10)]
vertices = [1,2,3,4,5,6,7,8,9,10]
# saugomi kiekvienos virsunes atributai
class vertex:
    def __init__(self, value, color, start_time, end_time, parent):
        self.value = value
        self.color = color
        self.start_time = start_time
        self.end_time = end_time
        self.parent = parent

graph = [] # virsuniu klases list'as
for i in range(len(vertices)):
    graph.append(vertex(vertices[i], 'balta', 0, 0, None))

laikas = 0
depth = [] # virsunes, surasytos depth first radimo tvarka

def visit(u, laikas):
    u.color = 'pilka'
    laikas += 1
    u.start_time = laikas
    v = findRelatedVertices(relations, u.value)
    v = sorted(v, key=operator.attrgetter('value'))
    for j in range(len(v)):
        if v[j].color == 'balta':
            v[j].parent = u.value
            laikas, v[j] = visit(v[j], laikas)
    u.color = 'juoda'
    depth.append(u.value)
    laikas += 1
    u.end_time = laikas
    return laikas, u

# ieskoma taku siejanciu su kitomis virsunemis ir grazinamos virsunes i kurias galima nueiti is virsunes x
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

print("Eiles tvarka rastos virsunes - ",depth)

for i in range(len(vertices)):
    print("Virsune",graph[i].value,"buvo apdorota per",graph[i].end_time-graph[i].start_time,"zingsniu")