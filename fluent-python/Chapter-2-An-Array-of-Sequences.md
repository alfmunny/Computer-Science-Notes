---
title: Fluent Python - Chapter 2. An Array of Sequences
date: 2020-05-02 20:00:00
categories:
- [Book Notes, Fluent Python]
tags:
- Python

---

Container sequences: can hold different types. They contain references to the objects.

> list, tuple, collections.deque

Flat sequences: can hold one type. They physically sotre the value.

> str, bytes, bytearray, memoryview, array.array

Another way of grouping:

Mutable seuqences:

> list, byte, array.array, collections.deque and memoryview

Immutable sequences:

> tuple, str, bytes

## List Comprehensions and Generator Expressions

**Readability**

List comprehension is meant to do one thing only: to build a new list. It is possible to abuse it to write very incomprehensible code, you should avoid it.

```python
symbols = '$¢£¥€¤'
codes = [ord(symbol) for symbol in symbols]
codes
```

    [36, 162, 163, 165, 8364, 164]

No leak in Python 3

```python
x = 'ABC'
dummy = [ord(x) for x in x]
x
```

    'ABC'

```python
dummy
```

    [65, 66, 67]

**Versus map and filter**

```python
beyond_ascii = [ord(s) for s in symbols if ord(s) > 127]
beyond_ascii
```

    [162, 163, 165, 8364, 164]

```python
beyond_ascii = list(filter(lambda c: c > 127, map(ord, symbols)))
beyond_ascii
```

    [162, 163, 165, 8364, 164]

**Cartesian Products**

Multiple Loops

```python
colors = ['black', 'white']
sizes = ['S', 'M', 'L']
tshirts = [(color, size) for color in colors for size in sizes]
tshirts
```

    [('black', 'S'),
     ('black', 'M'),
     ('black', 'L'),
     ('white', 'S'),
     ('white', 'M'),
     ('white', 'L')]

We can also arrange them by size

```python
colors = ['black', 'white']
sizes = ['S', 'M', 'L']
tshirts = [(color, size) for size in sizes for color in colors]
tshirts
```

    [('black', 'S'),
     ('white', 'S'),
     ('black', 'M'),
     ('white', 'M'),
     ('black', 'L'),
     ('white', 'L')]

**Generator Expressions** To initialize tuples, arrays, and other tyoes of sequences, you can use Generator Expressions (genexps).

Genexps saves memory because it yields items one by one.

Generator Expressions use the same syntax as list comprehension, but are enclosed in parentheses rather than brackets.

```python
symobls = '$¢£¥€¤'
tuple(ord(symbol) for symbol in symbols)
```

    (36, 162, 163, 165, 8364, 164)

If you have millions of items, only to feed the loop, genexp can save the expense of building a list for that.

```python
colors = ['black', 'white']
sizes = ['S', 'M', 'L']
for tshirt in ('%s %s' % (c, s) for c in colors for s in sizes):
    print(tshirt)
```

    black S
    black M
    black L
    white S
    white M
    white L

## Tuples Ate Not Just Immutable Lists

Tuples do double duty:

1.  immutable lists
2.  as records with no field names

### Tuple as Records

```python
lax_coordinates = (33.9425, -118.408056)
city, year, pop, chg, area = ('Tokyo', 2003, 32450, 0.66, 8014)
traveler_ids = [('USA', '31195855'), ('BRA', 'CE342567'), ('ESP', 'XDA205856')]
for passport in sorted(traveler_ids):
    print("%s/%s" % passport)
```

    BRA/CE342567
    ESP/XDA205856
    USA/31195855

```python
for country, _ in traveler_ids:
    print(country)
```

    USA
    BRA
    ESP

### Tuple Unpacking

**parallel assignment**

```python
lax_coordinates = (33.9425, -118.408056)
latitude, longitude = lax_coordinates
latitude
```

    33.9425

```python
longitude
```

    -118.408056

**swap**

```python
a = 1
b = 2
b, a = a, b
print(a, b)
```

    2 1

**Prefixing an argument with a start**

```python
divmod(20, 8) 
```

    (2, 4)

```python
t = (20, 8)
divmod(*t)
```

    (2, 4)

```python
quotient, remainder = divmod(*t)
quotient, remainder
```

    (2, 4)

**Focus on certain part**

```python
import os
_, filename = os.path.split('/home/luciano/.ssh/idrsa.pub')
filename
```

    'idrsa.pub'

**Using \* to grab excess items**

Without a \*, it ignore the rest elements while unpacking.

```python
a, b, rest = range(5)
a, b, rest
```

```python
a, b, *rest = range(5)
a, b, rest
```

    (0, 1, [2, 3, 4])

```python
a,  b, *rest = range(3)
a, b, rest
```

    (0, 1, [2])

Any place

```python
a, *body, c, d = range(5)
a, body, c, d
```

    (0, [1, 2], 3, 4)

