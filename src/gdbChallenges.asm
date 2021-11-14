global gdbme

%macro push_params 0
    push rdi
    push rsi
    push rdx
    push rcx
%endmacro

%macro pop_params 0
    pop rcx
    pop rdx
    pop rsi
    pop rdi
%endmacro

extern strlen
extern write

; gdbme(int writeFd, char* answerBase, char* answerValue, char* badAnswer)
gdbme:
        push rbp
        mov rbp, rsp

        cmp eax, 0x12345678
        jne writeBadAnswer

        push_params
        mov rdi, rsi        ; put answerBase string as argument
        call strlen
        pop_params
        
        push_params
        mov rdx, rax        ; chars to print, rsi still has answerBase string
        call write
        pop_params

        push_params
        mov rdi, rdx        ; put answerValue string as argument
        call strlen
        pop_params
        
        push_params
        mov rsi, rdx        ; put answerValue string as argument
        mov rdx, rax        ; chars to print
        call write
        pop_params

        jmp end

    writeBadAnswer:
        push_params
        mov rdi, rcx        ; put badAnswer string as argument
        call strlen
        pop_params

        push_params
        mov rsi, rcx        ; put badAnswer as string
        mov rdx, rax        ; chars to print
        call write
        pop_params

        jmp end

    end:
        pop rbx
        leave
        ret