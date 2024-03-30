# Proyecto Intermedio

**Nota:** Por favor antes de ejecutar las intrucciones, lea el siguiente archivo con cuidado.

Asegúrese de estar dentro del directorio en el cual se encuentra este documento y ejecute los siguientes comandos en función de la acción que busque realizar.

1. Para compilar y ejecutar el código base sin optimización y generar las gráficas.

	```
	make
	```

2. Para compilar y ejecutar con optimización

	```
	make run_optimized
	```

3. Para hacer los test usando `catch2`.

	```
	make test
	```

4. Para hacer profiling con `gprof`.

	```
	make gprof
	```

5. Para hacer profiling con `valgrind-cachegrind`.

	```
	make cachegrind
	```

6. Para evaluar el uso de memoria con `valgrind-memcheck`.

	```
	make memcheck
	```