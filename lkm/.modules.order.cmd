cmd_/home/admin/blue_red_pills/lkm/modules.order := {   echo /home/admin/blue_red_pills/lkm/lkm_example.ko; :; } | awk '!x[$$0]++' - > /home/admin/blue_red_pills/lkm/modules.order
