;a) Sa se insereze intr-o lista liniara un atom a dat dupa al 
;2-lea, al 4-lea, al 6-lea,....element.

(defun inserare(l a i)
    (cond
        ((null l) NIL)
        ((=(mod i 2) 0) (cons (car l) (cons a (inserare(cdr l) a (+ i 1)) ) ) )
        (T (cons (car l) (inserare(cdr l) a (+ i 1)) )) 
    )
)

;(print (inserare '(1 2 3 4 5) 9 0))

;b) Definiti o functie care obtine dintr-o lista data lista tuturor atomilor 
;care apar, pe orice nivel, dar in ordine inversa. De exemplu: (((A B) C) (D E)) --> (E D C B A)

(defun invers(l)
    (cond
        ((null l) NIL)
        ((listp (car l)) (append  (invers (cdr l)) (invers(car l)) ) )
        (T (append  (invers (cdr l)) (list(car l)) ))
    )
)

;(print (invers '(1(2 3)((4)5))))

;c) Definiti o functie care intoarce cel mai 
;mare divizor comun al numerelor dintr-o lista neliniara.

(defun cmmdc(x y)
    (cond 
        ((= y 0) x)
        (T (cmmdc y (mod x y)))
    )
)

(defun div(l)
    (cond
        ((null l) 0)
        ((numberp (car l)) (cmmdc (car l) (div (cdr l))) )
        ( T (cmmdc (div (car l)) (div (cdr l))) )
  
    )
)

;(print (div '(10 (2 32)((4)52))))


;d) Sa se scrie o functie care determina 
;numarul de aparitii ale unui atom dat intr-o lista neliniara.


(defun aparitii (l e)
    (cond
        ((null l) 0) 
        ((atom l) (if (eq l e) 1 0)) 
        (t (apply #'+ (mapcar (lambda (x) (aparitii x e)) l)))
    )
) 


(print (aparitii '(1 (2 1) 3 (1 4)) 1))













