
substituie([],_,_,[]):-!.

substituie([H|L], H,E,[E|R]):-
    !,
    substituie(L,H,E,R).

substituie([H1|L],H,E,[H1|R]):-
    substituie(L,H,E,R).
