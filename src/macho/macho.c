/**
 * 
 *     libhelper
 *     Copyright (C) 2019, @h3adsh0tzz
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#include "macho.h"


uint32_t macho_read_magic (unsigned char *buf, int offset)
{
    uint32_t magic = 0;
    memcpy (&magic, buf, sizeof(uint32_t));
    if (!magic) {
        g_print ("[*] Error: Could not read magic from Mach-O.\n");
        exit (0);
    }
    return magic;
}

mach_header_t *mach_header_load (unsigned char *buf)
{
    // Create a mach_header_t, and cast buf.
    mach_header_t *header = (mach_header_t *) buf;

    // Check that it was allocated correctly
    if (header->magic != MACH_MAGIC_64) {
        g_print ("[*] Error: File not 64bit Mach-O\n");
        exit (0);
    }

    // Return the header
    return header;
}

char *mach_header_read_cpu_type (cpu_type_t type)
{
    char *cpu_type = "";

    switch (type) {
        case CPU_TYPE_X86:
            cpu_type = "x86";
            break;
        case CPU_TYPE_X86_64:
            cpu_type = "x86_64";
            break;
        case CPU_TYPE_ARM:
            cpu_type = "arm";
            break;
        case CPU_TYPE_ARM64:
            cpu_type = "arm64";
            break;
        case CPU_TYPE_ARM64_32:
            cpu_type = "arm64_32";
            break;
        default:
            cpu_type = "unknown";
            break;
    }

    return cpu_type;
}

char *mach_header_read_file_type (uint32_t type)
{
    char *ret = "";

    switch (type) {
        case MACH_TYPE_OBJECT:
            ret = "Mach Object (MH_OBJECT)";
            break;
        case MACH_TYPE_EXECUTE:
            ret = "Mach Executable (MH_EXECUTE)";
            break;
        case MACH_TYPE_DYLIB:
            ret = "Mach Dynamic Library (MH_DYLIB)";
            break;
        default:
            ret = "Unknown";
            break;
    }
    return ret;
}

void mach_header_dump_test (mach_header_t *header)
{
    g_print ("==================\nMach-O Header Dump\n==================\n\n");

    g_print ("Magic: \t\t0x%x\n", header->magic);
    g_print ("CPU Type: \t%s\n", mach_header_read_cpu_type(header->cputype));
    g_print ("CPU Sub-Type: \t0x%x\n", header->cpusubtype);
    g_print ("File Type: \t%s\n", mach_header_read_file_type (header->filetype));
    g_print ("Load Commands: \t%d\n", header->ncmds);
    g_print ("LC Size: \t%d\n", header->sizeofcmds);
}