; File: calculator.asm
; Description: An assembly program implementing a calculator with addition,
; subtraction, multiplication, division, and modulus operations.
;
; Each operation is implemented as a separate function (procedure).

section .data
    ; Menu strings
    prompt_msg      db "Calculator Menu:", 10
                    db "1. Addition", 10
                    db "2. Subtraction", 10
                    db "3. Multiplication", 10
                    db "4. Division", 10
                    db "5. Modulus", 10
                    db "0. Exit", 10
                    db "Enter choice (0-5): ", 0
    
    ; Input prompts
    num1_msg        db "Enter first number: ", 0
    num2_msg        db "Enter second number: ", 0
    
    ; Output message
    result_msg      db "Result: ", 0
    
    ; Error message
    div_zero_msg    db "Error: Division by zero!", 10, 0
    
    ; Format strings for scanf and printf
    format_input    db "%d", 0
    format_output   db "%d", 10, 0
    newline         db 10, 0

section .bss
    ; Variables to store values
    choice  resd 1      ; User's menu choice
    num1    resd 1      ; First operand
    num2    resd 1      ; Second operand
    result  resd 1      ; Result of the operation

section .text
    global main
    extern printf       ; C function for formatted output
    extern scanf        ; C function for formatted input

; Main function - program entry point
main:
    ; Function prologue - save base pointer
    push rbp
    mov rbp, rsp

; Main menu loop
menu_loop:
    ; Display the menu
    mov rdi, prompt_msg
    xor rax, rax
    call printf

    ; Get user choice
    lea rdi, [format_input]
    lea rsi, [choice]
    xor rax, rax
    call scanf

    ; Check if exit chosen (0)
    mov eax, [choice]
    cmp eax, 0
    je exit_program

    ; Validate choice (1-5)
    cmp eax, 5
    jg menu_loop        ; If > 5, show menu again
    cmp eax, 1
    jl menu_loop        ; If < 1, show menu again

    ; Prompt for first number
    mov rdi, num1_msg
    xor rax, rax
    call printf

    ; Get first number
    lea rdi, [format_input]
    lea rsi, [num1]
    xor rax, rax
    call scanf

    ; Prompt for second number
    mov rdi, num2_msg
    xor rax, rax
    call printf

    ; Get second number
    lea rdi, [format_input]
    lea rsi, [num2]
    xor rax, rax
    call scanf

    ; Call appropriate operation based on choice
    mov eax, [choice]
    cmp eax, 1
    je do_addition
    cmp eax, 2
    je do_subtraction
    cmp eax, 3
    je do_multiplication
    cmp eax, 4
    je do_division
    cmp eax, 5
    je do_modulus
    jmp menu_loop       ; Fallback - should not reach here

; Addition operation dispatcher
do_addition:
    call addition
    jmp display_result

; Subtraction operation dispatcher
do_subtraction:
    call subtraction
    jmp display_result

; Multiplication operation dispatcher
do_multiplication:
    call multiplication
    jmp display_result

; Division operation dispatcher
do_division:
    ; Check for division by zero
    mov eax, [num2]
    cmp eax, 0
    je division_by_zero
    call division
    jmp display_result

; Modulus operation dispatcher
do_modulus:
    ; Check for division by zero (also applies to modulus)
    mov eax, [num2]
    cmp eax, 0
    je division_by_zero
    call modulus
    jmp display_result

; Division by zero error handler
division_by_zero:
    mov rdi, div_zero_msg
    xor rax, rax
    call printf
    jmp menu_loop

; Display the result of the operation
display_result:
    ; Print "Result: " prefix
    mov rdi, result_msg
    xor rax, rax
    call printf
    
    ; Print the actual result value
    mov rdi, format_output
    mov esi, [result]
    xor rax, rax
    call printf
    
    jmp menu_loop

; Exit the program
exit_program:
    ; Function epilogue - restore base pointer
    mov rsp, rbp
    pop rbp
    xor eax, eax        ; Return 0
    ret

;-------------------------------------------------------------------------
; Function implementations for each arithmetic operation
;-------------------------------------------------------------------------

; Addition function - adds num1 and num2, stores result in result
addition:
    mov eax, [num1]
    add eax, [num2]
    mov [result], eax
    ret

; Subtraction function - subtracts num2 from num1, stores result in result
subtraction:
    mov eax, [num1]
    sub eax, [num2]
    mov [result], eax
    ret

; Multiplication function - multiplies num1 by num2, stores result in result
multiplication:
    mov eax, [num1]
    imul eax, [num2]
    mov [result], eax
    ret

; Division function - divides num1 by num2, stores quotient in result
division:
    mov eax, [num1]
    cdq                 ; Sign-extend EAX into EDX:EAX
    idiv dword [num2]   ; Divide EDX:EAX by num2
    mov [result], eax   ; Store quotient in result
    ret

; Modulus function - divides num1 by num2, stores remainder in result
modulus:
    mov eax, [num1]
    cdq                 ; Sign-extend EAX into EDX:EAX
    idiv dword [num2]   ; Divide EDX:EAX by num2
    mov [result], edx   ; Store remainder in result (in EDX)
    ret
