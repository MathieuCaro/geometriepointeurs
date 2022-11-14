#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846264338327950288419716939937510
#define ANGLE_DROIT 90.00
#define _USE_MATH_DEFINES 

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"
#define CYN   "\x1B[36m"
#define MGT   "\x1B[35m"
#define YEL   "\x1B[33m"
#define GRN   "\x1B[32m"
#define FONDBC  "\x1B[47m"
#define GRAS   "\x1B[1m"

typedef struct Point{
    char* nom;
    float coordonne_x;
    float coordonne_y;
}Point;

typedef struct Segment{
    char* nom;
    Point A,B;
    float longueur;
}Segment;

typedef struct Angle{
    Point A,B,C;
    int valeur;
}Angle;

typedef struct Quadrilatere{
    char* figure;
    Point A,B,C,D;
    float longueur, largeur, cote;
    float aire, perimetre;
}Quadrilatere;

typedef struct Triangle{
    char* figure;
    Point A,B,C;
    float longueur, hauteur;
    float cote1,cote2,cote3;
    float aire, perimetre;
}Triangle;

float distance_entre_points(Point A, Point B){
    struct Segment AB;
    float x_ab_2, y_ab_2;
    x_ab_2 = pow(B.coordonne_x-A.coordonne_x,2);
    y_ab_2=pow(B.coordonne_y-A.coordonne_y,2);
    AB.longueur=sqrt(x_ab_2+y_ab_2);
    return AB.longueur;
}

float radiantodeg(float angle_value_rad){
    float angle_value_deg = angle_value_rad*(180/PI);
    return angle_value_deg;
}


float mesure_angle(Point A, Point B, Point C){
    struct Angle ABC;
    float AB = distance_entre_points(A,B);
    float BC = distance_entre_points(B,C);
    float AB_carre=pow(distance_entre_points(A,B),2);
    float BC_carre=pow(distance_entre_points(B,C),2);
    float AC_carre=pow(distance_entre_points(A,C),2);
    float angle_value_rad = acos((BC_carre+AB_carre-AC_carre)/(2*BC*AB));
    ABC.valeur = radiantodeg(angle_value_rad);
    return ABC.valeur;
}

float perimetre(Point A, Point B, Point C, Point D){
    float perimetre = distance_entre_points(A,B)+distance_entre_points(B,C)+distance_entre_points(C,D)+distance_entre_points(D,A);
    return perimetre;
}

float aire(Point A, Point B, Point C, Point D){
    float aire = distance_entre_points(A,B)*distance_entre_points(B,C);
    return aire;
}

float aire_triangle_isocele_equilateral(Point A, Point B, Point C){
    float milieu_AC_x = (A.coordonne_x+C.coordonne_x)/2;
    float milieu_AC_y = (A.coordonne_y+C.coordonne_y)/2;
    Point H = {"H",H.coordonne_x=milieu_AC_x,H.coordonne_y};
    float BH = distance_entre_points(B,H);
    float AC = distance_entre_points(A,C);
    float aire = (AC*BH)/2;
    return aire;
}

float aire_triangle_rectangle(float cote1,float cote2){
    float aire=(cote1*cote2)/2;
    return aire;
}

int is_equilateral(float longueur1,float longueur2,float longueur3){
    if((longueur1==longueur2)&&(longueur2==longueur3)){
        return 1;
    }else{
        return 0;
    }  
}

int is_triangle_rectangle(Point A, Point B, Point C){
    if((mesure_angle(A,B,C)==ANGLE_DROIT)||(mesure_angle(B,C,A)==ANGLE_DROIT)||(mesure_angle(C,A,B)==ANGLE_DROIT)){
        return 1;
    } else{
        return 0;
    }
}

Triangle is_triangle_rectangle_isocele(Triangle T, float angle1, float angle2, float angle3){
        if(angle1==ANGLE_DROIT){
            float hypothenus =T.cote3;
            float Aire = aire_triangle_rectangle(T.cote1,T.cote2);
            T.aire=Aire;
            if(T.cote1==T.cote2){
                T.figure="Rectangle isocèle";
            }
        }
        if(angle2==ANGLE_DROIT){
            float hypothenus =T.cote1;
            float Aire = aire_triangle_rectangle(T.cote2,T.cote3);
            T.aire=Aire;
            if(T.cote3==T.cote2){
                T.figure="Rectangle isocèle";
            }
        }
        else{
            float hypothenus = T.cote2;
            float Aire = aire_triangle_rectangle(T.cote1,T.cote3);
            T.aire=Aire;
             if(T.cote3==T.cote1){
                T.figure="Rectangle isocèle";
            }
        }
        return T;
    }


