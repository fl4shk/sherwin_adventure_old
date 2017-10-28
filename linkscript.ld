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
			__data0_rom_start__ = LOADADDR(.data0); 
			__data0_ewram_start__ = .; 
			*(.__data0 .__data0.*); 
			. = ALIGN(4); 
			__data0_ewram_end__ = .; 
		} 
		.data1 
		{ 
			__data1_rom_start__ = LOADADDR(.data1); 
			__data1_ewram_start__ = .; 
			*(.__data1 .__data1.*); 
			. = ALIGN(4); 
			__data1_ewram_end__ = .; 
		} 
		.data2 
		{ 
			__data2_rom_start__ = LOADADDR(.data2); 
			__data2_ewram_start__ = .; 
			*(.__data2 .__data2.*); 
			. = ALIGN(4); 
			__data2_ewram_end__ = .; 
		} 
		.data3 
		{ 
			__data3_rom_start__ = LOADADDR(.data3); 
			__data3_ewram_start__ = .; 
			*(.__data3 .__data3.*); 
			. = ALIGN(4); 
			__data3_ewram_end__ = .; 
		} 
		.data4 
		{ 
			__data4_rom_start__ = LOADADDR(.data4); 
			__data4_ewram_start__ = .; 
			*(.__data4 .__data4.*); 
			. = ALIGN(4); 
			__data4_ewram_end__ = .; 
		} 
		.data5 
		{ 
			__data5_rom_start__ = LOADADDR(.data5); 
			__data5_ewram_start__ = .; 
			*(.__data5 .__data5.*); 
			. = ALIGN(4); 
			__data5_ewram_end__ = .; 
		} 
		.data6 
		{ 
			__data6_rom_start__ = LOADADDR(.data6); 
			__data6_ewram_start__ = .; 
			*(.__data6 .__data6.*); 
			. = ALIGN(4); 
			__data6_ewram_end__ = .; 
		} 
		.data7 
		{ 
			__data7_rom_start__ = LOADADDR(.data7); 
			__data7_ewram_start__ = .; 
			*(.__data7 .__data7.*); 
			. = ALIGN(4); 
			__data7_ewram_end__ = .; 
		} 
		.data8 
		{ 
			__data8_rom_start__ = LOADADDR(.data8); 
			__data8_ewram_start__ = .; 
			*(.__data8 .__data8.*); 
			. = ALIGN(4); 
			__data8_ewram_end__ = .; 
		} 
		.data9 
		{ 
			__data9_rom_start__ = LOADADDR(.data9); 
			__data9_ewram_start__ = .; 
			*(.__data9 .__data9.*); 
			. = ALIGN(4); 
			__data9_ewram_end__ = .; 
		} 
		.data10 
		{ 
			__data10_rom_start__ = LOADADDR(.data10); 
			__data10_ewram_start__ = .; 
			*(.__data10 .__data10.*); 
			. = ALIGN(4); 
			__data10_ewram_end__ = .; 
		} 
		.data11 
		{ 
			__data11_rom_start__ = LOADADDR(.data11); 
			__data11_ewram_start__ = .; 
			*(.__data11 .__data11.*); 
			. = ALIGN(4); 
			__data11_ewram_end__ = .; 
		} 
		.data12 
		{ 
			__data12_rom_start__ = LOADADDR(.data12); 
			__data12_ewram_start__ = .; 
			*(.__data12 .__data12.*); 
			. = ALIGN(4); 
			__data12_ewram_end__ = .; 
		} 
		.data13 
		{ 
			__data13_rom_start__ = LOADADDR(.data13); 
			__data13_ewram_start__ = .; 
			*(.__data13 .__data13.*); 
			. = ALIGN(4); 
			__data13_ewram_end__ = .; 
		} 
		.data14 
		{ 
			__data14_rom_start__ = LOADADDR(.data14); 
			__data14_ewram_start__ = .; 
			*(.__data14 .__data14.*); 
			. = ALIGN(4); 
			__data14_ewram_end__ = .; 
		} 
		.data15 
		{ 
			__data15_rom_start__ = LOADADDR(.data15); 
			__data15_ewram_start__ = .; 
			*(.__data15 .__data15.*); 
			. = ALIGN(4); 
			__data15_ewram_end__ = .; 
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
		__data8_section_size = SIZEOF(.data8); 
		__data9_section_size = SIZEOF(.data9); 
		__data10_section_size = SIZEOF(.data10); 
		__data11_section_size = SIZEOF(.data11); 
		__data12_section_size = SIZEOF(.data12); 
		__data13_section_size = SIZEOF(.data13); 
		__data14_section_size = SIZEOF(.data14); 
		__data15_section_size = SIZEOF(.data15); 
 



	OVERLAY : NOCROSSREFS
	{
		/*
		.iwram_data0
		{
			__iwram_data0_load = LOADADDR(.iwram_data0);
			__iwram_data0_start = .;

			*(.iwram_data0 .iwram_data0.*)
			. = ALIGN(4);
			__iwram_data0_end = .;
		}
		*/
		.iwram_data0 
		{ 
			__iwram_data0_rom_start__ = LOADADDR(.iwram_data0); 
			__iwram_data0_iwram_start__ = .; 
			*(.iwram_data0 .iwram_data0.*) 
			. = ALIGN(4); 
			__iwram_data0_iwram_end__ = .; 
		} 
		.iwram_data1 
		{ 
			__iwram_data1_rom_start__ = LOADADDR(.iwram_data1); 
			__iwram_data1_iwram_start__ = .; 
			*(.iwram_data1 .iwram_data1.*) 
			. = ALIGN(4); 
			__iwram_data1_iwram_end__ = .; 
		} 
		.iwram_data2 
		{ 
			__iwram_data2_rom_start__ = LOADADDR(.iwram_data2); 
			__iwram_data2_iwram_start__ = .; 
			*(.iwram_data2 .iwram_data2.*) 
			. = ALIGN(4); 
			__iwram_data2_iwram_end__ = .; 
		} 
		.iwram_data3 
		{ 
			__iwram_data3_rom_start__ = LOADADDR(.iwram_data3); 
			__iwram_data3_iwram_start__ = .; 
			*(.iwram_data3 .iwram_data3.*) 
			. = ALIGN(4); 
			__iwram_data3_iwram_end__ = .; 
		} 
		.iwram_data4 
		{ 
			__iwram_data4_rom_start__ = LOADADDR(.iwram_data4); 
			__iwram_data4_iwram_start__ = .; 
			*(.iwram_data4 .iwram_data4.*) 
			. = ALIGN(4); 
			__iwram_data4_iwram_end__ = .; 
		} 
		.iwram_data5 
		{ 
			__iwram_data5_rom_start__ = LOADADDR(.iwram_data5); 
			__iwram_data5_iwram_start__ = .; 
			*(.iwram_data5 .iwram_data5.*) 
			. = ALIGN(4); 
			__iwram_data5_iwram_end__ = .; 
		} 
		.iwram_data6 
		{ 
			__iwram_data6_rom_start__ = LOADADDR(.iwram_data6); 
			__iwram_data6_iwram_start__ = .; 
			*(.iwram_data6 .iwram_data6.*) 
			. = ALIGN(4); 
			__iwram_data6_iwram_end__ = .; 
		} 
		.iwram_data7 
		{ 
			__iwram_data7_rom_start__ = LOADADDR(.iwram_data7); 
			__iwram_data7_iwram_start__ = .; 
			*(.iwram_data7 .iwram_data7.*) 
			. = ALIGN(4); 
			__iwram_data7_iwram_end__ = .; 
		} 
		.iwram_data8 
		{ 
			__iwram_data8_rom_start__ = LOADADDR(.iwram_data8); 
			__iwram_data8_iwram_start__ = .; 
			*(.iwram_data8 .iwram_data8.*) 
			. = ALIGN(4); 
			__iwram_data8_iwram_end__ = .; 
		} 
		.iwram_data9 
		{ 
			__iwram_data9_rom_start__ = LOADADDR(.iwram_data9); 
			__iwram_data9_iwram_start__ = .; 
			*(.iwram_data9 .iwram_data9.*) 
			. = ALIGN(4); 
			__iwram_data9_iwram_end__ = .; 
		} 
		.iwram_data10 
		{ 
			__iwram_data10_rom_start__ = LOADADDR(.iwram_data10); 
			__iwram_data10_iwram_start__ = .; 
			*(.iwram_data10 .iwram_data10.*) 
			. = ALIGN(4); 
			__iwram_data10_iwram_end__ = .; 
		} 
		.iwram_data11 
		{ 
			__iwram_data11_rom_start__ = LOADADDR(.iwram_data11); 
			__iwram_data11_iwram_start__ = .; 
			*(.iwram_data11 .iwram_data11.*) 
			. = ALIGN(4); 
			__iwram_data11_iwram_end__ = .; 
		} 
		.iwram_data12 
		{ 
			__iwram_data12_rom_start__ = LOADADDR(.iwram_data12); 
			__iwram_data12_iwram_start__ = .; 
			*(.iwram_data12 .iwram_data12.*) 
			. = ALIGN(4); 
			__iwram_data12_iwram_end__ = .; 
		} 
		.iwram_data13 
		{ 
			__iwram_data13_rom_start__ = LOADADDR(.iwram_data13); 
			__iwram_data13_iwram_start__ = .; 
			*(.iwram_data13 .iwram_data13.*) 
			. = ALIGN(4); 
			__iwram_data13_iwram_end__ = .; 
		} 
		.iwram_data14 
		{ 
			__iwram_data14_rom_start__ = LOADADDR(.iwram_data14); 
			__iwram_data14_iwram_start__ = .; 
			*(.iwram_data14 .iwram_data14.*) 
			. = ALIGN(4); 
			__iwram_data14_iwram_end__ = .; 
		} 
		.iwram_data15 
		{ 
			__iwram_data15_rom_start__ = LOADADDR(.iwram_data15); 
			__iwram_data15_iwram_start__ = .; 
			*(.iwram_data15 .iwram_data15.*) 
			. = ALIGN(4); 
			__iwram_data15_iwram_end__ = .; 
		} 

	} >iwram AT >rom

	/* __iwram_data0_section_size = SIZEOF(.iwram_data0); */
		__iwram_data0_section_size = SIZEOF(.iwram_data0); 
		__iwram_data1_section_size = SIZEOF(.iwram_data1); 
		__iwram_data2_section_size = SIZEOF(.iwram_data2); 
		__iwram_data3_section_size = SIZEOF(.iwram_data3); 
		__iwram_data4_section_size = SIZEOF(.iwram_data4); 
		__iwram_data5_section_size = SIZEOF(.iwram_data5); 
		__iwram_data6_section_size = SIZEOF(.iwram_data6); 
		__iwram_data7_section_size = SIZEOF(.iwram_data7); 
		__iwram_data8_section_size = SIZEOF(.iwram_data8); 
		__iwram_data9_section_size = SIZEOF(.iwram_data9); 
		__iwram_data10_section_size = SIZEOF(.iwram_data10); 
		__iwram_data11_section_size = SIZEOF(.iwram_data11); 
		__iwram_data12_section_size = SIZEOF(.iwram_data12); 
		__iwram_data13_section_size = SIZEOF(.iwram_data13); 
		__iwram_data14_section_size = SIZEOF(.iwram_data14); 
		__iwram_data15_section_size = SIZEOF(.iwram_data15); 


	OVERLAY : NOCROSSREFS
	{
		/*
		.iwram_code0
		{
			iwram_code0_rom_start = LOADADDR(.iwram_code0);

			iwram_code0_iwram_start = .;

			*(.iwram_code0 .iwram_code0.*);

			. = ALIGN(4);
		}
		*/
		.iwram_code0 
		{ 
			__iwram_code0_rom_start__ = LOADADDR(.iwram_code0); 
			__iwram_code0_iwram_start__ = .; 
			*(.iwram_code0 .iwram_code0.*); 
			. = ALIGN(4); 
			__iwram_code0_iwram_end__ = .; 
		} 
		.iwram_code1 
		{ 
			__iwram_code1_rom_start__ = LOADADDR(.iwram_code1); 
			__iwram_code1_iwram_start__ = .; 
			*(.iwram_code1 .iwram_code1.*); 
			. = ALIGN(4); 
			__iwram_code1_iwram_end__ = .; 
		} 
		.iwram_code2 
		{ 
			__iwram_code2_rom_start__ = LOADADDR(.iwram_code2); 
			__iwram_code2_iwram_start__ = .; 
			*(.iwram_code2 .iwram_code2.*); 
			. = ALIGN(4); 
			__iwram_code2_iwram_end__ = .; 
		} 
		.iwram_code3 
		{ 
			__iwram_code3_rom_start__ = LOADADDR(.iwram_code3); 
			__iwram_code3_iwram_start__ = .; 
			*(.iwram_code3 .iwram_code3.*); 
			. = ALIGN(4); 
			__iwram_code3_iwram_end__ = .; 
		} 
		.iwram_code4 
		{ 
			__iwram_code4_rom_start__ = LOADADDR(.iwram_code4); 
			__iwram_code4_iwram_start__ = .; 
			*(.iwram_code4 .iwram_code4.*); 
			. = ALIGN(4); 
			__iwram_code4_iwram_end__ = .; 
		} 
		.iwram_code5 
		{ 
			__iwram_code5_rom_start__ = LOADADDR(.iwram_code5); 
			__iwram_code5_iwram_start__ = .; 
			*(.iwram_code5 .iwram_code5.*); 
			. = ALIGN(4); 
			__iwram_code5_iwram_end__ = .; 
		} 
		.iwram_code6 
		{ 
			__iwram_code6_rom_start__ = LOADADDR(.iwram_code6); 
			__iwram_code6_iwram_start__ = .; 
			*(.iwram_code6 .iwram_code6.*); 
			. = ALIGN(4); 
			__iwram_code6_iwram_end__ = .; 
		} 
		.iwram_code7 
		{ 
			__iwram_code7_rom_start__ = LOADADDR(.iwram_code7); 
			__iwram_code7_iwram_start__ = .; 
			*(.iwram_code7 .iwram_code7.*); 
			. = ALIGN(4); 
			__iwram_code7_iwram_end__ = .; 
		} 
		.iwram_code8 
		{ 
			__iwram_code8_rom_start__ = LOADADDR(.iwram_code8); 
			__iwram_code8_iwram_start__ = .; 
			*(.iwram_code8 .iwram_code8.*); 
			. = ALIGN(4); 
			__iwram_code8_iwram_end__ = .; 
		} 
		.iwram_code9 
		{ 
			__iwram_code9_rom_start__ = LOADADDR(.iwram_code9); 
			__iwram_code9_iwram_start__ = .; 
			*(.iwram_code9 .iwram_code9.*); 
			. = ALIGN(4); 
			__iwram_code9_iwram_end__ = .; 
		} 
		.iwram_code10 
		{ 
			__iwram_code10_rom_start__ = LOADADDR(.iwram_code10); 
			__iwram_code10_iwram_start__ = .; 
			*(.iwram_code10 .iwram_code10.*); 
			. = ALIGN(4); 
			__iwram_code10_iwram_end__ = .; 
		} 
		.iwram_code11 
		{ 
			__iwram_code11_rom_start__ = LOADADDR(.iwram_code11); 
			__iwram_code11_iwram_start__ = .; 
			*(.iwram_code11 .iwram_code11.*); 
			. = ALIGN(4); 
			__iwram_code11_iwram_end__ = .; 
		} 
		.iwram_code12 
		{ 
			__iwram_code12_rom_start__ = LOADADDR(.iwram_code12); 
			__iwram_code12_iwram_start__ = .; 
			*(.iwram_code12 .iwram_code12.*); 
			. = ALIGN(4); 
			__iwram_code12_iwram_end__ = .; 
		} 
		.iwram_code13 
		{ 
			__iwram_code13_rom_start__ = LOADADDR(.iwram_code13); 
			__iwram_code13_iwram_start__ = .; 
			*(.iwram_code13 .iwram_code13.*); 
			. = ALIGN(4); 
			__iwram_code13_iwram_end__ = .; 
		} 
		.iwram_code14 
		{ 
			__iwram_code14_rom_start__ = LOADADDR(.iwram_code14); 
			__iwram_code14_iwram_start__ = .; 
			*(.iwram_code14 .iwram_code14.*); 
			. = ALIGN(4); 
			__iwram_code14_iwram_end__ = .; 
		} 
		.iwram_code15 
		{ 
			__iwram_code15_rom_start__ = LOADADDR(.iwram_code15); 
			__iwram_code15_iwram_start__ = .; 
			*(.iwram_code15 .iwram_code15.*); 
			. = ALIGN(4); 
			__iwram_code15_iwram_end__ = .; 
		} 

	} >iwram AT >rom

	/* __iwram_code0_section_size = SIZEOF(.iwram_code0); */
		__iwram_code0_section_size = SIZEOF(.iwram_code0); 
		__iwram_code1_section_size = SIZEOF(.iwram_code1); 
		__iwram_code2_section_size = SIZEOF(.iwram_code2); 
		__iwram_code3_section_size = SIZEOF(.iwram_code3); 
		__iwram_code4_section_size = SIZEOF(.iwram_code4); 
		__iwram_code5_section_size = SIZEOF(.iwram_code5); 
		__iwram_code6_section_size = SIZEOF(.iwram_code6); 
		__iwram_code7_section_size = SIZEOF(.iwram_code7); 
		__iwram_code8_section_size = SIZEOF(.iwram_code8); 
		__iwram_code9_section_size = SIZEOF(.iwram_code9); 
		__iwram_code10_section_size = SIZEOF(.iwram_code10); 
		__iwram_code11_section_size = SIZEOF(.iwram_code11); 
		__iwram_code12_section_size = SIZEOF(.iwram_code12); 
		__iwram_code13_section_size = SIZEOF(.iwram_code13); 
		__iwram_code14_section_size = SIZEOF(.iwram_code14); 
		__iwram_code15_section_size = SIZEOF(.iwram_code15); 


	OVERLAY : NOCROSSREFS
	{
		/*
		.iwram_bss0
		{
			*(.iwram_bss0 .iwram_bss0.*);

			. = ALIGN(4);
		}
		*/
		.iwram_bss0 
		{ 
			__iwram_bss0_start__ = .; 
			*(.iwram_bss0 .iwram_bss0.*); 
			. = ALIGN(4); 
			__iwram_bss0_end__ = .; 
		} 
		.iwram_bss1 
		{ 
			__iwram_bss1_start__ = .; 
			*(.iwram_bss1 .iwram_bss1.*); 
			. = ALIGN(4); 
			__iwram_bss1_end__ = .; 
		} 
		.iwram_bss2 
		{ 
			__iwram_bss2_start__ = .; 
			*(.iwram_bss2 .iwram_bss2.*); 
			. = ALIGN(4); 
			__iwram_bss2_end__ = .; 
		} 
		.iwram_bss3 
		{ 
			__iwram_bss3_start__ = .; 
			*(.iwram_bss3 .iwram_bss3.*); 
			. = ALIGN(4); 
			__iwram_bss3_end__ = .; 
		} 
		.iwram_bss4 
		{ 
			__iwram_bss4_start__ = .; 
			*(.iwram_bss4 .iwram_bss4.*); 
			. = ALIGN(4); 
			__iwram_bss4_end__ = .; 
		} 
		.iwram_bss5 
		{ 
			__iwram_bss5_start__ = .; 
			*(.iwram_bss5 .iwram_bss5.*); 
			. = ALIGN(4); 
			__iwram_bss5_end__ = .; 
		} 
		.iwram_bss6 
		{ 
			__iwram_bss6_start__ = .; 
			*(.iwram_bss6 .iwram_bss6.*); 
			. = ALIGN(4); 
			__iwram_bss6_end__ = .; 
		} 
		.iwram_bss7 
		{ 
			__iwram_bss7_start__ = .; 
			*(.iwram_bss7 .iwram_bss7.*); 
			. = ALIGN(4); 
			__iwram_bss7_end__ = .; 
		} 
		.iwram_bss8 
		{ 
			__iwram_bss8_start__ = .; 
			*(.iwram_bss8 .iwram_bss8.*); 
			. = ALIGN(4); 
			__iwram_bss8_end__ = .; 
		} 
		.iwram_bss9 
		{ 
			__iwram_bss9_start__ = .; 
			*(.iwram_bss9 .iwram_bss9.*); 
			. = ALIGN(4); 
			__iwram_bss9_end__ = .; 
		} 
		.iwram_bss10 
		{ 
			__iwram_bss10_start__ = .; 
			*(.iwram_bss10 .iwram_bss10.*); 
			. = ALIGN(4); 
			__iwram_bss10_end__ = .; 
		} 
		.iwram_bss11 
		{ 
			__iwram_bss11_start__ = .; 
			*(.iwram_bss11 .iwram_bss11.*); 
			. = ALIGN(4); 
			__iwram_bss11_end__ = .; 
		} 
		.iwram_bss12 
		{ 
			__iwram_bss12_start__ = .; 
			*(.iwram_bss12 .iwram_bss12.*); 
			. = ALIGN(4); 
			__iwram_bss12_end__ = .; 
		} 
		.iwram_bss13 
		{ 
			__iwram_bss13_start__ = .; 
			*(.iwram_bss13 .iwram_bss13.*); 
			. = ALIGN(4); 
			__iwram_bss13_end__ = .; 
		} 
		.iwram_bss14 
		{ 
			__iwram_bss14_start__ = .; 
			*(.iwram_bss14 .iwram_bss14.*); 
			. = ALIGN(4); 
			__iwram_bss14_end__ = .; 
		} 
		.iwram_bss15 
		{ 
			__iwram_bss15_start__ = .; 
			*(.iwram_bss15 .iwram_bss15.*); 
			. = ALIGN(4); 
			__iwram_bss15_end__ = .; 
		} 

	} >iwram

	/* __iwram_bss0_section_size = SIZEOF(.iwram_bss0); */
		__iwram_bss0_section_size = SIZEOF(.iwram_bss0); 
		__iwram_bss1_section_size = SIZEOF(.iwram_bss1); 
		__iwram_bss2_section_size = SIZEOF(.iwram_bss2); 
		__iwram_bss3_section_size = SIZEOF(.iwram_bss3); 
		__iwram_bss4_section_size = SIZEOF(.iwram_bss4); 
		__iwram_bss5_section_size = SIZEOF(.iwram_bss5); 
		__iwram_bss6_section_size = SIZEOF(.iwram_bss6); 
		__iwram_bss7_section_size = SIZEOF(.iwram_bss7); 
		__iwram_bss8_section_size = SIZEOF(.iwram_bss8); 
		__iwram_bss9_section_size = SIZEOF(.iwram_bss9); 
		__iwram_bss10_section_size = SIZEOF(.iwram_bss10); 
		__iwram_bss11_section_size = SIZEOF(.iwram_bss11); 
		__iwram_bss12_section_size = SIZEOF(.iwram_bss12); 
		__iwram_bss13_section_size = SIZEOF(.iwram_bss13); 
		__iwram_bss14_section_size = SIZEOF(.iwram_bss14); 
		__iwram_bss15_section_size = SIZEOF(.iwram_bss15); 


	OVERLAY : NOCROSSREFS
	{
		/*
		.ewram_code0
		{
			__ewram_code0_rom_start = LOADADDR(.ewram_code0);
			__ewram_code0_ewram_start = .;
			*(.ewram_code0 .ewram_code0.*);
			. = ALIGN(4);
		}
		*/
		.ewram_code0 
		{ 
			__ewram_code0_rom_start__ = LOADADDR(.ewram_code0); 
			__ewram_code0_ewram_start__ = .; 
			*(.ewram_code0 .ewram_code0.*); 
			. = ALIGN(4); 
			__ewram_code0_ewram_end__ = .; 
		} 
		.ewram_code1 
		{ 
			__ewram_code1_rom_start__ = LOADADDR(.ewram_code1); 
			__ewram_code1_ewram_start__ = .; 
			*(.ewram_code1 .ewram_code1.*); 
			. = ALIGN(4); 
			__ewram_code1_ewram_end__ = .; 
		} 
		.ewram_code2 
		{ 
			__ewram_code2_rom_start__ = LOADADDR(.ewram_code2); 
			__ewram_code2_ewram_start__ = .; 
			*(.ewram_code2 .ewram_code2.*); 
			. = ALIGN(4); 
			__ewram_code2_ewram_end__ = .; 
		} 
		.ewram_code3 
		{ 
			__ewram_code3_rom_start__ = LOADADDR(.ewram_code3); 
			__ewram_code3_ewram_start__ = .; 
			*(.ewram_code3 .ewram_code3.*); 
			. = ALIGN(4); 
			__ewram_code3_ewram_end__ = .; 
		} 
		.ewram_code4 
		{ 
			__ewram_code4_rom_start__ = LOADADDR(.ewram_code4); 
			__ewram_code4_ewram_start__ = .; 
			*(.ewram_code4 .ewram_code4.*); 
			. = ALIGN(4); 
			__ewram_code4_ewram_end__ = .; 
		} 
		.ewram_code5 
		{ 
			__ewram_code5_rom_start__ = LOADADDR(.ewram_code5); 
			__ewram_code5_ewram_start__ = .; 
			*(.ewram_code5 .ewram_code5.*); 
			. = ALIGN(4); 
			__ewram_code5_ewram_end__ = .; 
		} 
		.ewram_code6 
		{ 
			__ewram_code6_rom_start__ = LOADADDR(.ewram_code6); 
			__ewram_code6_ewram_start__ = .; 
			*(.ewram_code6 .ewram_code6.*); 
			. = ALIGN(4); 
			__ewram_code6_ewram_end__ = .; 
		} 
		.ewram_code7 
		{ 
			__ewram_code7_rom_start__ = LOADADDR(.ewram_code7); 
			__ewram_code7_ewram_start__ = .; 
			*(.ewram_code7 .ewram_code7.*); 
			. = ALIGN(4); 
			__ewram_code7_ewram_end__ = .; 
		} 
		.ewram_code8 
		{ 
			__ewram_code8_rom_start__ = LOADADDR(.ewram_code8); 
			__ewram_code8_ewram_start__ = .; 
			*(.ewram_code8 .ewram_code8.*); 
			. = ALIGN(4); 
			__ewram_code8_ewram_end__ = .; 
		} 
		.ewram_code9 
		{ 
			__ewram_code9_rom_start__ = LOADADDR(.ewram_code9); 
			__ewram_code9_ewram_start__ = .; 
			*(.ewram_code9 .ewram_code9.*); 
			. = ALIGN(4); 
			__ewram_code9_ewram_end__ = .; 
		} 
		.ewram_code10 
		{ 
			__ewram_code10_rom_start__ = LOADADDR(.ewram_code10); 
			__ewram_code10_ewram_start__ = .; 
			*(.ewram_code10 .ewram_code10.*); 
			. = ALIGN(4); 
			__ewram_code10_ewram_end__ = .; 
		} 
		.ewram_code11 
		{ 
			__ewram_code11_rom_start__ = LOADADDR(.ewram_code11); 
			__ewram_code11_ewram_start__ = .; 
			*(.ewram_code11 .ewram_code11.*); 
			. = ALIGN(4); 
			__ewram_code11_ewram_end__ = .; 
		} 
		.ewram_code12 
		{ 
			__ewram_code12_rom_start__ = LOADADDR(.ewram_code12); 
			__ewram_code12_ewram_start__ = .; 
			*(.ewram_code12 .ewram_code12.*); 
			. = ALIGN(4); 
			__ewram_code12_ewram_end__ = .; 
		} 
		.ewram_code13 
		{ 
			__ewram_code13_rom_start__ = LOADADDR(.ewram_code13); 
			__ewram_code13_ewram_start__ = .; 
			*(.ewram_code13 .ewram_code13.*); 
			. = ALIGN(4); 
			__ewram_code13_ewram_end__ = .; 
		} 
		.ewram_code14 
		{ 
			__ewram_code14_rom_start__ = LOADADDR(.ewram_code14); 
			__ewram_code14_ewram_start__ = .; 
			*(.ewram_code14 .ewram_code14.*); 
			. = ALIGN(4); 
			__ewram_code14_ewram_end__ = .; 
		} 
		.ewram_code15 
		{ 
			__ewram_code15_rom_start__ = LOADADDR(.ewram_code15); 
			__ewram_code15_ewram_start__ = .; 
			*(.ewram_code15 .ewram_code15.*); 
			. = ALIGN(4); 
			__ewram_code15_ewram_end__ = .; 
		} 

	} >ewram AT >rom

	/* __ewram_code0_section_size = SIZEOF(.ewram_code0); */
		__ewram_code0_section_size = SIZEOF(.ewram_code0); 
		__ewram_code1_section_size = SIZEOF(.ewram_code1); 
		__ewram_code2_section_size = SIZEOF(.ewram_code2); 
		__ewram_code3_section_size = SIZEOF(.ewram_code3); 
		__ewram_code4_section_size = SIZEOF(.ewram_code4); 
		__ewram_code5_section_size = SIZEOF(.ewram_code5); 
		__ewram_code6_section_size = SIZEOF(.ewram_code6); 
		__ewram_code7_section_size = SIZEOF(.ewram_code7); 
		__ewram_code8_section_size = SIZEOF(.ewram_code8); 
		__ewram_code9_section_size = SIZEOF(.ewram_code9); 
		__ewram_code10_section_size = SIZEOF(.ewram_code10); 
		__ewram_code11_section_size = SIZEOF(.ewram_code11); 
		__ewram_code12_section_size = SIZEOF(.ewram_code12); 
		__ewram_code13_section_size = SIZEOF(.ewram_code13); 
		__ewram_code14_section_size = SIZEOF(.ewram_code14); 
		__ewram_code15_section_size = SIZEOF(.ewram_code15); 



	OVERLAY : NOCROSSREFS
	{
		/* Uninitialized (set to zero) variables that go into EWRAM */
		/*
		.bss0
		{
			__bss0_start__ = .;
			*(.bss0 .bss0.*)
			. = ALIGN(4);
			__bss0_end__ = .;
		}
		*/
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
		.bss8 
		{ 
			__bss8_start__ = .; 
			*(.bss8 .bss8.*) 
			. = ALIGN(4); 
			__bss8_end__ = .; 
		} 
		.bss9 
		{ 
			__bss9_start__ = .; 
			*(.bss9 .bss9.*) 
			. = ALIGN(4); 
			__bss9_end__ = .; 
		} 
		.bss10 
		{ 
			__bss10_start__ = .; 
			*(.bss10 .bss10.*) 
			. = ALIGN(4); 
			__bss10_end__ = .; 
		} 
		.bss11 
		{ 
			__bss11_start__ = .; 
			*(.bss11 .bss11.*) 
			. = ALIGN(4); 
			__bss11_end__ = .; 
		} 
		.bss12 
		{ 
			__bss12_start__ = .; 
			*(.bss12 .bss12.*) 
			. = ALIGN(4); 
			__bss12_end__ = .; 
		} 
		.bss13 
		{ 
			__bss13_start__ = .; 
			*(.bss13 .bss13.*) 
			. = ALIGN(4); 
			__bss13_end__ = .; 
		} 
		.bss14 
		{ 
			__bss14_start__ = .; 
			*(.bss14 .bss14.*) 
			. = ALIGN(4); 
			__bss14_end__ = .; 
		} 
		.bss15 
		{ 
			__bss15_start__ = .; 
			*(.bss15 .bss15.*) 
			. = ALIGN(4); 
			__bss15_end__ = .; 
		} 

	} >ewram

	/* __bss0_section_size = SIZEOF(.bss0); */
		__bss0_section_size = SIZEOF(.bss0); 
		__bss1_section_size = SIZEOF(.bss1); 
		__bss2_section_size = SIZEOF(.bss2); 
		__bss3_section_size = SIZEOF(.bss3); 
		__bss4_section_size = SIZEOF(.bss4); 
		__bss5_section_size = SIZEOF(.bss5); 
		__bss6_section_size = SIZEOF(.bss6); 
		__bss7_section_size = SIZEOF(.bss7); 
		__bss8_section_size = SIZEOF(.bss8); 
		__bss9_section_size = SIZEOF(.bss9); 
		__bss10_section_size = SIZEOF(.bss10); 
		__bss11_section_size = SIZEOF(.bss11); 
		__bss12_section_size = SIZEOF(.bss12); 
		__bss13_section_size = SIZEOF(.bss13); 
		__bss14_section_size = SIZEOF(.bss14); 
		__bss15_section_size = SIZEOF(.bss15); 



	/* 
	I figure I might as well have this, though it's probably not 
	needed.
	*/
	OVERLAY : NOCROSSREFS
	{
		/*
		.sram0
		{
			__sram0_start__ = .;
			*(.sram0 .sram0.*);

			. = ALIGN(4);
			__sram0_end__ = .;
		}
		*/
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
		.sram8 
		{ 
			__sram8_start__ = .; 
			*(.sram8 .sram8.*); 

			. = ALIGN(4); 
			__sram8_end__ = .; 
		} 
		.sram9 
		{ 
			__sram9_start__ = .; 
			*(.sram9 .sram9.*); 

			. = ALIGN(4); 
			__sram9_end__ = .; 
		} 
		.sram10 
		{ 
			__sram10_start__ = .; 
			*(.sram10 .sram10.*); 

			. = ALIGN(4); 
			__sram10_end__ = .; 
		} 
		.sram11 
		{ 
			__sram11_start__ = .; 
			*(.sram11 .sram11.*); 

			. = ALIGN(4); 
			__sram11_end__ = .; 
		} 
		.sram12 
		{ 
			__sram12_start__ = .; 
			*(.sram12 .sram12.*); 

			. = ALIGN(4); 
			__sram12_end__ = .; 
		} 
		.sram13 
		{ 
			__sram13_start__ = .; 
			*(.sram13 .sram13.*); 

			. = ALIGN(4); 
			__sram13_end__ = .; 
		} 
		.sram14 
		{ 
			__sram14_start__ = .; 
			*(.sram14 .sram14.*); 

			. = ALIGN(4); 
			__sram14_end__ = .; 
		} 
		.sram15 
		{ 
			__sram15_start__ = .; 
			*(.sram15 .sram15.*); 

			. = ALIGN(4); 
			__sram15_end__ = .; 
		} 

	} >sram

	/* __sram0_section_size = SIZEOF(.sram0); */
		__sram0_section_size = SIZEOF(.sram0); 
		__sram1_section_size = SIZEOF(.sram1); 
		__sram2_section_size = SIZEOF(.sram2); 
		__sram3_section_size = SIZEOF(.sram3); 
		__sram4_section_size = SIZEOF(.sram4); 
		__sram5_section_size = SIZEOF(.sram5); 
		__sram6_section_size = SIZEOF(.sram6); 
		__sram7_section_size = SIZEOF(.sram7); 
		__sram8_section_size = SIZEOF(.sram8); 
		__sram9_section_size = SIZEOF(.sram9); 
		__sram10_section_size = SIZEOF(.sram10); 
		__sram11_section_size = SIZEOF(.sram11); 
		__sram12_section_size = SIZEOF(.sram12); 
		__sram13_section_size = SIZEOF(.sram13); 
		__sram14_section_size = SIZEOF(.sram14); 
		__sram15_section_size = SIZEOF(.sram15); 


}

/*PROVIDE( _HEAP_START = 0x020200000 );

PROVIDE( _HEAP_END = 0x020300000 );*/

