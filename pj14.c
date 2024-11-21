#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int size = 0,maxsize=0,globalmaks[5]={0,0,0,0,0},globalmin[5]={0,0,0,0,0};

typedef struct{
    char **mahasiswa;
    int *nilai;
    long long int *nrp;
    int *util;
    float *rata2;
} data;


void freeAll(data *mahasiswa);

void tambahData (data* mahasiswa){
    static char* print[4] = {"Eval-1","Eval-2","Eval-3","UAS"};
    char isContinue = 'w';
    do {
        isContinue='w';
        size++;
        int status = system("clear");
        if (status) system("cls");
    
        if (maxsize<size){
            maxsize+=30;
            mahasiswa->mahasiswa=(char**)realloc(mahasiswa->mahasiswa,sizeof(char*) * maxsize);
            mahasiswa->nilai=(int *)realloc(mahasiswa->nilai,sizeof(int) * maxsize * 4);
            mahasiswa->nrp=(long long int *)realloc(mahasiswa->nrp,sizeof(long long int) * maxsize);
            mahasiswa->util = (int *)realloc(mahasiswa->util,sizeof(int)*2* maxsize);
            mahasiswa->rata2 = (float*)realloc(mahasiswa->rata2, sizeof(float)*maxsize);
        }
    
        int  lokalmaks=INT_MIN,lokalmin=INT_MAX;
        mahasiswa->mahasiswa[size-1]=(char*)realloc(mahasiswa->mahasiswa[size-1], sizeof(char)*30);
    
        //input the NRP and Name
        printf("Data Mahasiswa ke-%d\n",size);
        printf("NRP:    ");
        scanf("%d",&mahasiswa->nrp[size-1]);
        getchar();
        printf("Nama:   ");
        fgets(mahasiswa->mahasiswa[size-1], 29,stdin);
    
        //remove \n at the end of string
        int length = strlen(mahasiswa->mahasiswa[size-1]);
        mahasiswa->mahasiswa[size-1][length-1] = '\0';
        float sum =0;
        //input each Nilai while calculating the min/max
        for(int i =0;i<4;i++){
            printf("Nilai %s\t:   ",print[i]);
            scanf("%d",&mahasiswa->nilai[(size-1)*4+i]);
            getchar();
    
            //setting the local min/max
            if(lokalmaks<mahasiswa->nilai[(size-1)*4+i]) lokalmaks = mahasiswa->nilai[(size-1)*4+i];
            if(lokalmin>mahasiswa->nilai[(size-1)*4+i]) lokalmin = mahasiswa->nilai[(size-1)*4+i];
    
            sum+=mahasiswa->nilai[(size-1)*4+i];
            //setting the global min/max
            if(mahasiswa->nilai[globalmaks[i]*4+i] <= mahasiswa->nilai[(size-1)*4+i]) globalmaks[i] = size-1;
            if(mahasiswa->nilai[globalmin[i]*4+i] >= mahasiswa->nilai[(size-1)*4+i]) globalmin[i] = size-1;
    
            sum+= mahasiswa->nilai[size*4+i];
        }
        mahasiswa->util[(size-1)*2] = lokalmaks;
        mahasiswa->util[(size-1)*2+1] = lokalmin;
        mahasiswa->rata2[size-1] = sum/4;
            do{
                printf("Mau Menambahkan lagi? (y/t):    ");
                scanf("%c",&isContinue);
                getchar();
            }while(isContinue!='y'&&isContinue!='t');
    } while(isContinue!='t');


}

