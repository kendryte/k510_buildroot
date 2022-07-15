[![Référentiel Gitee](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
 [![Version gitHub](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

* [English](../README.md)
* [简体中文](README.zh-Hans.md)
* [繁體中文](README.zh-Hant.md)
* [Nederlands](README.nl.md)
* [Français](README.fr.md)
* [Deutsch](README.de.md)
* [Italiano](README.it.md)
* [日本語](README.ja.md)
* [한국어](README.ko.md)
* [Русский](README.ru.md)
* [Español](README.es.md)
* [Polski](README.pl.md)

# Kit de développement logiciel (SDK) K510

Kanzhi K510 est la deuxième génération de puces d'inférence côté bord IA lancées par Canaan, qui offre des capacités de traitement d'image et de parole hautes performances pour les applications d'IA. Le K510 est équipé du processeur de réseau neuronal de deuxième génération KPU2.0, qui adopte la technologie de flux de données informatiques d'origine, qui augmente la puissance de calcul de 3 fois par rapport à la génération précédente et réduit la consommation d'énergie. Intégré à la dernière génération de processeur d'image ISP, prend en charge l'accès à la caméra de profondeur TOF, prend en charge la réduction du bruit 2D / 3D, la plage dynamique étendue (WDR), le matériel 3A et d'autres fonctions complètes. Les FAI 3D prennent en charge les capteurs TOF de caméra de profondeur. Il peut être largement utilisé dans différents domaines d'application tels que les véhicules aériens sans pilote, la photographie aérienne haute définition, les caméras professionnelles, la vidéoconférence, les robots intelligents, les STEAM éducatifs et la conduite assistée automatique.

K510 SDK est un kit de développement logiciel fourni par Canaan pour le développement d'applications de puce K510, sa configuration par défaut est basée sur K510 CRB (plate-forme de référence client), le contenu de l'entrepôt comprend le logiciel toolchain, la boîte à outils PC, le code Linux, le chargeur de démarrage, le bbl, le logiciel de système de construction buildroot et les documents de ressources matérielles connexes que les utilisateurs peuvent utiliser dans le développement de la puce K510. Les utilisateurs peuvent personnaliser le développement des modifications en fonction de leurs propres besoins en fonction de cet ensemble de base de code logiciel, et enfin créer et compiler le fichier image utilisé pour le déploiement.

## Descriptions du contenu matériel et liens vers des ressources de référence

| Non | Adresse du lien | illustrer  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | Le code compile le répertoire de travail |
|2|[docs/](https://github.com/kendryte/k510_docs)| Compilation du système K510 et documentation sur le développement d'applications; Documentation d'introduction aux ressources matérielles
|3|[forfait/](/package/)| Fournir des exemples d'applications de développement de périphériques système Linux; Divers codes sources d'applications de démonstration d'IA  |
|4|[Canaan Kanchi](https://canaan-creative.com/product/勘智k510)|Site officiel de Canaan Kanji|
|5|[Communauté de développeurs](https://canaan-creative.com/developer)|Canaan Kanchi Forum
|6|[Vidéo de démonstration](https://space.bilibili.com/677429436)|Vidéo prête à l'emploi de la carte de développement K510 et plusieurs vidéos de démonstration d'applications d'IA|
|7|[K510 CRB-KIT](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510 Board Kit Lien d'achat en ligne|
|8|Communication instantanée|  Community Mutual Aid QQ Group: 790699378</br>Telegram: nncase community |

## Introduction à la suite de développeurs CRB K510

K510 CRB-KIT est une suite de développeurs basée sur le développement de la puce K510, qui adopte une conception hiérarchique, basée sur le module central K510, avec des périphériques riches et faciles à étendre. Prise en charge USB 2.0 OTG + PHY, port Gigabit Ethernet, 3xSDIO, 3xSPI et autres interfaces de communication haute vitesse, prise en charge de 4xUART, GPIO, I2C et I2S et autres interfaces de communication à faible vitesse. Simple à utiliser, informatif, peut aider les clients à réaliser rapidement une évaluation créative, une vérification du prototype de produit, raccourcir le cycle de conception du produit.
![Canaan-board .png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB photo frontale </center>

![hw_1_3.png
](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png) d'image <center>Schéma fonctionnel du système K510</center>  

![hw_3_1.png d'](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
image <center>Diagramme du module de la carte centrale K510</center>  

## Premiers pas avec le développement logiciel K510

### Configurer un environnement de développement logiciel

Le développement logiciel K510 est basé sur un environnement Linux. Les utilisateurs doivent préparer un hôte avec un système d'exploitation Linux pour la compilation et le déploiement de logiciels, et si vous travaillez sous Windows, il est recommandé d'installer Windows WSL pour le travail de développement logiciel.

### Téléchargement du code source

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### Démarrer Docker

```sh
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

### Compiler la base de code

Après être entré dans l'environnement docker, entrez la commande suivante pour compiler le système.

```sh
make dl
make
```

`make dl`Étape facultative pour accélérer les téléchargements de code source.
Le premier nouveau système prend beaucoup de temps à compiler, alors soyez patient (le temps est lié aux performances du processeur hôte et à la vitesse des téléchargements réseau).

### Flashez le fichier image

Le K510 prend en charge les modes de démarrage sdcard et eMMC, et les utilisateurs peuvent basculer entre différents modes de démarrage en modifiant les paramètres du commutateur SW1 sur la carte ouverte.  
La valeur d'usine par défaut est de démarrer à partir d'emmc. Pour faciliter le développement, il est recommandé de préparer une carte TF et de basculer le commutateur de code en mode de démarrage de la carte SD, puis d'envisager de transformer le fichier image en emmc.  
Que vous travailliez sous Linux ou Windows, vous pouvez télécharger [l'outil Etcher](https://www.balena.io/etcher/) pour graver le fichier image compilé (k510_buildroot/k510_crb_lp3_v1_2_defconfig/image/sysimage-sdcard.img) sur votre carte TF.
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### Fonctionnement sous tension

Vérifiez que le commutateur SW1 est sélectionné en mode de démarrage de la carte SD, insérez la carte TF gravée dans l'emplacement pour carte ouvert, puis débranchez le commutateur d'alimentation K1 en position ON et le système peut s'allumer. Vous verrez l'écran afficher l'écran du logo CANAAN, si vous avez un port série connecté, vous pouvez voir la sortie du journal de démarrage dans le port série.
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### Modifier le programme de démarrage par défaut

Par défaut, le système exécute automatiquement l'exemple de programme (v4l2_drm.out) sous le chemin d'accès /app/mediactl_lib on. Vous pouvez également modifier manuellement le programme de configuration pour exécuter d'autres programmes de démonstration à la place. Voici comment le modifier :

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## Contribution Guide

Si vous êtes intéressé par ce projet et que vous souhaitez obtenir des commentaires sur un problème ou soumettre un code, veuillez vous référer à[CONSOLIDATION](.github/CONTRIBUTING.md)

## Contactez-nous

Beijing Canaan Jiesi Information Technology Co., Ltd  
URL:[canaan-creative.com](https://canaan-creative.com)  
Demandes de renseignements des entreprises :[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**Clause de non-responsabilité en matière de**  
Pour la commodité des clients, Canaan utilise un traducteur IA pour traduire du texte en plusieurs langues, ce qui peut contenir des erreurs. Nous ne garantissons pas l'exactitude, la fiabilité ou l'actualité des traductions fournies. Canaan ne sera pas responsable de toute perte ou dommage causé par la confiance accordée à l'exactitude ou à la fiabilité des informations traduites. S'il existe une différence de contenu entre les traductions dans différentes langues, la version simplifiée en chinois prévaudra.

Si vous souhaitez signaler une erreur de traduction ou une inexactitude, n'hésitez pas à nous contacter par courrier.
