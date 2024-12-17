%inversare(L:lista,R:lista,C:lista)
%L: lista pe care dorim sa o inversam
%R: lista unde o sa obtinem lista inversata
%C: lista colectare pentru lista inversata
%Model de flux(i,i,o)

inversare([],C,C).

inversare([H|L],R,C):-
    inversare(L,[H|R],C).

%eliminare_aux(L:lista,I:intreg,K:intreg,R:lista)
% L: lista din care dorim sa eliminam elementele aflate pe poz
% 1,3,7,15,31 ...
% I: indicele curent in lista
% K: indicele de pe ce pozitie vom elimina elemente
% R: lista rezultata cu elementele de pe pozitiile 1,3,7.. eliminate
% Model de flux(i,i,i,o)

eliminare_aux([],_,_,[]). %daca lista e goala returnam lista goala

%daca i=k atunci nu adaugam element in rezultat si k devine 2*k+1
eliminare_aux([_|L],I,K,R):-
    I =:= K,
    I1 is I+1,
    K1 is K*2 +1,
    !,
    eliminare_aux(L,I1,K1,R).

%daca i!=k atunci adaugam elementul curent in lista rezultat
%si incrementam indexul curent i
eliminare_aux([H|L],I,K,[H|R]):-
    I =\= K,
    I1 is I+1,
    eliminare_aux(L,I1,K,R).

eliminare(L,R):-
    eliminare_aux(L,1,1,R1),
    inversare(R1,[],R).
