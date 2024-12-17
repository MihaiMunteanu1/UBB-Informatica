%numar([1, 2, 1, 2, 1, 3, 1], X) va produce
%X = [[1, 4], [2, 2], [3, 1]].

nr_apar_cu_elim([],_,0,[]).

nr_apar_cu_elim([E|T],E,Nr,R):-
    !,
    nr_apar_cu_elim(T,E,Nr1,R),
    Nr is Nr1 + 1.

nr_apar_cu_elim([H|T],E,Nr,[H|R]):-
    H \== E,
    nr_apar_cu_elim(T,E,Nr,R).

elim_lista([],[]).

elim_lista([H|L],[[H,Nr]|R]):-
    nr_apar_cu_elim([H|L],H,Nr,R1),
    elim_lista(R1,R).
