//------------------------------<FPU_FUNCTIONS>--------------------------------//

//------------------------------<STACK_FUNCTIONS>------------------------------//

//------------------------------<INITIALIZATION_FUNCTIONS>---------------------//
void Motherboard::decl(std::string type, std::string name, int size, int smth) {
    std::cout << "Variable '" << name << "' with typename '" << type << "' was declared!\n";
    if (type == "byte") { 
    	BUFF_2[VC].name = name;
    	BUFF_2[size].num = VC;
    	VC = VC + 1;
    }
    else {

    	if (type == "word") {
    		BUFF_2[VC].name = name;
    		BUFF_2[size].num = VC;
    		VC = VC + 2;
    	}
    	else {

    		if (type == "dword") {
    			BUFF_2[VC].name = name;
    			BUFF_2[size].num = VC;
    			VC = VC + 4;
    		}
    		else {

    			if (type == "qword") {
    				BUFF_2[VC].name = name;
    				BUFF_2[size].num = VC;
    				VC = VC + 8;
    			}
    			else {
    				#define DECLARATION_ERROR 0
    				assert(DECLARATION_ERROR);
    				#undef DECLARATION_ERROR
    			}
    		}
    	}
	}
}
//------------------------------<INITIALIZE_FUNC_SEGMENT>----------------------//
void Motherboard::init_ram () {
	int i;
    printf("Func init_ram started!\n");
	for (i = 0; i < 15; i++) {
		RAM[CS + PC + i] = 0;
	}
}
//------------------------------<SET_FUNCTION_CODE>----------------------------//
void Motherboard::set_func (int code) {
    printf("Func set_func() started!\n");
	RAM[CS + PC] = code;
}
//------------------------------<SET_CONSTANT>---------------------------------//
void Motherboard::set_const (union CONSTANT Const) {
	int i;
    printf("Func set_const() started!\n");
	for (i = 0; i < 8; i++) {
		RAM[CS + PC + i + 7] = Const.part[i];
	}
}
//------------------------------<SET_DATA_MOVING>------------------------------//
void Motherboard::set_moving (union Removal data) {
    int i;
    printf("Func set_moving() started!\n");
    for (i = 0; i < 4; i++) {
        RAM[CS + PC + i + 3] = data.part[i];
    }
}
//----------------<SET_BINARY_EQUAL_EXRRESSION_FOR_EACH_OPERAND>---------------//
bool Motherboard::binator(std::string operand) {
    printf("Func binarator() started!\n");
    int j = 0 ,i;
//--------------------------<IF_OPERAND_IS_REGISTER>---------------------------//
    #define REGISTER(NAME,NUM,TYPE,ADRESS)\
    if (operand == NAME) {\
        if ((RAM[CS + PC + 1] & (1 << 1)) > 0) {\
            RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 2);\
            RAM[CS + PC + 2] = NUM;\
            RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << TYPE);\
            printf("Operand is register!\n");\
            return 0;\
        }\
        else {\
            RAM[CS + PC + 1] = RAM[CS + PC + 1] | 1;\
            RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 2);\
            RAM[CS + PC + 2] = NUM;\
            RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << TYPE);\
            printf("Operand is register!\n");\
            return 0;\
        }\
    }\
    j ++
    #include "Register.hpp"
    #undef REGISTER
    printf("Operand is not register!\n");
//------------------------<IF_OPERAND_IS_TYPENAME>----------------------------//
    if (operand == "byte") {
        RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 7);
        printf("Operand is typename!\n");
        return 0;
    }
    if (operand == "word") {
        RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 6);
        printf("Operand is typename!\n");
        return 0;
    }
    if (operand == "dword") {
        RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 5);
        printf("Operand is typename!\n");
        return 0;
    }
    if (operand == "qword") {
        RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 4);
        printf("Operand is typename!\n");
        return 0;
    }
    if (operand == "label") {
        RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 4);
        printf("Operand is typename!\n");
        return 0;
    }
    if (operand == "register") {
        RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 4);
        printf("Operand is typename!\n");
        return 0;
    }
    if (operand == "const") {
        if ((((RAM[CS + PC + 1]) & (1 << 7)) + ((RAM[CS + PC + 1]) & (1 << 6)) + ((RAM[CS + PC + 1]) & (1 << 5))) > 0) {
            RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 4);
        }
        RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 3);
        printf("Operand is typename!\n");
        printf("Type name is const, returning 1!\n");
        return 1;
    }
    printf("Operand is not typename!\n");
