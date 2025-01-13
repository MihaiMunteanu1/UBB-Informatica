
;ex1 2019
;sterge un element

(defun sterg_el(l e)
    (cond
        ((equal l e) NIL)
        ((atom l) l)
        (T (mapcar (lambda (l) (sterg_el l e)) l))
    )
)
;sau
(defun sterg_el2(l e)
    (cond
        ((null l) NIL)
        ((listp (car l)) (cons (sterg_el2 (car l) e) (sterg_el2 (cdr l) e) ) )
        ((equal (car l) e) (sterg_el2 (cdr l) e))
        (T (cons (car l) (sterg_el2 (cdr l) e)))
    )
)
;(print (sterg_el2 '(1 (2 A(3 A) (A))) 'A))

;nr sublistelor unde ultimul atom de la orice nivel e atom nenumeric
(defun verif_lista(l)
    (cond
        ((null l) NIL)
        ((and (listp (car l)) (null (cdr l))) (verif_lista (car l)))
        ((listp (car l)) (verif_lista (cdr l)))
        ((and (null (cdr l)) (numberp (car l))) NIL)
        ((null (cdr l)) T)
        (T (verif_lista (cdr l)))
    )
)

(defun last_atom(l)
    (cond
        ((null l) 0)
        ((atom l) 0)
        ((verif_lista l) (+ 1 (apply #'+ (mapcar #' last_atom l))))
        (T (apply #'+ (mapcar #' last_atom l)))
    )
)
;(print (last_atom '(1 2 3 (5 A 2) B C (D C) (3 A) 4)) )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;ex1 2020

(defun f(l1 l2)
    ((lambda (l)
        (append l
            (cond
                ((null l1) (cdr l2))
                (T (list l (car l2)))
            )
        )
     )
     (f (car l1) l2)
    )
)

;;;

; (defun g(l)
;     (mapcon #' list l)
; )

; (apply #' append (mapcon #' g '(1 2))) => (1 2 2 2)

;           g '(1 2) => ((1 2) 2)
; mapcon #' g '(1 2) => ((1 2) (2) (2))



(defun sterge_div3(l)
    (cond
        ((and (numberp l) (= (mod l 3) 0)) NIL)
        ((atom l) l)
        (T (mapcar #' sterge_div3 l))
    )
)

;(print (sterge_div3 '(1(2 A(3 A))(6)) ))
;(print (sterge_div3 '(1(2 C)) ))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;ex2 2019

(defun crst_nr_par(l)
    (cond
        ((and (numberp l) (= (mod l 2) 0)) (+ l 1))
        ((atom l) l)
        (T (mapcar #' crst_nr_par l))
    )
)

(defun crst_nr_par2(l)
    (cond
        ((null l) NIL)
        ((and (numberp (car l)) (= (mod (car l) 2) 0)) (cons (+ (car l) 1) (crst_nr_par2 (cdr l)) ))
        ((atom (car l)) (cons (car l) (crst_nr_par2 (cdr l))))
        (T (cons (crst_nr_par2(car l)) (crst_nr_par2 (cdr l))))
    )
)

;(print (crst_nr_par2 '(1 s 4(2 f(7))) ))


;;;;
(defun nr_max(l mx)
    (cond
        ((null l) mx)
        ((and (numberp (car l)) (> (car l) mx)) (nr_max (cdr l) (car l)))
        ((atom (car l)) (nr_max (cdr l) mx))
        (T (max (nr_max (car l) mx) (nr_max (cdr l) mx)))
    )
)

(defun nr_subl(l nv)
    (cond
        ((atom l) 0)
        ((and (= (mod nv 2) 1) (= (mod (nr_max l 0) 2 ) 0)) 
               (+ 1 (apply #'+ (mapcar (lambda (subl) (nr_subl subl (+ nv 1))) l ) )))
        (T (apply #'+ (mapcar (lambda (subl) ( nr_subl subl (+ nv 1))) l)))
    )
)


;(print (nr_subl '(A(B 2)(1 C 4)(1 (6 F))(((G)4)6)) 1))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;ex2 2020

;1. Folosim lambda:

(defun Fct(F L)
    ((lambda (X)
        (cond
            ((NULL L) nil)
            (X 
                (cons X (Fct F (CDR L)))
            )
            (T nil)
        )
     )
    )
)

;;; => A A
(defun gg(l)
    (list (car l) (car l))
)

;;;
;INLOCUIESTE TOATE NODURILE DE PE NIVELURI IMPARE CU UN ELEMENT

(defun replce(l e nv)
    (cond
        ((and (atom l) (= (mod nv 2) 1)) e)
        ((atom l) l)
        (T (cons (replce (car l) e nv) (mapcar (lambda (l) (replce l e (+ nv 1))) (cdr l))))
    )
)


;(print (replce '(a(b(c(d(e(f)))))) 'h 0))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;ex3 2019


(defun stergn(l n i)
    (cond
        ((null l) NIL)
        ((= (mod i n) 0) (stergn (cdr l) n (+ i 1) ))
        (T (cons (car l) (stergn (cdr l) n (+ i 1))))
    )
)

;(print (stergn '(1 2 3 4 5) 2 1))

;;;
;nr de subliste cu nr impar de atomi nenumerici la nivelele pare

(defun nr_atom (l)
    (cond
        ((null l) 0)                              
        ((numberp (car l)) (nr_atom (cdr l)))     
        ((atom (car l)) (+ 1 (nr_atom (cdr l))))  
        (T (+ (nr_atom (car l)) (nr_atom (cdr l))))
    )
) 


(defun nr_subl(l nv)
    (cond
        ((atom l) 0)
        ((and (= (mod nv 2) 0) (= (mod (nr_atom l) 2 ) 1)) 
               (+ 1 (apply #'+ (mapcar (lambda (subl) (nr_subl subl (+ nv 1))) l ) )))
        (T (apply #'+ (mapcar (lambda (subl) ( nr_subl subl (+ nv 1))) l)))
    )
)


;(print (nr_subl '(A(B 2)(1 C 4)(1 (6 F))(((G)4)6)) 1))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;ex3 2020


;1.3 ==>  1 2 3 4 5 7

(defun rpl_niv_0(l nv k)
    (cond
        ((and (atom l) (= nv k)) 0)
        ((atom l) l)
        (T (mapcar (lambda(elem)( rpl_niv_0 elem (+ nv 1) k)) l))
    )
)

(print (rpl_niv_0 '(a(1(2 b))(c(d))) 0 2))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;ex4 2019

(defun inlocuire0 (l k nv)
    (cond
        ((and (atom (car l)) (= k nv)) (cons 0 (inlocuire0 (cdr l) k nv)))
        ((atom (car l)) (cons (car l) (inlocuire0 (cdr l) k nv)))
        (T (cons (inlocuire0 (car l) k (+ nv 1)) (inlocuire0 (cdr l) k nv) ))
    )
)

;(print (inlocuire0 '(a(1(2 b))(c(d))) 2 1))


;;;





