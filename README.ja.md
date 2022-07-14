[![Gitee リポジトリ](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
[![GitHub のリリース](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

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

Yuan Zhi K510は、AIアプリケーションのための高性能画像と音声処理能力を提供する第2世代のAIエッジサイド推論チップです。 K510 は、独自に開発された第 2 世代ニューラル ネットワーク プロセッサ KPU2.0 を搭載し、独自のコンピューティング データ フロー テクノロジを使用して、前世代の 3 倍の電力を削減します。 最新世代の画像処理プロセッサISPを内蔵し、TOF深度カメラアクセスをサポートし、2D/3Dノイズリダクション、ワイドダイナミックレンジ(WDR)、ハードウェア3Aなどの完全な機能をサポートします。 3D ISP は深度カメラ TOF sensor をサポートします。 ドローン、HD航空写真、プロのカメラ、ビデオ会議、インテリジェントロボット、教育STEAM、自動アシスト運転など、さまざまなアプリケーション分野で広く使用されています。

K510 SDK は、K510 CRB (カスタマー リファレンス プラットフォーム) に基づく既定の構成で、K510 チップを使用して開発する可能性のあるツールチェーン ソフトウェア、PC キット、Linux コード、bootloader、bbl、buildroot 構築システム ソフトウェア、および関連するハードウェア リソース ドキュメントを含む、K510 チップ アプリケーション開発用のソフトウェア開発パッケージです。 ユーザーは、ソフトウェア コード ベースのこのセットに基づいて、独自のニーズに合わせて変更をカスタマイズして開発し、最終的にビルド展開で使用されるミラー ファイルを構築およびコンパイルできます。

## 資料の説明と参照リソースへのリンク

| いいえ | リンク アドレス | 命令  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | コードコンパイル作業ディレクトリ |
|2|[ドキュメント/](https://github.com/kendryte/k510_docs)| K510 システムコンパイルとアプリケーション開発ドキュメント。 ハードウェア リソースの概要ドキュメント
|3|[パッケージ/](/package/)| Linux システム周辺機器開発アプリケーションの例を提供します。 さまざまな AI デモ アプリケーションのソース コード  |
|4|[ジア・ユアンは知恵を調査した](https://canaan-creative.com/product/勘智k510)|ジア・ユアンは、知的な公式ウェブサイトを調査します|
|5|[開発者コミュニティ](https://canaan-creative.com/developer)|ジア・ユアン・カオ・ジ・フォーラム
|6|[デモビデオ](https://space.bilibili.com/677429436)|K510開発ボードの箱から出してビデオといくつかのAIアプリケーションディスプレイビデオ|
|7|[K510 CRB-キット](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510開発ボードセットオンライン購入リンク|
|8|インスタントコミュニケーション|  コミュニティ相互扶助 QQ グループ: 790699378</br>Telegram:nncase community |

## K510 CRB開発者キットの紹介

K510 CRB-KITは、K510コアモジュールに基づくグレーディング設計で、拡張しやすい豊富な周辺機器を備えたK510チップ開発開発者パッケージです。 USB 2.0 OTG+PHY、ギガビット イーサネット ポート、3xSDIO、3xSPI などの高速通信インターフェイス、4xUART、GPIO、I2C、I2S などの低速通信インターフェイスをサポートします。 シンプルで有益な製品を使用して、お客様が創造的な評価、製品プロトタイプ検証を迅速に実装し、製品設計サイクルを短縮するのに役立ちます。
![canaan-board.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB 正面写真 </center>

![image-hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
 <center>K510システムブロック図</center>  

![image-hw_3_1.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
 <center>K510コアプレートモジュール図</center>  

## K510 ソフトウェア開発の概要

### ソフトウェア開発環境の構築

K510 ソフトウェア開発は Linux 環境に基づいています。 ユーザーは、ソフトウェアのコンパイルと展開のために Linux オペレーティング システムを搭載したホストを準備する必要があり、Windows で作業している場合は、ソフトウェア開発作業のために Windows WSL をインストールすることをお勧めします。

### ソース コードのダウンロード

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### docker を起動します

```sh
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

### コード ベースをコンパイルします

docker 環境に入ったら、次のようなコマンドを入力してシステムコンパイルを行います。

```sh
make dl
make
```

`make dl`ソースのダウンロードを高速化するオプションの手順。
最初の新しいシステムコンパイルに時間がかかるので、辛抱強く(時間とホストCPUのパフォーマンスとネットワークのダウンロード速度に関連しています)。

### ミラー ファイルを書き込みます

K510 は sdcard と eMMC の起動方法をサポートしており、ユーザーはオープンボードの SW1 コード抜きスイッチの設定を変更することで、異なる起動モードを切り替えることができます。  
工場出荷時のデフォルトはemmcから起動されます。 開発を容易にするために、TFカードを用意し、コード抜きスイッチをSDカード起動モードに切り替えることをお勧めします。  
Linux または Windows システムで作業している場合でも[、Etcher](https://www.balena.io/etcher/) ツールをダウンロードして、コンパイルされたイメージ ファイル (k510_buildroot/k510_crb_lp3_v1_2_defconfig/image/sysimage-sdcard.img) を TF カードに書き込みます。
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### 電源投入時に実行します

SW1スイッチがSDカード起動モードで選択されていることを確認し、書き込み済みのTFカードをオープンボードカードスロットに挿入し、電源スイッチK1をON位置に引き抜き、システムを電源投入します。 CANAAN ロゴ画面が表示され、シリアル ポートがある場合は、シリアル ポートに起動ログ出力が表示されます。
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### 既定のランチャーを変更します

既定では、/app/mediactl_lib パスの下にあるサンプル プログラム (v4l2_drm.out) が自動的に実行されます。 また、構成プログラムを手動で変更して、他のデモ プログラムを実行することもできます。 変更方法は次のとおりです。

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## 貢献ガイド

このプロジェクトに興味があり、質問をフィードバックしたり、コードを送信したりする場合は、[CONTRIBUTING を参照してください](.github/CONTRIBUTING.md)

## お問い合わせ下さい

北京Jiayuan Jetth情報技術有限公司  
URL:[canaan-creative.com](https://canaan-creative.com)  
ビジネスお問い合わせ:[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**免責事項を翻訳します**  
お客様の便宜のために、カナアンはAI翻訳プログラムを使用してテキストを複数の言語に翻訳し、エラーが含まれている可能性があります。 当社は、提供される翻訳の正確性、信頼性、または適時性を保証するものではありません。 カナアンは、翻訳された情報の正確性または信頼性への依存に起因するいかなる損失または損害についても責任を負いません。 異なる言語翻訳間でコンテンツの違いがある場合は、簡体字中国語版が優先されます。

翻訳エラーや不正確な問題を報告する場合は、メールでお問い合わせください。
