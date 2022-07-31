[![Gitee opslagplaats](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
 [![GitHub-release](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

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

# K510 SDK

Kendryte K510 is de tweede generatie AI edge-side inferentiechips gelanceerd door Canaan, die hoogwaardige beeld- en spraakverwerkingsmogelijkheden biedt voor AI-toepassingen. De K510 is uitgerust met de zelfontwikkelde tweede generatie neurale netwerkprocessor KPU2.0, die de originele computergegevensstroomtechnologie overneemt, die de rekenkracht met 3 keer verhoogt in vergelijking met de vorige generatie en het stroomverbruik vermindert. Geïntegreerd met de nieuwste generatie beeldprocessor ISP, ondersteuning voor TOF-dieptecameratoegang, ondersteuning voor 2D / 3D-ruisonderdrukking, breed dynamisch bereik (WDR), hardware 3A en andere complete functies. 3D ISP's ondersteunen dieptecamera TOF-sensoren. Het kan op grote schaal worden gebruikt in verschillende toepassingsgebieden, zoals onbemande luchtvaartuigen, high-definition luchtfotografie, professionele camera's, videoconferenties, intelligente robots, educatieve STEAM en automatisch geassisteerd rijden.

K510 SDK is een software development kit geleverd door Canaan voor K510 chip applicatie ontwikkeling, de standaard configuratie is gebaseerd op K510 CRB (klant referentie platform), de magazijn inhoud omvat de toolchain software, PC toolkit, Linux code, bootloader, bbl, buildroot build systeem software en gerelateerde hardware resource documenten die gebruikers kunnen gebruiken bij de ontwikkeling van K510 chip. Gebruikers kunnen de wijzigingsontwikkeling aanpassen aan hun eigen behoeften op basis van deze set softwarecodebasis en ten slotte het installatiekopiebestand bouwen en compileren dat wordt gebruikt voor implementatie.

## Beschrijvingen van materiaalinhoud en links naar referentiebronnen

| Nee | Link adres | illustreren  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | De code compileert de werkmap |
|2|[docs/](https://github.com/kendryte/k510_docs)| K510 systeem compilatie en applicatie ontwikkeling documentatie; Documentatie voor de introductie van hardwarebronnen
|3|[pakket/](/package/)| Geef linux systeem randapparatuur ontwikkeling applicatie voorbeelden; Diverse AI demo applicatie broncode  |
|4|[Kanaän Kendryte](https://canaan-creative.com/product/勘智k510)|Canaan Kendryte officiële website|
|5|[Ontwikkelaarscommunity](https://canaan-creative.com/developer)|Kanaän Kendryte Forum
|6|[Demo video](https://space.bilibili.com/677429436)|K510 development board out-of-the-box video en meerdere AI-applicatie demonstratie video's|
|7|[K510 CRB-KIT](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510 Board Kit Online Aankoop Link|
|8|Directe communicatie|  Community Mutual Aid QQ Group: 790699378</br>Telegram: nncase community |

## Inleiding tot de K510 CRB Developer Suite

K510 CRB-KIT is een ontwikkelaarssuite op basis van de ontwikkeling van de K510-chip, die een hiërarchisch ontwerp aanneemt, gebaseerd op de K510-kernmodule, met rijke randapparatuur en gemakkelijk uit te breiden. Ondersteuning USB 2.0 OTG + PHY, Gigabit Ethernet-poort, 3xSDIO, 3xSPI en andere high-speed communicatie-interfaces, ondersteuning voor 4xUART, GPIO, I2C en I2S en andere low-speed communicatie-interfaces. Eenvoudig te gebruiken, informatief, kan klanten helpen snel creatieve evaluatie, productprototypeverificatie te bereiken en de productontwerpcyclus te verkorten.
![Kanaän-board .png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB voorfoto </center>

![afbeelding-hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
 <center>K510 systeem blokdiagram</center>  

![afbeelding-hw_3_1.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
 <center>K510 core board module diagram</center>  

## Aan de slag met K510 software ontwikkeling

### Een softwareontwikkelingsomgeving instellen

K510 software ontwikkeling is gebaseerd op een Linux omgeving. Gebruikers moeten een host met een Linux-besturingssysteem voorbereiden op het compileren en implementeren van software, en als u onder Windows werkt, wordt het aanbevolen om Windows WSL te installeren voor softwareontwikkelingswerk.

### Broncode downloaden

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### Docker starten

```sh
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

### Compileer de codebasis

Nadat u de dockeromgeving hebt geopend, voert u de volgende opdracht in om het systeem te compileren.

```sh
make dl
make
```

`make dl`Optionele stap om het downloaden van broncodes te versnellen.
Het eerste nieuwe systeem duurt lang om te compileren, dus wees geduldig (tijd is gerelateerd aan de prestaties van de host-CPU en de snelheid van netwerkdownloads).

### Flash het afbeeldingsbestand

De K510 ondersteunt sdcard- en eMMC-opstartmodi en gebruikers kunnen schakelen tussen verschillende opstartmodi door de instellingen van de SW1-trekschakelaar op het open bord te wijzigen.  
De fabrieksstandaard is om op te starten vanaf emmc. Voor het gemak van de ontwikkeling wordt aanbevolen dat u een TF-kaart voorbereidt en de codeschakelaar overschakelt naar de opstartmodus van de SD-kaart en vervolgens overweegt het afbeeldingsbestand uit te harden in emmc.  
Of u nu op Linux of Windows werkt, u kunt [de Etcher-tool downloaden](https://www.balena.io/etcher/) om het gecompileerde afbeeldingsbestand (k510_buildroot /k510_crb_lp3_v1_2_defconfig / image / sysimage-sdcard.img) op uw TF-kaart te branden.
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### Inschakelbediening

Controleer of de SW1-schakelaar is geselecteerd in de opstartmodus van de SD-kaart, plaats de gebrande TF-kaart in de open kaartsleuf en koppel vervolgens de aan /uit-schakelaar K1 los in de AAN-stand en het systeem kan worden opgestart. U ziet het scherm met het CANAAN-logoscherm, als u een aangesloten seriële poort hebt, kunt u de uitvoer van het opstartlogboek in de seriële poort zien.
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### Het standaard opstartprogramma wijzigen

Standaard voert het systeem automatisch het voorbeeldprogramma (v4l2_drm.out) uit onder het pad /app/mediactl_lib aan. U kunt het configuratieprogramma ook handmatig wijzigen om in plaats daarvan andere demoprogramma's uit te voeren. U kunt dit als volgt wijzigen:

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## Bijdrage gids

Als u geïnteresseerd bent in dit project en feedback wilt over een probleem of code wilt indienen, raadpleeg dan[CONSOLIDEREN](.github/CONTRIBUTING.md)

## Neem contact met ons op

Canaan Inc.  
URL:[canaan-creative.com](https://canaan-creative.com)  
Zakelijke vragen:[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**Vertaling Disclaimer**  
Voor het gemak van klanten gebruikt Canaan een AI-vertaler om tekst in meerdere talen te vertalen, wat fouten kan bevatten. Wij garanderen niet de nauwkeurigheid, betrouwbaarheid of tijdigheid van de geleverde vertalingen. Canaan is niet aansprakelijk voor enig verlies of schade veroorzaakt door het vertrouwen op de nauwkeurigheid of betrouwbaarheid van de vertaalde informatie. Als er een inhoudelijk verschil is tussen de vertalingen in verschillende talen, prevaleert de vereenvoudigd Chinese versie.

Als u een vertaalfout of onnauwkeurigheid wilt melden, neem dan gerust contact met ons op via e-mail.
