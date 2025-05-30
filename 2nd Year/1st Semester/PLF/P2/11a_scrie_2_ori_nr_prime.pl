%dublam nr prime

estePrim(E, _) :-
        E < 2, !,
        fail.
estePrim(E, D) :-
        E < D * D, !.
estePrim(E, D) :-
        not(E mod D =:= 0),
        D1 is D + 1,
        estePrim(E, D1).

dubPrim([],[]).

dubPrim([H|T],[H,H|R]):-
    estePrim(H,2),
    !,
    dubPrim(T, R).

dubPrim([H|T],[H|R]):-
    dubPrim(T, R).
