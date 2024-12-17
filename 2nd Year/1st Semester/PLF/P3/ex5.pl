%multimi(L:Lista, K:Integer, R:Lista)
%model de flux(i,i,o)
%L: Lista din care se extrag elemente din submultimi
%K: Numarul de elemente care trebuie extrase din Lista
%R: Lista rezultata care va avea K elemente din L


multimi(_,0,[]):-!.

multimi([H|T],K,[H|R]):-
    K1 is K-1,
    multimi(T,K1,R).

multimi([_|T],K,R):-
    multimi(T,K,R).


%setMultimi(L:Lista, K:Integer, R:Lista)
%model de flux (i,i,o)
%L:Lista din care extragem submultimile
%K: Lungimea submultimilor din lista L
%R: Lista rezultata cu submultimile de cate K elemente din L

setMultimi([],_,[]):-!.

setMultimi(_,0,[]):-!.

setMultimi(L,K,R):-
    findall(RS, multimi(L,K,RS), R).

teste5:-
    setMultimi([2,3,4],2,[[2,3],[2,4],[3,4]]),
    setMultimi([2,3],1,[[2],[3]]),
    setMultimi([],4,[]).
