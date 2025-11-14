
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char** citanje_spiska(char** spisak, char** cy, char** lt) {

    char ulaz[120 * sizeof(char)];
    int i;
    FILE* ptr;
    ptr = fopen("spisak_vsu.txt", "r");
    for (i=0; i<52; i++) {
        fgets(ulaz, 120, ptr);
        ulaz[strcspn(ulaz, "\n")] = '\0';
        strcpy(*(spisak + i), ulaz);
    }
    for (i=0; i<52; i++) {
        fgets(ulaz, 120, ptr);
        ulaz[strcspn(ulaz, "\n")] = '\0';
        strcpy(*(cy + i), ulaz);
    }
    for (i=0; i<52; i++) {
        fgets(ulaz, 120, ptr);
        ulaz[strcspn(ulaz, "\n")] = '\0';
        strcpy(*(lt + i), ulaz);
    }
    //for (i=0; i<52; i++) printf("%s(%s)(%s)\n", *(spisak + i), *(cy + i), *(lt + i));
    return spisak, cy, lt;
}

bool unos_nula_jedan(){
    bool greska = 1;
    char unos[20];
    char karakter;

    while (greska) {
        scanf("%s", unos);
        if (strlen(unos) != 1) {
            printf("\nГрешка при уносу, унети опет: ");
        }
        else {
            karakter = unos[0];
            if (karakter != '0' && karakter != '1') {
                printf("\nГрешка при уносу, унети опет: ");
            }
            else {
                greska = 0;
                if (karakter == '1') {
                    return 1;
                }
                else {
                    return 0;
                }
            }

        }
    }
}

int* pocetno_prisustvo(char** vsu, int* izlaz) {

    int i;
    char unos[20];
    int unos_int ;

    printf("-------------------------------------------------------------------------------------\n\nПpoвepa присутности високошколских установа\n");
    printf("0(није присутна), 1(присутна), 2(неко преноси њихов глас):\n");

    for (i=0; i<52; i++) {
        printf("%s: ", *(vsu + i));
        scanf("%s", unos);
        if (strlen(unos) != 1) {
            printf("\nПoгpeшнo унето, поновити унос!\n");
            i--;
        }
        else {
            unos_int = unos[0] - '0';
            if (unos_int > 2) {
                printf("\nПoгpeшнo унето, поновити унос!\n\n");
                i--;
            }
            else {
                *(izlaz + i) = unos_int;
            }        
        }
    }
    printf("\n--------------------------------------\n");
    printf("Присутност одрађена успешно!");
    printf("\n--------------------------------------\n");
    return izlaz;
}

char** upis_glasova(char** vsu, int* prisustvo) {

    bool uspesno = 0;
    bool greska;
    int a, b, i, j;
    char br_tacaka_char[20];
    int br_tacaka = 0;
    char ulaz[120] = "";

    while (br_tacaka == 0) {
        printf("\n-------------------------------------------------------------------------------------\n\nУнeти лабелу: \n");
        printf("Унети број тачака за гласање: ");
        scanf("%s", br_tacaka_char);
        printf("\n");

        if (strlen(br_tacaka_char) == 1) {
            a = br_tacaka_char[0] - '0';
            if (a > 9) {
                printf("\nПoгpeшнo унето, поновити унос!\n");
            } else {
                br_tacaka = a;
            }
        } else if (strlen(br_tacaka_char) == 2) {
            a = br_tacaka_char[0] - '0';
            b = br_tacaka_char[1] - '0';
            if (a > 9 || b > 9) {
                printf("\nПoгpeшнo унето, поновити унос!\n");
            } else {
                br_tacaka = 10 * a + b;
            }
        } else {
            printf("\nПoгpeшнo унето, поновити унос!\n");
        }
    }

    char** izlaz = malloc(52 * sizeof(char*));
    for (i = 0; i < 52; i++) {
        izlaz[i] = malloc(120 * sizeof(char));
        izlaz[i][0] = '\0';
    }

    for (i = 0; i < 52; i++) {
        if (prisustvo[i] != 0) {
            printf("%s: ", vsu[i]);
            scanf("%s", ulaz);

            if (strlen(ulaz) != br_tacaka) {
                printf("\nПoгpeшнo унето, поновити унос1!\n");
                i--;
                continue;
            }

            greska = false;
            for (j = 0; j < br_tacaka; j++) {
                if (ulaz[j] != '0' && ulaz[j] != '1' && ulaz[j] != '2' && ulaz[j] != '3') {
                    printf("\nПoгpeшнo унето, поновити унос2!\n");
                    greska = true;
                    break;
                }
            }

            if (greska) {
                i--;
            } else {
                strcpy(izlaz[i], ulaz);
            }
        } else {
            // Ako nije prisutan, upisujemo "3" za svaku tačku
            for (j = 0; j < br_tacaka; j++) {
                ulaz[j] = '3';
            }
            strcpy(izlaz[i], ulaz);
        }
        if (i == 51) uspesno = 1;
    }
    if (uspesno) return izlaz;
    else {
        strcpy(izlaz[0], "9");
        return izlaz;
    }
}

