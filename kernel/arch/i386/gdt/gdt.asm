global gdt_load
gdt_load:
    mov eax, [esp+4]
    mov [gdt_descriptor + 2], eax
    mov ax, [esp+8]
    mov [gdt_descriptor], ax
    lgdt [gdt_descriptor]

    jmp 0x08:.reload_cs

.reload_cs:

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret


section .data
gdt_descriptor:
    dw 0x00 ; Size
    dd 0x00 ; GDT Start Address