```python
*head, b, c, d = range(5)
head, b, c, d
```

    ([0, 1], 2, 3, 4)

### Nested Tuple Unpacking

Unpacking nested tuple, like (a, b, (c, d))

```python
metro_areas = [
    ('Tokyo', 'JP', 36.933, (35.689722, 139.691667)),
    ('Delhi NCR', 'IN', 21.935, (28.613889, 77.208889)),
    ('Mexico City', 'MX', 20.142, (19.433333, -99.133333)),
    ('New York-Newark', 'US', 20.104, (40.808611, -74.020386)),
    ('Sao Paulo', 'BR', 19.649, (-23.547778, -46.635833)),
]

print('{:15} | {:^9} | {:^9}'.format('', 'lat.', 'long.'))
fmt = '{:15} | {:9.4f} | {:9.4f}'

for name, cc, pop, (latitude, longitude) in metro_areas:
    if longitude <= 0:
        print(fmt.format(name, latitude, longitude))
```

                    |   lat.    |   long.  
    Mexico City     |   19.4333 |  -99.1333
    New York-Newark |   40.8086 |  -74.0204
    Sao Paulo       |  -23.5478 |  -46.6358

### Named Tuples

```python
from collections import namedtuple
City = namedtuple('City', 'name country population coordinates')
tokyo = City('Tokyo', 'JP', 36.933, (35.689722, 139.691667))
tokyo
```

    City(name='Tokyo', country='JP', population=36.933, coordinates=(35.689722, 139.691667))

```python
tokyo.population
```

    36.933

```python
tokyo.coordinates
```

    (35.689722, 139.691667)

Named tuple attributes

```python
City._fields
```

    ('name', 'country', 'population', 'coordinates')

```python
LatLong = namedtuple('LatLong', 'lat long')
delhi_data = ('Delhi NCR', 'IN', 21.935, LatLong(28.613889, 77.208889))
delhi = City._make(delhi_data)
delhi._asdict()
```

    {'coordinates': LatLong(lat=28.613889, long=77.208889),
     'country': 'IN',
     'name': 'Delhi NCR',
     'population': 21.935}

You can also use \*.

```python
delhi = City(*delhi_data)
delhi
```

    City(name='Delhi NCR', country='IN', population=21.935, coordinates=LatLong(lat=28.613889, long=77.208889))

### Tuple as Immutable Lists

Tuple supports all list methods that do not involve adding or removing items, like

> s.\_\_iadd\_\_, s.\_\_append\_\_. s.clear(), s.copy(), s.\_\_delitem\_\_, s.\_\_insert\_\_, s.\_\_imul\_\_, s.\_\_reversed\_\_()

reversed(tuple) works without s.\_\_reversed\_\_. (list has it only for optimization)

## Slicing

s[a:b:c]: a to b with a c stride.

```python
s = 'bicycle'
s[::3]
```

    'bye'

```python
s[::-1]
```

    'elcycib'

```python
s[::-2]
```

    'eccb'

```python
l = list(range(10))
l
```

    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

```python
l[2:5] = [20, 30]
l
```

    [0, 1, 20, 30, 5, 6, 7, 8, 9]

```python
del l[5:7]
l
```

    [0, 1, 20, 30, 5, 8, 9]

```python
l[3::2] = [11, 22]
l
```

    [0, 1, 20, 11, 5, 22, 9]

The value must be a iterable

```python
l[2:5] = 100
l
```

```python
l[2:5] = [100]
l
```

    [0, 1, 100, 22, 9]

## Using + and \* with Sequences

How to create list of lists?

Wrong way

```python
weird_board = [['_'] * 3] * 3 # The same reference got added 3 times
weird_board
```

    [['_', '_', '_'], ['_', '_', '_'], ['_', '_', '_']]

```python
weird_board[1][2] = 'O'
weird_board
```

    [['_', '_', 'O'], ['_', '_', 'O'], ['_', '_', 'O']]

Right way

```python
board = [['_'] * 3 for i in range(3)]
board
```

    [['_', '_', '_'], ['_', '_', '_'], ['_', '_', '_']]

## Augmented Assignment with Sequences

+= : `__iadd__`, in-place add

\*= : `__imul__`, in-place multiply

### Puzzle

What happend next?

1.  Error
2.  Or success

```python
t = (1, 2, [30, 40])
t[2] += [50, 60]
```

Answer: Both happened

```python
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: 'tuple' object does not support item assignment
```

```python
t
```

    (1, 2, [30, 40, 50, 60])

Look at bytecode

```python
import dis
dis.dis('s[a] += b')
```

```
1           0 LOAD_NAME                0 (s)
            2 LOAD_NAME                1 (a)
            4 DUP_TOP_TWO
            6 BINARY_SUBSCR                         1
            8 LOAD_NAME                2 (b)
           10 INPLACE_ADD                           2
           12 ROT_THREE
           14 STORE_SUBSCR                          3
           16 LOAD_CONST               0 (None)
           18 RETURN_VALU
```

