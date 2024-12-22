bits 32 

global start        

extern exit               
import exit msvcrt.dll   

segment data use32 class=data
    s db 1,3,2,3,4,5,6,7,8,3,4,5,9
    len equ $-s
    s1 db 3,4,5
    len1 equ $-s1
    d times len db 0
    
;28. Dandu-se un sir de octeti si un subsir al sau, sa se elimine din primul sir toate aparitiile subsirului.
segment code use32 class=code
    start:
        mov ecx, len
        mov esi, 0          ; i = 0
        mov edi, 0          ; j = 0
    repeta:
        ; citesc s[i]
        mov al, [s+esi]     ; AL = s[i]
        
        ; compar cu toate elementele subsirului s1
        push ecx
        push edi
        mov ecx, len1
        cld                 ; DF=0
        mov edi, s1         ; offsetul primului element din s1
        cauta:
            scasb           ; cmp AL, <ES:EDI> si inc EDI
            je continua
            loop cauta
        
        pop edi
        pop ecx
        mov [d+edi], al
        inc edi
        jmp mai_departe
        
    continua:
        pop edi
        pop ecx
    mai_departe:
        inc esi
        loop repeta
        
        
    
        push    dword 0      
        call    [exit]      
