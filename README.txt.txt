Manuel Utilisateur

Le programme s’exécute de la manière suivante : se placer dans la racine du projet, puis exécuter
 la commande « bin/main -PARAMETRE FICHIER ». « -PARAMETRE » correspond aux paramètres permettant 
de faire les différentes actions disponibles, il en existe trois. « FICHIER » est le fichier à 
compresser ou décompresser. Le fichier peut être n’importe où sur l’ordinateur, il suffit juste 
de glisser et déposer le fichier dans le terminal pour avoir son chemin.

Dans les cas de compression et décompression, le fichier de sorti est directement envoyé au même 
endroit que le fichier d’origine.

Les paramètres disponibles sont les suivants :
    • « -c » : permet de compresser un fichier qui est au format .txt. Le paramètre doit être suivit du chemin vers le fichier.
    • « -d » : permet de décompresser un fichier. Le paramètre doit être suivit du chemin vers le fichier.
    • « -h » : permet d’afficher une aide pour l’utilisateur.

Il est nécessaire d’indiquer le chemin du fichier pour la compression et la décompression, mais 
cela n’est pas nécessaire pour afficher l’aide. 
Lorsque la compression ou décompression est terminée, un message est affiché dans le terminal.

Par exemple, si on veut compresser le fichier « harry_potter.txt », on exécute la commande suivant :
« bin/main -c [chemin du fichier] ». Le fichier en sorti s’appellera alors « harry_potter_Comp.txt »
et se trouvera au même endroit que le fichier d’origine.

Si on veut ensuite décompresser ce fichier, on exécute la commande suivante : 
« bin/main -d [chemin du fichier] ». Le fichier en sorti s’appellera alors 
« harry_potter_Comp_Decomp.txt », et se trouvera au même endroit que le fichier d’origine.