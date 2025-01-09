

;5. Definiti o functie care testeaza apartenenta unui nod intr-un arbore n-ar
;reprezentat sub forma (radacina lista_noduri_subarb1... lista_noduri__subarbn)
;Ex: arborelele este (a (b (c)) (d) (e (f))) si nodul este 'b => adevarat



(defun SAU2(l)
    (cond
        ( (null l) NIL )
        ( T (or (car l) (SAU2 (cdr l))) )
    )
)

(defun apare(l e)
    (cond
        ( (null l) NIL )
        ( (eq (car l) e) T )
        ( T (SAU2 (mapcar (lambda (arb) (apare arb e)) (cdr l))) )
    )
)

(print (apare '(a (b (c)) (d) (e (f))) 'b))