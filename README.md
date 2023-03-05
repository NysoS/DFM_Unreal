# DFM_Unreal

Build du projet dans le dossier build

## Partie 1

### DFM1Character
  * Move
    ```
    Déplace le personnage selon les touches zqsd
    ```
    
  * FellOutOfWorld
    ```
    Fonction de callback, 
    lorsque le joueur tombe dans le vide, elle appele la fonction Trapped
    ```
    
  * Trapped
    ```
    Appelle la fonction OntakeDamage() du composant de vie (LifeComponent),
    et appele la fonction ResetSpawn
    ```
    
  * ResetSpawn
    ```
    Réinitialise la position du joueur à sa position d'apparition au lancement du niveau
    ```
    
  * AddCollectible
    ```
    Incrémente le nombre de collectables
    ```
    
  * RemoveCollectible
    ```
    Décrémente le nombre de collectables
    ```
    
  * GetCountCollectible()
    ```
    Retourne le nombre de collectables
    ```

### LifeComponent
  
  * GetMaxLife
    ```
    Retourne la valeur maximum de point vie
    ```
    
  * GetLife
    ```
    Retourne la valeur des points de vie actuel
    ```
    
  * OntakeDamage
    ```
    Décrémente la valeur des points de vie actuel,
    Si le nombre de vie est à 0, le niveau est réinitialisé
    Dans le cas contraire l'événement DelegateTakeDamage est appellé avec la valeur des points de vie actuel  
    ```

### Collectible

  * NotifyActorBeginOverlap
    ```
    Est appellée lorsque le joueur entre en collision avec ce type d'objet,
    Incrémente de 1 le nombre de pièce du joueur,
    Appelle l'événement DelegateTakeCollectible afin d'affiché la nouvelle valeur dans l'UI,
    Détruie la pièce  
    ```

### BasicTrap

  * NotifyActorBeginOverlap
    ```
    Vérifie si l'object entrant en collision est le joueur,
    Si c'est le cas, la fonction Trapped du joueur est appllée
    ```

### EndingZone

  * NotifyActorBeginOverlap
    ```
    Vérifie si l'object entrant en collision est le joueur,
    Si le joueur a collecté toutes les pièces du niveau,
    L'événement 'DelegateEndGame' de fin de niveau est appellé
    ```

### WBP_Life

  * Event Pre Construct
    ```
    Abonner à l'événement TakeDamage du composant 'LifeComponent',
    Appelle la fonction RemoveLife, lorsque l'événement TakeDamage est déclenché
    ```
    
  * Event Construct
    ```
    Récupère la valeur de points de vie maximum, 
    Appelle la fonction DrawLife
    ```
    
  * DrawLife
    ```
    Affiche la valeur du nombre de points de vie dans l'UI
    ```
    
  * RemoveLife
    ```
    Retire un point de vie dans l'UI
    ```

### UICollectible

  * NativeConstruct
    ```
    Récupère la liste de toutes pièces du niveau,
    S'abonne à l'événement 'DelegateTakeCollectible' pour chaque pièce
    ```
    
  * OnTakeCollectible
    ```
    Incrémente la valeur le nombre de collectables récupérés,
    Affiche la valeur du nombre de collectables récupérés dans l'UI
    ```

- - - - 

## Partie 2 - Dash semi-circulaire

### DFM1Character

  * LeftDash
    ```
    Effectue un dash semi-circulaire vers la gauche
    ```
    
  * RightDash
    ```
    Effectue un dash semi-circulaire vers la droite
    ```

### DashComponent

  * DashMoving
    ```
    Etablie l'orientation du dash et éxecute le mouvement du personnage,
    Si la projection du dash a detectée aucun obstacle
    ```
    
  * CanDash
    ```
    Calcul le mouvement du dash de facon semi-circulaire
    Au contact d'un obstacle, la trajectoire dash est annulé
    La valeur true est retournée, si aucun obstacle n'a été détecté
    ```
    
  * DashProgress
    ```
    Effectue le mouvement du dash à chaque frame,
    Le personnage est déplacé sur chaque position calculée avec sa vitesse définie
    ```
    
  * DashReset
    ```
    Réinitialise le calcul du dash
    ```
    
  * IsDashing
    ```
    Retourne l'état du dash
    ```
    
  * SetOrientationDash
    ```
    Etablie l'orientation du dash
    ```
    
  * TickComponent
    ```
    Les fonctions 'DashProgress' et 'DashReset' sont appellées
    ```