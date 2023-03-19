#include "BIOSKOP.h"

void createListPenonton(Listpenonton &L){
    first(L) = NULL;
}
void createListFilm(ListFilm &L){
    first(L) = NULL;
    last(L) = NULL;
}
adrPenonton newPenonton(string x){
    adrPenonton p = new elmPenonton;
    info(p) = x;
    next(p) = NULL;
    child(p) = NULL;
    return p;
}
adrFilm newFilm(infotypeFilm x){
    adrFilm p = new elmFilm;
    info(p) = x;
    next(p) = NULL;
    prev(p) = NULL;
    bobot(p) = 0;
    return p;
}

adrConect newConect(adrFilm x){
    adrConect p = new elmConect;
    infochild(p) = x;
    bobot(x) += 1;
    next(p) = NULL;
    return p;
}


/*Menambahkan data penonton.*/
void insertPenontonFirst(Listpenonton &L, adrPenonton P){
    if (first(L) == NULL){
        first(L) = P;
    }else{
        adrPenonton q = first(L);
        while(next(q) != NULL){
            q = next(q);
        }
        next(q) = P;
    }
}

/*Menambahkan data film.*/
void insertFilm(ListFilm &L, adrFilm P){
    if(first(L) == NULL){
        first(L) = P;
        last(L) = P;
        next(P) = first(L);
        prev(P) = first(L);
    }else{
        adrFilm q = first(L);
        while(next(q) != first(L)){
            q = next(q);
        }
        next(q) = P;
        prev(P) = q;
        next(P) = first(L);
        prev(first(L)) = P;
        last(L) = P;
    }
}

/*Mencari data penonton tertentu.*/
adrPenonton searchPenonton(Listpenonton L, string nama){
    adrPenonton P = first(L);
    while(P!=NULL&&info(P)!=nama){
        P = next(P);
    }
    return P;
}


adrFilm searchFilm(ListFilm L, string film){
    adrFilm P = first(L);
    if (first(L) == NULL){
        return NULL;
    }else{
        while(next(P) != first(L)&&info(P).judul!=film){
            P = next(P);
        }
        if (info(P).judul == film){
           return P;
        }else {
            return NULL;
        }

    }
}


/*Menambahkan relasi penonton dengan film yang ditonton.*/
void InsertConect(adrPenonton &P, adrConect C){
    if (child(P) == NULL){
        child(P) = C;
    }else {
        next(C) = child(P);
        child(P) = C;
    }
}

/*Mencari data penonton yang menonton film tertentu.*/
void searchConectPenonton(Listpenonton LP, ListFilm LF, string judul){
    adrFilm AF = searchFilm(LF,judul);
    adrPenonton AP = first(LP);
    while(AP != NULL){
        adrConect c = child(AP);
        while(c != NULL){
            if(infochild(c)==AF){
                cout<<"- "<<info(AP)<<endl;
            }
            c = next(c);
        }
        AP = next(AP);
    }
}

void deletePenonton(Listpenonton &L, adrPenonton &P, string nama){
    if(first(L)!=NULL){
        P=searchPenonton(L,nama);
        if(P!=NULL){
            if(next(first(L))==NULL){
                first(L)=NULL;
            }
            else if(P==first(L)){
                first(L)=next(first(L));
                next(P) = NULL;
            }
            else{
                adrPenonton temp = first(L);
                while(next(temp)!=P){
                    temp=next(temp);
                }
                if(next(P)==NULL){
                    next(temp)=NULL;
                }
                else{
                    next(temp)=next(P);
                    next(P) =NULL;
                }
            }
        }
        else{
            cout<<"Penonton tidak ketemu"<<endl;
        }
    }
    else{
        cout<<"List kosong"<<endl;
    }
}

