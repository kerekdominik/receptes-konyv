#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "debugmalloc.h"
#include "kislista.h"
#include "nagylista.h"
#include "fuggvenyek.h"

#ifdef _WIN32
    #include <windows.h>
#endif

void kereses_recept_neve(NagyLista *rec_konyv) {
    getchar();
    char almenu = -1;
    do {
        if(almenu == '1') {
            system("cls");
            printf("\n                     RECEPTEK"
                   "\n---------------------------------------------------\n\n");
            ListaElem *mozgo2 = rec_konyv->elso->kov;
            while (mozgo2->kov != NULL) {
                printf("\t%s\n", mozgo2->nev);
                mozgo2 = mozgo2->kov;
            }
            printf("\n---------------------------------------------------"
                   "\nAdd meg a keresett recept nevét:\n");
            char *keresettNev = hosszu_sort_olvas();
            char *seged = (char*) malloc((strlen(keresettNev)+1)*sizeof(char));
            strcpy(seged, keresettNev);
            seged[0] = (char) toupper(seged[0]);
            system("cls");

            ListaElem *mozgo = rec_konyv->elso->kov;
            printf("\n                      TALÁLATOK"
                   "\n---------------------------------------------------\n\n");
            while (mozgo->kov != NULL) {
                if (strstr(mozgo->nev, keresettNev) != NULL || strstr(mozgo->nev, seged)!= NULL)
                    printf("\t%d. %s\n", mozgo->sorszam, mozgo->nev);
                mozgo = mozgo->kov;
            }

            reszletek(rec_konyv);
            free(seged);
            free(keresettNev);
        }

        system("cls");
        printf("\n\t-----------------------------------"
               "\n\t| *KERESÉS A RECEPT NEVE ALAPJÁN* |"
               "\n\t-----------------------------------"
               "\n\t|1. Keresés                       |"
               "\n\t-----------------------------------"
               "\n\t|0. Fõmenü                        |"
               "\n\t-----------------------------------");
        almenu = getchar();
        getchar();
    } while (almenu != '0');
}
void nincs_otletem(NagyLista *rec_konyv) {
    getchar();
    char almenu = -1;
    do {
        if (rec_konyv->utolso->elozo->sorszam < 3) {
            system("cls");
            printf("\n\t-----------------------------------"
                   "\n\t|           *ÖTLETEK*             |"
                   "\n\t-----------------------------------");
            printf("\n\n\tKevés a recept a jó ötletekhez :c"
                   "\n\tAdj még hozzá párat!"
                   "\n\n\tVissza: Enter");
            getchar();
            return;
        }
        if (almenu == '1') {
            system("cls");
            printf("Ötletek:\n");
            int otlet = -1, elozo = -1, elozo_elotti = -1;
            for (int i = 0; i < 3; ++i) {
                while (otlet == elozo || otlet == elozo_elotti) {
                    otlet = rand()%rec_konyv->utolso->elozo->sorszam + 1;
                }
                if (i == 1)
                    elozo_elotti = elozo;
                elozo = otlet;

                ListaElem *mozgo = rec_konyv->elso->kov;
                while (mozgo->kov != NULL) {
                    if (mozgo->sorszam == otlet) {
                        printf("\t%d. %s\n", mozgo->sorszam, mozgo->nev);
                    }
                    mozgo = mozgo->kov;
                }
            }
            reszletek(rec_konyv);
        }

        system("cls");
        printf("\n\t-----------------------------------"
               "\n\t|           *ÖTLETEK*             |"
               "\n\t-----------------------------------"
               "\n\t|1. Új ötletek                    |"
               "\n\t-----------------------------------"
               "\n\t|0. Fõmenü                        |"
               "\n\t-----------------------------------");
        almenu = getchar();
        getchar();
    } while (almenu != '0');
}
void de_ennek_egy_kis(NagyLista *rec_konyv) {
    getchar();
    char almenu = -1;
    do {
        if (almenu == '1') {
            system("cls");
            printf("\nAdj meg egy hozzávalót:\n");
            char *keresettHozz = hosszu_sort_olvas();
            char *seged = (char*) malloc((strlen(keresettHozz)+1)*sizeof(char));
            strcpy(seged, keresettHozz);
            seged[0] = (char) toupper(seged[0]);
            system("cls");

            ListaElem *mozgo = rec_konyv->elso->kov;
            printf("Találatok:\n\n");
            while (mozgo->kov != NULL) {
                hozzavalo_keres(mozgo, keresettHozz, seged);
                mozgo = mozgo->kov;
            }
            reszletek(rec_konyv);
            free(seged);
            free(keresettHozz);
        }

        system("cls");
        printf("\n\t-----------------------------------"
               "\n\t|      *A KÍVÁNT HOZZÁVALÓ*       |"
               "\n\t-----------------------------------"
               "\n\t|1. Keresés egy hozzávaló alapján |"
               "\n\t-----------------------------------"
               "\n\t|0. Fõmenü                        |"
               "\n\t-----------------------------------");
        almenu = getchar();
        getchar();
    } while (almenu != '0');
}
void el_kell_hasznalni(NagyLista *rec_konyv) {
    getchar();
    char almenu = -1;
    do {
        if (almenu == '1') {
            system("cls");
            printf("Ha nincs több hozzávaló írj egy '0'-át!\n");
            printf("\nAdj meg több hozzávalót:\n");
            KlistaElem *keresettek = el_kellHozzavalok(); /*elhasználandó hozzávalók bekérése*/

            ListaElem *mozgo = rec_konyv->elso->kov;
            printf("Találatok:\n\n");
            bool vanIlyen;
            int talalatok = 0;
            while (mozgo->kov != NULL) {
                vanIlyen = hozzavalo_keresTobb(mozgo, keresettek);
                mozgo = mozgo->kov;
                if (vanIlyen) {
                    talalatok++;
                }
            }
            if (talalatok == 0) {
                printf("\tSajnos nincs olyan recept, ami ezeket mind tartalmazza :c"
                       "\n\nVissza: Enter");
                getchar();
            }
            else reszletek(rec_konyv);

            felszabadit_kisLista(keresettek);
        }

        system("cls");
        printf("\n\t-----------------------------------"
               "\n\t|       *EL KELL HASZNÁLNI*       |"
               "\n\t-----------------------------------"
               "\n\t|1. Keresés                       |"
               "\n\t-----------------------------------"
               "\n\t|0. Fõmenü                        |"
               "\n\t-----------------------------------");
        almenu = getchar();
        getchar();
    } while (almenu != '0');
}
NagyLista *recept_hozzaad(NagyLista *rec_konyv, KlistaElem *beolv_hozzEleje) {
    char ujra = -1;
    do {
        if (ujra == '1') {
            getchar(); /*\n eltuntetese*/

            ListaElem *uj_beolvasott = (ListaElem *) malloc(sizeof(ListaElem)); check(uj_beolvasott); /*a majd hozzáfûzendõ új NagyLista elem, ami tárol egy egész receptet*/

            system("cls");
            printf("Add meg a recept nevét:");
            uj_beolvasott->nev = hosszu_sort_olvas();

            system("cls");
            KlistaElem *kisList_uj = NULL;
            char almenu = 9;
            do {
                    system("cls");
                    eddigiek_kiir(almenu, kisList_uj, uj_beolvasott); //eddig hozzáadott hozzávalók és mennyiségek kiírása
                    printf("\n1. Új hozzáadasa"
                           "\n2. Kiválasztas a meglévõek közül"
                           "\n0. Nincs több hozzávaló");
                    almenu = getchar();
                    getchar();
                    kisList_uj = almenuFGV(kisList_uj, beolv_hozzEleje, almenu); //új hozzáad VAGY fájlból kiválaszt
                    printf("\n");
            } while (almenu != '0');
            uj_beolvasott->hozz_menny = kisList_uj;

            printf("\nAdd meg az elkészítés módját:");
            uj_beolvasott->elkeszites = hosszu_sort_olvas();
            uj_beolvasott->sorszam = rec_konyv->utolso->elozo->sorszam+1;

            hozzafuz(rec_konyv, uj_beolvasott);
        }
        mentes(rec_konyv);

        /*almenu*/
        system("cls");
        printf("\n\t-----------------------------------"
               "\n\t|      *ÚJ RECEPT HOZZÁADSA*      |"
               "\n\t-----------------------------------"
               "\n\t|1. Hozzáadás                     |"
               "\n\t-----------------------------------"
               "\n\t|0. Fõmenü                        |"
               "\n\t-----------------------------------");
        ujra = getchar();
    } while (ujra != '0');
    return rec_konyv;
}
NagyLista *recept_torlese(NagyLista *rec_konyv) {
    getchar();
    char almenu = -1;
    do {
        if (almenu == '1') {
            system("cls");
            ListaElem *mozgo = rec_konyv->elso->kov;
            printf("\n                     RECEPTEK"
                   "\n---------------------------------------------------\n\n");
            while (mozgo->kov != NULL) {
                printf("\t%d. %s\n", mozgo->sorszam, mozgo->nev);
                mozgo = mozgo->kov;
            }
            printf("\n---------------------------------------------------\n");
            torles(rec_konyv);
            mentes(rec_konyv);
        }
        system("cls");
        printf("\n\t-----------------------------------"
               "\n\t|         *RECEPT TÖRLÉSE*        |"
               "\n\t-----------------------------------"
               "\n\t|1. Törlés                        |"
               "\n\t-----------------------------------"
               "\n\t|0. Fõmenü                        |"
               "\n\t-----------------------------------");
        almenu = getchar();
        getchar();
    } while (almenu != '0');

    return rec_konyv;
}

