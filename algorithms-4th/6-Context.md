# 6. Context

Intractablilty.

Exponential running time.

Search problems

> A search problem is a problem having solutions with the property that the time needed to certify that any solution is correct is bounded by a polynomial in size of the input. We say that an algorithm solves a search problem if, given any input, it either produces a solution or reports that none exists.

> NP is the set of all search problems.

The N in NP stands for nondeterminism. It represents the idea that one way to extend the power of a computer is to endow it with the power of nondeterminism: to assert that when an algorithm is faced with a choice of several options, it has the power to "guess" the right one.

> P is the set of all search problems that can be solved in polynomial time.

The main question

**Does P = NP?**

No one has been able to find a single probelm that can be proven to be in NP but not in P.

Ohter ways of posing the question:

1.  Are there any hard-to-solve search problems?
2.  Would we be able to solve some search prolems more efficiently if we could build a nondeterministic computing device?

Virtually no one believes that P = NP, and a considerable amount of effort has gone into proving the contrary, but this remains the outstanding open research problem in computer science.

**NP-completeness**

> A search problem is said to be NP-complete if all problems in NP poly-time reduce to A.

To prove that a search problem is in P, we need to exhibit a polynomial-time algorithm for solving it, perhaps by reducing it to a problem known to be in P. To prove that a problem in NP is NP-complete, we need to show that some known NP-complete problem is poly-time reducible to it: that is, that a polynomial- time algorithm for the new problem could be used to solve the NP-complete problem, and then could, in turn, be used to solve all problems in NP.
