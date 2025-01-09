

;11. Sa se scrie o functie care sterge toate aparitiile unui atom de la
; toate nivelurile unei liste.

(defun strg (l e)
    (cond
        ((equal l e) nil )
        ((atom l) l)
        (T (remove nil (mapcar (lambda (l) (strg l e)) l)))
    )
)

(print (strg '(1 3(1 4)(5(1)3) 2) 1 ))