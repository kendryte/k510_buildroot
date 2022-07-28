[![Gitee repository](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
[![GitHub 發佈](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

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

# K510 開發工具組

勘智K510是嘉楠公司推出的第二代AI邊緣側推理晶元，它為AI應用提供了高性能的圖像及語音處理能力。 K510搭載自主研發的第二代神經網路處理器KPU2.0， 採用獨創計算數據流技術，算力較上一代提升3倍同時降低功耗。 集成最新一代圖像處理器ISP，支援TOF深度相機接入，支援2D/3D降噪、寬動態範圍（WDR）、硬體3A等完備功能。 3D ISP支援深度攝像頭TOF sensor。 可廣泛應用於無人機、高清航拍、專業相機、視頻會議、智能機器人、教育STEAM、自動輔助駕駛等不同應用領域。

K510 SDK是嘉楠公司提供的用於K510晶元應用研發的軟體開發資料包，它的預設配置基於K510 CRB（客戶參考平臺），倉庫內容包括使用者在使用 K510 晶元進行開發中可能用到的工具鏈軟體、PC工具包、Linux代碼、bootloader、bbl、buildroot構建系統軟體及相關的硬體資源文檔。 用戶可以基於本套軟體代碼庫，根據自己的需求進行定製更改開發，最終構建並編譯生成部署使用的鏡像檔。

## 資料內容說明和參考資源連結

| 不 | 連結位址 | 說明  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | 代碼編譯工作目錄 |
|2|[文件/](https://github.com/kendryte/k510_docs)| K510系統編譯及應用開發文檔; 硬體資源介紹文件
|3|[包裝/](/package/)| 提供Linux系統外設開發應用範例; 各種AI演示應用原始程式碼  |
|4|[嘉楠勘智](https://canaan-creative.com/product/勘智k510)|嘉楠勘智官網|
|5|[開發者社區](https://canaan-creative.com/developer)|嘉楠勘智論壇
|6|[演示視頻](https://space.bilibili.com/677429436)|K510開發板開箱視頻及多個 AI 應用展示視頻|
|7|[K510 系列](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510 開發板套裝在線購買連結|
|8|即時溝通|  社區互助 QQ 群：790699378</br>Telegram：nncase community |

## K510 CRB 開發者套裝介紹

K510 CRB-KIT是基於K510晶元研發的開發者套裝，它採用分級設計，以K510核心模組為基礎，外設豐富，便於擴展。 支援USB 2.0 OTG+PHY、千兆乙太網口、3xSDIO、3xSPI等高速通信介面，支援4xUART、GPIO、I2C和I2S等低速通信介面。 使用簡單、資料豐富、能夠幫助客戶快速實現創意評估、產品原型驗證，縮短產品設計週期。
![canaan-board.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB 正面照 </center>

![image-hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
 <center>K510系統框圖</center>  

![image-hw_3_1.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
 <center>K510核心板模組圖</center>  

## K510 軟體開發入門

### 建立軟體開發環境

K510 軟體開發基於Linux環境。 使用者需要準備一台裝有Linux作業系統的主機用於軟體編譯及部署，如果您工作在 windows 下，推薦安裝 Windows WSL 以便進行軟體開發工作。

### 原始碼下載

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### 啟動docker

```sh
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

### 編譯代碼庫

進入docker環境后，輸入如下命令進行系統編譯。

```sh
make dl
make
```

`make dl`為可選步驟，用於加速源碼下載。
第一次全新系統編譯時間較長，請耐心等待（時間和主機CPU的性能和網路下載速度相關）。

### 燒寫鏡像檔

K510 支援sdcard和eMMC啟動方式，用戶可以通過改變開板上SW1拔碼開關的設置切換不同啟動模式。  
出廠預設為從emmc啟動。 為方便開發，建議您準備一張TF卡，並將拔碼開關切換至SD卡啟動模式，後續可考慮將鏡像檔固化至emmc中。  
無論您工作在Linux還是 Windows系統下， 均可下載 [Etcher](https://www.balena.io/etcher/) 工具，將編譯生成的鏡像檔（k510_buildroot/k510_crb_lp3_v1_2_defconfig/image/sysimage-sdcard.img）燒錄至 TF 卡中。
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### 上電運行

確認SW1開關選擇在SD卡啟動模式下，將燒錄完成的TF卡插入進開板板卡槽中，然後將電源開關K1拔到ON位置，系統可上電。 您會看到螢幕顯示 CANAAN logo 畫面，如果您有接好串口，可在串口中看到啟動日誌輸出。
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### 更改預設啟動程式

默認情況下，系統開機會自動運行 /app/mediactl_lib 路徑下的範例程式（v4l2_drm.out）。 你也可以手動更改配置程式，改成運行其它演示程式。 變更方法如下：

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## 貢獻指南

如果您對本專案感興趣，想要反饋問題或提交代碼，請參考[CONTRIBUTING](.github/CONTRIBUTING.md)

## 聯繫我們

北京嘉楠捷思資訊技術有限公司  
網址：[canaan-creative.com](https://canaan-creative.com)  
商務垂詢：[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**翻譯免責聲明**  
為方便客戶，Canaan 使用 AI 翻譯程式將文字翻譯為多種語言，它可能包含錯誤。 我們不保證提供的譯文的準確性、可靠性或時效性。 對於因依賴已翻譯信息的準確性或可靠性而造成的任何損失或損害，Canaan 概不負責。 如果不同語言翻譯之間存在內容差異，以簡體中文版本為準。

如果您要報告翻譯錯誤或不準確的問題，歡迎通過郵件與我們聯繫。
