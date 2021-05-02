#include <stdio.h>
#include <string.h>
#define filein "..\\text\\log.txt"
#define MAX_CHAR_CORSA 30
#define MAX_LENGTH_DATA 1000

typedef enum {
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_errore,
    r_fine
} comando_e;

typedef struct corsa{
    char code[MAX_CHAR_CORSA+1];
    char start[MAX_CHAR_CORSA+1];
    char dest[MAX_CHAR_CORSA+1];
    char timeStart[MAX_CHAR_CORSA+1];
    char timeEnd[MAX_CHAR_CORSA+1];
    int date[3];
    int delay;
} t_corsa;

typedef struct request{
    char code[MAX_CHAR_CORSA+1];
    char start[MAX_CHAR_CORSA+1];
    char dest[MAX_CHAR_CORSA+1];
    int dateStart[3];
    int dateEnd[3];
    int delayMin;           
} t_request;

comando_e leggiComando();

int query(t_request req, t_corsa data[], int lenData, int res[]);

int menuParola(comando_e cmd, t_corsa data[MAX_LENGTH_DATA], int lenData);

int handleFileInput(char fileName[], t_corsa data[]);

int dateBetween(int date[3], int start[3], int end[3]);

void printMenu();

int main(){
    int finished, status, lenData;
    comando_e command;
    t_corsa data[MAX_LENGTH_DATA];

    lenData = handleFileInput(filein, data);

    finished = 0;
    printMenu();
    while(!finished){
        printf("\nInsersici comando: ");

        command = leggiComando();
        if(command == r_fine)                   finished=1;
        
        status = menuParola(command, data, lenData);
        
        if((command == r_errore || status == 1) && !finished)   printf("Errore di acquisizione\n");
    }

    return 0;
}

void printMenu(){
    printf("\nElenco comandi menu: \n\
    1.elencare tutte le corse partite in un certo intervallo di date [date aaaa/mm/gg aaaa/mm/gg]\n\
    2.elencare tutti le corse partite da una certa fermata [partenza nome_citta]\n\
    3.elencare tutti le corse aventi una data destinazione [capolinea nome_citta]\n\
    4.elencare tutte le corse che hanno raggiunto la destinazione in ritardo,in un certo intervallo di date [ritardo aaaa/mm/gg aaaa/mm/gg]\n\
    5.elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta [ritardo_tot codice]\n\n"
    );
}

comando_e leggiComando(){
    char word[MAX_CHAR_CORSA];
    comando_e command;

    scanf("%s", word);
    command = r_errore;
    if(strcmp(word, "date") == 0)              command = r_date;
    if(strcmp(word, "partenza") == 0)          command = r_partenza;
    if(strcmp(word, "capolinea") == 0)         command = r_capolinea;
    if(strcmp(word, "ritardo") == 0)           command = r_ritardo;
    if(strcmp(word, "ritardo_tot") == 0)       command = r_ritardo_tot;
    if(strcmp(word, "fine") == 0)              command = r_fine;

    return command;    
}

int menuParola(comando_e cmd, t_corsa data[MAX_LENGTH_DATA], int lenData){
    t_request req;
    t_corsa corsa;
    int responseList[MAX_LENGTH_DATA], lenResponse, i, delayTot;
    
    memset(&req, 0, sizeof(req));
    switch(cmd){
        case r_partenza:        scanf("%s", req.start);      break;
        case r_capolinea:       scanf("%s", req.dest);     break;
        case r_ritardo_tot:     scanf("%s", req.code);      break;

        case r_ritardo:         req.delayMin = 1;
        case r_date:
            scanf("%d/%d/%d", &req.dateStart[0], &req.dateStart[1], &req.dateStart[2]);
            scanf("%d/%d/%d", &req.dateEnd[0], &req.dateEnd[1], &req.dateEnd[2]);
            break;

        case r_errore:
        default:             return 1;  //Error handling
    }

    lenResponse = query(req, data, lenData, responseList);

    if(lenResponse > 0){
        if(cmd == r_ritardo_tot){

            for(i=0 , delayTot=0 ; i<lenResponse ; i++){
                corsa = data[responseList[i]];
                delayTot += corsa.delay;
            }
            printf("\nRitardo complessivo relativo a %s: %d\n", corsa.code, delayTot);

        } else {

            printf("\n");
            for(i=0 ; i<lenResponse ; i++){
                corsa = data[responseList[i]];
                printf("corsa %d: %s Da: %-15s A: %-15s Il: %d/%02d/%02d Partenza: %s Arrivo: %s Ritardo: %d\n", 
                        i, corsa.code, corsa.start, corsa.dest, corsa.date[0], corsa.date[1], corsa.date[2],
                        corsa.timeStart, corsa.timeEnd, corsa.delay);
            }

        }
    }

    return 0;
}

int query(t_request req, t_corsa data[], int lenData, int res[]){
    int i, indexRes, valid, validDate;

    for(i=0 , indexRes=0 ; i<lenData ; i++){      
        
        valid=1;
        validDate = dateBetween(data[i].date, req.dateStart, req.dateEnd);
        if(req.code[0] != '\0' && strcmp(data[i].code, req.code) != 0)          valid=0;
        if(req.start[0] != '\0' && strcmp(data[i].start, req.start) != 0)       valid=0;
        if(req.dest[0] != '\0' && strcmp(data[i].dest, req.dest) != 0)          valid=0;
        if(req.dateStart[0] != 0 && !validDate)                                 valid=0;
        if(req.delayMin > data[i].delay)                                        valid=0;

        if(valid){
            res[indexRes] = i;
            indexRes++;
        }
    }

    return indexRes;
}

int handleFileInput(char fileName[], t_corsa data[]){
    int lenData, i;
    char c[MAX_CHAR_CORSA+1], s[MAX_CHAR_CORSA+1], d[MAX_CHAR_CORSA+1], ts[MAX_CHAR_CORSA+1], te[MAX_CHAR_CORSA+1];
    int a, m, g, dl;
    FILE *fp;

    if((fp=fopen(fileName, "r")) == NULL){
        printf("Errore apertura file\n");
        return 0;
    }

    fscanf(fp, "%d", &lenData);
    for(i=0 ; i<lenData ; i++){
        fscanf(fp, "%s %s %s %d/%d/%d %s%s %d", c, s, d, &a, &m, &g, ts, te, &dl);
        strcpy(data[i].code, c);
        strcpy(data[i].start, s);
        strcpy(data[i].dest, d);
        strcpy(data[i].timeStart, ts);
        strcpy(data[i].timeEnd, te);
        data[i].date[0] = a;
        data[i].date[1] = m;
        data[i].date[2] = g;
        data[i].delay   = dl;
    }

    fclose(fp);
    return lenData;
}

int dateBetween(int date[3], int start[3], int end[3]){
    int valid, d, s, e;

    // simple method wich converts aaaa mm gg in a integer aaaammgg for comparison
    d = date[0]*10000+ date[1]*100+ date[2];
    e = end[0]*10000+end[1]*100+end[2];
    s = start[0]*10000+start[1]*100+start[2];

    valid = (d<=e && d>=s);

    return valid;
}
    