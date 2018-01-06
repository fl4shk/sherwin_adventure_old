// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#include "overlay_loader_stuff.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
#include "../general_utility_stuff/misc_defines.hpp"

//#include "extra_overlay_defines.hpp"

#define MAKE_OVERLAY_LIST(X) \
	X(0) X(1) X(2) X(3) X(4) X(5) X(6) X(7) \
	X(8) X(9) X(10) X(11) X(12) X(13) X(14) X(15)

MAKE_OVERLAY_LIST(_EXPOSE_EWRAM_OVERLAY);
MAKE_OVERLAY_LIST(_EXPOSE_IWRAM_OVERLAY);
MAKE_OVERLAY_LIST(_EXPOSE_BSS_OVERLAY);
MAKE_OVERLAY_LIST(_EXPOSE_IWRAM_BSS_OVERLAY);
MAKE_OVERLAY_LIST(_EXPOSE_SRAM_OVERLAY);
MAKE_OVERLAY_LIST(_EXPOSE_EWRAM_CODE_OVERLAY);
MAKE_OVERLAY_LIST(_EXPOSE_IWRAM_CODE_OVERLAY);


static constexpr size_t max_num_overlays = 16;

extern "C" 
{
#define X(num) (&_EWRAM_OVERLAY_SECTION_ROM_START(num)),
size_t * const __ewram_overlay_section_rom_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_EWRAM_OVERLAY_SECTION_EWRAM_START(num)),
size_t * const __ewram_overlay_section_ewram_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_EWRAM_OVERLAY_SECTION_END(num)),
size_t * const __ewram_overlay_section_end[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X


#define X(num) (&_IWRAM_OVERLAY_SECTION_ROM_START(num)),
size_t * const __iwram_overlay_section_rom_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_IWRAM_OVERLAY_SECTION_IWRAM_START(num)),
size_t * const __iwram_overlay_section_iwram_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_IWRAM_OVERLAY_SECTION_END(num)),
size_t * const __iwram_overlay_section_end[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X


#define X(num) (&_BSS_OVERLAY_SECTION_START(num)),
size_t * const __bss_overlay_section_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_BSS_OVERLAY_SECTION_END(num)),
size_t * const __bss_overlay_section_end[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X


#define X(num) (&_IWRAM_BSS_OVERLAY_SECTION_START(num)),
size_t * const __iwram_bss_overlay_section_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_IWRAM_BSS_OVERLAY_SECTION_END(num)),
size_t * const __iwram_bss_overlay_section_end[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X


#define X(num) (&_SRAM_OVERLAY_SECTION_START(num)),
size_t * const __sram_overlay_section_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_SRAM_OVERLAY_SECTION_END(num)),
size_t * const __sram_overlay_section_end[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X



#define X(num) (&_EWRAM_CODE_OVERLAY_SECTION_ROM_START(num)),
size_t * const __ewram_code_overlay_section_rom_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_EWRAM_CODE_OVERLAY_SECTION_EWRAM_START(num)),
size_t * const __ewram_code_overlay_section_ewram_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_EWRAM_CODE_OVERLAY_SECTION_END(num)),
size_t * const __ewram_code_overlay_section_end[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X


#define X(num) (&_IWRAM_CODE_OVERLAY_SECTION_ROM_START(num)),
size_t * const __iwram_code_overlay_section_rom_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_IWRAM_CODE_OVERLAY_SECTION_IWRAM_START(num)),
size_t * const __iwram_code_overlay_section_iwram_start[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

#define X(num) (&_IWRAM_CODE_OVERLAY_SECTION_END(num)),
size_t * const __iwram_code_overlay_section_end[]
	= {MAKE_OVERLAY_LIST(X) nullptr};
#undef X

}


