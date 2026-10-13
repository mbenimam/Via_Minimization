#include "segment.h"
Segment* initialize_segment(int NumRes, int p1, int p2, int HouV, int numSg){
  Segment* temp = (Segment*)malloc(sizeof(Segment));
  // s'il y a une erreur
  if(!temp){
    fprintf(stderr, "Erreur Allocation espace Segment\n");
    return NULL;
  }

  // sinon on initialise les variables
  temp->NumRes = NumRes;// numero du reseau
  temp->p1 = p1; // le premier point
  temp->p2 = p2; // le deuxieme point
  temp->HouV=HouV;// 0 horizontal 1 vertical
  temp->Lintersec = NULL; // il n'y a pas d'intersection pour l'instant
  temp->printed = 0;
  temp->numSg = numSg;
  temp->affectation = -1;
  // et finallement on retourene le pointeur
  return temp;
}
void afficher_segment(Segment* seg){
  if(seg->printed>=2){
    printf("WTF\n");
    seg->printed = 0;
    return;
  }
  seg->printed=1;
  //char c = (seg->HouV == 0) ? 'H':'V';
  // printf("%c", c);
  /*if(svg != NULL){*/
    double xa, xb, ya, yb;
    Point** pt = netlist_globale->T_Res[seg->NumRes]->T_Pt;
    xa=pt[seg->p1]->x;
    ya=pt[seg->p1]->y;
    xb=pt[seg->p2]->x;
    yb=pt[seg->p2]->y;
    //printf("%.f(%d)", ya, seg->NumRes);
 SVGline(&img, xa, ya, xb, yb);
//}
}
