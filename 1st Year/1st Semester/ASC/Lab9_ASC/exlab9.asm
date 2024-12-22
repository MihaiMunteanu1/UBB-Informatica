bits 32 

global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd 0
    
    dimensiune dd 1
    count dd 100

    sir resb 100
    lungime_sir dd 0
    cifra_max db -1
    
    format_afisare db "%d", 0
    
;EX:  Citim sirul din fisier si afisam pe ecran cifra para maxima
segment code use32 class=code
    start:
        ; FILE * fopen(const char* nume_fisier, const char * mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp EAX, 0
        je final
        
        mov [descriptor_fisier], EAX
        
        ; int fread(void * str, int size, int count, FILE * stream)
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp, 4*4
        
        mov [lungime_sir], EAX ;eax tine minte lungime sir
        
        mov esi, sir
        mov ecx, [lungime_sir]
        cld
        jecxz sfarsitBucla
        
        bucla:
            ; Determinam cifra para maxima
            lodsb ; AL <- sir[i]
            
            sub AL, '0'
            
            test AL, 1
            jnz salt     ; Verificam daca e par
            
            cmp AL, [cifra_max]
            jle salt     ; Verificam daca e mai mare decat cifra_max
            
            mov [cifra_max], AL
            
            salt:
            loop bucla
        sfarsitBucla:
        
        ; int printf(const char * format, variabila_1);
        ; GRESIT: push dword [cifra_max]
        
        mov EAX, 0
        mov AL, [cifra_max]
        
        push EAX
        push dword format_afisare
        call [printf]
        add esp, 4*2
        
        ; int fclose(FILE * descriptor)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        
        final:
        ; exit(0)
        push    dword 0      
        call    [exit]       