namespace sherwin_adventure
{
namespace game_engine
{

void OverlayLoader::load(OverlayNum n_overlay_num)
{
	__overlay_num = n_overlay_num;
	//memcpy32(_TITLE_SCREEN_EWRAM_SECTION_EWRAM_START,
	//	_TITLE_SCREEN_EWRAM_SECTION_ROM_START,
	//	((size_t)_TITLE_SCREEN_EWRAM_SECTION_END
	//	- (size_t)_TITLE_SCREEN_EWRAM_SECTION_EWRAM_START));

	if ((overlay_num() >= OverlayNum::Lim)
		|| ((size_t)overlay_num() >= max_num_overlays))
	{
		//halt();
		err("OverlayLoader::load():  Eek!");
	}

	//thing_0();
	//thing_1();
	//thing_2();
	//thing_3();
	//thing_4();
	//thing_5();
	//thing_6();

	asm_comment("First thing");
	memcpy(__ewram_overlay_section_ewram_start
			[(size_t)overlay_num()],
		__ewram_overlay_section_rom_start
			[(size_t)overlay_num()],
		((size_t)__ewram_overlay_section_end
			[(size_t)overlay_num()]
		- (size_t)__ewram_overlay_section_ewram_start
			[(size_t)overlay_num()]));

	asm_comment("Second thing");
	memcpy(__iwram_overlay_section_iwram_start
			[(size_t)overlay_num()],
		__iwram_overlay_section_rom_start
			[(size_t)overlay_num()],
		((size_t)__iwram_overlay_section_end
			[(size_t)overlay_num()]
		- (size_t)__iwram_overlay_section_iwram_start
			[(size_t)overlay_num()]));

	asm_comment("Third thing");
	memset(__bss_overlay_section_start
			[(size_t)overlay_num()], 
		0,
		((size_t)__bss_overlay_section_end
			[(size_t)overlay_num()]
		- (size_t)__bss_overlay_section_start
			[(size_t)overlay_num()]));

	asm_comment("Fourth thing");
	memset(__iwram_bss_overlay_section_start
			[(size_t)overlay_num()], 
		0,
		((size_t)__iwram_bss_overlay_section_end
			[(size_t)overlay_num()]
		- (size_t)__iwram_bss_overlay_section_start
			[(size_t)overlay_num()]));

	asm_comment("Fifth thing");
	memfill8(__sram_overlay_section_start
			[(size_t)overlay_num()], 
		0,
		((size_t)__sram_overlay_section_end
			[(size_t)overlay_num()]
		- (size_t)__sram_overlay_section_start
			[(size_t)overlay_num()]));

	asm_comment("Sixth thing");
	memcpy(__ewram_code_overlay_section_ewram_start
			[(size_t)overlay_num()],
		__ewram_code_overlay_section_rom_start
			[(size_t)overlay_num()],
		((size_t)__ewram_code_overlay_section_end
			[(size_t)overlay_num()]
		- (size_t)__ewram_code_overlay_section_ewram_start
			[(size_t)overlay_num()]));

	asm_comment("Seventh thing");
	memcpy(__iwram_code_overlay_section_iwram_start
			[(size_t)overlay_num()],
		__iwram_code_overlay_section_rom_start
			[(size_t)overlay_num()],
		((size_t)__iwram_code_overlay_section_end
			[(size_t)overlay_num()]
		- (size_t)__iwram_code_overlay_section_iwram_start
			[(size_t)overlay_num()]));

}


//void OverlayLoader::thing_0()
//{
//	asm_comment("First thing");
//	memcpy(__ewram_overlay_section_ewram_start
//			[(size_t)overlay_num()],
//		__ewram_overlay_section_rom_start
//			[(size_t)overlay_num()],
//		((size_t)__ewram_overlay_section_end
//			[(size_t)overlay_num()]
//		- (size_t)__ewram_overlay_section_ewram_start
//			[(size_t)overlay_num()]));
//}
//void OverlayLoader::thing_1()
//{
//	asm_comment("Second thing");
//	memcpy(__iwram_overlay_section_iwram_start
//			[(size_t)overlay_num()],
//		__iwram_overlay_section_rom_start
//			[(size_t)overlay_num()],
//		((size_t)__iwram_overlay_section_end
//			[(size_t)overlay_num()]
//		- (size_t)__iwram_overlay_section_iwram_start
//			[(size_t)overlay_num()]));
//}
//void OverlayLoader::thing_2()
//{
//	asm_comment("Third thing");
//	memset(__bss_overlay_section_start
//			[(size_t)overlay_num()], 
//		0,
//		((size_t)__bss_overlay_section_end
//			[(size_t)overlay_num()]
//		- (size_t)__bss_overlay_section_start
//			[(size_t)overlay_num()]));
//}
//void OverlayLoader::thing_3()
//{
//	asm_comment("Fourth thing");
//	memset(__iwram_bss_overlay_section_start
//			[(size_t)overlay_num()], 
//		0,
//		((size_t)__iwram_bss_overlay_section_end
//			[(size_t)overlay_num()]
//		- (size_t)__iwram_bss_overlay_section_start
//			[(size_t)overlay_num()]));
//}
//void OverlayLoader::thing_4()
//{
//	asm_comment("Fifth thing");
//	memfill8(__sram_overlay_section_start
//			[(size_t)overlay_num()], 
//		0,
//		((size_t)__sram_overlay_section_end
//			[(size_t)overlay_num()]
//		- (size_t)__sram_overlay_section_start
//			[(size_t)overlay_num()]));
//}
//void OverlayLoader::thing_5()
//{
//	asm_comment("Sixth thing");
//	memcpy(__ewram_code_overlay_section_ewram_start
//			[(size_t)overlay_num()],
//		__ewram_code_overlay_section_rom_start
//			[(size_t)overlay_num()],
//		((size_t)__ewram_code_overlay_section_end
//			[(size_t)overlay_num()]
//		- (size_t)__ewram_code_overlay_section_ewram_start
//			[(size_t)overlay_num()]));
//}
//void OverlayLoader::thing_6()
//{
//	asm_comment("Seventh thing");
//	memcpy(__iwram_code_overlay_section_iwram_start
//			[(size_t)overlay_num()],
//		__iwram_code_overlay_section_rom_start
//			[(size_t)overlay_num()],
//		((size_t)__iwram_code_overlay_section_end
//			[(size_t)overlay_num()]
//		- (size_t)__iwram_code_overlay_section_iwram_start
//			[(size_t)overlay_num()]));
//}

}
}