void tampilData(data*mahasiswa){
    float total =0;
    int status = system("clear");
    if (status) system("cls");
    printf("=====================================================================================================================\nNo.\tNRP\t\tNama\t\t\tEval-1\tEval-2\tEval-3\tUAS\tRata-rata\tmaks\tmin\thuruf\n");
    int maxIndex=0,minIndex=0;
    for(int i=0;i<size;i++){
        float rata = mahasiswa->rata2[i];
        printf("%d\t%-10lld\t%-20s\t%d\t%d\t%d\t%d\t%g\t\t%d\t%d\t%s\n",i+1,mahasiswa->nrp[i],mahasiswa->mahasiswa[i],mahasiswa->nilai[(i)*4+0],mahasiswa->nilai[(i)*4+1],mahasiswa->nilai[(i)*4+2],mahasiswa->nilai[(i)*4+3],round(rata),mahasiswa->util[(i)*2],mahasiswa->util[(i)*2+1], rata>85?"A":rata>80?"A-":rata>75?"AB":rata>70?"B+":rata>65?"B":rata>60?"BC":rata>55?"C":rata>40?"D":"E");

        total += mahasiswa->rata2[i];

        if(mahasiswa->rata2[globalmaks[4]]<rata) globalmaks[4] = i;
        if(mahasiswa->rata2[globalmin[4]]>rata) globalmin[4] = i;
    }
    printf("\n\nNilai rata-rata seluruh mahasiswa\t: %g\nNilai Mahasiswa tertinggi\t\t: %s dengan nilai %g\nNilai Mahasiswa terendah\t\t: %s dengan nilai %g\nNilai Mahasiswa dengan Eval1 tertinggi\t: %s dengan nilai %d\nNilai Mahasiswa dengan Eval1 terendah\t: %s dengan nilai %d\nNilai Mahasiswa dengan Eval2 tertinggi\t: %s dengan nilai %d\nNilai Mahasiswa dengan Eval2 terendah\t: %s dengan nilai %d\nNilai Mahasiswa dengan Eval3 tertinggi\t: %s dengan nilai %d\nNilai Mahasiswa dengan Eval3 terendah\t: %s dengan nilai %d\nNilai Mahasiswa dengan UAS tertinggi\t: %s dengan nilai %d\nNilai Mahasiswa dengan UAS terendah\t: %s dengan niai %d\n\n",
    round(total/size),
    mahasiswa->mahasiswa[globalmaks[4]],round(mahasiswa->rata2[globalmaks[4]]),
    mahasiswa->mahasiswa[globalmin[4]],round(mahasiswa->rata2[globalmin[4]]),
    mahasiswa->mahasiswa[globalmaks[0]], mahasiswa->nilai[globalmaks[0]*4+0], 
    mahasiswa->mahasiswa[globalmin[0]], mahasiswa->nilai[globalmin[0]*4+0], 
    mahasiswa->mahasiswa[globalmaks[1]], mahasiswa->nilai[globalmaks[1]*4+1], 
    mahasiswa->mahasiswa[globalmin[1]], mahasiswa->nilai[globalmin[1]*4+1], 
    mahasiswa->mahasiswa[globalmaks[2]], mahasiswa->nilai[globalmaks[2]*4+2], 
    mahasiswa->mahasiswa[globalmin[2]], mahasiswa->nilai[globalmin[2]*4+2], 
    mahasiswa->mahasiswa[globalmaks[3]], mahasiswa->nilai[globalmaks[3]*4+3], 
    mahasiswa->mahasiswa[globalmin[3]], mahasiswa->nilai[globalmin[3]*4+3]);

    printf("\nPress enter to continue\n");
    getchar();
}

int main() {
    data *mahasiswa;
    mahasiswa = malloc(sizeof(data));
    

    printf("\t\tSelamat Datang\n\t\tMenu Data Mahasswa\n\n");
    
    char isContinue = 'w';

    do{
        int status = system("clear");
        if (status) system("cls");
        isContinue ='w';
        printf("Data pada entri saat ini - %d\nMenu Pilihan:\n1.    Menambahkan mahasiswa dan nilai\n2.    Menampilkan Data Mahasiswa\n3.    Selesai\n",size);
        
        while(isContinue!='1'&&isContinue!='2'&&isContinue!='3'){
            printf("Pilihan Anda:   ");
            scanf("%c", &isContinue);
            getchar();
        }
        if (isContinue=='1') tambahData(mahasiswa);
        else if (isContinue == '2' && size!=0) tampilData(mahasiswa);
        else if (isContinue =='2'&& size ==0){
            printf("Masukkan Data terlebih dahulu!\n"); 
            sleep(1);
        }
    }while(isContinue!='3');
    freeAll(mahasiswa);
    return 0;
}

void freeAll(data*mahasiswa){

for (int i = 0; i < size; i++) {
    if (mahasiswa->mahasiswa[i] != NULL) {
        free(mahasiswa->mahasiswa[i]);  
        mahasiswa->mahasiswa[i] = NULL; 
    }
}
if (mahasiswa->mahasiswa != NULL) {
    free(mahasiswa->mahasiswa);
    mahasiswa->mahasiswa = NULL;
}
if (mahasiswa->nilai != NULL) {
    free(mahasiswa->nilai);
    mahasiswa->nilai = NULL;
}
if (mahasiswa->nrp != NULL) {
    free(mahasiswa->nrp);
    mahasiswa->nrp = NULL;
}
if (mahasiswa->util != NULL) {
    free(mahasiswa->util);
    mahasiswa->util = NULL;
}
if (mahasiswa->rata2 != NULL) {
    free(mahasiswa->rata2);
    mahasiswa->rata2 = NULL;
}
}
