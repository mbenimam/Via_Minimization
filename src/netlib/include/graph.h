#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "structs.h"
#include "netlist.h"
#include "point.h"
#include "segment.h"
#include "cell_segment.h"
#include "reseau.h"

// fonctions relative au graph

// fonction de creation de graph
Graph* init_graph(Netlist* nl);
void methode_naiif(Graph* G, Netlist* nl);
void afficher_graph(Netlist* nl, Graph* g, char* nomFichier);
void bicolore(Graph* G);
void detect_cycle(Graph* G);
// fonction de viz
void vizualize_graph(Graph* G);
// pour connaitre si le poind est un via
int isVia(Graph* g, Point* p);
// nombre de via
int nbr_via(Graph* g, Netlist* nl);
// liberation de memoire graph
void free_graph(Graph* G);

#endif