int main () {
    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif
    /*fõmenü*/
    char menu;
    do {
        NagyLista *rec_konyv = mentes_beolvas(); //a mentett receptek beolvasása
        KlistaElem *beolv_hozzEleje = beolvasKisLista(); //a mentett hozzávalók beolvasása

        system("cls");
        printf("\n\t-----------------------------------"
               "\n\t|        RECEPTES KÖNYV           |");
        printf("\n\t-----------------------------------"
               "\n\t|1.  Keresés a recept neve szerint|"
               "\n\t-----------------------------------"
               "\n\t|2.  Nincs ötletem...             |"
               "\n\t-----------------------------------"
               "\n\t|3.  De ennék egy kis...          |"
               "\n\t-----------------------------------"
               "\n\t|4.  El kell használni...         |"
               "\n\t-----------------------------------"
               "\n\t|5.  Recept hozzáadasa            |"
               "\n\t-----------------------------------"
               "\n\t|6.  Recept törlése               |"
               "\n\t-----------------------------------"
               "\n\t|0.  Kilépés                      |"
               "\n\t-----------------------------------");
        menu = getchar();
        switch (menu) {
            case '0': {
                /*felszabaditasok*/
                felszabadit_egesz(rec_konyv);
                felszabadit_kisLista(beolv_hozzEleje);
                exit(0);
            }
            case '1':
                kereses_recept_neve(rec_konyv);
                break;
            case '2':
                nincs_otletem(rec_konyv);
                break;
            case '3':
                de_ennek_egy_kis(rec_konyv);
                break;
            case '4':
                el_kell_hasznalni(rec_konyv);
                break;
            case '5':
                system("cls");
                rec_konyv = recept_hozzaad(rec_konyv, beolv_hozzEleje);
                break;
            case '6':
                rec_konyv = recept_torlese(rec_konyv);
                break;
            default:
                printf("Ervenytelen menupont...\n");
                break;
        }
        felszabadit_egesz(rec_konyv);
        felszabadit_kisLista(beolv_hozzEleje);
    } while (menu != 0);
}
