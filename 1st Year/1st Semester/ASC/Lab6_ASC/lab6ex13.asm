bits 32 

global start        

extern exit               
import exit msvcrt.dll   

segment data use32 class=data
    s dd 12345607h, 1A2B3C15h, 13A33412h
    len equ ($-s)/4
    d times len db 0
    sapte db 7
; Se da un sir S de dublucuvinte.
; Sa se obtina sirul D format din octetii inferiori ai cuvintelor inferioare din elementele sirului de dublucuvinte, care sunt multiplii de 7.
; Exemplu:
; s DD 12345607h, 1A2B3C15h, 13A33412h
; d DB 07h, 15h
segment code use32 class=code
    start:
        mov esi,s
        mov edi,d
        cld
        mov ecx,len
        jecxz final
        repeta:
            lodsd   
            mov ah,0
            mov bl,al
            div byte[sapte]
            cmp ah,0
            jnz continua
            mov al,bl
            stosb
            continua:
        loop repeta
        jmp final

    final:
        push    dword 0      
        call    [exit]      
