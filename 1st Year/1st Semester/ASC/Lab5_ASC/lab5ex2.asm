bits 32
global start        

extern exit               
import exit msvcrt.dll    
segment data use32 class=data
    a db '+','4','2','a','@','3','$','*'
    len equ $-a
    d times len db 0
;Se da un sir de caractere S. Sa se construiasca sirul D care sa 
;contina toate caracterele speciale (!@#$%^&*) din sirul S.
; S: '+', '4', '2', 'a', '@', '3', '$', '*'
; D: '@','$','*'
segment code use32 class=code
    start:
        mov ecx, len
        mov esi, 0
        jecxz sfarsit

    repeta:
        mov al, [a+esi]
        cmp al, '@'
        je adauga
        cmp al, '$'
        je adauga
        cmp al, '*'
        je adauga
        jmp urmator

    adauga:
        mov [d+esi], al

    urmator:
        inc esi
        loop repeta
    sfarsit:
        push    dword 0      
        call    [exit]       
