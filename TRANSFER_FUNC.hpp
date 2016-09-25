//------------------------------<TRANSFER_FUNCTIONS>---------------------------//
void Motherboard::jmp(int situation, int type, int reg, int moving, long Const) {
    printf("jmp() was started!\n");
    PC = Const * 15;
    printf("PC was just changed on %d\n", PC);
}