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
    nume_fisier db "input.txt",0
    mod_acces db "r",0
    descriptor_fisier dd 0
    cifre db '0','1','2','3','4','5','6','7','8','9',0
    lenc equ $-cifre
    
    dimensiune dd 1
    count dd 100
    sir resb 100    
    lungime_sir dd 0
    
    format_afisare db "cifra: %d, cu frecventa: %d", 0

segment code use32 class=code
    start:
        ;fopen
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        mov [descriptor_fisier],eax
        
        ;fread
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp,4*4
        
        mov [lungime_sir],eax
        
        mov esi,cifre
        mov ecx,lenc
        cld
        jecxz final
        mov edx,0
        mov eax,0
        mov ebx,0
        repeta:
            lodsb
            push ecx
            mov ecx,[lungime_sir]
            mov bl,0
            mov edi,sir
            repeta2:
                scasb
                je adauga
                jmp salt
                adauga:
                inc bl
                salt:
            loop repeta2
            cmp bl,dl ;compara frecventa
            jg cifra_max
            jmp continua
            cifra_max:
            mov dl,bl ;pune frecv maxima in dl
            mov dh,al ;muta cifra maxima in dh
            continua:
            pop ecx
        loop repeta
        
        mov eax,0
        mov al,dh
        sub al,'0'
        mov ebx,0
        mov bl,dl
        
        push ebx
        push eax
        push dword format_afisare
        call [printf]
        add esp,4*3
        
        ;fclose
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
    final:
        push    dword 0      
        call    [exit]      
