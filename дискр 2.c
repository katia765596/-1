#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct elem {
    char el;
    struct elem* next_el;
} elem;
typedef struct para {
    char a, b;
    struct para* next_para;
} para;
elem* add_elem(elem* start, char el) {
    elem* e = (elem*)malloc(sizeof(elem));
    e->el = el;
    e->next_el = start;
    return e;}
bool check(elem* start, char el) {
    for (elem* pr = start; pr!=0; pr = pr->next_el)
        if (pr->el == el) return true;
    return false;}
para* add_para(para* start, char a, char b) {
    para* p = (para*)malloc(sizeof(para));
    p->a = a;
    p->b = b;
    p->next_para = start;
    return p;}
bool check_para(para* start, char a, char b) {
    for (para* p = start; p; p = p->next_para)
        if (p->a == a && p->b == b) return true;
    return false;}
bool revleksivnost(elem* elems, para* pa) {
    for (elem* e = elems; e!=0; e = e->next_el)
        if (!check_para(pa, e->el, e->el)) return false;
    return true;}
bool irrevleksivnost(elem* elems, para* pe) {
    for (elem* e = elems; e!=0; e = e->next_el)
        if (check_para(pe, e->el, e->el)) return false;
    return true;}
bool symmetric(para* pa) {
    for (para* p = pa; p!=0; p = p->next_para)
        if (!check_para(pa, p->b, p->a)) return false;
    return true;}
bool antisymmetric(para* pa) {
    for (para* p = pa; p!=0; p = p->next_para)
        if (p->a != p->b && check_para(pa, p->b, p->a)) return false;
    return true;}
bool asymmetric(para* pa) {
    for (para* p = pa; p!=0; p = p->next_para)
        if (check_para(pa, p->b, p->a)) return false;
    return true;}
bool transitive(para* pa) {
    for (para* p1 = pa; p1!=0; p1 = p1->next_para)
        for (para* p2 = pa; p2!=0; p2 = p2->next_para)
            if (p1->b == p2->a && !check_para(pa, p1->a, p2->b))
                return false;
    return true;}
bool antitransitive(para* pa) {
    for (para* p1 = pa; p1!=0; p1 = p1->next_para)
        for (para* p2 = pa; p2!=0; p2 = p2->next_para)
            if (p1->b == p2->a && check_para(pa, p1->a, p2->b))
                return false;
    return true;}
bool polnota(elem* elems, para* pa) {
    for (elem* a = elems; a!=0; a = a->next_el)
        for (elem* b = elems; b!=0; b = b->next_el)
            if (a != b && !check_para(pa, a->el, b->el) && !check_para(pa, b->el, a->el))
                return false;
    return true;}
void e_classes(elem* elems, para* pa) {
    elem* k = NULL;
    for (elem* e = elems; e!=0; e = e->next_el) k = add_elem(k, e->el);
    int class_count = 0;
    while (k!=0) {
        elem* s = add_elem(0, k->el);
        elem* c = 0;
        while (s!=0) {
            char el_ = s->el;
            elem* t = s;
            s = s->next_el;
            free(t);
            c = add_elem(c, el_);
            elem* pr_el = 0;
            elem* t_el = k;
            while (t_el) {
                if (check_para(pa, el_, t_el->el)) {
                    s = add_elem(s, t_el->el);
                    if (pr_el!=0) pr_el->next_el = t_el->next_el;
                    else k = t_el->next_el;
                    elem* t2 = t_el;
                    t_el = pr_el ? pr_el ->next_el : k;
                    free(t2);}
                else {
                    pr_el = t_el;
                    t_el = t_el->next_el;}
            }
        }
        printf("Class %d: { ", ++class_count);
        for (elem* e = c; e!=0; e = e->next_el) {
            printf("%c", e->el);
            if (e->next_el) printf(", ");
        }
        printf(" }\n");
        while (c) { elem* t = c; c = c->next_el; free(t); }
    }
    printf("Index of : %d\n", class_count);
}
void minmax(elem* elems, para* pa) {
    printf("Minimal elements: ");
    for (elem* e = elems; e!=0; e = e->next_el) {
        bool flag = true;
        for (elem* ell = elems; ell!=0; ell = ell->next_el)
            if (e != ell && check_para(pa, ell->el, e->el)) flag = false;
        if (flag!=0) printf("%c ", e->el);
    }
    printf("\nMaximal elements: ");
    for (elem* e = elems; e!=0; e = e->next_el) {
        bool flagm = true;
        for (elem* ell2 = elems; ell2!=0; ell2 = ell2->next_el)
            if (e != ell2 && check_para(pa, e->el, ell2->el)) flagm = false;
        if (flagm) printf("%c ", e->el);
    }
    printf("\n");
}
int main() {
    char name_file[50];
    printf("Enter name file: ");
    scanf("%s", name_file);
    FILE* file_ = fopen(name_file, "r");
    if (file_==0) {
        fprintf(stderr, "Can not open file\n");
        return 1;}
    elem* elems = 0;
    char l[256];
    if (fgets(l, sizeof(l), file_)) {
        for (int i = 0; l[i]; i++)
            if (l[i] != ' ' && l[i] != '\n') elems = add_elem(elems, l[i]);}
    para* pa = 0;
    char a, b;
    while (fscanf(file_, " %c %c", &a, &b) == 2)
        pa = add_para(pa, a, b);
    fclose(file_);
    printf("Reflexive: %s\n", revleksivnost(elems, pa) ? "+" : "-");
    printf("Irreflexive: %s\n", irrevleksivnost(elems, pa) ? "+" : "-");
    printf("Symmetric: %s\n", symmetric(pa) ? "+" : "-");
    printf("Antisymmetric: %s\n", antisymmetric(pa) ? "+" : "-");
    printf("Asymmetric: %s\n", asymmetric(pa) ? "+" : "-");
    printf("Transitive: %s\n", transitive(pa) ? "+" : "-");
    printf("Antitransitive: %s\n", antitransitive(pa) ? "+" : "-");
    printf("Polnota: %s\n", polnota(elems, pa) ? "+" : "-");
    if (revleksivnost(elems, pa) && symmetric(pa) && transitive(pa)) {
        printf("Relation is equivalence\n");
        e_classes(elems, pa);}
    if (revleksivnost(elems, pa) && antisymmetric(pa) && transitive(pa)) {
        printf("Relation is partial order\n");
        minmax(elems, pa);}
    while (elems) { elem* t = elems; elems = elems->next_el; free(t); }
    while (pa) { para* t = pa; pa = pa->next_para; free(t); }
    return 0;
}
