# Chapter 1: The Python Data Model

You can think of the data model as a description of Python as a framework.  
It formalizes the interfaces of the building blocks of the language itself,  
such as sequences, iterators, functions, classes, context managers, and so on.  

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

    Card(rank='7', suit='diamonds')

`len()` function returns the number of cards in it.  

```python
deck = FrenchDeck()
len(deck)
```

    52

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

    Card(rank='7', suit='spades')

```python
choice(deck)
```

    Card(rank='10', suit='hearts')

Slicing support, because `__getitem__`  delegates to the [] oeprator of `self._cards`  

```python
deck[:3]
```

```python
[Card(rank='2', suit='spades'), Card(rank='3', suit='spades'), Card(rank='4', suit='spades')]
```

```python
deck[12::13]
```

```python
[Card(rank='A', suit='spades'), Card(rank='A', suit='diamonds'), Card(rank='A', suit='clubs'), Card(rank='A', suit='hearts')]
```

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

```python
True
```

```python
Card('7', 'beasts') in deck
```

```python
False
```

Sorting  

```python
suit_values = dict(spades=3, hearts=2, diamonds=1, clubs=0)

def spades_high(card):
    rank_value = FrenchDeck.ranks.index(card.rank)
    return rank_value * len(suit_values) + suit_values[card.suit]

for card in sorted(deck, key=spades_high):
    print(card)
```

```python
Card(rank='2', suit='clubs')
Card(rank='2', suit='diamonds')
Card(rank='2', suit='hearts')
Card(rank='2', suit='spades')
...
Card(rank='A', suit='clubs')
Card(rank='A', suit='diamonds')
Card(rank='A', suit='hearts')
Card(rank='A', suit='spades')
```
