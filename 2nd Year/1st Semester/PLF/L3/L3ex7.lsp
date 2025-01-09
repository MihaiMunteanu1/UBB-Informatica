

;7. Sa se scrie o functie care calculeaza suma numerelor pare minus suma
;numerelor impare la toate nivelurile unei liste.


(defun sum(l)
    (cond
        ((and (numberp l) (= (mod l 2) 0 ))l )
        ((numberp l) (- l))
        ((atom l) 0)
        (T (apply '+ (mapcar #' sum l)))
    )
)

(print (sum '(1 2(3(4)5))))