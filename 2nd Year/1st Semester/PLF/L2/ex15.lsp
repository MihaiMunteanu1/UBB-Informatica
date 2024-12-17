
; 15. Sa se construiasca lista nodurilor unui arbore de tipul (1) 
; parcurs in postordine

; (A 2 B 0 C 2 D 0 E 0)  => ( B D E C A )


;parcurg_st(l1..n, nv, nm) ={ (), daca n = 0
;                           { (), daca nv = nm + 1 si n>0
;                           { l1 (+) l2 (+) parcurg_st(l3..n, nv+1, nm+l2) altfel

;stang(l1..n) = parcurg_st(l1..n, 0, 0)

(defun parcurg_st(arb nv nm)
    (cond
        ((null arb) nil)
        ((= nv (+ 1 nm)) nil)
        (t (cons (car arb) (cons (cadr arb) (parcurg_st (cddr arb) (+ 1 nv) (+ (cadr arb) nm)))))
    )
)

(defun stang(arb)
    (parcurg_st (cddr arb) 0 0)
)


;parcurg_dr(l1..n, nv, nm) ={ (), daca n = 0
;                           { parcurg_dr(l3..n, nv + 1, nm + l2), daca nv <= nm  si n>0
;                           { l1..n, altfel

;drept(l1..n) = parcurg_dr(l1..n, 0, 0)

(defun parcurg_dr(arb nv nm)
    (cond
        ((null arb) nil)
        (( <= nv nm ) (parcurg_dr (cddr arb) (+ 1 nv) (+ (cadr arb) nm)) )
        (t arb )
    )
)

(defun drept(arb)
    (parcurg_dr (cddr arb) 0 0)
)

;postordine(l1..n) = { (), daca n=0
;                    { postordine(stang(l1..n)) (+) postordine(drept(l1..n)) (+) l1, altfel

(defun postordine (arb)
    (cond
        ((null arb) nil)
        (t ( append (postordine (stang arb) ) (postordine (drept arb) ) (list (car arb)) ) )
    )
)

(print (postordine '(A 2 B 0 C 2 D 0 E 0) ))
(print (postordine '(A 2 B 1 D 0 C 2 E 0 F 0))) 
(print (postordine '(A 2 B 1 H 1 I 1 J 0 C 2 D 2 F 1 K 0 G 0 E 0))) 



