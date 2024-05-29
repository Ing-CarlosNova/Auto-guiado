Elementos para el desarrollo de Vehiculo Autónomo


![image](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/efd5039a-c48c-4896-9af5-6b82946d3841)



El sensor de fuerza o presión mf01 autoadherible para Arduino es ideal para detectar una fuerza aplicada en la membrana. Básicamente, al detectar una flexión en la membrana el sensor cambia su resistencia interna. Este sensor esta fabricado de 2 capas separadas por un espaciador, cuanto más se presiona, por ejemplo, más puntos de elemento activo tocan el semiconductor. Por lo tanto, esto hace que la resistencia disminuya. Cuando no es presionado, su resistencia es de aproximadamente 20 MΩ. Su rango de presión varía de 30 gramos a 1 Kg. Por lo que basta con ponerlo en un divisor de tensión, para poder medir la salida en voltaje con algún ADC.

Estos sensor de fuerza son de bajo costo, funciona con cualquier tarjeta de desarrollo o microcontrolador con etapa de ADC. Tiene una extensión que termina en dos puntas que se pueden soldar cómodamente. Es muy sencillo de utilizar y puede tener multitud de aplicaciones en muchos proyectos electrónicos. Sirve para la mayoría de las aplicaciones sensibles al tacto. Puede utilizar cualquier fuente de alimentación ya que utiliza menos de 1 mA de corriente. En resumen, con este dispositivo podemos medir una fuerza proporcional a la presión generada sobre el sensor.

Estos sensores son raramente precisos. Así que, básicamente, cuando se utiliza este sensor sólo se debe esperar para obtener “rangos” de respuesta. Tal sensor de fuerza pueden detectar el peso, pero son una mala elección para detectar exactamente cuántas libras de peso hay en ellos.

Fuerza de actuación: 30g min.
Rango de sensibilidad: 30 a 10,000g.
Repetitividad: 5%.
Resistencia sin carga: 20 MOhms.
Histéresis: 10%.
Tiempo de respuesta: <1ms.
Rango de temperatura: -30ºC a 70ºC.
Ancho: 0.05 mm.
Rendimiento: 100 KΩ (presión ligera) a 200Ω (máx. presión)
Gama Fuerza: 0 a 20 libras (0 a 100 Newtons)

Como hemos dicho, la resistencia del sensor cambia con respecto a presión. Cuando no hay presión, el sensor se parece por lo general a una resistencia infinita (circuito abierto), ya que la presión aumenta, la resistencia disminuye. Este gráfico indica aproximadamente la resistencia del sensor en diferentes mediciones de la fuerza. (Ten en cuenta que la fuerza no se mide en gramos y lo que realmente quiere decir es Newtons * 100) de hecho.

![Captura de pantalla 2024-05-29 054218](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/8ec8558c-d0f7-4dbc-b934-8c15bdb62633)



Por otro lado, cabe mencionar que la figura previa es logarítmica en ambos ejes. No obstante el comportamiento se puede considerar una recta, sin embargo no se comporta como tal. Por ese motivo, a continuación se presenta una tabla con valores tomados. Como resultado podemos observar que la variación no es lineal.
Cabe aclarar que el sensor de fuerza no es recomendable para tomar pesos exactos, pero se puede tener un aproximado, para ello se realiza una ecuación de tendencia que permite realizar ajustes y obetner pesos aproximados. 


![image](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/b36bd8e3-9248-4864-84f9-a4323b23c449)



Características
Peso sensado 0.1-9.8N
Largo: 5.2cm
Ancho 13mm
Área de detección Circunferencia de 13mm
Tipo de salida: 2 pines varia la resistencia


![image](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/a5ba482b-14e9-4565-baa9-1d1e6e488139)




El sensor TCRT5000 es un sensor infrarrojo que consta de un diodo emisor de luz infrarroja y un fototransistor sensible a la luz infrarroja. Este sensor es muy utilizado en proyectos de detección de objetos, ya que es capaz de detectar la presencia de objetos opacos a la luz infrarroja a una distancia de hasta 1 cm, o para detectar contrastes como en el caso de un robot seguidor de linea

Características:
Detección: contrastes de colores
Voltaje: 5Vdc
Señal de salida: Digital
Señal de salida: analógica
Calibración: potenciómetro
distancia de detección: 1 cm
Led de detección: si



