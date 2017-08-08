ENTRY(_start2)
/*STARTUP(objs/main.o)*/

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)


MEMORY
{
	rom	: ORIGIN = 0x08000000, LENGTH = 32M
	iwram	: ORIGIN = 0x03000000, LENGTH = 32K
	ewram	: ORIGIN = 0x02000000, LENGTH = 224K
	free_store	: ORIGIN = 0x02038000, LENGTH = 32K
	sram	: ORIGIN = 0x0e000000, LENGTH = 64K
}

__text_start	=	ORIGIN(rom);
__iwram_start	=	ORIGIN(iwram);
__ewram_start	=	ORIGIN(ewram);
__free_store_start	=	ORIGIN(free_store);
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
	
	startup_section_size = SIZEOF(.startup);
	
	.text :
	{
		CREATE_OBJECT_SYMBOLS
		/*
			*(.text .text.* .gnu.linkonce.t.*)
		*/
		
		*(.text .gnu.linkonce.t.*)
		
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
		
		. = ALIGN(4);
	} >rom
	
	text_section_size = SIZEOF(.text);
	
	.text_hot :
	{
		text_hot_rom_start = LOADADDR(.text_hot);
		text_hot_iwram_start = .;
		
		*(.text.hot*);
		
		. = ALIGN(4);
	} >iwram AT >rom
	
	text_hot_section_size = SIZEOF(.text_hot);
	
	/* 
		*(.text.*) is put AFTER *(.text.hot*) so that the .text_hot section
		goes into IWRAM
	*/
	.text_extra :
	{
		*(.text.*)
		. = ALIGN(4);
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
	
	init_array_section_size = SIZEOF(.init_array);
	
	
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
	
	data_section_size = SIZEOF(.data);
	
	
	/* Initialized data in IWRAM */
	.iwram_data :
	{
		__iwram_data_load = LOADADDR(.iwram_data);
		__iwram_data_start = .;
		
		*(.iwram_data .iwram_data.*)
		. = ALIGN(4);
		__iwram_data_end = .;
	} >iwram AT >rom
	iwram_data_section_size = SIZEOF(.iwram_data);
	
	
	
	/* Non .text.hot* Code to be copied to IWRAM */
	.iwram_code :
	{
		/* The start of code to be copied to IWRAM*/
		iwram_code_rom_start = LOADADDR(.iwram_code);
		
		iwram_code_iwram_start = .;
		
		*(.iwram_code);
		
		. = ALIGN(4);
	} >iwram AT >rom
	
	iwram_code_section_size = SIZEOF(.iwram_code);

	
	
	/* MaxMOD puts SOME code in the .iwram segment, so it will be treated as
	such here also */
	.some_maxmod_code :
	{
		. = ALIGN(4);
		/* The start of some MaxMOD code to be copied to IWRAM*/
		some_maxmod_code_rom_start = LOADADDR(.some_maxmod_code);
		
		some_maxmod_code_iwram_start = .;
		
		/* Some of MaxMOD's code goes into the ".iwram" section */
		*(.iwram);
		
		some_maxmod_code_iwram_end = .;
		
		. = ALIGN(4);
		
	} >iwram AT >rom
	
	some_maxmod_code_section_size = SIZEOF(.some_maxmod_code);
	
	/* Uninitialized variables that go into IWRAM*/
	.iwram_bss :
	{
		*(.iwram_bss .iwram_bss.*);
		
		. = ALIGN(4);
		/* The symbols end or __end__ are used to tell where malloc, new, and friends have free access. */
		/*end = .;*/
		/*__end__ = .;*/
	} >iwram
	
	iwram_bss_section_size = SIZEOF(.iwram_bss);

	
	/* total_iwram_var_size = iwram_data_section_size + iwram_bss_section_size; */
	
    /*total_iwram_code_size = text_hot_section_size + iwram_code_section_size + some_maxmod_code_section_size; */
	/* total_iwram_usage = total_iwram_var_size + total_iwram_code_size; */

	
	.ewram_code :
	{
		/* The start of code to be copied to EWRAM */
		ewram_code_rom_start = LOADADDR(.ewram_code);
		
		ewram_code_ewram_start = .;
		*(.ewram_code .ewram_code.*);
		
		. = ALIGN(4);
	} >ewram AT >rom

	ewram_code_section_size = SIZEOF(.ewram_code);
	
	
	
	/* BSS that's always "active" */
	.bss :
	{
		__bss_start__ = .;
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(.ewram .ewram.*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} >ewram
	bss_section_size = SIZEOF(.bss);

	/* The symbols end or __end__ are used to tell where malloc, new, and friends have free access. */
	end = __free_store_start;
	__end__ = __free_store_start;
	
	
	
	/*
	total_ewram_var_size = init_array_section_size + data_section_size + bss_section_size;
	total_ewram_code_size = ewram_code_section_size;
	total_ewram_usage = total_ewram_var_size + total_ewram_code_size;
	*/
	
	
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
	
	sram_section_size = SIZEOF(.sram);
	
	.stab : { *(.stab) } AT >rom
	.stabstr : { *(.stabstr) } AT >rom
	.comment : { *(.comment) } AT >rom
	.debug_frame : { *(.debug_frame) } AT >rom

	OVERLAY : NOCROSSREFS
	{
		.data0
		{
			__data0_load = LOADADDR(.data0);
			__data0_start = .;
			*(.data0 .data0.*);
			. = ALIGN(4);
			__data0_end = .;
		}
		.data1
		{
			__data1_load = LOADADDR(.data1);
			__data1_start = .;
			*(.data1 .data1.*);
			. = ALIGN(4);
			__data1_end = .;
		}
		.data2
		{
			__data2_load = LOADADDR(.data2);
			__data2_start = .;
			*(.data2 .data2.*);
			. = ALIGN(4);
			__data2_end = .;
		}
		.data3
		{
			__data3_load = LOADADDR(.data3);
			__data3_start = .;
			*(.data3 .data3.*);
			. = ALIGN(4);
			__data3_end = .;
		}
		.data4
		{
			__data4_load = LOADADDR(.data4);
			__data4_start = .;
			*(.data4 .data4.*);
			. = ALIGN(4);
			__data4_end = .;
		}
		.data5
		{
			__data5_load = LOADADDR(.data5);
			__data5_start = .;
			*(.data5 .data5.*);
			. = ALIGN(4);
			__data5_end = .;
		}
		.data6
		{
			__data6_load = LOADADDR(.data6);
			__data6_start = .;
			*(.data6 .data6.*);
			. = ALIGN(4);
			__data6_end = .;
		}
		.data7
		{
			__data7_load = LOADADDR(.data7);
			__data7_start = .;
			*(.data7 .data7.*);
			. = ALIGN(4);
			__data7_end = .;
		}
	} >ewram AT >rom
	__data0_section_size = SIZEOF(.data0);
	__data1_section_size = SIZEOF(.data1);
	__data2_section_size = SIZEOF(.data2);
	__data3_section_size = SIZEOF(.data3);
	__data4_section_size = SIZEOF(.data4);
	__data5_section_size = SIZEOF(.data5);
	__data6_section_size = SIZEOF(.data6);
	__data7_section_size = SIZEOF(.data7);
	
	OVERLAY : NOCROSSREFS
	{
		.iwram_data0
		{
			__iwram_data0_load = LOADADDR(.iwram_data0);
			__iwram_data0_start = .;
			
			*(.iwram_data0 .iwram_data0.*)
			. = ALIGN(4);
			__iwram_data0_end = .;
		}
		.iwram_data1
		{
			__iwram_data1_load = LOADADDR(.iwram_data1);
			__iwram_data1_start = .;
			
			*(.iwram_data1 .iwram_data1.*)
			. = ALIGN(4);
			__iwram_data1_end = .;
		}
		.iwram_data2
		{
			__iwram_data2_load = LOADADDR(.iwram_data2);
			__iwram_data2_start = .;
			
			*(.iwram_data2 .iwram_data2.*)
			. = ALIGN(4);
			__iwram_data2_end = .;
		}
		.iwram_data3
		{
			__iwram_data3_load = LOADADDR(.iwram_data3);
			__iwram_data3_start = .;
			
			*(.iwram_data3 .iwram_data3.*)
			. = ALIGN(4);
			__iwram_data3_end = .;
		}
		.iwram_data4
		{
			__iwram_data4_load = LOADADDR(.iwram_data4);
			__iwram_data4_start = .;
			
			*(.iwram_data4 .iwram_data4.*)
			. = ALIGN(4);
			__iwram_data4_end = .;
		}
		.iwram_data5
		{
			__iwram_data5_load = LOADADDR(.iwram_data5);
			__iwram_data5_start = .;
			
			*(.iwram_data5 .iwram_data5.*)
			. = ALIGN(4);
			__iwram_data5_end = .;
		}
		.iwram_data6
		{
			__iwram_data6_load = LOADADDR(.iwram_data6);
			__iwram_data6_start = .;
			
			*(.iwram_data6 .iwram_data6.*)
			. = ALIGN(4);
			__iwram_data6_end = .;
		}
		.iwram_data7
		{
			__iwram_data7_load = LOADADDR(.iwram_data7);
			__iwram_data7_start = .;
			
			*(.iwram_data7 .iwram_data7.*)
			. = ALIGN(4);
			__iwram_data7_end = .;
		}
	} >iwram AT >rom
	__iwram_data0_section_size = SIZEOF(.iwram_data0);
	__iwram_data1_section_size = SIZEOF(.iwram_data1);
	__iwram_data2_section_size = SIZEOF(.iwram_data2);
	__iwram_data3_section_size = SIZEOF(.iwram_data3);
	__iwram_data4_section_size = SIZEOF(.iwram_data4);
	__iwram_data5_section_size = SIZEOF(.iwram_data5);
	__iwram_data6_section_size = SIZEOF(.iwram_data6);
	__iwram_data7_section_size = SIZEOF(.iwram_data7);
	
	OVERLAY : NOCROSSREFS
	{
		.iwram_code0
		{
			iwram_code0_rom_start = LOADADDR(.iwram_code0);
			
			iwram_code0_iwram_start = .;
			
			*(.iwram_code0 .iwram_code0.*);
			
			. = ALIGN(4);
		}
		.iwram_code1
		{
			iwram_code1_rom_start = LOADADDR(.iwram_code1);
			
			iwram_code1_iwram_start = .;
			
			*(.iwram_code1 .iwram_code1.*);
			
			. = ALIGN(4);
		}
		.iwram_code2
		{
			iwram_code2_rom_start = LOADADDR(.iwram_code2);
			
			iwram_code2_iwram_start = .;
			
			*(.iwram_code2 .iwram_code2.*);
			
			. = ALIGN(4);
		}
		.iwram_code3
		{
			iwram_code3_rom_start = LOADADDR(.iwram_code3);
			
			iwram_code3_iwram_start = .;
			
			*(.iwram_code3 .iwram_code3.*);
			
			. = ALIGN(4);
		}
		.iwram_code4
		{
			iwram_code4_rom_start = LOADADDR(.iwram_code4);
			
			iwram_code4_iwram_start = .;
			
			*(.iwram_code4 .iwram_code4.*);
			
			. = ALIGN(4);
		}
		.iwram_code5
		{
			iwram_code5_rom_start = LOADADDR(.iwram_code5);
			
			iwram_code5_iwram_start = .;
			
			*(.iwram_code5 .iwram_code5.*);
			
			. = ALIGN(4);
		}
		.iwram_code6
		{
			iwram_code6_rom_start = LOADADDR(.iwram_code6);
			
			iwram_code6_iwram_start = .;
			
			*(.iwram_code6 .iwram_code6.*);
			
			. = ALIGN(4);
		}
		.iwram_code7
		{
			iwram_code7_rom_start = LOADADDR(.iwram_code7);
			
			iwram_code7_iwram_start = .;
			
			*(.iwram_code7 .iwram_code7.*);
			
			. = ALIGN(4);
		}
	} >iwram AT >rom
	__iwram_code0_section_size = SIZEOF(.iwram_code0);
	__iwram_code1_section_size = SIZEOF(.iwram_code1);
	__iwram_code2_section_size = SIZEOF(.iwram_code2);
	__iwram_code3_section_size = SIZEOF(.iwram_code3);
	__iwram_code4_section_size = SIZEOF(.iwram_code4);
	__iwram_code5_section_size = SIZEOF(.iwram_code5);
	__iwram_code6_section_size = SIZEOF(.iwram_code6);
	__iwram_code7_section_size = SIZEOF(.iwram_code7);
	
	OVERLAY : NOCROSSREFS
	{
		.iwram_bss0
		{
			*(.iwram_bss0 .iwram_bss0.*);

			. = ALIGN(4);
		}
		.iwram_bss1
		{
			*(.iwram_bss1 .iwram_bss1.*);

			. = ALIGN(4);
		}
		.iwram_bss2
		{
			*(.iwram_bss2 .iwram_bss2.*);

			. = ALIGN(4);
		}
		.iwram_bss3
		{
			*(.iwram_bss3 .iwram_bss3.*);

			. = ALIGN(4);
		}
		.iwram_bss4
		{
			*(.iwram_bss4 .iwram_bss4.*);

			. = ALIGN(4);
		}
		.iwram_bss5
		{
			*(.iwram_bss5 .iwram_bss5.*);

			. = ALIGN(4);
		}
		.iwram_bss6
		{
			*(.iwram_bss6 .iwram_bss6.*);

			. = ALIGN(4);
		}
		.iwram_bss7
		{
			*(.iwram_bss7 .iwram_bss7.*);

			. = ALIGN(4);
		}
	}
	__iwram_bss0_section_size = SIZEOF(.iwram_bss0);
	__iwram_bss1_section_size = SIZEOF(.iwram_bss1);
	__iwram_bss2_section_size = SIZEOF(.iwram_bss2);
	__iwram_bss3_section_size = SIZEOF(.iwram_bss3);
	__iwram_bss4_section_size = SIZEOF(.iwram_bss4);
	__iwram_bss5_section_size = SIZEOF(.iwram_bss5);
	__iwram_bss6_section_size = SIZEOF(.iwram_bss6);
	__iwram_bss7_section_size = SIZEOF(.iwram_bss7);
	
	OVERLAY : NOCROSSREFS
	{
		.ewram_code0
		{
			__ewram_code0_rom_start = LOADADDR(.ewram_code0);
			__ewram_code0_ewram_start = .;
			*(.ewram_code0 .ewram_code0.*);
			. = ALIGN(4);
		}
		.ewram_code1
		{
			__ewram_code1_rom_start = LOADADDR(.ewram_code0);
			__ewram_code1_ewram_start = .;
			*(.ewram_code1 .ewram_code1.*);
			. = ALIGN(4);
		}
		.ewram_code2
		{
			__ewram_code2_rom_start = LOADADDR(.ewram_code0);
			__ewram_code2_ewram_start = .;
			*(.ewram_code2 .ewram_code2.*);
			. = ALIGN(4);
		}
		.ewram_code3
		{
			__ewram_code3_rom_start = LOADADDR(.ewram_code0);
			__ewram_code3_ewram_start = .;
			*(.ewram_code3 .ewram_code3.*);
			. = ALIGN(4);
		}
		.ewram_code4
		{
			__ewram_code4_rom_start = LOADADDR(.ewram_code0);
			__ewram_code4_ewram_start = .;
			*(.ewram_code4 .ewram_code4.*);
			. = ALIGN(4);
		}
		.ewram_code5
		{
			__ewram_code5_rom_start = LOADADDR(.ewram_code0);
			__ewram_code5_ewram_start = .;
			*(.ewram_code5 .ewram_code5.*);
			. = ALIGN(4);
		}
		.ewram_code6
		{
			__ewram_code6_rom_start = LOADADDR(.ewram_code0);
			__ewram_code6_ewram_start = .;
			*(.ewram_code6 .ewram_code6.*);
			. = ALIGN(4);
		}
		.ewram_code7
		{
			__ewram_code7_rom_start = LOADADDR(.ewram_code0);
			__ewram_code7_ewram_start = .;
			*(.ewram_code7 .ewram_code7.*);
			. = ALIGN(4);
		}
	} >ewram AT >rom
	__ewram_code0_section_size = SIZEOF(.ewram_code0);
	__ewram_code1_section_size = SIZEOF(.ewram_code1);
	__ewram_code2_section_size = SIZEOF(.ewram_code2);
	__ewram_code3_section_size = SIZEOF(.ewram_code3);
	__ewram_code4_section_size = SIZEOF(.ewram_code4);
	__ewram_code5_section_size = SIZEOF(.ewram_code5);
	__ewram_code6_section_size = SIZEOF(.ewram_code6);
	__ewram_code7_section_size = SIZEOF(.ewram_code7);
	
	OVERLAY : NOCROSSREFS
	{
		/* Uninitialized (set to zero) variables that go into EWRAM */
		.bss0
		{
			__bss0_start__ = .;
			*(.bss0 .bss0.*)
			. = ALIGN(4);
			__bss0_end__ = .;
		}
		.bss1
		{
			__bss1_start__ = .;
			*(.bss1 .bss1.*)
			. = ALIGN(4);
			__bss1_end__ = .;
		}
		.bss2
		{
			__bss2_start__ = .;
			*(.bss2 .bss2.*)
			. = ALIGN(4);
			__bss2_end__ = .;
		}
		.bss3
		{
			__bss3_start__ = .;
			*(.bss3 .bss3.*)
			. = ALIGN(4);
			__bss3_end__ = .;
		}
		.bss4
		{
			__bss4_start__ = .;
			*(.bss4 .bss4.*)
			. = ALIGN(4);
			__bss4_end__ = .;
		}
		.bss5
		{
			__bss5_start__ = .;
			*(.bss5 .bss5.*)
			. = ALIGN(4);
			__bss5_end__ = .;
		}
		.bss6
		{
			__bss6_start__ = .;
			*(.bss6 .bss6.*)
			. = ALIGN(4);
			__bss6_end__ = .;
		}
		.bss7
		{
			__bss7_start__ = .;
			*(.bss7 .bss7.*)
			. = ALIGN(4);
			__bss7_end__ = .;
		}
	} >ewram
	__bss0_section_size = SIZEOF(.bss0);
	__bss1_section_size = SIZEOF(.bss1);
	__bss2_section_size = SIZEOF(.bss2);
	__bss3_section_size = SIZEOF(.bss3);
	__bss4_section_size = SIZEOF(.bss4);
	__bss5_section_size = SIZEOF(.bss5);
	__bss6_section_size = SIZEOF(.bss6);
	__bss7_section_size = SIZEOF(.bss7);
	

	/* 
	I figure I might as well have this, though it's probably not 
	needed.
	*/
	OVERLAY : NOCROSSREFS
	{
		.sram0
		{
			__sram0_start__ = .;
			*(.sram0 .sram0.*);

			. = ALIGN(4);
			__sram0_end__ = .;
		}
		.sram1
		{
			__sram1_start__ = .;
			*(.sram1 .sram1.*);

			. = ALIGN(4);
			__sram1_end__ = .;
		}
		.sram2
		{
			__sram2_start__ = .;
			*(.sram2 .sram2.*);

			. = ALIGN(4);
			__sram2_end__ = .;
		}
		.sram3
		{
			__sram3_start__ = .;
			*(.sram3 .sram3.*);

			. = ALIGN(4);
			__sram3_end__ = .;
		}
		.sram4
		{
			__sram4_start__ = .;
			*(.sram4 .sram4.*);

			. = ALIGN(4);
			__sram4_end__ = .;
		}
		.sram5
		{
			__sram5_start__ = .;
			*(.sram5 .sram5.*);

			. = ALIGN(4);
			__sram5_end__ = .;
		}
		.sram6
		{
			__sram6_start__ = .;
			*(.sram6 .sram6.*);

			. = ALIGN(4);
			__sram6_end__ = .;
		}
		.sram7
		{
			__sram7_start__ = .;
			*(.sram7 .sram7.*);

			. = ALIGN(4);
			__sram7_end__ = .;
		}
	} >sram
	
	__sram0_section_size = SIZEOF(.sram0);
	__sram1_section_size = SIZEOF(.sram1);
	__sram2_section_size = SIZEOF(.sram2);
	__sram3_section_size = SIZEOF(.sram3);
	__sram4_section_size = SIZEOF(.sram4);
	__sram5_section_size = SIZEOF(.sram5);
	__sram6_section_size = SIZEOF(.sram6);
	__sram7_section_size = SIZEOF(.sram7);
	
}

/*PROVIDE( _HEAP_START = 0x020200000 );

PROVIDE( _HEAP_END = 0x020300000 );*/

