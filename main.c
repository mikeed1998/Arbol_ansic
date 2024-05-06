#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0

typedef int tipo_dato;

typedef struct tipo_nodo {
    tipo_dato elem;
    struct tipo_nodo *izq;
    struct tipo_nodo *der;
}tipo_nodo;

typedef tipo_nodo *tipo_arbol;
typedef tipo_nodo *tipo_pos;

void inicializa(tipo_arbol *a) {
    *a = NULL;
}

int vacio(tipo_arbol a) {
    return (a == NULL) ? TRUE : FALSE;
}

int recupera(tipo_pos pos, tipo_arbol a) {
    if(a == NULL || pos == NULL)
        return -1;
    return pos->elem;
}

void inserta(tipo_dato elem, tipo_arbol *a) {
    if(*a == NULL) {
        tipo_nodo* aux = (tipo_nodo*)malloc(sizeof(tipo_nodo));
        aux->elem = elem;
        aux->izq = NULL;
        aux->der = NULL;
        *a = aux;
    } else {
        if(elem < (*a)->elem) 
            inserta(elem, &((*a)->izq));
        else 
            inserta(elem, &((*a)->der));
    }
}

tipo_pos localiza(tipo_dato elem, tipo_arbol a) {
    if(a == NULL) {
        return NULL;
    } else {
        if(elem == a->elem) {
            return a;
        } else {
            if(elem < a->elem) 
                return localiza(elem, a->izq);
            else
                return localiza(elem, a->der);
        }
    }
}

tipo_pos menor(tipo_arbol a) {
    if(a == NULL) {
        return NULL;
    } else {
        if(a->izq == NULL)
            return a;
        else 
            return menor(a->izq);
    }
}

tipo_pos mayor(tipo_arbol a) {
    if(a == NULL) {
        return NULL;
    } else {
        if(a->der == NULL) 
            return a;
        else 
            return mayor(a->der);
    }
}

int es_hoja(tipo_arbol a) {
    if(a == NULL)
        return FALSE;
    
    if(a->izq == NULL && a->der == NULL)
        return TRUE;
    else
        return FALSE;
}

void recorrido_preorder(tipo_arbol a) {
    if(a == NULL)
        return;
    
    printf("[%d]", a->elem);
    recorrido_preorder(a->izq);
    recorrido_preorder(a->der);
}

void recorrido_inorder(tipo_arbol a) {
    if(a == NULL)
        return;

    recorrido_inorder(a->izq);
    printf("[%d]", a->elem);
    recorrido_inorder(a->der);
}

void recorrido_postorder(tipo_arbol a) {
    if(a == NULL)
        return;

    recorrido_postorder(a->izq);
    recorrido_postorder(a->der);
    printf("[%d]", a->elem);
}

void elimina(tipo_pos pos, tipo_arbol *a) {
    if(*a == NULL || pos == NULL) {
        printf("Error\n");
        return;
    }

    if(es_hoja(pos)) {
        *a = NULL;
    } else {
        tipo_nodo **ptr_a_eliminar;
        if((*a)->izq != NULL && pos == mayor((*a)->izq)) {
            ptr_a_eliminar = &((*a)->izq);
        } else if ((*a)->der != NULL && pos == menor((*a)->der)) {
            ptr_a_eliminar = &((*a)->der);
        } else {
            printf("Error: El nodo a eliminar no es un hijo directo del nodo actual\n");
            return;
        }

        tipo_nodo* pos_reemplazo = NULL;
        if((*ptr_a_eliminar)->izq != NULL)
            pos_reemplazo = mayor((*ptr_a_eliminar)->izq); // Obtener el nodo de reemplazo como el mayor elemento en el subárbol izquierdo
        else 
            pos_reemplazo = menor((*ptr_a_eliminar)->der); // Obtener el nodo de reemplazo como el menor elemento en el subárbol derecho
        
        (*a)->elem = pos_reemplazo->elem; // Reemplazar el elemento en el nodo actual con el elemento del nodo de reemplazo
        elimina(pos_reemplazo, ptr_a_eliminar); // Eliminar el nodo de reemplazo
    }
}


int main(int argc, char *argv[]) {
    tipo_arbol arbol;

    inicializa(&arbol);
    printf("\n%s\n", (vacio(arbol) == 1) ? "Esta vacio" : "No esta vacio");
    
    if (!vacio(arbol)) {
        printf("\n%d\n", recupera(arbol, arbol));
    } else {
        printf("\nEl arbol esta vacio, no se puede recuperar ningun elemento.\n");
    }

    inserta(1, &arbol);
    inserta(8, &arbol);
    inserta(4, &arbol);
    inserta(6, &arbol);
    inserta(2, &arbol);
    inserta(3, &arbol);
    inserta(4, &arbol);

    if (!vacio(arbol)) {
        printf("\nElemento %d recuperado del arbol\n", recupera(arbol, arbol));
    } else {
        printf("\nEl arbol esta vacio, no se puede recuperar ningun elemento.\n");
    }

    printf("\n%s\n", (vacio(arbol) == 1) ? "Esta vacio" : "No esta vacio");

    tipo_dato buscar = 6;
    tipo_pos pos_encontrada = localiza(buscar, arbol);
    if (pos_encontrada != NULL) {
        printf("\n\nElemento %d tiene una posicion valida en el arbol.\n", buscar);
    } else {
        printf("\n\nElemento %d no tiene una posicion valida en el arbol.\n", buscar);
    }

    tipo_pos menor_nodo = menor(arbol);
    printf("\nMenor elemento: %d\n", recupera(menor_nodo, arbol));

    tipo_pos mayor_nodo = mayor(arbol);
    printf("\nMayor elemento: %d\n", recupera(mayor_nodo, arbol));

    if (es_hoja(arbol)) { // el árbol será hoja cuando solo exista un nodo o la raíz este sola
        printf("\nEl arbol es una hoja.\n");
    } else {
        printf("\nEl arbol no es una hoja.\n");
    }

    printf("\nRecorrido PreOrder\n");
    recorrido_preorder(arbol);
    printf("\nRecorrido InOrder\n");
    recorrido_inorder(arbol);
    printf("\nRecorrido PostOrder\n");
    recorrido_postorder(arbol);

    tipo_pos nodo_a_eliminar = localiza(2, arbol);
    if (nodo_a_eliminar != NULL) {
        elimina(nodo_a_eliminar, &arbol);

        // Imprimir el árbol después de eliminar el nodo
        printf("\nRecorrido PreOrder\n");
        recorrido_preorder(arbol);
        printf("\nRecorrido InOrder\n");
        recorrido_inorder(arbol);
        printf("\nRecorrido PostOrder\n");
        recorrido_postorder(arbol);
    } else {
        printf("\n\nEl elemento a eliminar no se encuentra en el arbol.\n");
    }

    return 0;
}