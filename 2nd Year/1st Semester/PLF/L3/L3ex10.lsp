

; 10. Definiti o functie care determina numarul nodurilor de pe nivelul k
; dintr-un arbore n-ar reprezentat sub forma (radacina lista_noduri_subarb1
; ... lista_noduri_subarbn) Ex: arborelele este (a (b (c)) (d) (e (f))) si
; k=1 => 3 noduri

;;  nrnoduri(L, k):
;;                0                         , n = 0
;;                1                         , k = 0 si n != 0
;;          SUMA(nrnoduri(li, k-1))         , L = l1...ln si k != 0 si n != 0
;;        i = 2 -> n

(defun nrnod(l k)
    (cond
        ((null l) 0)
        ((= k 0) 1)
        (T (apply '+ (mapcar (lambda (l) (nrnod l (- k 1))) (cdr l))))
    )
)

(print (nrnod '(a (b (c)) (d) (e (f))) 1))