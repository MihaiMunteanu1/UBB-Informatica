
;11
;a) Sa se determine cel mai mic multiplu comun al valorilor numerice dintr-o lista neliniara.

(defun cmmdc (x y)
    (cond
        ((= y 0) x)
        (T (cmmdc y (mod x y))))
)

(defun cmmmc-doua (a b)
    (/ (* a b) (cmmdc a b))) ; Formula CMMMC: (a * b) / CMMDC(a, b)

(defun cmmmc-lista (l)
    (cond
        ((null l) 1)
        ((numberp (car l)) (cmmmc-doua (car l) (cmmmc-lista (cdr l)))) 
        (T (cmmmc-doua (cmmmc-lista (car l)) (cmmmc-lista (cdr l))))
    ) 
)

;(print (cmmmc-lista '(1 2 (3 4 (7) 5))))


;b) Sa se scrie o functie care sa testeze daca o lista liniara formata din numere intregi are aspect de ;"munte"(o secvență se spune ca are aspect de "munte" daca elementele cresc pana la un moment dat, apoi ;descresc. De ex. 10 18 29 17 11 10).


(defun munte(l ok)
    (cond
        ((null l) NIL)
        ((and (null l) (= ok 1)) T)
        ((and (null (cdr l)) (= ok 1)) T)
        ((and (null (cdr l)) (= ok 0)) NIL)
        ((and (> (cadr l) (car l)) (= ok 0) ) (munte (cdr l) 0))
        ((and (< (cadr l) (car l) ) (= ok 0) ) (munte (cdr l) 1))
        ((and (< (cadr l) (car l)) (= ok 1) ) (munte (cdr l) 1))
        (T NIL)
    )
)

(defun munte_bun(l)
    (cond
        ((null l) NIL)
        (T (munte l 0))
    )
)

;(print (munte_bun '(10 18 29 17 11 15 10)))

;c) Sa se elimine toate aparitiile elementului numeric maxim dintr-o lista neliniara.

;facut




;d) Sa se construiasca o functie care intoarce produsul atomilor numerici pari dintr-o lista, de la orice nivel.


(defun prod(l)
    (cond
        ((null l) 1)
        ((listp (car l)) (* (prod (car l)) (prod (cdr l) )) )
        ((and (numberp (car l)) (= (mod (car l) 2) 0)) (* (car l) (prod (cdr l))) )
        (T (prod(cdr l)) )
    )
)

(print (prod '(1 2(5(6))4)))







