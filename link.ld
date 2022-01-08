ENTRY(start)
phys = 0x00100000;
SECTIONS
{
    .text phys : AT(phys) {
        code = .;
        *(.text)
        *(.rodata)
        . = ALIGN(4096);
    }
    .data : AT(phys + (data - code))
    {
        start_ctors = .;
        KEEP(*( .init_array ));
        KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
        end_ctors = .;

        data = .;
        *(.data)
        . = ALIGN(4096);
    }
    .bss : AT(phys + (bss - code))
    {
        bss = .;
        *(.bss)
        . = ALIGN(4096);
    }
    end = .;
}