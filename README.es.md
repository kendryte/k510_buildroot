[![Repositorio gitee](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
 [![Versión de GitHub](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

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

Kanzhi K510 es la segunda generación de chips de inferencia del lado del borde de IA lanzados por Canaan, que proporciona capacidades de procesamiento de imágenes y voz de alto rendimiento para aplicaciones de IA. El K510 está equipado con el procesador de red neuronal de segunda generación de desarrollo propio KPU2.0, que adopta la tecnología de flujo de datos informáticos original, que aumenta la potencia de cálculo en 3 veces en comparación con la generación anterior y reduce el consumo de energía. Integrado con la última generación de procesador de imagen ISP, admite acceso a cámara de profundidad TOF, admite reducción de ruido 2D / 3D, amplio rango dinámico (WDR), hardware 3A y otras funciones completas. Los ISP 3D admiten sensores TOF de cámara de profundidad. Puede ser ampliamente utilizado en diferentes campos de aplicación, como vehículos aéreos no tripulados, fotografía aérea de alta definición, cámaras profesionales, videoconferencias, robots inteligentes, STEAM educativo y conducción asistida automática.

K510 SDK es un kit de desarrollo de software proporcionado por Canaan para el desarrollo de aplicaciones de chip K510, su configuración predeterminada se basa en K510 CRB (plataforma de referencia del cliente), el contenido del almacén incluye el software de cadena de herramientas, kit de herramientas de PC, código Linux, gestor de arranque, bbl, software de sistema de compilación buildroot y documentos de recursos de hardware relacionados que los usuarios pueden usar en el desarrollo del chip K510. Los usuarios pueden personalizar el desarrollo del cambio de acuerdo con sus propias necesidades en función de este conjunto de código base de software y, finalmente, crear y compilar el archivo de imagen utilizado para la implementación.

## Descripciones del contenido del material y enlaces a recursos de referencia

| No | Dirección del enlace | ilustrar  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | El código compila el directorio de trabajo |
|2|[documentos/](https://github.com/kendryte/k510_docs)| Compilación del sistema K510 y documentación de desarrollo de aplicaciones; Documentación de introducción a recursos de hardware
|3|[paquete/](/package/)| Proporcionar ejemplos de aplicaciones de desarrollo de periféricos del sistema Linux; Varios código fuente de la aplicación de demostración de IA  |
|4|[Canaán Kanchi](https://canaan-creative.com/product/勘智k510)|Sitio web oficial de Canaan Kanji|
|5|[Comunidad de desarrolladores](https://canaan-creative.com/developer)|Foro Canaan Kanchi
|6|[Vídeo de demostración](https://space.bilibili.com/677429436)|Video listo para usar de la placa de desarrollo K510 y múltiples videos de demostración de aplicaciones de IA|
|7|[K510 CRB-KIT](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|Enlace de compra en línea del kit de placa K510|
|8|Comunicación instantánea|  Community Mutual Aid QQ Group: 790699378</br>Telegram: nncase community |

## Introducción a K510 CRB Developer Suite

K510 CRB-KIT es una suite de desarrolladores basada en el desarrollo del chip K510, que adopta un diseño jerárquico, basado en el módulo central K510, con periféricos ricos y fáciles de expandir. Admite USB 2.0 OTG + PHY, puerto Gigabit Ethernet, 3xSDIO, 3xSPI y otras interfaces de comunicación de alta velocidad, admite 4xUART, GPIO, I2C e I2S y otras interfaces de comunicación de baja velocidad. Fácil de usar, informativo, puede ayudar a los clientes a lograr rápidamente una evaluación creativa, verificación de prototipos de productos, acortar el ciclo de diseño del producto.
![Canaan-board .png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB foto frontal </center>

![hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
 de imagen <center>Diagrama de bloques del sistema K510</center>  

![hw_3_1.png de imagen](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
 <center>Diagrama del módulo de la placa central K510</center>  

## Introducción al desarrollo de software K510

### Configurar un entorno de desarrollo de software

El desarrollo de software K510 se basa en un entorno Linux. Los usuarios deben preparar un host con un sistema operativo Linux para la compilación e implementación de software, y si está trabajando en Windows, se recomienda instalar Windows WSL para el trabajo de desarrollo de software.

### Descarga de código fuente

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### Iniciar Docker

```sh
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

### Compilar el código base

Después de ingresar al entorno de docker, ingrese el siguiente comando para compilar el sistema.

```sh
make dl
make
```

`make dl`Paso opcional para acelerar las descargas de código fuente.
El primer sistema nuevo tarda mucho tiempo en compilarse, así que tenga paciencia (el tiempo está relacionado con el rendimiento de la CPU del host y la velocidad de las descargas de la red).

### Flashear el archivo de imagen

El K510 admite los modos de arranque sdcard y eMMC, y los usuarios pueden cambiar entre diferentes modos de arranque cambiando la configuración del interruptor de extracción SW1 en la placa abierta.  
El valor predeterminado de fábrica es arrancar desde emmc. Para facilitar el desarrollo, se recomienda que prepare una tarjeta TF y cambie el interruptor de código al modo de arranque de la tarjeta SD, y luego considere curar el archivo de imagen en emmc.  
Ya sea que trabaje en Linux o Windows, puede descargar [la herramienta Etcher](https://www.balena.io/etcher/) para grabar el archivo de imagen compilado (k510_buildroot / k510_crb_lp3_v1_2_defconfig / image / sysimage-sdcard.img) en su tarjeta TF.
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### Funcionamiento de encendido

Confirme que el conmutador SW1 está seleccionado en el modo de arranque de la tarjeta SD, inserte la tarjeta TF grabada en la ranura para tarjeta de la placa abierta y, a continuación, desenchufe el interruptor de alimentación K1 a la posición ON y el sistema podrá encenderse. Verá que la pantalla muestra la pantalla del logotipo de CANAAN, si tiene un puerto serie conectado, puede ver la salida del registro de arranque en el puerto serie.
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### Cambiar el programa de inicio predeterminado

De forma predeterminada, el sistema ejecuta automáticamente el programa de ejemplo (v4l2_drm.out) en la ruta /app/mediactl_lib on. También puede cambiar manualmente el programa de configuración para ejecutar otros programas de demostración. A continuación, le indicamos cómo cambiarlo:

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## Guía de contribución

Si está interesado en este proyecto y desea recibir comentarios sobre un problema o enviar código, consulte[CONSOLIDACIÓN](.github/CONTRIBUTING.md)

## Contáctenos

Beijing Canaan Jiesi Información Technology Co., Ltd  
URL:[canaan-creative.com](https://canaan-creative.com)  
Consultas comerciales:[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**Descargo de responsabilidad de**traducción  
Para la comodidad de los clientes, Canaan utiliza un traductor de IA para traducir texto a varios idiomas, que pueden contener errores. No garantizamos la exactitud, fiabilidad o puntualidad de las traducciones proporcionadas. Canaan no será responsable de ninguna pérdida o daño causado por la confianza en la exactitud o fiabilidad de la información traducida. Si existe una diferencia de contenido entre las traducciones en diferentes idiomas, prevalecerá la versión en chino simplificado.

Si desea informar de un error o inexactitud de traducción, no dude en ponerse en contacto con nosotros por correo.
