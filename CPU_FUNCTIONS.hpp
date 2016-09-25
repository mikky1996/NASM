//------------------------------<CPU_FUNCTIONS>--------------------------------//
void Motherboard::add(int situation,int type, int reg, int moving, long Const) {
    printf("add() was started!\n");
    switch (situation) {
        case reg_const: {
            #define REGISTER(NAME,NUM,TYPE,ADRESS)\
            if (reg == NUM)\
                ADRESS = Const + ADRESS;\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        case data_const: {
            if (type == 1) {char elem = read_byte(moving); elem = elem + Const; write_byte(moving, elem);}
            if (type == 2) {short elem = read_word(moving); elem = elem + Const; write_word(moving, elem);}
            if (type == 4) {int elem = read_int(moving); elem = elem + Const; write_int(moving, elem);}
            if (type == 8) {long elem = read_long(moving); elem = elem + Const; write_long(moving, elem);}
            break;
        }
        case reg_data: {
            #define REGISTER(NAME,NUM,TYPE,ADRESS)\
            if (reg == NUM) {\
                if (type == 1) {char elem = read_byte(moving); ADRESS = ADRESS + elem;}\
                if (type == 2) {short elem = read_word(moving); ADRESS = ADRESS + elem;}\
                if (type == 4) {int elem = read_int(moving); ADRESS = ADRESS + elem;}\
                if (type == 8) {long elem = read_long(moving); ADRESS = ADRESS + elem;}\
            }\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        case data_reg: {
            #define REGISTER(NAME,NUM,TYPE,ADRESS)\
             if (reg == NUM) {\
                if (type == 1) {char elem = read_byte(moving); elem = ADRESS + elem; write_byte(moving, elem);}\
                if (type == 2) {short elem = read_word(moving); elem = ADRESS + elem; write_word(moving, elem);}\
                if (type == 4) {int elem = read_int(moving); elem = ADRESS + elem; write_int(moving, elem);}\
                if (type == 8) {long elem = read_long(moving); elem = ADRESS + elem; write_long(moving, elem);}\
            }\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        default:
            #define ADD_ERROR 0
            assert(ADD_ERROR);
            #undef ADD_ERROR
    }
}
void Motherboard::mov(int situation,int type, int reg, int moving, long Const) {
    printf("mov() was started!\n");
    switch (situation) {
        case reg_const: {
            #define REGISTER(NAME,NUM,TYPE,ADRESS)\
            if (reg == NUM)\
                ADRESS = Const;\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        case data_const: {
            if (type == 1) {char elem ; elem = Const; write_byte(moving, elem);}
            if (type == 2) {short elem ; elem = Const; write_word(moving, elem);}
            if (type == 4) {int elem ; elem = Const; write_int(moving, elem);}
            if (type == 8) {long elem ; elem = Const; write_long(moving, elem);}
            break;
        }
        case reg_data: {
            #define REGISTER(NAME,NUM,TYPE,ADRESS)\
            if (reg == NUM) {\
                if (type == 1) {char elem = read_byte(moving); ADRESS = elem;}\
                if (type == 2) {short elem = read_word(moving); ADRESS = elem;}\
                if (type == 4) {int elem = read_int(moving); ADRESS = elem;}\
                if (type == 8) {long elem = read_long(moving); ADRESS = elem;}\
            }\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        case data_reg: {
            #define REGISTER(NAME,NUM,TYPE,ADRESS)\
             if (reg == NUM) {\
                if (type == 1) {char elem ; elem = ADRESS ; write_byte(moving, elem);}\
                if (type == 2) {short elem ; elem = ADRESS ; write_word(moving, elem);}\
                if (type == 4) {int elem ; elem = ADRESS ; write_int(moving, elem);}\
                if (type == 8) {long elem  ; elem = ADRESS ; write_long(moving, elem);}\
            }\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        default:
            #define MOV_ERROR 0
            assert(MOV_ERROR);
            #undef MOV_ERROR
    }
}
void Motherboard::print(int situation,int type, int reg, int moving, long Const) {
    printf("print() was started!\n");
    switch (situation) {
        case data: {
            if (type == 1) {char elem  = read_byte(moving); printf("%d\n",elem);}
            if (type == 2) {short elem = read_word(moving); printf("%d\n",elem);}
            if (type == 4) {int elem   = read_int(moving);  printf("%d\n",elem);}
            if (type == 8) {long elem  = read_long(moving); printf("%ld\n",elem);}
            break;
        }
        case my_reg: {
        #define REGISTER(NAME,NUM,TYPE,ADRESS)\
            if (reg == NUM) {\
                if (type == 1) {char  elem ; std::cout << ADRESS << "\n";}\
                if (type == 2) {short elem ; std::cout << ADRESS << "\n";}\
                if (type == 4) {int   elem ; std::cout << ADRESS << "\n";}\
                if (type == 8) {long  elem ; std::cout << ADRESS << "\n";}\
            }\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        case number: {
            std::cout << Const << "\n";
            break;
        }
        default: {
            #define DATA_CAN_NOT_BE_PRINTED 0
            assert(DATA_CAN_NOT_BE_PRINTED);
            #undef DATA_CAN_NOT_BE_PRINTED
        }
    }
}
void Motherboard::mul(int situation,int type, int reg, int moving, long Const) {
    printf("mul() was started!\n");
    switch (situation) {
        case reg_const: {
            #define REGISTER(NAME,NUM,TYPE,ADRESS)\
            if (reg == NUM)\
                ADRESS = Const * ADRESS;\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        case data_const: {
            if (type == 1) {char elem = read_byte(moving); elem = elem * Const; write_byte(moving, elem);}
            if (type == 2) {short elem = read_word(moving); elem = elem * Const; write_word(moving, elem);}
            if (type == 4) {int elem = read_int(moving); elem = elem * Const; write_int(moving, elem);}
            if (type == 8) {long elem = read_long(moving); elem = elem * Const; write_long(moving, elem);}
            break;
        }
        case reg_data: {
            #define REGISTER(NAME,NUM,TYPE,ADRESS)\
            if (reg == NUM) {\
                if (type == 1) {char elem = read_byte(moving); ADRESS = ADRESS * elem;}\
                if (type == 2) {short elem = read_word(moving); ADRESS = ADRESS * elem;}\
                if (type == 4) {int elem = read_int(moving); ADRESS = ADRESS * elem;}\
                if (type == 8) {long elem = read_long(moving); ADRESS = ADRESS * elem;}\
            }\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        case data_reg: {
            #define REGISTER(NAME,NUM,TYPE,ADRESS)\
             if (reg == NUM) {\
                if (type == 1) {char elem = read_byte(moving); elem = ADRESS * elem; write_byte(moving, elem);}\
                if (type == 2) {short elem = read_word(moving); elem = ADRESS * elem; write_word(moving, elem);}\
                if (type == 4) {int elem = read_int(moving); elem = ADRESS * elem; write_int(moving, elem);}\
                if (type == 8) {long elem = read_long(moving); elem = ADRESS * elem; write_long(moving, elem);}\
            }\

            #include "Register.hpp"
            #undef REGISTER
            break;
        }
        default:
            #define MUL_ERROR 0
            assert(MUL_ERROR);
            #undef MUL_ERROR
    }
}