void izmena_prisustva(char** skracenice, int* prisustvo) {

    bool greska = 1;
    char unos[20];
    int i, j;
    int unos_int;
    printf("\n-------------------------------------------------------------------------------------\n\nИзмeнa присутности високошколске установе\n");
    while (greska) {
        printf("Унети шифру вшу којој ce мења присуство: ");
        scanf("%s", unos);
        for (i=0; i<52; i++) {
            if (!strcmp(unos, skracenice[i])) {
                j = i;
                greska = 0;
                break;
            }            
        }
        if (greska) {
            printf("\nПoгpeшнo унето, поновити унос!\n");
        }
    }
    greska = 1;
    while (greska) {
        printf("Унети присутност: \n0(није присутна), 1(присутна), 2(неко преноси њихов глас)   %s: ", skracenice[j]);
        scanf("%s", unos);
        if (strlen(unos) != 1) {
            printf("\nПoгpeшнo унето, поновити унос!\n");
            continue;
        }
        else {
            unos_int = unos[0] - '0';
            if (unos_int > 2) {
                printf("\nПoгpeшнo унето, поновити унос!\n");
                continue;
            }
            else {
                greska = 0;
                *(prisustvo + j) = unos_int;
                printf("\nИзмeнa одрађена успешно!\n");
            }
        }
    }
}

void datum_vreme(FILE* ptr1, FILE* ptr2) {
    time_t now = time(NULL);         
    struct tm *t = localtime(&now);
    printf("%d/%d\n", t->tm_mday, t->tm_mon + 1);
    fprintf(ptr1, "%d/%d\n", t->tm_mday, t->tm_mon + 1);
    fprintf(ptr2, "Датум: %d/%d\n", t->tm_mday, t->tm_mon + 1);
}

void ispis_glasanja(FILE* ptr, char** glasovi, int* status) {

    int i;
    int duzina = strlen(*(glasovi));

    if (duzina < 10) {
        fprintf(ptr, "g0%d\n", duzina);
    }    
    else {
        fprintf(ptr, "g%d\n", duzina - 1);
    }

    for (i=0; i<duzina; i++) {
        fprintf(ptr, "%d", *(status+i));
    }
    fprintf(ptr, "\n--\n");
    for (i=0; i<52; i++) {
        fprintf(ptr, "%s\n", *(glasovi + i));
    }
    fprintf(ptr, "#");
}

void obrada_glasanja(FILE* ptr, char** glasovi) {

    const int kvorum=26;
    int br_tacaka = strlen(*glasovi);
    int i, j;
    int za=0;    int protiv=0;     int uzdrzani=0;     int neizjasnjeni=0;
    char glas;
    int* status_tacke = malloc((br_tacaka+1) * sizeof(int)); 

    for (j=0; j<br_tacaka; j++) {
        for (i=0; i<52; i++) {
            glas = *(*(glasovi + i) + j);
            if (glas == '0') uzdrzani++;
            else if (glas == '1') za++;
            else if (glas == '2') protiv++;
            else neizjasnjeni++;
        }
        printf("Резултати тачке %d cy:\n", j+1);
        printf("(ЗA: %d) (ПРОТИВ: %d) (УЗДРЖАНИ: %d) (НЕИЗЈАШЊЕНИ: %d)\n", za, protiv, uzdrzani, neizjasnjeni);

        if (neizjasnjeni < kvorum) {
            if (za > protiv) {
                printf("Тачка %d je изгласана за!\n", j+1);
                *(status_tacke+j)=1;
            }
            else {
                printf("Тачка %d je изгласана против!\n", j+1);
                *(status_tacke+j)=2;
            }
        }
        else {
            printf("Тачка %d ce враћа на доглашавање...", j+1);
            *(status_tacke+j)=3;
        }
        za=0;     protiv=0;     uzdrzani=0;     neizjasnjeni=0;
    }
    ispis_glasanja(ptr, glasovi, status_tacke);
}

