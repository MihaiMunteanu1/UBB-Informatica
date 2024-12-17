%inverseaza_aux(L:lista,Cp:lista,R:lista)
%model de flux(i,i,o)
%L -> lista pe care dorim sa o inversam
%Cp -> lista copie unde adaugam pe rand elem din L
%R -> lista inversata rezultata

%cand lista e goala si am terminat de inversat
%rezultatul va fi salvat in R
inverseaza_aux([],Cp,Cp).

%adaugam primul el din L in Lista T
inverseaza_aux([H|L],Cp,R):-
    inverseaza_aux(L,[H|Cp],R).

inverseaza(L,R):-inverseaza_aux(L,[],R).

%produs_aux(L:lista,C:int,P:int,R:lista)
%model de flux(i,i,i,o)
%L-> lista pe care o inmultim
%C-> cifra de transport
%P-> nr cu care inmultim fiecare cifra
%R-> lista inmultita cu cifra P

%daca ultima cifra de transport ii 0 si lista e goala
%returnam lista goala si nu mai cautam
produs_aux([],0,_,[]):-!.

%daca ultima cifra de transport ii !=0 o adaugam
%in lista finala
produs_aux([],C,_,[C]).

produs_aux([H|L],C,P,[Rest|R]):-
    Prod is H*P + C,
    C1 is Prod div 10,
    Rest is Prod mod 10,
    produs_aux(L,C1,P,R).


produs(L,R,P):-inverseaza(L,R1),
    produs_aux(R1,0,P,R2),
    inverseaza(R2,R).

teste7a:-
    produs([1,2,3],[2,4,6],2),
    produs([4,5,6],[1,3,6,8],3),
    produs([7,8,9],[3,1,5,6],4),
    produs([4],[1,2],3),
    produs([],[],9).
