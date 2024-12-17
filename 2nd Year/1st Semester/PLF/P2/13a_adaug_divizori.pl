%DUPA FIECARE ELEM ADAUGA DIV

divizori(E, _, []) :-
    E < 2,
    !.

divizori(E, E, []) :- !.

divizori(E, D, [D | R]) :-
        E mod D =:= 0,
        !,
        D1 is D + 1,
        divizori(E, D1, R).

divizori(E, D, R) :-
        D1 is D + 1,
        divizori(E, D1, R).

concat([],L2,L2).

concat([H|L],L2,[H|R]):-
    concat(L,L2,R).

adauga([],[]).

adauga([H|L],[H|R1]):-
    divizori(H,2,Rez),
    concat(Rez,R,R1),
    adauga(L,R).

