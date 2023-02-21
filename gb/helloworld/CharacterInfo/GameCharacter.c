#include "gamecharacter.h"

const struct CPU_List CPU_info = {
    {
        {
            {{0, 1, 2, 3}, 120, 50, 0, DOWN}, // base
            "Hello, I'm a CPU!", // dialog
            0 // isBattleCPU
        },
        {
            {{0, 1, 2, 3}, MIDDLE_X, MIDDLE_Y, 0, DOWN}, // base
            "Let's battle!", // dialog
            1, // isBattleCPU
            {CHARMANDER, SQUIRTLE, BULBASAUR, DRAGONITE, ALAKAZAM, GARDEVOIR},
            0,
            "You've defeated me!"
        },
        {
            {{0, 1, 2, 3}, 120, 50, 0, DOWN}, // base
            "You won't beat me!", // dialog
            1, // isBattleCPU
            {CHARIZARD, BLASTOISE, VENUSAUR, GOLEM, CHARMANDER2, SQUIRTLE2},
            0,
            "You've defeated me!"
        },
        {
            {{0, 1, 2, 3}, MIDDLE_X, 70, 0, DOWN}, // base
            "Get ready!", // dialog
            1, // isBattleCPU
            {BULBASAUR2, DRAGONITE2, ALAKAZAM2, GARDEVOIR2, CHARIZARD2, BLASTOISE2},
            0,
            "You've defeated me!"
        },
    },
    MAX_CPU
};

enum MonsterIndex* getCPUMonsterTeam(int index) {
    if (index >= CPU_info.count) {
        return NULL; // Invalid index.
    }

    if (CPU_info.characters[index].isBattleCPU) {
        // This is a BattleCPU.
        struct BattleCPU* battle_cpu = (struct BattleCPU*)(&CPU_info.characters[index]);
        return battle_cpu->team;
    } else {
        // This is a CPU.
        struct CPU* cpu = (struct CPU*)(&CPU_info.characters[index]);
        return NULL;
    }
}

UBYTE getCPUIsDefeated(int index) {
    if (index >= CPU_info.count) {
        return 0; // Invalid index.
    }
    if (CPU_info.characters[index].isBattleCPU) {
        return ((struct BattleCPU*)&CPU_info.characters[index])->isDefeated;
    }
    return 0; // Not a battle CPU.
}

char* getCPUDefeatedDialog(int index) {
    if (index >= CPU_info.count) {
        return NULL; // Invalid index.
    }
    if (CPU_info.characters[index].isBattleCPU) {
        return ((struct BattleCPU*)&CPU_info.characters[index])->defeatedDialog;
    }
    return NULL; // Not a battle CPU.
}