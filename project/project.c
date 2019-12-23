
#define M 258                   //lunghezza dati con "
#define N 256                  //lunghezza nomi
#define H 254                 //altezza massima
#define F 1024                //massimi figli
#define C 11                //massima lunghezza di un comando
#define P 65026              //massima lunghezza percorso

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
    char *strada;
    int max_strada;
} t_percorso;


int CopiaStringa (char[],char[]);
int CopiaStringaWrite (char[],char[]);
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
void ScriviStrada (char[]);
void StampaStrada();
int OrdinaStringhe(char [],char []);


t_directory radice;
t_percorso testa_find;
t_percorso *attuale;
int trovati;


int main(){
    char comando[C],percorso[P],contenuto[M],ch;
    int i;
    radice.name[0]='\0';
    radice.figli_f=0;
    radice.figli_d=0;
    scanf("%s",comando);
    /*scanf("%c",&ch);
    while(ch==' ')
        scanf("%c",&ch);
    if(ch=='\n'){
        percorso[0]='n';
        percorso[1]='\0';
    }
    else{
        percorso[0]=ch;*/
        scanf("%s",&percorso[0]);                      //1
        if(ComparaStringhe(comando,"write")){
            /*scanf("%c",&ch);
            while(ch==' ')
                scanf("%c",&ch);
            if(ch=='\n')
                comando[0]='n';
            else{
                contenuto[0]=ch;*/
                scanf("%s",&contenuto[0]);          //1
                /*scanf("%c",&ch);
                while(ch==' ')
                    scanf("%c",&ch);
                while(ch!='\n'){
                    comando[0]='n';
                    scanf("%c",&ch);
                }
            }
        }
        else{
            scanf("%c",&ch);
            while(ch==' ')
                scanf("%c",&ch);
            while(ch!='\n'){
                comando[0]='n';
                scanf("%c",&ch);
            }
        }*/
    }
    while (ComparaStringhe(comando,"exit")==0){
        IdentificaComando(comando,percorso,contenuto);
        scanf("%s",comando);
       /* scanf("%c",&ch);
        while(ch==' ')
            scanf("%c",&ch);
        if(ch=='\n'){
            percorso[0]='n';
            percorso[1]='\0';
        }
        else{
            percorso[0]=ch;
            scanf("%s",&percorso[1]);
            if(ComparaStringhe(comando,"write")){
                scanf("%c",&ch);
                while(ch==' ')
                    scanf("%c",&ch);
                if(ch=='\n')
                    comando[0]='n';
                else{
                    contenuto[0]=ch;
                    scanf("%s",&contenuto[1]);
                    scanf("%c",&ch);
                    while(ch==' ')
                        scanf("%c",&ch);
                    while(ch!='\n'){
                        comando[0]='n';
                        scanf("%c",&ch);
                    }
                }
            }
            else{
                scanf("%c",&ch);
                while(ch==' ')
                    scanf("%c",&ch);
                while(ch!='\n'){
                    comando[0]='n';
                    scanf("%c",&ch);
                }
            }
        }*/
        scanf("%s",percorso);
        if(ComparaStringhe(comando,"write")){
            scanf("%s",contenuto);
        }
    }
    return 0;
}


void IdentificaComando (char comando[],char percorso[],char contenuto[]){
  /*  if (ComparaStringhe(comando,"find")){
        Find(percorso);
        return ;
    }*/
    if(percorso[0]!='/'){
        printf("no\n");
        return ;
    }
   /* if (ComparaStringhe(comando,"create")){
        Create(percorso);
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
    }*/
    if (ComparaStringhe(comando,"create_dir")){
        Create_dir(percorso);
        return ;
    }
    printf("no\n");
    return  ;
}