Triangle is_triangle(Point A, Point B, Point C){
    Triangle T1={"",A,B,C};
    float AB_1 = distance_entre_points(T1.A,T1.B);
    float BC_1 = distance_entre_points(T1.B,T1.C);
    float CA_1 = distance_entre_points(T1.C,T1.A);
    float angle_ABC=mesure_angle(A,B,C);
    float angle_BCA=mesure_angle(B,C,A);
    float angle_CAB=mesure_angle(C,A,B);

    if(is_equilateral(AB_1,BC_1,CA_1)==1){
        T1.figure="Equilateral";
        T1.cote1=AB_1;
        T1.aire=aire_triangle_isocele_equilateral(A,B,C);
        T1.perimetre=AB_1+BC_1+CA_1;
    }
     if(is_triangle_rectangle(A,B,C)==1){
        T1.figure="Rectangle";
        T1.perimetre=AB_1+BC_1+CA_1; 
        T1.cote1=AB_1,T1.cote2=BC_1,T1.cote3=CA_1;
        T1=is_triangle_rectangle_isocele(T1,angle_ABC,angle_BCA, angle_CAB);
    }
    return T1;
}
 
Quadrilatere is_quadrilatere(Point A, Point B, Point C, Point D){
    Quadrilatere Q1={"",A,B,C,D};
    float AB = distance_entre_points(Q1.A,Q1.B);
    float BC = distance_entre_points(Q1.B,Q1.C);
    float CD = distance_entre_points(Q1.C,Q1.D);
    float DA = distance_entre_points(Q1.D,Q1.A);
    if((mesure_angle(A,B,C)==mesure_angle(B,C,D))&&(mesure_angle(B,C,D)==mesure_angle(C,D,A))&&(mesure_angle(C,D,A)==mesure_angle(D,A,B))){
        if((AB==BC)&&(BC==CD)){
            Q1.figure ="Carre";
            Q1.cote=AB;
            Q1.aire=aire(A,B,C,D);
            Q1.perimetre=perimetre(A,B,C,D);
        }else if((AB==CD)&&(AB!=BC)){
            printf("%s",Q1.figure);
            Q1.figure ="Rectangle";
            if(AB<BC){
                Q1.largeur=AB;
                Q1.longueur=BC;
            }else{
                Q1.largeur=BC;
                Q1.longueur=AB;
            }
            Q1.aire=aire(A,B,C,D);
            Q1.perimetre=perimetre(A,B,C,D);
        } 
    };
    return Q1;
}

 
int main(void){

    printf(GRAS GRN"\n****************************************************************  Exemple 1: Point  ****************************************************************\n\n"RESET);
    Point A1_1={"A1",10,20};
    printf("Point %s(x:%f,y:%f)\n",A1_1.nom,A1_1.coordonne_x,A1_1.coordonne_y);
    Point A1_2={"A2",0,5};
    printf("Point %s(x:%f,y:%f)\n",A1_2.nom,A1_2.coordonne_x,A1_2.coordonne_y);
    Point A1_3={"A3",-2,3};
    printf("Point %s(x:%f,y:%f)\n",A1_3.nom,A1_3.coordonne_x,A1_3.coordonne_y);
    printf(GRAS YEL "\n****************************************************************  Exemple 2: Segment ****************************************************************\n\n"RESET);
    Point A2_1={"A",3,2},B2_1={"B",5,7};
    Segment S1={"AB_1",A2_1,B2_1};
    S1.longueur=distance_entre_points(A2_1,B2_1);
    printf("Segment %s(longueur:%f)\n",S1.nom,S1.longueur);
    Point A2_2={"A",4,7},B2_2={"B",10,14};
    Segment S2={"AB_2",A2_2,B2_2};
    S2.longueur=distance_entre_points(A2_2,B2_2);
    printf("Segment %s(longueur:%f)\n",S2.nom,S2.longueur);
    printf(GRAS CYN"\n*****************************************************************  Exemple 3: Carre  *****************************************************************\n\n"RESET);
    Point A3_1={"A",0,0},B3_1={"B",0,2},C3_1={"C",2,2},D3_1={"D",2,0};
    Quadrilatere Q1 = is_quadrilatere(A3_1,B3_1,C3_1,D3_1);
    printf("Quadrilatère(Type:%s, Longueur:%f, Perimetre:%f, Aire:%f)\n",Q1.figure,Q1.cote,Q1.perimetre,Q1.aire);
    Point A3_2={"A",0,5},B3_2={"B",5,0},C3_2={"C",10,5},D3_2={"D",5,10};
    Quadrilatere Q2 = is_quadrilatere(A3_2,B3_2,C3_2,D3_2);
    printf("Quadrilatère(Type:%s, Longueur:%f, Perimetre:%f, Aire:%f)\n",Q2.figure,Q2.cote,Q2.perimetre,Q2.aire);
    printf(GRAS CYN"\n**************************************************************** Exemple 4: Rectangle  ****************************************************************\n\n"RESET);
    Point A4_1={"A",0,0},B4_1={"B",0,2},C4_1={"C",4,2},D4_1={"D",4,0};
    Quadrilatere Q3 = is_quadrilatere(A4_1,B4_1,C4_1,D4_1);
    printf("Quadrilatère(Type:%s, Longueur:%f, Largeur:%f, Perimetre:%f, Aire:%f)\n",Q3.figure,Q3.longueur,Q3.largeur,Q3.perimetre,Q3.aire);
    Point A4_2={"A",-10,-2},B4_2={"B",-10,2},C4_2={"C",20,2},D4_2={"D",20,-2};
    Quadrilatere Q4 = is_quadrilatere(A4_2,B4_2,C4_2,D4_2);
    printf("Quadrilatère(Type:%s, Longueur:%f, Largeur:%f, Perimetre:%f, Aire:%f)\n",Q4.figure,Q4.longueur,Q4.largeur,Q4.perimetre,Q4.aire);
    Point A4_3={"A",0,0},B4_3={"B",0,10},C4_3={"C",20,10},D4_3={"D",20,0};
    Quadrilatere Q5 = is_quadrilatere(A4_3,B4_3,C4_3,D4_3);
    printf("Quadrilatère(Type:%s, Longueur:%f, Largeur:%f, Perimetre:%f, Aire:%f)\n",Q5.figure,Q5.longueur,Q5.largeur,Q5.perimetre,Q5.aire);
    printf(GRAS RED "\n********************************************************  Exemple 5: Triangle Equilateral ************************************************************\n\n"RESET);
    Point A5_1={"A",0.0,0.0},B5_1={"B",2.5,sqrt(18.75)},C5_1={"C",5,0};
    Triangle T1 = is_triangle(A5_1,B5_1,C5_1);
    printf("Triangle(type:%s, Longueur du coté : %f, Périmètre: %f, Aire: %f)\n", T1.figure,T1.cote1,T1.perimetre,T1.aire);
    Point A5_2={"A",-10,0.0},B5_2={"B",0,sqrt(300)},C5_2={"C",10,0};
    Triangle T2 = is_triangle(A5_2,B5_2,C5_2);
    printf("Triangle(type:%s, Longueur du coté : %f, Périmètre: %f, Aire: %f)\n", T2.figure,T2.cote1,T2.perimetre,T2.aire);
    printf(GRAS RED "\n********************************************************* Exemple 6: Triangle Rectangle **************************************************************\n\n"RESET);
    Point A6_1={"A",0.0,0.0},B6_1={"B",0,4},C6_1={"C",10,0};
    Triangle T3 = is_triangle(A6_1,B6_1,C6_1);
    printf("Triangle(Type:%s(Longueur des cotés(1:%f,2:%f,3:%f),Périmètre: %f, Aire: %f)\n", T3.figure,T3.cote1,T3.cote2,T3.cote3,T3.perimetre,T3.aire);
    Point A6_2={"A",-10,0.0},B6_2={"B",0,5},C6_2={"C",0,0};
    Triangle T4 = is_triangle(A6_2,B6_2,C6_2);
    printf("Triangle(Type:%s(Longueur des cotés(1:%f,2:%f,3:%f),Périmètre: %f, Aire: %f)\n", T4.figure,T4.cote1,T4.cote2,T4.cote3,T4.perimetre,T4.aire);
    printf(GRAS RED"\n****************************************************** Exemple 7: Triangle Rectangle Isocele **********************************************************\n\n"RESET);
    Point A7_1={"A",0.0,0.0},B7_1={"B",0,10},C7_1={"C",10,0};
    Triangle T5 = is_triangle(A7_1,B7_1,C7_1);
    printf("Triangle(Type:%s(Longueur des cotés(1:%f,2:%f,3:%f),Périmètre: %f,Aire: %f)\n", T5.figure,T5.cote1,T5.cote2,T5.cote3,T5.perimetre,T5.aire);
    Point A7_2={"A",-5,0.0},B7_2={"B",0,5},C7_2={"C",0,0};
    Triangle T6 = is_triangle(A7_2,B7_2,C7_2);
    printf("Triangle(Type:%s(Longueur des cotés(1:%f,2:%f,3:%f),Périmètre: %f,Aire: %f)\n\n", T6.figure,T6.cote1,T6.cote2,T6.cote3,T6.perimetre,T6.aire);
    

}