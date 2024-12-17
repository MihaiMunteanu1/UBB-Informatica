:-consult('7a.pl').

%inlocuire_aux(L:lista,I:int,R:lista)
%model de fluz(i,i,o)
%L: lista pe care o parcurgem si inlocuim sublistele cu rezultatul
%inmultirii sublistei cu nr de ordine
%I: nr de ordine
%R: lista rezultata dupa inmultirea fiecarei subliste din L cu
%numarul de ordine respectiv

%cand lista e goala returnam lista goala
inlocuire_aux([],_,[]).

%verificam daca H e lista, atunci in H1 salvam
%sublista inmultita cu nr de ordine I, pe care il incrementam dupa
inlocuire_aux([H|L],I,[H1|R]):-
    is_list(H),
    produs(H,H1,I),
    I1 is I+1,
    inlocuire_aux(L,I1,R).

%daca elem curent nu e lista, il adaugam in lista rezultat
inlocuire_aux([H|L],I,[H|R]):-
    \+ is_list(H),
    inlocuire_aux(L,I,R).

inlocuire(L,R):-inlocuire_aux(L,1,R),!.

teste7b:-
    inlocuire([1,2,3],[1,2,3]),
    inlocuire([1,[5,7],3,[8,9]],[1,[5,7],3,[1,7,8]]),
    inlocuire([],[]),
    inlocuire([1,[2,3],[4,1,4],3,6,[7,5,1,3,9],5,[1,1,1],7],
             [1,[2,3],[8,2,8],3,6,[2,2,5,4,1,7],5,[4,4,4],7]),
    inlocuire([[1],[9]],[[1],[1,8]]).
