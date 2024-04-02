# Proyecto Intermedio

Por favor antes de ejecutar las intrucciones, lea el siguiente archivo con cuidado.

Asegúrese de estar dentro del directorio en el cual se encuentra este documento y ejecute los siguientes comandos en función de la acción que busque realizar.

1. Para compilar y ejecutar el código base con sanitizers, optimización y generar las gráficas. Las gráficas son guardadas en el directorio `output`.

	```
	make
	```

	**Nota:** Los códigos de gnuplot con los que se realiza la graficación, están elaborados para los valores del informe. No garantizamos un buen ajuste de ejes para otros valores.

2. Para compilar y ejecutar sin optimización. No tiene contemplado la generación de gráficas.

	```
	make no_optimized
	```

3. Para hacer los test usando `catch2`. No utiliza banderas de optimización.

	```
	make test
	```

4. Para hacer profiling con `gprof`. No utiliza banderas de optimización. El reporte es generado en el directorio `report`.

	```
	make gprof
	```

5. Para hacer profiling con `valgrind-cachegrind`. No utiliza banderas de optimización. El reporte es generado en el directorio `report`.

	```
	make cachegrind
	```

6. Para evaluar el uso de memoria con `valgrind-memcheck`. No utiliza banderas de optimización.

	```
	make memcheck
	```

**Nota:** Por defecto el programa esta leyendo un archivo de parámetros de entrada con la siguiente ruta `code/input/input.txt`, sin embargo, para realizar el profiling y evaluar el uso de memoria, el archivo de entrada cambia a `code/input/input-profiling.txt` debido a los tiempos de ejecución y el no uso de banderas de optimización, los cuales no generan un cambio dentro de estos procesos.

Es por ello que la generación de gráficas utilizadas en el reporte se realiza únicamente cuando se utiliza el comando `make`.