void deletePenontonConect(Listpenonton &LP, ListFilm &LF, string namaPenonton, string namaFilm){
    adrPenonton AP = searchPenonton(LP,namaPenonton);
    adrFilm AF = searchFilm(LF,namaFilm);
    if(AP!=NULL&&AF!=NULL){
        adrConect AC = child(AP);
        adrConect temp;
        while(AC!=NULL&&infochild(AC)!=AF){
            temp = AC;
            AC=next(AC);
        }
        if (AC==NULL){
            cout<<"Penonton dan film tidak terhubung"<<endl;
            return;
        }
        else{
            if(AC==child(AP)){
                child(AP)=next(child(AP));
                delete AC;
            }
            else{
                if(next(AC)==NULL){
                    next(temp) = NULL;
                    delete AC;
                }
                else{
                    next(temp) = next(AC);
                    delete AC;
                }
            }
        }
    }
    else{
        cout<<"Not found"<<endl;
    }
}


//Menghapus data film yang ditonton oleh penonton tertentu.
void deleteFilm(ListFilm &L, adrFilm P){
    adrFilm q;
    if(first(L) == P){
        if(first(L) == last(L)){
            first(L) = NULL;
            last(L) = NULL;
        }else{
            q = first(L);
            while(next(q) != first(L)){
                q = next(q);
            }
            first(L) = next(P);
            next(q) = first(L);
            prev(first(L)) = q;
            prev(P) = NULL;
            next(P) = NULL;

        }
    }
}


/*Menampilkan data seluruh penonton dan film yang ditonton.*/
void ShowAll(Listpenonton LP, ListFilm LF){
    if(first(LP)==NULL||first(LF)==NULL){
        cout<<"List kosong"<<endl;
        return;
    }
    adrPenonton p = first(LP);
    if(p!=NULL){
        adrConect c = child(p);
        while(p != NULL){
            c=child(p);
            cout<<"- Penonton "<<info(p)<<" menonton film: "<<endl;
            while(c!=NULL){
                cout<<"- "<<info(infochild(c)).judul<<" ("<<info(infochild(c)).durasi<<" menit)"<<endl;
                c=next(c);
            }
            p=next(p);
        }
    }
}

/*Menghitung banyaknya penonton yang menonton film tertentu.*/
int countPenonton(Listpenonton LP, string judul){
    int jum = 0;
    adrPenonton p = first(LP);
    while(p != NULL){
        adrConect r = child(p);
        while(r != NULL){
            if(info(infochild(r)).judul == judul){
                jum++;
            }
            r = next(r);
        }
        p=next(p);
    }
    return jum;
}

/*Menampilkan data film yang paling banyak diminati.*/
void ShowMaxFilm(ListFilm LF){
    int max = 0;
    string most;
    adrFilm p = first(LF);
    while(next(p)!=first(LF)){
        if(bobot(p)>max){
            max = bobot(p);
            most = info(p).judul;
        }
        p=next(p);
    }
    if(bobot(p)>max){
        max = bobot(p);
        most = info(p).judul;
    }
    cout<<"Film yang paling diminati adalah: "<<most<<" dengan penonton sebanyak "<<max<<endl;
}

//Menu/
int Menu(){
    int pilihan = 0;
    cout<<"========================"<<endl;
    cout<<"====== Menu ======"<<endl;
    cout<<"1. Menambahkan data penonton"<<endl;
    cout<<"2. Menambahkan data film."<<endl;
    cout<<"3. Mencari data penonton tertentu."<<endl;
    cout<<"4. Menambahkan relasi penonton dengan film yang ditonton."<<endl;
    cout<<"5. Mencari data penonton yang menonton film tertentu."<<endl;
    cout<<"6. Menghapus data penonton berserta relasinya."<<endl;
    cout<<"7. Menghapus data film yang ditonton oleh penonton tertentu."<<endl;
    cout<<"8. Menampilkan data seluruh penonton dan film yang ditonton."<<endl;
    cout<<"9. Menghitung banyaknya penonton yang menonton film tertentu."<<endl;
    cout<<"10.Menampilkan data film yang paling banyak diminati."<<endl;
    cout<<"0. Keluar"<<endl;
    cout<<"Pilihan : ";

    cin>>pilihan;
    return pilihan;
}

void showList(Listpenonton LF){
    adrPenonton p;
    adrConect q;
    p = first(LF);
    while(p != NULL){
        cout<<"Penonton "<<info(p)<<": ";
        q = child(p);
        while(q != NULL){
            cout<< " - "<<infochild(q);
            q = next(q);
        }
        cout<<endl;
        p = next(p);
    }
}

