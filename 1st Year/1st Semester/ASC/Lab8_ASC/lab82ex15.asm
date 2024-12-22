bits 32 

global start        

extern exit,fopen,fread,fclose,fprintf,printf,scanf               
import exit msvcrt.dll  
import printf msvcrt.dll 
import scanf msvcrt.dll 
import fopen msvcrt.dll  
import fread msvcrt.dll 
import fclose msvcrt.dll 
import fprintf msvcrt.dll 

segment data use32 class=data
    text db 'V#Hj@7m*a4',0
    len_text equ $-text
    abc resb 10
    nume_fisier db 'ex15.txt',0
    carac_speciale db '(!@#$%^&*)',0
    lenc equ $-carac_speciale
    mod_acces db "w",0
    descriptor_fisier dd 0
    format db "%s",0
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        mov [descriptor_fisier],eax
        
        mov esi,0
        mov ecx,len_text
        cld
        repeta:
            mov al,[text+esi]
            push ecx
            mov ecx,lenc
            mov edi,0
            repeta2:    
                mov bl,[carac_speciale+edi]
                cmp al,bl
                je schimba
                jmp salt
                schimba:
                mov byte[text+esi],'X'
                jmp continua
                salt:
                inc edi
            loop repeta2
            continua:
            pop ecx
            inc esi
        loop repeta
        
        ; mov esi,text
        ; mov ecx,len_text
        ; cld
        ; repeta:
            ; lodsb
            ; push ecx
            ; mov ecx,lenc
            ; mov edi,carac_speciale
            ; repeta2:
                ; scasb
                ; je modifica
                ; jmp salt
                ; modifica:
                ; mov bl,'X'
                ; dec esi
                ; mov [text+esi],bl
                ; inc esi
                ; jmp continua
                ; salt:
            ; loop repeta2
            ; continua:
            ; pop ecx
        ; loop repeta
        
        push dword text
        push dword format
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      
        call    [exit]      
