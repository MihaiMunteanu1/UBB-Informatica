%PREDECESORUL [1,0,0] => [9,9]

inverseaza_aux([],Cp,Cp).

inverseaza_aux([H|L],Cp,R):-
    inverseaza_aux(L,[H|Cp],R).

inverseaza(L,R):-inverseaza_aux(L,[],R).

predecesor([], 0, []) :- !.

predecesor([H | T], TR, [9 | R]) :-
        S is H - TR,
        S < 0, !,
        predecesor(T, 1, R).
predecesor([H | T], TR, [S | R]) :-
        S is H - TR,
        predecesor(T, 0, R).


predecesor([0], [-1]) :- !.

predecesor(L, R) :-
        inverseaza(L, R1),
        predecesor(R1, 1, R2),
        inverseaza(R2, R).
