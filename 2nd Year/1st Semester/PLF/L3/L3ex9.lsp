

;9. Definiti o functie care substituie un element E prin elementele
;unei liste L1 la toate nivelurile unei liste date L.

(defun subs(l e l1)
    (cond
        ((equal e l) l1)
        ((atom l) l)
        (T (mapcar (lambda (l) (subs l e l1)) l))
    )
)

(print (subs '(1 2 ( 3 2 ) 2) 2 '(9 9) ))