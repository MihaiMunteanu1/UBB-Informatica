

; 16. Definiti o functie care inverseaza o lista impreuna cu toate sublistele
; sale de pe orice nivel.

(defun invers(l)
    (cond
        ((null l) NIL)
        ((atom l) l)
        (T (append (invers (cdr l)) (list (car l))))
    )
)

(defun invs(l)
    (cond
        ((atom l) l)
        (T (mapcar #' invs(invers l)))
    )
)

(print (invs '(a b(c (d e g) h) i j) ))