1.  Put the value of s[a] on TOS (Top Of Stack).
2.  Perform TOS += b. This succeeds if TOS refers to a mutable object.
3.  Assign s[a] = TOS. This fails if s is immutable.

### list.sort and sorted

list.sort: in-place, return None

sorted: create a copy

Two optional arguments:

`reverse`: `key`:

## Managing Ordered Sequences with bisect

bisect and insort.

bisect is alias for bisect\_right.

The element equal to the found value, will be inserted on the right side.

bisect\_left insert the new to the left.

```python
import bisect
import sys
HAYSTACK = [1, 4, 5, 6, 8, 12, 15, 20, 21, 23, 23, 26, 29, 30]
NEEDLES = [0, 1, 2, 5, 8, 10, 22, 23, 29, 30, 31]
ROW_FMT = '{0:2d} @ {1:2d}    {2}{0:<2d}'
def demo(bisect_fn):
  for needle in reversed(NEEDLES):
    position = bisect_fn(HAYSTACK, needle)
    offset = position * '  |'
    print(ROW_FMT.format(needle, position, offset))


bisect_fn = bisect.bisect
print('haystack ->', ' '.join('%2d' % n for n in HAYSTACK))
demo(bisect_fn)
```

    haystack ->  1  4  5  6  8 12 15 20 21 23 23 26 29 30
    31 @ 14      |  |  |  |  |  |  |  |  |  |  |  |  |  |31
    30 @ 14      |  |  |  |  |  |  |  |  |  |  |  |  |  |30
    29 @ 13      |  |  |  |  |  |  |  |  |  |  |  |  |29
    23 @ 11      |  |  |  |  |  |  |  |  |  |  |23
    22 @  9      |  |  |  |  |  |  |  |  |22
    10 @  5      |  |  |  |  |10
     8 @  5      |  |  |  |  |8 
     5 @  3      |  |  |5 
     2 @  1      |2 
     1 @  1      |1 
     0 @  0    0

```python
bisect_fn = bisect.bisect_left
print('haystack ->', ' '.join('%2d' % n for n in HAYSTACK))
demo(bisect_fn)
```

    haystack ->  1  4  5  6  8 12 15 20 21 23 23 26 29 30
    31 @ 14      |  |  |  |  |  |  |  |  |  |  |  |  |  |31
    30 @ 13      |  |  |  |  |  |  |  |  |  |  |  |  |30
    29 @ 12      |  |  |  |  |  |  |  |  |  |  |  |29
    23 @  9      |  |  |  |  |  |  |  |  |23
    22 @  9      |  |  |  |  |  |  |  |  |22
    10 @  5      |  |  |  |  |10
     8 @  4      |  |  |  |8 
     5 @  2      |  |5 
     2 @  1      |2 
     1 @  0    1 
     0 @  0    0

insort keep the order and insert new element.

```python
import bisect
import random

SIZE = 7
random.seed(1729)

my_list = []

for i in range(SIZE):
  new_item = random.randrange(SIZE*2)
  bisect.insort(my_list, new_item)
  print('%2d ->' % new_item, my_list)
```

    10 -> [10]
     0 -> [0, 10]
     6 -> [0, 6, 10]
     8 -> [0, 6, 8, 10]
     7 -> [0, 6, 7, 8, 10]
     2 -> [0, 2, 6, 7, 8, 10]
    10 -> [0, 2, 6, 7, 8, 10, 10]

## When a List is Not the Answer

10 million floating-point values: `array` is more efficient

removing and adding items fro mthe ends of a list: `deque` works faster

a lot of containment checks: `set` are optimized for fast membership checking

### Arrays

If the list will only contain numbers, an `array.array` is more efficient than a list.

```python
from array import array
from random import random
floats = array('d', (random() for i in range(10**7)))
floats[-1]
```

    0.1288579230853678

### Deques

```python
from collections import deque
dq = deque(range(10), maxlen=10)
dq
```

    deque([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], maxlen=10)

```python
dq.rotate(3)
dq
```

    deque([7, 8, 9, 0, 1, 2, 3, 4, 5, 6], maxlen=10)

```python
dq.rotate(-4)
dq
```

    deque([1, 2, 3, 4, 5, 6, 7, 8, 9, 0], maxlen=10)

```python
dq.appendleft(-1)
dq
```

    deque([-1, 1, 2, 3, 4, 5, 6, 7, 8, 9], maxlen=10)

```python
dq.extend([11, 12, 33])
dq
```

    deque([3, 4, 5, 6, 7, 8, 9, 11, 12, 33], maxlen=10)

```python
dq.extendleft([10, 20, 30, 40])
dq
```

    deque([40, 30, 20, 10, 3, 4, 5, 6, 7, 8], maxlen=10)

Other Queues:

`queue`: thread-safe

`multiprocessing`: its own bounded Queue

`asyncio`: Queue, LifoQUeue, PriorityQueue

`heapq`: heappop, heappush
