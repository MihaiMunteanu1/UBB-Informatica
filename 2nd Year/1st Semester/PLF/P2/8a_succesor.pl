%SUCCESORUL UNUI NR: [1,9] => [2,0]

inverseaza_aux([],Cp,Cp).

inverseaza_aux([H|L],Cp,R):-
    inverseaza_aux(L,[H|Cp],R).

inverseaza(L,R):-inverseaza_aux(L,[],R).

succ_aux([],0,[]):-!.

succ_aux([],1,[1]).

succ_aux([H|L],C,[Nr|R]):-
    Sum is H+C,
    Nr is Sum mod 10,
    C1 is Sum div 10,
    succ_aux(L,C1,R).

succe(L,R):-inverseaza(L,L1),
    succ_aux(L1,1,R1),
    inverseaza(R1,R).
