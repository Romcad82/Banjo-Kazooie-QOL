
def main():
    with open("asm/header.s", "r") as f:
        contents = f.readlines()

    contents.insert(0, '#include "config.h"\n\n')
    contents[11] = '.ascii INTERNAL_ROM_NAME /* Internal name */\n'
    contents.insert(14, '#ifdef EEPROM_16K\n.ascii "ED"            /* Cartridge ID */\n#else\n')
    contents.insert(16, '#endif\n')
    contents.insert(18, '#ifdef EEPROM_16K\n.byte 0x22             /* Version */\n#else\n')
    contents.insert(20, '#endif\n')

    with open("asm/header.s", "w") as f:
        contents = "".join(contents)
        f.write(contents)

if __name__ == '__main__':
    main()