void Create(char percorso[]){
    int i,j,k,h;
    char nodo[N];
    t_directory *padre;
    padre=&radice;
    i=0;
    j=0;
    h=1;
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
    } while (percorso[i]=='/' && h<H);
    if(percorso[i]!='\0'){
        printf("no\n");
        return ;
    }
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
        padre->figlio_f[j]=(t_file*) malloc (sizeof(t_file) * 1);
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
    int i,j,k,h,min,mid,max,found;
    char nodo[N];
    t_directory *padre,*comodo,*comodo2;
    padre=&radice;
    i=0;
    j=0;
    h=1;
    do{
        k=0;
        for(i=i+1; percorso[i]!='/' && percorso[i]!='\0'; i++){
            nodo[k]=percorso[i];
            k ++;
        }
        nodo[k]='\0';
        if(percorso[i]=='/'){
            if(padre->figli_d==0){
                printf("no\n");
                return ;
            }
            found=0;
            min=0;
            max=padre->figli_d-1;
            mid=max/2;
            if(ComparaStringhe(padre->figlio_d[min]->name,nodo)==0){
                if(ComparaStringhe(padre->figlio_d[max]->name,nodo)==0){
                    for(j=0; mid!=min && mid!=max ; j++){
                        if(ComparaStringhe(padre->figlio_d[mid]->name,nodo)==1){
                            found=1;
                            break;
                        }
                        if(OrdinaStringhe(padre->figlio_d[mid]->name,nodo)==1){
                            min=mid;
                            mid=(max+min)/2;
                        }
                        else{
                            max=mid;
                            mid=(max+min)/2;
                        }
                    }
                }
                else{
                    mid=max;
                    found=1;
                }
            }
            else{
                mid=min;
                found=1;
            }
            if(found)
                padre=padre->figlio_d[mid];
            else{
                printf ("no\n");
                return ;
            }
        }
        h++;
    } while (percorso[i]!='\0' && h<H);
    if(percorso[i]!='\0'){
        printf("no\n");
        return ;
    }
    if(padre->figli_f + padre->figli_d < F){
        found=0;
        if(padre->figli_f==0){
            ;
        }
        else{
            min=0;
            max=padre->figli_f-1;
            mid=max/2;
            if(ComparaStringhe(padre->figlio_f[min]->name,nodo)==0){
                if(ComparaStringhe(padre->figlio_f[max]->name,nodo)==0){
                    for(j=0; mid!=min && mid!=max ; j++){
                        if(ComparaStringhe(padre->figlio_f[mid]->name,nodo)==1){
                            found=1;
                            break;
                        }
                        if(OrdinaStringhe(padre->figlio_f[mid]->name,nodo)==1){
                            min=mid;
                            mid=(max+min)/2;
                        }
                        else{
                            max=mid;
                            mid=(max+min)/2;
                        }
                    }
                }
                else{
                    mid=max;
                    found=1;
                }
            }
            else{
                mid=min;
                found=1;
            }
        }
        if(found){
            printf ("no\n");
            return ;
        }
        if(padre->figli_d==0)
             mid=0;
        else{
            min=0;
            max=padre->figli_d-1;
            mid=max/2;
            if(ComparaStringhe(padre->figlio_d[min]->name,nodo)==0){
                if(ComparaStringhe(padre->figlio_d[max]->name,nodo)==0){
                    for(j=0; mid!=min && mid!=max ; j++){
                        if(ComparaStringhe(padre->figlio_d[mid]->name,nodo)==1){
                            found=1;
                            break;
                        }
                        if(OrdinaStringhe(padre->figlio_d[mid]->name,nodo)==1){
                            min=mid;
                            mid=(max+min)/2;
                        }
                        else{
                            max=mid;
                            mid=(max+min)/2;
                        }
                    }
                }
                else{
                    mid=max;
                    found=1;
                }
            }
            else{
                mid=min;
                found=1;
            }
        }
        if(found){
            printf ("no\n");
            return ;
        }
        if(padre->figli_d==0){
            padre->figlio_d[mid]=(t_directory*) malloc (sizeof(t_directory) * 1);
            j=mid;
        }
        else{
            if(padre->figli_d>1){
                if(mid+1<padre->figli_d){
                    comodo=padre->figlio_d[mid+1];
                    padre->figlio_d[mid+1]=(t_directory*) malloc (sizeof(t_directory) * 1);
                    for(j=mid+2;j<padre->figli_d;j++){
                        comodo2=comodo;
                        comodo=padre->figlio_d[j];
                        padre->figlio_d[j]=comodo2;
                    }
                    padre->figlio_d[j]=comodo;
                    j=mid+1;
                }
                else{
                    padre->figlio_d[mid+1]=(t_directory*) malloc (sizeof(t_directory) * 1);
                    j=mid+1;
                }
            }
            else{
                if(OrdinaStringhe(padre->figlio_d[mid]->name,nodo)==1){
                    padre->figlio_d[mid+1]=(t_directory*) malloc (sizeof(t_directory) * 1);
                    j=mid+1;
                }
                else{
                    padre->figlio_d[mid+1]=padre->figlio_d[mid];
                    padre->figlio_d[mid]=(t_directory*) malloc (sizeof(t_directory) * 1);
                    j=mid;
                }
            }
        }
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
    char nodo[N];
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
                padre->figli_f=padre->figli_f -1;
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
    padre->figli_d = padre->figli_d-1;
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
    car_scritti=CopiaStringaWrite(file->data,contenuto);
    if(car_scritti<259)
        printf("ok %d\n",car_scritti);
    else
        printf("no\n");
    return ;
}

