cmake_minimum_required(VERSION 3.24)
project(gb C)

set(CMAKE_C_STANDARD 11)

include_directories(helloworld/Sprite/Character)

add_executable(gb
        helloworld/Background/Battle/battle_data.c
        helloworld/Background/Battle/battle_map.c
        helloworld/Background/Room_Bottom/room_bottom_data.c
        helloworld/Background/Room_Bottom/room_bottom_map.c
        helloworld/Background/Room_Top/room_top_data.c
        helloworld/Background/Room_Top/room_top_map.c
        helloworld/Background/SplashScreen/splashscreen_data.c
        helloworld/Background/SplashScreen/splashscreen_map.c
        helloworld/Sprite/Character/SmilerSprites.c
        helloworld/Sprite/Character/SmilerSprites.h
        helloworld/main.c helloworld/battle/moves.h helloworld/battle/moves.c helloworld/battle/monsters.h helloworld/battle/monsters.c helloworld/battle/battle.c helloworld/Navigation/Rooms.c helloworld/Navigation/Rooms.c)
