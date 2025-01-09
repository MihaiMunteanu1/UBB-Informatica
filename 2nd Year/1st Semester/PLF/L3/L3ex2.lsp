

;2. Definiti o functie care obtine dintr-o lista data lista tuturor atomilor
;care apar, pe orice nivel, dar in aceeasi ordine. De exemplu
;(((A B) C) (D E)) --> (A B C D E)

(defun apar(l)
    (cond
        ((null l) NIL)
        ((atom l) (list l))
        (T (mapcan #' apar l))
    )
)

(print (apar '(((A B) C) (D E))))