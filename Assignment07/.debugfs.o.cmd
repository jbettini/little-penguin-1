savedcmd_/root/little-penguin-1/Assignment07/debugfs.o := ld -m elf_x86_64 -z noexecstack --no-warn-rwx-segments   -r -o /root/little-penguin-1/Assignment07/debugfs.o @/root/little-penguin-1/Assignment07/debugfs.mod  ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --ibt --orc --retpoline --rethunk --static-call --uaccess --prefix=16  --link  --module /root/little-penguin-1/Assignment07/debugfs.o

/root/little-penguin-1/Assignment07/debugfs.o: $(wildcard ./tools/objtool/objtool)
