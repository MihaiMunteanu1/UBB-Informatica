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
    nume_fisier db "ex13.txt",0
    text db 'sbGVHSbj@73ima',0
    mod_acces db "w",0
    len_text equ $-text
    text_bun resb 20
    
    descriptor_fisier dd 0
    format db "%s",0
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        mov [descriptor_fisier],eax
        mov esi,text
        mov ecx,len_text
        mov edi,text_bun
        cld
        repeta:
            lodsb
            cmp al,'a'
            jge next
            jmp salt
            next:
            cmp al,'z'
            jle next2
            jmp salt
            next2:
            sub al,32  ;lit mica in mare
            salt:
            stosb
        loop repeta
        
        
        push dword text_bun
        push dword format
        push dword [descriptor_fisier]
        call  [fprintf]
        add esp,4*3
        
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      
        call    [exit]      
