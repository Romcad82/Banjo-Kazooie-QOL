
def main():
    with open("asm/header.s", "r") as f:
        contents = f.readlines()

    contents.insert(0,  '#include "config.h"\n\n')
    contents.insert(11, '#ifdef INTERNAL_ROM_NAME\n.ascii INTERNAL_ROM_NAME /* Internal name */\n#else\n')
    contents.insert(13, '#endif\n')
    contents.insert(16, '#if defined(SAVE_FILE_DATA_SIZE) && (SAVE_FILE_DATA_SIZE >= 0x78)\n.ascii "ED"            /* Cartridge ID */\n#else\n')
    contents.insert(18, '#endif\n')
    contents.insert(20, '#if defined(SAVE_FILE_DATA_SIZE) && (SAVE_FILE_DATA_SIZE >= 0x78)\n.byte 0x22             /* Version */\n#else\n')
    contents.insert(22, '#endif\n')

    with open("asm/header.s", "w") as f:
        contents = "".join(contents)
        f.write(contents)

if __name__ == '__main__':
    main()
