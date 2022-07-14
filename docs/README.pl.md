[![Repozytorium](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
 Gitee [![Wydanie GitHub](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

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

Kanzhi K510 to druga generacja układów wnioskowania brzegowego AI wprowadzonych przez Canaan, która zapewnia wysokowydajne możliwości przetwarzania obrazu i mowy dla aplikacji AI. K510 jest wyposażony we samodzielnie opracowany procesor sieci neuronowej drugiej generacji KPU2.0, który przyjmuje oryginalną technologię przepływu danych obliczeniowych, która zwiększa moc obliczeniową o 3 razy w porównaniu z poprzednią generacją i zmniejsza zużycie energii. Zintegrowany z najnowszą generacją procesorów obrazu ISP, obsługuje dostęp do kamery głębi TOF, obsługuje redukcję szumów 2D / 3D, szeroki zakres dynamiki (WDR), sprzęt 3A i inne kompletne funkcje. Dostawcy usług internetowych 3D obsługują czujniki TOF kamery głębi. Może być szeroko stosowany w różnych dziedzinach zastosowań, takich jak bezzałogowe statki powietrzne, fotografia lotnicza o wysokiej rozdzielczości, profesjonalne kamery, wideokonferencje, inteligentne roboty, edukacyjny STEAM i automatyczna wspomagana jazda.

K510 SDK to zestaw programistyczny dostarczony przez Canaan do tworzenia aplikacji chipów K510, jego domyślna konfiguracja opiera się na K510 CRB (platforma referencyjna dla klientów), zawartość magazynu obejmuje oprogramowanie toolchain, zestaw narzędzi PC, kod Linux, bootloader, bbl, oprogramowanie systemu buildroot i powiązane dokumenty zasobów sprzętowych, które użytkownicy mogą wykorzystać do rozwoju układu K510. Użytkownicy mogą dostosować rozwój zmian zgodnie z własnymi potrzebami w oparciu o ten zestaw bazy kodu oprogramowania, a na koniec skompilować i skompilować plik obrazu użyty do wdrożenia.

## Opisy treści materiałów i linki do zasobów referencyjnych

| Nie | Adres linku | Ilustrują  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | Kod kompiluje katalog roboczy |
|2|[dokumenty/](https://github.com/kendryte/k510_docs)| Kompilacja systemu K510 i dokumentacja rozwoju aplikacji; Dokumentacja wprowadzająca do zasobów sprzętowych
|3|[pakiet/](/package/)| Podaj przykłady aplikacji do tworzenia urządzeń peryferyjnych systemu Linux; Różne kody źródłowe aplikacji demonstracyjnych AI  |
|4|[Kanaan Kanchi](https://canaan-creative.com/product/勘智k510)|Oficjalna strona Canaan Kanji|
|5|[Społeczność programistów](https://canaan-creative.com/developer)|Canaan Kanchi Forum
|6|[Film demonstracyjny](https://space.bilibili.com/677429436)|Gotowe do użycia płytki programistycznej K510 i wiele filmów demonstracyjnych aplikacji AI|
|7|[K510 ZESTAW CRB](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510 Board Kit Link do zakupu online|
|8|Natychmiastowa komunikacja|  Community Mutual Aid QQ Group: 790699378</br>Telegram: społeczność nncase |

## Wprowadzenie do pakietu K510 CRB Developer Suite

K510 CRB-KIT to pakiet programistów oparty na rozwoju układu K510, który przyjmuje hierarchiczną konstrukcję, opartą na module rdzenia K510, z bogatymi urządzeniami peryferyjnymi i łatwymi do rozbudowy. Obsługa USB 2.0 OTG + PHY, portu Gigabit Ethernet, 3xSDIO, 3xSPI i innych szybkich interfejsów komunikacyjnych, obsługa 4xUART, GPIO, I2C i I2S oraz innych interfejsów komunikacyjnych o niskiej prędkości. Prosty w użyciu, informacyjny, może pomóc klientom szybko osiągnąć kreatywną ocenę, weryfikację prototypu produktu, skrócić cykl projektowania produktu.
![Canaan-board .png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB zdjęcie z przodu </center>

![hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
 obrazu <center>Schemat blokowy systemu K510</center>  

![hw_3_1.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
 obrazu <center>Schemat modułu płytki rdzeniowej K510</center>  

## Pierwsze kroki z tworzeniem oprogramowania K510

### Konfigurowanie środowiska programistycznego

Rozwój oprogramowania K510 opiera się na środowisku Linux. Użytkownicy muszą przygotować hosta z systemem operacyjnym Linux do kompilacji i wdrażania oprogramowania, a jeśli pracujesz w systemie Windows, zaleca się zainstalowanie Windows WSL do pracy nad tworzeniem oprogramowania.

### Pobieranie kodu źródłowego

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### Uruchamianie platformy Docker

```sh
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

### Kompilowanie bazy kodu

Po wejściu do środowiska docker wprowadź następujące polecenie, aby skompilować system.

```sh
make dl
make
```

`make dl`Opcjonalny krok przyspieszający pobieranie kodu źródłowego.
Pierwsza nowa kompilacja systemu zajmuje dużo czasu, więc bądź cierpliwy (czas jest związany z wydajnością procesora hosta i szybkością pobierania z sieci).

### Flashowanie pliku obrazu

K510 obsługuje tryby rozruchu sdcard i eMMC, a użytkownicy mogą przełączać się między różnymi trybami rozruchu, zmieniając ustawienia przełącznika SW1 pull na otwartej płycie.  
Domyślnie fabrycznie jest uruchamianie z emmc. Aby ułatwić programowanie, zaleca się przygotowanie karty TF i przełączenie przełącznika kodu na tryb rozruchu karty SD, a następnie rozważenie wyleczenia pliku obrazu w emmc.  
Niezależnie od tego, czy pracujesz w systemie Linux, czy Windows, możesz pobrać [narzędzie Etcher](https://www.balena.io/etcher/), aby nagrać skompilowany plik obrazu (k510_buildroot /k510_crb_lp3_v1_2_defconfig/image/sysimage-sdcard.img) na kartę TF.
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### Zasilanie

Upewnij się, że przełącznik SW1 jest wybrany w trybie rozruchu karty SD, włóż nagraną kartę TF do gniazda otwartej karty płyty, a następnie odłącz przełącznik zasilania K1 do pozycji ON, a system może się włączyć. Zobaczysz ekran wyświetlający ekran z logo CANAAN, jeśli masz podłączony port szeregowy, możesz zobaczyć wyjście dziennika rozruchowego w porcie szeregowym.
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### Zmienianie domyślnego programu startowego

Domyślnie system automatycznie uruchamia przykładowy program (v4l2_drm.out) w ścieżce /app/mediactl_lib on. Możesz także ręcznie zmienić program konfiguracyjny, aby zamiast tego uruchamiać inne programy demonstracyjne. Aby to zmienić:

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## Przewodnik po składkach

Jeśli jesteś zainteresowany tym projektem i chciałbyś uzyskać opinię na temat problemu lub przesłać kod, zapoznaj się z[SEKCJĄ KONSOLIDACJA](.github/CONTRIBUTING.md)

## Skontaktuj się z nami

Pekin Canaan Jiesi Information Technology Co Ltd  
Adres internetowy:[canaan-creative.com](https://canaan-creative.com)  
Zapytania biznesowe:[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**Zrzeczenie się odpowiedzialności za**tłumaczenie  
Dla wygody klientów Canaan używa tłumacza AI do tłumaczenia tekstu na wiele języków, które mogą zawierać błędy. Nie gwarantujemy dokładności, rzetelności ani terminowości dostarczonych tłumaczeń. Canaan nie ponosi odpowiedzialności za jakiekolwiek straty lub szkody spowodowane poleganiem na dokładności lub wiarygodności przetłumaczonych informacji. W przypadku różnic w treści tłumaczeń w różnych językach, pierwszeństwo ma chińska wersja uproszczona.

Jeśli chcesz zgłosić błąd lub niedokładność tłumaczenia, skontaktuj się z nami pocztą.
