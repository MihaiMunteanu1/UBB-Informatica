%daca lista e goala rez ii tot o lista goala
subs([], _, _, []):-!.

%daca primul elem X=Y atc il punem pe Y in lista Rez
subs([X | T], X, Y, [Y | Rez]) :-
        !, % se opreste cautarea altor reguli
        subs(T, X, Y, Rez).  % se continua recursiv cu restul listei

subs([H | T], X, Y, [H | Rez]) :- %daca primul elem nu e egal cu cel cautat
        subs(T, X, Y, Rez).  %continuam recursiv cu restul listei


teste12a:-
    subs([], 5, 5, []),
    subs([1, 2, 3], 5, 6, [1, 2, 3]),
    subs([1, 2, 3, 4], 2, 5, [1, 5, 3, 4]),
    subs([1, 2, 1, 4], 1, 5, [5, 2, 5, 4]),
    subs([1,1,1],1,2,[2,2,2]).
