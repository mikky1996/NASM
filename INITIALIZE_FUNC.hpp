//------------------------------<CPU_FUNCTIONS>--------------------------------//
    void  add       (int, int, int, int, long);
    void  mov       (int, int, int, int, long);
    void  mul       (int, int, int, int, long);
//------------------------------<FPU_FUNCTIONS>--------------------------------//

//------------------------------<STACK_FUNCTIONS>------------------------------//

//------------------------------<TRANSFER_FUNCTIONS>---------------------------//
    void  jmp       (int, int, int, int, long);
//------------------------------<INITIALIZATION_FUNCTIONS>---------------------//
    char  read_byte (int);
    short read_word (int);
    int   read_int  (int);
    long  read_long (int);
    void  write_byte(int,char);
    void  write_word(int,short);
    void  write_int (int,int);
    void  write_long(int,long);
    void  init_ram  ();
    void  set_moving(union Removal);
    void  set_func  (int);
    void  set_const (union CONSTANT);
    long  get_const ();
    int   get_situation();
    int   get_reg   ();
    int   get_moving();
    int   get_type  ();
    int   get_code  ();
    bool  binator   (std::string);
    void  decl      (std::string ,std::string ,int ,int);
//------------------------------<COMMON_FUNCTIONS>----------------------------//
    void  print     (int, int, int, int, long);
    void  end       (int, int, int, int, long);
