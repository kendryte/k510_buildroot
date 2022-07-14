[![Gitee repository](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
 [![Versione di GitHub](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

* [English](README.md)
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

Kanzhi K510 è la seconda generazione di chip di inferenza edge-side AI lanciati da Canaan, che fornisce funzionalità di elaborazione vocale e di immagini ad alte prestazioni per applicazioni AI. Il K510 è dotato del processore di rete neurale di seconda generazione KPU2.0, che adotta la tecnologia di flusso di dati di calcolo originale, che aumenta la potenza di calcolo di 3 volte rispetto alla generazione precedente e riduce il consumo energetico. Integrato con l'ultima generazione di ISP del processore di immagini, supporta l'accesso alla telecamera di profondità TOF, supporta la riduzione del rumore 2D / 3D, l'ampia gamma dinamica (WDR), l'hardware 3A e altre funzioni complete. Gli ISP 3D supportano i sensori TOF della telecamera di profondità. Può essere ampiamente utilizzato in diversi campi di applicazione come veicoli aerei senza equipaggio, fotografia aerea ad alta definizione, telecamere professionali, videoconferenze, robot intelligenti, STEAM educativo e guida assistita automatica.

K510 SDK è un kit di sviluppo software fornito da Canaan per lo sviluppo di applicazioni di chip K510, la sua configurazione predefinita è basata su K510 CRB (piattaforma di riferimento del cliente), il contenuto del magazzino include il software toolchain, il toolkit per PC, il codice Linux, il bootloader, il bbl, il software del sistema buildroot build e i relativi documenti di risorse hardware che gli utenti possono utilizzare nello sviluppo del chip K510. Gli utenti possono personalizzare lo sviluppo delle modifiche in base alle proprie esigenze in base a questo set di codice software di base e infine compilare e compilare il file di immagine utilizzato per la distribuzione.

## Descrizioni del contenuto del materiale e collegamenti alle risorse di riferimento

| No | Indirizzo del collegamento | illustrare  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | Il codice compila la directory di lavoro |
|2|[documenti/](https://github.com/kendryte/k510_docs)| Compilazione del sistema K510 e documentazione per lo sviluppo di applicazioni; Documentazione introduttiva alle risorse hardware
|3|[pacchetto/](/package/)| Fornire esempi di applicazioni di sviluppo di periferiche di sistema Linux; Vari codice sorgente dell'applicazione demo AI  |
|4|[Canaan Kanchi](https://canaan-creative.com/product/勘智k510)|Canaan Kanji sito ufficiale|
|5|[Comunità di sviluppatori](https://canaan-creative.com/developer)|Canaan Kanchi Forum
|6|[Video dimostrativo](https://space.bilibili.com/677429436)|Video out-of-the-box della scheda di sviluppo K510 e più video dimostrativi di applicazioni AI|
|7|[K510 CRB-KIT](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510 Board Kit Link di acquisto online|
|8|Comunicazione istantanea|  Community Mutual Aid QQ Group: 790699378</br>Telegram: nncase community |

## Introduzione alla K510 CRB Developer Suite

K510 CRB-KIT è una suite per sviluppatori basata sullo sviluppo del chip K510, che adotta un design gerarchico, basato sul modulo core K510, con periferiche ricche e facili da espandere. Supporta USB 2.0 OTG + PHY, porta Gigabit Ethernet, 3xSDIO, 3xSPI e altre interfacce di comunicazione ad alta velocità, supporta 4xUART, GPIO, I2C e I2S e altre interfacce di comunicazione a bassa velocità. Semplice da usare, informativo, può aiutare i clienti a ottenere rapidamente la valutazione creativa, la verifica del prototipo del prodotto, abbreviare il ciclo di progettazione del prodotto.
![Canaan-board .png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB foto frontale </center>

![hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
 immagine <center>Diagramma a blocchi del sistema K510</center>  

![hw_3_1.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
 immagine <center>Diagramma del modulo della scheda centrale K510</center>  

## Introduzione allo sviluppo software K510

### Configurare un ambiente di sviluppo software

Lo sviluppo software K510 si basa su un ambiente Linux. Gli utenti devono preparare un host con un sistema operativo Linux per la compilazione e la distribuzione del software e, se si lavora con Windows, si consiglia di installare Windows WSL per il lavoro di sviluppo software.

### Download del codice sorgente

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### Avvia Docker

```sh
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

### Compilare la base di codice

Dopo aver inserito l'ambiente docker, immettere il comando seguente per compilare il sistema.

```sh
make dl
make
```

`make dl`Passaggio opzionale per accelerare i download del codice sorgente.
Il primo nuovo sistema richiede molto tempo per la compilazione, quindi sii paziente (il tempo è legato alle prestazioni della CPU host e alla velocità dei download di rete).

### Lampeggiare il file immagine

Il K510 supporta le modalità di avvio sdcard ed eMMC e gli utenti possono passare da una modalità di avvio all'altra modificando le impostazioni dell'interruttore a strappo SW1 sulla scheda aperta.  
L'impostazione predefinita di fabbrica è l'avvio da emmc. Per facilitare lo sviluppo, si consiglia di preparare una scheda TF e passare il passaggio del codice alla modalità di avvio della scheda SD, quindi considerare la possibilità di polimerizzare il file di immagine in emmc.  
Sia che tu lavori su Linux o Windows, puoi scaricare [lo strumento Etcher](https://www.balena.io/etcher/) per masterizzare il file di immagine compilato (k510_buildroot / k510_crb_lp3_v1_2_defconfig / image / sysimage-sdcard.img) sulla tua scheda TF.
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### Funzionamento a accensione

Verificare che lo switch SW1 sia selezionato in modalità di avvio della scheda SD, inserire la scheda TF masterizzata nello slot per schede scheda aperto, quindi scollegare l'interruttore di alimentazione K1 in posizione ON e il sistema può accendersi. Vedrai lo schermo visualizzare la schermata del logo CANAAN, se hai una porta seriale collegata, puoi vedere l'output del registro di avvio nella porta seriale.
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### Modificare il programma di avvio predefinito

Per impostazione predefinita, il sistema esegue automaticamente il programma di esempio (v4l2_drm.out) nel percorso /app/mediactl_lib su. È inoltre possibile modificare manualmente il programma di configurazione per eseguire altri programmi demo. Ecco come modificarlo:

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## Guida ai contributi

Se sei interessato a questo progetto e desideri un feedback su un problema o inviare codice, fai riferimento a[CONSOLIDATING](.github/CONTRIBUTING.md)

## Contattaci

Pechino Canaan Jiesi Information Technology Co., Ltd  
URL:[canaan-creative.com](https://canaan-creative.com)  
Richieste commerciali:[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**Traduzione Disclaimer**  
Per la comodità dei clienti, Canaan utilizza un traduttore AI per tradurre il testo in più lingue, che possono contenere errori. Non garantiamo l'accuratezza, l'affidabilità o la tempestività delle traduzioni fornite. Canaan non sarà responsabile per eventuali perdite o danni causati dall'affidamento sull'accuratezza o sull'affidabilità delle informazioni tradotte. Se c'è una differenza di contenuto tra le traduzioni in lingue diverse, prevarrà la versione cinese semplificata.

Se desideri segnalare un errore di traduzione o un'inesattezza, non esitare a contattarci via mail.
