%apelam predicatul auxiliar cu un contor care incepe de la 0
sublista(L,M,N,Rez):-sublista_aux(L,0,M,N,Rez).

%daca lista e vida atunci lista rezultata va fi vida
sublista_aux([],_,_,_,[]):-!.

%daca am ajuns la poz N rezultatul va fi []
sublista_aux(_,N,_,N,[]):-!.

%daca contorul c este incrementat si egal cu m incepem sa adaugam
%elemente in lista Rez, apoi incrementam pe M si continuam recursiv
%pentru restul listei
sublista_aux([H|T],C,M,N,[H|Rez]):-
    C1 is C+1,
    C1 >= M,
    C1 =< N,
    !,
    M1 is M+1,
    sublista_aux(T,C1,M1,N,Rez).

%daca nu am ajuns inca la poz M,incrementam contorul si continuam
%fara sa adaugam elemente
sublista_aux([_|T],C,M,N,Rez):-
    C1 is C+1,
    sublista_aux(T,C1,M,N,Rez).

teste12b:-
    sublista([1,2,3,4,5],2,4,[2,3,4]),
    sublista([],1,2,[]),
    sublista([1,2,3],0,0,[]),
    sublista([1,2,3],0,1,[]),
    sublista([1,2,3],3,3,[3]).
