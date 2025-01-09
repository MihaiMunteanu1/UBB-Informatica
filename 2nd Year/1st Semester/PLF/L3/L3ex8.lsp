

;8. Sa se construiasca o functie care intoarce maximul atomilor numerici
;dintr-o lista, de la orice nivel.


(defun mx(l)
    (cond
        ((numberp l) l)
        ((atom l) 0)
        ;(T (apply 'max (mapcar #' mx l)))
        (T (apply 'max (mapcar (lambda (l) (mx l)) l)))
    )
)

(print (mx '(1 2(3(4 9)8)7)))