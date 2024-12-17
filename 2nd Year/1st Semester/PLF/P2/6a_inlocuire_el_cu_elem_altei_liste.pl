% [1,2,3],1,[4,5] => [4,5,2,3] INLOCUIRE ELEM CU O LISTA

inlocuire([],_,[],[]).

inlocuire([],_,L,L):-!.

inlocuire([E|T],E,[H],[H|R]):-
    !,
    inlocuire(T,E,[],R).


inlocuire([E|T],E,[H|L],[H|R]):-
    !,
    inlocuire([E|T],E,L,R).


inlocuire([H|T],E,L,[H|R]):-
    inlocuire(T,E,L,R).
