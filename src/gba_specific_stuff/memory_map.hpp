#ifndef memory_map_hpp
#define memory_map_hpp

#include "../game_engine_stuff/misc_types.hpp"


#define mem_ewram 0x02000000
#define mem_iwram 0x03000000
#define mem_sram 0x0e000000


#define mem_io 0x04000000
#define mem_pal_ram 0x05000000
#define mem_vram 0x06000000
#define mem_oam 0x07000000


#define mem_vram_page_0 0x06000000
#define mem_vram_page_1 0x0600a000



// The start of BG Palette RAM
#define mem_bg_pal 0x05000000

// The start of OBJ Palette RAM
#define mem_obj_pal 0x05000200




#endif		// memory_map_hpp
