

;10. Se da un arbore de tipul (2). Sa se precizeze nivelul pe care apare un nod
;x in arbore. Nivelul radacii se considera a fi 0.

;(A (B) (C (D) (E)))

(defun nivel (l nv nod)
    (cond
        ((null l) -1)
        ((equal (car l) nod) nv)
        (T (max (nivel (cadr l) (+ nv 1) nod) (nivel (caddr l) (+ nv 1) nod)) )
    )
)

; ori '-1' si 'max'  SAU  'NIL' si 'or'

(defun niv(l nod)
    (cond
        ((null l) NIL)
        (T (nivel l 0 nod ) )
    )
)

(print (niv '(A (B) (C (D (G) (H) ) (E))) 'G ))