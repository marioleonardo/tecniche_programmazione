#include <stdio.h>
#include <string.h>
#define filein "..\\text\\mat.txt"


int main(){
    int firstTeam, firstTeamPoints, n, m, mat[20][20], points[20];
    FILE *fp_read;


    if((fp_read = fopen(filein, "r"))==NULL){
        printf("Error opening file\n");
        return 1;
    }

    fscanf(fp_read, "%d%d ", &n, &m);
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            fscanf(fp_read, "%d", &mat[i][j]);

    memset(points, 0, 20);
    for(int i=0; i<m; i++){
        firstTeamPoints=0;
        for (int team=0; team <n; team++){
            points[team]+=mat[team][i];
            if(points[team]>firstTeamPoints){
                firstTeamPoints=points[team];
                firstTeam=team;
            }
        }
        printf("La squadra capolista della giornata %d e' la numero %d\n", i+1, firstTeam+1);
    }
}