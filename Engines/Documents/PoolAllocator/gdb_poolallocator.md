```sh
Breakpoint 1, UserPlayLayer::onAttach (this=0x555555c442c0)
    at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:36
36			LOG_TRACE("Free memory");
(gdb) set $i = 0
(gdb) while $i < 10
 >printf "i=%d, Addr=%p, ID=%d, Name=%s\n", $i, robotObjects[$i], robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >set $i = $i + 1
 >end
i=0, Addr=0x7ffff3feffe0, ID=0, Name=RobotObject: 0
i=1, Addr=0x7ffff3feffb8, ID=1, Name=RobotObject: 1
i=2, Addr=0x7ffff3feff90, ID=2, Name=RobotObject: 2
i=3, Addr=0x7ffff3feff68, ID=3, Name=RobotObject: 3
i=4, Addr=0x7ffff3feff40, ID=4, Name=RobotObject: 4
i=5, Addr=0x7ffff3feff18, ID=5, Name=RobotObject: 5
i=6, Addr=0x7ffff3fefef0, ID=6, Name=RobotObject: 6
i=7, Addr=0x7ffff3fefec8, ID=7, Name=RobotObject: 7
i=8, Addr=0x7ffff3fefea0, ID=8, Name=RobotObject: 8
i=9, Addr=0x7ffff3fefe78, ID=9, Name=RobotObject: 9
(gdb) c
Continuing.
[21:43:55] [onAttach:36] [Client] [Thread:13144] Free memory

Breakpoint 2, UserPlayLayer::onAttach (this=0x555555c442c0)
    at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:37
37			mAllocator->memFree(robotObjects[1]);
(gdb) set $i = 0
(gdb) while $i < 10
 >printf "i=%d, Addr=%p, ID=%d, Name=%s\n", $i, robotObjects[$i], robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >set $i = $i + 1
 >end
i=0, Addr=0x7ffff3feffe0, ID=0, Name=RobotObject: 0
i=1, Addr=0x7ffff3feffb8, ID=1, Name=RobotObject: 1
i=2, Addr=0x7ffff3feff90, ID=2, Name=RobotObject: 2
i=3, Addr=0x7ffff3feff68, ID=3, Name=RobotObject: 3
i=4, Addr=0x7ffff3feff40, ID=4, Name=RobotObject: 4
i=5, Addr=0x7ffff3feff18, ID=5, Name=RobotObject: 5
i=6, Addr=0x7ffff3fefef0, ID=6, Name=RobotObject: 6
i=7, Addr=0x7ffff3fefec8, ID=7, Name=RobotObject: 7
i=8, Addr=0x7ffff3fefea0, ID=8, Name=RobotObject: 8
i=9, Addr=0x7ffff3fefe78, ID=9, Name=RobotObject: 9
(gdb) c
Continuing.

Breakpoint 3, UserPlayLayer::onAttach (this=0x555555c442c0)
    at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:38
38			mAllocator->memFree(robotObjects[2]);
(gdb) set $i = 0
(gdb) while $i < 10
 >printf "i=%d, Addr=%p, ID=%d, Name=%s\n", $i, robotObjects[$i], robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >set $i = $i + 1
 >end
i=0, Addr=0x7ffff3feffe0, ID=0, Name=RobotObject: 0
i=1, Addr=0x7ffff3feffb8, ID=-201392560, Name=RobotObject: 1
i=2, Addr=0x7ffff3feff90, ID=2, Name=RobotObject: 2
i=3, Addr=0x7ffff3feff68, ID=3, Name=RobotObject: 3
i=4, Addr=0x7ffff3feff40, ID=4, Name=RobotObject: 4
i=5, Addr=0x7ffff3feff18, ID=5, Name=RobotObject: 5
i=6, Addr=0x7ffff3fefef0, ID=6, Name=RobotObject: 6
i=7, Addr=0x7ffff3fefec8, ID=7, Name=RobotObject: 7
i=8, Addr=0x7ffff3fefea0, ID=8, Name=RobotObject: 8
i=9, Addr=0x7ffff3fefe78, ID=9, Name=RobotObject: 9
(gdb) c
Continuing.

Breakpoint 4, UserPlayLayer::onAttach (this=0x555555c442c0)
    at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:40
40			void *memory = mAllocator->allocateChunk();
(gdb) set $i = 0
(gdb) while $i < 10
 >printf "i=%d, Addr=%p, ID=%d, Name=%s\n", $i, robotObjects[$i], robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >set $i = $i + 1
 >end
i=0, Addr=0x7ffff3feffe0, ID=0, Name=RobotObject: 0
i=1, Addr=0x7ffff3feffb8, ID=-201392560, Name=RobotObject: 1
i=2, Addr=0x7ffff3feff90, ID=-201392200, Name=RobotObject: 2
i=3, Addr=0x7ffff3feff68, ID=3, Name=RobotObject: 3
i=4, Addr=0x7ffff3feff40, ID=4, Name=RobotObject: 4
i=5, Addr=0x7ffff3feff18, ID=5, Name=RobotObject: 5
i=6, Addr=0x7ffff3fefef0, ID=6, Name=RobotObject: 6
i=7, Addr=0x7ffff3fefec8, ID=7, Name=RobotObject: 7
i=8, Addr=0x7ffff3fefea0, ID=8, Name=RobotObject: 8
i=9, Addr=0x7ffff3fefe78, ID=9, Name=RobotObject: 9
(gdb) c
Continuing.

Breakpoint 5, UserPlayLayer::onAttach (this=0x555555c442c0)
    at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:45
45			memory = mAllocator->allocateChunk();
(gdb) set $i = 0
(gdb) while $i < 10
 >printf "i=%d, Addr=%p, ID=%d, Name=%s\n", $i, robotObjects[$i], robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >set $i = $i + 1
 >end
i=0, Addr=0x7ffff3feffe0, ID=0, Name=RobotObject: 0
i=1, Addr=0x7ffff3feffb8, ID=-201392560, Name=RobotObject: 1
i=2, Addr=0x7ffff3feff90, ID=11, Name=RobotObject: 11
i=3, Addr=0x7ffff3feff68, ID=3, Name=RobotObject: 3
i=4, Addr=0x7ffff3feff40, ID=4, Name=RobotObject: 4
i=5, Addr=0x7ffff3feff18, ID=5, Name=RobotObject: 5
i=6, Addr=0x7ffff3fefef0, ID=6, Name=RobotObject: 6
i=7, Addr=0x7ffff3fefec8, ID=7, Name=RobotObject: 7
i=8, Addr=0x7ffff3fefea0, ID=8, Name=RobotObject: 8
i=9, Addr=0x7ffff3fefe78, ID=9, Name=RobotObject: 9
(gdb) c
Continuing.

Breakpoint 6, UserPlayLayer::onAttach (this=0x555555c442c0)
    at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:50
50			robotObjects.clear();
(gdb) set $i = 0
(gdb) while $i < 10
 >printf "i=%d, Addr=%p, ID=%d, Name=%s\n", $i, robotObjects[$i], robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >set $i = $i + 1
 >end
i=0, Addr=0x7ffff3feffe0, ID=0, Name=RobotObject: 0
i=1, Addr=0x7ffff3feffb8, ID=12, Name=RobotObject: 12
i=2, Addr=0x7ffff3feff90, ID=11, Name=RobotObject: 11
i=3, Addr=0x7ffff3feff68, ID=3, Name=RobotObject: 3
i=4, Addr=0x7ffff3feff40, ID=4, Name=RobotObject: 4
i=5, Addr=0x7ffff3feff18, ID=5, Name=RobotObject: 5
i=6, Addr=0x7ffff3fefef0, ID=6, Name=RobotObject: 6
i=7, Addr=0x7ffff3fefec8, ID=7, Name=RobotObject: 7
i=8, Addr=0x7ffff3fefea0, ID=8, Name=RobotObject: 8
i=9, Addr=0x7ffff3fefe78, ID=9, Name=RobotObject: 9
(gdb) c
Continuing.

Breakpoint 7, UserPlayLayer::onAttach (this=0x555555c442c0)
    at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:61
61		}
(gdb) set $i = 0
(gdb) while $i < 10
 >printf "i=%d, Addr=%p, ID=%d, Name=%s\n", $i, robotObjects[$i], robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >set $i = $i + 1
 >end
i=0, Addr=0x55555572e0e0, ID=1433285440, Name=
i=1, Addr=0x5555556c9010, ID=327684, Name=Cannot access memory at address 0x3000000000001



```