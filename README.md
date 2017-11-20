# GNU Bison fork with alternative GLR algorithm

[![Build Status](https://travis-ci.org/rofirrim/bison.svg?branch=master)](https://travis-ci.org/rofirrim/bison)

See [Elkhound: A Fast, Practical GLR Parser Generator](https://people.eecs.berkeley.edu/~necula/Papers/elkhound_tr.pdf)
for the TR about this algorithm.

This fork aims at implementing this algorithm as an alternative of the existing
GLR algorithm of Bison (we call this algorithm *Stack-GLR*).

This project does not pretend to replace the existing Stack-GLR implementation
in Bison because is very good for almost all situations.

That said, there are some circumstances in which Stack-GLR algorithm behaves
exponentially. This is a [documented fact in Bison](https://www.gnu.org/software/bison/manual/html_node/Generalized-LR-Parsing.html).

The Elkhound algorithm provides an asymptotically better algorithm at the cost
of a higher overhead. Instead of duplicating stacks it represents the parsing
using a graph. We want to use an algorithm based on Elkound that we call
*Graph-GLR*.

## Goals

 - Provide an alternative implementation of GLR (Graph-GLR) for GNU bison based on the Elkhound algorithm.
 - Make it as production ready as Stack-GLR algorithm.
   - This means that `make check` should pass and check both algorithms.
 - Make Graph-GLR reasonably competitive respect Stack-GLR
   - We accept that the performance of Graph-GLR will always be behind that of Stack-GLR.

## Non-goals

 - Make Graph-GLR the new GLR default of Bison.
 - Make the algorithm match or exceed the performance of the Stack-GLR algoritm.
