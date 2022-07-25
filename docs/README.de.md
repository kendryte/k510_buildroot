[![Gitee-Repository](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
 [![GitHub-Version](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

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

Kendryte K510 ist die zweite Generation von KI-Edge-Side-Inferenzchips, die von Canaan auf den Markt gebracht wurden und leistungsstarke Bild- und Sprachverarbeitungsfunktionen für KI-Anwendungen bieten. Der K510 ist mit dem selbst entwickelten neuronalen Netzwerkprozessor der zweiten Generation KPU2.0 ausgestattet, der die ursprüngliche Rechendatenflusstechnologie verwendet, die die Rechenleistung im Vergleich zur Vorgängergeneration um das 3-fache erhöht und den Stromverbrauch senkt. Integriert mit der neuesten Generation von Bildprozessor ISP, Unterstützung TOF Tiefenkamera Zugriff, Unterstützung 2D / 3D Rauschunterdrückung, Wide Dynamic Range (WDR), Hardware 3A und andere komplette Funktionen. 3D-ISPs unterstützen Tiefenkamera-TOF-Sensoren. Es kann in verschiedenen Anwendungsbereichen wie unbemannten Luftfahrzeugen, hochauflösenden Luftaufnahmen, professionellen Kameras, Videokonferenzen, intelligenten Robotern, pädagogischem STEAM und automatischem assistiertem Fahren eingesetzt werden.

K510 SDK ist ein Software-Entwicklungskit, das von Canaan für die Entwicklung von K510-Chip-Anwendungen bereitgestellt wird, seine Standardkonfiguration basiert auf K510 CRB (Kundenreferenzplattform), der Lagerinhalt umfasst die Toolchain-Software, das PC-Toolkit, den Linux-Code, den Bootloader, den bbl, die Buildroot-Build-Systemsoftware und die zugehörigen Hardware-Ressourcendokumente, die Benutzer bei der Entwicklung des K510-Chips verwenden können. Benutzer können die Änderungsentwicklung basierend auf diesem Satz von Software-Codebasis an ihre eigenen Anforderungen anpassen und schließlich die für die Bereitstellung verwendete Image-Datei erstellen und kompilieren.

## Beschreibungen des Materialinhalts und Links zu Referenzressourcen

| Nein | Link-Adresse | illustrieren  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | Der Code kompiliert das Arbeitsverzeichnis |
|2|[docs/](https://github.com/kendryte/k510_docs)| K510-Systemkompilierungs- und Anwendungsentwicklungsdokumentation; Dokumentation zur Einführung in Hardwareressourcen
|3|[Paket/](/package/)| Bereitstellung von Anwendungsbeispielen für die Entwicklung von Linux-Systemperipheriegeräten; Quellcode für verschiedene KI-Demoanwendungen  |
|4|[Kanaan Kendryte](https://canaan-creative.com/product/勘智k510)|Offizielle Website von Canaan Kendryte|
|5|[Entwickler-Community](https://canaan-creative.com/developer)|Kanaan Kendryte Forum
|6|[Demo-Video](https://space.bilibili.com/677429436)|Out-of-the-Box-Video zur K510-Entwicklungsplatine und mehrere Videos zur Demonstration von KI-Anwendungen|
|7|[K510 CRB-KIT](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510 Board Kit Online-Kauflink|
|8|Sofortige Kommunikation|  QQ-Gruppe für gegenseitige Hilfe der Gemeinschaft: 790699378</br>Telegramm: nncase community |

## Einführung in die K510 CRB Developer Suite

K510 CRB-KIT ist eine Entwicklersuite, die auf der K510-Chipentwicklung basiert, die ein hierarchisches Design annimmt, das auf dem K510-Kernmodul basiert, mit umfangreichen Peripheriegeräten und einfach zu erweitern. Unterstützt USB 2.0 OTG + PHY, Gigabit-Ethernet-Port, 3xSDIO, 3xSPI und andere High-Speed-Kommunikationsschnittstellen, unterstützt 4xUART, GPIO, I2C und I2S und andere Low-Speed-Kommunikationsschnittstellen. Einfach zu bedienen, informativ, kann Kunden helfen, schnell eine kreative Bewertung zu erreichen, Produktprototypen zu überprüfen und den Produktdesignzyklus zu verkürzen.
![Canaan-Board .png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB Frontfoto </center>

![Bild-hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
 <center>K510 Systemblockdiagramm</center>  

![Bild-hw_3_1.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
 <center>Diagramm des K510-Kernplatinenmoduls</center>  

## Erste Schritte mit der K510-Softwareentwicklung

### Einrichten einer Softwareentwicklungsumgebung

Die K510-Softwareentwicklung basiert auf einer Linux-Umgebung. Benutzer müssen einen Host mit einem Linux-Betriebssystem für die Softwarekompilierung und -bereitstellung vorbereiten, und wenn Sie unter Windows arbeiten, wird empfohlen, Windows WSL für die Softwareentwicklung zu installieren.

### Quellcode-Download

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### Docker starten

```sh
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

### Kompilieren der Codebasis

Geben Sie nach dem Aufrufen der Docker-Umgebung den folgenden Befehl ein, um das System zu kompilieren.

```sh
make dl
make
```

`make dl`Optionaler Schritt zur Beschleunigung von Quellcode-Downloads.
Die Kompilierung des ersten neuen Systems dauert lange, also seien Sie geduldig (die Zeit hängt mit der Leistung der Host-CPU und der Geschwindigkeit der Netzwerk-Downloads zusammen).

### Flashen Sie die Bilddatei

Der K510 unterstützt die Boot-Modi sdcard und eMMC, und Benutzer können zwischen verschiedenen Boot-Modi wechseln, indem sie die Einstellungen des SW1-Pull-Schalters auf der offenen Platine ändern.  
Die werkseitige Voreinstellung ist es, von emmc zu booten. Zur Vereinfachung der Entwicklung wird empfohlen, eine TF-Karte vorzubereiten und den Codeschalter in den Bootmodus der SD-Karte zu schalten und dann in Betracht zu ziehen, die Image-Datei in emmc zu kurieren.  
Unabhängig davon, ob Sie unter Linux oder Windows arbeiten, können Sie [das Etcher-Tool herunterladen](https://www.balena.io/etcher/) , um die kompilierte Image-Datei (k510_buildroot/k510_crb_lp3_v1_2_defconfig/image/sysimage-sdcard.img) auf Ihre TF-Karte zu brennen.
![Balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### Einschaltbetrieb

Vergewissern Sie sich, dass der SW1-Schalter im Boot-Modus der SD-Karte ausgewählt ist, setzen Sie die gebrannte TF-Karte in den offenen Kartensteckplatz ein, und ziehen Sie dann den Netzschalter K1 in die ON-Position, und das System kann eingeschaltet werden. Sie werden sehen, dass der Bildschirm den CANAAN-Logo-Bildschirm anzeigt, wenn Sie eine angeschlossene serielle Schnittstelle haben, können Sie die Boot-Log-Ausgabe in der seriellen Schnittstelle sehen.
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### Ändern des Standardstartprogramms

Standardmäßig führt das System das Beispielprogramm (v4l2_drm.out) automatisch unter dem Pfad /app/mediactl_lib aus. Sie können das Konfigurationsprogramm auch manuell ändern, um stattdessen andere Demoprogramme auszuführen. So ändern Sie es:

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## Leitfaden für Beiträge

Wenn Sie an diesem Projekt interessiert sind und Feedback zu einem Problem wünschen oder Code einreichen möchten, lesen Sie bitte KONSOLIDIERUNG[](.github/CONTRIBUTING.md)

## Kontaktieren Sie uns

Canaan Inc.  
URL:[canaan-creative.com](https://canaan-creative.com)  
Geschäftliche Anfragen:[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**Haftungsausschluss**für Übersetzungen  
Für die Bequemlichkeit der Kunden verwendet Canaan einen KI-Übersetzer, um Text in mehrere Sprachen zu übersetzen, die Fehler enthalten können. Wir übernehmen keine Gewähr für die Genauigkeit, Zuverlässigkeit oder Aktualität der bereitgestellten Übersetzungen. Canaan haftet nicht für Verluste oder Schäden, die durch das Vertrauen auf die Richtigkeit oder Zuverlässigkeit der übersetzten Informationen verursacht werden. Wenn es einen inhaltlichen Unterschied zwischen den Übersetzungen in verschiedenen Sprachen gibt, ist die vereinfachte chinesische Version maßgebend.

Wenn Sie einen Übersetzungsfehler oder eine Ungenauigkeit melden möchten, können Sie uns gerne per E-Mail kontaktieren.
