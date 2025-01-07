;permutari

;insereaza e pe pozitia n in lista l
(defun ins (e n l)
    (cond
        ((= n 1) (cons e l))
        (T (cons (car l) (ins e (- n 1) (cdr l))))
    )
)

;Creează o listă care conține toate posibilitățile de a insera elementul e în lista l, în toate ;pozițiile posibile, de la 1 până la n.
(defun insert (e n l)
    (cond
        ((= n 0) nil)
        (T (cons (ins e n l) (insert e (- n 1) l)))
    )
)

; Inserează elementul e în toate pozițiile posibile ale listei l.
(defun inserare (e l)
    (insert e (+ (length l) 1) l)
)

(defun permutari (l)
    (cond
        ((null l) (list nil)) 
        (T (permutari-aux (car l) (permutari (cdr l))))
    )
)

(defun permutari-aux (e p)
    (cond
        ((null p) nil) 
        (T (append (inserare e (car p)) (permutari-aux e (cdr p))))
   )
)

               
               
;(print (permutari '(1 2 3)))


;--------------------------------------------------------------------------------



;L1) 6.
; c) Sa se determine numarul tuturor sublistelor unei
; liste date, pe orice nivel. Prin sublista se intelege fie
; lista insasi, fie un element de pe orice nivel, care este lista.
; Exemplu: (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5
; (lista insasi, (3 ...), (4 5), (6 7), (9 10)).

(defun nrsubliste (l)
    (cond
        ((atom l) 0) 
        (T (+ 1 (nrsubliste-helper l)))
    )
)

(defun nrsubliste-helper (l)
    (cond
        ((null l) 0) 
        (T (+ (nrsubliste (car l)) (nrsubliste-helper (cdr l))))
    )
)


;(print (nrsubliste '(1 2 (3 (4 5) (6 7)) 8 (9 10))))



;L1) 4.
;c) Sa se scrie o functie care plecand de la o lista data ca argument, inverseaza numai secventele continue de atomi. Exemplu:
;(a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))

(defun inv(l)
    (cond
        ((null l) NIL)
        (T (append (inv (cdr l))(list(car l))))
    )
)


(defun invrseaza2(l linv)
    (cond
        ((null l) linv)
        ((listp (car l)) (append linv (cons (invrseaza2 (car l) ()) (invrseaza2 (cdr l) ())) ) )
        (T (invrseaza2 (cdr l) (append (list(car l)) linv  ) ) )
    )
)

;(print (invrseaza2 '(a b c (d (e f) g h i)) '() ))


;L1) 3a.
;Produs a doi vectori

(defun prodvectori (l p)
    (cond
        ((or (null l) (null p)) 0) 
        (t (+ (* (car l) (car p)) (prodvectori (cdr l) (cdr p))))
    )
)


;(print (prodvectori '(12 3) '(6 3)))


;L1) 3c.
;Definiti o functie care sorteaza fara pastrarea dublurilor o lista liniara.

(defun eliminaval(l e)
    (cond
        ( (null l) l )
        ( (= (car l) e) (eliminaval (cdr l) e) )
        ( T (cons (car l) (eliminaval (cdr l) e)) )
    )
)

(defun sorteaza (l)
    (cond
        ( (null l) () )
        ( T 
            (setq minim (apply #'min l))
            (cons minim (sorteaza (eliminaval l minim))) 
        )
    )
)

(print (sorteaza '(6 3 2 5 1 2 9)))








