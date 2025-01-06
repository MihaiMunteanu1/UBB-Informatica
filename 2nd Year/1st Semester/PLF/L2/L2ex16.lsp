

;16. Sa se decida daca un arbore de tipul (2) este echilibrat (diferenta dintre
;adancimile celor 2 subarbori nu este mai mare decat 1).

(defun nivell (l nv)
    (cond
        ((null l) nv)
        (T (max (nivell (cadr l) (+ nv 1)) (nivell (caddr l) (+ nv 1))) )
    )
)

(defun ech(l)
    (setf niv_st (nivell (cadr l) 0))
    (setf niv_dr (nivell (caddr l) 0))
    (print niv_st)
    (print niv_dr)
    (cond
        ((null l) NIL)
        ((> niv_st (+ niv_dr 1)) NIL)
        ((> niv_dr (+ niv_st 1)) NIL)
        (T T)
    )
)

(print (ech '(A (B(C (E)(F))(D)) )))
;    A
;   B
; C   D
;E F