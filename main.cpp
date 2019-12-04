#include "halfsize.cpp"

int main(int argc, char **argv)
// int main()
{
    tga p;
    char *in, *out;
    if (argc!=3)
        printf("\nInvalid input. Please try again.\n");
    else{        
        in = argv[1];  //  File name of the original image
        out = argv[2]; // File name of the resized image
        p.resizeTGA(in, out);
    }
    return 0;
}