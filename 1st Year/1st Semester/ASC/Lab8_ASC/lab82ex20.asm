bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fclose msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "ex22.txt", 0
    mod_acces db "w", 0
    descriptor dd 0
    format db "%c", 0
    
    text db "Problema   20 eqe"
    len equ $-text
    caracter db 0
    sir times 10 db 0

; our code starts here
segment code use32 class=code
    adaugare_fisier:
        push ecx
        mov [caracter], al
        push dword [caracter]
        push dword format
        push dword [descriptor]
        call [fprintf]
        add esp, 3*4
        pop ecx
        ret
        
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 8
        
        mov [descriptor], eax
        
        mov esi, 0
        mov ecx, len
        
        repeta:
            push ecx
            mov al, [text + esi]
            cmp al, " "
            je spatiu
            
            test esi, 01h
            je par
            
            mov eax, esi
            mov bl, 10
            mov edi, 0
            .repeta1:
                mov ah, 0
                div bl
                push eax
                mov al, ah
                add al, "0"
                mov [sir + edi], al
                inc edi
                pop eax
                cmp al, 0
            jne .repeta1
            push ecx
            mov ecx, edi
            .repeta2:
                mov al, [sir + ecx - 1]
                call adaugare_fisier
            loop .repeta2
            pop ecx
            
            jmp mai_departe
                
            par:
            
            spatiu:
            
            call adaugare_fisier
            
            mai_departe:
            pop ecx
            inc esi
        loop repeta
        
        push dword [descriptor]
        call [fclose]
        add esp, 4
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
