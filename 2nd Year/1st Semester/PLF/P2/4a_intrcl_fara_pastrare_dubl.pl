%INTERCLASARE 2 LISTE SORTATE

intr([],[],[]):-!.

intr([H|L1],[H1|L2],[H|R]):-
    H < H1,
    !,
    intr(L1,[H1|L2],R).

intr([H|L1],[H1|L2],[H1|R]):-
    H1 < H,
    !,
    intr([H|L1],L2,R).

intr([H|L1],[H|L2],[H|R]):-
    !,
    intr(L1,L2,R).

intr([H|L1],[],[H|R]):-
    intr(L1,[],R).

intr([],[H|L2],[H|R]):-
    intr([],L2,R).

