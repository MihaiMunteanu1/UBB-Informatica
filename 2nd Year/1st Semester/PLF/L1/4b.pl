
elimina([],_,_,[]).

elimina([_|L],I,N,R):-
    I =:= N,
    !,
    I1 is I+1,
    elimina(L,I1,N,R).


elimina([H|L],I,N,[H|R]):-
    I1 is I+1,
    elimina(L,I1,N,R).


elimin(L,N,R):-elimina(L,1,N,R).
