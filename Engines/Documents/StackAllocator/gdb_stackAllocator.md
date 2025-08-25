
```sh
Breakpoint 1, UserPlayLayer::onAttach (this=0x555555c45300) at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:36
warning: Source file is more recent than executable.
36			mAllocator->memClear();
(gdb) set $i = 0
(gdb) while $i < 5
 >    printf "i=%d, Addr=%p, ID=%d, Name=%s\n", $i, robotObjects[$i], robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >    set $i = $i + 1
 >end
i=0, Addr=0x7fffebff0018, ID=0, Name=RobotObject: 0
i=1, Addr=0x7fffebff0048, ID=1, Name=RobotObject: 1
i=2, Addr=0x7fffebff0078, ID=2, Name=RobotObject: 2
i=3, Addr=0x7fffebff00a8, ID=3, Name=RobotObject: 3
i=4, Addr=0x7fffebff00d8, ID=4, Name=RobotObject: 4
(gdb) c
Continuing.

Breakpoint 2, UserPlayLayer::onAttach (this=0x555555c45300) at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:46
46			mAllocator->memClear();

set $i = 0
while $i < 10
printf "i=%d, Addr=%p, ID=%d, Name=%s\n", $i, robotObjects[$i], robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
set $i = $i + 1
end
i=0, Addr=0x7fffebff0018, ID=10000, Name=RobotObject: 0
i=1, Addr=0x7fffebff0048, ID=10001, Name=RobotObject: 1
i=2, Addr=0x7fffebff0078, ID=10002, Name=RobotObject: 2
i=3, Addr=0x7fffebff00a8, ID=10003, Name=RobotObject: 3
i=4, Addr=0x7fffebff00d8, ID=10004, Name=RobotObject: 4

```

Sizeof object
```sh
0x7fffebff0048 - 0x7fffebff0018 = 0x30 (48 decimal) byte.
```


