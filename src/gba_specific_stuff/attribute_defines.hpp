#ifndef attribute_defines_hpp
#define attribute_defines_hpp


/* ---- #defines for Sections ---- */

// Example:  __attribute__((_ewram))
// Another example:  __attribute__(( _ewram, _align4 ))

// #defines for putting INITIAILZED stuff in EWRAM and IWRAM
#define _ewram section(".data")
#define _iwram section(".iwram_data")

// #defines for UNITIALIZED global variables that go into EWRAM, IWRAM,
// and SRAM
#define _bss section(".bss")
#define _iwram_bss section(".iwram_bss")
#define _sram section(".sram")


// #defines for putting stuff in the code (sections for EWRAM and IWRAM
#define _ewram_code section(".ewram_code")
#define _iwram_code section(".iwram_code")

/* ---- End of #defines for Sections ---- */


// A #define for aligning structs/classes
#define _align4 aligned(4)


// A #define for making sure that structs/classes have the exact size of
// all their members combined (USE WITH CAUTION)
#define _packed packed



#endif		// attribute_defines_hpp
