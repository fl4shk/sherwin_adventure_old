#ifndef grass_and_dirt_block_stuff_classes_hpp
#define grass_and_dirt_block_stuff_classes_hpp


class grass_single_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 6;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));

class grass_top_left_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 7;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));
class grass_top_middle_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 8;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));
class grass_top_right_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 9;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));


class dirt_middle_left_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 10;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));
class dirt_middle_middle_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 11;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));
class dirt_middle_right_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 12;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
		__attribute__((_iwram_code));
} __attribute__((_align4));

class dirt_bottom_left_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 13;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));
class dirt_bottom_middle_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 14;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));
class dirt_bottom_right_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 15;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));

// Slopes
class grass_slope_135_degrees_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = num_pixels_per_block_row;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
	static constexpr u32 height_mask_size = 16;
	static const u32 height_mask[height_mask_size]; 
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));
class grass_slope_45_degrees_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 17;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
	static constexpr u32 height_mask_size = num_pixels_per_block_row;
	static const u32 height_mask[height_mask_size];
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));

class grass_in_slope_left_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 18;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));
class grass_in_slope_right_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 19;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const u32 get_metatile_number()
	{
		return metatile_number;
	}
	inline virtual const u32 get_palette_number()
	{
		return palette_number;
	}
	inline virtual const u32 get_metatile_graphics_slot()
	{
		return metatile_graphics_slot;
	}
} __attribute__((_align4));


#endif		// grass_and_dirt_block_stuff_classes_hpp
