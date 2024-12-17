%elim nr care se repeta

nr_apar(_,[],0).

nr_apar(X,[X|L],C):-
    !,
    nr_apar(X,L,C1),
    C is C1+1.

nr_apar(X,[_|L],C):-
    nr_apar(X,L,C).

elimElem([],_,[]).

elimElem([E|T],E,R):-
    !,
    elimElem(T,E,R).

elimElem([H|T],E,[H|R]):-
    H \== E,
    elimElem(T,E,R).

elimRep([],[]).

elimRep([H|T],R):-
    nr_apar(H,T,C),
    C > 0,
    !,
    elimElem(T,H,R1),
    elimRep(R1,R).

elimRep([H|T],[H|R]):-
    elimRep(T,R).


