#include <stdio.h>
#include <malloc.h>
#define N 12                  //lunghezza nomi
#define H 12                 //altezza massima
#define F 12                //massimi figli
#define C 10                //massima lunghezza di un comando
#define P 120               //massima lunghezza percorso+comando
#define R 130               //massima lunghezza riga

typedef struct directory {
    struct directory *padre;
    char name[N];
    int figli_d_max;
    int figli_f_max;
    struct directory *figlio_d[F];
    struct file *figlio_f[F];
} t_directory;

typedef struct file {
    struct directory *padre;
    char name[N];
    char data [N];
} t_file;

typedef struct struttura_percorso{
    struct struttura_percorso *successivo;
    char strada[P];
} t_percorso;

t_percorso primo;
t_percorso *attuale;
int trovati;
t_directory radice;
char strada [P];




void CopiaStringa (char[],char[]);
void CercaNodi (t_directory *,char[]);
void ConcatenaStringhe (char[]);
int ComparaStringhe(char [],char []);
void Find (char []);
void OrdinaStampaStrada();
int OrdinaStringhe(char [],char []);

int main(){
    t_directory *padre;
    radice.name[0]='\0';
    ConcatenaStringhe("ciao");
    ConcatenaStringhe("bella");
    ConcatenaStringhe("ok");
    printf("%s\n",strada);
    return ;






}
int ComparaStringhe (char str1[],char str2[]){
    int i;
    for(i=0;str1[i]!='\0'&&str2[i]!='\0';i++){
        if (str1[i]!=str2[i])
            return 0;
    }
    if (str1[i]==str2[i])
        return 1;
    return 0;
}
void CopiaStringa (char str1[],char str2[]){
    int i;
    for (i=0;str2[i]!='\0';i++)
        str1[i]=str2[i];
    str1[i]='\0';
    return ;
}
void CercaNodi(t_directory *nodo,char nome[]){
    int i;
    for(i=0;i<nodo->figli_f_max;i++){
        if(ComparaStringhe(nodo->figlio_f[i]->name,nome)==1){
            trovati ++;
            ConcatenaStringhe(nodo->figlio_f[i]->name);
            while (nodo->name[0]!='\0'){
                ConcatenaStringhe(nodo->name);
                nodo=nodo->padre;
            }
            attuale->successivo=(t_percorso*) malloc (sizeof(t_percorso) * 1);
            attuale=attuale->successivo;
            attuale->strada[0]='\0';
        }
    }
    for(i=0;i<nodo->figli_d_max;i++){
        if(nodo->figlio_d[i]->name[0]=='!'){
            if(ComparaStringhe(nodo->figlio_d[i]->name,nome)==1){
                trovati ++;
                ConcatenaStringhe(nodo->figlio_d[i]->name);
                while (nodo->name[0]!='\0'){
                    ConcatenaStringhe(nodo->name);
                    nodo=nodo->padre;
                }
                attuale->successivo=(t_percorso*) malloc (sizeof(t_percorso) * 1);
                attuale=attuale->successivo;
                attuale->strada[0]='\0';
            }
            CercaNodi(nodo->figlio_d[i],nome);
        }
    }
    return ;
}


 void ConcatenaStringhe(char nodo []){
     int i,j;
     for(j=0;nodo[j]!='\0';j++){
            ;
     }
     for(i=0;attuale->strada[i]!='\0';i++)
            ;
     for(;i>=0;i--){
        strada[i+j+1]=attuale->strada[i];
     }
     attuale->strada[i+j]='\0';
     attuale->strada[0]='/' ;
     for(i=0;i<j;i++){
            attuale->strada[i+1]=nodo[i];
     }


     return ;
 }

 void Find (char nome[]){
    int i;
    attuale=&primo;
    attuale->strada[0]='\0';
    trovati=0;
    CercaNodi(&radice,nome);
    OrdinaStampaStrada();
    return ;
 }

void OrdinaStampaStrada(){
    int i,j;
    t_percorso *min,*supporto,*elimina;
    attuale=&primo;
    supporto=&primo;
    for(i=0;i<trovati;i++){
        min=supporto;
        attuale=supporto;
        for (j=i;j<trovati;j++){
            if(OrdinaStringhe(min->strada,attuale->strada)==0)
                min=attuale;
            attuale=attuale->successivo;
        }
        printf("%s\n",supporto->strada);
        elimina=supporto;
        supporto=supporto->successivo;
        free(elimina);
    }
    return ;
}

int OrdinaStringhe(char str1[],char str2[]){
    int i;
    for(i=0;str1[i]!='\0'&&str2[i]!='\0';i++){
        if (str1[i]<str2[i])
            return 1;
        if (str1[i]>str2[i])
            return 0;
    if (str1[i]=='\0')
        return 1;
    return 0;
}
}
