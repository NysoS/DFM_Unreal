# DFM_Unreal

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
    Appele la fonctione de OntakeDamage() du composant de vie (LifeComponent),
    et appele la fonction ResetSpawn
    ```
    
  * ResetSpawn
    ```
    Réinitialise la position du joueur à sa position d'apparition lors du lancement du niveau
    ```
    
  * AddCollectible
    ```
    Incrémente le nombre de collectible
    ```
    
  * RemoveCollectible
    ```
    Décrément le nombre de collectible
    ```
    
  * GetCountCollectible()
    ```
    Retourne le nombre de collectible
    ```

### LifeComponent
  
  * GetMaxLife
    ```
    Retourne le nombre maximum de vie
    ```
    
  * GetLife
    ```
    Retourne le nombre de vie
    ```
    
  * OntakeDamage
    ```
    Décrémente le nombre de vie,
    Si le nombre de vie est à 0, on recharge le niveau
    Sinon on appele l'événement DelegateTakeDamage en passant le nombre de vie restant  
    ```

### Collectible

  * NotifyActorBeginOverlap
    ```
    Est appeler lorsque le joueur entre en collision avec un objet,
    Incrément de 1 au joueur son nombre de pièce,
    Appele l'événement DelegateTakeCollectible pour afficher la nouvelle valeur sur l'UI,
    Détruie la pièce  
    ```

### BasicTrap

  * NotifyActorBeginOverlap
    ```
    Vérifie si l'object qui rentre en collision avec lui est le joueur,
    Si c'est le joueur, on appele la fonction Trapped du joueur
    ```

### EndingZone

  * NotifyActorBeginOverlap
    ```
    Vérifie si l'object qui rentre en collision avec lui est le joueur,
    Si le joueur a collecté toutes les pièces du niveau,
    On appele l'événement 'DelegateEndGame' de fin de niveau
    ```

### WBP_Life

  * Event Pre Construct
    ```
    S'abonne à l'événement TakeDamage du composant 'LifeComponent',
    Appele la fonction RemoveLife, lorsque l'événement TakeDamage est appelée
    ```
    
  * Event Construct
    ```
    Récupère le nombre de vie maximum, 
    Appele la fonction DrawLife
    ```
    
  * DrawLife
    ```
    Affiche le nombre de vie sur l'UI
    ```
    
  * RemoveLife
    ```
    Retire une vie sur l'UI
    ```

### UICollectible

  * NativeConstruct
    ```
    Récupère la liste de toutes pièces du niveau,
    S'abonne à l'événement 'DelegateTakeCollectible' pour chaque pièce
    ```
    
  * OnTakeCollectible
    ```
    Incrément le nombre de collectible,
    Affiche le nombre de collectible sur l'UI
    ```

- - - - 

## Partie 2 - Dash circulaire

### DFM1Character

  * LeftDash
    ```
    Effectue le dash circulaire vert la gauche
    ```
    
  * RightDash
    ```
    Effectue le dash circulaire vert la droite
    ```

### DashComponent

  * DashMoving
    ```
    Configure la l'orientation du dash et lance le mouvement du dash,
    Si la projection du dash a detectée aucun obstacle
    ```
    
  * CanDash
    ```
    Project le mouvement du dash de facon circulaire
    Si il y a un obstacle sur la trajectoire on annule le dash
    Retourne true, si aucun obstacle a été détecté
    ```
    
  * DashProgress
    ```
    Effectue le mouvement du dash a chaque frame, selon l'orientation du dash
    Le personnage se déplace sur chaque position projeter selon une vitesse définie/le nombre de position projeter
    ```
    
  * DashReset
    ```
    Réinitialise la configuration du mouvement du dash
    ```
    
  * IsDashing
    ```
    Retourne l'état du dash
    ```
    
  * SetOrientationDash
    ```
    Configure l'orientation du dash
    ```
    
  * TickComponent
    ```
    On appele les fonction 'DashProgress' et 'DashReset'
    ```