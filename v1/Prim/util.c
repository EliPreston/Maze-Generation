// Helper function to generate a random number between min and max
int genRandNum(int min, int max) {
    
    unsigned int rand_seed;    
    FILE *f;
    
    f = fopen("/dev/urandom", "r");
    fread(&rand_seed, sizeof(rand_seed), 1, f);
    fclose(f);

    srand(rand_seed);    
    return rand() % (max-1) + min;
}

// printf("%d, %d\n", genRandNum(0, height-1), genRandNum(0, width-1));
// printf("%d, %d\n", genRandNum(0, height-1), genRandNum(0, width-1));