//------------------------------<IF_OPERAND_IS_DATA>------------------------//
    for (i = 0; i < VC ; i ++) {
        if (operand == BUFF_2[i].name) {
            if (((RAM[CS + PC + 1]) & (1 << 2)) > 0) {
                union Removal data;
                RAM[CS + PC + 1] = RAM[CS + PC + 1] | 1;
                RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 1);
                data.moving = BUFF_2[i].num;
                set_moving(data);
                printf("Operand is variable!\n");
                return 0;
            }
            else {
                union Removal data;
                RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 1);
                data.moving = BUFF_2[i].num;
                set_moving(data);
                printf("Operand is variable!\n");
                return 0;
            }
        }
    }
    printf("Operand is not declared variable!\n");
//-----------------------------<IF_OPERAND_IS_LABEL>-----------------------//
    for (i = 0; i < LC ; i ++) {
        if (operand == BUFF_1[i].label) {
            union CONSTANT label; 
            RAM[CS + PC + 1] = RAM[CS + PC + 1] | (1 << 3);
            RAM[CS + PC + 1] = RAM[CS + PC + 1] | 1;
            label.num = BUFF_1[i].num;
            printf("Operand is label!\n");
            set_const(label);
            return 0;
        }
    }
    printf("Operand is not Label!\n");
    #define WRONG_SYNTAX_OR_UNDECLARED_VARIABLE_DETECTED 0
    assert(WRONG_SYNTAX_OR_UNDECLARED_VARIABLE_DETECTED);
    #undef WRONG_SYNTAX_OR_UNDECLARED_VARIABLE_DETECTED
    return 0;
}
void Motherboard::end(int situation, int type, int reg, int moving, long Const) {
    printf("Program ended!\n");
}
//-----------------------------<DATA_GETERS_FROM_BINARY>------------------//
long Motherboard::get_const() {
    union CONSTANT elem;
    printf("We are in get_const, PC is %d.\n",PC);
    elem.part[0] = RAM[CS + PC + 7];
    elem.part[1] = RAM[CS + PC + 8]; 
    elem.part[2] = RAM[CS + PC + 9];
    elem.part[3] = RAM[CS + PC + 10];
    elem.part[4] = RAM[CS + PC + 11];
    elem.part[5] = RAM[CS + PC + 12];
    elem.part[6] = RAM[CS + PC + 13];
    elem.part[7] = RAM[CS + PC + 14];
    return elem.num;
}
int Motherboard::get_reg() {
    printf("We are in get_reg(), PC is %d.\n",PC);
    int ret;
    ret = RAM[CS + PC + 2];
    return ret;
}
int Motherboard::get_code() {
    printf("We are in get_code(), PC is %d.\n",PC);
    int ret;
    ret = RAM[CS + PC];
    return ret;
}
int Motherboard::get_moving() {

    union Removal elem_1;
    elem_1.part[0] = RAM[CS + PC + 3];
    elem_1.part[1] = RAM[CS + PC + 4];
    elem_1.part[2] = RAM[CS + PC + 5];
    elem_1.part[3] = RAM[CS + PC + 6];
    return elem_1.moving;
}
int Motherboard::get_type() {
    int i;
    for (i = 7; i > 3; i --) {
        if ((RAM[CS + PC + 1] & (1 << i)) > 0) {
            switch (i) {
                case 4: return 8;
                case 5: return 4;
                case 6: return 2;
                case 7: return 1;
                default: 
                #define UNKNOWN_ERROR 0
                assert(UNKNOWN_ERROR);
                #undef UNKNOWN_ERROR
            }
        }
    }
    if ((RAM[CS + PC] != 4)&&(RAM[CS + PC] != 6)) {
        printf("%d\n",RAM[CS + PC]);
        #define TYPE_NOT_SELECTED 0
        assert(TYPE_NOT_SELECTED);
        #undef TYPE_NOT_SELECTED
    }
    return 0;
}
int Motherboard::get_situation() {
    int ret;
    if (((RAM[CS + PC + 1] & (1 << 3))*(RAM[CS + PC + 1] & (1 << 2))) > 0) {
        return 0; 
    }
    if (((RAM[CS + PC + 1] & (1 << 3))*(RAM[CS + PC + 1] & (1 << 1))) > 0) {
        return 1; 
    }
    if (((RAM[CS + PC + 1] & (1 << 2))*(RAM[CS + PC + 1] & (1 << 1))*(RAM[CS + PC + 1] & 1) > 0)) {
        return 2; 
    }
    if (((RAM[CS + PC + 1] & (1 << 2))*(RAM[CS + PC + 1] & (1 << 1))) > 0) {
        return 3; 
    }
    if ((RAM[CS + PC + 1] & (1 << 2)) > 0) {
        return 4; 
    }
    if ((RAM[CS + PC + 1] & (1 << 1)) > 0) {
        return 5; 
    }
    if ((RAM[CS + PC + 1] & (1 << 3)) > 0) {
        return 6; 
    }
    if ((RAM[CS + PC]) != 4) {
        #define UNDEFINED_SITUATION 0
        assert(UNDEFINED_SITUATION);
        #undef UNDEFINED_SITUATION
    }
        return 7;
}
char Motherboard::read_byte(int moving) {
    char elem;
    elem = RAM[DS + moving];
    return elem;
}
short Motherboard::read_word(int moving) {
    union Word elem;
    elem.part[0] = RAM[DS + moving + 0];
    elem.part[1] = RAM[DS + moving + 1];
    return elem.word;
}
int Motherboard::read_int(int moving) {
    union Int elem;
    elem.part[0] = RAM[DS + moving + 0];
    elem.part[1] = RAM[DS + moving + 1];
    elem.part[2] = RAM[DS + moving + 2];
    elem.part[3] = RAM[DS + moving + 3];
    return elem.integer;
}
long Motherboard::read_long(int moving) {
    union Long elem;
    elem.part[0] = RAM[DS + moving + 0];
    elem.part[1] = RAM[DS + moving + 1];
    elem.part[2] = RAM[DS + moving + 2];
    elem.part[3] = RAM[DS + moving + 3];
    elem.part[4] = RAM[DS + moving + 4];
    elem.part[5] = RAM[DS + moving + 5];
    elem.part[6] = RAM[DS + moving + 6];
    elem.part[7] = RAM[DS + moving + 7];
    return elem.long_int;
}
void Motherboard::write_byte(int moving, char elem) {
    RAM[DS + moving] = elem;
}
void Motherboard::write_word(int moving, short elem_1) {
    union Word elem;
    elem.word = elem_1;
    RAM[DS + moving + 0] = elem.part[0];
    RAM[DS + moving + 1] = elem.part[1];
}
void Motherboard::write_int(int moving, int elem_1) {
    union Int elem;
    elem.integer = elem_1;
    RAM[DS + moving + 0] = elem.part[0];
    RAM[DS + moving + 1] = elem.part[1];
    RAM[DS + moving + 2] = elem.part[2];
    RAM[DS + moving + 3] = elem.part[3];
}
void Motherboard::write_long(int moving, long elem_1) {
    union Long elem;
    elem.long_int = elem_1;
    RAM[DS + moving + 0] = elem.part[0];
    RAM[DS + moving + 1] = elem.part[1];
    RAM[DS + moving + 2] = elem.part[2];
    RAM[DS + moving + 3] = elem.part[3];
    RAM[DS + moving + 4] = elem.part[4];
    RAM[DS + moving + 5] = elem.part[5];
    RAM[DS + moving + 6] = elem.part[6];
    RAM[DS + moving + 7] = elem.part[7];
}
