bits 32 

global start        

extern exit               
import exit msvcrt.dll   

segment data use32 class=data
    s db 1,2,3,4,5,6,7,8
    len equ $-s
    jumatatelen equ (len+1)/2
    d times len db 0

;6.Se da un sir de octeti S. Sa se construiasca sirul D astfel: sa se puna mai intai elementele de pe pozitiile pare din S iar apoi elementele de pe pozitiile impare din S.
; Exemplu:
; S: 1, 2, 3, 4, 5, 6, 7, 8
; D: 1, 3, 5, 7, 2, 4, 6, 8
segment code use32 class=code
    start:
	    mov ecx, len ;punem lungimea in ECX pentru a putea realiza bucla loop de ecx ori
	    mov esi, 0
        mov edi, 0
	    jecxz Sfarsit
	repeta:
        mov edx, 0
		mov eax, esi
        mov ebx, 2
        
        div ebx
        
        cmp edx, 0
        je pozPara
        ; Pozitie impara
        mov AL, [s + esi]
        mov [d + edi + jumatatelen], AL
        inc edi        
        inc esi
        
        jmp finalLoop
        
    pozPara: ; Pozitie para
        mov AL, [s + esi]
        mov [d + edi], AL
        inc esi
        
    finalLoop:
	    loop repeta
        
	Sfarsit:
	    push dword 0 
	    call [exit]  
