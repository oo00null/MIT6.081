// Format of an ELF executable file

#define ELF_MAGIC 0x464C457FU  // "\x7FELF" in little endian

// File header
struct elfhdr {
  uint magic;  // must equal ELF_MAGIC
  uchar elf[12];
  ushort type;
  ushort machine;
  uint version;
  uint64 entry; //程序的入口地址
  uint64 phoff; //程序头表在文件中的偏移量。
  uint64 shoff; //程序头表在文件中的偏移量。
  uint flags;
  ushort ehsize;    //ELF头的大小（字节）
  ushort phentsize; //程序头表中每个表项的大小
  ushort phnum;     //程序头表中的表项数量
  ushort shentsize;
  ushort shnum;
  ushort shstrndx;
};

// Program section header
struct proghdr {
  uint32 type;
  uint32 flags;
  uint64 off; //程序段在文件中的偏移量
  uint64 vaddr;
  uint64 paddr;
  uint64 filesz;//程序段在文件中的大小
  uint64 memsz; //程序段在内存中的大小
  uint64 align;
};

// Values for Proghdr type
#define ELF_PROG_LOAD           1

// Flag bits for Proghdr flags
#define ELF_PROG_FLAG_EXEC      1
#define ELF_PROG_FLAG_WRITE     2
#define ELF_PROG_FLAG_READ      4
