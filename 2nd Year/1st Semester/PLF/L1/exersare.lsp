;(1(2 c f 1 ( d 2 c 4) e))  --- > ((f (d 4) e))

(defun nrap (l e)
    (cond
        ((null l) 0)
        ((listp (car l)) (+ (nrap (car l) e) (nrap (cdr l) e ) ))
        ((equal (car l) e) (+ 1 (nrap (cdr l) e)))
        (T (nrap (cdr l) e))
    )
)


(defun elimin (l1 l2)
    (cond
        ((null l1) NIL)
        ((listp (car l1)) (cons (elimin (car l1) l2 ) (elimin (cdr l1) l2 ) ) )
        ((> (nrap l2 (car l1)) 1) (elimin (cdr l1) l2))
        (T ( cons (car l1) (elimin (cdr l1) l2) ))
    )
)

(defun rulare(l)
    (cond
        ((null l) NIL)
        (T (elimin l l))
    )
)

;(print (rulare '(1(2 c f 1 ( d 2 c 4) e))))


;-------------------------------------------------------------------------------------------------
;adaugare un element la sfarsit

;ins (L : list, E : element, Poz : Intreg, P : Intreg)
;insereaza un element intr-o lista pe o pozitie data
;L = lista in care trebuie sa adaugam
;E = elementul pe care trebuie sa il adaugam
;Poz = Pozitia pe care trebuie sa il adaugam
;P = pozitia la fiecare pas in executie
(defun ins (L E Poz P)
    (cond 
        ((and (null L) (= Poz P)) (list E))
        ((null L) nil)
        ((= Poz P) (append (cons E (list (car L))) (ins (cdr L) E Poz (+ P 1))))
        (T (cons (car L) (ins (cdr L) E Poz (+ P 1))))
    )
)

;inserare1 (L : list, E : element, Poz : Intreg)
;insereaza un element pe toate pozitiile disponibile intr-o lista
;L = lista in care trebuie sa adaugam
;E = elementul pe care trebuie sa il adaugam
;Poz = Pozitia pe care trebuie sa il adaugam pe E la un anumit pas
(defun inserare1 (E L N Poz)
    (cond 
        ((< N Poz) nil)
        (T (append (list (ins L E Poz 1)) (inserare1 E L N (+ Poz 1))))
    )
)

;len (L : lista)
;determina lungimea unei liste
;L = lista a carei lungime vrem sa o aflam
(defun len (L)
    (cond 
        ((null L) 0)
        (T (+ 1 (len (cdr L))))
    )
)

;inserare (E : element, L : list)
;functia main
;E = elementul ce trebuie adaugat 
;L = lista in care trebuie adaugat
(defun inserare (E L)
    (cond
        ((null L) (list E))
        (T (inserare1 E L (+ (len L) 1) 1))
    )
)


;(print (inserare 4 '(1 2(3 5 8) 9)))


;-------------------------------------------------------------------------------------------

; eliminare toate aparitiile elementului maxim

(defun elmax(l mm)
    (cond
        ((null l) mm)
        ((listp (car l)) (max (elmax (car l) mm)(elmax (cdr l) mm) ))
        ((> (car l) mm)(elmax (cdr l) (car l)))
        (T (elmax (cdr l) mm) )
    )
)

(defun elemmax(l)
    (cond
        ((null l) ())
        (T (elmax l 0))
    )
)


(defun el(l lcop)
    (cond
        ((null l) ())
        ((listp (car l)) (cons (el(car l) lcop) (el (cdr l) lcop)) )
        ((= (car l) (elemmax lcop)) (el (cdr l) lcop))
        (T (cons (car l) (el (cdr l) lcop)))
    )
)

(defun eli(l)
    (cond
        ((null l) nil)
        (T (el l l))
    )
)

;(print (eli '(1 9 4( 5(3 9))5 2)))


;--------------------------------------------------------------------------------

; diferenta a 2 numere: (3 3 3)(1 1 1) => (2 2 2)

(defun subtract-sets (set1 set2)
  "Calculează diferența element cu element între două mulțimi."
  (mapcar #'- set1 set2)
)

;; Exemplu de utilizare directă
(print (subtract-sets '(3 3 3) '(1 9 1)))














