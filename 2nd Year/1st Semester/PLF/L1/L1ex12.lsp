


;a) Definiti o functie care intoarce produsul scalar a doi vectori.


;b) Sa se construiasca o functie care intoarce maximul atomilor numerici dintr-o lista, de la orice ;nivel.

(defun mx(l mm)
    (cond
        ((null l) mm)
        ((listp (car l)) (max (mx (car l) mm) (mx (cdr l) mm) ))
        ((> (car l) mm) (mx (cdr l) (car l)))
        (T (mx (cdr l) mm))
    )
)

(defun mx2(l)
    (cond   
        ((null l) NIL)
        (T (mx l 0))
    )
)

(print (mx2 '(4 5(5 6(8 9))3 2)))


;c) Sa se scrie o functie care intoarce lista permutarilor unei liste date.


(defun permutari (L)
    (cond
        ( (null (cdr L)) (list L) )
        ( T 
            (mapcan (lambda (e) (mapcar (lambda (p) (cons e p)) (permutari (remove e L)))) L)
        )
    )
)

;Implementare
; Functie auxiliara pentru a insera un element pe o anumita pozitie:
; ins(E: Element, K: Intreg, L: ListaElement)
(defun ins(E K L)
    (cond
        ((= K 1) (cons E L))
        (T (cons (car L) (ins E (- K 1) (cdr L))))
    )
)

; Functie auxiliara care sa returneze multimea formata din listele obtinute prin inserarea unui element E pe pozitiile 1, 2, ..., lungimea listei + 1 intr-o lista
; insert(E: Element, N: Intreg, L: ListaElement)
(defun insert(E N L)
    (cond
        ((= N 0) nil)
        (T (cons (ins E N L) (insert E (- N 1) L)))
    )
)

(defun size(L)
    (cond
        ((null L) 0)
        (T (+ 1 (size (cdr L))))
    )
)

; ListaDeListaElement: Lista formata din ListaElement
; insert_in_each_list(E: Element, L: ListaDeListaElement)
(defun insert_in_each_list (E L)
    (cond
        ((null L) nil)
        (T (append (insert E (+ (size (car L)) 1) (car L)) (insert_in_each_list E (cdr L))))
    )
)

(defun permutari(L)
    (cond
        ((null L) (list nil))
        (T (insert_in_each_list (car L) (permutari (cdr L))))
    )
)


;d) Sa se scrie o functie care intoarce T daca o lista are numar par de elemente pe primul nivel si NIL ;in caz contrar, fara sa se numere elementele listei.

(defun even (lst)
    (cond
        ( (null lst) T ) 
        ( (null (cdr lst)) NIL )
        ( T (even (cddr lst)) )
    )
)






