ENTRY(_start2)
/*STARTUP(objs/main.o)*/

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)


MEMORY
{
	rom	: ORIGIN = 0x08000000, LENGTH = 32M
	iwram	: ORIGIN = 0x03000000, LENGTH = 32K
	ewram	: ORIGIN = 0x02000000, LENGTH = 256K
	sram	: ORIGIN = 0x0e000000, LENGTH = 64K
}

__text_start	=	ORIGIN(rom);
__ewram_start	=	ORIGIN(ewram);
__iwram_start	=	ORIGIN(iwram);
__sram_start	=	ORIGIN(sram);

SECTIONS
{
	. = __text_start;
	
	.startup :
	{
		*(.startup);
		*(.asm_text);
		. = ALIGN(4);
	} >rom
	
	.text :
	{
		CREATE_OBJECT_SYMBOLS
		*(.text .text.* .gnu.linkonce.t.*)
		*(.plt)
		*(.gnu_warning)
		*(.glue_7t) *(.glue_7)
		
		
		. = ALIGN(4);
		
		KEEP(*crtbegin.o(.ctors))
		KEEP(*(EXCLUDE_FILE(*crtend.o) .ctors))
		KEEP(*(SORT(.ctors.*)))
		KEEP(*crtend.o(.ctors))
		KEEP(*ctrbegin.o(.dtors))
		KEEP(*(EXCLUDE_FILE(*crtend.o) .dtors))
		KEEP(*(SORT(.dtors.*)))
		KEEP(*ctrend.o(.dtors))
		
		*(.rodata .rodata.* .gnu.linkonce.r.*)
		
		
		*(.init)
		*(.fini)
	} >rom
	
	.ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >rom
	__exidx_start = .;
	.ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } >rom
	__exidx_end = .;
	
	.ARM.attributes : { *(.ARM.attributes) } >rom
	
	
	.init_array : ALIGN(4)
	{
		__init_array_load = LOADADDR(.init_array);
		__init_array_start = .;
		*(.init_array)
		*(SORT_BY_INIT_PRIORITY(.init_array.*))
		__init_array_end = .;
	} >ewram AT >rom
	
	
	/* Initialized data in EWRAM */
	.data :
	{
		__data_load = LOADADDR(.data);
		__data_start = .;
		KEEP(*(.jcr))
		*(.got.plt) *(.got)
		*(.shdata)
		*(.data .data.* .gnu.linkonce.d.*)
		. = ALIGN(4);
		__data_end = .;
	} >ewram AT >rom
	
	/* Initialized data in IWRAM */
	.iwram_data :
	{
		__iwram_data_load = LOADADDR(.iwram_data);
		__iwram_data_start = .;
		
		*(.iwram_data .iwram_data.*)
		. = ALIGN(4);
		__iwram_data_end = .;
	} >iwram AT >rom
	
	
	/* Code to be copied to IWRAM */
	.iwram_code :
	{
		/* The start of code to be copied to IWRAM*/
		iwram_code_rom_start = LOADADDR(.iwram_code);
		
		iwram_code_iwram_start = .;
		
		*(.iwram_code);
		
		. = ALIGN(4);
	} >iwram AT >rom
	
	iwram_code_size = SIZEOF(.iwram_code);
	
	
	/* MaxMOD puts code in the .iwram segment, so it will be treated as such
	 * here also */
	.maxmod_code :
	{
		. = ALIGN(4);
		/* The start of MaxMOD code to be copied to IWRAM*/
		maxmod_code_rom_start = LOADADDR(.maxmod_code);
		
		maxmod_code_iwram_start = .;
		
		*(.iwram);
		
		maxmod_code_iwram_end = .;
		
		. = ALIGN(4);
		
	} >iwram AT >rom
	
	maxmod_code_size = SIZEOF(.maxmod_code);
	
	/* Uninitialized variables that go into IWRAM*/
	.iwram_bss :
	{
		*(.iwram_bss);
		
		. = ALIGN(4);
		/* The symbols end or __end__ are used to tell where malloc, new, and friends have free access. */
		/*end = .;*/
		/*__end__ = .;*/
	} >iwram
	
	
	.ewram_code :
	{
		/* The start of code to be copied to EWRAM */
		ewram_code_rom_start = LOADADDR(.ewram_code);
		
		ewram_code_ewram_start = .;
		*(.ewram_code);
		
		. = ALIGN(4);
	} >ewram AT >rom
	
	ewram_code_size = SIZEOF(.ewram_code);
	
	
	/* Uninitialized variables that go into EWRAM */
	.bss :
	{
		__bss_start__ = .;
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(.ewram .ewram.*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
		
		/* The symbols end or __end__ are used to tell where malloc, new, and friends have free access. */
		end = .;
		__end__ = .;
	} >ewram
	
	
	
	
	/*
	__iwram_size = SIZEOF(.iwram);
	__iwram_used = iwram_code_size + __iwram_size;
	__iwram_remaining = LENGTH(iwram) - __iwram_used;
	*/
	
	
	
	.sram :
	{
		*(.sram .sram.*);
		
		. = ALIGN(4);
	} >sram
	
	
	.stab : { *(.stab) } AT >rom
	.stabstr : { *(.stabstr) } AT >rom
	.comment : { *(.comment) } AT >rom
	.debug_frame : { *(.debug_frame) } AT >rom
}

/*PROVIDE( _HEAP_START = 0x020200000 );

PROVIDE( _HEAP_END = 0x020300000 );*/

