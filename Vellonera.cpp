#include "Vellonera.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Vellonera::Vellonera() {
    _primera = NULL;
    _ultima = NULL;
    _actual = NULL;
    _repetir = false;
}

// ...existing code...

void Vellonera::OrdenarCanciones()
{
    // Ordenar la lista de menor a mayor duración usando bubble sort de nodos
    if (_primera == NULL || _primera->GetSiguiente() == NULL) return;
    bool swapped;
    do {
        swapped = false;
        Cancion* curr = _primera;
        while (curr->GetSiguiente() != NULL) {
            Cancion* next = curr->GetSiguiente();
            if (curr->GetDuracion().GetTiempoTotal() > next->GetDuracion().GetTiempoTotal()) {
                // Intercambiar nodos curr y next
                Cancion* prev = curr->GetAnterior();
                Cancion* nextNext = next->GetSiguiente();

                // Enlazar prev con next
                if (prev != NULL)
                    prev->SetSiguiente(next);
                else
                    _primera = next;

                next->SetAnterior(prev);

                // Enlazar next con curr
                next->SetSiguiente(curr);
                curr->SetAnterior(next);

                // Enlazar curr con nextNext
                curr->SetSiguiente(nextNext);
                if (nextNext != NULL)
                    nextNext->SetAnterior(curr);
                else
                    _ultima = curr;

                swapped = true;
                // Después de intercambiar, next está antes de curr, así que seguimos desde next
                curr = next;
            }
            curr = curr->GetSiguiente();
        }
    } while (swapped);

    // Ajustar _ultima
    Cancion* temp = _primera;
    while (temp->GetSiguiente() != NULL) temp = temp->GetSiguiente();
    _ultima = temp;
}

// ...existing code...

void Vellonera::CancionSiguiente()
{
    if (_actual == NULL) return;
    if (_actual->GetSiguiente() != NULL) {
        _actual = _actual->GetSiguiente();
    } else if (_repetir && _primera != NULL) {
        _actual = _primera;
    }
}

// ...existing code...

void Vellonera::CancionAnterior()
{
    if (_actual == NULL) return;
    if (_actual->GetAnterior() != NULL) {
        _actual = _actual->GetAnterior();
    } else if (_repetir && _ultima != NULL) {
        _actual = _ultima;
    }
}

// ...existing code...

bool Vellonera::Eliminar(int indice)
{
    if (_primera == NULL) return false;
    int i = 0;
    Cancion* curr = _primera;
    while (curr != NULL && i < indice) {
        curr = curr->GetSiguiente();
        i++;
    }
    if (curr == NULL) return false;
    // Actualizar enlaces
    if (curr->GetAnterior() != NULL)
        curr->GetAnterior()->SetSiguiente(curr->GetSiguiente());
    else
        _primera = curr->GetSiguiente();

    if (curr->GetSiguiente() != NULL)
        curr->GetSiguiente()->SetAnterior(curr->GetAnterior());
    else
        _ultima = curr->GetAnterior();

    if (_actual == curr) {
        if (curr->GetSiguiente() != NULL)
            _actual = curr->GetSiguiente();
        else if (curr->GetAnterior() != NULL)
            _actual = curr->GetAnterior();
        else
            _actual = NULL; // Si la lista queda vacía
    }
    delete curr;
    return true;
}

void Vellonera::Agregar(Cancion* cancion)
{
    // Agregar al final de la lista doblemente enlazada
    if (_primera == NULL) {
        _primera = cancion;
        _ultima = cancion;
        _actual = cancion;
        cancion->SetAnterior(NULL);
        cancion->SetSiguiente(NULL);
    } else {
        _ultima->SetSiguiente(cancion);
        cancion->SetAnterior(_ultima);
        cancion->SetSiguiente(NULL);
        _ultima = cancion;
    }
    OrdenarCanciones();
    // Después de ordenar, _actual debe ser la primera canción si solo hay una,
    // o la última agregada si hay varias (puedes dejarlo apuntando a _primera)
    if (_actual == NULL) _actual = _primera;
}