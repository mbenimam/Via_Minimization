#include "graph.h"
// fonction de creation de graph
Graph* init_graph(Netlist* nl){
  // on assume que la netlist est complette
  // ok alors on veut avoir un tableau des noeud segment
  // et un autre sur les noeud points
  Segment** T_Seg = tableau_segments(nl);
  Point** T_Pt = tableau_points(nl);

  int* affectation_via = (int*)malloc(sizeof(int)*nl->nbPt);
  int i=0;
  for(i=0; i<nl->nbPt;i++){
    affectation_via[i] = -1;
  }
  // creation du tableau d'affectation  // callocl()
  Graph* g = (Graph*)malloc(sizeof(Graph));
  g->T_Seg = T_Seg;
  g->T_Pt = T_Pt;
  g->affectation_via = affectation_via;
  

  return g;
}
void afficher_graph(Netlist* nl, Graph* g, char* nomFichier){
  int i;
  //SVGlineRandColor(&img);
  SVGinit(&img, nomFichier, nl->xmin, nl->ymin, nl->xoffsef, nl->yoffset);
  SVGlineRandColor(&img);
  SVGgroup(&img);
  for(i=0; i<nl->nbSeg;i++){
    if(g->T_Seg[i]->affectation == 1){
       afficher_segment(g->T_Seg[i]);
       //printf("H\n");
    }
  }
  SVGgroup_end(&img);

  SVGlineRandColor(&img);
  SVGgroup(&img);
  for(i=0; i<nl->nbSeg;i++){
    if((g->T_Seg[i]->affectation) == 2){
      // dashed
       afficher_segment(g->T_Seg[i]);
       //printf("V\n");
    }
  }
  for(i=0; i<nl->nbPt;i++){
    if(!g->affectation_via[i])
      SVGpoint(&img, g->T_Pt[i]->x, g->T_Pt[i]->y);
  }
  SVGgroup_end(&img);
  SVGfinalize(&img);
}
int getindice_point(Graph* g, Netlist* nl,  Point* p){
  //int indice = p->num_res+p->numpt;
  return 0;
}
int isVia(Graph* g, Point* p){
  //verifier si le fles fils ont des faces differente

  // on fixe la liste
  Cell_segment* cell = p->Lincid;
  int h = p->Lincid->seg->affectation;
  while(cell->suiv){
    if(cell->suiv->seg->affectation != h){
      // c'est un via
      return 0;
    }
    cell = cell->suiv;
  }
  // n'est pas via
  return 1;
}
void methode_naiif(Graph* G, Netlist* nl){
  // creation de S
  //int* s = (int*)malloc(sizeof(int)*(nl->nbSeg + nl->nbPt);
  // affectation des faces
  int i;
  for(i=0; i<nl->nbSeg; i++){
    G->T_Seg[i]->affectation = G->T_Seg[i]->HouV+1;
  }
   // detection de via
  for(i=0; i<nl->nbPt; i++){
    G->affectation_via[i] = isVia(G, G->T_Pt[i]);
  }
 
  return;
}
void graph_dot(Graph* g, Netlist* nl){
  // pour chaque sommet on cree le block ou cercle 
  // on cree les connections 
  // format P12 pour dire point 12
  // S10 pour dire le segment 10
}
// algorithme principale
void minimize_via(Graph* G){
  return;
}
void bicolore(Graph* G){
  // initialise un segment a une face, parcourir

  // mettre tout les fils a l'autre face
  return;
}




// compter le nombre de via dans le graph
int nbr_via(Graph* g, Netlist* nl){
  int i = 0;
  int cpt = 0;
  for(i=0; i<nl->nbPt;i++){
    if(!g->affectation_via)cpt++;
  }
  return cpt;
}

void detect_cycle(Graph* G){
  return;
}
// fonction de viz
void vizualize_graph(Graph* G){
  return;
}
// liberation de memoire graph
void free_graph(Graph* G){
  free(G->T_Pt);
  free(G->T_Seg);
  return;
}
