LabQuimicaNXT
=============

Sifteo Chemistry Lab using sifteo next generation SDK

Para compilar o projeto é precisar fazer algumas modificações no SDK do sifteo.

Essas modificações estão descritas nos commits a baixo:

* cdb82dfcf1b6c286f506d87050c576a1c1b85607
* 27aa793a05fbf4008084ca2154cf3681ee861632

Para usar o simulador é preciso dizer explicitamente que precisa de 4 cubos, então use o seguinte comando:

`siftulator -n 4 labquimica.elf`
