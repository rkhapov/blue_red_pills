cmd_/home/admin/blue_red_pills/lkm/lkm_example.ko := ld -r -m elf_x86_64 -z noexecstack --build-id=sha1  -T scripts/module.lds -o /home/admin/blue_red_pills/lkm/lkm_example.ko /home/admin/blue_red_pills/lkm/lkm_example.o /home/admin/blue_red_pills/lkm/lkm_example.mod.o;  true