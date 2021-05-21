#ifndef RECEPTES_TISZTAZAT_KISLISTA_H
#define RECEPTES_TISZTAZAT_KISLISTA_H

/*hozzavalok listaja*/
typedef struct klistaElem {
    char *hozzavalo;
    char *mennyiseg;
    int sorszam;

    struct klistaElem *kov;
}KlistaElem;

void felszabadit_kisLista(KlistaElem *adat);
void hozzavalok_mentes(KlistaElem *lista);

KlistaElem *beolvasKisLista();
KlistaElem *megvizsgal(KlistaElem *lista, KlistaElem *szo);
KlistaElem *egy_elem();
KlistaElem *uj_elem_hozzafuz(KlistaElem *hozz_menny, KlistaElem *uj);
KlistaElem *fajlbol(KlistaElem *beolv_hozz);

#endif //RECEPTES_TISZTAZAT_KISLISTA_H
