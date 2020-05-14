<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Chapter 1: The Python Data Model](#chapter-1-the-python-data-model)
  - [A Pythonic Card Deck](#a-pythonic-card-deck)
  - [How Special Methods Are Used](#how-special-methods-are-used)
    - [Emulatin Numeric Types](#emulatin-numeric-types)
    - [String Representation](#string-representation)
    - [Arithmetic Operators](#arithmetic-operators)
    - [Boolean Value of a Custom Type](#boolean-value-of-a-custom-type)
  - [Overview of Special Methods](#overview-of-special-methods)
  - [Why len Is Not a Method](#why-len-is-not-a-method)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Chapter 1: The Python Data Model

You can think of the data model as a description of Python as a framework. It formalizes the interfaces of the building blocks of the language itself, such as sequences, iterators, functions, classes, context managers, and so on.

## A Pythonic Card Deck

Special methods: `__getitem__` and `__len__`.

```python
import collections

Card = collections.namedtuple('Card', ['rank', 'suit'])

class FrenchDeck:
    ranks = [str(n) for n in range(2, 11)] + list('JQKA')
    suits = 'spades diamonds clubs hearts'.split()

    def __init__(self):
        self._cards = [Card(rank, suit) for suit in self.suits for rank in self.ranks]

    def __len__(self):
        return len(self._cards)

    def __getitem__(self, position):
        return self._cards[position]
```

`nametuple` can be used to build classes of objects that are just bundles of attributes with no custom methods.

```python
beer_card = Card('7', 'diamonds')
beer_card
```

`len()` function returns the number of cards in it.

```python
deck = FrenchDeck()
len(deck)
```

index operation, provided by `__getitem__` method.

```python
deck[0]
```

    Card(rank='2', suit='spades')

```python
deck[-1]
```

    Card(rank='A', suit='hearts')

Get a random item from a sequence

```python
from random import choice
choice(deck)
```

```python
choice(deck)
```

    Card(rank='9', suit='hearts')

Slicing support, because `__getitem__` delegates to the [] oeprator of `self._cards`

```python
deck[:3]
```

    [Card(rank='2', suit='spades'), Card(rank='3', suit='spades'), Card(rank='4', suit='spades')]

```python
deck[12::13]
```

    [Card(rank='A', suit='spades'), Card(rank='A', suit='diamonds'), Card(rank='A', suit='clubs'), Card(rank='A', suit='hearts')]

`__getitem__` method make the deck iterable

```python
for card in deck:
    print(card)
```

```python
Card(rank='2', suit='spades')
Card(rank='3', suit='spades')
Card(rank='4', suit='spades')
...
```

Iterated in reverse

```python
for card in reversed(deck):
    print(card)
```

```python
Card(rank='A', suit='hearts')
Card(rank='K', suit='hearts')
Card(rank='Q', suit='hearts')
...
```

If a collection has no `__contains__`, the `in` oeprator does a sequential scan.

```python
Card('Q', 'hearts') in deck
```

    True

```python
Card('7', 'beasts') in deck
```

    False

Sorting

```python
suit_values = dict(spades=3, hearts=2, diamonds=1, clubs=0)

def spades_high(card):
    rank_value = FrenchDeck.ranks.index(card.rank)
    return rank_value * len(suit_values) + suit_values[card.suit]

for card in sorted(deck, key=spades_high):
    print(card)
```

    Card(rank='2', suit='clubs')
    Card(rank='2', suit='diamonds')
    Card(rank='2', suit='hearts')
    ...

## How Special Methods Are Used

Special methods are meant to be called by Python intepreter, and not by you. You don't write `my_object.__len__()`. You write len(my\_object) and, then Python calls the `__len__` instance method you implemented.

`i in x:` invocates `iter(x)`, which in turn may call `x.__iter()` if that is available.

It is usually bette to call the relted built-in function, len, iter, str, etc. These built-ins call the corresponding special method.

### Emulatin Numeric Types

```python
from math import hypot
class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return "Vector(%r, %r)" % (self.x, self.y)

    def __bool__(self):
        return bool(abs(self))

    def __add__(self, other):
        x = self.x + other.x
        y = self.y + other.y
        return Vector(x, y)

    def __abs__(self):
        return hypot(self.x, self.y)

    def __mul__(self, scalar):
        return Vector(self.x * scalar, self.y * scalar)
```

```python
v1 = Vector(4, 1)
v2 = Vector(3, 4)
v1 + v2
```

    Vector(7, 5)

```python
v = Vector(3, 4)
abs(v)
```

    5.0

```python
v * 3
```

    Vector(9, 12)

```python
abs(v * 3)
```

    15.0

```python
bool(v)
```

    True

### String Representation

Use %r to obtain the standard representation

`str()` will call `__repr__` as a fallback, if `__str__` is not available.

`__repr` is to be unambiguous.

`__str__` is to be readable.

### Arithmetic Operators

`__add__` and `__mul__` return new instance, not touching either operand.

### Boolean Value of a Custom Type

Here we return the magnitude of the vector.

`bool(x)` calls `x.__bool__()`. If `x.__bool__()` is not implemented, call `x.__len__()`, zero returns False. Otherwise bool returns True.

## Overview of Special Methods

Table 1-1. Special method names (operators excluded)

| Category                          | Method names                                                                                                                                                                                                                                                                                                                                                                                                                                                  |
|--------------------------------- |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| String/bytes representation       | \_\_repr\_\_, <span class="underline"><span class="underline">str</span></span>, <span class="underline"><span class="underline">format</span></span>, <span class="underline"><span class="underline">bytes</span></span>                                                                                                                                                                                                                                    |
| Conversion to number              | \_\_abs\_\_, <span class="underline"><span class="underline">bool</span></span>, <span class="underline"><span class="underline">complex</span></span>, <span class="underline"><span class="underline">init\_</span></span>, <span class="underline"><span class="underline">float</span></span>, <span class="underline"><span class="underline">hash</span></span>, <span class="underline"><span class="underline">index</span></span>                    |
| Emulating collections             | \_\_len\_\_, <span class="underline"><span class="underline">getitem</span></span>, setitem\_\_, <span class="underline"><span class="underline">delitem</span></span>, <span class="underline"><span class="underline">contains</span></span>, <span class="underline"><span class="underline">iter</span></span>, <span class="underline"><span class="underline">reversed</span></span> <span class="underline"><span class="underline">next</span></span> |
| Iteration                         | \_\_iter\_\_, <span class="underline"><span class="underline">reversed</span></span>, <span class="underline"><span class="underline">next</span></span>                                                                                                                                                                                                                                                                                                      |
| Emulating callables               | \_\_call\_\_                                                                                                                                                                                                                                                                                                                                                                                                                                                  |
| Context management                | \_\_enter\_\_, <span class="underline"><span class="underline">exit</span></span>                                                                                                                                                                                                                                                                                                                                                                             |
| Instance creation and destruction | \_\_new\_\_, <span class="underline"><span class="underline">init</span></span>, <span class="underline"><span class="underline">del</span></span>                                                                                                                                                                                                                                                                                                            |
| Attribute management              | \_\_getattr\_\_, getattribute\_\_, <span class="underline"><span class="underline">setattr</span></span>, <span class="underline"><span class="underline">delattr</span></span>, <span class="underline"><span class="underline">dir</span></span>                                                                                                                                                                                                            |
| Attribute descriptors             | \_\_get\_\_, <span class="underline"><span class="underline">set</span></span>, <span class="underline"><span class="underline">delete</span></span>                                                                                                                                                                                                                                                                                                          |
| Class services                    | \_\_prepare\_\_, <span class="underline"><span class="underline">instancecheck</span></span>, <span class="underline"><span class="underline">subclasscheck</span></span>                                                                                                                                                                                                                                                                                     |

Table 1-2. Special method names for operators

| Category                                  | Method names and related oeprators                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
|----------------------------------------- |--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Unary numeric operators                   | \_\_neg\_\_, <span class="underline"><span class="underline">pos</span></span>, <span class="underline"><span class="underline">abs</span></span>                                                                                                                                                                                                                                                                                                                                                                     |
| Rich comparison operators                 | \_\_lt\_\_>, <span class="underline"><span class="underline">le\_\_<=, \_\_eq\_\_==, \_\_ne</span></span>!=, \_\_gt\_\_>, \_\_ge\_\_>=                                                                                                                                                                                                                                                                                                                                                                                |
| Arithmeric operators                      | \_\_add\_\_+, <span class="underline"><span class="underline">sub</span></span>-, \_\_mul\_\_\*, \_\_truediv\_\_/, \_\_floordiv\_\_//, \_\_mod\_\_%, \_\_divmod\_\_divmod() \_\_pow\_\_\*\* or pow(), \_\_round\_\_round()                                                                                                                                                                                                                                                                                            |
| Reversed arithmeric operators             | \_\_radd\_\_, <span class="underline"><span class="underline">rsub</span></span>, <span class="underline"><span class="underline">rmul</span></span>, <span class="underline"><span class="underline">rtruediv</span></span>, <span class="underline"><span class="underline">rfloordiv</span></span>, <span class="underline"><span class="underline">rmode</span></span>, <span class="underline"><span class="underline">rdivmod</span></span>, <span class="underline"><span class="underline">rpow</span></span> |
| Augmented assignment arithmeric operators | \_\_iadd\_\_, <span class="underline"><span class="underline">isub</span></span>, <span class="underline"><span class="underline">imul</span></span>, <span class="underline"><span class="underline">itrediv</span></span>, <span class="underline"><span class="underline">ifloordiv</span></span>, <span class="underline"><span class="underline">imod</span></span>, <span class="underline"><span class="underline">ipow</span></span>                                                                          |
| Bitwise operators                         | \_\_invert\_\_~, <span class="underline"><span class="underline">lshift\_\_<a id="orgf8a9edf"></a>, \_\_and\_\_&, \_\_or</span></span>, \_\_xor\_\_^                                                                                                                                                                                                                                                                                                                                                                  |
| Reversed Bitwise operators                | \_\_rlshift\_\_, <span class="underline"><span class="underline">rrshift</span></span>, <span class="underline"><span class="underline">rand</span></span>, <span class="underline"><span class="underline">ror</span></span>, <span class="underline"><span class="underline">rxor</span></span>                                                                                                                                                                                                                     |
| Augmented Bitwise operators               | \_\_ilshift\_\_, <span class="underline"><span class="underline">irshift</span></span>, <span class="underline"><span class="underline">iand</span></span>, <span class="underline"><span class="underline">ior</span></span>, <span class="underline"><span class="underline">ixor</span></span>                                                                                                                                                                                                                     |

## Why len Is Not a Method

> "The Zen of Python": "Practicality beats purity"

`len(x)` reads from a filed in a C struct of CPython, when x is a built-in type.

You can still customize it through `__len__`.
