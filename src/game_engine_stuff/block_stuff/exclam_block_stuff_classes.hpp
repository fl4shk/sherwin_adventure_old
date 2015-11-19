#ifndef exclam_block_stuff_classes_hpp
#define exclam_block_stuff_classes_hpp

class exclam_block_stuff : public block_base_stuff
{
public:		// enums
	enum persistent_data_state { is_exclam, is_bt_dud } 
		__attribute__((_align4));
	
public:		// variables
	static const u32 metatile_number = 4;
	static const u32 palette_number = 0;
	static const u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number() __attribute__((_iwram_code));
	virtual const u32 get_palette_number() __attribute__((_iwram_code));
	virtual const u32 get_metatile_graphics_slot()
		__attribute__((_iwram_code));
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord ) __attribute__((_iwram_code));
	
	virtual void finish_initializing_using_persistent_data
		( block& the_block ) __attribute__((_iwram_code));
	
} __attribute__((_align4));

#endif		// exclam_block_stuff_classes_hpp
