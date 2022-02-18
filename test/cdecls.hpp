extern "C"
{
    typedef struct
    {
        void *state;
        void *param;
        char *name;
        double (*GetU01)(void *param, void *state);
        unsigned long (*GetBits)(void *param, void *state);
        void (*Write)(void *state);
    } unif01_Gen;

    unif01_Gen *unif01_CreateExternGenBitsL(char *name, unsigned long (*genB)(void));
    unif01_Gen *unif01_CreateExternGenBits(char *name, unsigned int (*genB)(void));

    void bbattery_SmallCrush(unif01_Gen *gen);

    void bbattery_Crush(unif01_Gen *gen);

    void bbattery_BigCrush(unif01_Gen *gen);

    void unif01_DeleteExternGenBits(unif01_Gen *gen);

    unif01_Gen *unif01_CreateExternGen01(char *name, double (*gen01)(void));
    void unif01_DeleteExternGen01(unif01_Gen *);
}

