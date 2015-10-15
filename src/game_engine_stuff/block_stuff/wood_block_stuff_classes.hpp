#ifndef wood_block_stuff_classes_hpp
#define wood_block_stuff_classes_hpp

class wood_block_stuff : public block_base_stuff
{
public:		// variables
	static const u32 metatile_number = 2;
	static const u32 palette_number = 0;
	static const u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number() __attribute__((_iwram_code));
	virtual const u32 get_palette_number() __attribute__((_iwram_code));
	virtual const u32 get_metatile_graphics_slot()
		__attribute__((_iwram_code));
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord ) __attribute__((_iwram_code));
	
} __attribute__((_align4));


class wood_block_with_bt_dud_stuff : public wood_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord ) __attribute__((_iwram_code));
} __attribute__((_align4));
class wood_block_with_st_waffle_stuff : public wood_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord ) __attribute__((_iwram_code));
} __attribute__((_align4));
class wood_block_with_st_muffin_stuff : public wood_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord ) __attribute__((_iwram_code));
} __attribute__((_align4));
class wood_block_with_st_fire_muffin_stuff : public wood_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord ) __attribute__((_iwram_code));
} __attribute__((_align4));
class wood_block_with_st_ice_muffin_stuff : public wood_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord ) __attribute__((_iwram_code));
} __attribute__((_align4));
class wood_block_with_st_chocolate_muffin_stuff : public wood_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord ) __attribute__((_iwram_code));
} __attribute__((_align4));


#endif		// wood_block_stuff_classes_hpp
