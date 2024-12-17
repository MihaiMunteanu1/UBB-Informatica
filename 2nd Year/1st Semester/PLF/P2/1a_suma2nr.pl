inverseaza_aux([],Cp,Cp).

inverseaza_aux([H|L],Cp,R):-
    inverseaza_aux(L,[H|Cp],R).

inverseaza(L,R):-inverseaza_aux(L,[],R).

suma([],[],[],0):-!.

suma([],[],[C],C).

suma([H|L],[],[H|R],0):-
    suma(L,[],R,0).

suma([],[H|L],[H|R],0):-
    suma([],L,R,0).

suma([H|L1], [H1|L2],[A|R], C):-
    Sum is H+H1+C,
    A is Sum mod 10,
    C1 is Sum div 10,
    suma(L1,L2,R,C1).


ss(L1,L2,R):-
    inverseaza(L1,LL1),
    inverseaza(L2,LL2),
    suma(LL1,LL2,R1,0),
    inverseaza(R1,R).
