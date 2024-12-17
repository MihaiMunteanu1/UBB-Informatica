%adauga o val dupa 1,2,4,8.. element.

adauga_val_aux([],_,_,_,[]):-!.

adauga_val_aux([H|T],V,IC,IA,[H,V|R]):-
    IC =:= IA,
    !,
    IC1 is IC + 1,
    IA1 is IA*2,
    adauga_val_aux(T,V,IC1,IA1,R).

adauga_val_aux([H|T],V,IC,IA,[H|R]):-
    IC1 is IC+1,
    adauga_val_aux(T,V,IC1,IA,R).

adauga_val(L,V,R):-adauga_val_aux(L,V,1,1,R).
