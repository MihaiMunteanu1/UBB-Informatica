%[1,2,3,4,5] => [[2,4],[1,3,5]] si sa se calc nr de nr pare/impare

listeParImpar([], 0, 0, [], []).
listeParImpar([H | T], I1, P, [H | RI], RP) :-
        H mod 2 =:= 1, !,
        listeParImpar(T, I, P, RI, RP),
        I1 is I + 1.
listeParImpar([H | T], I, P1, RI, [H | RP]) :-
        listeParImpar(T, I, P, RI, RP),
        P1 is P + 1.

listeParImpar(L, I, P, [RI, RP]) :- listeParImpar(L, I, P, RI, RP).

