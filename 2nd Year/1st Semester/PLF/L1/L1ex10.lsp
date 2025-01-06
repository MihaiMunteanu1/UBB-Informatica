

;a) Sa se construiasca o functie care intoarce produsul atomilor numerici dintr-o lista, de la nivelul ;superficial.

(defun prod(l)
    (cond
        ((null l) 1)
        ((numberp (car l)) (* (car l) (prod (cdr l))))
        (T (prod (cdr l)))
    )
)

;(print (prod '(2 3(4 5) 6)))


;b) Sa se scrie o functie care, primind o lista, intoarce multimea tuturor perechilor din lista. De ;exemplu: (a b c d) --> ((a b) (a c) (a d)(b c) (b d) (c d))


(defun pair (e l)
    (cond
        ((null l) nil)
        (T (cons (list e (car l)) (pair e (cdr l))))
    )
)

(defun pairs (l)
    (cond
        ((null (car l)) nil)
        (T (append (pair (car l) (cdr l)) (pairs (cdr l))))  
    )
)

;(print (pairs '(a b c d)))

;c) Sa se determine rezultatul unei expresii aritmetice memorate in preordine pe o stiva. Exemple:
;(+ 1 3) ==> 4 (1 + 3)
;(+ * 2 4 3) ==> 11 ((2 * 4) + 3)
;(+ * 2 4 - 5 * 2 2) ==> 9 ((2 * 4) + (5 - (2 * 2))

(defun _expression (op a b)
	(cond
		((string= op "+") (+ a b)) 
		((string= op "-") (- a b))
		((string= op "*") (* a b))
		((string= op "/") (floor a b))
	)
)

(defun expression (l) 
    (cond
        ((null l) nil)
        ((and (and (numberp (cadr l)) (numberp (caddr l))) (atom (car l))) 
            (cons (_expression (car l) (cadr l) (caddr l)) (expression (cdddr l))))
        (T (cons (car l) (expression (cdr l))))
    )
)

(defun solve (l)
    (cond
        ((null (cdr l)) (car l))
        (T (solve (expression l)))
    )
)
            


;d) Definiti o functie care, dintr-o lista de atomi, produce o lista de perechi (atom n), unde atom ;apare in lista initiala de n ori. De ex:
;(A B A B A C A) --> ((A 4) (B 2) (C 1)).


(defun nr_app (l e)
    (cond
        ((null l) 0)
        ((equal (car l) e) (+ 1 (nr_app (cdr l) e)))
        (T (nr_app (cdr l) e))
    )
)

(defun remov (l e)
    (cond
        ((null l) nil)
        ((equal (car l) e) (remov (cdr l) e))
        (T (cons (car l) (remov (cdr l) e)))
    )
)

(defun freq (l)
    (cond
        ((null l) nil)
        (T (cons (list (car l) (nr_app l (car l))) (freq (remov (cdr l) (car l)))))
    )
)

(print (freq '(A B A B A C A)))




