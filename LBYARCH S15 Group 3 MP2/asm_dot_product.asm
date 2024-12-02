;MP2 of Diamante, David Alexander, & Javid, Isaac
section .data
    fmt db "Assembly Dot Product = %lf", 10, 0    ; Format string for printf (newline included)

section .bss
    temp resq 1        ; Temporary space for storing the result

section .text
global asm_dot_product
extern printf

asm_dot_product:

    ;rcx has ptr A, rdx has ptr B, r8 has int n

    vxorpd xmm2, xmm2, xmm2   ; Clear xmm2 to store the sum
    mov rax, rcx
    mov rbx, rdx
    mov rcx, r8           ; Move the integer argument into rcx for loop
    xor r8, r8                ; r8 will hold the loop index
    
.loop:

    movsd xmm0, [rax + r8 * 8]     ; Load the double value pointed to by ptr1
    movsd xmm1, [rbx + r8 * 8]     ; Load the double value pointed to by ptr2
    mulsd xmm0, xmm1           ; Multiply A and B elements
    addsd xmm2, xmm0           ; Accumulate into xmm0

    inc r8                     ; Increment loop counter
    
    dec rcx                    ; Decrement index by 1
    jnz .loop                 ; Repeat the loop

    ; Result is stored in xmm2 (floating-point return convention)
    movsd qword [rel temp], xmm2  ; Store result in temp for output
    
    sub rsp, 8*5		; set up stack frame, must be alligned
	
    mov rdx, [rel temp]
    mov	rcx, fmt
    call printf		; Call C function

    add rsp, 8*5		; restore stack
    
    xor rax, rax
    ret                        ; Return (result in xmm0)
