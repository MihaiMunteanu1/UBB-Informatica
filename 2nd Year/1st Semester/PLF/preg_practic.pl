%ex1 2019
%2.
invers_list([],Aux,Aux).

invers_list([H|T],Aux,R):-
    is_list(H),
    !,
    invers_list(H,[],L_small),
    invers_list(T,[L_small|Aux],R).

invers_list([H|T], AUX, R):- invers_list(T, [H|AUX] ,R).


main_invers_list(L, R):- invers_list(L, [], R).

%3.

subsets([H|_],1,[H]).

subsets([_|T],N,R):-
    subsets(T,N,R).

subsets([H|T],N,R):-
    N1 is N-1,
    subsets(T,N1,R1),
    R = [H|R1].


%!  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%ex1 2020

%.2
% f([],0).
% f([H|T],S):-f(T,S1),
%     aux(S1,S,H).
% aux(S1,S,H):-S1<H,
%      !,
%      S is H.
% aux(S1,S,_):-S is S1.
%   -> sau aux(S1,S1,_).

%.4
f([],[]).

f([H|T],[H|S]):-f(T,S).

f([H|T],S):-H mod 2 =:= 0, f(T,S).

%  => [1,2,3], [1,3]

%II
% Permutari cu diferenta

permut(L,P):-
    permutari(L,P),
    verif_dif(P).

permutari([],[]).

permutari([E|T],P):-
    permutari(T,L),
    insereaza(E,L,P). %(i,i,O).


insereaza(E,L,[E|L]).

insereaza(E,[H|T],[H|Rez]):-
    insereaza(E,T,Rez).


verif_dif([]).

verif_dif([_]).

verif_dif([X,Y|T]):-
    abs(X-Y) =< 3,
    verif_dif([Y|T]).

%.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%ex2 2019

exista([H|_], H):- !.
exista([_|T], E):- exista(T, E).

set([], []).
set([H|T], R):- set(T, R),
                exista(R, H), !.

set([H|T], R):- set(T, R1),
                R = [H|R1].

%aranjamente luate cate k cu produs p

alege([H|_], H).
alege([_|T], X):- alege(T, X).


aranj_aux(_,0,P,Raux,P,Raux).

aranj_aux(L,N,P,Raux,P1,R):-
    N>0,
    P1 < P,
    N1 is N-1,
    alege(L,X),
    P2 is P1*X,
    Raux1 = [X|Raux],
    aranj_aux(L,N1,P,Raux1,P2,R).

aranj(L,N,P,R):-aranj_aux(L,N,P,[],1,R).


%.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%ex2 2020

%.4
%f2([],0).

%f2([H|T],S):-
%    f(T,S1),
%    S1 is S-H.
%
%    eroare pt ca S nu e evaluata si nu se poate calcula S-H
%    S nu a fost legata inca


%.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%ex3 2019

%2.
sterge_poz_aux([],_,_,[]):-!.

sterge_poz_aux([_|L],P,Pz,R):-
    P =:= Pz,
    !,
    sterge_poz_aux(L,P+1,2*Pz,R).

sterge_poz_aux([H|L],P,Pz,[H|R]):-
    P1 is P+1,
    sterge_poz_aux(L,P1,Pz,R).

sterge_poz(L,Pz,R):-sterge_poz_aux(L,1,Pz,R).

%3. subliste de lungime para a unei liste

lungime([],0):-!.

lungime([_|T],L):-
    lungime(T,L1),
    L is L1+1.


%generarea tuturor sublistelor ->
sublist([],[]):-!.

sublist([_|T],Sublista):-
    sublist(T,Sublista).

sublist([H|T],[H|Sublista]):-
    sublist(T,Sublista).


subliste_lung_par(L,S):-
   findall(SubL,(sublist(L,SubL),lungime(SubL,Lungime),0 is Lungime mod 2),
           S).
   % sau ->
   % sublist(L,S),
   % lungime(S,Lungime),
   % 0 is Lungime mod 2.

%.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% ex3 2020
%subliste de dim >= n si suma elementelor mod 3 = 0

lg([],0):-!.

lg([_|T],L):-
    lg(T,L1),
    L is L1+1.

sum_el([],0):-!.

sum_el([H|L],S):-
    sum_el(L,S1),
    S is S1 + H.

subl([],[]):-!.

subl([_|T],R):-subl(T,R).

subl([H|T],[H|R]):-subl(T,R).


subset_sum_lg(L,N,Rez):-
    findall(Subs,(subl(L,Subs),lg(Subs,Lung),Lung >= N,sum_el(Subs,Suma),
                 0 is Suma mod 3),Rez).

%.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ex4 2019

%2. adauga un el. dupa al 3,5,9,17 el
% nu are sens prob asta ca nu vad tot in poza

adauga_el_aux([],_,_,_,[]):-!.

adauga_el_aux([H|L],E,Pz,PA,[H,E|R]):-
    Pz =:= PA,
    !,
    adauga_el_aux(L,E,Pz+2,2*PA-1+1,R).


adauga_el_aux([H|L],E,Pz,PA,[H|R]):-
    Pz1 is Pz+1,
    adauga_el_aux(L,E,Pz1,PA,R).

adauga_el(L,E,R):-adauga_el_aux(L,E,1,3,R).



%perm el n,n+1,2*n-1, unde dif abs <= 2

generare_lista(N,[],Mx):-
    N > Mx,
    !.

generare_lista(N,[N|R],Mx):-
    N1 is N+1,
    N =< Mx,
    generare_lista(N1,R,Mx).

generare_l(N,R):-
    Mx is 2*N-1,
    generare_lista(N,R,Mx).

insrz([],_,[]).

insrz(E,L,[E|L]).

insrz(E,[H|T],[H|Rez]):-
    insrz(E,T,Rez).

verif_dif2([]).

verif_dif2([_]).

verif_dif2([X,Y|T]):-
    abs(X-Y) =< 2,
    verif_dif2([Y|T]).

permt([],[]).

permt([E|T],P):-
    permt(T,L),
    insrz(E,L,P).

perm_main(N):-
    generare_l(N,L),
    permt(L,P),
    verif_dif2(P),
    write(P),nl.

%.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



p(1).
p(2).
q(1).
q(2).
r(1).
r(2).

s :- p(X), q(Y), r(Z),!,
     write(X), write(' '), write(Y), write(' '), write(Z), nl.
