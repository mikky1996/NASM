#include <assert.h> 
class Motherboard {
//---------------<Struct List>-----------------------//
    union Word {
        short word;
        char part[2];
    };
    union Int {
        int integer;
        char part[4];
    };
    union Long {
        long long_int;
        char part[8];
    };
    enum Situation {
        reg_const  = 0,
        data_const = 1,
        reg_data   = 2,
        data_reg   = 3,
        my_reg     = 4,
        data       = 5,
        number     = 6
    };
    union Register {
        long e;
        int x[2];
        char h[8];
    };
    struct Label {
        std::string label;
        int num;
    };
    struct Vars {
        std::string name;
        int num;
    };
    union Removal {
        int moving;
        char part[4];
    };
    union CONSTANT {
        long num;
        char part[8];
    };
//-------------<GLOBAL VARIABELS>--------------------//
private:
    int CS;                // Сегмент кода
    int DS;                // Сегмент даннных
    int SS;                // Сегмент стека
    int ES;                // Сегмент вспомогательный
    int SP;                // Вершина стека
    int BP;                // База стека
    int SI;                // Индекс источника
    int DI;                // Индекс приемника
public:
    int PC;                // Счетчик команд
//--------------------<CPU>---------------------------//
    
    union Register a;      // Арифметический регистр
    union Register b;      // Базовый регистр
    union Register c;      // Подсчетный регистр
    union Register d;      // Вспомогательный регистр
private:
    char  EFLAGS;          // Флаговый регистр
//--------------------<FPU>---------------------------//
public:
    double f_reg[8];       // Циклический стек дробных регистров
private:
    int FC;                // Счетчик операций со стеком (pop -> FC-1; push -> FC+1)
//---------------<Initialization>---------------------//
public:
    char * RAM;            // Оперативная память
    std::string * BUFF;    // Буфер для инициализации
    struct Label * BUFF_1; // Буфер для инициализации меток
    struct Vars  * BUFF_2; // Буфер для инициализации переменных
    int VC;                // Счетчик для инициализации переменных
    int LC;                // Счетчик для инициализации меток
//-----------------<Functions>------------------------//
    Motherboard();
    ~Motherboard();
    void Initialize_var(std::string file);
    void compilation(std::string file);
    void Create_obj_file();
    void start(std::string file);
    #include "INITIALIZE_FUNC.hpp"
};
//----------------<Constructor>----------------------//
Motherboard::Motherboard() {
    int i;
    EFLAGS = 0;
    CS = 0;
    DS = 0;
    SS = 0;
    ES = 0;
    SP = 0;
    BP = 0;
    SI = 0;
    DI = 0;
    PC = 0;
    DS = 0;
    a.e = 0;
    b.e = 0;
    c.e = 0;
    d.e = 0;
    FC = 0;
    VC = 0;
    RAM = NULL;
    BUFF_1 = new struct Label [100];
    BUFF_2 = new struct Vars [100];
    for (i = 0; i < 8; i++) {
        f_reg[i] = 0;
    }
}
//----------------<Distructorr>------------------------//
Motherboard::~Motherboard() {
//----------------<FREE_MEMORY>------------------------//
    if (RAM != NULL)    delete [] RAM;
    if (BUFF_1 != NULL) delete [] BUFF_1;
    if (BUFF_2 != NULL) delete [] BUFF_2;
}
//-----------------<ASM_FUNC>--------------------------//
#include "TRANSFER_FUNC.hpp"
#include "CPU_FUNCTIONS.hpp"
#include "FUNC_LIST.hpp"
//----------<VARIABELS_INITIALIZATION>-----------------//
void Motherboard::Initialize_var(std::string file) {
    std::cout << "Inizialization in progress..." <<"\n\n";
    std::ifstream in;
    in.open(file);
    int i, counter = 0;
    int k;
    k = 0;
    i = 0;
    c.e = 0;
    int pointer;
    std::string command;
    std::string operand_1;
    std::string operand_2;
    std::string operand_3;
    std::string operand_4;
    command = "start";
    while (command != "END") {
        pointer = 0;
        in >> command;
        #define COMMAND(NAME, NUM, FUNC, CODE)\
        if (command == NAME) {\
            c.x[0] ++;\
            pointer = 1;\
            if (NUM == 1) {\
                in >> operand_1;\
            }\
            if (NUM == 2) {\
                in >> operand_1;\
                in >> operand_2;\
                if (command == "DEC") {\
                    decl(operand_1, operand_2, counter, 0);\
                    counter ++;\
                }\
            }\
            if (NUM == 3) {\
                in >> operand_1;\
                in >> operand_2;\
                in >> operand_3;\
            }\
            if (NUM == 4) {\
                in >> operand_1;\
                in >> operand_2;\
                in >> operand_3;\
                in >> operand_4;\
            }\
        }\
        k++
        #include "COMMAND_LIST.hpp"
        COMMAND("DEC", 2 , decl , 5 );
        #undef COMMAND
        if (pointer == 0) {
            BUFF_1[c.x[1]].label = command;
            BUFF_1[c.x[1]].num = c.x[0] - 1;
            std::cout << "Label '" << command << "' with number '" << c.x[0] << "' was declared!\n";
            c.x[1]++;
        }
    }
    VC = counter;
    LC = c.x[1];
    in.close();
    printf("\n");
    std::cout << "Inizialization successfully completed!" << "\n";
}


