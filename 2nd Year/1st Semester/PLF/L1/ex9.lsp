;a) Sa se scrie o functie care intoarce diferenta a doua multimi

; contine(L:lista, e:element)
; Model de flux: (i,i)
; L:lista in care vom cauta daca un element exista
; e: elementul pe care il cautam in lista

; contine(l1..n,e)={ False, n=0
;                  { True, e=l1 si n>0
;                  { contine(l2..n, e), altfel                   

(defun contine(l e)
    (cond
        ( (null l)  NIL )
        ( (equal (car l) e) T )
        ( T (contine (cdr l) e) )
    )
)

;diferenta(l1..n, L)= { [], daca n=0
;                     { l1 (+) diferenta(l2..n, L), l1 nu apartine L si n>0
;                     { diferenta(l2..n, L), altfel


(defun diferenta(l p)
    (cond
        ( (null l)  NIL )
        ( (not (contine p (car l))) (cons (car l) (diferenta (cdr l) p)) )
        ( T  (diferenta (cdr l) p) )
    )
)

(print (diferenta '(1 2 3 4 5) '(5 7 8 9)))
(print (diferenta '(1 2 3 (4 5 6) ) '((4 5) 6 7)) )



;b) Definiti o functie care inverseaza o lista impreuna cu toate sublistele sale

;inverseaza(l1..n) = { [], n=0
;                    { inverseaza(l2..n) append inverseaza(l1), l1 lista
;                    { inverseaza(l2..n) append l1, altfel     

(defun inverseaza(l)
    (cond
        ( (null l)  ())
        ( (atom (car l)) (append (inverseaza(cdr l)) (list (car l)) ) )
        ( T  ( append (inverseaza (cdr l)) (list(inverseaza(car l)) ) ) )
    )
)

(print (inverseaza '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))


;c) Dandu-se o lista, sa se construiasca lista primelor elemente ale tuturor elementelor lista ce au ;un numar impar de elemente la nivel superficial. 
;Exemplu: (1 2 (3 (4 5) (6 7)) 8 (9 10 11)) => (1 3 9)

(defun nrelem(l)
    (cond
        ( (null l) 0 )
        ( T (+ 1 (nrelem (cdr l))) )
    )
)

(defun nrelemimpar(l)
    (= (mod (nrelem l) 2) 1)
)


(defun listai(l)
    (cond
        ((null l) NIL) 
        ((atom (car l)) (listai (cdr l))) 
        ((nrelemimpar (car l)) (append (list(car (car l))) (listai (car l)) (listai (cdr l)))) 
        (T ( append (listai (car l)) (listai (cdr l)) ))
    )
) 

(defun listamain(l)
    (cond
        ( (null l) NIL)
        ( (AND (numberp(car l)) (nrelemimpar l)) (cons (car l) (listai(cdr l) )))
        (T (listai(l)) )
    )
)

;listai(l1..n) =     { [], daca n=0
;                    { listai(l2...n), daca l1 e atom
;                    { l1.1 (+) listai(l1.1...l1.n) (+)  listai(l2...n), l1 lista si n impar
;                    { listai(l1) (+) listai(l2..n) , daca l1 are nr par elem 

;listamain(l1...n) =  { [], daca n=0
;                     { l1 (+) listai(l2..n), daca l1 e numar si l1...n are numar impar de elemente
;                     { listai(l1..n), altfel

(print (listamain '(1 2 (3 (4 6 5) (6 7)) 8 (9 10 11))))


;d) Sa se construiasca o lista care intoarce suma atomilor numerici dintr-o lista la nivel superficial

; suma(l1..n) = { 0, daca n=0
;               { l1 + suma(l2..n), daca l1 e numar si n>0
;               { suma(l2..n), daca l1 nu e numar si n>0


(defun suma(l)
    (cond
        ((null l) 0)
        ((numberp (car l)) (+ (car l) (suma (cdr l)) ) )
        (T (suma (cdr l)))
    )
)

(print (suma '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))

; sumaToate(l1..n) = { 0, daca n=0
;                    { l1 + sumaToate(l2..n), daca l1 e numar si n>0
;                    { sumaToate(l1) + sumaToate(l2..n), daca l1 e lista si n>0
;                    { sumaToate(l2..n), daca l1 nu e numar si n>0


(defun suma2(l)
    (cond
        ((null l) 0)
        ((numberp (car l)) (+ (car l) (suma2 (cdr l)) ) )
        ((listp (car l)) (+ (suma2(car l)) (suma2(cdr l))  ) )
        (T (suma2 (cdr l)))
    )
)
