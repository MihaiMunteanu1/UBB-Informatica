

; 6. Sa se construiasca o functie care intoarce produsul atomilor numerici 
; dintr-o lista, de la orice nivel

; produs(x) = { x, daca x e numar
;             { 1, daca x e atom nenumeric
;             { produs(x1)*produs(x2)*...*produs(xn), unde x=x1..n

(defun produs(x)
    (cond
        ((numberp x) x)
        ((atom x) 1)
        (T (apply '*(mapcar #' produs x)))
    )
)

(print (produs'(A 1 (B (3)) 4 C)))
