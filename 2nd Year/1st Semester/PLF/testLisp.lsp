
;(1 2 (3(4 5 5)(6 B 7)) 8 (9 L 10 11))  => (1 3 4 9)

;nrimpar(l1..n, c) = { c, daca n=0
;                    { nrimpar(l2..n,c+1), daca l1 e atom numeric si n>0
;                    { nrimpar(l2..n,c), altfel
;l : lista a carei atomi numerici ii numaram
;c : variabila in care tinem minte nr de atomi numerici

(defun nrimpar(l)
    (cond
        ((null l) 0)
        ((numberp (car l)) (+ (nrimpar(cdr l) ) 1 ))
        (T (nrimpar (cdr l)) )
    )
)

;impar(l1..n) = { NIL, daca n=0
;               { NIL, daca are nr par de atomi numerici si n>0
;               { T, altfel
;l: lista pe care o verificam daca are un numar impar de atomi numerici

(defun impar(l)
    (cond
        ((null l) NIL)
        ((= (mod (nrimpar l) 2) 0) NIL)
        (T T)
    )
)


;primelem(l1..n,ok) = { NIL, daca n=0
;                     { l1 (+) primelem(l2..n,1), daca l1 e atom si l are numar impar de atomi ;                                                 numerici si ok=0 si n>0
;                     { primelem(l2..n,1), daca l1 e atom si n>0
;                     { primelem(l11...l1n,0) (+) primelem(l2..n,ok), altfel
;                                                                     (daca l1 e lista)

;l : lista din care dorim sa obtinem lista primelor elemente ale tuturor sublistelor cu numar impar de ;    atomi numerici
;ok: flag care ne ajuta sa tinem minte daca deja a fost adaugat sau nu atomul numeric al unei liste cu ;    numar impar de atomi numerici


(defun primelem(l ok)
    (cond
        ((null l) NIL)
        ((and (and (atom (car l)) (impar l )) (= ok 0) ) (cons (car l) (primelem (cdr l) 1)))
        ((atom (car l)) (primelem (cdr l) 1))
        (T (append ( primelem (car l) 0) ( primelem (cdr l) ok)) )
    )
)


(print (primelem '(1 2(3 (4 5 5)(6 B 7)) 8 (9 L 10 11)) 0))
; => (1 3 4 9)

(print (primelem '(1 A 2 B 3 4 5) 0))
; => (1)

(print (primelem '(1 (2 B 4)(4 J 7 (5 G 6)) (7 8)) 0))
; => (1)

(print (primelem '(1 (2 A)(3 (A 4))(5 6(9 F 9)(7 (8 6 9) 10)) 11) 0))
; => (2 3 A 8)






