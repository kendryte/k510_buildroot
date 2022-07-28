[![Gitee 저장소](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
[![GitHub 릴리스](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

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

2세대 AI 에지 사이드 추론 칩인 Zhenzhi K510은 AI 애플리케이션을 위한 고성능 이미지 및 음성 처리 기능을 제공합니다. K510은 자체 개발한 2세대 신경망 프로세서인 KPU2.0을 탑재하고 있으며, 독창적인 컴퓨팅 데이터 스트림 기술을 사용하여 이전 세대보다 3배 더 많은 컴퓨팅 파워를 제공하면서 전력 소비를 줄입니다. 최신 이미지 프로세서 ISP가 통합되어 TOF 깊이 카메라 액세스를 지원하며 2D/3D 노이즈 감소, 넓은 동적 범위(WDR), 하드웨어 3A 등을 지원합니다. 3D ISP는 깊이 카메라 TOF 센서를 지원합니다. 드론, HD 항공 사진, 전문 카메라, 화상 회의, 지능형 로봇, 교육 STEAM, 자동 보조 운전 및 기타 응용 분야에서 널리 사용될 수 있습니다.

K510 SDK는 K510 칩 응용 프로그램 개발을 위한 Jianan의 소프트웨어 개발 키트이며, 기본 구성은 K510 CRB(고객 참조 플랫폼)를 기반으로 하며, 창고 콘텐츠에는 사용자가 K510 칩을 사용하여 개발할 때 사용할 수 있는 도구 체인 소프트웨어, PC 키트, Linux 코드, bootloader, bbl, buildroot 빌드 시스템 소프트웨어 및 관련 하드웨어 리소스 문서가 포함됩니다. 사용자는 소프트웨어 코드 베이스 집합을 기반으로 필요에 맞게 사용자 지정 변경을 개발하고 빌드 배포에 사용되는 이미지 파일을 빌드하고 컴파일할 수 있습니다.

## 리소스 설명 및 참조 리소스에 대한 링크입니다

| 아니요 | 링크 주소입니다 | 설명합니다  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | 코드 컴파일 작업 디렉터리입니다 |
|2|[문서/](https://github.com/kendryte/k510_docs)| K510 시스템 컴파일 및 응용 프로그램 개발 문서; 하드웨어 리소스 소개 문서입니다
|3|[패키지/](/package/)| Linux 시스템 주변 장치 개발 응용 프로그램의 예를 제공합니다. 다양한 AI 데모 앱 소스 코드  |
|4|[가남이 지혜를 조사하다](https://canaan-creative.com/product/勘智k510)|지아난 캄지 공식 홈페이지|
|5|[개발자 커뮤니티](https://canaan-creative.com/developer)|지아난의 지포럼
|6|[데모 비디오](https://space.bilibili.com/677429436)|K510 개발 보드는 비디오 및 여러 AI 응용 프로그램 디스플레이 비디오를 제공합니다|
|7|[K510 CRB-키트](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510 보드 번들 온라인 구매 링크|
|8|즉각적인 의사 소통|  커뮤니티 상호 지원 QQ 그룹: 790699378</br>Telegram:nncase community |

## K510 CRB 개발자 키트 소개

K510 CRB-KIT는 K510 칩을 기반으로 개발된 개발자 키트로, K510 코어 모듈을 기반으로 계층화된 디자인을 갖추고 있으며, 주변 장치가 풍부하여 쉽게 확장할 수 있습니다. USB 2.0 OTG+PHY, 기가비트 이더넷 포트, 3xSDIO, 3xSPI 등의 고속 통신 인터페이스를 지원하며 4xUART, GPIO, I2C 및 I2S와 같은 저속 통신 인터페이스를 지원합니다. 고객이 창의적인 평가, 프로토타입 검증 및 제품 설계 주기를 신속하게 달성할 수 있도록 간단하고 풍부한 데이터를 사용할 수 있습니다.
![canaan-board.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB 정면 사진 </center>

![image-hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
 <center>K510 시스템 블록 다이어그램</center>  

![image-hw_3_1.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
 <center>K510 코어 플레이트 모듈 다이어그램</center>  

## K510 소프트웨어 개발 시작하기

### 소프트웨어 개발 환경을 설정합니다

K510 소프트웨어 개발은 Linux 환경을 기반으로 합니다. 사용자는 소프트웨어 컴파일 및 배포를 위해 Linux 운영 체제가 설치된 호스트를 준비해야 하며 Windows에서 작업하는 경우 소프트웨어 개발을 위해 Windows WSL을 설치하는 것이 좋습니다.

### 소스 코드 다운로드

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### docker를 시작합니다

```sh
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

### 코드 베이스를 컴파일합니다

docker 환경에 들어가면 시스템 컴파일에 다음 명령을 입력합니다.

```sh
make dl
make
```

`make dl`소스 다운로드 속도를 높이기 위한 선택적 단계입니다.
첫 번째 새 시스템은 컴파일 시간이 오래 걸리며 호스트 CPU의 성능 및 네트워크 다운로드 속도와 관련이 있습니다.

### 미러 파일을 굽습니다

K510은 sdcard 및 eMMC 시작 모드를 지원하며, 사용자는 오픈 보드의 SW1 코드 추출 스위치 설정을 변경하여 다른 시작 모드를 전환할 수 있습니다.  
공장 기본값은 emmc에서 시작하는 것입니다. 개발을 용이하게 하기 위해 TF 카드를 준비하고 코드 추출 스위치를 SD 카드 시작 모드로 전환한 다음 미러 파일을 emmc로 경화하는 것이 좋습니다.  
Linux 또는 Windows 시스템에서 작업하든 [Etcher](https://www.balena.io/etcher/) 도구를 다운로드하여 컴파일된 미러 파일(k510_buildroot/k510_crb_lp3_v1_2_defconfig/image/sysimage-sdcard.img)을 TF 카드에 구울 수 있습니다.
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### 전원을 켜고 실행합니다

SW1 스위치가 SD 카드 시작 모드에서 선택되었는지 확인하고, 레코딩된 TF 카드를 오픈 보드 카드 슬롯에 삽입한 다음 전원 스위치 K1을 ON 위치로 당겨 시스템의 전원을 켭니다. 화면에 CANAAN 로고 화면이 표시되고 직렬 포트가 있는 경우 시작 로그 출력이 표시됩니다.
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### 기본 시작 프로그램을 변경합니다

기본적으로 시스템은 /app/mediactl_lib 경로 아래의 샘플 프로그램(v4l2_drm.out)을 자동으로 실행합니다. 구성 프로그램을 수동으로 변경하여 다른 데모 프로그램을 실행하도록 변경할 수도 있습니다. 변경 방법은 다음과 같습니다.

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## 기여 가이드

이 프로젝트에 관심이 있거나 질문에 대한 피드백을 제공하거나 코드를 제출하려면[CONTRIBUTING을 참조하십시오](.github/CONTRIBUTING.md)

## 저희에게 연락하십시오

Canaan Inc.  
웹 사이트:[canaan-creative.com](https://canaan-creative.com)  
비즈니스 문의:[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**번역 면책 조항**  
고객의 편의를 위해 Canan은 AI 번역 프로그램을 사용하여 오류를 포함할 수 있는 여러 언어로 텍스트를 번역합니다. 당사는 제공된 번역의 정확성, 신뢰성 또는 적시성을 보장하지 않습니다. Canan은 번역된 정보의 정확성이나 신뢰성에 의존하여 발생하는 손실이나 손해에 대해 책임을 지지 않습니다. 언어 번역 간에 콘텐츠 차이가 있는 경우 중국어 간체 버전이 우선합니다.

번역 오류 또는 부정확한 문제를 신고하려면 이메일로 문의하시기 바랍니다.
