### print adress memory (HEX)
p *robotObjects._M_impl._M_start@15

### result: ##################################################################

Breakpoint 1, UserPlayLayer::onAttach (this=0x555555c44200) at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:37
37			robotObjects.clear();
(gdb) p *robotObjects._M_impl._M_start@15
$1 = {0x7fffebff0010, 0x7fffebff0038, 0x7fffebff0060, 0x7fffebff0088, 0x7fffebff00b0, 0x7fffebff00d8, 0x7fffebff0100, 0x7fffebff0128, 0x7fffebff0150, 
  0x7fffebff0178, 0x7fffebff01a0, 0x7fffebff01c8, 0x7fffebff01f0, 0x7fffebff0218, 0x7fffebff0240}

Breakpoint 2, UserPlayLayer::onAttach (this=0x555555c44200) at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:47
47			robotObjects.clear();
(gdb) p *robotObjects._M_impl._M_start@15
$5 = {0x7fffebff0010, 0x7fffebff0038, 0x7fffebff0060, 0x7fffebff0088, 0x7fffebff00b0, 0x7fffebff00d8, 0x7fffebff0100, 0x7fffebff0128, 0x7fffebff0150, 
  0x7fffebff0178, 0x7fffebff01a0, 0x7fffebff01c8, 0x7fffebff01f0, 0x7fffebff0218, 0x7fffebff0240}

set $i = 0
while $i < 5
    printf "i=%d, ID=%d, Name=%s\n", $i, robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
    set $i = $i + 1
end
##################################################################

### result: ##################################################################
Reading symbols from build/bin/ViRobot...
(gdb) b UI_ViRobotLayer.h:37
Breakpoint 1 at 0x22cdd: file /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h, line 37.
(gdb) b UI_ViRobotLayer.h:47
Breakpoint 2 at 0x22e49: file /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h, line 47.
(gdb) run
Starting program: /home/devh/Build_EmbSys/Engines/build/bin/ViRobot 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
----- Start CreateApplication -----
[19:39:49] [GLFWPlatformWindow:11] [ViSolEngine] [Thread:18881] Call constructure GLFW
[19:39:49] [LayerStack:7] [ViSolEngine] [Thread:18881] Create layer stack
[19:39:49] [ViRobot:9] [Client] [Thread:18881] ViRobot client constructor init
[19:39:49] [main:10] [Client] [Thread:18881] After Create Application
[19:39:49] [init:25] [ViSolEngine] [Thread:18881] GLFW Init success
[19:39:49] [init:38] [ViSolEngine] [Thread:18881] Window created success
[19:39:49] [init:106] [ViSolEngine] [Thread:18881] Glad load success
[19:39:49] [addEventListener:25] [ViSolEngine] [Thread:18881] Create event type: N11ViSolEngine18WindowResizedEventE - with ID: 10335306245377322741 
[19:39:49] [addEventListener:25] [ViSolEngine] [Thread:18881] Create event type: N11ViSolEngine15KeyPressedEventE - with ID: 10858488873949338736 
[19:39:49] [addEventListener:25] [ViSolEngine] [Thread:18881] Create event type: N11ViSolEngine12KeyHeldEventE - with ID: 5731208569850014587 
[19:39:49] [addEventListener:25] [ViSolEngine] [Thread:18881] Create event type: N11ViSolEngine16KeyReleasedEventE - with ID: 4312422859198956200 
[19:39:49] [addEventListener:25] [ViSolEngine] [Thread:18881] Create event type: N11ViSolEngine15MouseMovedEventE - with ID: 16300746582389347028 
[19:39:49] [addEventListener:25] [ViSolEngine] [Thread:18881] Create event type: N11ViSolEngine18MouseScrolledEventE - with ID: 17325097712926797971 
[19:39:49] [addEventListener:25] [ViSolEngine] [Thread:18881] Create event type: N11ViSolEngine23MouseButtonPressedEventE - with ID: 5216910053759682737 
[19:39:49] [addEventListener:25] [ViSolEngine] [Thread:18881] Create event type: N11ViSolEngine20MouseButtonHeldEventE - with ID: 18320548421092210828 
[19:39:49] [addEventListener:25] [ViSolEngine] [Thread:18881] Create event type: N11ViSolEngine24MouseButtonReleasedEventE - with ID: 10203333618449765728 
[19:39:49] [main:12] [Client] [Thread:18881] Entry init
[19:39:49] [run:50] [ViSolEngine] [Thread:18881] App is running: 800 600 ViSolEngine version 1.0.0 
[19:39:49] [onInitClient:13] [Client] [Thread:18881] ViRobot is init
[19:39:49] [Layer:14] [ViSolEngine] [Thread:18881] Create layer ID: 16764893585577351372
[19:39:49] [onAttach:13] [Client] [Thread:18881] UserPlayLayer is attached

Breakpoint 1, UserPlayLayer::onAttach (this=0x555555c441c0) at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:37
37			robotObjects.clear();
(gdb) set $i = 0
(gdb) while $i < 5
 >    printf "i=%d, ID=%d, Name=%s\n", $i, robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >    set $i = $i + 1
 >end
i=0, ID=0, Name=RobotObject: 0
i=1, ID=1, Name=RobotObject: 1
i=2, ID=2, Name=RobotObject: 2
i=3, ID=3, Name=RobotObject: 3
i=4, ID=4, Name=RobotObject: 4
(gdb) c
Continuing.

Breakpoint 2, UserPlayLayer::onAttach (this=0x555555c441c0) at /home/devh/Build_EmbSys/Engines/ClientProject/source/UI_ViRobotLayer.h:47
47			robotObjects.clear();
(gdb) set $i = 0
(gdb) while $i < 5
 >    printf "i=%d, ID=%d, Name=%s\n", $i, robotObjects[$i]->ID, robotObjects[$i]->Name.c_str()
 >    set $i = $i + 1
 >end
i=0, ID=10000, Name=RobotObject: 0
i=1, ID=10001, Name=RobotObject: 1
i=2, ID=10002, Name=RobotObject: 2
i=3, ID=10003, Name=RobotObject: 3
i=4, ID=10004, Name=RobotObject: 4
(gdb) c
Continuing.
##############################################################################