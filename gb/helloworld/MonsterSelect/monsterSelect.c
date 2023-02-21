#include "monsterSelect.h"



#define MAX_STACK_SIZE 6
UBYTE currentList = 1;
const UBYTE startCursor = 40; 


// Define the stack structure
typedef struct {
    int items[MAX_STACK_SIZE];
    int top;
} stack;

// Initialize the stack
void init_stack(stack *s) {
    s->top = -1;
}

// Check if the stack is empty
int is_empty(stack *s) {
    return s->top == -1;
}

// Check if the stack is full
int is_full(stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

// Push an item onto the stack
void push(stack *s, int item) {
    if (is_full(s)) {
        printf("Stack is full\n");
        return;
    }
    s->top++;
    s->items[s->top] = item;
}

// Pop an item from the stack
int pop(stack *s) {
    int item;
    if (is_empty(s)) {
        //printf("Stack is empty\n");
        return -1;
    }
    item = s->items[s->top];
    s->top--;
    if (s->top < -1) { // Check if top has gone out of bounds
        s->top = -1;
    }
    return item;
}

// // Peek at the top item of the stack
// int peek(stack *s) {
//     if (is_empty(s)) {
//         printf("Stack is empty\n");
//         return -1;
//     }
//     return s->items[s->top];
// }

int get_size(stack *s) {
    return s->top + 1;
}

stack s;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printPaddedNumber(int num, int length) {
    int i;
    int numDigits;
    int numSpaces;
    int temp = num;
    numDigits = 0;
    while (temp != 0) {
        temp /= 10;
        numDigits++;
    }
    numSpaces = length - numDigits;
    if (numSpaces > 0) {
        for (i = 0; i < numSpaces; i++) {
            printf(" ");
        }
    }
    printf("%d", num);
}

void printPaddedString(char* str, int length) {
    int i;
    int strLength = strlen(str);
    int numSpaces = length - strLength;
    printf("%s", str);
    if (numSpaces > 0) {
        for (i = 0; i < numSpaces; i++) {
            printf(" ");
        }
    }
}

void displayMonsterInfo(Monster *monster) {
    int i;
    // for (i = 0; i < 4; i++) {
    //     gotoxy(16, 5+i);
    //     printf("%s\n", moves[monster->moves[i]].name);
    // }
for (i = 0; i < 2; i++) {
    gotoxy(13, 9+i);
    if (i == 1 && monster->types[0] == monster->types[1]) {
        printPaddedString(" ", 6);
    } else {
        printPaddedString(ElementalTypes[monster->types[i]].name, 6);
    }
}
    // Print the monster's stats
gotoxy(16, 12);
printPaddedNumber(monster->health, 3);
gotoxy(16, 13);
printPaddedNumber(monster->attack, 3);
gotoxy(16, 14);
printPaddedNumber(monster->speed, 3);
gotoxy(17, 15);
printPaddedNumber(monster->defense, 2);
}

void setBackgound(){
    clearScreen();
    set_bkg_tiles(0,0,20,18,Select_Screen_map);
    gotoxy(0, 0);
    printf("Select Your Monsters");
    gotoxy(13, 8);
    printf("Stats:");
    gotoxy(13, 12);
    printf("HP");
    gotoxy(13, 13);
    printf("Atk");
    gotoxy(13, 14);
    printf("Sp");
    gotoxy(13, 15);
    printf("Def");
    gotoxy(3, 17);
    printf("Selected:");
    gotoxy(12, 17);
    printf("%d", get_size(&s));
}



void displayMonsterList(int listNum) {
    int i;
    int row = 3;

    // Print out the monsters for the given list number
    for (i = (listNum - 1) * 13; i < listNum * 13; i++) {
        if (i < MAX_MONSTERS) {
            gotoxy(1, row + i % 13);
            printf("%s\n", monsters[i].name);
        }
    }
}

UBYTE selectInput(){
    int i;
    int row; 
    UBYTE cursor_loc;     
    UBYTE exit_loop;
    row = 3;
    i = 0;
    init_stack(&s);

    cursor_loc = startCursor;

    set_sprite_data(0, 1, Cursors);
    set_sprite_tile(0, 80); // moving cursor
    move_sprite(80, 9, cursor_loc);

    // Print out the first list of monsters
    displayMonsterList(currentList);

    // Print out the info for the first monster
    displayMonsterInfo(&monsters[0]);

    exit_loop = 0;
    while(!exit_loop){
        switch(joypad()){
        case J_UP: 
            if (currentList == 1 && i == 0) {
                playCollisionSound();
                performantdelay(2);
                break;  // do not move the cursor or index
            }
            if (cursor_loc > (row + 1) * 10) {  // move the cursor up if it's not at the top of the list
                cursor_loc -= 8;
                move_sprite(80, 9, cursor_loc);  // move the cursor sprite
                i--;
                if (i < 0) {
                    currentList = (currentList == 1) ? 2 : 1;
                    i = (currentList == 1) ? 12 : MAX_MONSTERS - 13;
                    setBackgound();
                    displayMonsterList(currentList);
                    cursor_loc = (row + 1) * 10 + i * 8;
                    move_sprite(80, 9, cursor_loc);
                }
                //gotoxy(13, 15);
                //printf("%d",i);
                displayMonsterInfo(&monsters[(currentList - 1) * 13 + i]);
            }
            break;
            case J_DOWN: 
                if (cursor_loc < ((row + 13) * 8) + 16) {  // move the cursor down if it's not at the bottom of the list
                    cursor_loc += 8;
                    move_sprite(80, 9, cursor_loc);  // move the cursor sprite
                    i++;
                    if (i > 13 || (currentList == 2 && i >= MAX_MONSTERS - 13)) {
                        currentList = (currentList == 1) ? 2 : 1;
                        i = 0;
                        setBackgound();
                        displayMonsterList(currentList);
                        cursor_loc = (row + 1) * 10;
                        move_sprite(80, 9, cursor_loc);
                    }
                    //printf((currentList - 1) * 13 + i);
                    //gotoxy(13, 15);
                    //printf("%d",i);
                    displayMonsterInfo(&monsters[(currentList - 1) * 13 + i]);
                }
                break;
            case J_START:
                exit_loop = 1;
                break;
            case J_A:
                if (is_full(&s)) {
                    //printf("Stack is full. Please try again.\n");

                    break;
                }
                push(&s, i+ ((currentList == 1) ? 0 : 13));
                gotoxy(12, 17);
                printf("%d", get_size(&s));
                break;
            case J_B:
            if(is_empty(&s)){
                break;
            }
                pop(&s);
                gotoxy(12, 17);
                printf("%d", get_size(&s));
                break;
        }
        performantdelay(10);
    }
    return i;
}









void selectMonsters() {
    SHOW_SPRITES;    
    set_bkg_data(0,15, Select_Screen_data); 
    setBackgound();

    selectInput();

    waitpad(J_START);
    }
