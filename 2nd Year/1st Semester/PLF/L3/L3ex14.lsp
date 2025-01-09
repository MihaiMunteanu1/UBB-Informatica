

; 14. Definiti o functie care da adancimea unui arbore n-ar reprezentat sub forma
; (radacina lista_noduri_subarb1...lista_noduri_subarbn)
; Ex: adancimea arborelui este (a (b (c)) (d) (e (f))) este 3


(defun adanc(l)
    (cond
        ((null l) 0)
        ((atom l) 1)
        ((null (cdr l)) 1)
        (T (+ 1 (apply 'max (mapcar #' adanc (cdr l)))) )
    )
)


(print (adanc '(a (b (c)) (d) (e (f))) ))