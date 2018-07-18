
/* Custom para ejecutar el programa en la flash*/

/**/
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SEARCH_DIR(.)


/* Memory Spaces Definitions */
MEMORY
{
    /* ver datasheet pagina 38 */
    /* Realmente la ROM se encuentra en la dirección 0x0080 0000 *
     * e incluye un bootloader con SAM-BA IAP y FFPI,
     * pero la intención de esta definición es la flash. La      *
     * direccion de la flash varia para cada dispositivo. Para   *
     * el modelo SAM4SD32 se encuentra en 0x0040 00000. Este     *
     * dispositivo incluye 2 flash.                              */
/*    rom (rx) : ORIGIN 0x00800000, LENGTH = 0x00400000 */
    rom (rx)  : ORIGIN = 0x00400000, LENGTH = 0x00200000    /* Incluye 2 flash. 2*1024KB = 0x0020 0000 Bytes*/
/*    flash1 (rx) : ORIGIN = 0x00400000, LENGTH = 0x00100000 */
/*    flash2 (rx) : ORIGIN = 0x00500000, LENGTH = 0x00100000 */
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00028000    /* Addr 0x2000 0000 size
}


/* The stack size used by the application. NOTE: you need to adjust according to your application. */
STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : 0x400;

/* The heapsize used by the application. NOTE: you need to adjust according to your application. */
HEAP_SIZE = DEFINED(HEAP_SIZE) ? HEAP_SIZE : 0x200;



/* Secciones de nuestro programa salida*/
SECTIONS
{
. = 0x10000;    /* Location counter .  = 0x10000 */
/* Ahora listamos las input seccion que queremos incluir en esta output section.*/
.text :  /* *(.text) }  Todas las secion .text (* es un wildcard) las metemos en .text*/
{
    . = ALIGN(4);
    _sfixed = .; /* Almacenamos la dirección del inicial de la seccion en _sfixed*/
    /* En primer lugar colocamos los vectores de interrupcion*/
    KEEP(*(.vectors .vectors.*))   /* KEEP, evita que el garbage collector la borre, sea como sea.*/

     /* Support C constructors, and C destructors in both user code
     and the C library. This also provides support for C++ code. */
     . = ALIGN(4);
     KEEP(*(.init))
     . = ALIGN(4);
     __preinit_array_start = .;
     KEEP (*(.preinit_array))
     __preinit_array_end = .;

     . = ALIGN(4);
     __init_array_start = .;
     KEEP (*(SORT(.init_array.*)))
     KEEP (*(.init_array))
     __init_array_end = .;

     . = ALIGN(0x4);
     KEEP (*crtbegin.o(.ctors))
     KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
     KEEP (*(SORT(.ctors.*)))
     KEEP (*crtend.o(.ctors))

     . = ALIGN(4);
     KEEP(*(.fini))

     . = ALIGN(4);
     __fini_array_start = .;
     KEEP (*(.fini_array))
     KEEP (*(SORT(.fini_array.*)))
      __fini_array_end = .;

      KEEP (*crtbegin.o(.dtors))
      KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
      KEEP (*(SORT(.dtors.*)))
      KEEP (*crtend.o(.dtors))

      . = ALIGN(4);
      _efixed = .;            /* End of text section */
    } > rom

    /* .ARM.exidx is sorted, so has to go in its own output section.  */
PROVIDE_HIDDEN (__exidx_start = .);
.ARM.exidx :
               {
*(.ARM.exidx* .gnu.linkonce.armexidx.*)
} > rom
  PROVIDE_HIDDEN (__exidx_end = .);


    . = ALIGN(4);
    _efixed = .; /* Almacenamos la dirección del final de la seccion en _efixed*/
}

.relocate : AT (_etext)
{
. = ALIGN(4);
_srelocate = .;
*(.ramfunc .ramfunc.*);
*(.data .data.*);
. = ALIGN(4);
_erelocate = .;
} > ram

/* .bss section which is used for uninitialized data */
.bss (NOLOAD) :
{
. = ALIGN(4);
_sbss = . ;
_szero = .;
*(.bss .bss.*)
*(COMMON)
. = ALIGN(4);
_ebss = . ;
_ezero = .;
} > ram

/* stack section */
.stack (NOLOAD):
{
. = ALIGN(8);
_sstack = .;
. = . + STACK_SIZE;
. = ALIGN(8);
_estack = .;
} > ram

/* heap section */
.heap (NOLOAD):
{
. = ALIGN(8);
_sheap = .;
. = . + HEAP_SIZE;
. = ALIGN(8);
_eheap = .;
} > ram

. = ALIGN(4);
_end = . ;
_ram_end_ = ORIGIN(ram) + LENGTH(ram) -1 ;

. = 0x8000000; /* Location counter . = 0x8000000*/



.data : { *(.data) } /*Todas las secciones que tengan .data iran a continuacion */
.bss : { *(.bss) } /* Todas las secciones que tengan .bss iran a continuacion */
}
