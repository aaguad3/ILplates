# ILplates

Like many states in the USA, the state of Illinois allows car owners to order specialized license plates, e.g. “ILUVUIC”.
We will use hashing to efficiently process fines against cars with specialized license plates.

Rules for specialized license plates
There are a variety of formats for specialized Illinois license plates; this program accepts both Personalized and Vanity plates.

Personalized examples: 
A 1, B 99, ZZZZZ 1, ABCDEF 3 

Vanity examples:
007, 1, 42, X, AAA, ZZZEFGH 

The hash function returns a valid index into the hash table if the license plate fits one of the formats above;
if the license plate does not follow one of these formats, the hash function returns -1.

License plates are read through "ILplates.h" with hashing results displayed. 
