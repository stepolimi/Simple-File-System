#include <stdio.h>

#define N 255                  //lunghezza nomi
#define H 255                 //altezza massima
#define F 1024                //massimi figli
#define C 10                //massima lunghezza di un comando
#define P 65035              //massima lunghezza percorso+comando
#define R 70000               //massima lunghezza riga

typedef struct directory {
    struct directory *padre;
    char name[N];
    int figli_f;
    int figli_d;
    struct directory *figlio_d[F];
    struct file *figlio_f[F];
} t_directory;

typedef struct file {
    struct directory *padre;
    char name[N];
    char data [N];
} t_file;

typedef struct struttura_percorso{
    struct struttura_percorso *successivo,*precedente;
    char strada[P];
} t_percorso;


int CopiaStringa (char[],char[]);
int ComparaStringhe(char [],char []);
void IdentificaComando(char [],char [],char[]);
void Create (char[]);
void Create_dir (char[]);
void Delete (char[]);
void Delete_r(char[]);
void Read (char[]);
void Write (char[],char[]);
void Find (char []);
void CancellaFigli (t_directory *);
void CercaNodi (t_directory *,char[]);
void ConcatenaStringhe (char[]);
void OrdinaStampaStrada();
int OrdinaStringhe(char [],char []);


t_directory radice;
t_percorso primo;
t_percorso *attuale;
int trovati;


int main(){
    char c,*str;        //acquisizione
    char d,*percorso;       //percorso
    char comando[C],/*percorso[P],*/contenuto[N];
    char ris;
    int i,j;        //contatori for
    int g,k;        //gestione acquisizione
    int m,n;        //gestione percorso
    radice.name[0]='\0';
    radice.figli_f=0;
    radice.figli_d=0;
    g=10;
    k=0;
    scanf("%c",&c);
    str = (char*)malloc(g);
    while(c!='\n'){
        if(k<g){
            *(str+k)=c;
        }
        else{
            g=g+10;
            str=(char*)realloc(str,g);
            *(str+k)=c;
        }
        scanf("%c",&c);
        k++;
    }
    *(str+k)='\0';

    m=10;
    n=0;
    percorso = (char*)malloc(m);

    while (ComparaStringhe(str,"exit")==0){
        for (i=0;str[i]!=' ';i++) {                                    //prende il comando
            comando[i]=str[i];
        }
        comando[i]='\0';
        while (str[i]==' '){                                           //va fino al primo non spazio dopo al comando
            i++;
        }
        for (n=0;str[i]!='\0'&&str[i]!=' ';i++){                           //prende il percorso  o nome nel caso di find
            if(n<m){
                percorso[n]=str[i];
            }
            else{
                m=m+10;
                percorso = (char*)realloc(percorso,m);
                percorso[n]=str[i];
            }
            n++;
        }
        percorso[n]='\0';
        if (ComparaStringhe(comando,"write")){                                          //prende il contenuto in caso di write
            j=0;
            while (str[i]==' '||str[i]=='"' || i>=R)
                i++;
            for( ;str[i]!='"' || i>=R;i++){
                contenuto[j]=str[i];
                j++;
            }
            contenuto[j]='\0';
        }
        IdentificaComando(comando,percorso,contenuto);
        k=0;
        scanf("%c",&c);
        while(c!='\n'){
            if(k<g){
                *(str+k)=c;
            }
            else{
                g=g+10;
                str=(char*)realloc(str,g);
                *(str+k)=c;
            }
            scanf("%c",&c);
            k++;
        }
        *(str+k)='\0';
    }
    for(i=0;i<g;i++)
        free(str+i);
    return 0;
}


void IdentificaComando (char comando[],char percorso[],char contenuto[]){
    if (ComparaStringhe(comando,"create")){
        Create(percorso);
        return ;
    }
    if (ComparaStringhe(comando,"create_dir")){
        Create_dir(percorso);
        return ;
    }
    if (ComparaStringhe(comando,"delete")){
        Delete(percorso);
        return ;
    }
    if (ComparaStringhe(comando,"delete_r")){
        Delete_r(percorso);
        return ;
    }
    if (ComparaStringhe(comando,"read")){
        Read(percorso);
        return ;
    }
    if (ComparaStringhe(comando,"write")){
        Write(percorso,contenuto);
        return ;
    }
    if (ComparaStringhe(comando,"find")){
        Find(percorso);
        return ;
    }
    return  ;
}


