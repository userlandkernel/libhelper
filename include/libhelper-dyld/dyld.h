//===------------------------------ dyld -----------------------------===//
//
//                          Libhelper DYLD Parser
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//
//  Copyright (C) 2019, Is This On?, @h3adsh0tzz
//  me@h3adsh0tzz.com.
//
//
//===------------------------------------------------------------------===//

#ifndef LIBHELPER_DYLD_H
#define LIBHELPER_DYLD_H

/**
 *                  === The Libhelper Project ===
 *                          Mach-O Parser
 *
 *  DYLD Parser aimed at being able to parse an iOS DYLD Shared Cache file
 *  and splitting it into induvidual libraries, like dsc_extractor but
 *  good. 
 * 
 *  ----------------
 *  Original Author:
 *      Harry Moulton, @h3adsh0tzz  -   me@h3adsh0tzz.com.
 *
 */

#include "libhelper/hslist.h"
#include "libhelper/strutils.h"


/***********************************************************************
* DYLD Shared Cache header.
***********************************************************************/

/**
 *  Header for the DYLD Shared Cache file found on iOS devices.
 * 
 */
struct dyld_cache_header {
    char		magic[16];				// e.g. "dyld_v0    i386"
	uint32_t	mappingOffset;			// file offset to first dyld_cache_mapping_info
	uint32_t	mappingCount;			// number of dyld_cache_mapping_info entries
	uint32_t	imagesOffset;			// file offset to first dyld_cache_image_info
	uint32_t	imagesCount;			// number of dyld_cache_image_info entries
	uint64_t	dyldBaseAddress;		// base address of dyld when cache was built
	uint64_t	codeSignatureOffset;	// file offset of code signature blob
	uint64_t	codeSignatureSize;		// size of code signature blob (zero means to end of file)
	uint64_t	slideInfoOffset;		// file offset of kernel slid info
	uint64_t	slideInfoSize;			// size of kernel slid info
	uint64_t	localSymbolsOffset;		// file offset of where local symbols are stored
	uint64_t	localSymbolsSize;		// size of local symbols information
	uint8_t		uuid[16];				// unique value for each shared cache file
	uint64_t	cacheType;				// 0 for development, 1 for production
	uint32_t	branchPoolsOffset;		// file offset to table of uint64_t pool addresses
	uint32_t	branchPoolsCount;	    // number of uint64_t entries
	uint64_t	accelerateInfoAddr;		// (unslid) address of optimization info
	uint64_t	accelerateInfoSize;		// size of optimization info
	uint64_t	imagesTextOffset;		// file offset to first dyld_cache_image_text_info
	uint64_t	imagesTextCount;		// number of dyld_cache_image_text_info entries   
};
typedef struct dyld_cache_header        dyld_cache_header_t;

dyld_cache_header_t *dyld_cache_header_create ();

#endif /* libhelper_dyld_h */