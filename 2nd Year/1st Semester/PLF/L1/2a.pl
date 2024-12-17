%CMMMC al numerelor unei liste


cmmdc(X, Y, R):-
    X<0,
    !,
    X1 is -X,
    cmmdc(X1, Y, R).

cmmdc(X, Y, R):-
    Y<0,
    !,
    Y1 is -Y,
    cmmdc(X, Y1, R).

cmmdc(X, 0, X):-!.

cmmdc(X, Y, R):-
    Y>X,
    cmmdc(Y, X, R).

cmmdc(X, Y, R):-
    X >= Y,
    T is X mod Y,
    cmmdc(Y, T, R).

cmmmcLista([], 0).

cmmmcLista([E], E):-!.

cmmmcLista([A, B], R):-
        P is A*B,
        cmmdc(A, B, D),
        R is P/D,
        !.

cmmmcLista([H | T], R):-
        cmmmcLista(T, R1),
        P is H*R1,
        cmmdc(H, R1, D),
        R is P/D.
%!  %%%%%%%%%%%%%%%%%%
produs([], 0).

produs([E], E):-!.

produs([H|T], P):-
        produs(T, P1),
        P is H*P1.

%!  %%%%%%%%%%%%%%%%%%%%%%
cmmdcLista([], 1).

cmmdcLista([_], 1):-
        !.

cmmdcLista([A, B], R):-
        cmmdc(A, B, R),
        !.

cmmdcLista([H|T], R):-
        cmmdcLista(T, R1),
        cmmdc(H, R1, R).