void Create(char percorso[]){
    int i,j,k,h;
    char nodo[N];
    t_directory *padre;
    padre=&radice;
    i=0;
    j=0;
    h=0;
    do{
        k=0;
        for(i=i+1; percorso[i]!='/' && percorso[i]!='\0'; i++){
            nodo[k]=percorso[i];
            k++;
        }
        nodo[k]='\0';
        if(percorso[i]=='/'){
            for(j=0; j<padre->figli_d; j++){
                if(ComparaStringhe(padre->figlio_d[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_d)
                padre=padre->figlio_d[j];
            else{
                printf("no\n");
                return ;
            }
        }
        h++;
    } while (percorso[i]=='/' && h<254);
    if(padre->figli_f + padre->figli_d < F){

        for(i=0; i<padre->figli_d; i++){
            if(ComparaStringhe(padre->figlio_d[i]->name,nodo)==1)
                    break;
        }
        if(i<padre->figli_d){
            printf ("no\n");
            return ;
        }
        for(i=0; i<padre->figli_f; i++){
            if(ComparaStringhe(padre->figlio_f[i]->name,nodo)==1)
                    break;
        }
        if(i<padre->figli_f){
            printf ("no\n");
            return ;
        }

        j=padre->figli_f;
        padre->figlio_f[j]=(t_directory*) malloc (sizeof(t_file) * 1);
        CopiaStringa(padre->figlio_f[j]->name,nodo);
        padre->figlio_f[j]->data[0]='\0';
        padre->figli_f ++;
        padre->figlio_f[j]->padre=padre;
        printf("ok\n");
        return ;
    }
    printf("no\n");
    return ;


}
void Create_dir(char percorso[]){
    int i,j,k,h;
    char nodo[N];
    t_directory *padre;
    padre=&radice;
    i=0;
    j=0;
    h=0;
    do{
        k=0;
        for(i=i+1; percorso[i]!='/' && percorso[i]!='\0'; i++){
            nodo[k]=percorso[i];
            k++;
        }
        nodo[k]='\0';
        if(percorso[i]=='/'){
            for(j=0; j<padre->figli_d; j++){
                if(ComparaStringhe(padre->figlio_d[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_d)
                padre=padre->figlio_d[j];
            else{
                printf ("no\n");
                return ;
            }
        }
        h++;
    } while (percorso[i]=='/' && h<254);
    if(padre->figli_f + padre->figli_d < F){


            for(i=0; i<padre->figli_d  ; i++){
                if(ComparaStringhe(padre->figlio_d[i]->name,nodo)==1)
                    break;
            }
            if(i<padre->figli_d){
                printf ("no\n");
                return ;
            }
            for(i=0; i<padre->figli_f; i++){
                if(ComparaStringhe(padre->figlio_f[i]->name,nodo)==1)
                    break;
            }
            if(i<padre->figli_f){
                printf ("no\n");
                return ;
            }

        j=padre->figli_d;
        padre->figlio_d[j]=(t_directory*) malloc (sizeof(t_directory) * 1);
        padre->figlio_d[j]->figli_d=0;
        padre->figlio_d[j]->figli_f=0;
        CopiaStringa(padre->figlio_d[j]->name,nodo);
        padre->figli_d ++;
        padre->figlio_d[j]->padre=padre;
        printf("ok\n");
        return ;
    }
    printf ("no\n");
    return ;
}

void Delete(char percorso[]){
    int i,j,k;
    char nodo[N],c;
    t_directory *padre,*supporto;
    padre=&radice;
    i=0;
    j=0;
    do{
        k=0;
        for(i=i+1; percorso[i]!='/' && percorso[i]!='\0'; i++){
            nodo[k]=percorso[i];
            k++;
        }
        nodo[k]='\0';
        if(percorso[i]=='/'){
            for(j=0;  j<padre->figli_d; j++){
                if(ComparaStringhe(padre->figlio_d[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_d)
                padre=padre->figlio_d[j];
            else{
                printf ("no\n");
                return ;
            }
        }
        else{
            for(j=0; j<padre->figli_d; j++){
                if (ComparaStringhe(padre->figlio_d[j]->name,nodo)==1){
                    if(padre->figlio_d[j]->figli_d==0 && padre->figlio_d[j]->figli_f==0){
                        supporto=padre->figlio_d[j];
                        padre->figlio_d[j]=padre->figlio_d[padre->figli_d-1];
                        free(supporto);
                        padre->figli_d=padre->figli_d -1;
                        printf("ok\n");
                        return ;
                    }
                }
            }
            for(j=0; j<padre->figli_f;j++){
                if (ComparaStringhe(padre->figlio_f[j]->name,nodo)==1){
                    supporto=padre->figlio_f[j];
                    padre->figlio_f[j]=padre->figlio_f[padre->figli_f-1];
                    free(supporto);
                    padre->figli_f=padre->figli_f -1;
                    printf ("ok\n");
                    return ;
                }
            }
            printf("no\n");
            return ;
        }
    } while (percorso[i]=='/');
    return ;
}


void Delete_r(char percorso[]){
    int i,j,k;
    char nodo[N];
    t_directory *padre,*directory,*supporto;
    padre=&radice;
    i=0;
    j=0;
    do{
        k=0;
        for(i=i+1; percorso[i]!='/' && percorso[i]!='\0'; i++){
            nodo[k]=percorso[i];
            k++;
        }
        nodo[k]='\0';
        if(percorso[i]=='/'){
            for(j=0; j<padre->figli_d; j++){
                if(ComparaStringhe(padre->figlio_d[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_d)
                padre=padre->figlio_d[j];
            else{
                printf ("no\n");
                return ;
            }
        }
        else {
            for(j=0; j<padre->figli_d; j++){
                if(ComparaStringhe(padre->figlio_d[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_d){
                directory=padre->figlio_d[j];
                break;
            }
            for(j=0; j<padre->figli_f; j++){
                if(ComparaStringhe(padre->figlio_f[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_f){
                supporto=padre->figlio_f[j];
                padre->figlio_f[j]=padre->figlio_f[padre->figli_f-1];
                free(supporto);
                printf("ok\n");
                return ;
            }
            printf("no\n");
            return ;
        }
    } while (percorso[i]=='/');
    supporto=padre->figlio_d[j];
    padre->figlio_d[j]=padre->figlio_d[padre->figli_d-1];
    CancellaFigli(supporto);
    printf ("ok\n");
    return ;
}
void Read (char percorso[]){
    int i,j,k;
    char nodo[N];
    t_directory *padre;
    t_file *file;
    padre=&radice;
    i=0;
    j=0;
    do{
        k=0;
        for(i=i+1; percorso[i]!='/' && percorso[i]!='\0'; i++){
            nodo[k]=percorso[i];
            k++;
        }
        nodo[k]='\0';
        if(percorso[i]=='/'){
            for(j=0; j<padre->figli_d; j++){
                if(ComparaStringhe(padre->figlio_d[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_d)
                padre=padre->figlio_d[j];
            else{
                printf ("no\n");
                return ;
            }
        }
        else{
            for(j=0;  j<padre->figli_f; j++){
                if(ComparaStringhe(padre->figlio_f[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_f)
                file=padre->figlio_f[j];
            else{
                printf ("no\n");
                return ;
            }
        }
    } while (percorso[i]=='/');
    printf("contenuto %s\n",file->data);
    return ;

}
void Write (char percorso[],char contenuto[]){
    int i,j,k,car_scritti;
    char nodo[N];
    t_directory *padre;
    t_file *file;
    padre=&radice;
    i=0;
    j=0;
    do{
        k=0;
        for(i=i+1; percorso[i]!='/' && percorso[i]!='\0'; i++){
            nodo[k]=percorso[i];
            k++;
        }
        nodo[k]='\0';
        if(percorso[i]=='/'){
            for(j=0; j<padre->figli_d; j++){
                if(ComparaStringhe(padre->figlio_d[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_d)
                padre=padre->figlio_d[j];
            else{
                printf ("no\n");
                return ;
            }
        }
        else{
            for(j=0; j<padre->figli_f; j++){
                if(ComparaStringhe(padre->figlio_f[j]->name,nodo)==1)
                    break;
            }
            if(j<padre->figli_f)
                file=padre->figlio_f[j];
            else{
                printf("no\n");
                return ;
            }
        }
    } while (percorso[i]=='/');
    car_scritti=CopiaStringa(file->data,contenuto);
    printf("ok %d\n",car_scritti);
    return ;
}

void Find (char nome[]){
    int i;
    attuale=&primo;
    attuale->strada[0]='\0';
    trovati=0;
    CercaNodi(&radice,nome);
    if (trovati >0){
        OrdinaStampaStrada();
        return ;
    }
    printf ("no\n");
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
int CopiaStringa (char str1[],char str2[]){
    int i,j;
    j=0;
    for (i=0;str2[i]!='\0';i++){
        str1[i]=str2[i];
        j++;
    }
    str1[i]='\0';
    return j;
}

void CancellaFigli(t_directory *nodo){
    int i;
    t_directory *supporto;
    for(i=0;i<nodo->figli_f;i++){
        supporto=nodo->figlio_f[i];
        nodo->figlio_f[i]=nodo->figlio_f[nodo->figli_f-1];
        free(supporto);
    }
    for(i=0;i<nodo->figli_d;i++){
        CancellaFigli(nodo->figlio_d[i]);
    }
    free(nodo);
    return ;
}


void CercaNodi(t_directory *nodo,char nome[]){
    int i;
    t_directory *comodo;
    for(i=0;i<nodo->figli_f;i++){
        if(ComparaStringhe(nodo->figlio_f[i]->name,nome)==1){
            trovati ++;
            ConcatenaStringhe(nodo->figlio_f[i]->name);
            comodo=nodo;
            while (comodo->name[0]!='\0'){
                ConcatenaStringhe(comodo->name);
                comodo=comodo->padre;
            }
            attuale->successivo=(t_percorso*) malloc (sizeof(t_percorso) * 1);
            attuale->successivo->precedente=attuale;
            attuale=attuale->successivo;
            attuale->strada[0]='\0';
        }
    }
    for(i=0;i<nodo->figli_d;i++){
            if(ComparaStringhe(nodo->figlio_d[i]->name,nome)==1){
                trovati ++;
                ConcatenaStringhe(nodo->figlio_d[i]->name);
                comodo=nodo;
                while (comodo->name[0]!='\0'){
                    ConcatenaStringhe(comodo->name);
                    comodo=comodo->padre;
                }
                attuale->successivo=(t_percorso*) malloc (sizeof(t_percorso) * 1);
                attuale->successivo->precedente=attuale;
                attuale=attuale->successivo;
                attuale->strada[0]='\0';
            }
            CercaNodi(nodo->figlio_d[i],nome);
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
        attuale->strada[i+j+1]=attuale->strada[i];
     }
     attuale->strada[i+j]='\0';
     attuale->strada[0]='/' ;
     for(i=0;i<j;i++){
            attuale->strada[i+1]=nodo[i];
     }
     return ;
 }

void OrdinaStampaStrada(){
    int i,j;
    t_percorso *min,*supporto,*locale;
    for(i=0;i<trovati-1;i++){
        min=&primo;
        locale=(&primo)->successivo;
        supporto=&primo;
        for (j=i;j<trovati-1;j++){
            if(OrdinaStringhe(min->strada,locale->strada)==0){
                min=locale;
            }
            locale=locale->successivo;
        }
        printf("ok %s\n",min->strada);
        if(min!=supporto){
            min->precedente->successivo=min->successivo;
            free (min);
        }
        else{
            supporto=supporto->successivo;
            free(&primo);
            primo=*supporto;
        }
    }
    printf("ok %s\n",(&primo)->strada);
    free(&primo);
    return ;
}

int OrdinaStringhe(char str1[],char str2[]){
    int i;
    for(i=0;str1[i]!='\0'&&str2[i]!='\0';i++){
        if (str1[i]<str2[i])
            return 1;
        if (str1[i]>str2[i])
            return 0;
    }
    if (str1[i]=='\0')
        return 1;
    return 0;

}
