# Chapter 3: Dictionaries and Sets

---
title: Fluent Python - Chapter 3. Dictionaries and Sets
date: 2020-05-02 20:00:00
categories:
- [Book Notes, Fluent Python]
tags:
- Python
---

The keys must be hashable (str, bytes, numeric types, etc).

```python
a = dict(one=1, two=2, three=3)
b = {'one': 1, 'two': 2, 'three': 3}
c = dict(zip(['one', 'two', 'three'], [1, 2, 3]))
d = dict([('two', 2), ('one', 1), ('three', 3)])
e = dict({'two': 2, 'one': 1, 'three': 3})
a == b == c == d == e
```

    True

## dict Comprehensions

```python
DIAL_CODES = [
  (86, 'China'),
  (91, 'India'),
  (1, 'United States'),
  (62, 'Indonesia'),
  (55, 'Brazil'),
  (92, 'Pakistan'),
  (880, 'Bangladesh'),
  (234, 'Nigeria'),
  (7, 'Russia'),
  (81, 'Japan'),
]

country_code = {country: code for code, country in DIAL_CODES}
country_code
```

    {'Bangladesh': 880,
     'Brazil': 55,
     'China': 86,
     'India': 91,
     'Indonesia': 62,
     'Japan': 81,
     'Nigeria': 234,
     'Pakistan': 92,
     'Russia': 7,
     'United States': 1}

## Handling Missing Keys with setdefault

```python
my_dict.setdefault(key, []).append(new_value)
# is the same as running...
if key not in my_dict:
    my_dict[key] = []
my_dict[key].append(new_value)
```

or use `defaultdict(list)`

## The <span class="underline"><span class="underline">missing</span></span> Method

```python
class StrKeyDict(collections.UserDict):
    def __missing__(self, key):
        if isinstance(key, str):
            raise KeyError(key)
        return self[str(key)]

    def __contains__(self, key):
        return str(key) in self.data

    def __setitem__(self, key, item):
        self.data[str(key)] = item
```

## set Literals

```python
s = {1}
type(s)
```

    <class 'set'>

## set Comprehensions

```python
from unicodedata import name
{chr(i) for i in range(32, 256) if 'SIGN' in name(chr(i),'')}
```

    {'#',
     '$',
     '%',
     '+',
     '<',
     '=',
     '>',
     '¢',
     '£',
     '¤',
     '¥',
     '§',
     '©',
     '¬',
     '®',
     '°',
     '±',
     'µ',
     '¶',
     '×',
     '÷'}
