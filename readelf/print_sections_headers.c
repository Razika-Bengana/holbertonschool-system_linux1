#include "header.h"

int printSecHeaders(FileInfo *fileInfo)
{
    uint64_t i;
    char *sh_fmt = NULL;
    Elf64_Shdr *curr = NULL;

    /* when to use "\nThere are no sections to group in this file.\n"? */
    switch (fileInfo->header.e_shnum)
    {
    case 0:
        printf("\nThere are no sections in this file.\n");
        return 0;
    case 1:
        printf("There is %d section header, starting at offset 0x%lx:\n",
               fileInfo->header.e_shnum, fileInfo->header.e_shoff);
        break;
    default:
        printf("There are %d section headers, starting at offset 0x%lx:\n",
               fileInfo->header.e_shnum, fileInfo->header.e_shoff);
        break;
    }

    printf("\nSection Header%s:\n", fileInfo->header.e_shnum > 1 ? "s" : "");

    if (fileInfo->is32bit)
    {
        printf("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");
        sh_fmt = "  [%2i] %-17s %-15s %08x %06x %06x %02lx %3s %2u %3u %2lu\n";
    }
    else
    {
        printf("  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n");
        sh_fmt = "  [%2i] %-17s %-15s %016x %06x %06x %02lx %3s %2u %3u %2lu\n";
    }

    for (i = 0; i < fileInfo->header.e_shnum; i++)
    {
        curr = &(fileInfo->sectionHeaders[i]);
        printf(sh_fmt, i,
               fileInfo->sectionHeaderStringTable + curr->sh_name,
               getSecType(curr->sh_type),
               curr->sh_addr,
               curr->sh_offset,
               curr->sh_size,
               curr->sh_entsize,
               getSecFlags(curr->sh_flags),
               curr->sh_link,
               curr->sh_info,
               curr->sh_addralign);
    }

    printf("Key to Flags:\n");
    if (fileInfo->header.e_machine == EM_X86_64)
        printf("  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)\n");
    else
        printf("  W (write), A (alloc), X (execute), M (merge), S (strings)\n");
    printf("  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n"
           "  O (extra OS processing required) o (OS specific), p (processor specific)\n");

    return 0;
}
