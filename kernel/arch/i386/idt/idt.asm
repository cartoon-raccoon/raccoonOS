global idt_load
idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8]
    lidt [ebx]

    pop ebp
    ret

global enable_irqs
enable_irqs:
    sti
    ret

global disable_irqs
disable_irqs:
    cli
    ret

extern isr_handler

; Exception ISR handlers
%macro isr_err_stub 1
isr_stub_%+%1:
    push byte %1
    call isr_handler
    ;pop eax
    ;xor eax, eax
    iret
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    push byte 0
    push byte %1
    call isr_handler
    ;pop eax
    ;xor eax, eax
    iret
%endmacro

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

global isr_stub_table
isr_stub_table:
%assign i 0
%rep    32
    dd isr_stub_%+i
%assign i i+1
%endrep

extern int21h_handler

global int21h
int21h:
    cli
    pushad
    call int21h_handler
    popad
    sti
    iret