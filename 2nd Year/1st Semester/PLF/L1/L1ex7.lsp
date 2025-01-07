;7.
;a) Sa se scrie o functie care testeaza daca o lista este liniara.

(defun tst(l)
    (cond
        ((null l) NIL)
        ((listp (car l)) NIL)
        ((null (cdr l)) T)
        (T (tst (cdr l)))
    )
)

;(print (tst '(1 2 (3))))

;b) Definiti o functie care substituie prima aparitie a unui element intr-o lista data.

(defun substi(l x ok el)
    (cond
        ((null l) NIL)
        ((listp (car l)) (cons (substi (car l) x ok el) (substi (cdr l) x ok el)))
        ((and (= (car l) x) (= ok 0)) (append (list el) (substi (cdr l) x 1 el) ))
        (T ( append (list(car l)) (substi (cdr l) x ok el)))
    )
)

(defun sbs(l x el)
    (cond
        ((null l) NIL)
        (T (substi l x 0 el))
    )
)

;(print (sbs '(1 (4 5(5 5)5)) 5 9))


;c) Sa se inlocuiasca fiecare sublista a unei liste cu ultimul ei element. Prin sublista se intelege ;element de pe primul nivel, care este lista. Exemplu: (a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c ;(f)) ==> (a c f)
;(a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)


(defun ultim_el(l el)
    (cond
        ((null l) el)
        ((and (listp (car l)) (null (cdr l)) ) (ultim_el (car l) el ))
        ((listp (car l)) (ultim_el (cdr l) el ))
        (T (ultim_el (cdr l) (car l) ))
    )
)

(defun inlocuire(l)
    (cond
        ((null l) NIL)
        ((atom (car l)) (append (list(car l)) (inlocuire (cdr l))))
        (T (cons (ultim_el (car l) NIL) (inlocuire (cdr l))))
    )
)

;(print (inlocuire '(a (b c) (d ((e) f)))))


;d) Definiti o functie care interclaseaza fara pastrarea dublurilor doua liste liniare sortate.

;(1 2 3) (3 5 6) => (1 2 3 5 6)

(defun inlcire (l1 l2)
    (cond
        ((and (null l1) (null l2)) NIL)
        ((null l1) l2)
        ((null l2) l1)
        ((= (car l1) (car l2)) (cons (car l1) (inlcire (cdr l1) (cdr l2))))
        ((< (car l1) (car l2)) (cons (car l1) (inlcire (cdr l1) l2)))
        (T (cons (car l2) (inlcire l1 (cdr l2)) ))
    )
)

(print (inlcire '(1 2) '(1 2 3 5 6 7 8)))



