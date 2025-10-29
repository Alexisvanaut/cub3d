1. Structure et Setup Initial

 Créer la structure principale pour stocker les données parsées:

typedef struct s_data {
      char *no_texture;  // Chemin texture Nord
      char *so_texture;  // Chemin texture Sud
      char *we_texture;  // Chemin texture Ouest
      char *ea_texture;  // Chemin texture Est
      int floor_color[3];   // RGB floor
      int ceiling_color[3]; // RGB ceiling
      char **map;           // Map 2D
      int map_width;
      int map_height;
      char player_dir;      // N, S, E, ou W
      int player_x;
      int player_y;
  } t_data;

2. Lecture du Fichier

 Vérifier que l'argument est bien un fichier .cub
 Vérifier que le fichier existe et peut être ouvert
 Lire tout le fichier ligne par ligne
 Stocker les lignes dans un tableau temporaire

3. Parsing des Textures

 Parser la ligne NO et stocker le chemin
 Parser la ligne SO et stocker le chemin
 Parser la ligne WE et stocker le chemin
 Parser la ligne EA et stocker le chemin
 Vérifier que chaque texture existe et est accessible
 Vérifier qu'il n'y a pas de doublons (pas deux fois NO par exemple)

4. Parsing des Couleurs

 Parser la ligne F (Floor) au format R,G,B
 Parser la ligne C (Ceiling) au format R,G,B
 Vérifier que les valeurs RGB sont dans [0,255]
 Vérifier le format (virgules, pas d'espaces superflus, etc.)
 Vérifier qu'il n'y a pas de doublons

5. Parsing de la Map

 Identifier où commence la map (après toutes les configs)
 Récupérer toutes les lignes de la map
 Stocker la map dans un tableau 2D (char **)
 Gérer les espaces (ils font partie de la map!)
 Calculer la largeur et hauteur de la map

6. Validation de la Map

 Vérifier qu'il y a UN SEUL joueur (N, S, E, ou W)
 Stocker la position et direction du joueur
 Vérifier que la map contient uniquement: 0, 1, N, S, E, W, et espaces
 Vérifier que la map est fermée/entourée de murs:

 Première et dernière ligne = que des 1 ou espaces
 Première et dernière colonne = que des 1 ou espaces
 Flood fill ou algo similaire pour vérifier qu'on ne peut pas "sortir"
 Vérifier que les 0 ne touchent pas les espaces/bords



7. Gestion d'Erreurs

 Afficher "Error\n" suivi d'un message explicite pour:

 Mauvaise extension de fichier
 Fichier introuvable
 Texture manquante ou doublon
 Couleur manquante, doublon, ou invalide
 Map invalide (pas fermée, mauvais caractères, etc.)
 Pas de joueur ou plusieurs joueurs
 Mauvais format général


 Libérer toute la mémoire allouée avant de sortir

8. Fonctions Utilitaires à Créer

 ft_split pour séparer les lignes
 skip_spaces pour ignorer les espaces
 is_valid_map_char pour valider les caractères
 get_next_line ou équivalent pour lire le fichier
 Fonctions de free pour nettoyer la mémoire

9. Tests à Faire

 Fichier valide basique
 Map avec espaces
 Map non fermée (doit error)
 Plusieurs joueurs (doit error)
 Pas de joueur (doit error)
 Couleurs > 255 (doit error)
 Textures manquantes (doit error)
 Éléments en désordre (doit fonctionner)
 Lignes vides entre les éléments (doit fonctionner)