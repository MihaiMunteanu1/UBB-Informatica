;14. Sa se construiasca lista nodurilor unui arbore de tipul (2) parcurs in
;postordine.

(defun postordine(l)
    (cond
        ((null l) NIL)
        (T (append (postordine (cadr l)) (postordine(caddr l)) (list(car l))) )
    )
)

(print (postordine '(1 (2 (4 () (7) )) (3 (5) (6)) ) ))