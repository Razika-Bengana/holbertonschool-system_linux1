#include "header.h"

/**
 * get_section_header_str_table - reads ELF and stores section header string table in FileInfo
 *
 * @fileInfo: struct containing file data and info for error printing
 * Return: 1 on failure, 0 on success
 */

int get_section_header_str_table(FileInfo *fileInfo)
{
    Elf64_Shdr st_shdr;
    char *buff = NULL;

    st_shdr = fileInfo->sectionHeaders[fileInfo->header.e_shstrndx];

    rewind(fileInfo->stream);
    if (fseek(fileInfo->stream, st_shdr.sh_offset, SEEK_SET) == -1)
        return 1;

    buff = malloc(sizeof(char) * st_shdr.sh_size);
    if (!buff)
        return 1;

    if (fread(buff, 1, st_shdr.sh_size, fileInfo->stream) != st_shdr.sh_size)
        return 1;

    fileInfo->sectionHeaderStringTable = buff;

    return 0;
}
