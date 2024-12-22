bits 32 

global start        

extern exit,printf               
import exit msvcrt.dll  
import printf msvcrt.dll 

segment data use32 class=data
    s1 dq 9234567812345678h,9234567812344678h
    len equ ($-s1)/8
    s2 times len dd 0
    format_afis db 'Numar vocale: %d',0
    numar db 0
    vocalee db 'aeiouAEIOU',0
    len_v db $-vocalee
segment code use32 class=code
    start:
        mov esi,s1
        mov edi,s2
        cld
        mov ecx,len
        repeta:
            mov eax,0
            mov ebx,0
            mov ax,word[esi+4]
            mov bx,word[esi+6]
            cmp ax,bx
            jg adauga
            jmp continua
            adauga:
            mov eax,dword[esi+4]
            mov dword[edi+0],eax
            continua:
            add edi,4
            add esi,8
        loop repeta
        
        push dword len
        push dword s2
        call vocale
        add esp,4*2
        
        push dword[numar]
        push dword format_afis
        call [printf]
        add esp,4*2
        
        push    dword 0      
        call    [exit] 
        
    vocale:
        mov esi,[esp+4]
        mov ecx,[esp+8]
        cld
        repeta2:
            mov bl,byte[esi+1]
            push ecx
            push esi
            mov ecx,len_v
            mov esi,vocalee
            cld
            repeta_vocale:
                lodsb
                cmp al,bl
                je creste
                jmp continua2
                creste:
                mov dl,1
                add [numar],dl
                continua2:
            loop repeta_vocale
            pop esi
            pop ecx
            add esi,4
        loop repeta2
        ret 
        
