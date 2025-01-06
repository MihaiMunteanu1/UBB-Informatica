

;8. Sa se construiasca lista nodurilor unui arbore de tipul (2) parcurs in
;inordine.



(defun inordine(l)
    (cond
        ((null l) NIL)
        (T (append (inordine(cadr l)) (list(car l)) (inordine(caddr l)) ) )
    )
)

(print (inordine '(a (b () (f)) (d (e)))))

