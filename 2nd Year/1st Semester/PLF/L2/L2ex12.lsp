;12. Sa se construiasca lista nodurilor unui arbore de tipul (2) parcurs in
;preordine.


(defun preordine(l)
    (cond
        ((null l) NIL)
        (T (append (list(car l)) (preordine (cadr l)) (preordine(caddr l))) )
    )
)

(print (preordine '(1 (2 (4 () (7) )) (3 (5) (6)) ) ))