int main() {

    bool ispravno_uneto = 0;
    bool odradjena_prisutnost = 0;
    bool jedan;
    const int kvorum = 26;
    FILE* info_ptr;
    FILE* izlaz_ptr;
    info_ptr = fopen("glasovi.txt", "r");
    izlaz_ptr = fopen("izlaz.txt", "a");
    int i;
    int br_glasanja = 0;
    char glas[20];
    char unos_opcije[20];
    char izbor_opcije = 'a';

alociranje_memorije:
    char** spisak_vsu = malloc(53 * sizeof(char*));
    char** skracenice_cy = malloc(53 * sizeof(char*));
    char** skracenice_lt = malloc(53 * sizeof(char*));
    char** glasovi = malloc(53 * sizeof(char*));
    for (i=0; i<52; i++) {
        spisak_vsu[i] = malloc(120 * sizeof(char));
        skracenice_cy[i] = malloc(20 * sizeof(char));
        skracenice_lt[i] = malloc(20 * sizeof(char));
        glasovi[i] = malloc(20 * sizeof(char));
    }
    int* prisustvo = malloc(53 * sizeof(int));


    spisak_vsu, skracenice_cy, skracenice_lt = citanje_spiska(spisak_vsu, skracenice_cy, skracenice_lt);    //citanje spiska

    printf("\n--------------------------------------\n");                                       //meni:
    printf("vsd_skripta_v1.c by rgdev etf");    
    printf("\n--------------------------------------\n");
    while (izbor_opcije != '0') {
        sleep(1);
        printf("\n\nПОЧЕТНИ МЕНИ\n\n");
        printf("Почетна присутност:           1\n");
        printf("Измена присутности (не ради): 2\n");
        printf("Унос гласова:                 3\n");
        printf("Доглашавање:                  4\n");
        printf("Излаз:                        0\n\n");
        ispravno_uneto = 0;
        while (!ispravno_uneto) {
            printf("Унети опцију: ");
            scanf("%s", unos_opcije);
            if (strlen(unos_opcije) != 1) {
                printf("\nГpeшкa при уносу!\n");
            }
            else {
                if ((unos_opcije[0] != '0') && (unos_opcije[0] != '1') && (unos_opcije[0] != '2') && (unos_opcije[0] != '3') && (unos_opcije[0] != '4')) {
                    printf("\nГpeшкa при уносу!\n");
                }
                else {
                    izbor_opcije = unos_opcije[0];
                    ispravno_uneto = 1;
                }
            }           
        }
        if (izbor_opcije == '1') {                                                              //unosenje pocetnog prisustva:
            //prisustvo = pocetno_prisustvo(spisak_vsu, prisustvo);
            int prisustvo[52] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0};

            /*printf("РЕЗУЛТАТИ ПРИСУТНОСТИ: \n");
            for (i=0; i<52; i++) {
                printf("\n%s: %d", *(skracenice_cy + i), *(prisustvo + i));
            }
            */
           odradjena_prisutnost = 1;
        }
        else if (izbor_opcije == '2') {                                                         //izmena unetog prisustva:
            if (odradjena_prisutnost) {
                //for (i=0; i<52; i++) printf("%d ", prisustvo[i]);
                //izmena_prisustva(skracenice_lt, prisustvo);
                /*for (i=0; i<52; i++) printf("%d ", prisustvo[i]);
                printf("\n");*/
            }
            else {
                printf("\nПочетно присуство није одрађено!\n");
                printf("Да ли желите да га одрадите?\n1(ДА), 0(НЕ): ");
                jedan = unos_nula_jedan();
                if (jedan) {
                    //prisustvo = pocetno_prisustvo(spisak_vsu, prisustvo);
                    int prisustvo[52] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0};
                    odradjena_prisutnost = 1;
                }
                else {
                    system("clear");
                    printf("\nНије могуће одрадити измену док се не одради почетна присутност!\n");
                }

            }
        }
        else if (izbor_opcije == '3') {
            if (odradjena_prisutnost) {                                                         //unosenje i obrada glasova za nove predloge:
                //glasovi = upis_glasova(spisak_vsu, prisustvo);
                for (i=0; i<52; i++) {
                    fgets(glas, 10, info_ptr);
                    glas[strcspn(glas, "\n")] = '\0';
                    strcpy(*(glasovi + i), glas);
                }
                /*printf("РЕЗУЛТАТИ ГЛАСАЊА: \n");
                for (i=0; i<52; i++) {
                    printf("\n%s: %s", *(skracenice_cy + i), *(glasovi + i));
                }
                */
                obrada_glasanja(izlaz_ptr, glasovi);
                br_glasanja++;
            }
            else {
                printf("\nПочетно присуство није одрађено!\n");
                printf("Да ли желите да га одрадите?\n1(ДА), 0(НЕ): ");
                jedan = unos_nula_jedan();
                if (jedan) {
                    //prisustvo = pocetno_prisustvo(spisak_vsu, prisustvo);
                    int prisustvo[52] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0};
                    odradjena_prisutnost = 1;
                }
                else {
                    system("clear");
                    printf("\nНије могуће одрадити гласање док се не одради почетна присутност!\n");
                }
            }
        }       
        else if (izbor_opcije == '4') {                                                     //unesenje i obrada glasova za neizglasane predloge:
            printf("\nUNDER CONSTRUCTION\n");                                                 
        }
        else {
            printf("\n--------------------------------------\n");
            printf("Пpoгpaм је завршен!");                                                  //ispisivanje konacnog fajla i izlazak iz programa
            printf("\n--------------------------------------\n");
        }




        }

        
    return 0;
} 