//-------<TRANSFORMING_FILE_IN_BINARY_EQVIVALENT>------//
void Motherboard::compilation(std::string file) {
    std::cout << "Compilation in progress..." <<"\n\n";
    std::ifstream in;
    in.open(file);
    RAM = new char [10000 * c.x[0]];
    bool is_next_const = 0;
    int flag;
    int k = 0;
    std::string command;
    std::string operand_1;
    std::string operand_2;
    std::string operand_3;
    std::string operand_4;
    command = "start";
    while (command != "END") {
        is_next_const = 0;
        flag = 0;
        in >> command;
        #define COMMAND(NAME, NUM, FUNC, CODE)\
        if ((command == NAME)&&(NAME != "DEC")) {\
            std::cout << "Command search sucseeded! Command " << NAME << " found!" << "\n";\
            init_ram();\
            flag = 1;\
            union CONSTANT Const;\
            Const.num = 0;\
            set_func(CODE);\
            if (NUM == 1) {\
                printf("Number of arguments is %d.\n",NUM);\
                in >> operand_1;\
                binator(operand_1);\
            }\
            if (NUM == 2) {\
                printf("Number of arguments is %d.\n",NUM);\
                in >> operand_1;\
                is_next_const = binator(operand_1);\
                if (is_next_const) {\
                    printf("Reading constant...\n");\
                    in >> Const.num;\
                    set_const(Const);\
                    is_next_const = 0;\
                }\
                else {\
                   in >> operand_2;\
                   is_next_const = binator(operand_2);\
                }\
            }\
            if (NUM == 3) {\
                printf("Number of arguments is %d.\n",NUM);\
                in >> operand_1;\
                is_next_const = binator(operand_1);\
                if (is_next_const) {\
                    printf("Reading constant...\n");\
                    in >> Const.num;\
                    set_const(Const);\
                    is_next_const = 0;\
                }\
                else {\
                   in >> operand_2;\
                   is_next_const = binator(operand_2);\
                }\
                if (is_next_const) {\
                    printf("Reading constant...\n");\
                    in >> Const.num;\
                    set_const(Const);\
                    is_next_const = 0;\
                }\
                else {\
                   in >> operand_3;\
                   is_next_const = binator(operand_3);\
                }\
            }\
            if (NUM == 4) {\
                printf("Number of arguments is %d.\n",NUM);\
                in >> operand_1;\
                is_next_const = binator(operand_1);\
                if (is_next_const) {\
                    printf("Reading constant...\n");\
                    in >> Const.num;\
                    set_const(Const);\
                    is_next_const = 0;\
                }\
                else {\
                   in >> operand_2;\
                   is_next_const = binator(operand_2);\
                }\
                if (is_next_const) {\
                    printf("Reading constant...\n");\
                    in >> Const.num;\
                    set_const(Const);\
                    is_next_const = 0;\
                }\
                else {\
                   in >> operand_3;\
                   is_next_const = binator(operand_3);\
                }\
                if (is_next_const) {\
                    printf("Reading constant...\n");\
                    in >> Const.num;\
                    set_const(Const);\
                    is_next_const = 0;\
                }\
                else {\
                   in >> operand_4;\
                   is_next_const = binator(operand_4);\
                }\
            }\
            PC = PC + 15;\
        }\
        k ++
        #include "COMMAND_LIST.hpp"
        COMMAND("DEC", 2, decl, 5);
        #undef COMMAND
    }
    in.close();
    printf("\n");
    std::cout << "Compilation successfully completed!" << "\n";
    VC = PC;
}
//--------------<CREATE_OBJECT_FILE>-------------------//
void Motherboard::Create_obj_file() {
int i;
int j;
printf("\n");
printf("                     Object_file                     \n");
printf("-----------------------------------------------------\n");
//printf("--COMMAND_CODE--MASK--REG--MOVING--CONST-------------\n");
    for (i = 0; i < VC ; i = i + 15) {
        printf("%d ",RAM[CS + i]);
        for (j = 0; j < 8; j ++) {
            if ((RAM[CS + i + 1] & (1 << (7-j)))  > 0) {
                printf("1");
            }
            else {
                printf("0");
            }
        }
        printf(" ");
        printf("%d ",RAM[CS + i + 2]);
        union Removal elem_1;
        elem_1.part[0] = RAM[CS + i + 3];
        elem_1.part[1] = RAM[CS + i + 4];
        elem_1.part[2] = RAM[CS + i + 5];
        elem_1.part[3] = RAM[CS + i + 6];
        printf("%d ",elem_1.moving);
        union CONSTANT elem;
        elem.part[0] = RAM[CS + i + 7];
        elem.part[1] = RAM[CS + i + 8]; 
        elem.part[2] = RAM[CS + i + 9];
        elem.part[3] = RAM[CS + i + 10];
        elem.part[4] = RAM[CS + i + 11];
        elem.part[5] = RAM[CS + i + 12];
        elem.part[6] = RAM[CS + i + 13];
        elem.part[7] = RAM[CS + i + 14];
        printf("%ld ",elem.num);
        printf("\n");
    }
printf("-----------------------------------------------------\n");
}
//--------------<STARTING_ASM_PROGRAMM>----------------//
void Motherboard::start(std::string file) {
    printf("Program work in progres...\n");
    int i = 0;
    SS = PC + 2000;
    DS = PC + 2001;
    SP = PC + 2000;
    BP = PC + 2000; 
    PC = 0;
    int situation;
    int  code;
    int  type;
    int  reg;
    int  moving;
    long Const;
    while (code != 4) {
        situation = get_situation();
        code      = get_code();
        type      = get_type();
        reg       = get_reg();
        moving    = get_moving();
        Const     = get_const();
        #define COMMAND(NAME,NUM,FUNC,CODE)\
        if ((code == CODE)&&(CODE != 4)) {\
            FUNC(situation, type, reg, moving, Const);\
        }\
        i ++
        #include "COMMAND_LIST.hpp"
        #undef COMMAND
        PC = PC + 15;
    }
    printf("Program successfully ended its work\n");
}
