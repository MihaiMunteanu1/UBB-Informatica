

;1. Sa se construiasca o functie care intoarce adancimea unei liste.


; EX:  (1 2 3 4 5) -> 0?
;      (1 (2) (3 (4))) -> 2?



(defun adancime(l)
    (cond
        ((null (cdr l)) 0)
        (T (+ 1 (apply #'max (mapcar #' adancime (cdr l)) )  ))
    )
)

(print (adancime '(1 (2) (3 (4)))))