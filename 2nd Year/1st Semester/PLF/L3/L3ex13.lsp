

; 13. Definiti o functie care substituie un element prin altul la toate
; nivelurile unei liste date.

(defun sbs(l e1 e2)
    (cond
        ((equal l e1) e2)
        ((atom l) l)
        (T (mapcar (lambda (l) (sbs l e1 e2)) l))
    )
)

(print (sbs '(1 2(3 4(1))5) 1 9 ))