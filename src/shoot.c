#include "shoot.h"
#include "battle_c.h"

float Get_Radius_Angle(float x, float y){
    return atan2f(y, x); 
}

float Calculate_Position(float x_a, float x_b, float y_a, float y_b){
    float delta_x = x_b - x_a;  // Inverser ici
    float delta_y = y_b - y_a;  // Inverser ici
    
    // Affichage des coordonnées pour déboguer
    printf("Calcul de l'angle:\n");
    printf("x_a = %f, x_b = %f, y_a = %f, y_b = %f\n", x_a, x_b, y_a, y_b);
    printf("Delta x = %f, Delta y = %f\n", delta_x, delta_y);

    // Calcul et affichage de l'angle
    float angle = Get_Radius_Angle(delta_x, delta_y);
    printf("Angle calculé (en radians) : %f\n", angle);

    return angle;
}

BC_ShootResult ShootOnTarget(BC_Connection *connection, float x_a, float x_b, float y_a, float y_b){
    printf("Tir en cours...\n");

    // Calcul de l'angle avant d'effectuer le tir
    float angle = Calculate_Position(x_a, x_b, y_a, y_b);

    // Appel à la fonction de tir
    return bc_shoot(connection, angle);
}

char* BC_ShootResultFailReasonToString(enum BC_ShootResultFailReason_ type) {
    // Traduction de l'énumération de la raison de l'échec en chaîne de caractères
    switch (type) {
        case UNKNOWN: return "Échec inconnu";
        case COOLDOWN: return "Cooldown (temps de recharge)";
        case MISS: return "Tir raté";
        default: return "Raison de l'échec inconnue";
    }
}

void printShootInfo(BC_ShootResult shootresult){
    // Affichage des résultats du tir pour le débogage
    printf("Résultats du tir :\n");
    printf("Succès : %d\n", shootresult.success);
    printf("Target ID = %d\n", (int) shootresult.target_id);
    printf("Dégats : %d\n", (int) shootresult.damage_points);
    printf("Cible détruite ? : %d\n", shootresult.target_destroyed);
    printf("Raison de l'échec : %s\n", BC_ShootResultFailReasonToString(shootresult.fail_reason));   
}