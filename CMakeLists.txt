cmake_minimum_required(VERSION 3.21)
project(cck3_waterloo_S2022_project)

set(CMAKE_CXX_STANDARD 17)

include_directories(controller)
include_directories(model)
include_directories(model/decorator)
include_directories(model/enemy)
include_directories(model/player)
include_directories(observer)
include_directories(view)

file(COPY cc3kfloor.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(cck3_waterloo_S2022_project
        controller/EventHandler.cpp
        controller/EventHandler.h
        model/enemy/Dragon.cpp
        model/enemy/Dragon.h
        model/enemy/Enemy.cpp
        model/enemy/Enemy.h
        model/enemy/Goblin.cpp
        model/enemy/Goblin.h
        model/enemy/Merchant.cpp
        model/enemy/Merchant.h
        model/enemy/Phoenix.cpp
        model/enemy/Phoenix.h
        model/enemy/Troll.cpp
        model/enemy/Troll.h
        model/enemy/Vampire.cpp
        model/enemy/Vampire.h
        model/enemy/Werewolf.cpp
        model/enemy/Werewolf.h
        model/decorator/BarrierSuit.cpp
        model/decorator/BarrierSuit.h
        model/decorator/Decorator.cpp
        model/decorator/Decorator.h
        model/decorator/Effect.cpp
        model/decorator/Effect.h
        model/player/Dwarf.cpp
        model/player/Dwarf.h
        model/player/Elves.cpp
        model/player/Elves.h
        model/player/Orc.cpp
        model/player/Orc.h
        model/creature.h
        model/creature.cpp
        model/floor.h
        model/floor.cpp
        model/Observer.cpp
        model/Observer.h
        model/Player.cpp
        model/Player.h
        model/randomGen.cpp
        model/randomGen.h
        model/Subject.cpp
        model/Subject.h
        view/InteractiveTerminal.cpp
        view/InteractiveTerminal.h
        view/textDisplay.h
        view/textDisplay.cpp
        main.cpp)
