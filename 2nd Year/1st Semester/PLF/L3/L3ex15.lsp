

; 15. Sa se construiasca o functie care intoarce numarul atomilor dintr-o
; lista, de la orice nivel.

(defun nr_atomi(l)
    (cond 
        ((null l) 0)
        ((atom l) 1)
        (T (apply #'+ (mapcar #' nr_atomi l)))
    )
)

(print (nr_atomi '(1 2 32)))
