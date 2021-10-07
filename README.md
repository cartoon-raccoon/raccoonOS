# raccoonOS

## a small UNIX-like operating system

---

This really isn't anything much, not much code has been written yet.

To build and run this, you will need to set up a GCC cross-compiler for Intel i386, as outlined in the OSDev wiki.
The path to the compiler and binutils executable folders _must_ be in your `$PATH` environment variable, if not already in a system path folder.

You will also need the QEMU emulator, for the x86_64 architecture.

To build:

```bash
make build
```

To run:

```bash
make clean #optional
make run
```

## Currently implemented

- Multiboot support with GRUB
- GDT and IDT
- Printing formatted strings to VGA TTY
- Logging to a file via QEMU's COM1 port
- Tiny lib{c,k} for convenience functions

Currently this OS will be built for i386, but I plan to build for x86_64 in the future, and maybe also for RISC architectures.

## Planned

- x86_64 support
- Some (or full, if possible) POSIX compliance
- A POSIX-compliant shell
- Basic networking - RTL8139 driver
- A GUI, potentially via Intel HD Graphics
- Sound support
- Symmetric multiprocessing
