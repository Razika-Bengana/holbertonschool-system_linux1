#include "header.h"

int getSecHeaders(FILE *file, FileInfo *fileInfo)
{
    if (fileInfo->header.e_shoff)
    {
        if (fileInfo->is32bit)
            return get32bitSecHeaders(file, fileInfo);
        else
            return get64bitSecHeaders(file, fileInfo);
    }

    return 0;
}

int get64bitSecHeaders(FILE *file, FileInfo *fileInfo)
{
    Elf64_Shdr *s_headers = NULL;
    int i;

    s_headers = malloc(sizeof(Elf64_Shdr) * fileInfo->header.e_shnum);
    if (!s_headers)
        return 1;

    if (fseek(file, fileInfo->header.e_shoff, SEEK_SET) == -1)
        return 1;

    if (fread(s_headers, sizeof(Elf64_Shdr), fileInfo->header.e_shnum, file) != fileInfo->header.e_shnum)
        return 1;

    if (fileInfo->isBigEndian)
    {
        for (i = 0; i < fileInfo->header.e_shnum; i++)
            bswapElf64_Shdr(&s_headers[i]);
    }

    fileInfo->sectionHeaders = s_headers;

    return 0;
}

int get32bitSecHeaders(FILE *file, FileInfo *fileInfo)
{
    Elf32_Shdr *s_headers32 = NULL;
    Elf64_Shdr *s_headers64 = NULL;
    int i;

    s_headers32 = malloc(sizeof(Elf32_Shdr) * fileInfo->header.e_shnum);
    s_headers64 = malloc(sizeof(Elf64_Shdr) * fileInfo->header.e_shnum);
    if (!s_headers32 || !s_headers64)
        return 1;

    if (fseek(file, fileInfo->header.e_shoff, SEEK_SET) == -1)
        return 1;

    if (fread(s_headers32, sizeof(Elf32_Shdr), fileInfo->header.e_shnum, file) != fileInfo->header.e_shnum)
        return 1;

    if (fileInfo->isBigEndian)
    {
        for (i = 0; i < fileInfo->header.e_shnum; i++)
            bswapElf32_Shdr(&s_headers32[i]);
    }

    for (i = 0; i < fileInfo->header.e_shnum; i++)
    {
        Elf32_Shdr *curr32 = &s_headers32[i];
        Elf64_Shdr *curr64 = &s_headers64[i];

        curr64->sh_name = (Elf64_Word)curr32->sh_name;
        curr64->sh_type = (Elf64_Word)curr32->sh_type;
        curr64->sh_flags = (Elf64_Xword)curr32->sh_flags;
        curr64->sh_addr = (Elf64_Addr)curr32->sh_addr;
        curr64->sh_offset = (Elf64_Off)curr32->sh_offset;
        curr64->sh_size = (Elf64_Xword)curr32->sh_size;
        curr64->sh_link = (Elf64_Word)curr32->sh_link;
        curr64->sh_info = (Elf64_Word)curr32->sh_info;
        curr64->sh_addralign = (Elf64_Xword)curr32->sh_addralign;
        curr64->sh_entsize = (Elf64_Xword)curr32->sh_entsize;
    }

    free(s_headers32);
    fileInfo->sectionHeaders = s_headers64;

    return 0;
}

void bswapElf64_Shdr(Elf64_Shdr *shdr64)
{
    shdr64->sh_name = __builtin_bswap32(shdr64->sh_name);
    shdr64->sh_type = __builtin_bswap32(shdr64->sh_type);
    shdr64->sh_flags = __builtin_bswap64(shdr64->sh_flags);
    shdr64->sh_addr = __builtin_bswap64(shdr64->sh_addr);
    shdr64->sh_offset = __builtin_bswap64(shdr64->sh_offset);
    shdr64->sh_size = __builtin_bswap64(shdr64->sh_size);
    shdr64->sh_link = __builtin_bswap32(shdr64->sh_link);
    shdr64->sh_info = __builtin_bswap32(shdr64->sh_info);
    shdr64->sh_addralign = __builtin_bswap64(shdr64->sh_addralign);
    shdr64->sh_entsize = __builtin_bswap64(shdr64->sh_entsize);
}

void bswapElf32_Shdr(Elf32_Shdr *shdr32)
{
    shdr32->sh_name = __builtin_bswap32(shdr32->sh_name);
    shdr32->sh_type = __builtin_bswap32(shdr32->sh_type);
    shdr32->sh_flags = __builtin_bswap32(shdr32->sh_flags);
    shdr32->sh_addr = __builtin_bswap32(shdr32->sh_addr);
    shdr32->sh_offset = __builtin_bswap32(shdr32->sh_offset);
    shdr32->sh_size = __builtin_bswap32(shdr32->sh_size);
    shdr32->sh_link = __builtin_bswap32(shdr32->sh_link);
    shdr32->sh_info = __builtin_bswap32(shdr32->sh_info);
    shdr32->sh_addralign = __builtin_bswap32(shdr32->sh_addralign);
    shdr32->sh_entsize = __builtin_bswap32(shdr32->sh_entsize);
}
