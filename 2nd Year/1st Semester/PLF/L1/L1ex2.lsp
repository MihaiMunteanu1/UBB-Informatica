;a) Definiti o functie care selecteaza al n-lea element al unei liste, sau NIL, daca nu exista.

(defun select(l n)
    (cond
        ((null l) nil)
        ((= n 0) (car l))
        (T (select (cdr l) (- n 1) ))
    )
)

;(print (select '(1 2(3 4(5))6) 2))

;b) Sa se construiasca o functie care verifica daca un atom e membru al unei liste nu neaparat liniara.

(defun exista(l a)
    (cond
        ((null l) nil)
        ((equal (car l) a) T)
        ((listp (car l)) (or (exista (car l) a) (exista (cdr l) a)))
        (T (exista (cdr l) a))
    )
)

;(print (exista '(1 (2) 3) 2))

;c) Sa se construiasca lista tuturor sublistelor unei liste. Prin sublista se intelege fie lista ;insasi, fie un element de pe orice nivel, care este lista. Exemplu: (1 2 (3 (4 5) (6 7)) 8 (9 10)) =>
;( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) ).

(defun sublista (l)
    (cond 
        ((null l) ())
        ((listp (car l)) ( append (list (car l)) (sublista (car l)) (sublista (cdr l)) ) )
        (T (sublista(cdr l)))
    )
)

;(print (sublistewrapper '(1 2 (3 (4 5) (6 7)) 8 (9 10))))

;d) Sa se scrie o functie care transforma o lista liniara intr-o multime.


(defun nraparitii(l e)
    (cond
        ( (null l) 0 )
        ( (= e (car l)) (+ 1 (nraparitii (cdr l) e)) )
        ( T (nraparitii (cdr l) e) )
    )
)

(defun elimina(l)
    (cond
        ( (null l) () )
        ( (= (nraparitii (cdr l) (car l)) 0) (cons (car l) (elimina (cdr l))) )
        ( T (elimina (cdr l)))        
    )
)

(print (elimina '(1 2 3 1 4)))


