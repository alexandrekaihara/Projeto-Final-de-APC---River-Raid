/*
	Universidade de Brasilia
	Instituto de Ciencias Exatas
	Departamento de Ciencia da Computacao
	Algoritmos e Programação de Computadores – 1/2018
	Aluno(a): Alexandre Mitsuru Kaihara
	Matricula: 180029690
	Turma: A
	Versão do compilador: GCC 7.3.0
	Descricao: O programa esta estruturado em seçoes com sub-divisoes de acordo com o que cada funçoo estara chamando. Por exemplo, existe uma sessao acima da main_menu() que eh o conjunto de sub-algoritmos que sera utilizado pela main_menu. Da mesma forma ha sessoes que soo conjuntos de sub-algoritmos que serao utilizados por esta funçao, facilitando, assim, a leitura e entendimento do codigo. O codigo eh de um jogo para o trabalho de APC.
*/


# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>


/* Define o intervalo de aleatoriedade do jogo */
# define RAND() ((rand()%1000 + 1)) 

/* Define qual o comando de clear dependendo do sistema */
# ifdef _WIN32
    #define CLEAR "cls"
# else
    #define CLEAR "clear"
# endif

/* Define as funções de aleatoriedade do jogo */
#ifndef _WIN32
    # include <termios.h>
    int kbhit(){
        struct termios oldt, newt;
        int ch, oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if(ch != EOF){
            ungetc(ch, stdin);
            return 1;
        }
        return 0;
    }
    int getch(void){
        int ch;
        struct termios oldt;
        struct termios newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#else
    #include <conio.h>
#endif


/* Variaveis globais do jogo */
int myy1, x1; /* Variavel que define a posiçao y e x da matriz do personagem */
int usleep();
int velocidade=60000;
int x=135;
int y=12;
int porcentagem_inimigos=25; /* Variaveis que determinam a porcentagem em mil de inimigos e combustaveis*/
int porcentagem_combustivel=10;
int porcentagem_t=4;
int porcentagem_o=1;
int T_shoot_number=5;
int O_number_of_life=10;
int rankeado=0;
typedef struct{
        char nome[11];
        int pontuacao;
}player;
player river[11]; /*struct para armazenar os dados dos jogadores do arquivo binário*/
typedef struct{
    char obstacle;
    int T_shoots;
    int O_lives;
}matriz;
matriz map[12][135];


/* Função de ordenamento do ranking (qsort)*/
int compare2 (const void* a, const void* b) {
    /*Funçãp utilizada para ordenar o vetor do ranking do qsort*/
    player *d1 = (void*)a;
    player *d2 = (void*)b;
    if (d1->pontuacao > d2->pontuacao){
        return -1;
    }
    else if (d1->pontuacao < d2->pontuacao){
        return 1;
    }
    else return 0;
}


void bem_vindo(){
    system(CLEAR);
    printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                              \033[92m____                                                                                                         \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                             \033[92m/   /  \033[91m_________                                                                                              \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                            \033[92m/   /  \033[31m/   _____/______ _____     ____   ____   /  \\    /  \\_____  _______  ______                             \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                           \033[92m/   /   \033[91m\\_____  \\ \\____  \\__  \\  _/ ___\\_/ __ \\  \\   \\/\\/   /\\__  \\ \\_  __ \\/  ___/                             \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                          \033[92m/   /    \033[31m/        \\|  |_> >/ __ \\_\\  \\___\\  ___/   \\        /  / __ \\_|  | \\/\\___ \\                              \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                         \033[92m/   /    \033[91m/_______  /|   __/(____  / \\___  >\\___  >   \\__/\\  /  (____  /|__|  /____  >                             \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                        \033[92m/   /             \033[91m\\/ |__|        \\/      \\/     \\/         \\/        \\/            \\/                              \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                        \033[92m\\   \\_____\033[92m___________________________________________________________________________                              \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                         \033[92m\\_______\033[92m______________________________________________________________________________                            \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                                                    \033[5m//Pressione qualquer tecla para continuar//\033[45m                                            \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
    printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
    getchar();
    setbuf(stdin, NULL);
}



/*Funcoes para a funcao RANKING: INICIO*/
void acessar_tabela(){
    int comando=0, sair=0, i;
    /*struct para armazenar os dados do ranking*/       
    FILE *ranking;
    if (fopen("rankingriver.bin", "rb")== NULL){
        /*Se o  arquivo não existir, ele será criado*/
        ranking=fopen("rankingriver.bin", "wb+");    
    }
    else ranking=fopen("rankingriver.bin", "rb");
    /*Carregar os dados na struct*/
    for (i=0;i<20; i++){
        fscanf(ranking, " %s %d ", river[i].nome, &river[i].pontuacao);
    }
    while(sair==0){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                \033[92mRANKING                                                                    \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m            NOME                              PONTUACAO            \033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m      \033[92m1-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[0].nome, river[0].pontuacao);
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m      \033[92m2-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[1].nome, river[1].pontuacao);
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m      \033[92m3-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[2].nome, river[2].pontuacao);
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m      \033[92m4-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[3].nome, river[3].pontuacao);
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m      \033[92m5-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[4].nome, river[4].pontuacao);
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m      \033[92m6-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[5].nome, river[5].pontuacao);
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m      \033[92m7-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[6].nome, river[6].pontuacao);
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m      \033[92m8-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[7].nome, river[7].pontuacao);
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m      \033[92m9-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[8].nome, river[8].pontuacao);
        printf("\033[40m\033[30m#\033[45m                                   \033[102m\033[92m#\033[0m     \033[92m10-%s\t\t\t\t\t%d\t\t\033[102m\033[92m#\033[45m                                   \033[40m\033[30m#\033[40m\033[0m\n", river[9].nome, river[9].pontuacao);
        printf("\033[40m\033[30m#\033[45m             \033[93m\033[1m[2] RETORNAR                               \033[0m\033[45m                                                                                   \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &comando);
        if (comando==2){
            sair=1;
        }
    }
}
/*Funcoes para a funcao RANKING: FIM*/




/*Funcoes para a função JOGAR: INICIO*/
void define_map(matriz map[][x]){
    int i, j;
    for (i=0; i<y; i++){
        for(j=0; j<x; j++){
            if((i==0) || (i==y-1)){
                map[i][j].obstacle='#';
            }
            else map[i][j].obstacle=' ';
        }
        j=0;
    }
    map[y/2][1].obstacle='+';
}

void stop(){
    int i, j;
    for(i=0;i<y;i++){
        for(j=0;j<x;j++){
            if(map[i][j].T_shoots==0){
                printf(" ");
            }
            else printf("%d", map[i][j].T_shoots);
        }   
        printf("\n");
    }
    scanf("%d", &i);
}


void comando(matriz map[][x], int *combustivel, int *kills){
    int i , j, controle=1;
    char comando;
    if (kbhit()==1){
        comando = getch();
        for(i=0; i<y; i++){
            for(j=0; j<x; j++){
                if ((map[i][j].obstacle=='+') && (controle==1)){
                    /*Comando para descer o +*/
                    if (comando=='s'){
                        if (i<y-2){
                            controle=0;
                            map[i][j].obstacle=' ';
                            map[i+1][j].obstacle='+';
                            *combustivel+=-2;
                        }
                    }
                    else if (comando=='w'){
                        /*Comando para subir o +*/
                        if (i>1){
                            controle=0;
                            map[i][j].obstacle=' ';
                            map[i-1][j].obstacle='+';
                            *combustivel+=-2;
                        }
                    }
                    else if (comando=='p'){
                        /*Comando de tiro*/
                        *combustivel+=-3;
                        if ((map[myy1][x1].obstacle=='x') || (map[myy1][x1].obstacle=='f') || (map[myy1][x1].obstacle=='T') || (map[myy1][x1].obstacle=='<')){
                            /* Evita bug de quando houver um obstaculo imediatamente do lado do +, eles nao sumam e o tiro assuma o lugar deles*/
                            map[myy1][x1].obstacle=' ';
                            if (map[myy1][x1].obstacle=='x'){
                                (*kills)++;
                            }
                        }
                        else map[myy1][x1].obstacle='>';
                    }
                    else if (comando=='q'){
                        /*Comando de tiro*/
                        stop();
                    }
                }
                if ((comando!='p') && (comando!='s') && (comando!='w')){
                        printf("Comando inválido!\n");
                }
            }
            j=0;
        }
    }
}


int inimigos(matriz map[][x]){
    /* Funcao para gerar combustivel e inimigos para o update_screen */
    int k;
    k=RAND(); 
    if (k<=porcentagem_inimigos){
        return 'x';
    }
    else if ((k>porcentagem_inimigos) && (k<=porcentagem_combustivel+porcentagem_inimigos)){
        return 'f';
    }
    else if ((k>porcentagem_inimigos+porcentagem_combustivel) && (k<=porcentagem_combustivel+porcentagem_inimigos+porcentagem_o)){
        return 'O';
    }
    else if ((k>porcentagem_inimigos+porcentagem_combustivel+porcentagem_o) && (k<=porcentagem_combustivel+porcentagem_inimigos+porcentagem_o+porcentagem_t)){
        return 'T';
    }

    else return ' ';
}


void update_map(matriz map[][x], int *gameover, int *kills, int *score, int *combustivel, int *contscore){
    int i, j, apareceu_x=0, apareceu_f=0, apareceu_O=0, apareceu_T=0, a, b;
    (*combustivel)--;
    (*contscore)++;
    *score=(*kills)*50+*contscore;
    if (*combustivel<0){
        *gameover=1;
    }
    for (i=0;i<y; i++){
        for(j=1; j<x; j++){
            if ((j==x-1) && ((i!=0) && (i!=y-1))){
                /*Geracao de inimigos*/
                if ((apareceu_x==0) || (apareceu_f==0) || (apareceu_O=0) || (apareceu_T=0) ){
                    map[i][j].obstacle=inimigos(map);
                    map[i][j].T_shoots=T_shoot_number;
                    map[i][j].O_lives=O_number_of_life;
                    /*Codigo para evitar que apareçam mais de 1 inimigo e/ou fuel por coluna:INICIO*/
                    if (map[i][j].obstacle=='x'){
                        apareceu_x++;
                        if (apareceu_x>1){
                            map[i][j].obstacle=' ';
                        }
                    }
                    if (map[i][j].obstacle=='f'){
                        apareceu_f++;
                        if (apareceu_f>1){
                            map[i][j].obstacle=' ';
                        }
                    }
                    if (map[i][j].obstacle=='T'){
                        apareceu_T++;
                        if (apareceu_T>1){
                            map[i][j].obstacle=' ';
                        }
                    }
                    if (map[i][j].obstacle=='O'){
                        apareceu_O++;
                        if (apareceu_O>1){
                            map[i][j].obstacle=' ';
                        }
                    }
                    /*Código para evitar que apareçam mais de 1 inimigo e/ou fuel e/ou O e/ou T por coluna:INICIO*/
                }
            }
            if (map[i][j].obstacle=='+'){
                /*Determinação da posicao do personagem*/
                x1=j+1;
                myy1=i;
            }
            
            /*Movimentação dos inimigos e combustivel e tiro e poderes: INICIO*/
            else if (map[i][j].obstacle=='T'){  
                if (map[i][j-1].obstacle=='>'){
                    map[i][j].obstacle=' ';
                    map[i][j-1].obstacle=' ';
                }
                else if (map[i][j-1].obstacle=='+'){
                    *gameover=1;  
                    myy1=i;
                    x1=j-1;  
                }
                else if (j==1){
                    map[i][j].obstacle=' ';
                }
                else {
                    map[i][j-1].obstacle='T';
                    map[i][j].obstacle=' ';
                    /* Movimenta também o valor de tiros remanescentes */
                    if((map[i][j].T_shoots>0) && ((*score+T_shoot_number+i)%100==1)){
                        /* Verifica de ainda o T possui tiros disponíveis e permite atirar */    
                        if(j>1){
                            map[i][j].T_shoots--;
                            if(map[i][j-2].obstacle==' '){
                                map[i][j-2].obstacle='<';
                            }
                            else if(map[i][j-3].obstacle==' '){
                                map[i][j-3].obstacle='<';
                            }
                            else if(map[i][j-4].obstacle==' '){
                                map[i][j-4].obstacle='<';
                            }
                        }
                    }
                    map[i][j-1].T_shoots=map[i][j].T_shoots;
                    map[i][j].T_shoots=0;
                }
            }

            else if (map[i][j].obstacle=='O'){
                if (map[i][j-1].obstacle=='+'){
                    map[i][j].obstacle=' ';    
                }
                else if (map[i][j-1].obstacle=='>'){
                    if (map[i][j].O_lives>1){
                        map[i][j].O_lives--;
                        map[i][j-1].obstacle='O';
                        map[i][j].obstacle=' ';
                        map[i][j-1].O_lives=map[i][j].O_lives;
                        map[i][j].O_lives=0;
                    }
                    else if (map[i][j].O_lives==1){
                        /* Se o O tiver com vida zero, ele some com o tiro e mata cada x do mapa */
                        map[i][j].obstacle=' ';
                        map[i][j-1].obstacle=' ';
                        printf("\n");
                        for(a=0; a<y; a++){
                            for(b=0; b<x; b++){
                                if(map[a][b].obstacle=='x'){
                                    *(contscore)+=10;
                                    map[a][b].obstacle=' ';
                                }
                            }
                        }
                    }
                }
                else if (j==1){
                    map[i][j].obstacle=' ';
                }
                else if(map[i][j-1].obstacle==' '){
                    map[i][j-1].obstacle='O';
                    map[i][j].obstacle=' ';
                    map[i][j-1].O_lives=map[i][j].O_lives;
                    map[i][j].O_lives=0;
                }
            }


            else if (map[i][j].obstacle=='x'){
                if (map[i][j-1].obstacle=='>'){
                    map[i][j].obstacle=' ';
                    map[i][j-1].obstacle=' ';
                    (*kills)++;
                }
                else if (map[i][j-1].obstacle=='+'){
                    *gameover=1;  
                    myy1=i;
                    x1=j-1;  
                }
                else{
                    map[i][j-1].obstacle='x';
                    map[i][j].obstacle=' ';
                }
            }
            
            else if (map[i][j].obstacle=='f'){
                if (map[i][j-1].obstacle=='+'){
                    *combustivel+=40;
                    map[i][j].obstacle=' ';
                }
                else if (map[i][j-1].obstacle=='>'){
                    map[i][j].obstacle=' ';
                    map[i][j-1].obstacle=' ';
                }
                else{
                        map[i][j-1].obstacle='f';
                    map[i][j].obstacle=' ';
                }
            }

            else if (map[i][j].obstacle=='<'){
                if (map[i][j-1].obstacle=='>'){
                    map[i][j].obstacle=' ';
                    map[i][j-1].obstacle=' ';
                }
                else if (map[i][j-1].obstacle=='+'){
                    *gameover=1;    
                    myy1=i;
                    x1=j-1-1;
                }
                else if (map[i][j-2].obstacle=='+'){
                    /* evita que o tiro do T apague o + por andar 2 tiles por iteracao */
                    if(map[i][j-1].obstacle==' '){
                        map[i][j].obstacle=' ';
                        map[i][j-1].obstacle='<';
                    }
                }
                /* Se chegar no fim do mapa, o tiro some*/
                else if(j<=1){
                    map[i][j].obstacle=' ';
                } 
                /* Se chegar no fim do mapa, o tiro some*/
                else if (j==2){
                    map[i][j-1].obstacle='<';
                    map[i][j].obstacle=' ';
                }
                else if (j==3){
                    map[i][j-2].obstacle='<';
                    map[i][j].obstacle=' ';
                }
                else if (map[i][j-2].obstacle=='>'){
                    /* evita que o tiro do T apague o > por andar 2 tiles por iteracao */
                    map[i][j].obstacle=' ';
                    map[i][j-1].obstacle='<';
                }
                else if (map[i][j-2].obstacle!=' '){
                    if(map[i][j-3].obstacle==' '){
                        map[i][j].obstacle=' ';
                        map[i][j-3].obstacle='<';
                    }
                    else if (map[i][j-3].obstacle!=' '){
                        if(map[i][j-4].obstacle==' '){
                            map[i][j-4].obstacle='<';
                            map[i][j].obstacle=' ';
                        }
                    }
                }
                else{
                    map[i][j-2].obstacle='<';
                    map[i][j].obstacle=' ';
                }
            }

            else if (map[i][j].obstacle=='>'){
                /*Movimentação do tiro*/
                if (j==x-1){
                    /*Identificação do limite do mapa*/
                    map[i][j].obstacle=' ';
                }
                else if(map[i][j+1].obstacle==' ') {
                    map[i][j+1].obstacle='>';
                    map[i][j].obstacle=' ';
                    /*x2 e y2 é a posicao do tiro*/
                    j++;
                }
            }
            
        }
    }
}


void print_map(matriz map[][x], int score, int combustivel){
    /* Serve para realizar a movimentacao dos caracteres da matriz*/
    int i, j;
    printf("\033[30m\033[40m#######################################################################################################################################\033[45m\n");
    printf("                                                                                                                                      \033[40m\033[30m#\033[0m\n");
    printf("\033[45m  \033[33mCOMBUSTÍVEL = \033[36m%d \033[33mLITROS     SCORE: \033[36m%d                                                                                              \033[40m\033[30m#\033[0m\n", combustivel, score);
    printf("\033[45m                                                                                                                                      \033[40m\033[30m#\033[0m\n");
    for (i=0;i<y; i++){
        for(j=1; j<x; j++){
            if (map[i][j].obstacle=='+'){
                printf("\033[99m+\033[0m");
            }
            else if (map[i][j].obstacle=='#'){
                printf("\033[30m\033[40m#\033[0m");
            }
            else if (map[i][j].obstacle=='f'){
                printf( "\033[92m%c\033[0m", map[i][j].obstacle);
            }
            else if (map[i][j].obstacle=='x'){
                printf("\033[91m%c\033[0m", map[i][j].obstacle);
            }
            else if (map[i][j].obstacle=='>'){
                printf("\033[96m%c\033[0m", map[i][j].obstacle);
            }
            else if (map[i][j].obstacle=='<'){
                printf("\033[95m%c\033[0m", map[i][j].obstacle);
            }
            else if (map[i][j].obstacle=='T'){
                printf("\033[1m\033[93m%c\033[0m", map[i][j].obstacle);
            }
            else if (map[i][j].obstacle=='O'){
                printf("\033[1m\033[94m%c\033[0m", map[i][j].obstacle);
            }
            else printf("%c", map[i][j].obstacle);
        }
        printf("\033[40m\033[30m#\033[0m\n");
    }
    printf("\033[45m");
    printf("                                                                                                                                      \033[40m\033[30m#\033[0m\n");
    printf("\033[45m                                                                                                                         @RIVER Games \033[40m\033[30m#\033[0m\n");
    printf("\033[30m\033[40m#######################################################################################################################################\033[0m\n");
}


int game_over(int score, int combustivel){
    int option=-1;
    while((option!=1) && (option!=2)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                            \033[91m\033[1m          ____  _____     _____    ____     ____  ___  __  ____  _______              \033[0m\033[45m                         \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                            \033[91m\033[1m         / ___\\ \\__  \\   /     \\ _/ __ \\   /  _ \\ \\  \\/ /_/ __ \\ \\_  __ \\  \033[0m\033[45m                                    \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                            \033[91m\033[1m        / /_/  > / __ \\_|  Y Y  \\   ___/  (  <_> ) \\   / \\  ___/  |  | \\/        \033[0m\033[45m                              \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                            \033[91m\033[1m        \\___  / (____  /|__|_|  / \\___  >  \\____/   \\_/   \\___  > |__|           \033[0m\033[45m                              \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                            \033[91m\033[1m       /_____/       \\/       \\/      \\/                      \\/                  \033[0m\033[45m                             \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");

        if (combustivel<=0){
            printf("\033[40m\033[30m#\033[45m                                            \033[91m\033[1mVOCÊ FICOU SEM COMBUSTIVEL! VOCE FEZ %d PONTOS!!!\033[0m\033[45m                                             \033[40m\033[30m#\033[40m\033[0m\n",score);
        }
        else{
            printf("\033[40m\033[30m#\033[45m                      \033[91m\033[1mVOCE FOI INTERCEPTADO POR UM INIMIGO!!! TENHA CUIDADO NA PROXIMA VEZ!  VOCE FEZ %d PONTOS!!!\033[0m\033[45m                         \033[40m\033[30m#\033[40m\033[0m\n", score);
        }
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[1] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL); 
    }
    return option;
}

void register_match(int score){
    int i;
    FILE *ranking;
    if (fopen("rankingriver.bin", "rb")== NULL){
        /*Se o  arquivo não existir, ele será criado*/
        ranking=fopen("rankingriver.bin", "wb+");    
    }
    else ranking=fopen("rankingriver.bin", "rb");
    /*Carregar os dados na struct*/
    for (i=0;i<10; i++){
        fscanf(ranking, " %s %d ", river[i].nome, &river[i].pontuacao);
    }   
    fclose(ranking);
    FILE *ranking2;
    ranking2=fopen("rankingriver.bin", "wb");
    printf("Digite o seu nome:\n"); 
    if (score > river[9].pontuacao){
        /*Se o valor do score for maior que o menor do ranking, ele substitui o menor*/
        river[9].pontuacao = score;
        for(i=0;i<10;i++){
            river[9].nome[i] = river[10].nome[i];
        }
    }
    qsort (river, 10, sizeof(player), compare2);
    for (i=0;i<9; i++){
        fprintf(ranking2, " %s %d ", river[i].nome, river[i].pontuacao);
    }
    fclose(ranking2);
}
/*Funcoes para a função JOGAR: FIM*/




/*Funcoes para a função CONFIGURACOES: INICIO */
void velocidade_personalizada(){
    int controle=0;
    do{
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                             \033[1m\033[93mVELOCIDADE DO MAPA                                                            \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[3] \033[1m\033[33mFACIL                                                                                \033[94m%d\033[0m\033[45m                               \033[40m\033[30m#\033[40m\033[0m\n",velocidade);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[4] \033[1m\033[33mMEDIO                                                                                                                    \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[5] \033[1m\033[33mDIFICIL                                                                                                                  \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[6] \033[1m\033[33mOUTRO    DIGITE O VALOR:    (40000-70000 ms)                                                                             \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &controle);
        if ((controle>=40000) && (controle<=70000)){
            velocidade=controle;
        }
        setbuf(stdin, NULL); 
    }while ((controle<40000) || (controle>70000));
}


void velocidade_do_mapa(){
    int option=-1, retornar=0;
    while(((option!=2) && (option!=3) && (option!=4) && (option!=5) && (option!=6)) && (retornar==0)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                             \033[1m\033[93mVELOCIDADE DO MAPA                                                            \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[3] \033[1m\033[33mFACIL                                                                                \033[94m%d\033[0m\033[45m                               \033[40m\033[30m#\033[40m\033[0m\n",velocidade);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[4] \033[1m\033[33mMEDIO                                                                                                                    \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[5] \033[1m\033[33mDIFICIL                                                                                                                  \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[6] \033[1m\033[33mOUTRO                                                                                                                    \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL); 
        if (option==2){
            retornar=1;
        }
        else if (option==3){
            velocidade=60000;
        }
        else if (option==4){
            velocidade=45000;
        }
        else if (option==5){
            velocidade=40000;
        }
        else if (option==6){
            velocidade_personalizada();
        }
        option=-1;  
    }
}


void tamanho_personalizado(){
    int controle=0, controle2=0;
    do{
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                             \033[1m\033[93mTAMANHO DO MAPA                                                               \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[3] \033[1m\033[33mFACIL                                                                              \033[94m%d \033[93mX \033[94m%d\033[0m\033[45m                              \033[40m\033[30m#\033[40m\033[0m\n",x ,y);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[4] \033[1m\033[33mMEDIO                                                                                                                    \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[5] \033[1m\033[33mDIFICIL                                                                                                                  \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[6] \033[1m\033[33mOUTRO         Digite o valor: X =   (50<=x<=135)   Y =   (6<=y<=10)                                                      \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &controle);
        if ((controle>=50) && (controle<=135)){
            x=controle;
        }
        scanf("%d", &controle2);
        if ((controle2>=6) && (controle2<=10)){
            y=controle2;
        }
        setbuf(stdin, NULL); 
    }while (((controle<50) || (controle>135)) && ((controle2<6) || (controle2>10)));
}


void tamanho_do_mapa(){
    int option=-1, retornar=0;
    while(((option!=2) && (option!=3) && (option!=4) && (option!=5) && (option!=6)) && (retornar==0)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                             \033[1m\033[93mTAMANHO DO MAPA                                                               \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[3] \033[1m\033[33mFACIL                                                                              \033[94m%d \033[93mX \033[94m%d\033[0m\033[45m                              \033[40m\033[30m#\033[40m\033[0m\n",x ,y);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[4] \033[1m\033[33mMEDIO                                                                                                                    \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[5] \033[1m\033[33mDIFICIL                                                                                                                  \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[6] \033[1m\033[33mOUTRO                                                                                                                    \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL); 
        if (option==2){
            retornar=1;
        }
        else if (option==3){
            x=135;
            y=12;
        }
        else if (option==4){
            x=100;
            y=12;
        }
        else if (option==5){
            x=50;
            y=12;
        }
        else if (option==6){
            tamanho_personalizado();
        }
        option=-1;  
    }
}   


void porcentagem_obstaculos(){
    int option=-1, retornar=0;
    while(((option!=2) && (option!=3) && (option!=4) && (option!=5)) && (retornar==0)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m               \033[1m\033[33m                                          PORCENTAGEM DE F E X                                                              \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[33m[3]FACIL                                                                                                                     \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                              \033[1m\033[91mF = (%d)   X = (%d)\033[0m\033[45m                                          \033[40m\033[30m#\033[40m\033[0m\n", porcentagem_inimigos, porcentagem_combustivel);
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[33m[4]MEDIO                                                                                                                     \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[33m[5]DIFICIL                                                      \033[1m\033[91mO = (%d)   T = (%d)\033[0m\033[45m                                            \033[0m\033[40m\033[30m#\033[40m\033[0m\n", porcentagem_o, porcentagem_t);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL); 
        if (option==2){
            retornar=1;
        }
        else if (option==3){
            porcentagem_inimigos=25;
            porcentagem_combustivel=15;
            porcentagem_o=2;
            porcentagem_t=4;
        }
        else if (option==4){
            porcentagem_inimigos=35;
            porcentagem_combustivel=20;
            porcentagem_t=6;
            porcentagem_o=1;
        }
        else if (option==5){
            porcentagem_inimigos=45;
            porcentagem_combustivel=20;
            porcentagem_t=7;
            porcentagem_o=1;
        }
        option=-1;  
    }
}   


void reset_config(){
    char option=' ';
    while((option!='s') && (option!='n')){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                             \033[1m\033[93mCONFIGURACOES                                                                 \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[3] \033[1m\033[33mTAMANHO MAPA                                                                       \033[94m%d \033[93mX \033[94m%d\033[0m\033[45m                              \033[40m\033[30m#\033[40m\033[0m\n",x ,y);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[4] \033[1m\033[33mNPCs                                                                                                                     \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[5] \033[1m\033[33mMODO RANKEADO                                                                      \033[91m%d\033[0m\033[45m                                     \033[40m\033[30m#\033[40m\033[0m\n", rankeado);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[6] \033[1m\033[33mRESET CONFIGURACOES                                                                VOCE TEM CERTEZA? [s/n]               \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%c", &option);
        setbuf(stdin, NULL);
        if (option=='s'){
            velocidade=60000;
            y=12;
            x=135;
            porcentagem_inimigos=25;
            porcentagem_combustivel=10;
            porcentagem_o=1;
            porcentagem_t=4;
            O_number_of_life=10;
            T_shoot_number=5;
        }
    }       
}


void municaoT(){
    int option=-1, retornar=0;
    while(((option!=2) && (option!=3) && (option!=4) && (option!=5)) && (retornar==0)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m               \033[1m\033[33m                                          NUMERO DE TIROS DE T                                                              \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[33m[3]FACIL                                                                                                                     \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                  \033[1m\033[91mT > %d\033[0m\033[45m                    \033[40m\033[30m#\033[40m\033[0m\n", T_shoot_number);
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[33m[4]MEDIO                                                                                                                     \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[33m[5]DIFICIL                                                                                                                   \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL); 
        if (option==2){
            retornar=1;
        }
        else if (option==3){
            T_shoot_number=1;
        }
        else if (option==4){
            T_shoot_number=3;
        }
        else if (option==5){
            T_shoot_number=10;
        }
        option=-1;  
    }
}
 

void vidaO(){
    int option=-1, retornar=0;
    while(((option!=2) && (option!=3) && (option!=4) && (option!=5)) && (retornar==0)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m               \033[1m\033[33m                                          NUMERO DE TIROS DE O                                                              \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[33m[3]FACIL                                                                                                                     \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                  \033[1m\033[96m %d S2\033[0m\033[45m                   \033[40m\033[30m#\033[40m\033[0m\n", O_number_of_life);
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[33m[4]MEDIO                                                                                                                     \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[33m[5]DIFICIL                                                                                                                   \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL); 
        if (option==2){
            retornar=1;
        }
        else if (option==3){
            O_number_of_life=3;
        }
        else if (option==4){
            O_number_of_life=5;
        }
        else if (option==5){
            O_number_of_life=10;
        }
        option=-1;  
    }
}


void npcs(){
    int option=-1, retornar=0;
    while(((option!=2) && (option!=3) && (option!=4) && (option!=5) && (option!=6)) && (retornar==0)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                             \033[1m\033[93mNPC's                                                                         \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[3] \033[1m\033[33mPORCENTAGEM OBSTACULOS                                                                                                   \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[4] \033[1m\033[33mVELOCIDADE                                                                         \033[96m>>>>> %d \033[0m\033[45m                          \033[40m\033[30m#\033[40m\033[0m\n", velocidade);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[5] \033[1m\033[33mVIDA O                                                                            \33[1m\33[96m %d S2           \033[0m\033[45m                      \033[40m\033[30m#\033[40m\033[0m\n", O_number_of_life);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[6] \033[1m\033[33mMUNICAO T                                                                         \33[1m\33[96m T > %d            \033[0m\033[45m                     \033[0m\033[40m\033[30m#\033[40m\033[0m\n", T_shoot_number);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL);
        if (option==2){
            retornar=1;
        }
        else if (option==3){
            porcentagem_obstaculos();   
        }
        else if (option==4){
                velocidade_do_mapa();
        }
        else if (option==5){
                vidaO();
        }
        else if (option==6){
                municaoT();
        }
        option=-1;
    }
}

void salvaralteracoes(){
    if (rankeado==1){
        velocidade=60000;
        x=135;
        y=12;
        porcentagem_inimigos=25; /* Variaveis que determinam a porcentagem em mil de inimigos e combustaveis*/
        porcentagem_combustivel=10;
        porcentagem_t=4;
        porcentagem_o=1;
        T_shoot_number=5;
        O_number_of_life=10;
    }
    FILE *config2;
    config2=fopen("config.txt", "w");
    fprintf(config2,"%d %d %d %d %d %d %d %d %d", velocidade, x, y, porcentagem_inimigos, porcentagem_combustivel, porcentagem_t, porcentagem_o, T_shoot_number, O_number_of_life);
    fclose(config2);
}
/*Funcoes para a função CONFIGURACOES: FIM */






/*Funcoes a serem utilizadas pela MAIN_MENU: INICIO*/
void sair(){
}


int jogar(matriz map[][x]){
    /* A variavel combustivel esta declarado aqui porque necessita atualizacao para o valor inicial para cada restart, o mesmo para o score e kills*/
    srand(time(0));
    int gameover=0, kills=0, score=0, combustivel=400, contscore=0, controle=0, i;
    define_map(map);
    if(rankeado==1){
        /* Le o nome e verifica se tem mais de 10 caracteres*/
        while(controle==0){
            /*Se o nome digitado tiver main que 5 caracteres, ele pede para ler de novo*/
            system(CLEAR);
            printf("Digite seu nome:\n");
            scanf(" %s", river[10].nome);
            for(i=0; river[10].nome[i]!='\0'; i++){
            }
            if ((i>0) && (i<11)){
                controle=1;
            }
            else {
                printf("Digite novamente um nome entre 1 a 10 caracteres\n");
                usleep(1000000);
            }
            getchar();
            setbuf(stdin, NULL);
        }
    }
    while(gameover==0){
        system(CLEAR);
        comando(map, &combustivel, &kills);
        update_map(map, &gameover, &kills, &score, &combustivel, &contscore);
        print_map(map, score, combustivel);
        usleep(velocidade);
    }
    if(rankeado==1){
        register_match(score);
    }
    return game_over(score, combustivel);
}


int configuracoes(){
    int option=-1, retornar=0;
    while(((option!=2) && (option!=3) && (option!=4) && (option!=5) && (option!=6)) && (retornar==0)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                             \033[1m\033[93mCONFIGURACOES                                                                 \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[3] \033[1m\033[33mTAMANHO MAPA                                                                       \033[94m%d \033[93mX \033[94m%d\033[0m\033[45m                              \033[40m\033[30m#\033[40m\033[0m\n",x ,y);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[4] \033[1m\033[33mNPCs                                                                                                                     \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[5] \033[1m\033[33mMODO RANKEADO                                                                      \033[91m%d\033[0m\033[45m                                     \033[40m\033[30m#\033[40m\033[0m\n", rankeado);
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[1m\033[93m[6] \033[1m\033[33mRESET CONFIGURACOES                                                                                                      \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[2] RETORNAR\033[0m\033[45m                                                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL);
        if (option==2){
            retornar=1;
            salvaralteracoes();
        }
        else if (option==3){
            tamanho_do_mapa();
        }
        else if (option==4){
            npcs();   
        }
        else if (option==5){
            if (rankeado==1){
                rankeado=0;
            }
            else rankeado=1;
        }
        else if (option==6){
            reset_config();
        }
        option=-1;
    }
    return 1;
}


int ranking(){
    acessar_tabela();
    return 1;
}


int instrucoes(matriz map[][x]){
    int option=-1;
    while((option!=1) && (option!=2)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                             \033[91m\033[1mSPACE INVADERS\033[0m\033[45m                                                                \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93mO OBJETIVO DO JOGO EH CONDUZIR A NAVE E EVITAR OS INIMIGOS IDENTIFICADOS EM VERMELHO COMO 'X' E MANTER A NAVE                \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93mSEMPRE COM COMBUSTIVEL INDICADO EM VERDE COMO 'F'. EH POSSIVEL ATIRAR NOS INIMIGOS PARA ANIQUILA-LOS, MAS CUI                \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                        \033[93mDADO, OS TIROS PODEM DEIXAR VOCE SEM COMBUSTIVEL TAMBEM!                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[91m\033[1mCOMANDOS:\033[91m\033[0m\033[45m                                                                                                                    \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                     \033[91m\033[1mW :\033[0m\033[45m \033[93mDESLOCAR A NAVE PARA CIMA;                                                        \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                     \033[92m\033[1mS :\033[0m\033[45m \033[93mDESLOCAR A NAVE PARA BAIXO;                                                       \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                     \033[94m\033[1mP :\033[0m\033[45m \033[93mATIRAR;                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[0m\033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m              \033[93m\033[1m[1] RETORNAR           [2] SAIR\033[0m\033[45m                                                                                              \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL); 
    }
    return option;
}
/*Funcoes a serem utilizadas pela MAIN_MENU: FIM*/






int main_menu(matriz map[][x]){
    /* Menu principal para acessar configuracoes do jogo */
    int option=-1, option_funcoes=-1;
    while ((option!=1) && (option!=2) && (option!=3) && (option!=4) && (option!=5)){
        system(CLEAR);
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m        \033[1m\033[93m[1] \033[1m\033[33mJOGAR\033[0m\033[45m                          \033[32m____                                                                                            \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                          \033[32m/   /  \033[5m\033[31m_________                                                                                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m        \033[1m\033[93m[2] \033[1m\033[33mCONFIGURACOES\033[0m\033[45m                \033[32m/   /  \033[5m\033[31m/   _____/______ _____     ____   ____   /  \\    /  \\_____  _______  ______                \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                        \033[32m/   /   \033[31m\033[5m\\_____  \\ \\____  \\__  \\  _/ ___\\_/ __ \\  \\   \\/\\/   /\\__  \\ \\_  __ \\/  ___/                \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m        \033[1m\033[93m[3] \033[1m\033[33mINSTRUCOES\033[0m\033[45m                 \033[32m/   /    \033[5m\033[31m/        \\|  |_> >/ __ \\_\\  \\___\\  ___/   \\        /  / __ \\_|  | \\/\\___ \\                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                      \033[32m/   /    \033[31m\033[5m/_______  /|   __/(____  / \\___  >\\___  >   \\__/\\  /  (____  /|__|  /____  >                \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m        \033[1m\033[93m[4] \033[1m\033[33mRANKING\033[0m\033[45m                  \033[32m/   /             \033[5m\033[31m\\/ |__|        \\/      \\/     \\/         \\/        \\/            \\/                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                     \033[32m\\   \\_____\033[32m___________________________________________________________________________                 \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m        \033[1m\033[93m[5] \033[1m\033[33mSAIR\033[0m\033[45m                      \033[32m\\_______\033[32m______________________________________________________________________________               \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                                           \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#\033[45m                                                                                                                              @RIVER Games \033[40m\033[30m#\033[40m\033[0m\n");
        printf("\033[40m\033[30m#############################################################################################################################################\033[40m\033[0m\n");
        scanf("%d", &option);
        setbuf(stdin, NULL); 
        switch(option){
            case 1: option_funcoes=jogar(map); break;
            case 2: option_funcoes=configuracoes(); break;
            case 3: option_funcoes=instrucoes(map); break;
            case 4: option_funcoes=ranking(); break;
            case 5: sair(); break;
        }
    }
    return option_funcoes;
}


int main (){
    int option=1;
    bem_vindo();
    FILE *config;
    config=fopen("config.txt", "r");
    if(config != NULL){
        fscanf(config,"%d %d %d %d %d %d %d %d %d", &velocidade, &x, &y, &porcentagem_inimigos, &porcentagem_combustivel, &porcentagem_t, &porcentagem_o, &T_shoot_number, &O_number_of_life);
        fclose(config); 
    }
    else{
        FILE *config2;
        config2=fopen("config.txt", "w");
        fprintf(config2,"%d %d %d %d %d %d %d %d %d", velocidade, x, y, porcentagem_inimigos, porcentagem_combustivel, porcentagem_t, porcentagem_o, T_shoot_number, O_number_of_life);
        fclose(config2);
    }
    /*Eh para evitar que o programa necessite ser executado novamente caso o usuario queira retornar ao menu principal*/
    while(option==1){
        option=main_menu(map);
    }
    return 0;
}