void Find (char nome[]){
    int i;
    trovati=0;
    CercaNodi(&radice,nome);
    if (trovati >0){
        StampaStrada();
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
int CopiaStringa(char str1[],char str2[]){
    int i,j;
    j=0;
    for(i=0;str2[i]!='\0';i++){
        str1[i]=str2[i];
        j++;
    }
    str1[i]='\0';
    return j;
}
int CopiaStringaWrite (char str1[],char str2[]){
    int i,j;
    j=0;
    for (i=0;str2[i+2]!='\0';i++){
        str1[i]=str2[i+1];
        j++;
    }
    if(str2[i+1]!='"' || str2[0]!= '"')
        j=259;
    str1[i]='\0';
    return j;
}

void CancellaFigli(t_directory *nodo){
    int i;
    for(i=0;i<nodo->figli_f;i++){
        free(nodo->figlio_f[i]);
    }
    for(i=0;i<nodo->figli_d;i++){
        CancellaFigli(nodo->figlio_d[i]);
    }
    free(nodo);
    return ;
}


void CercaNodi(t_directory *nodo,char nome[]){
    int i,j,ordinato;
    t_directory *comodo;
    t_percorso *comodo2,*comodo3;
    for(i=0;i<nodo->figli_f;i++){
            if(ComparaStringhe(nodo->figlio_f[i]->name,nome)==1){
                ordinato=0;
                attuale=(t_percorso*) malloc (sizeof(t_percorso) * 1);
                attuale->strada=(char*)malloc(1);
                attuale->strada[0]='\0';
                attuale->max_strada=0;
                ScriviStrada(nodo->figlio_f[i]->name);
                comodo=nodo;
                while (comodo->name[0]!='\0'){
                    ScriviStrada(comodo->name);
                    comodo=comodo->padre;
                }
                if(trovati==0){
                    (&testa_find)->successivo=attuale;
                    attuale->precedente=&testa_find;
                    trovati ++;
                }
                else{
                    comodo3=(&testa_find)->successivo;
                    for(j=0;j<trovati;j++){
                        if(OrdinaStringhe(attuale->strada,comodo3->strada)==1){
                            ordinato=1;
                            break ;
                        }
                        if(j==trovati-1)
                            break ;
                        comodo3=comodo3->successivo;
                    }
                    comodo2=comodo3->precedente;
                    if(ordinato==1){
                        comodo2->successivo=attuale;
                        comodo3->precedente=attuale;
                        attuale->precedente=comodo2;
                        attuale->successivo=comodo3;
                    }
                    else{
                        comodo3->successivo=attuale;
                        attuale->precedente=comodo3;
                    }
                    trovati ++;
                }
        }
    }
    for(i=0;i<nodo->figli_d;i++){
            if(ComparaStringhe(nodo->figlio_d[i]->name,nome)==1){
                attuale=(t_percorso*) malloc (sizeof(t_percorso) * 1);
                attuale->strada=(char*)malloc(1);
                attuale->strada[0]='\0';
                attuale->max_strada=0;
                ScriviStrada(nodo->figlio_d[i]->name);
                comodo=nodo;
                while (comodo->name[0]!='\0'){
                    ScriviStrada(comodo->name);
                    comodo=comodo->padre;
                }
                if(trovati==0){
                    (&testa_find)->successivo=attuale;
                    attuale->precedente=&testa_find;
                    trovati ++;
                }
                else{
                    comodo3=(&testa_find)->successivo;
                    for(j=0;j<trovati;j++){
                        if(OrdinaStringhe(attuale->strada,comodo3->strada)==1){
                            ordinato=1;
                            break ;
                        }
                        if(j==trovati-1)
                            break ;
                        comodo3=comodo3->successivo;
                    }
                    comodo2=comodo3->precedente;
                    if(ordinato==1){
                        comodo2->successivo=attuale;
                        comodo3->precedente=attuale;
                        attuale->precedente=comodo2;
                        attuale->successivo=comodo3;
                    }
                    else{
                        comodo3->successivo=attuale;
                        attuale->precedente=comodo3;
                    }
                    trovati ++;
                }
            }
            CercaNodi(nodo->figlio_d[i],nome);
    }
    return ;
}

void ScriviStrada(char nodo []){
    int i,j;
    for(j=0;nodo[j]!='\0';j++){
        ;
    }
    i=attuale->max_strada;
    attuale->max_strada=attuale->max_strada+j+1;
    attuale->strada = (char*)realloc (attuale->strada,attuale->max_strada+1);
    for(;i>=0;i--){
        attuale->strada[i+j+1]=attuale->strada[i];
    }
    attuale->strada[0]='/' ;
    for(i=0;i<j;i++){
        attuale->strada[i+1]=nodo[i];
    }
    return ;
 }

void StampaStrada(){
    t_percorso *candidato,*supporto;
    int i;
    candidato=(&testa_find)->successivo;
    for(i=1;i<trovati;i++){
        printf("ok %s\n",candidato->strada);
        supporto=candidato;
        candidato=candidato->successivo;
        free(supporto->strada);
        free(supporto);
    }
    printf("ok %s\n",candidato->strada);
    free(candidato->strada);
    free(candidato);
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