![image](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/a7222e71-2189-41ed-9008-de423fe9b7aa)




Sensor ultrasónico Ref HC-SR04 marca Genérica para medir distancia, detectar objetos
El HC-SR04 es un sensor ultrasónico de línea económica que puedes usar para medir distancia, es recomendable para aplicaciones académicas donde requieras trabajar con Arduino o sistemas similares

Características
Voltaje de alimentación: 5Vdc.
Corriente de consumo 15ma.
Frecuencia de la señal: 40khz.
Rango de detección: 2cm a 4m.
Resolución: 1cm.
Angulo de detección: 15° aproximadamente.
Tipo de señal de salida: Digital.

![image](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/e407cd07-edbe-4b31-b4c2-a5a48212efe3)



El display LCD 2×16 con conexión I2C es un componente que te permite visualizar información de forma clara y sencilla en tus proyectos. esta LCD tiene soldado el controlador I2C, lo que te permite ahorrar pines en tu proyecto. Además, es compatible con muchas librerías. Con su forma compacta y su capacidad de mostrar hasta 32 caracteres en dos líneas, es una opción ideal para proyectos de pequeña escala.

Características
Pantalla: LCD 2×16
Backligth: Azul
Tipo: Alfanumérica
Voltaje funcionamiento: 5V
Controlador: HD44780
Número de columnas 16
Número de filas: 2
Comunicación: I2C
Compatible librería Arduino

![image](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/53fa1538-5e54-4a9d-8de0-1a665658aa3e)



Board puente H L298 marca Genérica para control motores
Este controlador es ideal para diseños académicos donde se quiere controlar un motor o dos motores DC, esta board es compatible con Arduino o sistemas similares

Características
Driver: L298N
Tensión de funcionamiento: 6Vdc a 24Vdc
Corriente de salida: 2A
Potencia máxima: 25W
Corriente máxima: 2A se va a calentar el disipador ten cuidado
Tamaño: 76mm * 44mm * 26mm




Consumo de energía y tiempo de baterias

![Captura de pantalla 2024-05-23 075417](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/66f45cbe-d1e3-4dff-b3a3-b8fa1db8976d)



Diagrama de bloques 

![Diagrama de bloques](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/8edc50fa-bbb6-4f64-930f-4be88e5e8c33)






Diseño circuito electrónico Utilizado para las conexciones de los diferentes actuadores, sensores y electrónica utilizada.

![Diseño electronico_page-0001](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/c04eb0fb-12cd-4ba6-9b2b-2d1d9e399891)


![Diseño electronico_page-0002](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/2ed8cffd-cbae-4f90-aa66-dbe60f371e1b)



Simulación Thinkercad:

Simulación de Evasor de Obstaculos con Interrupciones
https://www.tinkercad.com/things/lnS3gLotW7o-evasor-de-obstaculos?sharecode=9m478K4AdZ9hDG4MCgDQKTh78QYl6QmP7EFP44kt72A


Pasos a tener en cuenta: 


1- utilizar el programa de motores.ino para verificar los movimientos hacía adelante, átras, derecha e izquierda, la conexión de motores y puertos con la tarjeta de desarrollo.

![1](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/6beb7dfe-f6bb-46d8-b775-b4c26cbc65e0)






2- utilizar el progroma Evasor_de_Obstaculos.ino con este programa se comprueba y se ajusta el sensor ultrasonico con los motores actuales, además de mostrar la cantidad de objetos detectados.

![3](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/5720dd2f-caf5-4486-a811-6ad2d861dade)




3- utilizar el programa Sensor_de_linea_negra.ino con este programa se comprueba y se ajusta los sensores infrarojos de piso, lecturas en blanco y negro, además se muestra en la LCD un contador de tiempo.

![2](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/6c8b5047-d482-420d-be4c-7fbe9d5ecfd3)






4- utilizar el programa sensor_fuerza_peso.ino con este programa  se comprueba y se ajusta el sensor de fuerza y la conversión a peso, mostrando el monitor serial.






5- con los ajustes anteriores se crea el código Auto_muestras.ino se donde se integra los anteriores códigos calibrados para su operación. 

![7](https://github.com/Ing-CarlosNova/Auto-guiado/assets/15624468/605ff877-3104-48de-be8f-e94bbe07a424)


