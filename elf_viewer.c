#include "stdio.h"
#include "elf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
	printf("%s\n", argv[0]);
	
	Elf32_Ehdr elf_hdr;

	int32_t ret_val = open(argv[0], O_RDONLY);
	
	if (ret_val < 0) {
	    perror("");
	    return -1;
	}
	
	int file_des = ret_val;
	
	ret_val = read(file_des, &elf_hdr, sizeof(elf_hdr));
	
	if (ret_val < 0) {
	    perror("");
	    return -2;
	}
	
	printf("e_type: 0x%08X\n", elf_hdr.e_type);
	printf("e_machine: 0x%08X\n", elf_hdr.e_machine);
	printf("e_version: 0x%08X\n", elf_hdr.e_version);
	printf("e_entry: 0x%08X\n", elf_hdr.e_entry);
	printf("e_phoff: 0x%08X\n", elf_hdr.e_phoff);
	printf("e_shoff: 0x%08X\n", elf_hdr.e_shoff);
	printf("e_flags: 0x%08X\n", elf_hdr.e_flags);
	printf("e_ehsize: 0x%08X\n", elf_hdr.e_ehsize);
	printf("e_phentsize: 0x%08X\n", elf_hdr.e_phentsize);
	printf("e_phnum: 0x%08X\n", elf_hdr.e_phnum);
	printf("e_shentsize: 0x%08X\n", elf_hdr.e_shentsize);
	printf("e_shnum: 0x%08X\n", elf_hdr.e_shnum);
	printf("e_shstrndx: 0x%08X\n", elf_hdr.e_shstrndx);
	printf("###\n");

	lseek(file_des, elf_hdr.e_phoff, SEEK_SET);
	int32_t i = 0;
	Elf32_Phdr p_hdr;
	for (; i < elf_hdr.e_phnum; ++i) {
/*	for (; i < 3; ++i) { */
	    lseek(file_des, elf_hdr.e_phoff + i * elf_hdr.e_phentsize, SEEK_SET);
	    ret_val = read(file_des, &p_hdr, sizeof(p_hdr));
	    
	    if (ret_val < 0) {
		perror("");
		return -2;
	    }
	    printf("p_type 0x%08X\n", p_hdr.p_type);
	    printf("p_offset 0x%08X\n", p_hdr.p_offset);
	    printf("p_vaddr 0x%08X\n", p_hdr.p_vaddr);
	    printf("p_paddr 0x%08X\n", p_hdr.p_paddr);
	    printf("p_filesz 0x%08X\n", p_hdr.p_filesz);
	    printf("p_memsz 0x%08X\n", p_hdr.p_memsz);
	    printf("p_flags 0x%08X\n", p_hdr.p_flags);
	    printf("p_align 0x%08X\n", p_hdr.p_align);
	    printf("###\n");
	}
	close(ret_val);
	return 0;
}
