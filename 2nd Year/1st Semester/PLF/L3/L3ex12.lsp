

; 12. Definiti o functie care inlocuieste un nod cu altul intr-un arbore n-ar
; reprezentat sub forma (radacina lista_noduri_subarb1...lista_noduri_subarbn)
; Ex: arborelele este (a (b (c)) (d) (e (f))) si nodul 'b se inlocuieste cu
; nodul 'g => arborele (a (g (c)) (d) (e (f)))

(defun SAU(l)
    (cond
        ((null l) NIL)
        (T (or (car l) (SAU (cdr l))))
    )   
)


(defun inlcarb(l e enou)
    (cond
        ((null l) NIL)
        ((equal (car l) e) (cons enou (mapcar (lambda(l) (inlcarb l e enou)) (cdr l)) ))
        ((listp l) (cons (car l) (mapcar (lambda(l) (inlcarb l e enou)) (cdr l))))
        (T l)
    )
)

(print (inlcarb '(a (b (c)) (d) (e (f))) 'b 'g ))