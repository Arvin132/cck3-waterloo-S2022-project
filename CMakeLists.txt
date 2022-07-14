cmake_minimum_required(VERSION 3.21)
project(cck3_waterloo_S2022_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(controller)
include_directories(model/creature/enemy)
include_directories(model/creature/player)
include_directories(model/creature/player/decorator)
include_directories(observer)
include_directories(view)

add_executable(cck3_waterloo_S2022_project
        controller/EventHandler.cpp
        controller/EventHandler.h
        model/creature/enemy/Dragon.cpp
        model/creature/enemy/Dragon.h
        model/creature/enemy/Enemy.cpp
        model/creature/enemy/Enemy.h
        model/creature/enemy/Goblin.cpp
        model/creature/enemy/Goblin.h
        model/creature/enemy/Merchant.cpp
        model/creature/enemy/Merchant.h
        model/creature/enemy/Phoenix.cpp
        model/creature/enemy/Phoenix.h
        model/creature/enemy/Troll.cpp
        model/creature/enemy/Troll.h
        model/creature/enemy/Vampire.cpp
        model/creature/enemy/Vampire.h
        model/creature/enemy/Werewolf.cpp
        model/creature/enemy/Werewolf.h
        model/creature/player/decorator/BarrierSuit.cpp
        model/creature/player/decorator/BarrierSuit.h
        model/creature/player/decorator/Decorator.cpp
        model/creature/player/decorator/Decorator.h
        model/creature/player/decorator/Potion.cpp
        model/creature/player/decorator/Potion.h
        model/creature/player/Dwarf.cpp
        model/creature/player/Dwarf.h
        model/creature/player/Elves.cpp
        model/creature/player/Elves.h
        model/creature/player/Human.cpp
        model/creature/player/Human.h
        model/creature/player/Orc.cpp
        model/creature/player/Orc.h
        model/creature/player/Player.cpp
        model/creature/player/Player.h
        observer/Observer.cpp
        observer/Observer.h
        observer/Subject.cpp
        observer/Subject.h
        view/InteractiveTerminal.cpp
        view/InteractiveTerminal.h
        main.cpp)
