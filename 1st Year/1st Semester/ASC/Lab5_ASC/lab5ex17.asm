bits 32 

global start        

extern exit               
import exit msvcrt.dll   

segment data use32 class=data
    s1 db 1, 3, 6, 2, 3, 7
    len equ $-s1
    s2 db 6, 3, 8, 1, 2, 5
    ; sau scriu len equ s2-s1
    d times len db 0

; Se dau 2 siruri de octeti S1 si S2 de aceeasi lungime. Sa se construiasca sirul D astfel incatfiecare element din D sa reprezinte maximul dintre elementele de pe pozitiile corespunzatoare din S1 si S2.
; Exemplu:
; S1: 1, 3, 6, 2, 3, 7
; S2: 6, 3, 8, 1, 2, 5
;  D: 6, 3, 8, 2, 3, 7
segment code use32 class=code
    start:
        mov ecx,len
        mov esi,0
        jecxz sfarsit
    repeta:
        mov al,[s1+esi]
        mov bl,[s2+esi]
        cmp al,bl
        jge adauga_din_s1
        cmp al,bl
        jl adauga_din_s2
        jmp urmator
    
    adauga_din_s1:
        mov [d+esi],al
        jmp urmator        
        
    adauga_din_s2:
        mov [d+esi],bl
        
    urmator:
        inc esi
        loop repeta
        
    sfarsit:
        push    dword 0      
        call    [exit]      
