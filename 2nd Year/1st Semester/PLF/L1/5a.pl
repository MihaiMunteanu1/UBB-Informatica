
sterge([],_,[]).

sterge([E|L],E,R):-
    !,
    sterge(L,E,R).


sterge([H|L],E,[H|R]):-
    H =\= E,
    sterge(L,E,R).


