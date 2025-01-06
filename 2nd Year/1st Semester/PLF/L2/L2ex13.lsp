

;13. Se da un arbore de tipul (2). Sa se afiseze calea de la radacina pana la un
;nod x dat.

(defun find-path (tree x)
    (cond
        ;Dacă arborele este nil, nu avem cale
        ((null tree) nil) 
        
        ;Dacă nodul curent este nodul căutat, întoarce o listă cu nodul
        ((equal (car tree) x) (list (car tree))) 

        ;Încearcă să găsești nodul în subarborele stâng
        ((find-path (cadr tree) x)(cons (car tree) (find-path (cadr tree) x)))

        ;Dacă nu e în subarborele stâng, încearcă în cel drept
        ((find-path (caddr tree) x)(cons (car tree) (find-path (caddr tree) x)))

        (T nil) ;Dacă nodul nu este găsit, întoarce nil
    )
)

(print (find-path '(A (B) (C (D (G) (H) ) (E))) 'H ))