

;Sa se converteasca un arbore de tipul (2) la un arbore de tipul (1).
;(A (B) (C (D) (E))) => (A 2 B 0 C 2 D 0 E 0)

(defun convert(l)
    (cond
        ((null l) NIL)
        ((null (cadr l) ) (append (list(car l) 0) ))
        ((null (caddr l) ) (append list(car l) 1 (convert (cadr l) )  ) )
        (T ( append (list (car l) 2) (convert (cadr l)) (convert (caddr l)) )  )
    )
)

(print (convert '(A (B) (C (D) (E)))))

;convert(l1..n) = { null, n = 0
;                 { l1 0, daca cdr l = NIL
;                 { l1 1, daca cdr l != NIL si cddr l = NIL
;                 { l1 2, daca cdr l != NIL si cddr l != NIL