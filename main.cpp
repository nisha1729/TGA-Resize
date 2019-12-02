#include "halfsize.cpp"

int main(int argc, char **argv)
{
    tga p;
    char *in, *out;
    if (argc!=3)
        printf("\nInvalid input. Please try again.\n");
    else{        
        in = argv[1];
        out = argv[2];
        p.resizeTGA(in, out);
    }
    return 0;
}