import time
import random

y = ["A", "B", "C"]


def print_parts():
    x = [1,2,3,4]
    global y
    y = ["D", "E"]
    print(x, y)


def tuple_play():
    start = time.time()
    print("\n >> TUPLE >>>")
    x = (1, 2, 3, 123, 2, [123,456,789], "A", "B", 'C', "123")
    print(x[0])
    print(len(x ))
    # for i in x:
    #     print(i)
    print("\n >> TUPLE run in ", time.time() - start)

def set_play():
    start_time = time.time()
    print("\n SETS >>>>")
    x = {1,2,3,2,"A", "B", "C"}
    x.add('a')
    x.add('f')
    y = set('a')
    print(len(x))
    print(y)
    print(">> SET run in >>>", time.time()-start_time )

def list_play():
    start_time = time.time()
    list = [x for x in range(0, 50)]
    print(len(list))
    print(list)
    list[len(list):] = [100]
    list.append(100)
    #print(list.pop())
    print(len(list))
    for idx, value in enumerate(list):
        print('idx {ix} value {vle}'.format(ix=idx, vle=value))
    print(">>> LIST took ", time.time() - start_time)

def dict_play():
    start_time = time.time()
    list_keys = {'A' + str(x): x + random.randrange(0, 50) for x in range(0, 100)}
    print(list_keys)
    print(len(list_keys))
    print(list_keys['A0'])
    print('  >>>> DICT TOOK ', time.time() - start_time)


#tuple_play()
#set_play()
list_play()
dict_play()
